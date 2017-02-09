#include "stdafx.h"
#include "ConnectFourClasses.h"
#include "gameutils.h"
#include <iostream>

void ConnectFourBoard::placeInColumn(const std::size_t j, const char placed)
{
	for (auto i_plus = height(); i_plus > 0; i_plus--)
	{
		auto i = i_plus - 1;
		if (getFromSquare(i, j) == '_') { placeInSquare(i, j, placed); return; }
	}
	return;
}

bool ConnectFourBoard::columnFull(const std::size_t j) const
{
	for (auto i_plus = height(); i_plus > 0; i_plus--)
	{
		auto i = i_plus - 1;
		if (getFromSquare(i, j) == '_') { return false; }
	}
	return true;
}

bool ConnectFourBoard::gameTied() const
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
