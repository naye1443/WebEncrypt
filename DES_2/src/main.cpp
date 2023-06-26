#include <iostream>
#include <string>
#include "DES.hpp"
#include <codecvt>
#include <time.h>

using namespace std;

int main(){


	DES prac;
	string key; //= "1010101010111011000010010001100000100111001101101100110011011101";
	string plaintxt; //= "0001001000110100010101101010101111001101000100110010010100110110";

	/******************* BEGININNG PROGRAMM ***********************/
	bool restart = true;
	while(restart){

		cout << "would you like to encrypt or decrypt your text?(E for encrypt, D for Decrypt) :";
		char encOrdec;
		cin >> encOrdec;
		cout << "********************************************\n";
	
		if(encOrdec == 'E')
		{
			cout << "please enter the text you would like to Encrypt:" << endl;
			cout << "********************************************\n";
			cin.ignore();
			string plain_txt;
			getline(cin, plain_txt);
			cout << "********************************************\n";
			cout << " A random 64 bit key is being generated ..." << endl;
			cout << "********************************************\n";

			// generate random 64 bit key
			//key = "1010101010111011000010010001100000100111001101101100110011011101";

			key = "";
			srand(time(NULL));
			while(key.length() < 64){
				key += prac.Dec_to_Bin(rand() % 100);	
			}

			while(key.length() > 64)	// while the key length is greater than 64
				key.erase(key.begin());	// gets rid of values at the end of string

		
			/****************** ENCRYPTION STARTS *************************/

			string txtBITS = prac.txttoBits(plain_txt); //112 bits
			cout << "Your input in plain bits is :" << txtBITS << endl;
			cout << "********************************************\n";


			if(txtBITS.size() % 64 != 0)
			{
				int morebits = 64 - (txtBITS.size() % 64);	// the ammount of padding needed for a full block
				for(int i = 0; i < morebits; i++)			// adds the extra zeros to block
					txtBITS += "0";
			}

			int numOfencrypts = txtBITS.size() / 64;

			int z = 0;
			string output_txt = "";
			for(int i = 0; i < numOfencrypts; i++)
			{
				string tmpstr = "";
				int tmp_const = z;
				for(int j = z; j < tmp_const + 64;j++)	// takes 64 bits of the value and stores into string to encrypt
				{
					tmpstr += txtBITS[j];
					z++;
				}
				output_txt += prac.encrypt(tmpstr, key, encOrdec);	// encrypts and appends to output
			}
			cout << "The output from encryption in Hexadecimal is :"<< prac.bin2hex(output_txt) << endl;
			cout << "********************************************\n";
			cout << "The key is :"  << prac.bin2hex(key) << " make sure you remember this key for decryption!" << endl;
			cout << "********************************************\n";
		}
		else if(encOrdec == 'D')
		{
			//ciphertxt:51782C2711400500
			//key:AABB09182736CCDD

			cout << "please enter the text you would like to Decrypt. (This value is Hexadecimal) :";
			cin.ignore();
			string cipher_txt;
			getline(cin, cipher_txt);
			cout << "********************************************\n";

			string userkey;
			cout << "please enter a decryption key in Hexadecimal. The value must equate to 64 bits! :";
			getline(cin, userkey);
			cout << "********************************************\n";

			//turn the hexadecimal key into bits
			string userkeybin = prac.hex2bin(userkey);

			string txtBITS = prac.hex2bin(cipher_txt); 
			cout << "Your input in plain bits is :" << txtBITS << endl;	//the bits should be divisable by 64
			cout << "********************************************\n";


			int numOfencrypts = txtBITS.size() / 64;

			int z = 0;
			string output_txt = "";
			for(int i = 0; i < numOfencrypts; i++)
			{
				string tmpstr = "";
				int tmp_const = z;
				for(int j = z; j < tmp_const + 64;j++)	// takes 64 bits of the value and stores into string to encrypt
				{
					tmpstr += txtBITS[j];
					z++;
				}
				output_txt += prac.encrypt(tmpstr, userkeybin, encOrdec);	// encrypts and appends to output
			}

			cout << "The output from decryption in bits is :"<< output_txt << endl;
			cout << "********************************************\n";
			cout << "The output from decryption in text is :"<< prac.hex2char(prac.bin2hex(output_txt)) << endl;
			cout << "********************************************\n";
		}
		char decision;
		cout << "would you like to encrypt/ decrypt again?( Y or N) :" << endl;
		cout << "********************************************\n";
		cin >> decision;
		cin.ignore();
		cout << "********************************************\n";

		if( decision == 'Y')
			restart = true;
		else
			restart = false;

	}

	return 0;
}

  