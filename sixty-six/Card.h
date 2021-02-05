#pragma once
#include<iostream>
#include<string>
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
	clubs,
	diamonds,
	hearts,
	spades
};

string getColorString(Color color);

class Card
{
private:
	Color color;
	Value value;
public:
	friend bool operator==(const Card& lhs, const Card& rhs);

	Card(Color c, Value v);
	Card(const Card& card);

	bool isGreater(Card secondCard, Color coz);
	
	bool operator!=(const Card& secondCard);

	int getValue() const;

	Color getColor() const;

	string getName() const;

	string getColorName() const;
};

const Color colors[4] = { clubs, diamonds, hearts, spades };
const Value values[6] = { nine, jack, queen, king, ten, ace };