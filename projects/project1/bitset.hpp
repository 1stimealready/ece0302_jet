#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>

class Bitset{
public:

  // TODO COMMENT - DONE
  /**
   * Default constructor assumes size = 8, prewrites all 0s
  */
  Bitset();

  // TODO COMMENT - DONE
  /**
   * Constructor takes an input size and fills bitArray with 0s
   * 
   * @param size_T intmax_t integer that decides the size of the bitArray
  */
  Bitset(intmax_t size_T);

  // TODO COMMENT - DONE
  /**
   * Creates a bitarray that is a copy of the input string
   * 
   * @param value string in format: "001001", "1111001". 
  */
  Bitset(const std::string & value);

  // TODO COMMENT - DONE
  /**
   * Deletes dynamically allocated bitArray
  */
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  // TODO COMMENT
  /**
   * Returns the length of the bitset
   * @returns size as an intmax_t
   * 
   * 
   * 
  */
  intmax_t size() const;

  // TODO COMMENT
  /**
   * returns the validity of the bitset
   * 
   * A few things control the validity
   * -Trying to access an object outside of the array invalidates the bitset
   * -Inputing a string with values other than 1 or 0 invalidates the bitset
   * 
   * @returns A bool variable that is true for valid, or false for invalid
  */
  bool good() const;

  // TODO COMMENT
  /**
   * Sets the indexed bit of the bitset to 1
   * invalidates the array if index is out of bounds, and does not function if the array is already invalid
   * 
   * @param index integer that determines the location to set
   * 
  */
  void set(intmax_t index);

  // TODO COMMENT
  /**
   * Sets the indexed bit of the bitset to 0
   * invalidates the array if index is out of bounds, and does not function if the array is already invalid
   * 
   * @param index integer that determines the location to reset
  */
  void reset(intmax_t index);

  // TODO COMMENT
  /**
   * 
   * Toggles the indexed bit of the bitset
   * invalidates the array if index is out of bounds, and does not function if the array is already invalid
   * 
   * @param index integer that determines the location to toggle
   * 
  */
  void toggle(intmax_t index);

  // TODO COMMENT
  /**
   * Returns the value of the bit at the given index
   * 
   * @param index integer that determines the location to test
   * 
   * @returns the bool value of the indexed bit
   * 
  */
  bool test(intmax_t index);

  // TODO COMMENT
  /**
   * Converts the bitset into a returnable string array
   * 
   * @returns string that represents the bitset
  */
  std::string asString() const;

private:
  // TODO - DONE

  //pointer to bitArray created dynamically
  uint8_t * bitArray;

  //int to store size of array
  intmax_t bitArraySize;

  //if true, bitSet is only 1s and 0s. If false, it contains different integers.
  bool isValid;


};

#endif
