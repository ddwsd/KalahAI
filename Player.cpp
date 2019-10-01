#include "Player.h"

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
	AlarmClock(int ms)
	{
		m_timedOut = false;
		m_isRunning = true;
		m_alarmClockFuture = std::async([=]() {
			for (int k = 0; k < ms && m_isRunning; k++)
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (m_isRunning)
				m_timedOut = true;
		});
	}

	~AlarmClock()
	{
		m_isRunning = false;
		m_alarmClockFuture.get();
	}

	bool timedOut() const
	{
		//just to check if time's up
		//if (m_timedOut) {
		//	cout << "TIME'S UP" << endl;
		//}
		return m_timedOut;
	}

	AlarmClock(const AlarmClock&) = delete;
	AlarmClock& operator=(const AlarmClock&) = delete;
private:
	std::atomic<bool> m_isRunning;
	std::atomic<bool> m_timedOut;
	std::future<void> m_alarmClockFuture;
};

using namespace std;
//BASE CLASS
Player::Player(std::string name) :m_name(name) {

}

Player::~Player() {}

std::string Player::name() const {
	return m_name;
}

bool Player::isInteractive() const {
	return false;
}



//HUMAN PLAYER
HumanPlayer::HumanPlayer(std::string name) :Player(name) {

}

bool HumanPlayer::isInteractive() const {
	return true;
}

int HumanPlayer::chooseMove(const Board &b, Side s) const {
	int choice;
	do {
		cout << "Select a hole, " + name() + ": ";
		cin >> choice;
		if (choice <= 0 || choice > b.holes()) {
			cout << "The hole number must be from 1 to " + to_string(b.holes()) + "." << endl;
		}
		else if (b.beans(s, choice) == 0) {
			cout << "There are no beans in that hole." << endl;
		}
	} while (choice <= 0 || choice > b.holes() || b.beans(s, choice) <= 0);
	return choice;
}




//BAD PLAYER
BadPlayer::BadPlayer(std::string name) :Player(name) {

}

//int BadPlayer::chooseMove(const Board &b, Side s) const {
//	for (int i = 1; i <= b.holes(); i++) {
//		if (b.beans(s, i) > 0) {
//			return i;
//		}
//	}
//	return -1;
//}
int BadPlayer::chooseMove(const Board &b, Side s) const {
	for (int i = b.holes(); i != 0; i--) {
		if (b.beans(s, i) > 0) {
			return i;
		}
	}
	return -1;
}





//SMART PLAYER
SmartPlayer::SmartPlayer(std::string name) :Player(name) {

}


int SmartPlayer::chooseMove(const Board &b, Side s) const {
	AlarmClock ac(4000);
	int bestHole, value, depth(0);
	chooseMove(ac, b, s, bestHole, value, depth);
	return bestHole;
}

bool SmartPlayer::completeMove(Side s, int hole, Board &b, Side& endSide, int& endHole) const {
	//vector<int> isZero;
	//for (int i = 1; i <= b.holes(); i++) {
	//	if (b.beans(s, i) == 0) {
	//		isZero.push_back(i);
	//	};
	//}
	if (b.sow(s, hole, endSide, endHole)) {
		if (endHole == 0) { //take another turn, note that sow will always skip the opponent's pot so endhole = 0 implies endhole is on the same side as the player
			return false;
		}
		else if (endSide == s) {
			if (b.beans(s, endHole) == 1 && b.beans(opponent(s), endHole) > 0) { //capture
				b.moveToPot(opponent(s), endHole, s);
				b.moveToPot(s, endHole, s);
			}
		}
		return true;
	}
	return false;
}

void SmartPlayer::chooseMove(AlarmClock &ac, const Board& b, Side s, int& bestHole, int& value, int depth) const {
	if (ac.timedOut()) { //if time is up, stop checking
		bestHole = -1;
		value = evaluate(b);
		return;
	}
	if (depth > 6) { //set depth of 7; even though there is an alarm clock, we still need to set depth so that the function can explore more starting moves 
		bestHole = -1;
		value = evaluate(b);
		return;
	}
	if (b.beansInPlay(s) == 0 /*|| b.beansInPlay(opponent(s)) == 0*/) {
		bestHole = -1;
		value = evaluate(b);
		return;
	}
	int first = 1; //stores the first hole that would return a value
	for (int i = 1; i <= b.holes(); i++) {
		if (b.beans(s, i) == 0) { //invalid move
			first++;
			continue;
		}
		Board temp(b);
		Side endSide;
		int endHole, v2, h2, h3;
		if (completeMove(s, i, temp, endSide, endHole)) {//for the case where it is now opponents turn
			chooseMove(ac, temp, opponent(s), h2, v2, depth + 1);
		}
		else { //still the same player's turn
			chooseMove(ac, temp, s, h3, v2, depth);
		}
		if (i == first) { //set value and besthole to be that of the first move made, to ensure that the player would choose a legal move
			value = v2;
			bestHole = i;
		}
		if (s == SOUTH) {
			if (v2 > value) {
				value = v2;
				bestHole = i;
			}
		}
		else { //side is north
			if (v2 < value) {
				value = v2;
				bestHole = i;
			}
		}
		if (ac.timedOut()) { //if time is up, stop checking
			break;
		}
	}
	return;
}

int SmartPlayer::evaluate(const Board& b) const {//evaluate for SOUTH
	int north = b.beansInPlay(NORTH); //speeds up the function because it would only call beansinplay() once
	int south = b.beansInPlay(SOUTH);
	int n_pot = b.beans(NORTH, 0); //speeds up the function because it would only call beans() once
	int s_pot = b.beans(SOUTH, 0);
	if (south == 0 || north == 0) {
		if (/*b.beans(SOUTH, 0)*/s_pot + south > /*b.beans(NORTH, 0)*/n_pot + north) {
			return INT_MAX;
		}
		else if (/*b.beans(SOUTH, 0)*/s_pot +south < /*b.beans(NORTH, 0)*/n_pot + north) {
			return INT_MIN;
		}
		else { //draw
			return 0;
		}
	}
	return /*b.beans(SOUTH, 0)*/s_pot + south - /*b.beans(NORTH, 0)*/n_pot - north;
}
