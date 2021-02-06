#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

enum Value
{
	nine = 0,
	jack = 2,
	queen = 3,
	king = 4,
	ten = 10,
	ace = 11
};

enum Color
{
	clubs = 1,
	diamonds = 2,
	hearts = 3,
	spades = 4
};

string getColorString(Color color);

class Card
{
private:
	Color color;
	Value value;
public:
	friend bool operator==(const Card& lhs, const Card& rhs);
	friend bool operator<(const Card& lhs, const Card& rhs);

	Card(Color c, Value v);
	Card(const Card& card);

	bool isGreater(Card secondCard, Color coz);
	
	bool operator!=(const Card& secondCard);

	int getValue() const;

	Color getColor() const;

	string getName() const;

	string getColorName() const;

	static vector<Card> getRemainingCards(vector<Card> passedCards);
};

const Color colors[4] = { clubs, diamonds, hearts, spades };
const Value values[6] = { nine, jack, queen, king, ten, ace };
const vector<Card> deck = { Card(clubs,nine), Card(clubs,jack), Card(clubs,queen), Card(clubs,king), Card(clubs,ten), Card(clubs,ace),
							Card(diamonds,nine), Card(diamonds,jack), Card(diamonds,queen), Card(diamonds,king), Card(diamonds,ten), Card(diamonds,ace),
							Card(hearts,nine), Card(hearts,jack), Card(hearts,queen), Card(hearts,king), Card(hearts,ten), Card(hearts,ace),
							Card(spades,nine), Card(spades,jack), Card(spades,queen), Card(spades,king), Card(spades,ten), Card(spades,ace)};