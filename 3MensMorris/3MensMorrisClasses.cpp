#include "stdafx.h"
#include "3MensMorrisClasses.h"
#include <iostream>

void ThrMenMorGame::playTurn()
{
	std::size_t playRow, playCol;
	char move_dir;
	on_board_count++;
	while (true)
	{
		if (on_board_count <= 2 * morris_size)
		{
			std::cout << playerFromIdent(nextPlacedIdent()) << ", choose a square to place an " << nextPlacedIdent() << " on." << std::endl;
			playRow = getInput(std::cin, std::cout, "Choose a row. ", playRow, &ThrMenMorGame::validLocInput, this);
			playCol = getInput(std::cin, std::cout, "Choose a column. ", playCol, &ThrMenMorGame::validLocInput, this);
			if (m_board->getFromSquare(playRow - 1, playCol - 1) == '_') { m_board->placeInSquare(playRow - 1, playCol - 1, nextPlacedIdent()); return; }
			std::cout << "That square is already full. You cannot place there." << std::endl;
	    }
		else
		{
			std::cout << playerFromIdent(nextPlacedIdent()) << ", choose a square to move an " << nextPlacedIdent() << " from." << std::endl;
			playRow = getInput(std::cin, std::cout, "Choose a row. ", playRow, &ThrMenMorGame::validLocInput, this);
			playCol = getInput(std::cin, std::cout, "Choose a column. ", playCol, &ThrMenMorGame::validLocInput, this);
			if (m_board->getFromSquare(playRow - 1, playCol - 1) == nextPlacedIdent())
			{
				move_dir = getInput(std::cin, std::cout, "Choose a direction. Must be one of u,d,r,l. ", move_dir, &ThrMenMorGame::validMoveInput, this);
				try
				{
					if (move_dir == 'd') { m_board->moveFromSquarePlus<false>(playRow - 1, playCol - 1, 'v'); }
					else if (move_dir == 'u') { m_board->moveFromSquarePlus<true>(playRow - 1, playCol - 1, 'v'); }
					else if (move_dir == 'r') { m_board->moveFromSquarePlus<false>(playRow - 1, playCol - 1, 'h'); }
					else if (move_dir == 'l') { m_board->moveFromSquarePlus<true>(playRow - 1, playCol - 1, 'h'); }
					return;
				}
				catch (std::exception &exception)
				{
					std::cerr << exception.what() << '\n';
				}
			}
		}
	}
}