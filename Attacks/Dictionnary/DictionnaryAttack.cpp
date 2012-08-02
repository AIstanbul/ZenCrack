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
*/

using namespace std;

#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <omp.h>

class DictionnaryAttack {

	// Attributes
	private : unordered_map<string, bool> hashlist;
	private : vector<string> wordlist;
	private : vector<string> rulelist;
	private : Hash hash;
	private : InputCleaner cleaner;

	// Setters
	public : void setHashlist(string hashFileName) {
		cout << "## Start processing hashlist" << endl;
		hashlist = cleaner.cleanHashList(hashFileName);
		cout << "## Done" << endl;
	}

	public : void setWordlist(string wordFileName) {
		cout << "## Start processing wordlist" << endl;
		wordlist = cleaner.cleanWordList(wordFileName);
		cout << "## Done" << endl;
	}

	// Methods
	public : void run() {
		time_t t1 = time(NULL);
		cout << "## Run dictionnary attack :" << endl;
		Rules ruleParser;
		int i= 0;
		const int wsize = wordlist.size();
		unordered_map<string, bool> hashlistShared = hashlist;
		vector<string> resultlist;

		#pragma omp parallel for shared(i, hashlistShared, resultlist)
		for (i=0;i < wsize; i++) {
			string hashstr = hash.getHash(wordlist[i]);
			#pragma omp critical
			{
				if (hashlistShared[hashstr]) {
					cout << hashstr << ":" << wordlist[i] << endl;
					hashlistShared.erase(hashstr);
				}
			}
		}

		// Display stats
		cout << "--------------------------------" << endl;
		cout << "## Dictionary : " << wordlist.size() << " words." << endl;
		cout << "## Total time : " << double(difftime(time(NULL), t1)) << " sec." << endl;
		cout << "## Avg speed : " << int(wordlist.size() / double(difftime(time(NULL), t1))) << " hash/sec." << endl;
	}

	/*
	* Set hash type
	*/

	public : void setHashType(Hash & ahash) {
		hash = ahash;
		cleaner.setHash(hash);
	}
};
