#include "snowman.hpp"

#include <iostream>
#include <stdexcept>

constexpr int SEVEN = 10000000;
constexpr int SIX = 1000000;
constexpr int FIVE = 100000;
constexpr int FOUR = 10000;
constexpr int THREE = 1000;
constexpr int TWO = 100;
constexpr int TEN = 10;

namespace ariel{

string getHat(int x){
	int h = 0;
	h = (x / SEVEN);
	switch(h){
		case 1:
			return " _===_ ";
		case 2:
			return "  ___ \n .....";
		case 3:
			return "   _  \n  /_\\ ";
		case 4:
			return "  ___ \n (_*_)";
		default:
			throw invalid_argument ("got invalid H");
	}
	
}

string getNoseMouth(int x){
	int n = ((x / (SIX)) % TEN);
	switch(n){
		case 1:
			return ",";
		case 2:
			return ".";
		case 3:
			return "_";
		case 4:
			return " ";
		default:
			throw invalid_argument ("got invalid N");
	}
	
}

string getLeftEye(int x){
	int l = ((x / (FIVE)) % TEN);
	switch(l){
		case 1:
			return ".";
		case 2:
			return "o";
		case 3:
			return "O";
		case 4:
			return "-";
		default:
			throw invalid_argument ("got invalid L");
	}
	
}

string getRightEye(int x){
	int r = ((x / (FOUR)) % TEN);
	switch(r){
		case 1:
			return ".";
		case 2:
			return "o";
		case 3:
			return "O";
		case 4:
			return "-";
		default:
			throw invalid_argument ("got invalid R");
	}
	
}

string getLeftArm(int x){
	int x_ = ((x / (THREE)) % TEN);
	switch(x_){
		case 1:
		case 4:
		case 3:
			return " ";
		case 2:
			return "\\";
		default:
			throw invalid_argument ("got invalid X");
	}
	
}

string getLeftArm_low(int x){
	int x_ = ((x / (THREE)) % TEN);
	switch(x_){
		case 1:
			return "<";
		case 2:
		case 4:
			return " ";
		case 3:
			return "/";
		default:
			throw invalid_argument ("got invalid X");
	}
	
}

string getRightArm(int x){
	int y = ((x / (TWO)) % TEN);
	switch(y){
		case 1:
		case 4:
		case 3:
			return " ";
		case 2:
			return "/";
		default:
			throw invalid_argument ("got invalid Y");
	}
	
}

string getRightArm_low(int x){
	int y = ((x / (TWO)) % TEN);
	switch(y){
		case 1:
			return ">";
		case 2:
		case 4:
			return " ";
		case 3:
			return "\\";
		default:
			throw invalid_argument ("got invalid Y");
	}
	
}

string getTorso(int x){
	int t = ((x / (TEN)) % TEN);
	switch(t){
		case 1:
			return " : ";
		case 2:
			return "] [";
		case 3:
			return "> <";
		case 4:
			return "   ";
		default:
			throw invalid_argument ("got invalid T");
	}
	
}

string getBase(int x){
	int b = (x % TEN);
	switch(b){
		case 1:
			return " : ";
		case 2:
			return "\" \"";
		case 3:
			return "___";
		case 4:
			return "   ";
		default:
			throw invalid_argument ("got invalid B");
	}
	
}


// HNLRXYTB	
string snowman(int x){
	// if(x == NULL) return "got NULL input";
	
	string ans = getHat(x);
	ans += "\n";
	ans += getLeftArm(x) + "(" + getLeftEye(x) + getNoseMouth(x) + getRightEye(x) + ")" + getRightArm(x);
	ans += "\n";
	ans += getLeftArm_low(x) + "(" + getTorso(x) + ")" + getRightArm_low(x);
	ans += "\n";
	ans += + " (" + getBase(x) + ") ";
	ans += "\n";
	
	return ans;
}

} // namespace ariel
