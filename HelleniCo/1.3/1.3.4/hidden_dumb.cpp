#include "hiddenlib.h"

int main(){
    int N =getN();
    for(int i=1;i<=N;++i){
        if(ishidden(i)) break;
    }
    return 0;
}