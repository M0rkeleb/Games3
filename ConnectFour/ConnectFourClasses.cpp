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

ConnectFourGame::ConnectFourGame(std::size_t width, std::size_t height)
{
	m_playerNameList.resize(2);
	m_board = new ConnectFourBoard(width, height);
	char tttIdents[2]{ 'X','O' };
	initPlayerList(m_playerNameList, std::cin, std::cout, tttIdents);
}

ConnectFourGame::~ConnectFourGame()
{
	delete m_board;
}

bool ConnectFourGame::checkEnding()
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

std::string ConnectFourGame::playerFromIdent(char ident)
{
	for (auto e : m_playerNameList) if (ident == e.playerIdentShort) return e.playerName;
	return std::string();
}

void ConnectFourGame::playTurn()
{
	std::size_t playCol;
	while (true)
	{
		std::cout << playerFromIdent(nextPlacedIdent()) << ", choose a column to place an " << nextPlacedIdent() << " in." << std::endl;
		playCol = getInput(std::cin, std::cout, "Choose a column. ", playCol, &ConnectFourGame::validLocInput, this);
		if (!(m_board->columnFull(playCol - 1))) { m_board->placeInColumn(playCol - 1, nextPlacedIdent()); return; }
		std::cout << "That column is already full. You cannot place there." << std::endl;
	}
}

char ConnectFourGame::nextPlacedIdent()
{
	if ((*m_board).noPlaysYet()) { return 'X'; }
	if ((*m_board).currPlayer() == 'X') { return 'O'; }
	return 'X';
}

void ConnectFourGame::playGame()
{
	do {
		std::cout << (*m_board);
		playTurn();
	} while (!checkEnding());
	std::cout << (*m_board);
}
