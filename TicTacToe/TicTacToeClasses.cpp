#include "stdafx.h"
#include "TicTacToeClasses.h"
#include "gameutils.h"
#include <iostream>

bool TicTacToeBoard::victoryReached()
{
	bool rowWin = true;
	bool colWin = true;
	bool diagDownRightWin = (lastPlacedCol == lastPlacedRow);
	bool diagUpRightWin = (lastPlacedCol + lastPlacedRow + 1 == m_dimension);
	for (size_t i = 0; i < m_dimension; i++)
	{
		rowWin = rowWin && (getFromSquare(lastPlacedRow, i) == currPlayer());
		colWin = colWin && (getFromSquare(i, lastPlacedCol) == currPlayer());
		diagDownRightWin = diagDownRightWin && (getFromSquare(i, i) == currPlayer());
		diagUpRightWin = diagUpRightWin && (getFromSquare(i, m_dimension - 1 - i) == currPlayer());
	}
	return rowWin || colWin || diagDownRightWin || diagUpRightWin;
}

bool TicTacToeBoard::gameTied()
{
	for (auto e : boardContents)
	{
		for (auto f : e)
			if (f == '_') return false;
	}
	//going to assume victoryReached will be checked first, so a full board is always tied.
	return true;
}

void TicTacToeGame::playTurn()
{
	std::size_t playRow, playCol;
	while (true)
	{
		std::cout << playerFromIdent(nextPlacedIdent()) << ", choose a square to place an " << nextPlacedIdent() << " on." << std::endl;
		playRow = getInput(std::cin, std::cout, "Choose a row. ", playRow, &TicTacToeGame::validLocInput, this);
		playCol = getInput(std::cin, std::cout, "Choose a column. ", playCol, &TicTacToeGame::validLocInput, this);
		if ((*m_board).getFromSquare(playRow - 1, playCol - 1) == '_') { (*m_board).placeInSquare(playRow - 1, playCol - 1, nextPlacedIdent()); return; }
		std::cout << "That square is already full. You cannot place there." << std::endl;
	}
}
