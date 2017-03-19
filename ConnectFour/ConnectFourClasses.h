#pragma once

#pragma once
#include <gameutils.h>

class ConnectFourBoard : public RectGameBoard
{
public:
	ConnectFourBoard(const std::size_t width = 7, const std::size_t height = 6) : RectGameBoard(width, height) {}
	void placeInColumn(const std::size_t j, const char placed);
	bool columnFull(const std::size_t j) const;
	bool victoryReached() const override { return find_ina_row(4); }
	bool gameTied() const override;
private:

};

class ConnectFourGame : public RectGame
{
public:
	ConnectFourGame(const std::size_t width = 7, const std::size_t height = 6) { m_board = std::make_unique<ConnectFourBoard>(width, height); }
	void playTurn() override;
	bool validLocInput(const std::size_t userInput) const { return (userInput >= 1 && userInput <= m_board->width()); }
private:

};
