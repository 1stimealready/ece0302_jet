#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>
#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Calling all public members", "[DynamicBag]"){
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("Testing add with a variety of numbers", "[DynamicBag]") {

  DynamicBag<int> b;

  for (int i = 0; i < 100; i++) {

    b.add(i);

  }

  REQUIRE(b.getCurrentSize() == 100);

  b.add('c');

  b.add(-1);

  REQUIRE(b.add(0) == true);

}


TEST_CASE("Testing copy constructor", "[DynamicBag]") {

  DynamicBag<int> b;

  for (int i = 0; i < 10; i++) {

    b.add(i);

  }

  DynamicBag<int> copy_1;

  copy_1 = b;

  DynamicBag<int> copy_2(b);

  REQUIRE(b.getCurrentSize() == copy_1.getCurrentSize());

  REQUIRE(b.getCurrentSize() == copy_2.getCurrentSize());

  REQUIRE(copy_1.getFrequencyOf(1) == copy_2.getFrequencyOf(1));

}


TEST_CASE("Testing remove functionality", "[DynamicBag]") {

  DynamicBag<int> b;


  REQUIRE(b.remove(0) == false);

  b.add(1);

  REQUIRE(b.remove(0) == false);
  
  REQUIRE(b.remove(1) == true);

}

TEST_CASE("Test", "[DynamicBag]") {
  DynamicBag<int> b;

  for (int i = 0; i < 100; i++) {

    b.add(1);

  }

  REQUIRE(b.remove(1));

  REQUIRE(b.getCurrentSize() == 99);

}

TEST_CASE("Test isEmpty Function", "[DynamicBag]") {

  DynamicBag<int> b;

  REQUIRE(b.isEmpty() == true);

  b.add(1);

  REQUIRE(b.isEmpty() == false);

  b.remove(1);

  REQUIRE(b.isEmpty() == true);

}

TEST_CASE("Test getCurrentSize method", "[DynamicBag]") {

  DynamicBag<int> b;


  REQUIRE(b.getCurrentSize() == 0);

  for (int i = 0; i < 5; i++) { b.add(1); }

  REQUIRE(b.getCurrentSize() == 5);

  b.clear();

  REQUIRE(b.getCurrentSize() == 0);

}

TEST_CASE("Test clear functionality", "[DynamicBag]") {

  DynamicBag<int> b;

  for (int i = 0; i < 100; i++) {

    b.add(1);

  }

  b.clear();

  REQUIRE(b.getCurrentSize() == 0);

}

TEST_CASE("Test GetFrequency method", "[DynamicBag]") {

  DynamicBag<int> b;

  for (int i = 0; i < 5; i++) {

    b.add(10);

  }

  REQUIRE(b.getFrequencyOf(10) == 5);

  b.clear();

  REQUIRE(b.getFrequencyOf(10) == 0);

}

TEST_CASE("Test contains method", "[DynamicBag]") {

  DynamicBag<int> b;

  b.add(6);

  REQUIRE(b.contains(6) == true);

  REQUIRE(b.contains(10) == false);

}

TEST_CASE("Adding a max size integer to bag", "[DynamicBag]") {

  DynamicBag<int> b;

  b.add(INT_MAX);

  REQUIRE(b.getCurrentSize() == 1);

}

TEST_CASE("Bag with a type other than int", "[DynamicBag]") {

  DynamicBag<std::string> b;

  b.add("Hello World");

  REQUIRE(b.contains("Hello World") == true);






}
