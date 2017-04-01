#pragma once
#include <boost\multi_array.hpp>
#include <array_2d_iterator.hpp>
#include <string>
#include <vector>
#include <memory>
#include <exception>

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
	std::size_t width() const { return boardContents.shape()[1]; }
	std::size_t height() const { return boardContents.shape()[0]; }
	void placeInSquare(const std::size_t i, const std::size_t j, const char placed);
	template<bool const_fl, bool rev_fl>
	void placeInSquare(const gen_array_2d_iterator<char, const_fl, rev_fl> & iter, const char placed);
	char getFromSquare(const size_t i, const size_t j) const
	{
		if (i < height() && j < width()) { return boardContents[i][j]; } throw std::out_of_range("You cannot choose a square off the board.");
	}
	template<bool const_fl, bool rev_fl>
	char getFromSquare(const gen_array_2d_iterator<char, const_fl, rev_fl> & iter);
	template<bool rev_fl>
	void moveFromSquarePlus(std::size_t i, std::size_t j, char dir);
	friend std::ostream& operator<< (std::ostream &out, const RectGameBoard &rgBoard);
	bool find_ina_row(const std::size_t inarow, const std::vector<char> & dir_whitelist = std::vector<char>{}) const;
	virtual bool victoryReached() const = 0;
	virtual bool gameTied() const = 0;
	char currPlayer() const { return getFromSquare(lastPlacedRow, lastPlacedCol); }
	bool noPlaysYet() const { return (lastPlacedRow == height() || lastPlacedCol == width()); }
protected:
	boost::multi_array<char, 2> boardContents;
	std::size_t lastPlacedRow, lastPlacedCol;

};

template<bool const_fl, bool rev_fl>
inline char RectGameBoard::getFromSquare(const gen_array_2d_iterator<char, const_fl, rev_fl>& iter)
{
	if (iter.get_loc().first == 0 || iter.get_loc().second == 0) { throw std::out_of_range("You cannot choose a square off the board."); }
	return getFromSquare(iter.get_loc().first - 1, iter.get_loc().second - 1);
}

template<bool const_fl, bool rev_fl>
inline void RectGameBoard::placeInSquare(const gen_array_2d_iterator<char, const_fl, rev_fl>& iter, const char placed)
{
	if (iter.get_loc().first == 0 || iter.get_loc().second == 0) { throw std::out_of_range("You cannot choose a square off the board."); }
	placeInSquare(iter.get_loc().first - 1, iter.get_loc().second - 1, placed);
}

template<bool rev_fl>
inline void RectGameBoard::moveFromSquarePlus(std::size_t i, std::size_t j, char dir)
{
	gen_array_2d_iterator<char, false, rev_fl> mover(boardContents, i + 1, j + 1, dir);
	char to_place = getFromSquare(mover);
	++mover;
	if (getFromSquare(mover) != '_') { throw std::runtime_error("You cannot move to a filled square."); }
	placeInSquare(i, j, '_');
	placeInSquare(mover, to_place);
}


class RectGame
{
public:
	RectGame();
	bool checkEnding() const;
	std::string playerFromIdent(char ident) const;
	virtual void playTurn() = 0;
	char nextPlacedIdent() const;
	void playGame();
protected:
	std::unique_ptr<RectGameBoard> m_board;
	std::vector<GamePlayer> m_playerNameList;
};
