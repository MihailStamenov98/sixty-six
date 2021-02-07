#pragma once
# include "Player.h"
# include "EndGamePlayer.h"
# include "HumanPlayer.h"
# include "MonteCarloPlayer.h"
class GameController
{
private:
	vector<Card> minPlayerCards;
	vector<Card> maxPlayerCards;
	Color trump;
	MonteCarloPlayer* computerPlayer;//uses maxCards
	Player* humanPlayer;
	pair<int, int> trickComputerFirst(int computerResult, int oponentResult, bool hasTrickMax, bool hasTrickMin);
	pair<int, int> trickComputerSecond(int computerResult, int oponentResult, bool hasTrickMax, bool hasTrickMin);
	vector<Card> getDeck();
public:
	GameController();
	void play();
	void printCards();
};