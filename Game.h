#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include <iostream>

class Player;

class Game {
public:
	//Construct a Game to be played with the indicated players on a copy of the board b.The player on the south side always moves first.
	Game(const Board& b, Player* south, Player* north);

	//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
	void display() const;
	
	//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
	void status(bool& over, bool& hasWinner, Side& winner) const;
	
	//If the game is over, return false.Otherwise, make a complete move for the player whose turn it is(so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
	bool move();
	
	//Play the game.Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)
	void play();
	
	//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
	int beans(Side s, int hole) const;
	

private:
	Board m_board;
	Player* m_north;
	Player* m_south;
	Side turn;
};
#endif // !GAME_H
