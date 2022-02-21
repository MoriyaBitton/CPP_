#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
	ariel::Board board;

	cout << "\ntest:\n" << endl;
	board.post(/*row=*/100099, /*column=*/100200, Direction::Vertical, "cpp");
	cout << board.read(/*row=*/100099, /*column=*/100200, Direction::Horizontal, /*length=*/5) << board.read(/*row=*/100099, /*column=*/100200, Direction::Vertical, /*length=*/3) << endl; // "I <3 cpp"
	cout << '\n' << endl;
	board.show();
	
	// cout << "\nPrint testing:\n" << endl;
	// board.post(/*row=*/100, /*column=*/200, Direction::Horizontal, "I <3 cpp");
	// cout << board.read(/*row=*/99, /*column=*/206, Direction::Vertical, /*length=*/3) << endl; // "_p_"
	// cout << board.read(/*row=*/100, /*column=*/199, Direction::Horizontal, /*length=*/10) << endl; // "_I <3 cpp_ "
	
	// board.post(/*row=*/99, /*column=*/206, Direction::Vertical, "cpp");
	// cout << board.read(/*row=*/100, /*column=*/200, Direction::Horizontal, /*length=*/5) << board.read(/*row=*/99, /*column=*/206, Direction::Vertical, /*length=*/3) << endl; // "I <3 cpp"
	// cout << board.read(/*row=*/101, /*column=*/205, Direction::Horizontal, /*length=*/3) << endl; // "_p_"
	
	// cout << '\n' << endl;
	// board.show(); // shows the board in a reasonable way. For example:
	// 	//    99:  ______c__
	// 	//    100: I <3 cpp_
	// 	//    101: ______p__
	// 	//    102: _________
		
	// cout << '\n' << endl;
	// board.post(/*row=*/100, /*column=*/205, Direction::Horizontal, "Game's");
	// board.post(/*row=*/101, /*column=*/205, Direction::Horizontal, "over");
	// board.post(/*row=*/102, /*column=*/205, Direction::Horizontal, "olives");
	// board.post(/*row=*/103, /*column=*/205, Direction::Horizontal, "door");
	// board.post(/*row=*/105, /*column=*/205, Direction::Horizontal, "Justin Bieber");
	// board.post(/*row=*/106, /*column=*/205, Direction::Horizontal, "open");
	// board.post(/*row=*/107, /*column=*/205, Direction::Horizontal, "beauty");
	// board.post(/*row=*/108, /*column=*/205, Direction::Horizontal, "!?");
	
	// cout << board.read(/*row=*/100, /*column=*/205, Direction::Vertical, /*length=*/4) << endl; // "Good"
	// cout << board.read(/*row=*/105, /*column=*/205, Direction::Vertical, /*length=*/4) << endl; // "Job!"
	// cout << board.read(/*row=*/100, /*column=*/205, Direction::Vertical, /*length=*/9) << endl; // "Good_Job!"

	// cout << '\n' << endl;
	// board.show(); // shows the board in a reasonable way. For example:
	// 	//	99:	______c____________
	// 	//	100:	I <3 Gam's_________
	// 	//	101:	_____over__________
	// 	//	102:	_____olives________
	// 	//	103:	_____door__________
	// 	//	104:	___________________
	// 	//	105:	_____Justin Bieber_
	// 	//	106:	_____open__________
	// 	//	107:	_____beauty________
	// 	//	108:	_____!?____________
		
	// cout << '\n' << endl;
	// board.post(/*row=*/99, /*column=*/218, Direction::Horizontal, "Moriya's");
	// board.post(/*row=*/97, /*column=*/219, Direction::Vertical, "Project");
	// board.post(/*row=*/102, /*column=*/218, Direction::Horizontal, "Score");
	// board.post(/*row=*/103, /*column=*/215, Direction::Horizontal, "sweet SIXTEEN!");
	
	// cout << board.read(/*row=*/99, /*column=*/218, Direction::Horizontal, /*length=*/9) << board.read(/*row=*/97, /*column=*/219, Direction::Vertical, /*length=*/8) <<
	// board.read(/*row=*/102, /*column=*/218, Direction::Horizontal, /*length=*/6) << board.read(/*row=*/103, /*column=*/221, Direction::Horizontal, /*length=*/8) << endl; 
	// // Moriya's Project score sixteen
	
	// cout << '\n' << endl;
	// board.show(); // shows the board in a reasonable way. For example:
	// 	//	97:	___________________P__________
	// 	//	98:	___________________r__________
	// 	//	99:	______c___________Moriya's____
	// 	//	100:	I <3 Game's________j__________
	// 	//	101:	_____over__________e__________
	// 	//	102:	_____olives_______Score_______
	// 	//	103:	_____door______sweet SIXTEEN!_
	// 	//	104:	______________________________
	// 	//	105:	_____Justin Bieber____________
	// 	//	106:	_____open_____________________
	// 	//	107:	_____beauty___________________
	// 	//	108:	_____!?_______________________
		
	// cout << "\nPrint empty testing:\n" << endl;
	// board.post(/*row=*/0, /*column=*/0, Direction::Horizontal, "");
	// cout << board.read(/*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/3) << endl;
	
	// board.post(/*row=*/0, /*column=*/0, Direction::Vertical, "");
	// cout << board.read(/*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/3) << endl;
	
	// board.post(/*row=*/0, /*column=*/0, Direction::Horizontal, "");
	// cout << board.read(/*row=*/0, /*column=*/0, Direction::Vertical, /*length=*/3) << endl;
	
	// board.post(/*row=*/0, /*column=*/0, Direction::Vertical, "");
	// cout << board.read(/*row=*/0, /*column=*/0, Direction::Vertical, /*length=*/3) << endl;
}

