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

#include <cstring>
#include <vector>
#include <unordered_map>

class InputCleaner {
	
	private : Hash hash;

	public : void setHash(Hash & ahash) {
		hash = ahash;
	}

	public : vector<string> cleanWordList(string fileName) {
		return generalClean(fileName);
	}

	public : unordered_map<string, bool> cleanHashList(string fileName) {
		unordered_map<string, bool> hashlist;
		vector<string> buffer = generalClean(fileName);
		for(int i=0; i<buffer.size(); i++) {
			if (hash.testHash(buffer[i])) {
				hashlist[lower(buffer[i])] = true;
			}
		}
		return hashlist;
	}

	public : vector<string> cleanRulesList(string fileName) {
		vector<string> buffer = generalClean(fileName);
		vector<string> rulelist;
		for(int i=0; i<buffer.size(); i++) {
			if ( buffer[i].compare("") != 0 && buffer[i].find("##") == string::npos) {
				rulelist.push_back( buffer[i] );
			}
		}
		return rulelist;
	}

	/**
	* Remove end of line chars and double lines
	**/
	private : vector<string> generalClean(string fileName)  {
		ifstream file(fileName.c_str());
		if (file) {
			vector<string> buffer; 
			string line;
		    while(getline(file, line)) {
				line = replace(line, "\n", "");
				line = replace(line, "\r", "");
	        	buffer.push_back( line );
		    }
			removeDoublon(buffer);
			return buffer;
		} else {cout << "## Error opening file file." << endl;}
	}

	/**
	* Remove doubles string in vector
	*/
	private : int removeDoublon(vector<string> & liste)
	{
		int cpt=0;
		bool bFound=false;
		vector<string> final;
		vector<string>::iterator iterListe, iterFinal;
		if (liste.empty())
		    return cpt;
		final.push_back(*liste.begin());
		for (iterListe=liste.begin()+1; iterListe!=liste.end(); iterListe++)
		{
		    bFound=false;
		    for (iterFinal=final.begin(); iterFinal!=final.end() && !bFound; iterFinal++)
		    {
		        if (0==iterListe->compare(*iterFinal))
		        {
		            cpt++;
		            bFound=true;
		        }
		    }
		    if (!bFound)
		    {
		        final.push_back(*iterListe);
		    }
		}
		liste=final;
		return cpt;
	}

	/*
	* To lowercase
	*/
	string lower(string str) {
		for (int i=0;i<strlen(str.c_str());i++) 
		    if (str[i] >= 0x41 && str[i] <= 0x5A) 
		        str[i] = str[i] + 0x20;
		return str;
	}

	/*
	* Replace string into another
	*/
	private : string replace( string source, const string find, string replace ) {
		size_t j;
		for ( ; (j = source.find( find )) != string::npos ; ) {
			source.replace( j, find.length(), replace );
		}
		return source;
	}
};
