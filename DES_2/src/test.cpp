/*
This test the Output feedback mode functionality
*/

#include <iostream>
#include <string>
#include "DES.hpp"
#include <codecvt>
#include <time.h>

using namespace std;

int main(){
    DES prac("This is the best sentence in existence. We are going to make this test best sentence.", 'E');

    string key = "";
    srand(time(NULL));
    while(key.length() < 64){
        key += prac.Dec_to_Bin(rand() % 100);	
    }

    while(key.length() > 64)	// while the key length is greater than 64
        key.erase(key.begin());	// gets rid of values at the end of string

    prac.OFB("This is the best sentence in existence. We are going to maek this test best sentence.", key, 'E', 0);

    std::string ciphertxt = prac.bin2hex(prac.comtxt('E'));
    std::cout << "The encrypted value is " << ciphertxt << std::endl;

    DES prac1(ciphertxt, 'D');

    prac1.OFB(ciphertxt, key, 'D', 0);
    
    std::string plaintxt = prac1.hex2char(prac1.bin2hex(prac1.comtxt('D')));

    std::cout << "The decrypted value is " << plaintxt << std::endl;

    return 0;
}