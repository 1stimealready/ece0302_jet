#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"
#include "sort.hpp"
#include <string>

// write your test cases here
TEST_CASE("Test case", "sorting"){

  LinkedList<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 25);
  lst.insert(4, 11);

  LinkedList<int> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 4);
  REQUIRE(sorted.getEntry(1) == 10);
  REQUIRE(sorted.getEntry(2) == 11);
  REQUIRE(sorted.getEntry(3) == 25);
  REQUIRE(sorted.getEntry(4) == 100);
  
}

TEST_CASE("list with strings", "sorting"){

  LinkedList<std::string> lst;

  lst.insert(0, "E");
  lst.insert(1, "D");
  lst.insert(2, "C");
  lst.insert(3, "B");
  lst.insert(4, "A");

  LinkedList<std::string> sorted = sort(lst);

  REQUIRE(sorted.getEntry(0) == "A");
  REQUIRE(sorted.getEntry(1) == "B");
  REQUIRE(sorted.getEntry(2) == "C");
  REQUIRE(sorted.getEntry(3) == "D");
  REQUIRE(sorted.getEntry(4) == "E");
  



  
  
}

TEST_CASE("Test sort with char", "sorting"){

  LinkedList<char> lst;

  lst.insert(0, 'A');
  lst.insert(1, 'B');
  lst.insert(2, 'C');
  lst.insert(3, 'D');
  lst.insert(4, 'E');

  LinkedList<char> sorted = sort(lst);

  REQUIRE(sorted.getEntry(0) == 'A');
  REQUIRE(sorted.getEntry(1) == 'B');
  REQUIRE(sorted.getEntry(2) == 'C');
  REQUIRE(sorted.getEntry(3) == 'D');
  REQUIRE(sorted.getEntry(4) == 'E');
  
  
}

TEST_CASE("Test sort with doubles", "sorting"){

  LinkedList<double> lst;

  lst.insert(0, 1E10);
  lst.insert(1, 100);
  lst.insert(2, 1E-10);
  lst.insert(3, 0);
  lst.insert(4, -4000);

  LinkedList<double> sorted = sort(lst);

  REQUIRE(sorted.getEntry(0) == -4000);
  REQUIRE(sorted.getEntry(1) == 0);
  REQUIRE(sorted.getEntry(2) == 1E-10);
  REQUIRE(sorted.getEntry(3) == 100);
  REQUIRE(sorted.getEntry(4) == 1E10);
  
}

TEST_CASE("Test sort with random array of integers", "sorting"){

  LinkedList<int> lst;

  for (size_t i = 0; i < 100; i++) {

    lst.insert(i, rand());

  }

  LinkedList<int> sorted = sort(lst);

  int lastValue = sorted.getEntry(0);

  for (size_t i = 1; i < 100; i++) {

    REQUIRE(sorted.getEntry(i) >= lastValue);

    lastValue = sorted.getEntry(i);

  }
  
  
}