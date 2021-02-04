#include<iostream>
#include "EndGame.h"
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
Color colors[4] = { clubs, diamonds, hearts, spades };
Value values[6] = { nine, jack, queen, king, ten, ace };

vector<Card> getDeck()
{
	vector<Card> deck;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			Card temp(colors[i], values[j]);
			deck.push_back(temp);
		}
	}
	unsigned seed = std::chrono::system_clock::now()
		.time_since_epoch()
		.count();
	std::shuffle(std::begin(deck), std::end(deck), std::default_random_engine(seed));
	return deck;
}

int main()
{
	vector<Card> deck = getDeck();
	vector<Card>::const_iterator first = deck.begin() + 0;
	vector<Card>::const_iterator last = deck.begin() + 6;
	vector<Card> newVec(first, last);
	first = deck.begin() + 7;
	last = deck.begin() + 13;
	vector<Card> secVec(first, last);
	vector<Card> comp;
	EndGame game(diamonds, newVec, secVec);
	game.play();
	return 0;
}