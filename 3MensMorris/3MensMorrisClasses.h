#pragma once
#include "gameutils.h"
#include <string>

const std::size_t morris_size = 3;

class ThrMenMorBoard : public RectGameBoard
{
public:
	ThrMenMorBoard() : RectGameBoard(morris_size, morris_size) {}
	bool victoryReached() const override { return find_ina_row(morris_size, std::vector<char>{'a', 'd'}); }
	bool gameTied() const override { return false; }
private:

};

class ThrMenMorGame : public RectGame
{
public:
	ThrMenMorGame() : on_board_count(0), dir_moves("udrl") { m_board = std::make_unique<ThrMenMorBoard>(); }
	void playTurn() override;
	bool validLocInput(const std::size_t userInput) const { return (userInput >= 1 && userInput <= morris_size); }
	bool validMoveInput(const char userInput) const { return dir_moves.find(userInput) != std::string::npos; }
private:
	std::size_t on_board_count;
	std::string dir_moves;
};