//#include <iostream>
//#include <cassert>
//#include "Board.h"
//#include "Side.h"
////#include "Player.h"
////#include "Game.h"
//using namespace std;
//
//int main()
//{
//	{
//		//bad arguments to constructor
//		Board bad(0, -1);
//		assert(bad.holes() == 1);
//		assert(bad.beans(NORTH, 0) == 0);
//		assert(bad.beans(SOUTH, 0) == 0);
//		assert(bad.beans(SOUTH, 1) == 0);
//		assert(bad.beans(NORTH, 1) == 0);
//		assert(bad.beansInPlay(NORTH) == 0);
//		assert(bad.beansInPlay(SOUTH) == 0);
//		assert(bad.totalBeans() == 0);
//
//		//typical construction
//		Board b(7, 5);
//		assert(b.beans(NORTH, 0) == 0); //pots uninitialized
//		assert(b.beans(SOUTH, 0) == 0);
//		for (int i = 1; i <= 7; i++)
//		{
//			assert(b.beans(NORTH, i) == 5);
//			assert(b.beans(SOUTH, i) == 5);
//		}
//		assert(b.beansInPlay(NORTH) == 35);
//		assert(b.beansInPlay(SOUTH) == 35);
//		assert(b.totalBeans() == 70);
//
//		//copy constructor and assignment
//		Board *ptr;
//		{
//			Board temp(8, 1);
//			//set pots to unique values
//			assert(temp.setBeans(NORTH, 0, 99));
//			assert(temp.setBeans(SOUTH, 0, 19));
//			for (int i = 1; i <= 8; i++) //set holes to unique values
//			{
//				assert(temp.setBeans(NORTH, i, i));
//				assert(temp.setBeans(SOUTH, i, 2 * i));
//			}
//			b = temp;
//			ptr = new Board(temp);
//		}
//		//check copy/assignment
//		assert(ptr->holes() == 8);
//		assert(b.holes() == 8);
//		assert(b.beans(NORTH, 0) == 99);
//		assert(b.beans(SOUTH, 0) == 19);
//		assert(ptr->beans(NORTH, 0) == 99);
//		assert(ptr->beans(SOUTH, 0) == 19);
//		for (int i = 1; i <= 8; i++)
//		{
//			assert(b.beans(NORTH, i) == i);
//			assert(b.beans(SOUTH, i) == 2 * i);
//			assert(ptr->beans(NORTH, i) == i);
//			assert(ptr->beans(SOUTH, i) == 2 * i);
//		}
//		//basic math
//		assert(b.beansInPlay(NORTH) == 36);
//		assert(b.beansInPlay(SOUTH) == 72);
//		assert(ptr->beansInPlay(NORTH) == 36);
//		assert(ptr->beansInPlay(SOUTH) == 72);
//		assert(b.totalBeans() == 108 + 19 + 99);
//		assert(ptr->totalBeans() == 108 + 19 + 99);
//		b = Board(6, 4);
//		//invalid moving to pot
//		assert(!b.moveToPot(NORTH, 0, NORTH));
//		assert(!b.moveToPot(NORTH, 0, SOUTH));
//		assert(!b.moveToPot(SOUTH, 0, SOUTH));
//		assert(!b.moveToPot(SOUTH, 0, NORTH));
//		assert(!b.moveToPot(NORTH, -1, NORTH));
//		assert(!b.moveToPot(NORTH, -1, SOUTH));
//		assert(!b.moveToPot(SOUTH, -1, SOUTH));
//		assert(!b.moveToPot(SOUTH, -1, NORTH));
//		assert(!b.moveToPot(NORTH, 7, NORTH));
//		assert(!b.moveToPot(NORTH, 7, SOUTH));
//		assert(!b.moveToPot(SOUTH, 7, SOUTH));
//		assert(!b.moveToPot(SOUTH, 7, NORTH));
//		//nothing changed
//		assert(b.beansInPlay(NORTH) == 24);
//		assert(b.beansInPlay(SOUTH) == 24);
//		assert(b.beans(NORTH, 0) == 0);
//		assert(b.beans(SOUTH, 0) == 0);
//		//move to pots
//		for (int i = 1; i <= 4; i++)
//		{
//			assert(b.moveToPot(NORTH, i, NORTH));
//			assert(b.moveToPot(SOUTH, i, NORTH));
//		}
//		for (int i = 5; i <= 6; i++)
//		{
//			assert(b.moveToPot(NORTH, i, SOUTH));
//			assert(b.moveToPot(SOUTH, i, SOUTH));
//		}
//		//leaves holes empty
//		assert(b.beansInPlay(NORTH) == 0);
//		assert(b.beansInPlay(SOUTH) == 0);
//		//goes in right pots
//		assert(b.beans(NORTH, 0) == 32);
//		assert(b.beans(SOUTH, 0) == 16);
//
//		//sow stuff
//
//		//invalid arguments
//		int eh = -99;
//		Side es = SOUTH;
//		Board b0(5, 1);
//		b = b0;
//		assert(!b0.setBeans(NORTH, -1, 999));
//		assert(!b0.setBeans(NORTH, 6, 999));
//		assert(!b0.setBeans(NORTH, 1, -666));
//		assert(b0.beans(NORTH, -1) == -1);
//		assert(b0.beans(SOUTH, -1) == -1);
//		assert(b0.beans(NORTH, 6) == -1);
//		assert(b0.beans(SOUTH, 6) == -1);
//		assert(b0.totalBeans() == 10); //no change
//		//invalid sow arguments
//		b = b0;
//		b.setBeans(NORTH, 0, 10);
//		b.setBeans(SOUTH, 0, 7);
//		assert(!b.sow(NORTH, 0, es, eh) && es == SOUTH && eh == -99);
//		assert(!b.sow(SOUTH, 0, es, eh) && es == SOUTH && eh == -99);
//		assert(!b.sow(NORTH, 6, es, eh) && es == SOUTH && eh == -99);
//		assert(!b.sow(SOUTH, 6, es, eh) && es == SOUTH && eh == -99);
//		assert(!b.sow(NORTH, -1, es, eh) && es == SOUTH && eh == -99);
//		assert(!b.sow(SOUTH, -1, es, eh) && es == SOUTH && eh == -99);
//		//sow empty pot
//		b.setBeans(NORTH, 1, 0);
//		b.setBeans(SOUTH, 1, 0);
//		assert(!b.sow(NORTH, 1, es, eh) && es == SOUTH && eh == -99);
//		assert(!b.sow(SOUTH, 1, es, eh) && es == SOUTH && eh == -99);
//		//unchanged
//		assert(b.beansInPlay(NORTH) == 4);
//		assert(b.beansInPlay(SOUTH) == 4);
//		//sow single bean into pot
//		b = b0;
//		assert(b.sow(NORTH, 1, es, eh) && es == NORTH && eh == 0);
//		assert(b.sow(SOUTH, 5, es, eh) && es == SOUTH && eh == 0);
//		assert(b.beans(NORTH, 1) == 0);
//		assert(b.beans(SOUTH, 5) == 0);
//		assert(b.beansInPlay(NORTH) == 4);
//		assert(b.beansInPlay(SOUTH) == 4);
//		assert(b.totalBeans() == 10);
//
//
//		//check won't land in opponent pot
//		b = b0;
//		b.setBeans(NORTH, 5, 5);
//		b.setBeans(NORTH, 0, 3);
//		assert(b.sow(NORTH, 5, es, eh) && es == NORTH && eh == 0 && b.beans(NORTH, 5) == 0);
//		for (int i = 1; i < 5; i++)
//		{
//			assert(b.beans(NORTH, i) == 2);
//		}
//		assert(b.beans(NORTH, 0) == 4);
//		assert(b.beansInPlay(NORTH) == 8);
//		b.setBeans(SOUTH, 1, 5);
//		b.setBeans(SOUTH, 0, 3);
//		assert(b.sow(SOUTH, 1, es, eh) && es == SOUTH && eh == 0 && b.beans(SOUTH, 1) == 0);
//		for (int i = 2; i <= 5; i++)
//		{
//			assert(b.beans(SOUTH, i) == 2);
//		}
//		assert(b.beans(SOUTH, 0) == 4);
//		assert(b.beansInPlay(SOUTH) == 8);
//
//		//loop back around NORTH
//		b = b0;
//		b.setBeans(NORTH, 2, 8);
//		b.setBeans(NORTH, 0, 3);
//		assert(b.sow(NORTH, 2, es, eh) && es == NORTH && eh == 5 && b.beans(NORTH, 2) == 0);
//		assert(b.beans(NORTH, 1) == 2);
//		assert(b.beans(NORTH, 0) == 4);
//		for (int i = 1; i <= 5; i++)
//		{
//			assert(b.beans(SOUTH, i) == 2);
//		}
//		assert(b.beans(SOUTH, 0) == 0);
//		assert(b.beansInPlay(NORTH) == 6);
//		assert(b.beansInPlay(SOUTH) == 10);
//
//		//loop back around SOUTH
//		b = b0;
//		b.setBeans(SOUTH, 4, 8);
//		b.setBeans(SOUTH, 0, 3);
//		assert(b.sow(SOUTH, 4, es, eh) && es == SOUTH && eh == 1 && b.beans(SOUTH, 4) == 0);
//		assert(b.beans(SOUTH, 5) == 2);
//		assert(b.beans(SOUTH, 0) == 4);
//		for (int i = 1; i <= 5; i++)
//		{
//			assert(b.beans(NORTH, i) == 2);
//		}
//		assert(b.beans(NORTH, 0) == 0);
//		assert(b.beansInPlay(SOUTH) == 6);
//		assert(b.beansInPlay(NORTH) == 10);
//
//		//many loops NORTH
//		b = b0;
//		b.setBeans(NORTH, 3, 23);
//		assert(b.sow(NORTH, 3, es, eh) && es == NORTH && eh == 2);
//		assert(b.beans(NORTH, 0) == 2);
//		assert(b.beans(NORTH, 1) == 3);
//		assert(b.beans(NORTH, 2) == 4);
//		assert(b.beans(NORTH, 3) == 2);
//		assert(b.beans(NORTH, 4) == 3);
//		assert(b.beans(NORTH, 5) == 3);
//		assert(b.beans(SOUTH, 0) == 0);
//		for (int i = 1; i <= 5; i++)
//		{
//			assert(b.beans(SOUTH, i) == 3);
//		}
//
//		//many loops SOUTH
//		b = b0;
//		b.setBeans(SOUTH, 3, 23);
//		assert(b.sow(SOUTH, 3, es, eh) && es == SOUTH && eh == 4);
//		assert(b.beans(SOUTH, 0) == 2);
//		assert(b.beans(SOUTH, 1) == 3);
//		assert(b.beans(SOUTH, 2) == 3);
//		assert(b.beans(SOUTH, 3) == 2);
//		assert(b.beans(SOUTH, 4) == 4);
//		assert(b.beans(SOUTH, 5) == 3);
//		assert(b.beans(NORTH, 0) == 0);
//		for (int i = 1; i <= 5; i++)
//		{
//			assert(b.beans(NORTH, i) == 3);
//		}
//
//		//"typical" sowing of one and many beans
//		b = b0;
//		b.setBeans(NORTH, 4, 3);
//		b.setBeans(SOUTH, 2, 3);
//		assert(b.sow(NORTH, 4, es, eh) && es == NORTH && eh == 1);
//		assert(b.beans(NORTH, 4) == 0);
//		assert(b.beans(NORTH, 3) == 2);
//		assert(b.beans(NORTH, 2) == 2);
//		assert(b.beans(NORTH, 1) == 2);
//		assert(b.sow(SOUTH, 2, es, eh) && es == SOUTH && eh == 5);
//		assert(b.beans(SOUTH, 2) == 0);
//		assert(b.beans(SOUTH, 3) == 2);
//		assert(b.beans(SOUTH, 4) == 2);
//		assert(b.beans(SOUTH, 5) == 2);
//		assert(b.sow(NORTH, 5, es, eh) && es == NORTH && eh == 4);
//		assert(b.beans(NORTH, 5) == 0 && b.beans(NORTH, 4) == 1);
//		assert(b.sow(SOUTH, 1, es, eh) && es == SOUTH && eh == 2);
//		assert(b.beans(SOUTH, 1) == 0 && b.beans(SOUTH, 2) == 1);
//
//		//sowing with only 1 hole
//		bad.setBeans(NORTH, 1, 1);
//		assert(bad.sow(NORTH, 1, es, eh) && es == NORTH && eh == 0); //error
//		bad.setBeans(SOUTH, 1, 1);
//		assert(bad.sow(SOUTH, 1, es, eh) && es == SOUTH && eh == 0);
//		bad.setBeans(NORTH, 1, 5);
//		assert(bad.sow(NORTH, 1, es, eh) && es == SOUTH && eh == 1);
//		bad.setBeans(SOUTH, 1, 5);
//		assert(bad.sow(SOUTH, 1, es, eh) && es == NORTH && eh == 1);
//	}
//
//	/*    if(true)
//		{
//			HumanPlayer hp("");
//			BadPlayer bp("");
//			SmartPlayer sp("");
//		}
//
//		if (true)
//		{
//			HumanPlayer hp("");
//			BadPlayer bp("");
//			SmartPlayer sp("");
//			Board b(6, 4);
//			Game(b, &hp, &bp);
//		}*/
//	cerr << "ALL PASS" << endl;
//}
#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif
#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

