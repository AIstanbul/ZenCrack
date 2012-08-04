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
	Date : 31/07/2012
*/

using namespace std;

#include "Rules.cpp"
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <omp.h>

class RulesAttack {

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

	public : void setRulelist(string ruleFileName) {
		cout << "## Start processing rulelist" << endl;
		rulelist = cleaner.cleanRulesList(ruleFileName);
		cout << "## Done" << endl;
	}

	// Methods
	public : void run() {
		clock_t start, finish; 
		cout << "## Run rules based attack :" << endl;
		Rules ruleParser;
		int i,j = 0;

		const int rsize = rulelist.size();
		const int wsize = wordlist.size();
		unordered_map<string, bool> hashlistShared = hashlist;
		vector<string> resultlist;
		
		start = clock(); 
		#pragma omp parallel for collapse(2) shared(i, j, hashlistShared, resultlist)
		for (i=0;i < rsize; i++) {
			for (j=0;j < wsize; j++) {
				string word = ruleParser.applyRule(wordlist[j], rulelist[i]);
				string hashstr = hash.getHash(word);
				#pragma omp critical
				{
					if (hashlistShared[hashstr]) {
						cout << hashstr << ":" << word << endl;
						hashlistShared.erase(hashstr);
					}
				}
			}
		}
		finish = clock(); 
		double duration = (double)(finish - start) / CLOCKS_PER_SEC; 
		// Display stats
		cout << "--------------------------------" << endl;
		cout << "## Rules list : " << rulelist.size() << " words." << endl;
		cout << "## Dictionary : " << wordlist.size() << " words." << endl;
		cout << "## Total time : " << duration << " sec." << endl;
		duration = (duration == 0) ? 1 : duration;
		cout << "## Avg speed : " << int((wordlist.size() * rulelist.size()) / duration) << " hash/sec." << endl;
	}

	/*
	* Set hash type
	*/

	public : void setHashType(Hash & ahash) {
		hash = ahash;
		cleaner.setHash(hash);
	}

};
