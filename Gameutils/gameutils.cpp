#include <string>
#include "gameutils.h"

std::string getPlayerName(std::istream &inRead)
{
	std::string pName;
	inRead >> pName;
	return pName;
}

void initPlayerList(std::vector<GamePlayer> &playerList, std::istream &inRead, std::ostream &outRead, char *shortsList)
{
	std::size_t i = 0;
	for (auto &e : playerList)
	{
		e.playerIdentShort = *(shortsList + i);
		e.playerNumber = ++i;
		outRead << "Enter name for player " << e.playerNumber << std::endl;
		inRead >> e.playerName;
	}
}