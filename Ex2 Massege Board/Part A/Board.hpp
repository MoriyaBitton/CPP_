#pragma once

#include <string>
#include <vector>

#include "Direction.hpp"


namespace ariel {
	
	using namespace std; //for string 
	
	class Board {
	public: 
		void post(unsigned int row, unsigned int col, Direction d, string s);
		string read(unsigned int row, unsigned int col, Direction d, unsigned int n);
		void show();
	private: 
		vector<string> _board; 
		unsigned int numOfCols();
		void addRow (unsigned int rowToAdd);
		void addCol (unsigned int colsToAdd);
	};
}
