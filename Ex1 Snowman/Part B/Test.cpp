#include "doctest.h"
#include "snowman.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;


string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

// snowman
TEST_CASE("Good snowman code") {
    CHECK(nospaces(snowman(11114411)) == nospaces("_===_\n(.,.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(22221122)) == nospaces("___ \n .....\n(o.o)\n<(] [)>\n(\" \")"));
    CHECK(nospaces(snowman(33332233)) == nospaces("  _  \n  /_\\ \n\\(O_O)/\n(> <)\n(___)"));
    CHECK(nospaces(snowman(44441144)) == nospaces("___ \n (_*_)\n(- -)\n<(   )>\n(   )"));
    
    CHECK(nospaces(snowman(33232124)) == nospaces("  _  \n  /_\\ \n\\(o_O)\n (] [)>\n (   )"));
    CHECK(nospaces(snowman(12222212)) == nospaces(" _===_\n\\(o.o)/\n ( : )\n (\" \")"));
    CHECK(nospaces(snowman(44444432)) == nospaces(" ___\n(_*_)\n(- -)\n(> <)\n(\" \")"));
    CHECK(nospaces(snowman(44441144)) == nospaces("___ \n (_*_)\n(- -)\n<(   )>\n(   )"));
    CHECK(nospaces(snowman(41341144)) == nospaces("  ___\n (_*_)\n (O,-)\n<(   )>\n (   )"));
    CHECK(nospaces(snowman(11111111)) == nospaces(" _===_\n (.,.)\n<( : )>\n ( : )"));
    CHECK(nospaces(snowman(22222222)) == nospaces("  ___\n .....\n\\(o.o)/\n (] [)\n (\" \")"));
    CHECK(nospaces(snowman(23232223)) == nospaces("  ___\n .....\n\\(o_O)/\n (] [)\n (___)"));
}

TEST_CASE("Bad snowman code") {
    CHECK_THROWS(snowman(5));
    CHECK_THROWS(snowman(11114410));
    CHECK_THROWS(snowman(111));
    CHECK_THROWS(snowman(0));
    
    CHECK_THROWS(snowman(555));
    CHECK_THROWS_AS(snowman(555), logic_error);
    CHECK_THROWS_AS(snowman(11114511), invalid_argument);

    CHECK_THROWS(snowman(2224));
    CHECK_THROWS_AS(snowman(2224), logic_error);
    CHECK_THROWS_AS(snowman(11110011), invalid_argument);

    CHECK_THROWS(snowman(5551234));
    CHECK_THROWS_AS(snowman(5551234), logic_error);
    CHECK_THROWS_AS(snowman(11114011), invalid_argument);

    CHECK_THROWS(snowman(123451234));
    CHECK_THROWS_AS(snowman(123451234), logic_error);
    CHECK_THROWS_AS(snowman(11114000), invalid_argument);

    // check negative values
    CHECK_THROWS(snowman(-1232));
    CHECK_THROWS_AS(snowman(-1232), logic_error);
    CHECK_THROWS_AS(snowman(-12341234), logic_error);

    CHECK_THROWS(snowman(-9999));
    CHECK_THROWS_AS(snowman(-9999), logic_error);
    CHECK_THROWS_AS(snowman(-999999999), logic_error);
}

TEST_CASE("Check Throw message") {
    CHECK_THROWS_WITH_MESSAGE(snowman(5), "got invalid H", "");
    CHECK_THROWS_WITH_MESSAGE(snowman(6060), "got invalid H", "");
    CHECK_THROWS_WITH_MESSAGE(snowman(-560), "got invalid H", "");
    CHECK_THROWS_WITH_MESSAGE(snowman(-60600), "got invalid H", "");
    CHECK_THROWS_WITH_MESSAGE(snowman(123456789), "got invalid H", "");
    CHECK_THROWS_WITH_MESSAGE(snowman(-123456789), "got invalid H", "");
}


// getHat
TEST_CASE("Good Hat code") {
    CHECK(nospaces(snowman(11114411)) == nospaces("_===_\n(.,.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(21114411)) == nospaces("  ___ \n .....\n(.,.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(31114411)) == nospaces("  _  \n  /_\\ \n(.,.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(41114411)) == nospaces("  ___ \n (_*_)\n(.,.)\n( : )\n( : )"));   
} 

TEST_CASE("Bad Hat code") {
    CHECK_THROWS(snowman(51114411));
    CHECK_THROWS(snowman(91114411));
    CHECK_THROWS_WITH_MESSAGE(snowman(01114411), "got invalid H", "");
}


// getNoseMouth
TEST_CASE("Good Nose Mouth code") {
    CHECK(nospaces(snowman(11114411)) == nospaces("_===_\n(.,.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(22114411)) == nospaces("  ___ \n .....\n(...)\n( : )\n( : )"));
    CHECK(nospaces(snowman(33114411)) == nospaces("   _  \n  /_\\ \n(._.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(44114411)) == nospaces("  ___ \n (_*_)\n(. .)\n( : )\n( : )"));   
}

TEST_CASE("Bad Nose Mouth code") {
    CHECK_THROWS(snowman(15114411));
    CHECK_THROWS(snowman(10114411));
    CHECK_THROWS_WITH_MESSAGE(snowman(10114411), "got invalid N", "");
}


// getLeftEye
TEST_CASE("Good Left Eye code") {
    CHECK(nospaces(snowman(11114411)) == nospaces("_===_\n(.,.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(22214411)) == nospaces("  ___ \n .....\n(o..)\n( : )\n( : )"));
    CHECK(nospaces(snowman(33314411)) == nospaces("   _  \n  /_\\ \n(O_.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(44414411)) == nospaces("  ___ \n (_*_)\n(- .)\n( : )\n( : )"));  
}

TEST_CASE("Bad Left Eye code") {
    CHECK_THROWS(snowman(11514411));
    CHECK_THROWS(snowman(11014411));
    CHECK_THROWS_WITH_MESSAGE(snowman(11014411), "got invalid L", "");
}


// getRightEye
TEST_CASE("Good Right Eye code") {
    CHECK(nospaces(snowman(11114411)) == nospaces("_===_\n(.,.)\n( : )\n( : )"));
    CHECK(nospaces(snowman(22224411)) == nospaces("  ___ \n .....\n(o.o)\n( : )\n( : )"));
    CHECK(nospaces(snowman(33334411)) == nospaces("   _  \n  /_\\ \n(O_O)\n( : )\n( : )"));
    CHECK(nospaces(snowman(44444411)) == nospaces("  ___ \n (_*_)\n(- -)\n( : )\n( : )"));
}

TEST_CASE("Bad Right Eye code") {
    CHECK_THROWS(snowman(11154411));
    CHECK_THROWS(snowman(11104411));
    CHECK_THROWS_WITH_MESSAGE(snowman(11104411), "got invalid R", "");
}


// getLeftArm
TEST_CASE("Good Left Arm code") {
    CHECK(nospaces(snowman(11111411)) == nospaces("_===_\n(.,.)\n<( : )\n( : )"));
    CHECK(nospaces(snowman(22222411)) == nospaces("  ___ \n .....\n\\(o.o)\n( : )\n( : )"));
    CHECK(nospaces(snowman(33333411)) == nospaces("   _  \n  /_\\ \n(O_O)\n/( : )\n( : )"));
    CHECK(nospaces(snowman(44444411)) == nospaces("  ___ \n (_*_)\n(- -)\n( : )\n( : )"));  
}

TEST_CASE("Bad Left Arm code") {
    CHECK_THROWS(snowman(11115111));
    CHECK_THROWS(snowman(11110111));
    CHECK_THROWS_WITH_MESSAGE(snowman(11119111), "got invalid X", "");
}


// getRightArm
TEST_CASE("Good Right Arm code") {
    CHECK(nospaces(snowman(11111111)) == nospaces("_===_\n(.,.)\n<( : )>\n( : )"));
    CHECK(nospaces(snowman(22222211)) == nospaces("  ___ \n .....\n\\(o.o)/\n( : )\n( : )"));
    CHECK(nospaces(snowman(44444411)) == nospaces("  ___ \n (_*_)\n(- -)\n( : )\n( : )")); 
}

TEST_CASE("Bad Right Arm code") {
    CHECK_THROWS(snowman(11111511));
    CHECK_THROWS(snowman(11111011));
    CHECK_THROWS_WITH_MESSAGE(snowman(11111911), "got invalid Y", "");
}


// getTorso
TEST_CASE("Good Torso code") {
    CHECK(nospaces(snowman(11111111)) == nospaces("_===_\n(.,.)\n<( : )>\n( : )"));
    CHECK(nospaces(snowman(22222221)) == nospaces("  ___ \n .....\n\\(o.o)/\n(] [)\n( : )"));
    CHECK(nospaces(snowman(44444441)) == nospaces("  ___ \n (_*_)\n(- -)\n(   )\n( : )"));
}

TEST_CASE("Bad Torso code") {
    CHECK_THROWS(snowman(11111151));
    CHECK_THROWS(snowman(11111101));
    CHECK_THROWS_WITH_MESSAGE(snowman(11111191), "got invalid T", "");
}


// getBase
TEST_CASE("Good Base code") {
    CHECK(nospaces(snowman(11111111)) == nospaces("_===_\n(.,.)\n<( : )>\n( : )"));
    CHECK(nospaces(snowman(22222222)) == nospaces("  ___ \n .....\n\\(o.o)/\n(] [)\n(\" \")"));
    CHECK(nospaces(snowman(44444444)) == nospaces("  ___ \n (_*_)\n(- -)\n(   )\n(   )"));
}

TEST_CASE("Bad Base code") {
    CHECK_THROWS(snowman(11111115));
    CHECK_THROWS(snowman(11111110));
    CHECK_THROWS_WITH_MESSAGE(snowman(11111119), "got invalid B", "");
}
