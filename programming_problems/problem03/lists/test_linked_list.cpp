#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"
#include <string>

template class LinkedList<int>;

TEST_CASE( "Test default constructor", "[LinkedList]" ) {

  LinkedList<int> list;

  REQUIRE(list.getLength() == 0);

  REQUIRE(list.isEmpty());


}

TEST_CASE( "Test copy constructor", "[LinkedList]" ) {

  LinkedList<int> list;

  list.insert(0, 1);

  LinkedList<int> list1(list);

  REQUIRE(list1.getEntry(0) == 1);

  REQUIRE(list1.getLength() == 1);

  REQUIRE(list1.isEmpty() == false);


}

TEST_CASE( "Test = functionality", "[LinkedList]" ) {

  LinkedList<int> list;

  list.insert(0, 1);

  LinkedList<int> list1;

  list1 = list;

  REQUIRE(list1.getEntry(0) == 1);

  REQUIRE(list1.getLength() == 1);

  REQUIRE(list1.isEmpty() == false);

  list1.insert(0, 1);

  list = list1;

  REQUIRE(list.getLength() == 2);


}

TEST_CASE( "Test isEmpty", "[LinkedList]" ) {

  LinkedList<int> list;

  REQUIRE(list.isEmpty());

 list.insert(0 , 1);

 REQUIRE(list.isEmpty() == false);

}

TEST_CASE( "Test getLength", "[LinkedList]" ) {

  LinkedList<int> list;


  REQUIRE(list.getLength() == 0);

  list.insert(0, 1);
  list.insert(1, 1);
  list.insert(2, 1);

  REQUIRE(list.getLength() == 3);

  list.remove(2);

  REQUIRE(list.getLength() == 2);

}

TEST_CASE( "Test insert functionality", "[LinkedList]" ) {

  LinkedList<int> list;

  REQUIRE(list.insert(-1, 1) == false);

  REQUIRE(list.insert(1, 1) == false);

  REQUIRE(list.insert(0, 1));

  REQUIRE(list.insert(1, 1));

  REQUIRE(list.getLength() == 2);

  REQUIRE(list.insert(0, 10));

  REQUIRE(list.getEntry(0) == 10);

  REQUIRE(list.getLength() == 3);


}

TEST_CASE( "Test remove functionality", "[LinkedList]" ) {

  LinkedList<int> list;

  REQUIRE(list.remove(0) == false);

  list.insert(0, 4);
  list.insert(0, 3);
  list.insert(0, 2);
  list.insert(0, 1);

  REQUIRE(list.remove(0));

  REQUIRE(list.getLength() == 3);

  REQUIRE(list.remove(3) == false);

  REQUIRE(list.remove(2));

  REQUIRE(list.getLength() == 2);

  REQUIRE(list.remove(-1) == false);

  REQUIRE(list.remove(10) == false);

}

TEST_CASE( "Test clear functionality", "[LinkedList]" ) {

  LinkedList<int> list;

  for(int i = 0; i < 10; i++) {

    list.insert(i, i);

  }

  list.remove(3);

  list.clear();

  REQUIRE(list.getLength() == 0);

  REQUIRE(list.isEmpty());

}

TEST_CASE( "Test getEntry", "[LinkedList]" ) {

  LinkedList<int> list;

  REQUIRE(list.getEntry(0) == int());

  for(int i = 0; i < 10; i++) {

    list.insert(i, i);

  }

  REQUIRE(list.getEntry(0) == 0);

  REQUIRE(list.getEntry(3) == 3);



}

TEST_CASE( "Test setEntry", "[LinkedList]" ) {

  LinkedList<int> list;

  list.setEntry(0, 1);

  REQUIRE(list.isEmpty());

  REQUIRE(list.getLength() == 0);

  list.insert(0, 1);

  list.setEntry(0, 10);

  REQUIRE(list.getEntry(0) == 10);


}

TEST_CASE( "List with different type", "[LinkedList]") {

    LinkedList<std::string> list;

    list.insert(0, "Hello");
    list.insert(1, "World");

    REQUIRE(list.getEntry(0) == "Hello");

    REQUIRE(list.getEntry(1) == "World");

    list.clear();

    REQUIRE(list.getEntry(0) == "");


}

TEST_CASE( "All functions" , "[LinkedList]") {

    LinkedList<int> list;

    list.insert(0, 1);

    LinkedList<int> list1(list);

    REQUIRE(list1.getLength() == 1);

    list1.insert(0, 1);

    list = list1;

    REQUIRE(list.getLength() == 2);

    REQUIRE(list.remove(0));

    REQUIRE(list.getLength() == 1);

    list.setEntry(0, 100);

    REQUIRE(list.getEntry(0) == 100);

    for (int i = 0; i < 100; i++) {

        list.insert(0, i);

    }

    REQUIRE(list.getLength() == 101);

    list.clear();

    REQUIRE(list.isEmpty());
    


}