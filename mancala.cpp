#define CPU_WIN 10000 // high value
#define HUMAN_WIN -10000 // low value
#define DRAW -5000 // low value: CPU doesn't want to play draw
#define NO_MOVES -100000
#define MAX_DEPTH 4 // number of moves to lookahead by CPU (when tactic = lookahead)

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include "mancala.h"

using namespace std;

// Constructor
Mancala::Mancala (int pits, int stones) : pits(pits), stones(stones) {
	if (pits <= 0) cout << "Number of pits must be > 0" << endl;
	if (stones <= 0) cout << "Number of stones must be > 0" << endl;
	for (int i=0; i<=(2*pits+1); i++) {
		field.push_back(stones);
	}
	field[pits] = 0;
	field[2*pits+1] = 0;

	depth = 0;
	step = 0;
}

// Function that prints the field
void Mancala::printField(void) const {
	cout << "CPU: "; for(int i=(2*pits); i>pits; i--) {if (i < 10) {cout <<i<<" |";} else {cout <<i<<"|";}} cout<<endl;
	cout << " ----"; for(int i=pits; i>0; i--) {cout << "---";} cout << "---" <<  endl;
	cout << " |  |"; for(int i=(2*pits); i>pits; i--) {cout << field[i]; if (field[i]<10) {cout << " |";} else{cout << "|";} } cout << "  |" << endl;
	cout << " |" << field[(2*pits+1)]; if (field[2*pits+1]<10) {cout << " |";} else {cout << "|";};for(int i=pits; i>1; i--) {cout << "--+";} cout << "--|" << field[pits]; if (field[pits]<10) {cout << " |";} else {cout << "|";}; cout << endl;
	cout << " |  |"; for(int i=0; i<pits; i++) {cout << field[i]; if (field[i]<10) {cout << " |";} else{cout << "|";} } cout << "  |" << endl;
	cout << " ----"; for(int i=pits; i>0; i--) {cout << "---";} cout << "---" <<  endl;
	cout << "HUM: "; for(int i=0; i<pits; i++) {if (i < 10) {cout <<i<<" |";} else {cout <<i<<"|";}} cout<<endl;
}

// Function that steals from opponent
void Mancala::steal(Field& f, Side s, int lastpit) {
	int steal;
	if (s == COMPUTER) {
		if (lastpit > pits) {
			steal = lastpit-pits;
			steal = pits-steal;
			f[(2*pits+1)] += f[steal]; // add stones to steal to store
			f[(2*pits+1)]++; // also add own stone to store
			f[lastpit] = 0; // remove own stone
			//if (f[steel] > 0) {cout << "CPU steals " << f[steel] << " stones!" <<endl;}
			f[steal] = 0; // remove stolen stones
			
		}
	} else if (s == HUMAN) {
		if (lastpit < pits) {
			steal = pits-lastpit;
			steal = pits+steal;
			f[pits] += f[steal]; // add stones to steal to store
			f[pits]++; // add own stone to store
			f[lastpit] = 0; // remove own stone
			//if (f[steel] > 0) {cout << "HUMAN steals " << f[steel] << " stones!" <<endl;}
			f[steal] = 0; // remove stolen stones
		}
	}
}

// Function that sows stones, returns the last pit where a stone was sown in
Mancala::Lastpit Mancala::sow(Field& f, Side s, int frompit) {
	if ((s==HUMAN) && (frompit > pits)) {cout << "Illegal move - sow from your own side" << endl; return TRYAGAIN;}
	if (frompit<0) { cout << "Illegal move" << endl; return TRYAGAIN; }
	if ((frompit==pits) || (frompit == (2*pits+1))) { cout << "You cannot sow from a store" << endl; return TRYAGAIN; }
	if (f[frompit] == 0) {cout << "You cannot sow from an empty pit" << endl; return TRYAGAIN;}

	int sowstones = f[frompit];
	int pit = frompit, previouspit = frompit;
	f[frompit] = 0;
	while (sowstones > 0) {
		previouspit = pit;
		pit++;
		if (s == COMPUTER) {
			if (pit == (2*pits+1)) {
				// jump to next pit
				f[pit]++; // drop stone
				sowstones--; // decrement sowstones
				pit = -1;

			} else if (pit == pits) {
				// skip this pit
				pit++;
			}
		} else if (s == HUMAN) {
			if (pit == (2*pits+1)) {
				// jump to next pit
				pit = -1;
			} else if (pit == pits) {

			}
		}

		if(pit != -1) {
			f[pit]++; // place stone
			sowstones--; // decrement sowstones
		}
	}
	// pit -1 is a invalid index
	if (pit == -1) {
		pit = (2*pits+1);
	}
	
	// return value
	// if the last 
	if ( (f[pit] == 1) && !((pit == pits) || (pit == (2*pits+1))) ) {
		// steal!
		steal(f, s, pit);
		if (pit == (2*pits+1)) {
			pit = -1;
		}
		return EMPTY;
	}
	if ( ((s == HUMAN) && (pit == pits)) || ((s == COMPUTER) && (pit == (2*pits+1))) ) {
		if (pit == (2*pits+1)) {
			pit = -1;
		}
		return STORE;
	}
	return PIT;
};

