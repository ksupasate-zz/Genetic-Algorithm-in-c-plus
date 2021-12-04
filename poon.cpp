#include <stdio.h>
int max(int a,int b)
{
    if(a>b) return a;
    return b;
}
main()
{
    int i, j, k, n, wmax;
    int dp[20002], dp2[20002]; /*dp2 use as temp*/
    int value[2002];
    int weight[2002];
    scanf("%d",&n);
    scanf("%d",&wmax);
    for(i=1;i<=n;i++)
        scanf("%d%d",&value[i],&weight[i]);

    /*set dp array*/
    for(i=0;i<=wmax;i++)
        dp[i] = 0; dp2[i] = 0;


    for(i=0;i<=n;i++)
    {
        for(j=1;j<=wmax;j++)
        {
            if(j-weight[i]>=0)
                dp[j] = max(dp2[j],dp2[j-weight[i]]+value[i]);
            else
                dp[j] = dp2[j];
        }
        for(k=0;k<=wmax;k++)
            dp2[k] = dp[k];
    }

    printf("ANS = %d",dp[wmax]);
}
/*
4 5
12 2
10 1
20 3
15 2
*/