//void doBoardTests() {
//	Board b(3, 2);
//	assert(b.holes() == 3 && b.totalBeans() == 12 &&
//		b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
//	b.setBeans(SOUTH, 1, 1);
//	/*0 222
//	    122 0*/
//	b.moveToPot(SOUTH, 2, SOUTH);
//	/*0 222
//		102 2*/
//	assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 &&
//		b.beans(SOUTH, 2) == 0 && b.beans(SOUTH, POT) == 2 &&
//		b.beansInPlay(SOUTH) == 3);
//	Side es;
//	int eh;
//	b.sow(SOUTH, 3, es, eh);
//	assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
//		b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
//		b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
//
//	//bad arguments to constructor
//	Board bad(0, -1);
//	assert(bad.holes() == 1);
//	assert(bad.beans(NORTH, 0) == 0);
//	assert(bad.beans(SOUTH, 0) == 0);
//	assert(bad.beans(SOUTH, 1) == 0);
//	assert(bad.beans(NORTH, 1) == 0);
//	assert(bad.beansInPlay(NORTH) == 0);
//	assert(bad.beansInPlay(SOUTH) == 0);
//	assert(bad.totalBeans() == 0);
//
//	//typical construction
//	Board b(7, 5);
//	assert(b.beans(NORTH, 0) == 0); //pots uninitialized
//	assert(b.beans(SOUTH, 0) == 0);
//	for (int i = 1; i <= 7; i++)
//	{
//		assert(b.beans(NORTH, i) == 5);
//		assert(b.beans(SOUTH, i) == 5);
//	}
//	assert(b.beansInPlay(NORTH) == 35);
//	assert(b.beansInPlay(SOUTH) == 35);
//	assert(b.totalBeans() == 70);
//
//	//copy constructor and assignment
//	Board *ptr;
//	{
//		Board temp(8, 1);
//		//set pots to unique values
//		assert(temp.setBeans(NORTH, 0, 99));
//		assert(temp.setBeans(SOUTH, 0, 19));
//		for (int i = 1; i <= 8; i++) //set holes to unique values
//		{
//			assert(temp.setBeans(NORTH, i, i));
//			assert(temp.setBeans(SOUTH, i, 2 * i));
//		}
//		b = temp;
//		ptr = new Board(temp);
//	}
//	//check copy/assignment
//	assert(ptr->holes() == 8);
//	assert(b.holes() == 8);
//	assert(b.beans(NORTH, 0) == 99);
//	assert(b.beans(SOUTH, 0) == 19);
//	assert(ptr->beans(NORTH, 0) == 99);
//	assert(ptr->beans(SOUTH, 0) == 19);
//	for (int i = 1; i <= 8; i++)
//	{
//		assert(b.beans(NORTH, i) == i);
//		assert(b.beans(SOUTH, i) == 2 * i);
//		assert(ptr->beans(NORTH, i) == i);
//		assert(ptr->beans(SOUTH, i) == 2 * i);
//	}
//	//basic math
//	assert(b.beansInPlay(NORTH) == 36);
//	assert(b.beansInPlay(SOUTH) == 72);
//	assert(ptr->beansInPlay(NORTH) == 36);
//	assert(ptr->beansInPlay(SOUTH) == 72);
//	assert(b.totalBeans() == 108 + 19 + 99);
//	assert(ptr->totalBeans() == 108 + 19 + 99);
//	b = Board(6, 4);
//	//invalid moving to pot
//	assert(!b.moveToPot(NORTH, 0, NORTH));
//	assert(!b.moveToPot(NORTH, 0, SOUTH));
//	assert(!b.moveToPot(SOUTH, 0, SOUTH));
//	assert(!b.moveToPot(SOUTH, 0, NORTH));
//	assert(!b.moveToPot(NORTH, -1, NORTH));
//	assert(!b.moveToPot(NORTH, -1, SOUTH));
//	assert(!b.moveToPot(SOUTH, -1, SOUTH));
//	assert(!b.moveToPot(SOUTH, -1, NORTH));
//	assert(!b.moveToPot(NORTH, 7, NORTH));
//	assert(!b.moveToPot(NORTH, 7, SOUTH));
//	assert(!b.moveToPot(SOUTH, 7, SOUTH));
//	assert(!b.moveToPot(SOUTH, 7, NORTH));
//	//nothing changed
//	assert(b.beansInPlay(NORTH) == 24);
//	assert(b.beansInPlay(SOUTH) == 24);
//	assert(b.beans(NORTH, 0) == 0);
//	assert(b.beans(SOUTH, 0) == 0);
//	//move to pots
//	for (int i = 1; i <= 4; i++)
//	{
//		assert(b.moveToPot(NORTH, i, NORTH));
//		assert(b.moveToPot(SOUTH, i, NORTH));
//	}
//	for (int i = 5; i <= 6; i++)
//	{
//		assert(b.moveToPot(NORTH, i, SOUTH));
//		assert(b.moveToPot(SOUTH, i, SOUTH));
//	}
//	//leaves holes empty
//	assert(b.beansInPlay(NORTH) == 0);
//	assert(b.beansInPlay(SOUTH) == 0);
//	//goes in right pots
//	assert(b.beans(NORTH, 0) == 32);
//	assert(b.beans(SOUTH, 0) == 16);
//
//	//sow stuff
//
//	//invalid arguments
//	int eh = -99;
//	Side es = SOUTH;
//	Board b0(5, 1);
//	b = b0;
//	assert(!b0.setBeans(NORTH, -1, 999));
//	assert(!b0.setBeans(NORTH, 6, 999));
//	assert(!b0.setBeans(NORTH, 1, -666));
//	assert(b0.beans(NORTH, -1) == -1);
//	assert(b0.beans(SOUTH, -1) == -1);
//	assert(b0.beans(NORTH, 6) == -1);
//	assert(b0.beans(SOUTH, 6) == -1);
//	assert(b0.totalBeans() == 10); //no change
//	//invalid sow arguments
//	b = b0;
//	b.setBeans(NORTH, 0, 10);
//	b.setBeans(SOUTH, 0, 7);
//	assert(!b.sow(NORTH, 0, es, eh) && es == SOUTH && eh == -99);
//	assert(!b.sow(SOUTH, 0, es, eh) && es == SOUTH && eh == -99);
//	assert(!b.sow(NORTH, 6, es, eh) && es == SOUTH && eh == -99);
//	assert(!b.sow(SOUTH, 6, es, eh) && es == SOUTH && eh == -99);
//	assert(!b.sow(NORTH, -1, es, eh) && es == SOUTH && eh == -99);
//	assert(!b.sow(SOUTH, -1, es, eh) && es == SOUTH && eh == -99);
//	//sow empty pot
//	b.setBeans(NORTH, 1, 0);
//	b.setBeans(SOUTH, 1, 0);
//	assert(!b.sow(NORTH, 1, es, eh) && es == SOUTH && eh == -99);
//	assert(!b.sow(SOUTH, 1, es, eh) && es == SOUTH && eh == -99);
//	//unchanged
//	assert(b.beansInPlay(NORTH) == 4);
//	assert(b.beansInPlay(SOUTH) == 4);
//	//sow single bean into pot
//	b = b0;
//	assert(b.sow(NORTH, 1, es, eh) && es == NORTH && eh == 0);
//	assert(b.sow(SOUTH, 5, es, eh) && es == SOUTH && eh == 0);
//	assert(b.beans(NORTH, 1) == 0);
//	assert(b.beans(SOUTH, 5) == 0);
//	assert(b.beansInPlay(NORTH) == 4);
//	assert(b.beansInPlay(SOUTH) == 4);
//	assert(b.totalBeans() == 10);
//
//
//	//check won't land in opponent pot
//	b = b0;
//	b.setBeans(NORTH, 5, 5);
//	b.setBeans(NORTH, 0, 3);
//	assert(b.sow(NORTH, 5, es, eh) && es == NORTH && eh == 0 && b.beans(NORTH, 5) == 0);
//	for (int i = 1; i < 5; i++)
//	{
//		assert(b.beans(NORTH, i) == 2);
//	}
//	assert(b.beans(NORTH, 0) == 4);
//	assert(b.beansInPlay(NORTH) == 8);
//	b.setBeans(SOUTH, 1, 5);
//	b.setBeans(SOUTH, 0, 3);
//	assert(b.sow(SOUTH, 1, es, eh) && es == SOUTH && eh == 0 && b.beans(SOUTH, 1) == 0);
//	for (int i = 2; i <= 5; i++)
//	{
//		assert(b.beans(SOUTH, i) == 2);
//	}
//	assert(b.beans(SOUTH, 0) == 4);
//	assert(b.beansInPlay(SOUTH) == 8);
//
//	//loop back around NORTH
//	b = b0;
//	b.setBeans(NORTH, 2, 8);
//	b.setBeans(NORTH, 0, 3);
//	assert(b.sow(NORTH, 2, es, eh) && es == NORTH && eh == 5 && b.beans(NORTH, 2) == 0);
//	assert(b.beans(NORTH, 1) == 2);
//	assert(b.beans(NORTH, 0) == 4);
//	for (int i = 1; i <= 5; i++)
//	{
//		assert(b.beans(SOUTH, i) == 2);
//	}
//	assert(b.beans(SOUTH, 0) == 0);
//	assert(b.beansInPlay(NORTH) == 6);
//	assert(b.beansInPlay(SOUTH) == 10);
//
//	//loop back around SOUTH
//	b = b0;
//	b.setBeans(SOUTH, 4, 8);
//	b.setBeans(SOUTH, 0, 3);
//	assert(b.sow(SOUTH, 4, es, eh) && es == SOUTH && eh == 1 && b.beans(SOUTH, 4) == 0);
//	assert(b.beans(SOUTH, 5) == 2);
//	assert(b.beans(SOUTH, 0) == 4);
//	for (int i = 1; i <= 5; i++)
//	{
//		assert(b.beans(NORTH, i) == 2);
//	}
//	assert(b.beans(NORTH, 0) == 0);
//	assert(b.beansInPlay(SOUTH) == 6);
//	assert(b.beansInPlay(NORTH) == 10);
//
//	//many loops NORTH
//	b = b0;
//	b.setBeans(NORTH, 3, 23);
//	assert(b.sow(NORTH, 3, es, eh) && es == NORTH && eh == 2);
//	assert(b.beans(NORTH, 0) == 2);
//	assert(b.beans(NORTH, 1) == 3);
//	assert(b.beans(NORTH, 2) == 4);
//	assert(b.beans(NORTH, 3) == 2);
//	assert(b.beans(NORTH, 4) == 3);
//	assert(b.beans(NORTH, 5) == 3);
//	assert(b.beans(SOUTH, 0) == 0);
//	for (int i = 1; i <= 5; i++)
//	{
//		assert(b.beans(SOUTH, i) == 3);
//	}
//
//	//many loops SOUTH
//	b = b0;
//	b.setBeans(SOUTH, 3, 23);
//	assert(b.sow(SOUTH, 3, es, eh) && es == SOUTH && eh == 4);
//	assert(b.beans(SOUTH, 0) == 2);
//	assert(b.beans(SOUTH, 1) == 3);
//	assert(b.beans(SOUTH, 2) == 3);
//	assert(b.beans(SOUTH, 3) == 2);
//	assert(b.beans(SOUTH, 4) == 4);
//	assert(b.beans(SOUTH, 5) == 3);
//	assert(b.beans(NORTH, 0) == 0);
//	for (int i = 1; i <= 5; i++)
//	{
//		assert(b.beans(NORTH, i) == 3);
//	}
//
//	//"typical" sowing of one and many beans
//	b = b0;
//	b.setBeans(NORTH, 4, 3);
//	b.setBeans(SOUTH, 2, 3);
//	assert(b.sow(NORTH, 4, es, eh) && es == NORTH && eh == 1);
//	assert(b.beans(NORTH, 4) == 0);
//	assert(b.beans(NORTH, 3) == 2);
//	assert(b.beans(NORTH, 2) == 2);
//	assert(b.beans(NORTH, 1) == 2);
//	assert(b.sow(SOUTH, 2, es, eh) && es == SOUTH && eh == 5);
//	assert(b.beans(SOUTH, 2) == 0);
//	assert(b.beans(SOUTH, 3) == 2);
//	assert(b.beans(SOUTH, 4) == 2);
//	assert(b.beans(SOUTH, 5) == 2);
//	assert(b.sow(NORTH, 5, es, eh) && es == NORTH && eh == 4);
//	assert(b.beans(NORTH, 5) == 0 && b.beans(NORTH, 4) == 1);
//	assert(b.sow(SOUTH, 1, es, eh) && es == SOUTH && eh == 2);
//	assert(b.beans(SOUTH, 1) == 0 && b.beans(SOUTH, 2) == 1);
//
//	//sowing with only 1 hole
//	bad.setBeans(NORTH, 1, 1);
//	assert(bad.sow(NORTH, 1, es, eh) && es == NORTH && eh == 0); //error
//	bad.setBeans(SOUTH, 1, 1);
//	assert(bad.sow(SOUTH, 1, es, eh) && es == SOUTH && eh == 0);
//	bad.setBeans(NORTH, 1, 5);
//	assert(bad.sow(NORTH, 1, es, eh) && es == SOUTH && eh == 1);
//	bad.setBeans(SOUTH, 1, 5);
//	assert(bad.sow(SOUTH, 1, es, eh) && es == NORTH && eh == 1);
//
//}

