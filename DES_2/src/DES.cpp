#include <iostream>
#include <string>
#include <vector>
#include "DES.hpp"
#include <unordered_map>
#include <sstream>
#include <bitset>
#include <math.h>
#include <time.h>

using namespace std;

int DES::bit_to_dec(std::string num)
{
	int temp = static_cast<int>(std::bitset<32>(num).to_ulong());
	return temp;
}

std::string DES::shiftbits(std::string bits, int n, char dir)
{
	std::string temp = "";

	if(dir =='l')	// shift to left
	{
		for(std::size_t i = n; i < bits.size();i++)	// prints bits from n to length of std::string
			temp += bits[i];

		for(std::size_t i = 0; i < n;i++)	// then prints from 0 to n
			temp += bits[i];

	} else //shift to the right
	{
        int x = bits.length() - n;

        string temp_str = bits;
        reverse(temp_str.begin(), temp_str.begin()+x);
        reverse(temp_str.begin()+x, temp_str.end());
        reverse(temp_str.begin(), temp_str.end());

		temp = temp_str;

	}
	return temp;
}

std::string DES::xOr(std::string x1, std::string x2)
{
	std::string Xor = "";
	int bigest = std::max(x1.size(), x2.size());

	for(int i = 0; i < bigest; i++){
		if(x1[i] == x2[i])
			Xor += "0";
		else
			Xor += "1";
	}
	return Xor;
}

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
			l_Key = shiftbits(l_Key, num_leftShift[i], 'l');
			r_Key = shiftbits(r_Key, num_leftShift[i], 'l');
		} else
		{
			l_Key = shiftbits(l_Key, num_rightShift[i], 'r');
			r_Key = shiftbits(r_Key, num_rightShift[i], 'r');
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

	exceptOR = xOr(expand, subkey);	// XORS expanded right and current round subkey

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
		int row = bit_to_dec(row_bits);
		int column = bit_to_dec(column_bits);

		int sbox = S[z][row][column];
		
		std::string sbox_bin = Dec_to_Bin(sbox);

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

		right = xOr(left, sub_key);

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


string DES::hex2bin(string s)
{
    // hexadecimal to binary conversion
    unordered_map<char, string> mp;
    mp['0'] = "0000";
    mp['1'] = "0001";
    mp['2'] = "0010";
    mp['3'] = "0011";
    mp['4'] = "0100";
    mp['5'] = "0101";
    mp['6'] = "0110";
    mp['7'] = "0111";
    mp['8'] = "1000";
    mp['9'] = "1001";
    mp['A'] = "1010";
    mp['B'] = "1011";
    mp['C'] = "1100";
    mp['D'] = "1101";
    mp['E'] = "1110";
    mp['F'] = "1111";
    string bin = "";
    for (int i = 0; i < s.size(); i++) {
        bin += mp[s[i]];
    }
    return bin;
}
string DES::bin2hex(string s)
{
    // binary to hexadecimal conversion
    unordered_map<string, string> mp;
    mp["0000"] = "0";
    mp["0001"] = "1";
    mp["0010"] = "2";
    mp["0011"] = "3";
    mp["0100"] = "4";
    mp["0101"] = "5";
    mp["0110"] = "6";
    mp["0111"] = "7";
    mp["1000"] = "8";
    mp["1001"] = "9";
    mp["1010"] = "A";
    mp["1011"] = "B";
    mp["1100"] = "C";
    mp["1101"] = "D";
    mp["1110"] = "E";
    mp["1111"] = "F";
    string hex = "";
    for (int i = 0; i < s.length(); i += 4) {
        string ch = "";
        ch += s[i];
        ch += s[i + 1];
        ch += s[i + 2];
        ch += s[i + 3];
        hex += mp[ch];
    }
    return hex;
}

string DES::hex2dec(string s){

	// hexadecimal to decimal conversion
    unordered_map<char, string> mp;
    mp['0'] = "0";
    mp['1'] = "1";
    mp['2'] = "2";
    mp['3'] = "3";
    mp['4'] = "4";
    mp['5'] = "5";
    mp['6'] = "6";
    mp['7'] = "7";
    mp['8'] = "8";
    mp['9'] = "9";
    mp['A'] = "10";
    mp['B'] = "11";
    mp['C'] = "12";
    mp['D'] = "13";
    mp['E'] = "14";
    mp['F'] = "15";
	string dec = "";
	for(int i = 0; i < s.length(); i++){
		dec += mp[s[i]];
	}

	return dec;
}

std::string DES::Dec_to_Bin(int n)
{

	std::string binary = "";
	while(n > 0)
	{
	    std::string temp;
	    std::stringstream tmp;
	    tmp << (n % 2);
	    tmp >> temp;
		binary = temp + binary;
		n /= 2;
	}
	while(binary.size() < 4)
		binary = '0' + binary;

	//with encryption, the Dec to binary does not work, when getting rid of the 0 in front
	return binary;
}

string DES::txttoBits(string str)
{
	string bin = "";
	for (size_t i = 0; i < str.size(); ++i)
		bin += bitset<8>(str.c_str()[i]).to_string();

	return bin;
}

string DES::hex2char(string hex){
	// loop untill the end of the hex string

	if( hex.size() % 2 != 0){	// if hex value is not even, add a 0 to the front of it
		string temp = "0";
		temp += hex;
		hex = temp;
	}

	string valuestring = "";
	for(size_t i = 0; i < hex.size(); i += 2){

		// first take the first two hexadecimal numbers and convert to base 16
		string duo = hex.substr(i, 2);

		//change the values back into decimal and then typecase to character
		char temp = (char) (int)stoi(duo, NULL, 16);

		valuestring += temp;
	}	

	return valuestring;
}