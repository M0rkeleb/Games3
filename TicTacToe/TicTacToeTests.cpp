#include "stdafx.h"
#include "TicTacToeTests.h"
#include "TicTacToeClasses.h"

int testVictoryCondition()
{
	TicTacToeBoard myBoard1, myBoard2, myBoard3, myBoard4, myBoard5, myBoard6;
	myBoard1.placeInSquare(0, 0, 'X');
	myBoard1.placeInSquare(1, 0, 'O');
	myBoard1.placeInSquare(0, 1, 'X');
	myBoard1.placeInSquare(1, 1, 'O');
	myBoard1.placeInSquare(0, 2, 'X');
	if (!myBoard1.victoryReached()) { return 1; }
	myBoard2.placeInSquare(0, 0, 'X');
	myBoard2.placeInSquare(0, 1, 'O');
	myBoard2.placeInSquare(1, 0, 'X');
	myBoard2.placeInSquare(1, 1, 'O');
	myBoard2.placeInSquare(2, 0, 'X');
	if (!myBoard2.victoryReached()) { return 2; }
	myBoard3.placeInSquare(0, 0, 'X');
	myBoard3.placeInSquare(1, 0, 'O');
	myBoard3.placeInSquare(1, 1, 'X');
	myBoard3.placeInSquare(0, 1, 'O');
	myBoard3.placeInSquare(2, 2, 'X');
	if (!myBoard3.victoryReached()) { return 3; }
	myBoard4.placeInSquare(2, 0, 'X');
	myBoard4.placeInSquare(1, 0, 'O');
	myBoard4.placeInSquare(1, 1, 'X');
	myBoard4.placeInSquare(0, 1, 'O');
	myBoard4.placeInSquare(0, 2, 'X');
	if (!myBoard4.victoryReached()) { return 4; }
	myBoard5.placeInSquare(2, 0, 'X');
	myBoard5.placeInSquare(1, 0, 'O');
	myBoard5.placeInSquare(0, 1, 'X');
	myBoard5.placeInSquare(1, 1, 'O');
	myBoard5.placeInSquare(0, 2, 'X');
	if (myBoard5.victoryReached()) { return 5; }
	myBoard6.placeInSquare(2, 0, 'X');
	myBoard6.placeInSquare(1, 0, 'O');
	myBoard6.placeInSquare(0, 1, 'X');
	myBoard6.placeInSquare(1, 1, 'O');
	myBoard6.placeInSquare(1, 2, 'X');
	myBoard6.placeInSquare(2, 2, 'O');
	myBoard6.placeInSquare(0, 0, 'X');
	myBoard6.placeInSquare(0, 2, 'O');
	myBoard6.placeInSquare(2, 1, 'X');
	if (!myBoard6.gameTied()) { return 6; }
	return 0;
}