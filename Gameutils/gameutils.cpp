#include <string>
#include "gameutils.h"

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

RectGameBoard::RectGameBoard(std::size_t width, std::size_t height) :m_width(width), m_height(height), lastPlacedRow(height), lastPlacedCol(width)
{
	boardContents.resize(height);
	for (auto &e : boardContents)
	{
		e.resize(width);
		for (auto &f : e)
			f = '_';
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