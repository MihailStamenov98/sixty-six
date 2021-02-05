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
	else if (color == secondCard.color)
	{
		return value > secondCard.value;
	}
	else
	{
		return true;
	}
}

bool Card::operator!=(const Card& secondCard)
{
	return (color != secondCard.color || value != secondCard.value);
}

int Card::getValue() const
{
	return value;
}

Color Card::getColor() const
{
	return color;
}

string Card::getName() const
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

string Card::getColorName() const
{
	return getColorString(color);
}

string getColorString(Color color)
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

bool operator==(const Card& lhs, const Card& rhs)
{
	return (lhs.getColorName() == rhs.getColorName()) && (lhs.getValue() == rhs.getValue());
}