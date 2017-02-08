#pragma once
#include <string>
#include "gameutils.h"

class TicTacToeBoard : public RectGameBoard
{
public:
	TicTacToeBoard(const std::size_t dimension = 3) : RectGameBoard(dimension, dimension) {}
	std::size_t size() { return this->height(); }
	bool victoryReached() override { return find_ina_row(this->size()); }
	bool gameTied() override;
private:

};

class TicTacToeGame : public RectGame
{
public:
	TicTacToeGame(const std::size_t dimension = 3) { m_board = std::make_unique<TicTacToeBoard>(dimension); }
	void playTurn() override;
	bool validLocInput(const std::size_t userInput) { return (userInput >= 1 && userInput <= static_cast<TicTacToeBoard*>(m_board.get())->size()); }
private:

};

