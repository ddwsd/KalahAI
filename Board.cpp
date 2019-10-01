#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole) {
	if (nHoles < 1) {
		nHoles = 1;
	}
	m_holes = nHoles + 1; //mholes stores the pot as a hole as well
	if (nInitialBeansPerHole < 0) {
		nInitialBeansPerHole = 0;
	}
	total_beans = (m_holes - 1) * nInitialBeansPerHole * 2; //holes not including pot, multiplied by 2
	initializeVector(nInitialBeansPerHole, north_vector);
	initializeVector(nInitialBeansPerHole, south_vector);
}
//Construct a Board with the indicated number of holes per side(not counting the pot) and initial number of beans per hole.If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.

int Board::holes() const {
	return m_holes - 1;
}
//Return the number of holes on a side(not counting the pot).

int Board::beans(Side s, int hole) const {
	if (!isValidHole(hole) || !isValidSide(s)) {
		return -1;
	}
	if (s == SOUTH) { //south
		return south_vector[hole];
	}
	else { //north
		return north_vector[hole];
	}
}
//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.

int Board::beansInPlay(Side s) const {
	if (!isValidSide(s)) {
		return -1;
	}
	int total = 0;
	if (s == SOUTH) { //south
		for (int i = 1; i < m_holes; i++) {
			total += south_vector[i];
		}
	}
	else { //north
		for (int i = 1; i < m_holes; i++) {
			total += north_vector[i];
		}
	}
	return total;
}
//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.

int Board::totalBeans() const {
	return total_beans;
}
//Return the total number of beans in the game, including any in the pots.

bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
	if (!isValidHole(hole) || !isValidSide(s)) {
		return false;
	}
	if (hole == POT) {
		return false;
	}
	switch (s) {
	case(SOUTH):
		if (south_vector[hole] == 0) {
			return false;
		}
		break;
	case(NORTH):
		if (north_vector[hole] == 0) {
			return false;
		}
		break;
	}
	int currenthole(hole);
	Side currentside(s);
	if (s == SOUTH) {
		int counter = south_vector[hole];
		while (counter > 0) {
			if (currenthole == 0) { //switch sides if it passes the pot
				currentside = NORTH;
				currenthole = m_holes; //set the current hole to m_holes
			}
			if (currentside == SOUTH) {
				if (currenthole < m_holes - 1) { //if currenthole is not referring to the one before the pot
					currenthole++;
					south_vector[currenthole]++; //increment beans in currenthole
				}
				else { // next hole is the pot
					if (s == SOUTH) {
						currenthole = 0;
						south_vector[currenthole]++;
					}
				}
			}
			else { //currentside is north
				if (currenthole > 1) { //if currenthole is not referring to the hole before the pot
					currenthole--;
					north_vector[currenthole]++;
				}
				else { // next hole is the pot, so skip
					currentside = SOUTH; //switch side for the next iteration
					south_vector[currenthole]++; //current hole is one, which is correct
				}
			}
			south_vector[hole]--;
			counter--;
		}
	}
	else { //starting side is north
		int counter = north_vector[hole];
		while (counter > 0) {
			//change when currenthole = 0
			if (currenthole == 0) {
				currentside = SOUTH;
			}
			if (currentside == SOUTH) {
				if (currenthole < m_holes - 1) { //if currenthole is not referring to the one before the pot
					currenthole++;
					south_vector[currenthole]++; //increment beans in currenthole
				}
				else { // next hole is the pot, so skip
					currentside = NORTH; //switch side for the next iteration
					north_vector[currenthole]++; //current hole is the last one, which is correct
				}
			}
			else { //currentside is north
				if (currenthole > 0) { //if currenthole is not referring to the hole before the pot
					currenthole--;
					north_vector[currenthole]++;
				}
			}
			north_vector[hole]--;
			counter--;
		}
	}
	if (currenthole == 0 || currenthole == m_holes) { //if currenthole is pot
		currenthole = 0;
	}
	endHole = currenthole;
	endSide = currentside;
	return true;
}

//If the hole indicated by(s, hole) is empty or invalid or a pot, this function returns false without changing anything.Otherwise, it will return true after sowing the beans : the beans are removed from hole(s, hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)

bool Board::moveToPot(Side s, int hole, Side potOwner) {
	if (!isValidHole(hole) || !isValidSide(s)) {
		return false;
	}
	if (hole == 0) {
		return false;
	}
	int previous; //actually i dont think i need this
	if (s == SOUTH) {
		previous = south_vector[hole]; 
		if (potOwner == NORTH) {
			north_vector[POT] += previous;
		}
		else {
			south_vector[POT] += previous;
		}
		south_vector[hole] = 0;
	}
	else { // s is north
		previous = north_vector[hole];
		if (potOwner == NORTH) {
			north_vector[POT] += previous;
		}
		else {
			south_vector[POT] += previous;
		}
		north_vector[hole] = 0;
	}
	return true;
}
//If the indicated hole is invalid or a pot, return false without changing anything.Otherwise, move all the beans in hole(s, hole) into the pot belonging to potOwner and return true.

bool Board::setBeans(Side s, int hole, int beans) {
	if (!isValidHole(hole) || !isValidSide(s)) {
		return false;
	}
	if (beans < 0) {
		return false;
	}
	int previous; //stores the original number of beans in the hole
	if (s == SOUTH) {
		previous = south_vector[hole];
		south_vector[hole] = beans;
	}
	else { //s is north
		previous = north_vector[hole];
		north_vector[hole] = beans;
	}
	total_beans = total_beans - previous + beans; //so that we can edit the total beans accordingly
	return true;
}
//If the indicated hole is invalid or beans is negative, this function returns false without changing anything.Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program : None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)


void Board::initializeVector(int beans, vector<int> &m_vector) {
	m_vector.push_back(0); //this refers to the pot, which starts at 0
	for (int i = 1; i < m_holes; i++) { //the remaining holes will have the correct number of beans
		m_vector.push_back(beans);
	}
}
bool Board::isValidHole(int hole) const {
	for (int i = 0; i < m_holes; i++) {
		if (hole == i) {
			return true;
		}
	}
	return false;
} //checks hole is valid

bool Board::isValidSide(Side s) const {
	switch (s) {
	case(NORTH):
	case(SOUTH):
		return true;
	default:
		return false;
	}
} //checks side is valid