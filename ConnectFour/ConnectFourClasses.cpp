#include "stdafx.h"
#include "ConnectFourClasses.h"
#include "gameutils.h"
#include <iostream>

void ConnectFourBoard::placeInColumn(std::size_t j, char placed)
{
	for (std::size_t i_plus = m_height; i_plus > 0; i_plus--)
	{
		std::size_t i = i_plus - 1;
		if (getFromSquare(i, j) == '_') { placeInSquare(i, j, placed); return; }
	}
	return;
}

bool ConnectFourBoard::columnFull(std::size_t j)
{
	for (std::size_t i_plus = m_height; i_plus > 0; i_plus--)
	{
		std::size_t i = i_plus - 1;
		if (getFromSquare(i, j) == '_') { return false; }
	}
	return true;
}

bool ConnectFourBoard::victoryReached()
{
	int counts[3][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };
	bool going[3][3] = { { true,true,true },{ true,false,true },{ true,true,true } };
	std::size_t rowIndex[3][3] = { { lastPlacedRow,lastPlacedRow,lastPlacedRow },
	{ lastPlacedRow,lastPlacedRow,lastPlacedRow },
	{ lastPlacedRow,lastPlacedRow,lastPlacedRow } };
	std::size_t colIndex[3][3] = { { lastPlacedCol,lastPlacedCol,lastPlacedCol },
	{ lastPlacedCol,lastPlacedCol,lastPlacedCol },
	{ lastPlacedCol,lastPlacedCol,lastPlacedCol } };
	bool cont = true;
	while (cont)
	{
		cont = false;
		for (std::size_t i = 0; i < 3; i++)
		{
			for (std::size_t j = 0; j < 3; j++)
			{
				std::size_t nextRow = rowIndex[i][j] + i;
				std::size_t nextCol = colIndex[i][j] + j;
				if (nextRow <= 0 || nextRow > m_height || nextCol <= 0 || nextCol > m_width) { going[i][j] = false; }
				else if (getFromSquare(--nextRow, --nextCol) != currPlayer()) { going[i][j] = false; }
				else {
					rowIndex[i][j] = nextRow;
					colIndex[i][j] = nextCol;
				}
				cont = cont || going[i][j];
			}
		}
	}
	return (rowIndex[2][2] - rowIndex[0][0] >= 3 || rowIndex[2][1] - rowIndex[0][1] >= 3 || colIndex[0][2] - colIndex[2][0] >= 3 || colIndex[1][2] -

		colIndex[1][0] >= 3);
}

bool ConnectFourBoard::gameTied()
{
	for (auto e : boardContents)
	{
		for (auto f : e)
			if (f == '_') return false;
	}
	//going to assume victoryReached will be checked first, so a full board is always tied.
	return true;
}

void ConnectFourGame::playTurn()
{
	std::size_t playCol;
	while (true)
	{
		std::cout << playerFromIdent(nextPlacedIdent()) << ", choose a column to place an " << nextPlacedIdent() << " in." << std::endl;
		playCol = getInput(std::cin, std::cout, "Choose a column. ", playCol, &ConnectFourGame::validLocInput, this);
		if (!(static_cast<ConnectFourBoard*>(m_board)->columnFull(playCol - 1))) 
		{ 
			static_cast<ConnectFourBoard*>(m_board)->placeInColumn(playCol - 1, nextPlacedIdent()); return; 
		}
		std::cout << "That column is already full. You cannot place there." << std::endl;
	}
}
