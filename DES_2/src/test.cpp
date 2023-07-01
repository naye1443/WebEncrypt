/*
This test the Output feedback mode functionality
*/

#include <iostream>
#include <string>
#include "DES.hpp"
#include "BCM.hpp"
#include <codecvt>
#include <time.h>

#include <Binary.hpp>

using namespace std;

int main(){
    //DES prac("This is the best sentence in existence. We are going to make this test best sentence.", 'E');
    BCM prac2("This is not the best sentence in existence so don't say it is", 'E');

    string key = "";
    srand(time(NULL));
    while(key.length() < 64){
        key += Binary::Dec_to_Bin(rand() % 100);	
    }

    while(key.length() > 64)	// while the key length is greater than 64
        key.erase(key.begin());	// gets rid of values at the end of string

    //prac.OFB("This is the best sentence in existence. We are going to maek this test best sentence.", key, 'E', 0);
    prac2.OFB("This is not the best sentence in existence so don't say it is", key, 'E', 0);

    std::string ciphertxt = Binary::bin2hex(prac2.comtxt('E'));
    std::cout << "The encrypted value is " << ciphertxt << std::endl;

    //DES prac1(ciphertxt, 'D');
    BCM prac1(ciphertxt, 'D');

    prac1.OFB(ciphertxt, key, 'D', 0);
    
    std::string plaintxt = Binary::hex2char(Binary::bin2hex(prac1.comtxt('D')));

    std::cout << "The decrypted value is " << plaintxt << std::endl;

    return 0;
}