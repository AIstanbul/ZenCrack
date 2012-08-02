/*
	This file is part of a dirty hashcracker.

    This software is free : you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this software.  If not, see <http://www.gnu.org/licenses/>.

	Author : Ganapati
	Date : 31/07/2012

	Infos :
	int type = hash type
	 | 0 : md5
	 | 1 : sha1
	 | 2 : sha256
	 | 3 : sha512
*/

using namespace std;

#include <cstring>
#include <openssl/evp.h>

//Hardcore const FTW !
const char hex2asciiU_value[256][2] = { {'0','0'},{'0','1'},{'0','2'},{'0','3'},{'0','4'},{'0','5'},{'0','6'},{'0','7'},{'0','8'},{'0','9'},{'0','a'},{'0','b'},{'0','c'},{'0','d'},{'0','e'},{'0','f'},{'1','0'},{'1','1'},{'1','2'},{'1','3'},{'1','4'},{'1','5'},{'1','6'},{'1','7'},{'1','8'},{'1','9'},{'1','a'},{'1','b'},{'1','c'},{'1','d'},{'1','e'},{'1','f'},{'2','0'},{'2','1'},{'2','2'},{'2','3'},{'2','4'},{'2','5'},{'2','6'},{'2','7'},{'2','8'},{'2','9'},{'2','a'},{'2','b'},{'2','c'},{'2','d'},{'2','e'},{'2','f'},{'3','0'},{'3','1'},{'3','2'},{'3','3'},{'3','4'},{'3','5'},{'3','6'},{'3','7'},{'3','8'},{'3','9'},{'3','a'},{'3','b'},{'3','c'},{'3','d'},{'3','e'},{'3','f'},{'4','0'},{'4','1'},{'4','2'},{'4','3'},{'4','4'},{'4','5'},{'4','6'},{'4','7'},{'4','8'},{'4','9'},{'4','a'},{'4','b'},{'4','c'},{'4','d'},{'4','e'},{'4','f'},{'5','0'},{'5','1'},{'5','2'},{'5','3'},{'5','4'},{'5','5'},{'5','6'},{'5','7'},{'5','8'},{'5','9'},{'5','a'},{'5','b'},{'5','c'},{'5','d'},{'5','e'},{'5','f'},{'6','0'},{'6','1'},{'6','2'},{'6','3'},{'6','4'},{'6','5'},{'6','6'},{'6','7'},{'6','8'},{'6','9'},{'6','a'},{'6','b'},{'6','c'},{'6','d'},{'6','e'},{'6','f'},{'7','0'},{'7','1'},{'7','2'},{'7','3'},{'7','4'},{'7','5'},{'7','6'},{'7','7'},{'7','8'},{'7','9'},{'7','a'},{'7','b'},{'7','c'},{'7','d'},{'7','e'},{'7','f'},{'8','0'},{'8','1'},{'8','2'},{'8','3'},{'8','4'},{'8','5'},{'8','6'},{'8','7'},{'8','8'},{'8','9'},{'8','a'},{'8','b'},{'8','c'},{'8','d'},{'8','e'},{'8','f'},{'9','0'},{'9','1'},{'9','2'},{'9','3'},{'9','4'},{'9','5'},{'9','6'},{'9','7'},{'9','8'},{'9','9'},{'9','a'},{'9','b'},{'9','c'},{'9','d'},{'9','e'},{'9','f'},{'a','0'},{'a','1'},{'a','2'},{'a','3'},{'a','4'},{'a','5'},{'a','6'},{'a','7'},{'a','8'},{'a','9'},{'a','a'},{'a','b'},{'a','c'},{'a','d'},{'a','e'},{'a','f'},{'b','0'},{'b','1'},{'b','2'},{'b','3'},{'b','4'},{'b','5'},{'b','6'},{'b','7'},{'b','8'},{'b','9'},{'b','a'},{'b','b'},{'b','c'},{'b','d'},{'b','e'},{'b','f'},{'c','0'},{'c','1'},{'c','2'},{'c','3'},{'c','4'},{'c','5'},{'c','6'},{'c','7'},{'c','8'},{'c','9'},{'c','a'},{'c','b'},{'c','c'},{'c','d'},{'c','e'},{'c','f'},{'d','0'},{'d','1'},{'d','2'},{'d','3'},{'d','4'},{'d','5'},{'d','6'},{'d','7'},{'d','8'},{'d','9'},{'d','a'},{'d','b'},{'d','c'},{'d','d'},{'d','e'},{'d','f'},{'e','0'},{'e','1'},{'e','2'},{'e','3'},{'e','4'},{'e','5'},{'e','6'},{'e','7'},{'e','8'},{'e','9'},{'e','a'},{'e','b'},{'e','c'},{'e','d'},{'e','e'},{'e','f'},{'f','0'},{'f','1'},{'f','2'},{'f','3'},{'f','4'},{'f','5'},{'f','6'},{'f','7'},{'f','8'},{'f','9'},{'f','a'},{'f','b'},{'f','c'},{'f','d'},{'f','e'},{'f','f'} };

