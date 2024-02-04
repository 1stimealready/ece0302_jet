#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("Calling all public members", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);

}


TEST_CASE("Testing add functionality", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;

  REQUIRE(b.add(1));

  REQUIRE(b.contains(1));


  for (int i = 0; i < 101; i++) {

    b.add(1);

  }

  REQUIRE(b.add(1) == false);

  REQUIRE(b.getCurrentSize() == 100);

  REQUIRE(b.getFrequencyOf(1) == 100);

}

TEST_CASE("Test remove functionality", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;

  REQUIRE(b.remove(0) == false); 

  for (int i = 0; i < 100; i++) {

    b.add(i);

  }

  REQUIRE(b.remove(1));

  REQUIRE(b.getCurrentSize() == 99);

  REQUIRE(b.remove(1) == false);

}

TEST_CASE("Test remove functionality with multiples", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;

  for (int i = 0; i < 100; i++) {

    b.add(1);

  }

  REQUIRE(b.remove(1));

  REQUIRE(b.getCurrentSize() == 99);

}

TEST_CASE("Test isEmpty Function", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;

  REQUIRE(b.isEmpty());

  b.add(1);

  REQUIRE(b.isEmpty() == false);

  b.remove(1);

  REQUIRE(b.isEmpty());

}

TEST_CASE("Test getCurrentSize method", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;

  REQUIRE(b.getCurrentSize() == 0);

  for (int i = 0; i < 100 - 30; i++) {

    b.add(i);

  }

  REQUIRE(b.getCurrentSize() == 100 - 30);

  b.remove(1);

  REQUIRE(b.getCurrentSize() == 100 - 31);

}

TEST_CASE("Test clear method", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;

  for(int i = 0; i < 10; i++) {

    b.add(1);

  }

  b.clear();

  REQUIRE(b.getCurrentSize() == 0);

  REQUIRE(b.getFrequencyOf(1) == 0);

  REQUIRE(b.remove(1) == false);

}

TEST_CASE("Test getFrequencyOf Function", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;

  for (int i = 0; i < 10; i++) {

    b.add(1);

  }

  REQUIRE(b.getFrequencyOf(1) == 10);

  b.remove(1);

  REQUIRE(b.getFrequencyOf(1) == 9);

  REQUIRE(b.getFrequencyOf(2) == 0);

}

TEST_CASE("Test contains method", "[LimitedSizeBag]") {
  LimitedSizeBag<int> b;

  REQUIRE(b.contains(0) == false);

  for (int i = 0; i < 10; i++) {

    b.add(1);

  }

  REQUIRE(b.contains(1));

  REQUIRE(b.contains(2) == false);


}
