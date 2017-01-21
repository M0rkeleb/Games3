#pragma once

#pragma once
#include <string>
#include <gameutils.h>

class ConnectFourBoard : public RectGameBoard
{
public:
	ConnectFourBoard(std::size_t width = 7, std::size_t height = 6) : RectGameBoard(width, height) {}
	void placeInColumn(std::size_t j, char placed);
	bool columnFull(std::size_t j);
	bool victoryReached() override;
	bool gameTied() override;
private:

};

class ConnectFourGame : public RectGame
{
public:
	ConnectFourGame(std::size_t width = 7, std::size_t height = 6) { m_board = new ConnectFourBoard(width, height); }
	void playTurn() override;
	bool validLocInput(std::size_t userInput) { return (userInput >= 1 && userInput <= m_board->width()); }
private:

};
