#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Side.h"
#include"Board.h"
#include <iostream>

class AlarmClock;

class Player {
public:
	//Create a Player with the indicated name.
	Player(std::string name);

	//Return the name of the player.
	std::string name() const;

	//Return false if the player is a computer player.Return true if the player is human.Most kinds of players will be computer players.
	virtual bool isInteractive() const;

	//Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose.If no move is possible, return −1.
	virtual int chooseMove(const Board& b, Side s) const = 0;

	//Since this class is designed as a base class, it should have a virtual destructor.
	virtual ~Player();

private:
	string m_name;
};

	//A HumanPlayer chooses its move by prompting a person running the program for a move(reprompting if necessary until the person enters a valid hole number), and returning that choice.We will never test for a situation where the user doesn't enter an integer when prompted for a hole number. (The techniques for dealing with the issue completely correctly are a distraction to this project, and involve either a function like stoi or strtol, or the type istringstream.)
class HumanPlayer : public Player {
public:
	HumanPlayer(std::string name);
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const;
};

	//A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like : leftmost, nearest to pot, fewest beans, random, etc..The point of this class is to have an easy - to - implement class that at least plays legally.
class BadPlayer : public Player {
public:
	BadPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;
	//virtual ~BadPlayer() {};
};


class SmartPlayer: public Player {
public:
	SmartPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;

private:
	void chooseMove(AlarmClock &ac,const Board& b, Side s, int & bestHole, int& value, int depth) const;
	int evaluate(const Board& b) const;
	bool completeMove(Side s, int hole, Board &b, Side& endSide, int& endHole) const;
};
#endif // !PLAYER_H
