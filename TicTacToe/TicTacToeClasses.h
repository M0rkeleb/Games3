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

class TicTacToeGame : public RectGame
{
public:
	TicTacToeGame(std::size_t dimension = 3) { m_board = new TicTacToeBoard(dimension); }
	void playTurn() override;
	bool validLocInput(std::size_t userInput) { return (userInput >= 1 && userInput <= static_cast<TicTacToeBoard*>(m_board)->size()); }
private:

};

