#ifndef SIDE_H
#define SIDE_H


enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
	return Side(NSIDES - 1 - s);
}
#endif // !SIDE_H
