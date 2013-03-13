#define DEFAULT_PITS 6
#define DEFAULT_STONES 4

#include <iostream>
#include "mancala.h"

using namespace std;

int main() {
	cout << "Mancala - By Kees and Boaz" << endl << endl;
	int pits, stones;
	do {
		cout << "How many pits p? 1<p<8 (standaard aantal toets 0)" << endl;
		cin >> pits;
		if (pits == 0) {
			pits = DEFAULT_PITS;
		}
	} while (!((pits > 1) && (pits < 8)));
	do {
		cout << "How many stones s? 1<s<7 (standaard aantal toets 0)" << endl;
		cin >> stones;
		if (stones == 0) {
			stones = DEFAULT_STONES;
		}
	} while (!((stones > 1) && (stones < 7)));

	// create a board
	MancalaBoard mancala(pits, stones);
	// create two players and assign them to the board
	Computer cpuplayer(mancala);
	Human humanplayer(mancala);

	int begin;
	do {
		cout << "Who may begin? 1=HUMAN 2=CPU" << endl;
		cin >> begin;
		if (begin == 1) {
			humanplayer.setTurn(true);
		} else if (begin == 2) {
			cpuplayer.setTurn(true);
		} else {
			cout << "Wrong input, type 1 or 2 and press enter" << endl;
		}
	} while (!(begin == 1 || begin == 2));

	// print the board
	mancala.printBoard();

	do {
		MancalaPlayer::Lastpit reply;
		if (humanplayer.getTurn() == true) {
			int frompit;
			do {
				cout << "HUMAN sow: " << flush;
				cin >> frompit;

				reply = humanplayer.sow(mancala, MancalaPlayer::HUMAN, frompit);
			} while(reply == MancalaPlayer::TRYAGAIN);

			if (reply == MancalaPlayer::STORE) { // LAST SEED IN STORE, GO AGAIN
				cout << "HUMAN gets another turn!" << endl;
			} else {
				humanplayer.setTurn(false);
				cpuplayer.setTurn(true);
			}

		} else if (cpuplayer.getTurn() == true) {
			int frompit;

			// here the you can adjust the tactic (GREEDY / LOOKAHEAD)
			//cpuplayer.chooseMove(frompit, MancalaPlayer::COMPUTER, mancala, MancalaPlayer::GREEDY);
			cpuplayer.chooseMove(frompit, MancalaPlayer::COMPUTER, mancala, MancalaPlayer::LOOKAHEAD);

			cout << "CPU sows " << frompit << endl;

			reply = cpuplayer.sow(mancala, MancalaPlayer::COMPUTER, frompit);
			if (reply == MancalaPlayer::STORE) { // LAST SEED IN STORE, GO AGAIN
				cout << "CPU received another turn!" << endl;
			} else {
				humanplayer.setTurn(true);
				cpuplayer.setTurn(false);
			}
		}
		// print the board
		mancala.printBoard();
	} while (mancala.gameOver() == 0);

	cout << (mancala.gameOver() == 1 ? "The winner is: HUMAN" : mancala.gameOver() == 2 ? "The winner is: CPU" : "Everyone is a winner!: DRAW") << endl;

	cin.get();
	cin.get();
	return 0;
}
