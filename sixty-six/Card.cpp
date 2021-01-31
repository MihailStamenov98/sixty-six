#include "Card.h"

Card::Card(Color c, Value v)
{
	color = c;
	value = v;
}

bool Card::isGreater(Card secondCard, Color coz)
{
	if (color == coz && secondCard.color == coz)
	{
		return value > secondCard.value;
	}
	else if (color == coz)
	{
		return true;
	}
	else if (secondCard.color == coz)
	{
		return false;
	}
	return value >= secondCard.value;
}

bool Card::operator!=(const Card& secondCard)
{
	return (color != secondCard.color || value != secondCard.value);
}

int Card::getValue()
{
	return value;
}

Color Card::getColor()
{
	return color;
}