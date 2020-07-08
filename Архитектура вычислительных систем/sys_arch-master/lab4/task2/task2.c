#include <stdio.h>
#include <stdlib.h>

int f(int x,int y){
    int result;
    if(x>10){
        result = abs(x)+y; 
    }else{
        result = 1000/(x-y); 
    }
    return result;
};

int pow(int num,int pow){
    int result=1;
    for(int i=0;i<pow;i++){
        result = result * num;
    };
    return result;
}

int main(){
    int m=0x2;
    int x[2] = {0x4,0x4};
    int y[2] = {0x2,0x2};
    int h = 0x10;
    int sum = 0x0;
    int a,b,c;
    for (int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            sum += pow(x[i],5)+y[i]*(h+17*i)*f(x[i],y[j]);
            sum -= i*h;
            printf("pow(x[i],5) = %d(%x)\n",pow(x[i],5),pow(x[i],5));
            printf("h+17*i = %d(%x)\n",h+17*i,h+17*i);
            printf("(h+17*i)*f(x[i],y[j]) = %d(%x)\n",(h+17*i)*f(x[i],y[j]),(h+17*i)*f(x[i],y[j]));
            printf("y[i]*(h+17*i)*f(x[i],y[j]) = %d(%x)\n",y[i]*(h+17*i)*f(x[i],y[j]),y[i]*(h+17*i)*f(x[i],y[j]));
            printf("pow(x[i],5)+y[i]*(h+17*i)*f(x[i],y[j]) = %d(%x)\n",pow(x[i],5)+y[i]*(h+17*i)*f(x[i],y[j])
            ,pow(x[i],5)+y[i]*(h+17*i)*f(x[i],y[j]));

            printf("sum[%d][%d] = %d(%x)\n\n",i,j,sum,sum);
        }
    }
}