// Function that checks if the game is over. If so, it returns a value of the winner
int Mancala::gameOver(void) const {
	int human=0, cpu=0, endgame=0;
	
	for (int i=0 ; i<pits ; i++) {
		human += field[i];
	}
	if (human==0) {
		cpu=0;
		for (int i=pits+1 ; i<(2*pits+2) ; i++) {
			cpu += field[i];
		}
		endgame=1;
		human=field[pits];
	}

	for (int i=pits+1 ; i<(2*pits+1) ; i++) {
		cpu += field[i];
	}
	if (cpu==0) {
		human=0;
		for (int i=0 ; i<pits+1 ; i++) {
			human += field[i];
		}
		endgame=1;
		cpu=field[(2*pits+1)];
	}

	if ((human==cpu) && (endgame==1)) return 3;
	if ((cpu>human) && (endgame==1)) return 2;
	if ((human>cpu) && (endgame==1)) return 1;
	return 0;
}

// Function that chooses the best move for the CPU
int Mancala::chooseMove(int& bestMove, Side s, Field f, Tactic tactic) {
	depth++;
	int* a = NULL;
	a = new int[pits];
	Field fieldcopy = f;
	int dummy; //dummy variable

//-------------------------------------GREEDY----------------------------------------
// Finds the maximum number of stones that can be taken in 1 turn
// The best move will be the move that takes as many as possible stones
// before it is HUMAN's turn again.
//-----------------------------------------------------------------------------------
	if (tactic == GREEDY) {
		// Apply greedy tactic
		int score = f[(2*pits+1)]; // number of stones in pit
		int computerpits = 0; 
		for (int i=pits+1; i<(2*pits+1);i++){ // for each pit determine the movevalue
			int movevalue = score;
			if (f[i] != 0) { // Only sow if there are stones in the pit
				Lastpit reply = sow(fieldcopy, s, i);
				movevalue =  fieldcopy[(2*pits+1)] - score;
				if (reply == STORE) {
					a[computerpits] = movevalue + chooseMove(dummy, s, fieldcopy, GREEDY);
				} else {
					a[computerpits] = movevalue;
				}
			} else{ // if there are no stones in the pit this move is considered a low value
				a[computerpits] = NO_MOVES;
			}
			computerpits++;
			fieldcopy = f; // put back the original copy
		}

//-------------------------------------LOOKAHEAD-----------------------------------------
// This algorithm looks ahead MAX_DEPTH number of turns to determine the maximum score
// The best move(s) is the one that CPU gains to most points and HUMAN the least.
//---------------------------------------------------------------------------------------
	} else if (tactic == LOOKAHEAD) {
		if (s == HUMAN) {
			int score = f [pits]; // number of stones in pit
			for (int i=0; i<pits;i++){ // for each pit determine the movevalue
				int movevalue = score;
				if (f[i]!=0) { // Only sow if there are stones in the pit
					Lastpit reply = sow(fieldcopy, s, i);
					movevalue =  fieldcopy[pits] - score;
					if (reply == STORE) {
						depth--; // depth (turn) stays the same
						step++; // one step more on this depth
						a[i] = movevalue + chooseMove(dummy, HUMAN, fieldcopy, LOOKAHEAD); // recursive call of choosemove function
						step--;
						depth++;
					} else {
						if (depth <= MAX_DEPTH) {
							a[i] = movevalue - chooseMove(dummy, COMPUTER, fieldcopy, LOOKAHEAD); // recursive call of choosemove function
						}
						else{
							a[i] = movevalue;
						}
					}
				} else{ // if there are no stones in the pit this move is considered a low value
					a[i] = NO_MOVES;
				}
				fieldcopy = f; // put back the original copy
			}
		} else if (s == COMPUTER) {
			int score = f[(2*pits+1)]; // number of stones in pit
			int computerpits = 0;
			for (int i=pits+1; i<(2*pits+1);i++){ // for each pit determine the movevalue
				int movevalue = score;
				if (f[i]!=0){ // Only sow if there are stones in the pit
					Lastpit reply = sow(fieldcopy, s, i);
					movevalue =  fieldcopy[(2*pits+1)] - score;
					if (reply == STORE){
						depth--; // depth (turn) stays the same
						step++; // one step more on this depth
							a[computerpits] = movevalue + chooseMove(dummy,COMPUTER,fieldcopy,LOOKAHEAD); // recursive call of choosemove function
						step--;
						depth++;
					} else {
						if (depth <= MAX_DEPTH) {
							a[computerpits] = movevalue - chooseMove(dummy,HUMAN,fieldcopy,LOOKAHEAD); // recursive call of choosemove function
						}
						else{
							a[computerpits] = movevalue;
						}
					}
				} else{ // if there are no stones in the pit this move is considered a low value
					a[computerpits] = NO_MOVES;
				}
				computerpits++;
				fieldcopy = f; // put back the original copy
			}
		}	
	}

	
	int max = INT_MIN;
	for (int i=0; i<pits; i++) {
		if (a[i] > max) {
			max = a[i];
			bestMove = i+pits+1;
		}
		//if ((depth == 1) && (step == 0)) {cout << "value pit "; if ((i+pits+1) < 10) {cout <<" ";} cout << i+pits+1 << "= " << a[i] << endl;}
	}
	
	// if there are no more moves possible at this point assign a very high of very low movevalue
	if (max == NO_MOVES) {
		if (s == COMPUTER){
			if (fieldcopy[(2*pits+1)] > (pits*stones))
				max = CPU_WIN;
			else if (fieldcopy[(2*pits+1)] == (pits*stones))
				max = DRAW;
			else
				max = HUMAN_WIN;
		} else {
			if (fieldcopy[pits] > (pits*stones))
				max = -HUMAN_WIN;
			else if (fieldcopy[pits] == (pits*stones))
				max = -DRAW;
			else
				max = -CPU_WIN;
		}
	}
		
	depth--;
	delete [] a;
	return max;
}

