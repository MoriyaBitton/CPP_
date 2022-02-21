#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "Board.hpp" 


namespace ariel {

	//numOfRows = vector.size
	constexpr int OFFSET = 1;
	
	unsigned int Board::numOfCols(){
		if(_board.empty()){
			return 0;
		}
		return _board[0].size();
	}
	
	void Board::addRow (unsigned int rowToAdd){
		// add to memo and delete old one, in the new places put "_"
		string emptyRow(numOfCols(),'_');
		_board.resize(_board.size() + rowToAdd, emptyRow);				
	}
	
	void Board::addCol (unsigned int colsToAdd){
		for(unsigned int j = 0; j < _board.size(); j++){
			_board[j] += string(colsToAdd,'_');
		}
	}
	
	void Board::post(unsigned int row, unsigned int col, Direction d, string s){
		// take care of board size
		unsigned int maxRow = row + OFFSET;
		if(d == Direction::Vertical){
			maxRow += s.size();
		}
		if(maxRow > _board.size()) {
			addRow(maxRow - _board.size());
		}
		
		unsigned int maxCol = col + OFFSET;
		if(d == Direction::Horizontal){
			maxCol += s.size();
		}
		if(maxCol > numOfCols()){
			addCol(maxCol - numOfCols());
		}
		
		// add the message
		if (d==Direction::Horizontal) { // right
			for(unsigned int i = 0; i < s.size(); i++){
				_board[row][i + col] = s[i];
			}	
		} else { // down (d==Direction::Vertical)
			for(unsigned int i = 0; i < s.size(); i++){
				_board[i + row][col] = s[i];
			}
		}		
	}
	
	string Board::read(unsigned int row, unsigned int col, Direction d, unsigned int n){
		string ans;
		
		if (d==Direction::Horizontal) { // right
			if (row >= _board.size()){
				ans = string(n,'_');
			} else {
				size_t maxColToRead = col+n;
				for(unsigned int i = col; i < min(maxColToRead, _board[row].size()); i++){
					ans += _board[row][i];
				}
				
			} 
		} else { // down // (d==Direction::Vertical)
			if (col >= numOfCols()){
				ans = string(n,'_');
			} else {
				size_t maxRowToRead = row+n;
				for(unsigned int i = row; i < min<size_t>(maxRowToRead, _board.size()); i++){
					ans += _board[i][col];
				}
				
			} 
		}
		
		if (ans.size() < n ) {
			ans += string(n - ans.size(), '_');
		}
		return ans;
	}
	
	void Board::show(){
	}
}
