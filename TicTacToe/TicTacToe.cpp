// TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gameutils.h"
#include "TicTacToeTests.h"
#include "TicTacToeClasses.h"
#include <iostream>
#include <string>





int main()
{
	/*GamePlayer playerNames[2];
	char tttIdents[2]{ 'X','O' };
	initPlayerList(playerNames, 2, std::cin, std::cout, tttIdents);
	std::cout << "First player name read as " << playerNames[0].playerName << std::endl;*/

	//Section for testing victory condition, comment out when not needed.
	/*int testResult = testVictoryCondition();
	if (testResult == 0) { std::cout << "No failures." << std::endl; }
	else { std::cout << "Failed test " << testResult << "." << std::endl; }*/

	TicTacToeGame the_game;
	the_game.playGame();

	return 0;
}

