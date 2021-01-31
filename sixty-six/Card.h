#pragma once
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

	bool isGreater(Card secondCard, Color coz);
	
	bool operator!=(const Card& secondCard);

	int getValue();

	Color getColor();
};