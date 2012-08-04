/*
	File under New BSD License
	From : http://code.google.com/p/md5bf/
	Author : Traian Schiau
*/

using namespace std;

#include <string.h>
#include <stdio.h>

class BFGen
{

	private : char charset[257];
	private : int  length;
	private : int  contor[128];
	private : int  maxSim;
	private : int  genVars;
	private : int  minlen;
	public  : int  maxlen;

	public : BFGen(void) : genVars(0), minlen(0), maxlen(0)	{
	}

	public : ~BFGen(void) {
	}

	public : BFGen(char pchar[],int pminlen,int pmaxlen) {
		strcpy(charset,pchar);
		minlen=pminlen;
		maxlen=pmaxlen;
		length=minlen;
		reset();
	}

	private : void reset(void) {
		maxSim=(int)strlen(charset);
		memset(contor,0,128*sizeof(int));
		genVars=0;
	}

	private : int incContor(int poz) {
		if(poz<0)
			return 1;
		contor[poz]++;
		if(contor[poz]==maxSim)
		{
			contor[poz]=0;
			return incContor(poz-1);
		}
		return 0;
	}

	public : int getStr(char buff[]) {
		for(int i=0;i<length;i++)
		{
			buff[i]=charset[contor[i]];
		}
		buff[length]=0;

		if(incContor(length-1)!=0) {
			if(length==maxlen)
				return 1;
			else {
				length++;
				reset();
			}
		}

		return 0;

	}
};
