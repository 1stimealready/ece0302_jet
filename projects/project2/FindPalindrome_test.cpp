#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"
// There should be at least one test per FindPalindrome method

TEST_CASE( "Test adding a non-allowable word", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE("test recursion", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AAA"));
	REQUIRE(b.number() == 6);
}

TEST_CASE("Test number method", "[FindPalindrome]") {

	FindPalindrome b;

	b.add("a");
	b.add("Aa");
	b.add("AaA");

	REQUIRE(b.number() == 6);

}

TEST_CASE("Test with invalid string vector", "[FindPalindrome]") {

	FindPalindrome b;

	std::vector<std::string> invalidVector = { "1" , "!" };

	REQUIRE(!b.add(invalidVector));

	REQUIRE(b.number() == 0);

}

TEST_CASE("Test clear method", "[FindPalindrome]") {

	FindPalindrome b;

	b.add("BaB");
	b.add("AAA");
	b.add("aaA");

	b.clear();

	REQUIRE(b.number() == 0);

	REQUIRE(b.toVector() == std::vector<std::vector<std::string>>());

}

TEST_CASE("Test add method", "[FindPalindrome]") {

	FindPalindrome b;

	REQUIRE(b.add("A"));
	REQUIRE(b.number() == 1);

	REQUIRE(!b.add("1Asv"));

	REQUIRE(b.add("AB"));

	REQUIRE(b.number() == 1);

}

TEST_CASE("Test add vector method", "[FindPalindrome]") {

	FindPalindrome b;

	std::vector<std::string> validVector = { "A", "AA", "AAA" };

	REQUIRE(b.add(validVector));

	REQUIRE(b.number() == 6);

	REQUIRE(b.toVector().size() == 6);

	std::vector<std::string> invalidVector = { "A", "AA", "AAA", "1AS" };

	REQUIRE(b.add(invalidVector) == false);

	REQUIRE(b.number() == 6);

}

TEST_CASE("Test cutTest1 method", "[FindPalindrome]") {

	FindPalindrome b;

	std::vector<std::string> wordArray = {"A", "B"};

	REQUIRE(!b.cutTest1(wordArray));

	wordArray = {"A", "A"};

	REQUIRE(b.cutTest1(wordArray));

	wordArray = {"A", "A", "B", "CC"};

	REQUIRE(b.cutTest1(wordArray));



}

TEST_CASE("Test cutTest2 method", "[FindPalindrome]") {

	FindPalindrome b;

	std::vector<std::string> wordArray1 = {"A", "A"};

	std::vector<std::string> wordArray2 = {"A", "A", "A"};

	REQUIRE(b.cutTest2(wordArray1, wordArray2));

	wordArray1 = {"B", "A"};

	wordArray2 = {"A", "A", "A"};

	REQUIRE(!b.cutTest2(wordArray1, wordArray2));

	wordArray1 = {"A", "B"};

	wordArray2 = {"A", "A", "A"};

	REQUIRE(!b.cutTest2(wordArray1, wordArray2));
	



}

TEST_CASE("Test toVector method", "[FindPalindrome]") {

	FindPalindrome b;

	b.add("A");
	b.add("Ba");

	std::vector<std::vector<std::string>> solutionVector = { { "A", "Ba" }};

	REQUIRE(b.toVector() == solutionVector);

}

TEST_CASE("Test toVector method with more elements", "[FindPalindrome]") {

	FindPalindrome b;

	b.add("A");
	b.add("Aa");
	b.add("aAa");

	REQUIRE(b.toVector().size() == 6);

}

TEST_CASE("Test findPalindrome with larger Array method", "[FindPalindrome]") {

	FindPalindrome b;

	std::vector<std::string> vectorToAdd = {"A", "AA", "AAA", "AAAA", "AAAAA" };

	b.add(vectorToAdd);

	REQUIRE(b.number() == 120);



}


TEST_CASE("Verify can't add element already in array", "[FindPalindrome]") {

	FindPalindrome b;

	std::vector<std::string> vectorToAdd = {"A", "a"};

	REQUIRE(!b.add(vectorToAdd));



}

TEST_CASE("Verify can't add vector with elements already in array", "[FindPalindrome]") {

	FindPalindrome b;

	std::vector<std::string> vectorToAdd = {"A", "B"};

	REQUIRE(b.add(vectorToAdd));

	vectorToAdd = { "a", "G" };

	REQUIRE(!b.add(vectorToAdd));



}

TEST_CASE("Addind a string with a different capitalization", "[FindPalindrome]") {

	FindPalindrome b;

	b.add("A");

	REQUIRE(!b.add("a"));





}
