#include"Game.h"
#include"Player.h"
#include"Board.h"
using namespace std;

Game::Game(const Board& b, Player* south, Player* north) :m_board(b), m_south(south), m_north(north), turn(SOUTH) {
}

void Game::display() const {
	cout << "\t" + m_north->name() << endl;

	cout << "   ";
	for (int i = 1; i <= m_board.holes(); i++) {
		cout << " " + to_string(m_board.beans(NORTH, i)) + " ";
	}
	cout << endl;

	cout << " " + to_string(m_board.beans(NORTH, POT)) + " ";
	for (int i = 1; i <= m_board.holes(); i++) {
		cout << "   ";
	}
	cout << " " + to_string(m_board.beans(SOUTH, POT)) + " ";
	cout << endl;

	cout << "   ";
	for (int i = 1; i <= m_board.holes(); i++) {
		cout << " " + to_string(m_board.beans(SOUTH, i)) + " ";
	}
	cout << endl;

	cout << "\t" + m_south->name() << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const {
	if (m_board.beansInPlay(NORTH) != 0 && m_board.beansInPlay(SOUTH) != 0) { //game is not over
		over = false;
		hasWinner = false;
		return;
	}
	over = true;

	if (m_board.beans(NORTH, POT) > m_board.beans(SOUTH, POT)) { //north won
		hasWinner = true;
		winner = NORTH;
	}
	else if (m_board.beans(SOUTH, POT) > m_board.beans(NORTH, POT)) { //south won
		hasWinner = true;
		winner = SOUTH;
	}
	else { // its a draw
		hasWinner = false;
	}
	return;
}

bool Game::move() {
	int endHole;
	Side endSide;
	//vector<int> isZero; //creates a vector that stores the possible endholes that would result in a capture
	if (turn == SOUTH) {
		int hole = m_south->chooseMove(m_board, turn);
		if (!m_south->isInteractive()) { //indicate what moves the computer player makes
			cout << m_south->name() + " chooses hole " + to_string(hole) << endl;
		}
		//for (int i = 1; i <= m_board.holes(); i++) { //adds the endholes to the vector
		//	if (m_board.beans(turn, i) == 0) {
		//		isZero.push_back(i);\
		//	};
		//}
		if (m_board.sow(turn, hole, endSide, endHole)) {
			if (endHole == POT) {
				//note that sow will always skip the opponent's pot so endhole = 0 implies endhole is on the same side as the player
				display();
				if (m_board.beansInPlay(SOUTH) > 0) {
					cout << m_south->name() + " gets another turn." << endl;
					return move(); //player gets another turn
				}
			}
			else if (endSide == turn) {
				//for (int i = 0; i < isZero.size(); i++) {
				if (m_board.beans(turn, endHole) == 1 && m_board.beans(opponent(turn), endHole) > 0) { //capture
					m_board.moveToPot(opponent(turn), endHole, turn);
					m_board.moveToPot(turn, endHole, turn);
				}
				//}
			}
		}
	}
	else { //turn = north
		int hole = m_north->chooseMove(m_board, turn);
		if (!m_north->isInteractive()) {
			cout << m_north->name() + " chooses hole " + to_string(hole) << endl;
		}
		//for (int i = 1; i <= m_board.holes(); i++) {
		//	if (m_board.beans(turn, i) == 0) {
		//		isZero.push_back(i);
		//	};
		//}
		if (m_board.sow(turn, hole, endSide, endHole)) {
			if (endHole == POT) {
				display();
				if (m_board.beansInPlay(NORTH) > 0) {
					cout << m_north->name() + " gets another turn." << endl;
					return move(); //player gets another turn
				}
			}
			else if (endSide == turn) {
				//for (int i = 0; i < isZero.size(); i++) {
				if (m_board.beans(turn, endHole) == 1 && m_board.beans(opponent(turn), endHole) > 0) { //capture
					m_board.moveToPot(opponent(turn), endHole, turn);
					m_board.moveToPot(turn, endHole, turn);
				}
				//}
			}
		}
	}
	turn = opponent(turn);
	if (m_board.beansInPlay(NORTH) == 0) { //game is over
		display();
		cout << "Sweeping remaining beans into " + m_south->name() + "'s pot." << endl;
		for (int i = 1; i <= m_board.holes(); i++) { //loop through the south holes
			m_board.moveToPot(SOUTH, i, SOUTH);
		}
		return false;
	}
	else if (m_board.beansInPlay(SOUTH) == 0) {
		display();
		cout << "Sweeping remaining beans into " + m_north->name() + "'s pot." << endl;
		for (int i = 1; i <= m_board.holes(); i++) { //loop through north's holes
			m_board.moveToPot(NORTH, i, NORTH);
		}
		return false;
	}
	return true;
}

void Game::play() {
	bool over, hasWinner;
	Side winner;
	display();
	do {
		move();
		display();
		if (!m_south->isInteractive() && !m_north->isInteractive()) {
			cout << "Press ENTER to continue.";
			cin.ignore(10000, '\n');
		}
		status(over, hasWinner, winner);
	} while (!over);
	if (hasWinner) {
		if (winner == SOUTH) {
			cout << "The winner is " + m_south->name() << endl;
		}
		else {
			cout << "The winner is " + m_north->name() << endl;
		}
	}
	else {
		cout << "It's a tie." << endl;
	}
}

int Game::beans(Side s, int hole) const {
	return m_board.beans(s, hole);
}