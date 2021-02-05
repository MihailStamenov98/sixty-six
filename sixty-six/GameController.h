#pragma once
# include "Player.h"
class GameController
{
private:
	Player* player1;
	Player* player2;
	pair<int, int> trickComputerFirst(int computerResult, int oponentResult);
	pair<int, int> trickComputerSecond(int computerResult, int oponentResult);
public:
	void play();
	void printCards();
};