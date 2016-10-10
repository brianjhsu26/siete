#include "cards.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>


/* *************************************************
Card class
************************************************* */
Card::Card(){
	int r = 1 + rand() % 4;
	switch (r) {
	case 1: suit = OROS; break;
	case 2: suit = COPAS; break;
	case 3: suit = ESPADAS; break;
	case 4: suit = BASTOS; break;
	default: break;
	}

	r = 1 + rand() % 10;
	switch (r) {
	case  1: rank = AS; break;
	case  2: rank = DOS; break;
	case  3: rank = TRES; break;
	case  4: rank = CUATRO; break;
	case  5: rank = CINCO; break;
	case  6: rank = SEIS; break;
	case  7: rank = SIETE; break;
	case  8: rank = SOTA; break;
	case  9: rank = CABALLO; break;
	case 10: rank = REY; break;
	default: break;
	}
}

// Accessor: returns a string with the suit of the card in Spanish 
string Card::get_spanish_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "oros";
		break;
	case COPAS:
		suitName = "copas";
		break;
	case ESPADAS:
		suitName = "espadas";
		break;
	case BASTOS:
		suitName = "bastos";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in Spanish 
string Card::get_spanish_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "As";
		break;
	case DOS:
		rankName = "Dos";
		break;
	case TRES:
		rankName = "Tres";
		break;
	case CUATRO:
		rankName = "Cuatro";
		break;
	case CINCO:
		rankName = "Cinco";
		break;
	case SEIS:
		rankName = "Seis";
		break;
	case SIETE:
		rankName = "Siete";
		break;
	case SOTA:
		rankName = "Sota";
		break;
	case CABALLO:
		rankName = "Caballo";
		break;
	case REY:
		rankName = "Rey";
		break;
	default: break;
	}
	return rankName;
}


// Accessor: returns a string with the suit of the card in English 
string Card::get_english_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "Golds";
		break;
	case COPAS:
		suitName = "Cups";
		break;
	case ESPADAS:
		suitName = "Swords";
		break;
	case BASTOS:
		suitName = "Clubs";
		break;
	default: break;
	}
	return suitName; 
}

// Accessor: returns a string with the rank of the card in English 
string Card::get_english_rank() const {
	string english_rank;
	switch (rank){
	case AS:
		english_rank = "One"; break;
	case DOS:
		english_rank = "Two"; break;
	case TRES:
		english_rank = "Three"; break;
	case CUATRO:
		english_rank = "Four"; break;
	case CINCO:
		english_rank = "Five"; break;
	case SEIS:
		english_rank = "Six"; break;
	case SIETE:
		english_rank = "Seven"; break;
	case SOTA:
		english_rank = "Ten"; break;
	case CABALLO:
		english_rank = "Eleven"; break;
	case REY:
		english_rank = "Twelve"; break;
	}
	return english_rank;
}


// Assigns a numerical value to card based on rank.
// AS=1, DOS=2, ..., SIETE=7, SOTA=10, CABALLO=11, REY=12
int Card::get_rank() const {
	return static_cast<int>(rank)+1;
}

// Returns the value of the card
double Card::get_value() const{
	if ((this->get_english_rank() == "Ten") || (this->get_english_rank() == "Eleven") || (this->get_english_rank() == "Twelve")){
		return 0.5;
	}
	else
		return (this->get_rank());
}

// Comparison operator for cards
// Returns TRUE if card1 < card2
bool Card::operator < (Card card2) const {
	return rank < card2.rank;
}



/* *************************************************
Hand class
************************************************* */
// Default constructor, creates an empty vector cards
Hand::Hand(){}

// Generate a random card, display its statistics, and add it to the hand 
void Hand::draw(){
	Card newcard = Card(); 
	cards.push_back(newcard);
	std::cout << "The card drawn is the " << newcard.get_english_rank() << " of " << newcard.get_english_suit() << "\n";
	value += newcard.get_value();
	std::cout << "The current hand value is: " << value << "\n";
}

// Checks to see if total value has exceeded bust value
// Returns 1 if busted, 0 if not
bool Hand::bust(){
	if (value > 7.5){
		std::cout << "Hand busted!" << "\n";
		return 1;
	}
	else return 0;
}

// Accessor function: returns total value of cards in hand
double Hand::hand_value() const{
	return this->value;
}


// Compares two hands and accounts for busts.
// Returns 1 if player's hand is bigger, 0 if dealer wins
// House's advantage: the dealer wins if both hands are busted.
// 3 cases: 1 if player wins, 0 if dealer wins, 2 if they draw
unsigned int Hand::compare(Hand dealer){
	if ((this->bust() == 1) && (dealer.bust() == 1)){
		return 0;
	}
	else if ((this->bust() == 1) && (dealer.bust() == 0)){
		return 0;
	}
	else if ((this->bust() == 0) && (dealer.bust() == 1)){
		return 1;
	}
	else if ((this->bust() == 0) && (dealer.bust() == 0)){
		if (this->hand_value() == dealer.hand_value()){
			return 2;
		}
		else if (this->hand_value() > dealer.hand_value()){
			return 1;
		}
		else if (this->hand_value() < dealer.hand_value()){
			return 0;
		}
	}
}


/* *************************************************
Player class
************************************************* */
// Constructor: gives player m dollars 
Player::Player(int m) : money(m) {} 

// Transfers money from one person to another, amount (the bet) can be positive or negative;
// A positive amount means "this" player gained money from dealer
// A negative amount means "this" player gives money to dealer
void Player::exchange_money(Player dealer, int amount){
	money += amount;
	dealer.money -= amount;
}