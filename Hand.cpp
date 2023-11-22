#include "Hand.h"

ostream& operator<<(ostream& cout, Hand& hand) {

	vector<Card>::iterator it = hand.getCards().begin();
	
	while (it != hand.getCards().end() - 1)
	{
		cout << *it << "-";
		it++;
	}
	cout << *it << " ";

	return cout;
}

Hand::Hand(vector<string> cardsStr) {
	for (Card c : cardsStr) {
		cards.push_back(c);
	}
}

vector<Card>& Hand::getCards() {
	return this->cards;
}