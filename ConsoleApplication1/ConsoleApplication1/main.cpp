#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "cards.h"
using namespace std;

// Global constants (if any)


// *** NON MEMBER FUNCTION DECLARATIONS *** //

// Function that ensures all situations are suitable for one game cycle to occur, and then initiates cycle
// Ensures that player balance is > 0, dealer has not lost 900, and the bet made is acceptable
// Stop when the player loses all his money, or if the dealer loses 900
void play_game(Player& user, Player& dealer); 

// Function that assumes all conditions are suitable for one cycle to run based on a bet
void cycle(int bet, Player& user, Player& dealer_);

// *** NON MEMBER FUNCTION IMPLEMENTATIONS *** //
void cycle(int bet, Player& user, Player& dealer_){
	Hand player;
	Hand dealer;
	player.draw();
	dealer.draw(); // I assume on the first turn, they both show their cards?
	std::cout << "Your hand: " << "\n"; 
	player.show_hand();
	std::cout << "Dealer's hand: " << "\n";
	dealer.show_hand();
	std::cout << "\n";
	
	// First, the player draws until he busts or stands
	while (player.bust() != 1){
		std::string response;
		std::cout << "Would you like to draw another card? (y/n): ";
		std::cin >> response; 
		while ((response != "y") && (response != "n")){
			std::cout << "Please enter a valid response (y/n): "; 
			cin >> response;
		}
		if (response == "y"){
			player.draw();
			std::cout << "Your hand: " << "\n";
			player.show_hand();
			if (player.bust() == 1){
				std::cout << "Hand busted!" << "\n";
			}
		}
		else if (response == "n"){
			std::cout << "Your hand: " << "\n";
			player.show_hand();
			break;
		}
	}

	std::cout << "\n"; 
	// Now, the dealer 
	std::cout << "Dealer's hand..." << "\n";
	while (dealer.hand_value() < 5.5){
		dealer.draw();
		if (dealer.hand_value() >= 5.5){
			dealer.show_hand(); 
		}
	}
	
	// Check for the winner
	int status = player.compare(dealer);
	// Move money to the appropriate party
	if (status == 1){
		user.exchange_money(dealer_, bet);
	}
	else if (status == 0){
		user.exchange_money(dealer_, -1 * bet);
	}
	else if (status == 2){
		user.exchange_money(dealer_, 0);
	}
}

// Stub for main
int main(){
	Player user(100);
	Player dealer(900);
	cycle(50, user, dealer);
	std::cout << "User's Balance: " << user.get_balance() << "\n";
	std::cout << "Dealer's balance: " << dealer.get_balance() << "\n";
	return 0;
}