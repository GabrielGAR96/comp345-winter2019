#include "Player.h"
#include "PowerplantCard.h"
#include "HouseColor.h"

int main() {

	Player player1(BLACK);

std::cout << "Player 1 has been created...." << '\n';
std::cout << "\nPlayer 1:" << '\n';
player1.toString();

	PowerplantCard card(17, 2, 1, URANIUM);
	cout << "\nAdding a card to player...\n";
	player1.purchaseCard(card, 17);
	cout << "Buying resources for player..." << endl;
	player1.buyResource(0, URANIUM, 1, 10);
	cout<<"Buying City for player....\n";
	player1.buyCities("Montreal");
	std::cout << "\nPlayer 1:" << '\n';

player1.toString();
}
