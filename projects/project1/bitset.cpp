#include "bitset.hpp"

Bitset::Bitset() {
    // TODO - DONE
    bitArraySize = 8;

    bitArray = new uint8_t[bitArraySize];

    //Set new array to 0
    for (int i = 0; i < bitArraySize; i++) {

        *(bitArray + i) = 0; 

    }

    isValid = true;

}

Bitset::Bitset(intmax_t size_T) {
    // TODO - DONE
    
    bitArraySize = size_T;

    bitArray = new uint8_t[bitArraySize];

    for (int i = 0; i < bitArraySize; i++) {

        *(bitArray + i) = 0;

    }

    isValid = true;



}

Bitset::Bitset(const std::string & value) {
    // TODO - DONE
    bitArraySize = value.length();

    bitArray = new u_int8_t[bitArraySize];

    isValid = true; //Assume string is valid to start. If it is not, change that when we find that in the input string

    for (int i = 0; i < bitArraySize; i++) {

        if (value[i] == '0') {

            bitArray[i] = 0;

        } else if (value[i] == '1') {

            bitArray[i] = 1;

        } else {

            isValid = 0;

        }

    

    }

}

Bitset::~Bitset() {
    // TODO

    delete [] bitArray;


}

// TODO: other methods

//Returns the size of the bitset
intmax_t Bitset::size() const {

    return bitArraySize;

}

//Returns the validity of the bitset
bool Bitset::good() const {

    return isValid;

}

//Sets the index bit to 1, and if it is not a valid position instead invalidates the bitset
void Bitset::set(intmax_t index) {

    if (index >= 0 && index < bitArraySize && isValid) {

        bitArray[index] = 1;

    } else {

        isValid = false;

    }

}

//Sets the index bit to 0, and if it is not a valid position instead invalidates the bitset
void Bitset::reset(intmax_t index) {

    if (index >= 0 && index < bitArraySize && isValid) {

      bitArray[index] = 0;

    } else {

        isValid = false;

    }

}

//Toggles the index bit, and if it is not a valid position instead invalidates the bitset
void Bitset::toggle(intmax_t index) {

    if (index >= 0 && index < bitArraySize && isValid) {

      bitArray[index] = bitArray[index] != 1; //bitwise XOR to flip the bit

    } else {

        isValid = false;

    }

}

//Tests the value of a specific bit, and if the array is not valid or if the index is outside of bounds instead invalidate bitset
bool Bitset::test(intmax_t index) {

    if (index >= 0 && index < bitArraySize && isValid) {

      return bitArray[index];

    } else {

        isValid = false;

        return false;

    }

}

//Returns bitset as a string, notable does not check validity of array
//Returning an invalid string for troubleshooting seems useful
std::string Bitset::asString() const {

    std::string outputString = "";

    for (int i = 0; i < bitArraySize; i++) {

        if (bitArray[i] == 0) {
            outputString += '0';
        } else if (bitArray[i] == 1) {
            outputString += '1';
        } else {
            outputString += std::to_string(bitArray[i]);
        }

    }



    return outputString;

  }