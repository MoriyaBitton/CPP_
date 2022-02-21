#pragma once

#include <string>
#include <vector>

#include "Direction.hpp"
#include "ResizeMethod.hpp"


namespace ariel {
	
	using namespace std; 
	
	class Board {
	public: 
		void post(unsigned int row, unsigned int col, Direction d, const string& s);
		string read(unsigned int row, unsigned int col, Direction d, unsigned int n);
		void show();
	private:
		vector<string> _board;
		
		// dynamic points that represent the area of the posted message
		unsigned int row_start;
		unsigned int col_start;
		
		// represent us the board who not init yet
		bool initialized = false;
		
		unsigned int numOfCols();
		
		// update board size
		void addRow (unsigned int rowToAdd, ResizeMethod resize);
		void addCol (unsigned int colsToAdd, ResizeMethod resize);
		
		// resize bord by the same parameters of "post"
		void resizeBoard(unsigned int row, unsigned int col, Direction d, const string& s);
	};
}
