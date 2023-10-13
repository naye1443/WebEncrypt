#include "DES.hpp"
#include <time.h>
#include <iostream>

#ifndef _BCM_
#define _BCM_

class BCM: public DES {
    public:

    // Uses Base Des paraterized constructor
    // If key is empty, create a 64 bit key else set given key to
    BCM(std::string key , std::string text, char encOrdec): DES(text, encOrdec){
        if(key.empty()){
            srand(time(NULL));
            this->key = "";

            while(this->key.length() < 64)
                this->key += rand() % 1;     
        }else
            if(key.size() != 64)    // an exception could go here to catch incorrect key size
                
            this->key = key;
    }

    void OFB(std::string text, std::string key, char encOrdec, int currBlock);

    std::string AuxOFB(std::string text, std::string key, char encOrder, int currBlock);

    std::string comtxt(char encOrdec);

    std::string key;

};
#endif