void doBoardTests(){
	Board wrong(-1, -1);
	assert(wrong.holes() == 1);
	assert(wrong.beans(NORTH, 0) == 0);
	assert(wrong.beans(SOUTH, 0) == 0);
	assert(wrong.beans(SOUTH, 1) == 0);
	assert(wrong.beans(NORTH, 1) == 0);
	assert(wrong.beansInPlay(NORTH) == 0);
	assert(wrong.beansInPlay(SOUTH) == 0);
	assert(wrong.totalBeans() == 0);

	//construction
	Board b(6, 4);
	assert(b.beans(NORTH, 0) == 0);
	assert(b.beans(SOUTH, 0) == 0);
	for (int i = 1; i <= 6; i++)
	{
		assert(b.beans(NORTH, i) == 4);
		assert(b.beans(SOUTH, i) == 4);
	}
	assert(b.beansInPlay(NORTH) == 24);
	assert(b.beansInPlay(SOUTH) == 24);
	assert(b.totalBeans() == 48);

	//beans
	assert(b.beans(NORTH, 20) == -1);
	assert(b.beans(NORTH, 0) == 0); //beans() should work for pot as well

	//move to pot
	assert(!b.moveToPot(NORTH, 0, NORTH));
	assert(!b.moveToPot(NORTH, 7, SOUTH));
	assert(b.moveToPot(NORTH, 6, NORTH));
	assert(b.beans(NORTH, 6) == 0); //check that all beans have been moved
	assert(b.beansInPlay(NORTH) == 20);
	assert(b.moveToPot(NORTH, 6, NORTH)); //should still work even though beans in that hole is 0
	b.setBeans(NORTH, 6, 4);
	assert(b.totalBeans() == 52); //check that total has been updated 
	assert(b.beansInPlay(NORTH) == 24); //check beans in play has been updated
	b.setBeans(NORTH, 0, 0);
	assert(b.totalBeans() == 48);
	assert(b.beansInPlay(NORTH) == 24); //remains unchanged


	//Board b2(4, 0);
	//SmartPlayer south("bob");
	//b2.setBeans(NORTH, 0, 4);
	//b2.setBeans(NORTH, 1, 0);
	//b2.setBeans(NORTH, 2, 0);
	//b2.setBeans(NORTH, 3, 1);
	//b2.setBeans(SOUTH, 0, 1);
	//b2.setBeans(SOUTH, 1, 2);
	//b2.setBeans(SOUTH, 2, 0);
	//b2.setBeans(SOUTH, 4, 1);
	//assert(south.chooseMove(b2, SOUTH) == 4);
	//sow
	Board b1(2, 0);
	b1.setBeans(NORTH, 1, 5);
	int eh;
	Side es;
	assert(!b1.sow(NORTH, 2, es, eh)); //cannot sow an empty hole
	assert(b1.sow(NORTH, 1, es, eh)); //tests that sowing is only done 5 times, even though there is one bean remaining in north's hole 1
	/*0 5 0
		0 0 0*/
		/*1 1 1
			1 1 0*/
	assert(b1.beans(NORTH, 0) == 1 && b1.beans(NORTH, 1) == 1 && b1.beans(NORTH, 2) == 1 && b1.beans(SOUTH, 0) == 0 && b1.beans(SOUTH, 1) == 1 && b1.beans(SOUTH, 2) == 1 && es == NORTH && eh == 1);
	assert(!b1.sow(NORTH, 0, es, eh)); //cannot sow a pot
	Board b2(2, 0);
	b2.setBeans(SOUTH, 1, 8);
	/*0 0 0
		8 0 0*/
		/*0 1 2
			1 2 2*/
	assert(b2.sow(SOUTH, 1, es, eh));// test for south side, test the direction of sow
	assert(b2.beans(NORTH, 0) == 0 && b2.beans(NORTH, 1) == 1 && b2.beans(NORTH, 2) == 2 && b2.beans(SOUTH, 0) == 2 && b2.beans(SOUTH, 1) == 1 && b2.beans(SOUTH, 2) == 2 && es == NORTH && eh == 2);


}

