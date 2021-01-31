#include "RulesClosed.h"

RulesClosed::RulesClosed(Color trump)
{
	this->trump = trump;
}

vector<Card> RulesClosed::takeAlternatives(vector<Card> myCards, Card firstCard)
{
	vector<Card> possiblePlays;
	for (int i = 0; i < myCards.size(); ++i)
	{
		if (firstCard.getColor() == myCards[i].getColor())
		{
			possiblePlays.push_back(myCards[i]);
		}
	}

	if (!possiblePlays.empty())
		return possiblePlays;

	for (int i = 0; i < myCards.size(); ++i)
	{
		if (myCards[i].getColor() == trump)
		{
			possiblePlays.push_back(myCards[i]);
		}
	}

	if (!possiblePlays.empty())
		return possiblePlays;

	return myCards;
}