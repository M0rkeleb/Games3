#pragma once
#include <string>
#include "gameutils.h"

const std::size_t morris_size = 3;

class ThrMenMorBoard : public RectGameBoard
{
public:
	ThrMenMorBoard() : RectGameBoard(morris_size, morris_size) {}
	bool victoryReached() const override { return find_ina_row(morris_size); }
	bool gameTied() const override;
private:

};

class ThrMenMorGame : public RectGame
{
public:
	ThrMenMorGame() : on_board_count(0) { m_board = std::make_unique<ThrMenMorBoard>(); }
	void playTurn() override;
	bool validLocInput(const std::size_t userInput) const { return (userInput >= 1 && userInput <= morris_size); }
private:
	std::size_t on_board_count;
};