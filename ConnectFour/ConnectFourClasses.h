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

class ConnectFourGame
{
public:
	ConnectFourGame(std::size_t width = 7, std::size_t height = 6);
	~ConnectFourGame();
	bool checkEnding();
	std::string playerFromIdent(char ident);
	void playTurn();
	char nextPlacedIdent();
	void playGame();
	bool validLocInput(std::size_t userInput) { return (userInput >= 1 && userInput <= m_board->width()); }
private:
	ConnectFourBoard* m_board;
	std::vector<GamePlayer> m_playerNameList;

};
