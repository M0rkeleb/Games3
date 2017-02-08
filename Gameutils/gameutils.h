#pragma once
#include <boost\multi_array.hpp>
#include <array_2d_iterator.hpp>
#include <string>
#include <vector>
#include <memory>

std::string getPlayerName(std::istream &inRead);

//Minimal play data, if more is needed then make a class/struct object with one of these structs as a member.
struct GamePlayer
{
	std::string playerName;
	std::size_t playerNumber;
	char playerIdentShort;
};

void initPlayerList(std::vector<GamePlayer> &playerList, std::istream &inRead, std::ostream &outRead, const char *shortsList);

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
	RectGameBoard(const std::size_t width, const std::size_t height);
	std::size_t width() { return boardContents.shape()[1]; }
	std::size_t height() { return boardContents.shape()[0]; }
	void placeInSquare(const std::size_t i, const std::size_t j, const char placed);
	char getFromSquare(const size_t i, const size_t j)
	{
		if (i < height() && j < width()) { return boardContents[i][j]; } return '_';
	}
	friend std::ostream& operator<< (std::ostream &out, const RectGameBoard &rgBoard);
	bool find_ina_row(const std::size_t inarow);
	virtual bool victoryReached() = 0;
	virtual bool gameTied() = 0;
	char currPlayer() { return getFromSquare(lastPlacedRow, lastPlacedCol); }
	bool noPlaysYet() { return (lastPlacedRow == height() || lastPlacedCol == width()); }
protected:
	boost::multi_array<char, 2> boardContents;
	std::size_t lastPlacedRow, lastPlacedCol;

};


class RectGame
{
public:
	RectGame();
	bool checkEnding();
	std::string playerFromIdent(char ident);
	virtual void playTurn() = 0;
	char nextPlacedIdent();
	void playGame();
protected:
	std::unique_ptr<RectGameBoard> m_board;
	std::vector<GamePlayer> m_playerNameList;
};

