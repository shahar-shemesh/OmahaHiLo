#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

#include "Card.h"
#include "Hand.h"
#include "Board.h"

using namespace std;


vector<string> stringToCards(string& s, string sub) {
	int pos = s.find(sub);
	s.erase(pos, sub.length());

	stringstream sStream(s);
	string card;
	vector<string> cards;

	while (getline(sStream, card, '-'))
	{
		cards.push_back(card);
	}

	return cards;
}


int main() {

	ifstream input;
	ofstream output;
	input.open("input.txt");	
	output.open("output.txt");

	string HandA;
	string HandB;
	string Brd;

	while (input >> HandA >> HandB >> Brd)
	{
		Hand A(stringToCards(HandA, "HandA:"));
		Hand B(stringToCards(HandB, "HandB:"));
		Board board(stringToCards(Brd, "Board:"));

		board.join(A);
		board.join(B);

		char currentCh = 'A';
		for (Hand currentHand : board.getHands()) {
			vector<Card>::iterator it = currentHand.getCards().begin();

			cout << "Hand" << currentCh << ":";
			output << "Hand" << currentCh++ << ":";

			while (it != currentHand.getCards().end() - 1)
			{
				cout << *it << "-";
				output << *it << "-";
				it++;
			}
			cout << *it << " ";
			output << *it << " ";
		}

		vector<Card>::iterator it = board.getCards().begin();
		cout << "Board:";
		output << "Board:";

		while (it != board.getCards().end() - 1)
		{
			cout << *it << "-";
			output << *it << "-";
			it++;
		}
		cout << *it << endl;
		output << *it << endl;

		cout << "=> " << board.whoWinsHi() << ";   ";
		output << "=> " << board.whoWinsHi() << ";   ";

		cout << "=> " << board.whoWinsLo() << "\n\n";
		output << "=> " << board.whoWinsLo() << "\n\n";

	}


	input.close();
	output.close();


	return 0;
}