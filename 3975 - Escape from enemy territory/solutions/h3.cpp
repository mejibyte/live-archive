/*
  Obfuscation, NWERC '07, Mathijs Vogelzang April 2007

  26 minutes.
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
typedef vector<int> VI;
typedef vector<string> VS;

int N;
struct Word
{
      string chars;
      string orig;
      char endChr;
      int len;
};

vector<Word> words[26];
char s[1100];
string s_;
int len;

int possible(int idx, Word wrd)
{
   if(idx + wrd.len > len)
      return 0;
   if(wrd.len == 1)
      return 1;
   if(wrd.endChr != s[idx+wrd.len-1])
      return 0;
   string comp = s_.substr(idx+1, wrd.len-2);
   sort(comp.begin(), comp.end());
   if(comp != wrd.chars)
      return 0;
   return 1;
}

int main()
{
   int runs;
   scanf("%d", &runs);
   while(runs--)
   {
      for(int i=0;i<26;i++) words[i].clear();
 
      scanf(" %s ", s);
      s_ = s;
      len = strlen(s);
      scanf("%d", &N);
      char tmp[130];      
      for(int i=0;i<N;i++)
      {
         scanf(" %s ", tmp);
         Word word;
         word.orig = tmp;
         if(strlen(tmp) == 1)
         {
            word.chars ="";
            word.endChr = tmp[0];
            word.len = 1;
         }
         else
         {
            word.chars = word.orig.substr(1, word.orig.size()-2);
            sort(word.chars.begin(), word.chars.end());
            word.endChr = word.orig[word.orig.size()-1];
            word.len = word.orig.size();
         }
         words[tmp[0] - 'a'].push_back(word);
      }
      VS result[1100];
      bool ambig[1100];
      memset(ambig, 0, sizeof(ambig));
      for(int idx = len-1;idx >= 0;idx --)
      {
         VS &cur = result[idx];
         for(int j=0;j<words[s[idx]-'a'].size() && !ambig[idx];j++)
         {
            int newIndex = idx + words[s[idx]-'a'][j].len;
            
            if((newIndex == len || result[newIndex].size() > 0 || ambig[newIndex]) && possible(idx, words[s[idx]-'a'][j]))
            {
//               printf("%d %s\n", idx, words[s[idx]-'a'][j].orig.c_str());
               if(cur.size() > 0) ambig[idx] = 1;
               else
               {
                  if(ambig[newIndex]) ambig[idx] = 1;
                  else
                  {
                     cur = result[newIndex];
                     cur.push_back(words[s[idx]-'a'][j].orig);
                  }
               }
            }
         }
      }

      if(ambig[0])
         printf("ambiguous\n");
      else
         if(result[0].size() == 0)
            printf("impossible\n");
         else
         {
            for(int i=result[0].size()-1;i>=0;i--)
            {
               printf("%s", result[0][i].c_str());
               if(i == 0) printf("\n");
               else
                  printf(" ");
            }
         }
   }
   return 0;
}
