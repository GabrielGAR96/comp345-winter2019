#include "Player.h"
#include "PowerplantCard.h"
#include "HouseColor.h"

int main() {

	Player player1(BLACK);

	cout << "Player 1 has been created!" << endl;
	cout << "COLOR:\n";
	cout << player1.getColor();
	cout << "\nCARDS:\n";
	cout << player1.getCards() << endl;
	cout << "\nELEKTRO\n";
	cout <<"Player currently has: $" << player1.getMoney() << endl;
	cout << "\nRESOURCES\n";
	cout << player1.getResources() << endl;

	PowerplantCard card(17, 2, 1, URANIUM);
	cout << "\n Adding a card to player...\n";
	player1.purchaseCard(card, 17);
	cout << "Buying resources for player..." << endl;
	player1.buyResource(0, URANIUM, 1, 10);

	cout << "Player's new possessions:" << endl;
	cout << "\nCARDS:\n";
	cout << player1.getCards() << endl;
	cout << "\nELEKTRO\n";
	cout << "Player currently has: $" << player1.getMoney() << endl;
	cout << "\nRESOURCES\n";
	cout << player1.getResources() << endl;
}
