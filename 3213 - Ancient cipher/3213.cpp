#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>
#include<cstdio>
using namespace std;

int main()
{
  string code,decode;
  while( cin>>code>>decode )
    {
      map<char,int> encode;
      map<char,int> decoded;
      vector<int> line1;
      vector<int> line2;
      if(code.size() == decode.size())
        {
          for(int i=0;i<code.size();++i)
            {
              encode[code[i]]++;
              decoded[decode[i]]++;
            }
          for(map<char,int>::iterator it= encode.begin();it!=encode.end();++it)
            line1.push_back((*it).second);

          for(map<char,int>::iterator it= decoded.begin();it!=decoded.end();++it)
            line2.push_back((*it).second);

          sort(line1.begin(),line1.end());
          sort(line2.begin(),line2.end());
          
          if(equal(line1.begin(),line1.end(),line2.begin()))            
              puts("YES");            
          else
              puts("NO");            
        }
      else
        {
          puts("NO");
        }
    }
  return 0;
}
