#pragma once
#include <string>
#include "gameutils.h"

class TicTacToeBoard : public RectGameBoard
{
public:
	TicTacToeBoard(std::size_t dimension = 3) : RectGameBoard(dimension, dimension), m_dimension(dimension) {}
	bool victoryReached();
	bool gameTied();
	std::size_t size() { return m_dimension; }
private:
	const std::size_t m_dimension;

};

class TicTacToeGame
{
public:
	TicTacToeGame(std::size_t dimension = 3);
	~TicTacToeGame();
	bool checkEnding();
	std::string playerFromIdent(char ident);
	void playTurn();
	char nextPlacedIdent();
	void playGame();
	bool validLocInput(std::size_t userInput) { return (userInput >= 1 && userInput <= (*(m_board)).size()); }
private:
	TicTacToeBoard* m_board;
	std::vector<GamePlayer> m_playerNameList;

};

