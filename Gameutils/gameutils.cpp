#include "gameutils.h"
#include <string>
#include <iostream>

std::string getPlayerName(std::istream &inRead)
{
	std::string pName;
	inRead >> pName;
	return pName;
}

void initPlayerList(std::vector<GamePlayer> &playerList, std::istream &inRead, std::ostream &outRead, const char *shortsList)
{
	std::size_t i = 0;
	for (auto &e : playerList)
	{
		e.playerIdentShort = *(shortsList + i);
		e.playerNumber = ++i;
		outRead << "Enter name for player " << e.playerNumber << std::endl;
		inRead >> e.playerName;
	}
}

RectGameBoard::RectGameBoard(const std::size_t width, const std::size_t height) :lastPlacedRow(height), lastPlacedCol(width), 
	                                                                 boardContents(boost::multi_array<char, 2>{boost::extents[height][width]})
{
	for (auto &e : boardContents) {
		for (auto &f : e) { f = '_'; }
	}
}

void RectGameBoard::placeInSquare(const std::size_t i, const std::size_t j, const char placed)
{
	if ((placed == 'X' || placed == 'O') && i < height() && j < width())
	{
		boardContents[i][j] = placed;
		lastPlacedRow = i;
		lastPlacedCol = j;
	}
}

template<bool const_fl, bool rev_fl>
void RectGameBoard::placeInSquare(const gen_array_2d_iterator<char, const_fl, rev_fl>& iter, const char placed)
{
	placeInSquare(iter.get_loc().first, iter.get_loc().second, placed);
}

void RectGameBoard::moveFromSquarePlus(std::size_t i, std::size_t j, char dir)
{
	auto mover = iter_from_coord(boardContents, i, i, dir);
	char to_place = *mover;
	placeInSquare(mover, '_');
	placeInSquare(++mover, to_place);
}

template<bool const_fl, bool rev_fl>
void RectGameBoard::moveFromSquareMinus(std::size_t i, std::size_t j, char dir)
{
	auto mover = iter_from_coord(boardContents, i, i, dir);
	char to_place = *mover;
	placeInSquare(mover, '_');
	placeInSquare(--mover, to_place);
}

std::ostream & operator<<(std::ostream & out, const RectGameBoard & rgBoard)
{
	for (auto e : rgBoard.boardContents)
	{
		for (auto f : e) { out << f << " "; }
		out << std::endl;
	}
	return out;
}

bool RectGameBoard::find_ina_row(const std::size_t inarow, const std::vector<char> & dir_whitelist) const
{
	std::vector<char> directions{ 'h','v','d','a' };
	if (!dir_whitelist.empty()) {
		auto limit = std::remove_if(directions.begin(), directions.end(), 
			                        [dir_whitelist](char dir) {return std::count(dir_whitelist.cbegin(), dir_whitelist.cend(), dir) > 0; });
		directions.erase(limit, directions.end());
	}
	auto the_begin = ctwo_d_begin(boardContents);
	auto the_end = ctwo_d_end(boardContents);
	for (auto dir: directions)
	{
		auto itf = citer_from_coord(boardContents, lastPlacedRow, lastPlacedCol, dir);
		while (itf != the_begin) { itf--; }
		auto pos = std::search_n(itf, the_end, inarow, currPlayer());
		if (pos != the_end) { return true; }
	}
	return false;
}

RectGame::RectGame()
{
	m_playerNameList.resize(2);
	m_board = nullptr;
	char tttIdents[2]{ 'X','O' };
	initPlayerList(m_playerNameList, std::cin, std::cout, tttIdents);
}

bool RectGame::checkEnding() const
{
	//Check if the game is over and print result.
	//First check for a win.
	if (m_board->victoryReached())
	{
		std::cout << "Game is won by " << playerFromIdent(m_board->currPlayer()) << "." << std::endl;
		return true;
	}
	//Check for a tie.
	if (m_board->gameTied())
	{
		std::cout << "Game ends in a tie." << std::endl;
		return true;
	}
	return false;
}

std::string RectGame::playerFromIdent(char ident) const
{
	for (auto e : m_playerNameList) if (ident == e.playerIdentShort) return e.playerName;
	return std::string();
}

char RectGame::nextPlacedIdent() const
{
	if (m_board->noPlaysYet()) { return 'X'; }
	if (m_board->currPlayer() == 'X') { return 'O'; }
	return 'X';
}

void RectGame::playGame()
{
	do {
		std::cout << (*m_board);
		playTurn();
	} while (!checkEnding());
	std::cout << (*m_board);
}

