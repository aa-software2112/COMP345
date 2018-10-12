/*
 * Deck.h
 *
 *  Created on: Oct 10, 2018
 *      Author: Daniel
 */

#ifndef RISKAPPLICATION_H_DECK_H_
#define RISKAPPLICATION_H_DECK_H_

#include "Card.h"
#include <cstdio>
#include <algorithm>

#include <time.h>
using namespace std;

class Deck {
private:
	int numCards;
	Card* cards;

public:
	Deck(int numOfCountries) {

		numCards = numOfCountries;

		cards = new Card[numOfCountries];

		int start = 0;
		int end = numOfCountries;

		// Creating infantry
		for (int i = start; i < start + end/3; i++) {

			cards[i].setType(INFANTRY);

		}

		// Helping us have an equal amount of each type
		start = start + end / 3;

		// Creating artillery
		for (int i = start; i < start + end / 3; i++) {

			cards[i].setType(ARTILLERY);

		}
		start = start + end / 3;
		for (int i = start; i < start + end / 3; i++) {

			cards[i].setType(CAVALRY);

		}

		start = start + end / 3;

		// If deck is not divisible by 3, it will have at most one more card
			cardType type[3] = { INFANTRY, ARTILLERY, CAVALRY };
			int count = 0;
			for (int i = start; i < end; i++) {

				cards[i].setType(type[count]);
				count++;
				if (count > 3) {

					count = 0;

				}
			}

			// Shuffle deck
			srand(time(NULL));
			random_shuffle(&cards[0], &cards[end]);

	}

	Card* get_deck();
	int get_numCards();
	void set_cards(Card *deck);
	Card draw();

};


#endif /* RISKAPPLICATION_H_DECK_H_ */
