#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "Board.hpp" 


namespace ariel {

	constexpr int OFFSET = 1;
	
	unsigned int Board::numOfCols() {
		if (_board.empty()) {
			return 0;
		}
		return _board[0].size();
	}
	
	void Board::addRow (unsigned int rowToAdd, ResizeMethod resize) {
		string emptyRow(numOfCols(),'_');
		if (resize == ResizeMethod::After) { 
			_board.resize(_board.size() + rowToAdd, emptyRow);
		} else { // resize == ResizeMethod::Before
			_board.insert(_board.begin(), rowToAdd, emptyRow);
		}				
	}
	
	void Board::addCol (unsigned int colsToAdd, ResizeMethod resize) {
		for (unsigned int j = 0; j < _board.size(); j++) {
			if (resize == ResizeMethod::After) {
				_board[j] += string(colsToAdd,'_');	
			} else{
				_board[j] = string(colsToAdd,'_') + _board[j]; // sum two strings
			}
		}
	}
	
	void Board::post (unsigned int row, unsigned int col, Direction d, const string& s) {
		resizeBoard(row, col, d, s);
		
		// add message
		if (d==Direction::Horizontal) { 
			for (unsigned int i = 0; i < s.size(); i++) {
				_board[row - row_start][i + col - col_start] = s[i];
			}
		} else { // Direction::Vertical
			for (unsigned int i = 0; i < s.size(); i++) {
				_board[i + row - row_start][col - col_start] = s[i];
			}
		}		
	}
	
	void Board::resizeBoard (unsigned int row, unsigned int col, Direction d, const string& s) {
		if (!initialized){
			row_start = row;
			col_start = col;
			initialized = true;
		}
		
		// update by row
		unsigned int maxRow = row + OFFSET;
		if (d == Direction::Vertical) {
			maxRow += s.size();
		}
		
		if (row < row_start) {
			addRow(row_start - row, ResizeMethod::Before);
			row_start = row;
		}
		
		if (maxRow > row_start + _board.size()) {
			addRow(maxRow - row_start - _board.size(), ResizeMethod::After); 
		} 
		
		// update by col
		unsigned int maxCol = col + OFFSET;
		if (d == Direction::Horizontal) {
			maxCol += s.size();
		}
		
		if (col < col_start) {
			addCol(col_start - col, ResizeMethod::Before);
			col_start = col;
		}
		
		if (maxCol > col_start + numOfCols()) {
			addCol(maxCol - col_start - numOfCols(), ResizeMethod::After); 
		}
	}
	
	string Board::read(unsigned int row, unsigned int col, Direction d, unsigned int n){		
		string ans;
		if (!initialized) { // board is not initialized
			ans = string(n,'_');
			return ans;
		}
		
		if (d==Direction::Horizontal) { 
			if (row < row_start /*before board*/|| row - row_start > _board.size() /*after board*/) {
				ans = string(n,'_');
				return ans;
			}
			if (col < col_start) { // add empty cols befor row_start
				ans += string(min(col_start - col, n),'_');
			} 
			if (col + n > col_start) { // add text from the bord itself
				unsigned int maxColToRead = col + n - col_start;
				for (unsigned int i = max(col, col_start) - col_start; i < min(maxColToRead, numOfCols()); i++) {
					ans += _board[row - row_start][i];
				}
			}
		} else { // Direction::Vertical
			if (col < col_start /*before board*/|| col - col_start > numOfCols() /*after board*/) { 
				ans = string(n,'_');
				return ans;
			} 
			if (row < row_start) { // add empty rows before col_start
				ans += string(min(row_start - row, n),'_');
			}
			if (row + n > row_start) { // add test from the bord itself
				size_t maxRowToRead = row + n - row_start;
				for (unsigned int i = max(row, row_start) - row_start; i < min(maxRowToRead, _board.size()); i++) {
				
					ans += _board[i][col - col_start];
				}
			}	
		}
		
		if (ans.size() < n) { // add empty rows/ cols after maxRowToRead/ maxColToRead 
			ans += string(n - ans.size(), '_');
		}
		return ans;
	}
	
	void Board::show(){
		for (unsigned int i = 0; i < _board.size(); i++) {
			cout << i + row_start << ":\t" << _board[i] << endl;
		}
	}
}
