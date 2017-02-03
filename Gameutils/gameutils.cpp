#include "gameutils.h"
#include <string>
#include <iostream>

std::string getPlayerName(std::istream &inRead)
{
	std::string pName;
	inRead >> pName;
	return pName;
}

void initPlayerList(std::vector<GamePlayer> &playerList, std::istream &inRead, std::ostream &outRead, char *shortsList)
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

RectGameBoard::RectGameBoard(std::size_t width, std::size_t height) :m_width(width), m_height(height), lastPlacedRow(height), lastPlacedCol(width)//, boardContents(boost::multi_array<char, 2>{boost::extents[height][width]})
{
	boardContents.resize(boost::extents[height][width]);
	for (auto &e : boardContents) {
		for (auto &f : e) { f = '_'; }
	}
}

void RectGameBoard::placeInSquare(std::size_t i, std::size_t j, char placed)
{
	if ((placed == 'X' || placed == 'O') && i < m_height && j < m_width)
	{
		boardContents[i][j] = placed;
		lastPlacedRow = i;
		lastPlacedCol = j;
	}
}

std::ostream & operator<<(std::ostream & out, const RectGameBoard & tttBoard)
{
	for (auto e : tttBoard.boardContents)
	{
		for (auto f : e) { out << f << " "; }
		out << std::endl;
	}
	return out;
}

RectGame::RectGame()
{
	m_playerNameList.resize(2);
	m_board = nullptr;
	char tttIdents[2]{ 'X','O' };
	initPlayerList(m_playerNameList, std::cin, std::cout, tttIdents);
}

RectGame::~RectGame()
{
	delete m_board;
}

bool RectGame::checkEnding()
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

std::string RectGame::playerFromIdent(char ident)
{
	for (auto e : m_playerNameList) if (ident == e.playerIdentShort) return e.playerName;
	return std::string();
}

char RectGame::nextPlacedIdent()
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

