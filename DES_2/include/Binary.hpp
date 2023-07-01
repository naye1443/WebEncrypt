#include <iostream>
#include <string>


#ifndef _Binary_
#define _Binary_

class Binary{

public:

    static std::string shiftbits(std::string bits, int n /* number of shifts*/, char dir);

    static std::string xOr(std::string s1, std::string s2);	// does XOR of two std::strings

    static int bit_to_dec(std::string num);    // converts bits into decimal numbers

    static std::string hex2bin(std::string s);	// hexadecimal to bin

    static std::string bin2hex(std::string s);	// binary to hexadecimal
    
    static std::string Dec_to_Bin(int n);		// decimal to binary

    static std::string txttoBits(std::string str);	// text char's to binary

    static std::string hex2char(std::string hex);	// hexadecimal to strings of characters

    static std::string hex2dec(std::string s); // Hexadecimal to decimal number

};

#endif