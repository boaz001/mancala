#include <vector>

using namespace std;

class MancalaBoard {
public:
	typedef vector<int> Field;

	//constructor
	MancalaBoard(int pits, int stones);

	// public memberfuncties (const)
	void printBoard(void) const;
	int gameOver(void) const;
	int getNumberOfPits(void) const { return pits; };
	int getNumberOfStones(void) const { return stones; };
	int getField(int index) const;
	Field getField(void) const;
	// non-const
	void setField(int index, int value);
	void addField(int index, int add);

private:
	Field field; // vector<int>
	int pits; // number of pits per player 
	int stones; // number of stones per pit
};

class MancalaPlayer {
public:
	enum Side { HUMAN, COMPUTER };
	enum Lastpit { TRYAGAIN, STORE, EMPTY, PIT };
	enum Tactic { GREEDY, LOOKAHEAD };

	// constructor
	MancalaPlayer(MancalaBoard board, Side side);

	// get status, virtual functions; each player keeps track of the status itself
	virtual bool getTurn() const = 0;
	virtual void setTurn(bool turn) = 0;
	// the chooseMove functions have a different implementation for HUMAN and CPU
	virtual int chooseMove(int& bestMove, Side side, MancalaBoard board, Tactic tactic) = 0;
	
	// these functions are the same for every player
	Lastpit sow(MancalaBoard& board, Side side, int frompit);
	void steal(MancalaBoard& board, Side side, int lastpit);
	
private:
	Side side; 
	MancalaBoard board;
};

// de class of Human (derived from MancalaPlayer)
class Human: public MancalaPlayer {
public:
	// constructor
	Human(MancalaBoard& board);

	// think of a move...
	int chooseMove(int& bestMove, Side side, MancalaBoard board, Tactic tactic);
	
	// get status of the game (who's turn it is)
	bool getTurn() const { return turn; }
	void setTurn(bool t) { if (t==true) { turn=true; } if (t==false) { turn=false; } return;}

private:
	bool turn; // my turn?
};

// class of CPU (derived from MancalaPlayer)
class Computer: public MancalaPlayer {
public:
	// constructor
	Computer(MancalaBoard& board);
	
	// think of a move...
	int chooseMove(int& bestMove, Side side, MancalaBoard board, Tactic tactic);
	
	// get status of the game (who's turn it is)
	bool getTurn() const { return turn; }
	void setTurn(bool t) { if (t==true) { turn=true; } if (t==false) { turn=false; } return;}

private:
	bool turn; // my turn?
	int depth; // number of turns that is looked ahead
	int step; // number of steps within a turn that is tried
};
