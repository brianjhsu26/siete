#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include "cards.h"
using namespace std;


// *** NON MEMBER FUNCTION DECLARATIONS *** //
// Function that ensures all situations are suitable for one game cycle to occur, and then initiates cycle
// Ensures that player balance is > 0, dealer has not lost 900, and the bet made is acceptable
// Stop when the player loses all his money, or if the dealer loses 900
void play_game(Player& user, Player& dealer); 

// Function that assumes all conditions are suitable for one cycle to run based on a bet
// Also takes in a output stream to save each cycle into the log
void cycle(const int& bet, Player& user, Player& dealer_, std::ofstream& log);

void log_cycle(std::ofstream& file, const int& bet, Hand& user, Hand& dealer, Player& user_);

// *** NON MEMBER FUNCTION IMPLEMENTATIONS *** //
void play_game(Player& user, Player& dealer){
	// First keep track of the game number and open a log to contain the game every time it is played
	size_t game_num = 1;
	std::ofstream game_log;
	game_log.open("log.txt");

	while ((user.get_balance() > 0) && (dealer.get_total_loss() <= 900)){
		int bet = 0;
		std::cout << "Your current balance is " << user.get_balance() << " dollars" << "\n"
			<< "Enter the integer amount you would like to bet: ";
		cin.clear(); cin >> bet;
		while ((bet <= 0) || (bet > user.get_balance())){
			// Check if a bet is made that is negative or over the user's balance
			cin.clear();
			std::cout << "Please enter a valid bet amount: "; 
			std::cin >> bet; 
		}
		game_log << "**********************************************" << "\n" << "Game " << game_num << "\n"; // Too much trouble to implement in log_game fxn
		game_num++;
		cycle(bet, user, dealer, game_log);
		if (user.get_balance() <= 0){
			std::cout << "You have gone bankrupt!" << "\n";
			return;
		}
		if (dealer.get_total_loss() > 900){
			std::cout << "You have won too much from the casino!" << "\n";
			return;
		}
	}
	game_log.close();
}

void cycle(const int& bet, Player& user, Player& dealer_, std::ofstream& log){
	Hand player;
	Hand dealer;
	std::cout << "You draw..." << "\n";
	player.draw();
	std::cout << "The dealer draws..." << "\n";
	dealer.draw(); 
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
		}
		else if (response == "n"){
			std::cout << "Your hand: " << "\n";
			player.show_hand();
			std::cout << "Dealer's turn to draw" << "\n";
			break;
		}
	}
	std::cout << "\n"; 
	// Now, the dealer draws cards to his hand
	while (dealer.hand_value() < 5.5){
		dealer.draw();
		if (dealer.hand_value() >= 5.5){
			std::cout << "The dealer stops drawing, his hand is..." << "\n";
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
	std::cout << "\n" << "**********************************" << "\n";

	// Now, write the game history into the file before the variables go out of scope 
	log_cycle(log, bet, player, dealer, user);
}

void log_cycle(std::ofstream& file, const int& bet, Hand& user, Hand& dealer, Player& user_){
	// From play_game function, there is already the row of stars and the game number 
	file << "\n";
	file << "Bet: " << bet << setw(37) << right << "Resulting Balance: " << user_.get_balance() << "\n";
	file << "Your cards" << "\n";
	user.show_hand(file);
	file << "\n" << "Dealer's cards" << "\n";
	dealer.show_hand(file);
	file << "**********************************************" << "\n";
}

// Stub for main
int main(){
	std::cout << "Welcome to Siete y Medio!" << "\n";
	Player user(100);
	Player dealer(1000);
	play_game(user, dealer);
	std::cout << "Thanks for playing!" << "\n";
	return 0;
}