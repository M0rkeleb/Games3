#pragma once
#include <string>
#include <vector>

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

class GameBoard
{
public:
	GameBoard()
	{
	}

	~GameBoard()
	{
	}

private:

};

