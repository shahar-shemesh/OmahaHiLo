#include "Card.h"

ostream& operator<<(ostream& cout, const Card& c) {
	cout << c.rank << c.suit;
	return cout;
}

Card::Card(string card) {
	this->rank = card[0];
	this->suit = card[1];
}

char Card::getRank() {
	return this->rank;
}

char Card::getSuit() {
	return this->suit;
}