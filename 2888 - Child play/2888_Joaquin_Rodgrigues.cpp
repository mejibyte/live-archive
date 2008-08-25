#include <iostream.h>
#include <stdlib.h>

int si[200010];
int cual[200010];
int ind;
int N;
int sum, sumtot;

struct ea{
    int a;
    int b;
    int dif;
    int ind;
    }ficha[401];

int comp(const void *aa, const void *bb)
{
int k;
struct ea *a=(struct ea *)aa;
struct ea *b=(struct ea *)bb;

k=(b->a+b->b)-(a->a+a->b);
if(k!=0) return k;
else return b->b - a->b;
}

int main()
{
int i,j,k;
int lista[200000];
int lala;
int desc;
int cond;

cin >> N;
while(N!=0){
    sumtot=sum=0;

    for(i=0;i<N;i++){
        cin >> j >> k;
        if(j>k){ ficha[i].a=j; ficha[i].b=k; }
        else{ ficha[i].a=k; ficha[i].b=j; }
        ficha[i].dif=ficha[i].a-ficha[i].b;
        ficha[i].ind=i;
        sumtot+=ficha[i].a+ficha[i].b;
        sum+=ficha[i].dif;
        }
    for(j=1;j<=sum/2+1;j++) si[j]=0;
    ficha[N].dif=0;
    qsort(ficha,N,sizeof(ficha[0]),&comp);

    //for(i=0;i<N;i++) cout << ficha[i].b << ' ' << ficha[i].a << endl;

    cond=0;
    for(desc=N;desc>=0 && !cond;desc--){
        cond=0;
        si[0]=1;
        cual[0]=0;
        ind=1;
        if(ficha[desc].dif%2 != sum%2) continue;
        if(desc<N){
            sumtot=sumtot-(ficha[desc].a+ficha[desc].b);
            sum=sum-ficha[desc].dif;
            }
        for(j=1;j<=sum/2+1;j++) si[j]=0;

        //cout << "descartando " << desc+1 << "sum= " << sum << endl;

        for(i=0;i<N;i++){
            if(i!=desc){
                lala=0;
                for(j=0;j<ind;j++){
                    if(ficha[i].dif+cual[j]<=sum/2+1 && si[ficha[i].dif+cual[j]]==0){
                        lista[lala]=ficha[i].dif+cual[j];
                        lala++;
                        }
                    }
                for(j=0;j<lala;j++){si[lista[j]]=1; cual[ind]=lista[j]; ind++; }
                }
            }
        //for(j=0;j<sum/2+1;j++) if(si[j]==1) cout << "Se puede sumar " << j << endl;

        if(sum%2==0 && si[sum/2]==1){
            if(desc<N) cout << sumtot/2 << " discard " <<  ficha[desc].b << ' ' << ficha[desc].a << endl;
            else cout << sumtot/2 << " discard none" << endl;
            cond=1;
            }
        if(desc<N){
            sumtot+=(ficha[desc].a+ficha[desc].b);
            sum+=ficha[desc].dif;
            }
        }
    if(!cond) cout << "impossible" << endl;
    cin >> N;
    }

return 0;
}
