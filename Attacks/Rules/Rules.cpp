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
#include <cstdlib>

class Rules {

	public : string applyRule(string word, string rule) {
		int i=0;
		while (i < rule.size()) {
				 if(rule[i] == 'l') {
					ruleLowerCase(word);
				} else if(rule[i] == 'u') {
					ruleUpperCase(word);
				} else if(rule[i] == 'c') {
					ruleCapitalize(word);
				} else if(rule[i] == 'C') {
					ruleInverseCapitalize(word);
				} else if(rule[i] == 't') {
					ruleToggleCase(word);
				} else if(rule[i] == 'T') {
					ruleToggleCaseN(word, rule[i+1]);
					i = i+1;
				} else if(rule[i] == 'r') {
					ruleReverse(word);
				} else if(rule[i] == 'd') {
					ruleDuplicate(word);
				} else if(rule[i] == 'f') {
					ruleMirror(word);
				} else if(rule[i] == '{') {
					ruleRotateLeft(word);
				} else if(rule[i] == '}') {
					ruleRotateRight(word);
				} else if(rule[i] == '$') {
					ruleAppend(word, rule[i+1]);
					i = i+1;
				} else if(rule[i] == '^') {
					rulePrepend(word, rule[i+1]);
					i = i+1;
				} else if(rule[i] == '[') {
					ruleDeleteFirst(word);
				} else if(rule[i] == ']') {
					ruleDeleteLast(word);
				} else if(rule[i] == 'D') {
					ruleDeleteN(word, rule[i+1]);
					i = i+1;
				} else if(rule[i] == 'x') {
					ruleDeleteRange(word, rule[i+1], rule[i+2]);
					i = i+2;
				} else if(rule[i] == 'i') {
					ruleInsert(word, rule[i+1], rule[i+2]);
					i = i+2;
				} else if(rule[i] == 'o') {
					ruleOverwrite(word, rule[i+1], rule[i+2]);
					i = i+2;
				} else if(rule[i] == '\'') {
					ruleTruncate(word, rule[i+1]);
					i = i+1;
				} else if(rule[i] == 's') {
					ruleReplace(word, rule[i+1], rule[i+2]);
					i = i+2;
				} else if(rule[i] == '@') {
					rulePurge(word, rule[i+1]);
					i = i+1;
				} else if(rule[i] == 'z') {
					ruleDuplicateFirst(word, rule[i+1]);
					i = i+1;
				} else if(rule[i] == 'Z') {
					ruleDuplicateLast(word, rule[i+1]);
					i = i+1;
				} else if(rule[i] == 'q') {
					ruleDoubleAll(word);
				} else if(rule[i] == 'p') {
					ruleDuplicateWord(word, rule[i+1]);
					i = i+1;
				} else if (rule[i] == ':') {
					// Do nothing
				}
			i++;
		}
		return word;
	}

	private : void ruleLowerCase(string & word) {
		for (int i=0;i<strlen(word.c_str());i++)
		   word[i] = tolower(word[i]);
	}

	private : void ruleUpperCase(string & word) {
		for (int i=0;i<strlen(word.c_str());i++) 
		    word[i] = toupper(word[i]);
	}

	private : void ruleCapitalize(string & word) {
		word[0] = toupper(word[0]);
	}

	private : void ruleInverseCapitalize(string & word) {
		ruleCapitalize(word);
		word[0] = word[0] + 0x20;
	}

	private : void ruleToggleCase(string & word) {
		for (int i=0;i<strlen(word.c_str());i++) {
		    if (word[i] >= 0x61 && word[i] <= 0x7A) {
		        word[i] = word[i] - 0x20;
			} else if (word[i] >= 0x41 && word[i] <= 0x5A) {
				word[i] = word[i] + 0x20;
			}
		}
	}

	private : void ruleToggleCaseN(string & word, char pos) {
		int number = atoi( &pos );
		if (number > word.size()) return;
		if (word[number] >= 0x61 && word[number] <= 0x7A) {
		        word[number] = word[number] - 0x20;
			} else if (word[number] >= 0x41 && word[number] <= 0x5A) {
				word[number] = word[number] + 0x20;
			}
	}

	private : void ruleReverse(string & word) {
		string word2;
		for (int i=strlen(word.c_str());i>=0;i--) {
			word2 = word2 + word[i];		   
		}
		word = word2;
	}

	private : void ruleDuplicate(string & word) {
		word = word + word;
	}

	private : void ruleMirror(string & word) {
		for (int i=strlen(word.c_str());i>=0;i--) 
			word = word + word[i];		   
	}

	private : void ruleRotateLeft(string & word) {
		word = word + word[0];
		word.erase(0,1);
	}

	private : void ruleRotateRight(string & word) {
		word = word[word.size()-1] + word ;
		word.erase(word.size()-1,1);
	}

	private : void ruleAppend(string & word, char chr) {
		word = word + chr;
	}

	private : void rulePrepend(string & word, char chr) {
		word = chr + word;
	}

	private : void ruleDeleteFirst(string & word) {
		word.erase(0,1);
	}

	private : void ruleDeleteLast(string & word) {
		word.erase(word.size()-1,1);
	}

	private : void ruleDeleteN(string & word, char pos) {
		if (atoi( &pos ) > word.size()) return;
		word.erase(atoi( &pos ), 1);
	}

	private : void ruleDeleteRange(string & word, char startpos, char length) {
		if (atoi( &startpos )+atoi( &length ) > word.size()) return;
		word.erase(atoi( &startpos ), atoi( &length ));
	}

	private : void ruleInsert(string & word, char startpos, char chr) {
		if (atoi( &startpos )> word.size()) return;
		word = word.insert(atoi( &startpos ), 1, chr);
	}

	private : void ruleOverwrite(string & word, char startpos, char chr) {
		if (atoi( &startpos ) > word.size()) return;
		word[atoi( &startpos )] = chr;
	}

	private : void ruleTruncate(string & word, char length) {
		if (atoi( &length ) > word.size()) return;
		word = word.substr(0, atoi( &length ));
	}

	private : void ruleReplace(string & word, char char1, char char2) {
		for (int i=0;i<strlen(word.c_str());i++)
			if (word[i] == char1) {word[i] = char2;}
	}

	private : void rulePurge(string & word, char chr) {
		string word2;
		for (int i=0;i<strlen(word.c_str());i++) {
			if (word[i] != chr) {
				word2 = word2 + word[i];
			}
		}
		word = word2;
	}

	private : void ruleDuplicateFirst(string & word, char nb) {
		int num = atoi( &nb );
		while (num-->0) {word = word[0] + word;}
	}

	private : void ruleDuplicateLast(string & word, char nb) {
		int num = atoi( &nb );
		while (num-->0) {word = word + word[word.size()-1];}
	}

	private : void ruleDoubleAll(string & word) {
		string word2;
		for (int i=0; i<word.length(); i++) {
			word2 = word2 + word[i] + word[i];
		}
		word = word2;
	}

	private : void ruleDuplicateWord(string & word, char nb) {
		int num = atoi( &nb );
		string word2;
		for (int i=0; i<num; i++) {
			word2 = word2 + word;
		}
		word =  word2;
	}

};
