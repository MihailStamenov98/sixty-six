#pragma once
#include<vector>
#include "Card.h"
using namespace std;


class RulesClosed
{
private:
	Color trump;
public:

	RulesClosed(Color trump);
	vector<Card> takeAlternatives(vector<Card> myCards, Card firstCard);
};
