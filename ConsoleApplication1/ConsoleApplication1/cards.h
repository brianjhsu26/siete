/* *************************************
Ricardo Salazar, February 26, 2015

Interface of a simple Card class
************************************* */

#include <string>
#include <vector>
#include <fstream>

#ifndef CARDS_H
#define CARDS_H

using namespace std;

enum suit_t { OROS, COPAS, ESPADAS, BASTOS };

/*
The values for this type start at 0 and increase by one
afterwards until they get to SIETE.
The rank reported by the function Card::get_rank() below is
the value listed here plus one.
E.g:
The rank of AS is reported as    static_cast<int>(AS) + 1   = 0 + 1 =  1
The rank of SOTA is reported as  static_cast<int>(SOTA) + 1 = 9 + 1 = 10
*/
enum rank_t { AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA = 9, CABALLO = 10, REY = 11 };

class Card {
public:
	// Constructor assigns random rank & suit to card.
	Card();

	// Accessors 
	string get_spanish_suit() const;
	string get_spanish_rank() const;

	/*
	These are the only functions you'll need to code
	for this class. See the implementations of the two
	functions above to get an idea of how to proceed.
	*/
	string get_english_suit() const;
	string get_english_rank() const;

	// Converts card rank to number.
	// The possible returns are: 1, 2, 3, 4, 5, 6, 7, 10, 11 and 12
	int get_rank() const;

	// Converts card rank into a value
	// Possible returns are: 0.5, 1, 2, 3, 4, 5, 6, and 7
	double get_value() const;

	// Compare rank of two cards. E.g: Eight<Jack is true.
	// Assume Ace is always 1. 
	// Useful if you want to sort the cards.
	bool operator < (Card card2) const;

private:
	suit_t suit;
	rank_t rank;
};

// A vector of Cards
class Hand {
public:
	Hand();
	void draw(); // Draws a random card from the deck 
	void show_hand();
	bool bust(); // Check if the hand has gone bust (i.e. the values of the cards exceed 7.5) [implementing... done]
	double hand_value() const; // Returns total value of cards in hand
	unsigned int compare(Hand dealer); // Compares two hands to see which as the higher value 
private:
	vector<Card> cards;
	double value;
};


class Player {
public:
	Player(int m);
	int get_balance();
	int get_total_loss();
	void exchange_money(Player& dealer, const int amount);
private:
	int money;
	int total_loss;
};

#endif