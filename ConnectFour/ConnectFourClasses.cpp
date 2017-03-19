#include "stdafx.h"
#include "ConnectFourClasses.h"
#include <iostream>

void ConnectFourBoard::placeInColumn(const std::size_t j, const char placed)
{
	for (auto i = height(); i > 0; )
	{
		if (getFromSquare(--i, j) == '_') { placeInSquare(i, j, placed); return; }
	}
	return;
}

bool ConnectFourBoard::columnFull(const std::size_t j) const
{
	//Since we fill from the bottom up we only need to check the top row
	return (getFromSquare(0, j) != '_');
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
