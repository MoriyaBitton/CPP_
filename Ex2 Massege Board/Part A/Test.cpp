#include "Board.hpp"
#include "doctest.h"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;


TEST_CASE("Empty Board") {
	ariel::Board board;
	
	CHECK(board.read(0, 0, Direction::Vertical, 5) == "_____");
	CHECK(board.read(0, 0, Direction::Horizontal, 5) == "_____");
}

TEST_CASE("Empty places") {
	ariel::Board board;
	
	board.post(0, 1, Direction::Horizontal, "cpp");
	CHECK(board.read(0, 1, Direction::Horizontal, 3) == "cpp");
	CHECK(board.read(0, 0, Direction::Horizontal, 5) == "_cpp_");
	
	board.post(1, 1, Direction::Vertical, "pp");
	CHECK(board.read(0, 1, Direction::Vertical, 3) == "cpp");
	CHECK(board.read(0, 1, Direction::Vertical, 4) == "cpp_");
}

TEST_CASE("Good Overriding") {
	ariel::Board board;
	
	board.post(0, 1, Direction::Horizontal, "cpp");
	CHECK(board.read(0, 1, Direction::Horizontal, 3) == "cpp");
	
	board.post(0, 2, Direction::Vertical, "olimppiada");
	board.post(0, 4, Direction::Vertical, "ymca");
	CHECK(board.read(0, 0, Direction::Horizontal, 5) == "_copy");
}

TEST_CASE("Direction play") {
	ariel::Board board;
	
	board.post(0, 0, Direction::Horizontal, "Game");
	board.post(1, 0, Direction::Horizontal, "over");
	board.post(2, 0, Direction::Horizontal, "olives");
	board.post(3, 0, Direction::Horizontal, "door");
	board.post(5, 0, Direction::Horizontal, "Justin Bieber");
	board.post(6, 0, Direction::Horizontal, "open");
	board.post(7, 0, Direction::Horizontal, "beauty");
	board.post(8, 0, Direction::Horizontal, "!?");
	CHECK(board.read(0, 0, Direction::Vertical, 4) == "Good");
	CHECK(board.read(5, 0, Direction::Vertical, 4) == "Job!");
	CHECK(board.read(0, 0, Direction::Vertical, 9) == "Good_Job!");
}

TEST_CASE("Good post & read code") {
	ariel::Board board;
	
	board.post(0, 3, Direction::Vertical, "moriya");
	CHECK(board.read(0, 3, Direction::Vertical, 6) == "moriya");
	
	board.post(1, 0, Direction::Horizontal, "doriya");
	board.post(1, 5, Direction::Horizontal, "alice");
	CHECK(board.read(1, 0, Direction::Horizontal, 6) == "doriya");
	CHECK(board.read(1, 0, Direction::Horizontal, 10) == "doriyalice");
	CHECK(board.read(1, 3, Direction::Horizontal, 10) == "iyalice___");
	CHECK(board.read(1, 10, Direction::Horizontal, 1) == "_");
	
	board.post(0, 11, Direction::Horizontal, "I want to break free");
	CHECK(board.read(0, 11, Direction::Horizontal, 20) == "I want to break free");
	CHECK(board.read(0, 23, Direction::Horizontal, 9) == "eak free_");
	CHECK(board.read(0, 30, Direction::Horizontal, 1) == "e");
	CHECK(board.read(0, 11, Direction::Horizontal, 2) == "I ");
}
