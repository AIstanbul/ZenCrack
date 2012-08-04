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

#include <iostream>
#include <fstream>
#include <string>

#include "Utils/Hash.cpp"
#include "Utils/InputCleaner.cpp"
#include "Attacks/Rules/RulesAttack.cpp"
#include "Attacks/Dictionnary/DictionnaryAttack.cpp"
#include "Attacks/Combinator/CombinatorAttack.cpp"
#include "Attacks/BF/BruteForceAttack.cpp"
#include "Attacks/Masks/MaskAttack.cpp"

using namespace std;

int main(int argc, char *argv[])
{
	string hashFileName;
	string wordFileName;
	string rulesFileName;
	string charset;
	string mask;
	int	attackType = 0;
	int hashType = 0;
	int reqArgs = 0;
	int min;
	int max;
	bool args=false;

    for (int i=0; i < argc; i++)
    {
		string arg = argv[i];

		if (arg == "-h") {
			args=true;
			hashFileName = argv[i+1];
		}

		if (arg == "-a") {
			args=true;
			attackType = atoi( &argv[i+1][0] );
		}

		if (arg == "-min") {
			args=true;
			min = atoi( &argv[i+1][0] );
		}

		if (arg == "-max") {
			args=true;
			max = atoi( &argv[i+1][0] );
		}

		if (arg == "-c") {
			args=true;
			charset = argv[i+1];
		}

		if (arg == "-m") {
			args=true;
			mask = argv[i+1];
		}

		if (arg == "-w") {
			args=true;
			wordFileName = argv[i+1];
		}

		if (arg == "-r") {
			args=true;
			rulesFileName = argv[i+1];
		}

		if (arg == "-t") {
			args=true;
			hashType =  atoi( &argv[i+1][0] );
		}
    }

	if(!args) {
		cout << "\nZen Crack\n-----------\n" << endl;
		cout << "Usage : ./cracker -h hashlist.txt -w wordlist.txt -r rules.txt [-t hashtype] [-a attackMode] [-min # -max #] [-m mask]\n" << endl;
		cout << " - hashtype :\n   | 0 : md5 <- default\n   | 1 : sha1\n   | 2 : sha256\n   | 3 : sha512\n" << endl;
		cout << " - attackMode :\n   | 0 : dictionnary <- default\n   | 1 : rules\n   | 2 : combinator\n   | 3 : bruteforce\n   | 4 : masks\n" << endl;
		return 0;
	} else {

		Hash hash(hashType);

		switch (attackType) {
			case 0 : {
					DictionnaryAttack cracker;
					cracker.setHashType(hash);
					cracker.setHashlist(hashFileName);
					cracker.setWordlist(wordFileName);
					cracker.run();
				break;
			}
			case 1 : {
					RulesAttack cracker;
					cracker.setHashType(hash);
					cracker.setHashlist(hashFileName);
					cracker.setWordlist(wordFileName);
					cracker.setRulelist(rulesFileName);
					cracker.run();
				break;
			}
			case 2 : {
					CombinatorAttack cracker;
					cracker.setHashType(hash);
					cracker.setHashlist(hashFileName);
					cracker.setWordlist(wordFileName);
					cracker.run();
				break;
			}
			case 3 : {
					BruteForceAttack cracker;
					cracker.setHashType(hash);
					cracker.setRange(min, max);
					cracker.setHashlist(hashFileName);
					cracker.setCharset(charset);
					cracker.run();
				break;
			}
			case 4 : {
					MaskAttack cracker;
					cracker.setHashType(hash);
					cracker.setMask(mask);
					cracker.setHashlist(hashFileName);
					cracker.run();
				break;
			}
		}

		return 0;
	}
}