void doGameTests()
{
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);
	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.status(over, hasWinner, winner);
	assert(!over && !hasWinner && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   0  1  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && !hasWinner && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && !hasWinner && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  0  1
	g.status(over, hasWinner, winner);
	assert(!over && !hasWinner && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

	g.move();
	//   0  0  0
	// 1         4
	//   0  0  0
	g.status(over, hasWinner, winner);
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);

	Board c(2, 1);
	Game h(c, &bp1, &bp2);
	/*0 1 1
		1 1 0*/
	h.status(over, hasWinner, winner);
	assert(!over && !hasWinner && h.beans(NORTH, POT) == 0 && h.beans(SOUTH, POT) == 0 &&
		h.beans(NORTH, 1) == 1 && h.beans(NORTH, 2) == 1 &&
		h.beans(SOUTH, 1) == 1 && h.beans(SOUTH, 2) == 1 );
	h.move();  //my bad player takes the last hole always
	/*0 1 1
		1 0 1*/
	/*0 1 0
		0 0 3*/
	h.status(over, hasWinner, winner);
	assert(over && hasWinner && h.beans(NORTH, POT) == 1 && h.beans(SOUTH, POT) == 3 &&
		h.beans(NORTH, 1) == 0 && h.beans(NORTH, 2) == 0 &&
		h.beans(SOUTH, 1) == 0 && h.beans(SOUTH, 2) == 0);
	assert(winner == SOUTH);
}

