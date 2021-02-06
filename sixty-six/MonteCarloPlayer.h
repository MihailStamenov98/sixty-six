#pragma once
#include "Player.h"
#include <math.h> 
#include<vector>

class MonteCarloPlayer: Player
{
private:

	enum Anounces
	{
		no = 0,
		twenty = 20,
		forty = 40
	};

	struct Node
	{
		double t;
		int n;
		vector<Node*> children;
	};

	Color trump;

	int getRandomIndex(int elementsCount);
	double rollOutFirstPlay(vector<Card> myCards, vector<Card> passedCards, vector<Anounces> myAnounces, vector<Anounces> oponentAnounces);
	double rollOutSecondPlay(Card firstCard, vector<Card> myCards, vector<Card> passedCards, vector<Anounces> myAnounces, vector<Anounces> oponentAnounces);
	double evaluateNode(double t, int N, int ni);
public:
	MonteCarloPlayer(Color trump);
	void printCards(vector<Card> maxCards);
	int chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards);
	int chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards);

};