// Play the game; assign turns to players and end the game when it is over
void Mancala::playGame (void) {
	int b;
	do {
		cout << "Who may begin? 1=HUMAN 2=CPU" << endl;
		cin >> b;
		// !!! add catching of wrong input
	} while (!(b==1||b==2));
	if (b==1)
		setTurn(HUMAN);
	else if (b==2)
		setTurn(COMPUTER);

	printField();
	do {
		Lastpit reply;
		if (getTurn() == HUMAN) {
			int frompit;

			do {
				cout << "HUMAN sow? : " << flush;
				cin >> frompit;
				// !!! add catching of wrong input
				reply = sow(field, HUMAN, frompit);
			} while(reply == TRYAGAIN);
			
			if (reply == STORE) { // LAST SEED IN STORE, GO AGAIN
				cout << "HUMAN can go again!" << endl;
			} else {
				setTurn(COMPUTER);
			}

		} else if (getTurn() == COMPUTER) {
			int move;
			//chooseMove(move, COMPUTER, field, GREEDY);
			chooseMove(move, COMPUTER, field, LOOKAHEAD);
			cout << "CPU sows " << move << endl;

			reply = sow(field, COMPUTER, move);
			if (reply == STORE) { // LAST SEED IN STORE, GO AGAIN
				setTurn(COMPUTER);
				cout << "CPU received another turn!" << endl;
			} else {
				setTurn(HUMAN);
			}
		}
		printField();
	} while (gameOver()==0);

	cout << (gameOver()==1? "The winner is: HUMAN":gameOver()==2?"The winner is: CPU":"Both players are winners!: DRAW") << endl;
}
