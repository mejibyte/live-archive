#include <iostream>
#include <string>
using namespace std;

const int MAXSTRINGS = 5000;

class prefixInfo
{
public:
	string pre;
	long numEnd;
	int nextPres[MAXSTRINGS];
	int numNextPres;
	long curNum;
};

string strings[MAXSTRINGS];
int pindex[MAXSTRINGS];
prefixInfo prefixes[MAXSTRINGS];
int numPre;

int storePrefix(string s)
{
        int i;
	int len = s.length();
	string pre = s.substr(0, len-1);
	for(i=0; i<numPre; i++) {
		if (prefixes[i].pre == pre)
			break;
	}
	if (i == numPre) {
		prefixes[i].pre = pre;
		prefixes[i].numEnd = 1;
		prefixes[i].numNextPres = 0;
		prefixes[i].curNum = 1;
		numPre++;
	}
	else {
		prefixes[i].numEnd++;
	}
	return i;
}

void calcNextPrefixes(int n)
{
	for(int i=0; i<n; i++) {
		string suf = strings[i].substr(1, strings[i].length());
		for(int j=0; j<numPre; j++) {
			if (suf == prefixes[j].pre) {
				int index = pindex[i];
				prefixes[index].nextPres[prefixes[index].numNextPres++] = j;
				break;
			}
		}
	}
}

int main()
{
	long total;
	int n, length, num;
	cin >> n >> length >> num;
	while (n != 0) {
		numPre = 0;
		for(int i=0; i<num; i++) {
			cin >> strings[i];
			pindex[i] = storePrefix(strings[i]);
		}
		if (length < strings[0].length()) {
			total = 0;
		}
		else {
			calcNextPrefixes(num);

			for(int i=strings[0].length(); i<length; i++) {
				long tmp[MAXSTRINGS] = {0};
				for(int j=0; j<numPre; j++) {
					for(int k=0; k<prefixes[j].numNextPres; k++) {
						tmp[prefixes[j].nextPres[k]] += prefixes[j].curNum;
					}
				}
				for(int j=0; j<numPre; j++) {
					prefixes[j].curNum = tmp[j];
				}
			}
			total = 0;
			for(int i=0; i<numPre; i++) {
				total += prefixes[i].curNum*prefixes[i].numEnd;
				if (total < 0)
					break;
			}
		}
		if (total >= 0)
			cout << total << endl;
		else
			cout << "Too big!" << endl;

		cin >> n >> length >> num;
	}
 return 0;
}

