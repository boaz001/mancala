#include <vector>

using namespace std;

class Mancala {
public:
	enum Side { HUMAN, COMPUTER };
	enum Lastpit { TRYAGAIN, STORE, EMPTY, PIT };
	enum Tactic { GREEDY, LOOKAHEAD };
	
	typedef vector<int> Field;

	//constructor
	Mancala(int pits, int stones);

	//public memberfunctions
	void playGame(void);

private:
	//private variables
	int depth; // number of turns to lookahead
	int step; // number of possible moves that has been examined
	int pits, stones;
	Field field;
	Side turn;

	//private memberfunctions
	void printField(void) const;
	void steal(Field& f, Side s, int lastpit);
	Lastpit sow(Field& f, Side s, int frompit);
	int gameOver(void) const;
	int chooseMove(int& bestMove, Side s, Field f, Tactic tactic);
	Side getTurn() const { return turn; }
	void setTurn(Side S) { turn = S; return; }
};