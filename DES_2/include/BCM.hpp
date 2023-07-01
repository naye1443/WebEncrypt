#include "DES.hpp"

#ifndef _BCM_
#define _BCM_

class BCM: public DES {
    public:

    // Uses Base Des paraterized constructor
    BCM(std::string text, char encOrdec): DES(text, encOrdec){

    }

    void OFB(std::string text, std::string key, char encOrdec, int currBlock);

    std::string AuxOFB(std::string text, std::string key, char encOrder, int currBlock);

    std::string comtxt(char encOrdec);

};
#endif