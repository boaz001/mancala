#include <iostream>
#include "mancala.h"

#define PITS 6
#define STONES 4

using namespace std;

int main(){
	cout << "Mancala - By Kees and Boaz" << endl << endl;
	int p,s;
	do {
		cout << "How many pits p? 1<p<8 (for default type 0)" << endl;
		cin >> p;
		if (p==0) {p=PITS;}
	} while (!((p>1)&&(p<8)));
	do {
		cout << "How many stones s? 1<s<7 (for default type 0)" << endl;
		cin >> s;
		if (s==0) {s=STONES;}
	} while (!((s>1)&&(s<7)));
	Mancala mancala(p, s);
	mancala.playGame();
	cin.get();
	cin.get();
	return 0;
}
