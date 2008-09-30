/*
  Problem: 1116 - Drop the Triples
  Author: XOJ

  Accepted

  Código recibido en un e-mail de hukun_1761@163.com
*/
#include <iostream>
using namespace std;

typedef struct node
{
    int e[3];
}Triple;
Triple triple[10];
int a[14];
int b[14]; 
int n;
int num_a,num_b;
int temp,max;

bool out(int k){
    if(!k && num_a==num_b) return false;
    else if(num_a==num_b) printf("0\n");
    else if(num_a>num_b) printf("1\n");
    else printf("2\n");
    return true;  
}

void search(int e[14],int num,int ne,int se){
    if(num>temp) temp=num;
    int i;
    for(i=se;i<14;++i){
        if(ne==2 && i>=triple[num].e[0]+triple[num].e[1]) break;               
        if(e[i]>0){
            triple[num].e[ne]=i;
            --e[i];
            ++ne;
            if(ne==3) search(e,num+1,0,triple[num].e[0]);
            else search(e,num,ne,i);    
            --ne;
            ++e[i];           
        }     
    }
}

void solve(){
    temp=num_a=num_b=0;
    search(a,0,0,0);
    num_a=temp;
    temp=0;
    search(b,0,0,0);
    num_b=temp;
    out(1);
    return ;
}

int main(){
    int i;
    while(scanf("%d",&n),n){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(i=1;i<=n;++i){
            scanf("%d",&temp);
            if(i%2) ++a[temp];
            else ++b[temp]; 
        }
        num_a=num_b=0;
        for(i=1;i<14;++i){
            num_a+=a[i]/3;
            a[i]%=3;
            num_b+=b[i]/3;
            b[i]%=3;
        }    
        if(out(0)) continue;
        else solve();              
    }
    return 0;    
}