class Hash {

	private : bool (Hash::*testingMethod)(string);
	private : string (Hash::*transformMethod)(string);

	public : Hash(int type = 0) {
		switch(type) {
			case 0:
				testingMethod   = &Hash::test_md5;
				transformMethod = &Hash::to_md5;
				break;
			case 1:
				testingMethod   = &Hash::test_sha1;
				transformMethod = &Hash::to_sha1;
				break;
			case 2:
				testingMethod   = &Hash::test_sha256;
				transformMethod = &Hash::to_sha256;
				break;
			case 3:
				testingMethod   = &Hash::test_sha512;
				transformMethod = &Hash::to_sha512;
				break;
		}

	}

	public : bool testHash(string input) {
		return (*this.*testingMethod)(input);
	}


	public : string getHash(string input) {
		return (*this.*transformMethod)(input);	
	}

	private : bool test_md5(string text) {
		string chars = "0123456789abcdef";
		if (text.length() == 32) {
			for (int i=0; i< text.length()-1; i++) {
				if (chars.find(text[i]) == string::npos) {
					return false;
				}		
			}
			return true;
		} else {
			return false;
		}
	}

	private : string to_md5( string text ){
		EVP_MD_CTX mdctx;
		unsigned char md_value[EVP_MAX_MD_SIZE];
		unsigned int md_len;

		EVP_DigestInit( &mdctx, EVP_md5() );
		EVP_DigestUpdate( &mdctx, text.c_str(), text.size() );
		EVP_DigestFinal_ex( &mdctx, md_value, &md_len );
		EVP_MD_CTX_cleanup( &mdctx );

		return digest_to_hex_string( md_value, md_len );
	}

	private : bool test_sha1(string text) {
		string chars = "0123456789abcdef";
		if (text.length() == 40) {
			for (int i=0; i< text.length()-1; i++) {
				if (chars.find(text[i]) == string::npos) {
					return false;
				}		
			}
			return true;
		} else {
			return false;
		}
	}

	private : string to_sha1( string text ){
		EVP_MD_CTX mdctx;
		unsigned char md_value[EVP_MAX_MD_SIZE];
		unsigned int md_len;

		EVP_DigestInit( &mdctx, EVP_sha1() );
		EVP_DigestUpdate( &mdctx, text.c_str(), text.size() );
		EVP_DigestFinal_ex( &mdctx, md_value, &md_len );
		EVP_MD_CTX_cleanup( &mdctx );

		return digest_to_hex_string( md_value, md_len );
	}

	private : bool test_sha256(string text) {
		string chars = "0123456789abcdef";
		if (text.length() == 64) {
			for (int i=0; i< text.length()-1; i++) {
				if (chars.find(text[i]) == string::npos) {
					return false;
				}		
			}
			return true;
		} else {
			return false;
		}
	}

	private : string to_sha256( string text ){
		EVP_MD_CTX mdctx;
		unsigned char md_value[EVP_MAX_MD_SIZE];
		unsigned int md_len;

		EVP_DigestInit( &mdctx, EVP_sha256() );
		EVP_DigestUpdate( &mdctx, text.c_str(), text.size() );
		EVP_DigestFinal_ex( &mdctx, md_value, &md_len );
		EVP_MD_CTX_cleanup( &mdctx );

		return digest_to_hex_string( md_value, md_len );
	}

	private : bool test_sha512(string text) {
		string chars = "0123456789abcdef";
		if (text.length() == 128) {
			for (int i=0; i< text.length()-1; i++) {
				if (chars.find(text[i]) == string::npos) {
					return false;
				}		
			}
			return true;
		} else {
			return false;
		}
	}

	private : string to_sha512( string text ){
		EVP_MD_CTX mdctx;
		unsigned char md_value[EVP_MAX_MD_SIZE];
		unsigned int md_len;

		EVP_DigestInit( &mdctx, EVP_sha512() );
		EVP_DigestUpdate( &mdctx, text.c_str(), text.size() );
		EVP_DigestFinal_ex( &mdctx, md_value, &md_len );
		EVP_MD_CTX_cleanup( &mdctx );

		return digest_to_hex_string( md_value, md_len );
	}

	private : string digest_to_hex_string( const unsigned char* _pArray, unsigned int _len )
	{
		string str;
		str.resize(_len*2);
		char* pszHex = &str[0];
		const unsigned char* pEnd = _pArray + _len;
		for( const unsigned char* pChar = _pArray; pChar != pEnd; pChar++, pszHex += 2 ) {
		    pszHex[0] = hex2asciiU_value[*pChar][0];
		    pszHex[1] = hex2asciiU_value[*pChar][1];
		}
		return str;
	}
};
