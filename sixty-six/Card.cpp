#include "Card.h"

Card::Card(Color c, Value v)
{
	color = c;
	value = v;
}

Card::Card(const Card& card)
{
	color = card.color;
	value = card.value;
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

string Card::getName()
{
	switch (value)
	{
	case nine:
		return "9";
		break;
	case jack:
		return "J";
		break;
	case queen:
		return "Q";
		break;
	case king:
		return "K";
		break;
	case ten:
		return "10";
		break;
	case ace:
		return "A";
		break;
	default:
		return "";
		break;
	}
}

string Card::getColorName()
{
	switch (color)
	{
	case clubs:
		return "clubs";
		break;
	case diamonds:
		return "diamonds";
		break;
	case hearts:
		return "hearts";
		break;
	case spades:
		return "spades";
		break;
	default:
		return "";
		break;
	}
}