#include <iostream>
#include <string>
#include <vector>
#include "DES.hpp"
#include <unordered_map>
#include <bitset>
#include <math.h>
#include <time.h>
#include "Binary.hpp"

using namespace std;

std::string DES::expansion_ri(std::string input32bit)
{
	std::string str_temp = "";
	for(int i = 0; i < 48	/*The expansion of bits*/; i++)
		str_temp += input32bit[E_t[i] - 1];	// go through every bit position in table

	return str_temp;
}

std::vector<std::string> DES::key_sched_des(std::string key, char encOrdec){

	string key64 = key;
	string key56;
	string l_Key, r_Key;
	vector<string> mrgKey(16);
	vector<string> rndKey(16);

	for(int i = 0; i < 56; i++)
		key56 += key64[pc_1[i] - 1];

	// split key into left and right
	l_Key = key56.substr(0,28);
	r_Key = key56.substr(28,28);

	for(int i = 0; i < 16; i++){

		if( encOrdec == 'E'){
			l_Key = Binary::shiftbits(l_Key, num_leftShift[i], 'l');
			r_Key = Binary::shiftbits(r_Key, num_leftShift[i], 'l');
		} else
		{
			l_Key = Binary::shiftbits(l_Key, num_rightShift[i], 'r');
			r_Key = Binary::shiftbits(r_Key, num_rightShift[i], 'r');
		}

		mrgKey[i] = (l_Key + r_Key);

		for(int z = 0; z < 48; z++)
			rndKey[i] += mrgKey[i][pc_2[z] - 1];

	}
	return rndKey;
}

// F function that is done during each DES round
std::string DES::F(std::string subkey, std::string right_block)	//F function
{

	// expands incomning right block to 48 bits
	std::string expand = "";
	for(int i = 0; i < 48; i++)
		expand += right_block[E_t[i] - 1];

	std::string exceptOR;

	exceptOR = Binary::xOr(expand, subkey);	// XORS expanded right and current round subkey

	// take S box calculation by 6 bits at a time
	int z = 0;

	std::string comb_sbox = "";
	for(int i = 0; i < 48; i += 6)
	{

		std::string row_bits = "";
		std::string column_bits = "";

		row_bits = exceptOR[i];
		row_bits +=  exceptOR[i + 5];
		for(int j = i + 1; j < i + 5; j++)
			column_bits += exceptOR[j];

		// take bits and map to each S box
		int row = Binary::bit_to_dec(row_bits);
		int column = Binary::bit_to_dec(column_bits);

		int sbox = S[z][row][column];
		
		std::string sbox_bin = Binary::Dec_to_Bin(sbox);

		// need to combine sbox values and then use permutaiton
		comb_sbox += sbox_bin;

		z++;
	}

	std::string permutate;	// permutate the Sbox combination
	for(int i = 0; i < 32; i++)
		permutate += comb_sbox[P[i] - 1];

	return permutate;
}

// main function that encrypts plaintext
std::string DES::encrypt(std::string plain_txt, std::string key, char encOrdec)
{
	// set up keys
	std::vector<std::string> sub_strs;

	if(encOrdec == 'E'){
		sub_strs = key_sched_des(key, 'E');
	} else{
		sub_strs = key_sched_des(key, 'D');
	}


	// do inital permutations 
	std::string IP = "";
	for (int i = 0; i < 64; i++)
		IP += plain_txt[IP_t[i] - 1];

	std::string left, right;

	// stores bits into left and right 
	for(int i = 0; i < 32; i++)
		left += IP[i];
	for(int i = 32; i < 64; i++)
		right += IP[i];

	for(int i = 0; i < 16; i++)	//16 rounds of DES
	{

		std::string sub_key = "";

		sub_key = F(sub_strs[i], right);

		string x = right;

		right = Binary::xOr(left, sub_key);

		left = x;

		if (i != 15)
            swap(left, right);
	}
	
	//combine the std::strings of bits into one 64 bit block
	std::string combined = "";
	for(int i = 0; i < 32;i++)
		combined += right[i];
	
	for(int i = 0; i < 32;i++)
		combined += left[i];

	//do final permutation of block
	std::string final_perm = "";
	for(int i = 0; i < 64; i++)
		final_perm += combined[P_1[i] - 1];

	return final_perm;
}