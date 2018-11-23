#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//author: Canyellow
//date: 2018.11.20
//暴力穷举法
//dimension限制
//传入两个dimension参数m,n
//表示处理m列n行的点灯问题
//m必须在2～63之间
//因为用的uint64(unsigned long long int)类型,8字节64位
//初始值问题，不能取m=n=1.
int main(int argc,char *argv[])
{
    //使用uint64—t来表示穷举范围，意味着最多行数不能超过64行
    int dimensionM=atoi(argv[1]);
    int dimensionN=atoi(argv[2]);
    int resNum=0;
    //statusMax=2^64-1
    //即0xffffffffffffffff
    unsigned long long int soluMax=pow(2.0,dimensionM)-1;
    unsigned long long int *solution=calloc(dimensionN,sizeof(unsigned long long int));

    unsigned long long int statusLast=0;
    unsigned long long int statusNow=0;
    unsigned long long int statusNext=0;
    for(unsigned long long int soluIndex=0x0;soluIndex<=soluMax;soluIndex++)
    {
        solution[0]=soluIndex;
        statusLast=((solution[0]<<1)&soluMax)^solution[0]^(solution[0]>>1);
        statusNow=solution[0];
        //对第二行到倒数第二行进行操作
        for(int NIndex=1;NIndex<dimensionN-1;NIndex++)
        {
            //根据上一行确定这一行要按下哪些位置，对上一行取反
            solution[NIndex]=(~statusLast)&soluMax;

            //对本行根据相邻翻转原则重算
            statusNow=((solution[NIndex]<<1)&soluMax)^solution[NIndex]^(solution[NIndex]>>1)^statusNow;

            //对下一行根据规则判断
            statusNext=solution[NIndex];

            //准备下一轮的循环量
            statusLast=statusNow;
            statusNow=statusNext;
        }

        //最后一行
        solution[dimensionN-1]=(~statusLast)&soluMax;
        statusNow=((solution[dimensionN-1]<<1)&soluMax)^solution[dimensionN-1]^(solution[dimensionN-1]>>1)^statusNow;
        //判断最后一行的值
        if(statusNow==soluMax)
        {
            printf("%d\n",++resNum);
            for(int NIndex=0;NIndex<dimensionN;NIndex++)
            {
                printf("%llx\n",solution[NIndex]);
            }
            printf("\n");
        }
    }

    free(solution);
    return 0;
}
