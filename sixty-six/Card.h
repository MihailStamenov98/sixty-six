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


class Card
{
private:
	Color color;
	Value value;
public:
	Card(Color c, Value v);
	Card(const Card& card);

	bool isGreater(Card secondCard, Color coz);
	
	bool operator!=(const Card& secondCard);

	int getValue();

	Color getColor();

	string getName();

	string getColorName();
};