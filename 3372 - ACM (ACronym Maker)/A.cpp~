#include <iostream>
#include <string>
using namespace std;

const bool DEBUG = false;

const int MAXSIG = 100;		// max # of sig words and max # times any letter in acronym appears in text
const int MAXINSIG = 100;
const int MAXLEN = 100;		// maximum length of acronym

long table[MAXLEN][MAXSIG][MAXSIG]; // table[i][j][k] = # of time acronym[0..i-1] appears
									//   in text[0..j-1] using first k sig words


string dict[MAXINSIG];
int nDict;
string acronym, text;
int alen, tlen;

int startSig[MAXSIG+1], numSig;
int startPos[MAXLEN];		// earliest spot we can start looking for each
                            //   letter in acronym
int endPos[MAXLEN];			// acronym[i] must start before endPos[i]


bool isInsig(string s)
{
	for(int i=0; i<nDict; i++)
		if (s==dict[i])
			return true;
	return false;
}

string capitalize(string s)
{
	string ans = "";
	for(int i=0; i<s.length(); i++) {
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] += 'A'-'a';
		ans += s[i];
	}
	return ans;
}

bool process()
{
	text = "";
	numSig = 0;
	int loc = 0;
	while (true) {
		string word;
		cin >> word;
		if (word == "CASE")
			return false;
		if (!isInsig(word)) {
			startSig[numSig++] = loc;
			text += capitalize(word);
			loc += word.length();
		}
		if (cin.get() != ' ')
			break;
	}
	startSig[numSig] = loc;
									// determine starting and ending locations
									//   for each letter in acronym
	for(int i=0; i<acronym.length(); i++) {
		int index = numSig-acronym.length()+i;
		if (index > 0)
			startPos[i] = startSig[index];
		else
			startPos[i] = startSig[0]+i;
		if (i < numSig-1)
			endPos[i] = startSig[i+1];
		else
			endPos[i] = startSig[numSig] - (acronym.length()-i-1);
	}
/* 
	cout << text << endl;
	for(i=0; i<acronym.length(); i++) {
		cout << startPos[i] << ',' << endPos[i] << ' ';
	}
	cout << endl;
/* */
	return true;
}

void printTable(int k)
{
	cout << "k=" << k << endl;
	for(int i=0; i<=alen; i++) {
		for(int j=0; j<=tlen; j++) {
			cout << table[i][j][k] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

long fillTable(string acronym, string text)
{
if (DEBUG)
cout << acronym << ' ' << text << endl;
	int i, j, k;
	for(i=1; i<=alen; i++)
		for(j=0; j<=tlen; j++)
			for(k=1; k<=numSig; k++)
				table[i][j][k] = 0;
	for(j=0; j<=tlen; j++)
		table[0][j][0] = 1;
	for(i=1; i<=alen; i++)
		for(k=1; k<=numSig; k++)
			table[i][0][k] = 0;

if (DEBUG)
printTable(0);
	for(k=1; k<=numSig; k++) {
if (DEBUG) {
cout << "k=" << k << endl;
cout << "  j from " << startSig[k-1]+1 << " to " << startSig[k]+1 << endl;
}
		for(j=startSig[k-1]+1; j<startSig[k]+1; j++) {
			for(i=1; i<=alen; i++) {
				table[i][j][k] = table[i][j-1][k];
				if (acronym[i-1] == text[j-1]) {
if (DEBUG)
cout << "match " << i << ',' << j << ", change from " << table[i][j][k];
					table[i][j][k] += table[i-1][j-1][k] + table[i-1][j-1][k-1];
if (DEBUG)
cout << " to " << table[i][j][k] << ' ' << table[i-1][j-1][k] << '+' << table[i-1][j-1][k-1] << endl;
				}
			}
		}
		if (k < numSig) {
if (DEBUG)
cout << "  j to " << startSig[k+1]+1 << endl;
			for(j=startSig[k]+1; j<startSig[k+1]+1; j++) {
				for(i=1; i<=alen; i++) {
					table[i][j][k] = table[i][j-1][k];
				}
			}
		}

if (DEBUG)
printTable(k);
	}
	return table[alen][tlen][numSig];
}

void main()
{
	int i;
	cin >> nDict;
	while (nDict != 0) {
		for(i=0; i<nDict; i++) {
			cin >> dict[i];
		}

		cin >> acronym;
		while (process()) {
			alen = acronym.length();
			tlen = text.length();
			long ans = fillTable(acronym, text);
			if (ans > 0)
				cout << acronym << " can be formed in " << ans << " ways" << endl;
			else
				cout << acronym << " is not a valid abbreviation" << endl;

			cin >> acronym;
		}

		cin >> nDict;
	}
}