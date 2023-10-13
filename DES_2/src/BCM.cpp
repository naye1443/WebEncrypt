#include <string>
#include <iostream>
#include <vector>
#include "BCM.hpp"

#include "Binary.hpp"

/*
* Input: Plaintxt/Ciphertxt, 64 bit key, encrypt/Decrypt, currentBlock iteration
* Output: Void
* Description: 1st iteration takes 64 bit Initalization vector. iterations greater than 1
* Takes Encryption of previous block. The ciphertxt is created from XOR operation from output
* of encryption and Block 1 of Plaintxt.
*/
void BCM::OFB(std::string text, std::string key, char encOrdec, int currBlock){
	std::string output;

	// If first iteration
	if(currBlock == 0){
		std::string iv = "";

		srand(time(NULL));
		// Makes sure initalization vector is 64 bit block size
		while(iv.length() < 64)
			iv += Binary::Dec_to_Bin(rand() % 100);

		while(iv.length() > 64)	// while the key length is greater than 64
			iv.erase(iv.begin());	// gets rid of values at the end of std::string

		output = AuxOFB(iv, this->key, encOrdec, currBlock);
		OFB(output, this->key, encOrdec, ++currBlock);
	}else if(currBlock < Blocks){
		output = AuxOFB(text, this->key, encOrdec, currBlock);
		OFB(output, this->key, encOrdec, ++currBlock);
	}
	return;
}

/*
* Input: Either IV or previous encryption block, encryption key, encrypt/decrypt, current Plaintxt/ciphertxt block.
* Output: Encryption output.
* Description: Takes IV or previous encryption block and perform encryption/decryption.
* After push the output of encryption into cipherblock vector.
*/
std::string BCM::AuxOFB(std::string text, std::string key, char encOrdec, int currBlock){
	std::string output = encrypt(text, key, encOrdec);
	cipherBlock.push_back(Binary::xOr(output, PlainBlock[currBlock]));
	return output;
}

/*
* Input: Encryption/Decryption.
* Output: Combined ciphertxt blocks.
* Description: Combines all ciphertxt blocks.
*/
std::string BCM::comtxt(char encOrdec){
	std::string text = "";

	for(int i = 0; i < cipherBlock.size(); i++)
		text += cipherBlock[i];

	// Clears PlainBlocks/CipherBlocks and Block numbers
	PlainBlock.clear();
	cipherBlock.clear();
	Blocks = 0;
	return text;
}