#pragma once
# include "Player.h"
# include "EndGamePlayer.h"
# include "HumanPlayer.h"
class GameController
{
private:
	vector<Card> minPlayerCards;
	vector<Card> maxPlayerCards;
	Color trump;
	Player* computerPlayer;//uses maxCards
	Player* humanPlayer;
	pair<int, int> trickComputerFirst(int computerResult, int oponentResult, bool hasTrickMax, bool hasTrickMin);
	pair<int, int> trickComputerSecond(int computerResult, int oponentResult, bool hasTrickMax, bool hasTrickMin);
	vector<Card> getDeck();
public:
	GameController();
	void play();
	void printCards();
};