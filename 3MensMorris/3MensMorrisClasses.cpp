#include "stdafx.h"
#include "3MensMorrisClasses.h"
#include "gameutils.h"
#include <iostream>

bool ThrMenMorBoard::gameTied() const
{
	for (auto e : boardContents)
	{
		for (auto f : e)
			if (f == '_') return false;
	}
	//going to assume victoryReached will be checked first, so a full board is always tied.
	return true;
}

void ThrMenMorGame::playTurn()
{
	std::size_t playRow, playCol;
	while (true)
	{
		std::cout << playerFromIdent(nextPlacedIdent()) << ", choose a square to place an " << nextPlacedIdent() << " on." << std::endl;
		playRow = getInput(std::cin, std::cout, "Choose a row. ", playRow, &ThrMenMorGame::validLocInput, this);
		playCol = getInput(std::cin, std::cout, "Choose a column. ", playCol, &ThrMenMorGame::validLocInput, this);
		if (m_board->getFromSquare(playRow - 1, playCol - 1) == '_') { m_board->placeInSquare(playRow - 1, playCol - 1, nextPlacedIdent()); return; }
		std::cout << "That square is already full. You cannot place there." << std::endl;
	}
}