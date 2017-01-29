#pragma once
#include <string>
#include <vector>
#include <boost\multi_array.hpp>

std::string getPlayerName(std::istream &inRead);

//Minimal play data, if more is needed then make a class/struct object with one of these structs as a member.
struct GamePlayer
{
	std::string playerName;
	std::size_t playerNumber;
	char playerIdentShort;
};

void initPlayerList(std::vector<GamePlayer> &playerList, std::istream &inRead, std::ostream &outRead, char *shortsList);

template <typename T, typename F, typename Z>
T getInput(std::istream &inRead, std::ostream &outRead, std::string prompt, T &userInput, F valFcn, Z usingClass)
{
	while (true)
	{
		outRead << prompt;
		inRead >> userInput;
		if (inRead.fail())
		{
			inRead.clear();
			inRead.ignore(100, '\n');
		}
		else if (((*usingClass).*valFcn)(userInput))
		{
			inRead.ignore(100, '\n');
			return userInput;
		}
		outRead << "Invalid input, try again. ";
	}
}

class RectGameBoard
{
public:
	RectGameBoard(std::size_t width, std::size_t height);
	void placeInSquare(std::size_t i, std::size_t j, char placed);
	char getFromSquare(size_t i, size_t j)
	{
		if (i < m_height && j < m_width) { return boardContents[i][j]; } return '_';
	}
	friend std::ostream& operator<< (std::ostream &out, const RectGameBoard &rgBoard);
	virtual bool victoryReached() = 0;
	virtual bool gameTied() = 0;
	char currPlayer() { return getFromSquare(lastPlacedRow, lastPlacedCol); }
	bool noPlaysYet() { return (lastPlacedRow == m_height || lastPlacedCol == m_width); }
	std::size_t width() { return m_width; }
	std::size_t height() { return m_height; }

protected:
	const std::size_t m_width, m_height;
	boost::multi_array<char, 2> boardContents;
	std::size_t lastPlacedRow, lastPlacedCol;

};

class RectGame
{
public:
	RectGame();
	~RectGame();
	bool checkEnding();
	std::string playerFromIdent(char ident);
	virtual void playTurn() = 0;
	char nextPlacedIdent();
	void playGame();
protected:
	RectGameBoard* m_board;
	std::vector<GamePlayer> m_playerNameList;
};

