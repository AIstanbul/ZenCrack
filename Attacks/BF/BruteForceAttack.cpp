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
#include "BFGen.cpp"

class BruteForceAttack {

	// Attributes
	private : unordered_map<string, bool> hashlist;
	private : Hash hash;
	private : char *buff;
	private : int min, max;
	private : int charsetlength;
	private : InputCleaner cleaner;

	// Setters
	public : void setHashlist(string hashFileName) {
		cout << "## Start processing hashlist" << endl;
		hashlist = cleaner.cleanHashList(hashFileName);
		cout << "## Done" << endl;
	}

	public : void setCharset(string charset) {
		
		charsetlength = charset.length();
		buff = new char[charset.length()];
		for (int i=0;i<charset.length(); i++)
			 buff[i] = charset[i];
	}

	public : void setRange(int amin, int amax) {
		min = amin;
		max = amax;
	}

	// Methods
	public : void run() {
		clock_t start, finish; 
		cout << "## Run Bruteforce attack :" << endl;
		unordered_map<string, bool> hashlistShared = hashlist;
		vector<string> resultlist;
		start = clock(); 
		
		// DO MAGIC HERE
		BFGen bg(buff,min,max);
		while(bg.getStr(buff)==0){
			string hashstr = hash.getHash(buff);
			if (hashlistShared[hashstr]) {
					cout << hashstr << ":" << buff << endl;
					hashlistShared.erase(hashstr);
				}
		}
		// END MAGIC

		finish = clock(); 
		
		// Display stats
		cout << "--------------------------------" << endl;
		double duration = (double)(finish - start) / CLOCKS_PER_SEC; 
		cout << "## Total time : " << duration << " sec." << endl;
		duration = (duration == 0) ? 1 : duration;
		cout << "## Avg speed : " << int(pow((max-min), charsetlength) / duration) << " hash/sec." << endl;
	}

	/*
	* Set hash type
	*/

	public : void setHashType(Hash & ahash) {
		hash = ahash;
		cleaner.setHash(hash);
	}
};