void doPlayerTests()
{
	HumanPlayer hp("Marge");
	assert(hp.name() == "Marge"  &&  hp.isInteractive());
	BadPlayer bp("Homer");
	assert(bp.name() == "Homer" && !bp.isInteractive());
	SmartPlayer sp("Lisa");
	assert(sp.name() == "Lisa" && !sp.isInteractive());
	Board player(3, 2);
	player.setBeans(SOUTH, 2, 0);
	cout << "=========" << endl;
	//int n = hp.chooseMove(player, SOUTH);
	//cout << "=========" << endl;
	//assert(n == 1 || n == 3);
	int n = bp.chooseMove(player, SOUTH);
	assert(n == 1 || n == 3);
	n = sp.chooseMove(player, SOUTH);
	assert(n == 1 || n == 3);
	player.setBeans(SOUTH, 1, 0);
	player.setBeans(SOUTH, 3, 0);
	assert(bp.chooseMove(player, SOUTH) == -1);
	//hp.chooseMove(player, SOUTH);


	Board p1(4, 0);
	p1.setBeans(NORTH, 0, 4);
	p1.setBeans(NORTH, 1, 0);
	p1.setBeans(NORTH, 2, 0);
	p1.setBeans(NORTH, 3, 1);
	p1.setBeans(SOUTH, 0, 1);
	p1.setBeans(SOUTH, 1, 2);
	p1.setBeans(SOUTH, 2, 0);
	p1.setBeans(SOUTH, 4, 1);
	/*4 0 0 1 0
	    2 0 0 1 1*/
	assert(sp.chooseMove(p1, SOUTH) == 4 || 1); //hole 4 and 1 would both lead to victory

	Board p2(2, 1);
	assert(sp.chooseMove(p1, SOUTH) == 2); //hole 2 would lead to instant victory

	//(6,4) smartplayer vs badplayer -> smart wins
	// badplayer vs smartplayer -> smart wins
}


