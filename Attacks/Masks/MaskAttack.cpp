/*
	This file is part of ZenCracker.

    This software is free : you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ZenCracker is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this software.  If not, see <http://www.gnu.org/licenses/>.

	Author : Ganapati
	Date : 04/08/2012
*/

using namespace std;

#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <omp.h>

class MaskAttack {

	// Attributes
	private : unordered_map<string, bool> hashlist;
	private : Hash hash;
	private : vector<string> charset;
	private : vector<int> charsetindexes;
	private : InputCleaner cleaner;

	// Setters
	public : void setHashlist(string hashFileName) {
		cout << "## Start processing hashlist" << endl;
		hashlist = cleaner.cleanHashList(hashFileName);
		cout << "## Done" << endl;
	}

	public : void setMask(string mask) {

		string numeric   = "0123456789";
		string lowercase = "abcdefghijklmnopqrstuvwxyz";
		string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		string special   = "!#$%&'()*+,-./:;?@[\\]^_`{|}~";

		for (int i=0;i<mask.length(); i++) {
			if (mask[i] == 'd') {
				charset.push_back(numeric);
			} else if (mask[i] == 'l') {
				charset.push_back(lowercase);
			} else if (mask[i] == 'u') {
				charset.push_back(uppercase);
			} else if (mask[i] == 's') {
				charset.push_back(special);
			}
			charsetindexes.push_back(0);
		}
	}

	// Methods
	public : void run() {
		clock_t start, finish; 
		cout << "## Run Mask attack :" << endl;
		unordered_map<string, bool> hashlistShared = hashlist;
		vector<string> resultlist;
		start = clock(); 
		//initialize word
		char * word = new char[charset.size()];
		for (int i=0;i<charset.size(); i++) {
			word[i] = charset[i][0];
		}
		bool end = false;

		// DO MAGIC HERE
		while(!end) {

			string hashstr = hash.getHash(word);
			if (hashlistShared[hashstr]) {
				cout << hashstr << ":" << word << endl;
				hashlistShared.erase(hashstr);
			}

			//check end 
			end = true;
			for (int i=0;i<charset.size(); i++) {		
				if (word[i] != charset[i][charset[i].size()-1]) {
					end = false;				
				}
			}
			
			if (word[0] == charset[0][charset[0].size()-1]) {
				cascade(word);
				charsetindexes[0] = 0;
				word[0] = charset[0][0];
			} else {
				charsetindexes[0] = charsetindexes[0]+1;
				word[0] = charset[0][charsetindexes[0]];
			}
						
		}
		// END MAGIC

		finish = clock(); 
		
		// Display stats
		cout << "--------------------------------" << endl;
		double duration = (double)(finish - start) / CLOCKS_PER_SEC; 
		cout << "## Total time : " << duration << " sec." << endl;
	}

	private : void cascade(char * word) {
		for (int i=0;i<charset.size(); i++) {
			if (word[i] == charset[i][charset[i].size()-1]) {
				if ( i < charset.size()-1) {
					next(word, i+1);
				}
			}
		}
	}

	private : void next(char * word, int i) {
		if (word[i] == charset[i][charset[i].size()-1]) {
			word[i] = charset[i][0];
			charsetindexes[i] = 0;
		} else {
			charsetindexes[i] = charsetindexes[i]+1;
			word[i] = charset[i][charsetindexes[i]];
		}
	}
	/*
	* Set hash type
	*/

	public : void setHashType(Hash & ahash) {
		hash = ahash;
		cleaner.setHash(hash);
	}
};
