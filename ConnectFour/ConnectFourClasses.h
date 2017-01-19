#pragma once

#pragma once
#include <string>
#include <gameutils.h>

class ConnectFourBoard
{
public:
	ConnectFourBoard(std::size_t width = 7, std::size_t height = 6);
	void placeInSquare(std::size_t i, std::size_t j, char placed);
	void placeInColumn(std::size_t j, char placed);
	char getFromSquare(size_t i, size_t j)
	{
		if (i < m_height && j < m_width) { return boardContents[i][j]; } return '_';
	}
	friend std::ostream& operator<< (std::ostream &out, const ConnectFourBoard &tttBoard);
	bool columnFull(std::size_t j);
	bool victoryReached();
	bool gameTied();
	char currPlayer() { return getFromSquare(lastPlacedRow, lastPlacedCol); }
	bool noPlaysYet() { return (lastPlacedRow == m_height || lastPlacedCol == m_width); }
	std::size_t width() { return m_width; }
	std::size_t height() { return m_height; }
private:
	const std::size_t m_width, m_height;
	std::vector<std::vector<char>> boardContents;
	std::size_t lastPlacedRow, lastPlacedCol;

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