int main()
{
	//doPlayerTests();
	//SmartPlayer hp("Marge");
	//SmartPlayer bp("Homer");
	//Board b(6,4);
	//Game g(b, &hp, &bp);
	//g.play();
	//doGameTests();
	//doBoardTests();
	//Board a(3,0);
	//SmartPlayer south("Asdf");
	//a.setBeans(NORTH, 0, 4);
	//a.setBeans(NORTH, 1, 0);
	//a.setBeans(NORTH, 2, 1);
	//a.setBeans(NORTH, 3, 0);
	//a.setBeans(SOUTH, 0, 0);
	//a.setBeans(SOUTH, 1, 4);
	//a.setBeans(SOUTH, 2, 0);
	//a.setBeans(SOUTH, 3, 1);
	//cout << south.chooseMove(a, SOUTH);
	//cout << south.chooseMove(a, SOUTH);
	//Board test(2, 2);
	//Board hello(1, 1);
	//test = hello; //simple test for assignment operator
	//assert(test.holes() == 1 && test.beans(NORTH,1) == 1 && test.beans(SOUTH,1) == 1 && test.totalBeans() == 2 && test.beans(NORTH, POT) == 0);
	//Board b(3, 2);
	//assert(b.holes() == 3 && b.totalBeans() == 12 &&
	//	b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
	//b.setBeans(SOUTH, 1, 1);
	//b.moveToPot(SOUTH, 2, SOUTH);
	//assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 &&
	//	b.beans(SOUTH, 2) == 0 && b.beans(SOUTH, POT) == 2 &&
	//	b.beansInPlay(SOUTH) == 3);
	//Side es;
	//int eh;
	//b.sow(SOUTH, 3, es, eh);
	//assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
	//	b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
	//	b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
	cout << "Passed all tests" << endl;
}