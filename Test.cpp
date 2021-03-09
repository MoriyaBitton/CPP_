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
}

TEST_CASE("Bad snowman code") {
    int negative = -7;
    CHECK_THROWS(snowman(5));
    CHECK_THROWS(snowman(11114410));
    CHECK_THROWS(snowman(91114411));
    CHECK_THROWS(snowman(negative));
    CHECK_THROWS(snowman((int)0.590));
    CHECK_THROWS(snowman(111));
    CHECK_THROWS(snowman(0));
}


// getHat
TEST_CASE("Good getHat code") {
    CHECK(getHat(11114411) == " _===_ ");
    CHECK(getHat(21114411) == "  ___ \n .....");
    CHECK(getHat(31114411) == "   _  \n  /_\\ ");
    CHECK(getHat(41114411) == "  ___ \n (_*_)");
}

TEST_CASE("Bad getHat code") {
    CHECK_THROWS(getHat(51114411));
    CHECK_THROWS(getHat(01114411));
    CHECK_THROWS(getHat(1114411));
}


// getNoseMouth
TEST_CASE("Good getNoseMouth code") {
    CHECK(getNoseMouth(11114411) == ",");
    CHECK(getNoseMouth(22114411) == ".");
    CHECK(getNoseMouth(33114411) == "_");
    CHECK(getNoseMouth(44114411) == " ");

}

TEST_CASE("Bad getNoseMouth code") {
    CHECK_THROWS(getNoseMouth(15114411));
    CHECK_THROWS(getNoseMouth(10114411));
    CHECK_THROWS(getNoseMouth(114411));

}


// getLeftEye
TEST_CASE("Good getLeftEye code") {
    CHECK(getLeftEye(11114411) == ".");
    CHECK(getLeftEye(21214411) == "o");
    CHECK(getLeftEye(31314411) == "O");
    CHECK(getLeftEye(41414411) == "-");
}

TEST_CASE("Bad getLeftEye code") {
    CHECK_THROWS(getLeftEye(11514411));
    CHECK_THROWS(getLeftEye(11014411));
    CHECK_THROWS(getLeftEye(14411));
}


// getRightEye
TEST_CASE("Good getRightEye code") {
    CHECK(getRightEye(11114411) == ".");
    CHECK(getRightEye(21224411) == "o");
    CHECK(getRightEye(31334411) == "O");
    CHECK(getRightEye(41444411) == "-");
}

TEST_CASE("Bad getRightEye code") {
    CHECK_THROWS(getRightEye(11154411));
    CHECK_THROWS(getRightEye(11104411));
    CHECK_THROWS(getRightEye(4411));
}


// getLeftArm
TEST_CASE("Good getLeftArm code") {
    CHECK(getLeftArm(11111411) == " ");
    CHECK(getLeftArm(21112411) == "\\");
    CHECK(getLeftArm(31113411) == "/");
    CHECK(getLeftArm(41114411) == " ");
}

TEST_CASE("Bad getLeftArm code") {
    CHECK_THROWS(getLeftArm(51115411));
    CHECK_THROWS(getLeftArm(01110411));
    CHECK_THROWS(getLeftArm(411));
}


// getLeftArm_low
TEST_CASE("Good getLeftArm_low code") {
    CHECK(getLeftArm_low(11111411) == "<");
    CHECK(getLeftArm_low(21112411) == " ");
    CHECK(getLeftArm_low(31113411) == " ");
    CHECK(getLeftArm_low(41114411) == " ");
}

TEST_CASE("Bad getLeftArm_low code") {
    CHECK_THROWS(getLeftArm_low(51115411));
    CHECK_THROWS(getLeftArm_low(01110411));
    CHECK_THROWS(getLeftArm_low(411));
}


// getRightArm
TEST_CASE("Good getRightArm code") {
    CHECK(getRightArm(11111111) == " ");
    CHECK(getRightArm(21112211) == "/");
    CHECK(getRightArm(31113311) == "\\");
    CHECK(getRightArm(41114411) == " ");
}

TEST_CASE("Bad getRightArm code") {
    CHECK_THROWS(getRightArm(51115511));
    CHECK_THROWS(getRightArm(01110011));
    CHECK_THROWS(getRightArm(11));
}


// getRightArm_low
TEST_CASE("Good getRightArm_low code") {
    CHECK(getRightArm_low(11111111) == ">");
    CHECK(getRightArm_low(21112211) == " ");
    CHECK(getRightArm_low(31113311) == " ");
    CHECK(getRightArm_low(41114411) == " ");
}

TEST_CASE("Bad getRightArm_low code") {
    CHECK_THROWS(getRightArm_low(51115511));
    CHECK_THROWS(getRightArm_low(01110011));
    CHECK_THROWS(getRightArm_low(11));
}


// getTorso
TEST_CASE("Good getTorso code") {
    CHECK(getTorso(11114411) == " : ");
    CHECK(getTorso(21114421) == "] [");
    CHECK(getTorso(31114431) == "> <");
    CHECK(getTorso(41114441) == "   ");
}

TEST_CASE("Bad getTorso code") {
    CHECK_THROWS(getTorso(51114451));
    CHECK_THROWS(getTorso(11114461));
    CHECK_THROWS(getTorso(1));
}


// getBase
TEST_CASE("Good getBase code") {
    CHECK(getBase(11114411) == " : ");
    CHECK(getBase(21114412) == "\" \"");
    CHECK(getBase(31114413) == "___");
    CHECK(getBase(41114414) == "   ");
}

TEST_CASE("Bad getBase code") {
    CHECK_THROWS(getBase(51114415));
    CHECK_THROWS(getBase(01114417));
}
