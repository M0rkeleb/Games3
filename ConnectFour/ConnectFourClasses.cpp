#include "stdafx.h"
#include "ConnectFourClasses.h"
#include "gameutils.h"
#include <iostream>

void ConnectFourBoard::placeInColumn(std::size_t j, char placed)
{
	for (std::size_t i_plus = height(); i_plus > 0; i_plus--)
	{
		std::size_t i = i_plus - 1;
		if (getFromSquare(i, j) == '_') { placeInSquare(i, j, placed); return; }
	}
	return;
}

bool ConnectFourBoard::columnFull(std::size_t j)
{
	for (std::size_t i_plus = height(); i_plus > 0; i_plus--)
	{
		std::size_t i = i_plus - 1;
		if (getFromSquare(i, j) == '_') { return false; }
	}
	return true;
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
		if (!(static_cast<ConnectFourBoard*>(m_board.get())->columnFull(playCol - 1))) 
		{ 
			static_cast<ConnectFourBoard*>(m_board.get())->placeInColumn(playCol - 1, nextPlacedIdent()); return; 
		}
		std::cout << "That column is already full. You cannot place there." << std::endl;
	}
}
