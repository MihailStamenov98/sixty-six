#include "MonteCarloPlayer.h"
#include<random>
double MonteCarloPlayer::evaluateNode(double t, int N, int ni)
{
	return (t / (double)ni) + sqrt(log(double(N))/double(ni));
}

int MonteCarloPlayer::getRandomIndex(int elementsCount)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> distribution(0, elementsCount-1);
	return distribution(rd);
}

double MonteCarloPlayer::rollOutFirstPlay(vector<Card> myCards, vector<Card> passedCards, vector<Anounces> myAnounces, vector<Anounces> oponentAnounces)
{
	int randIndex = getRandomIndex(myCards.size());
	Card firstCard = myCards[randIndex];

	vector<Card> knownCards;
	knownCards.insert(knownCards.end(), myCards.begin(), myCards.end());
	knownCards.insert(knownCards.end(), passedCards.begin(), passedCards.end());

	vector<Card> remainingCards = Card::getRemainingCards(knownCards);
	Card secondCard = remainingCards[getRandomIndex(remainingCards.size())];

	if (firstCard.isGreater(secondCard))
	{

	}
	return 0.0;
}


