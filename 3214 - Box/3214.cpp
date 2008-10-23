#include<iostream>
#include<stdio.h>
#include<map>
#include<vector>
#include<list>
#include<math.h>
#include<string>
#include<string.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<bitset>

using namespace std;

struct pallet
{
  int h,w;
  pallet(){}
  pallet(int H,int W)
  {
    h=max(H,W);
    w=min(H,W);
  }
  bool operator < (const pallet & t) const
  {
    return h<t.h || (h==t.h && w<t.w);
  }
  
  
};


int main()
{
  pallet pallets[6];
  for(int x, y; cin >> x >> y; ){
    pallets[0] = pallet(x, y);
    for(int i=1;i<6;++i)
      {
	cin >> x >> y;
	pallets[i]=pallet(x,y);
      }

    sort(pallets,pallets +6);

    bool ok = true;
    for(int i=0;i<6;i+=2)
      //validan paridad de pallets
      {
	if(pallets[i].w!=pallets[i+1].w || pallets[i].h!=pallets[i+1].h)
	  {
	    puts("IMPOSSIBLE");
	    ok = false;
	    break;
	  }
      }

    if (ok){
      if((pallets[0].w==pallets[2].w && pallets[2].h==pallets[4].h && pallets[4].w==pallets[0].h))
	puts("POSSIBLE");

      else
	puts("IMPOSSIBLE");
    }
  }
  return 0;
}
