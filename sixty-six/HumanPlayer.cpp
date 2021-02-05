#include "HumanPlayer.h"
HumanPlayer::HumanPlayer(Color trump): rules(trump)
{
	this->trump = trump;
}

int HumanPlayer::chooseCardFirstMove(vector<Card> maxCards, vector<Card> minCards)
{
	cout << "It is human's turn (enter index of your card): ";
	int cardIndex;
	cin >> cardIndex;
	return cardIndex;
}

int HumanPlayer::chooseCardSecondMove(Card firstCard, vector<Card> maxCards, vector<Card> minCards)
{
	auto possiblePlays = rules.takeAlternatives(maxCards, firstCard);
	cout << "It is human's turn (enter index of your card): ";
	int cardIndex;
	cin >> cardIndex;
	while (std::find(possiblePlays.begin(), possiblePlays.end(), minCards[cardIndex]) != possiblePlays.end())
	{
		cout << "Enter valid card index: ";
		cin >> cardIndex;
	}
	return cardIndex;
}

void HumanPlayer::printCards(vector<Card> cards)
{
	cout << endl << "HumanPlayer cards are are:";
	for (int i = 0; i < cards.size(); ++i)
	{
		cout << "(" << cards[i].getColorName() << "," << cards[i].getName() << "), ";
	}
	cout << endl;
}