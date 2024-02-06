#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE( "Test default constructor", "[ArrayList]" ) {

  ArrayList<int> list;

  REQUIRE(list.getLength() == 0);

  REQUIRE(list.isEmpty());


}

TEST_CASE( "Test copy constructor", "[ArrayList]" ) {

  ArrayList<int> list;

  list.insert(0, 1);

  ArrayList<int> list1(list);

  REQUIRE(list1.getEntry(0) == 1);

  REQUIRE(list1.getLength() == 1);

  REQUIRE(list1.isEmpty() == false);


}

TEST_CASE( "Test = functionality", "[ArrayList]" ) {

  ArrayList<int> list;

  list.insert(0, 1);

  ArrayList<int> list1;

  list1 = list;

  REQUIRE(list1.getEntry(0) == 1);

  REQUIRE(list1.getLength() == 1);

  REQUIRE(list1.isEmpty() == false);


}

TEST_CASE( "Test isEmpty", "[ArrayList]" ) {

  ArrayList<int> list;

  REQUIRE(list.isEmpty());

 list.insert(0 , 1);

 REQUIRE(list.isEmpty() == false);

}

TEST_CASE( "Test getLength", "[ArrayList]" ) {

  ArrayList<int> list;


  REQUIRE(list.getLength() == 0);

  list.insert(0, 1);
  list.insert(0, 1);
  list.insert(0, 1);

  REQUIRE(list.getLength() == 3);

  list.remove(2);

  REQUIRE(list.getLength() == 2);

}

TEST_CASE( "Test insert functionality", "[ArrayList]" ) {

  ArrayList<int> list;

  REQUIRE(list.insert(-1, 1) == false);

  REQUIRE(list.insert(1, 1) == false);

  REQUIRE(list.insert(0, 1));

  REQUIRE(list.insert(1, 1));

  REQUIRE(list.getLength() == 2);


}

TEST_CASE( "Test remove functionality", "[ArrayList]" ) {

  ArrayList<int> list;

  REQUIRE(list.remove(0) == false);

  list.insert(0, 1);

  REQUIRE(list.remove(0));

  REQUIRE(list.getLength() == 0);

  REQUIRE(list.remove(-1) == false);

  REQUIRE(list.remove(10) == false);

}

TEST_CASE( "Test clear functionality", "[ArrayList]" ) {

  ArrayList<int> list;

  for(int i = 0; i < 10; i++) {

    list.insert(i, i);

  }

  list.clear();

  REQUIRE(list.getLength() == 0);

  REQUIRE(list.isEmpty());

}

TEST_CASE( "Test getEntry", "[ArrayList]" ) {

  ArrayList<int> list;

  REQUIRE(list.getEntry(0) == int());

  for(int i = 0; i < 10; i++) {

    list.insert(i, i);

  }

  REQUIRE(list.getEntry(0) == 0);

  REQUIRE(list.getEntry(3) == 3);



}

TEST_CASE( "Test setEntry", "[ArrayList]" ) {

  ArrayList<int> list;

  list.setEntry(0, 1);

  REQUIRE(list.isEmpty());

  REQUIRE(list.getLength() == 0);

  list.insert(0, 1);

  list.setEntry(0, 10);

  REQUIRE(list.getEntry(0) == 10);


}
