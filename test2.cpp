#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <cstring>

using namespace std;
int v[5000], w[5000];
int itemN;
int MaxW;

void read_file()
{
    int sum = 0;
    int x;
    ifstream inFile;
    inFile.open("Set3.txt");

    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    inFile >> itemN >> MaxW;
    int i = 0;
    while (inFile) {
        inFile >> v[i] >> w[i];
        i++;
    }
    // for(i = 0; i < *itemN; i++){
    //     cout << Data[i].value << " " << Data[i].weight << "\n";
    // }
    inFile.close();
}

// int pop = 10,itemN,MaxW;
// int v[10],w[10];

// struct data{
//     int value = 0,weight = 0;
// }arr[5000];

int max(int x, int y)
{
    return (x > y) ? x : y;
}
using namespace std;

int KnapSack(int v[], int w[], int itemN, int MaxW)
{
    int dp[MaxW + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < itemN; i++)
        for (int j = MaxW; j >= w[i]; j--)
            dp[j] = max(dp[j], v[i] + dp[j - w[i]]);
    return dp[MaxW];
}

int main()
{
    read_file();
    // scanf("%d", &itemN);
    // scanf("%d", &MaxW);
    // for (int i = 0; i < itemN; i++)
    //     scanf("%d%d", &v[i], &w[i]);
    cout << KnapSack(v,w,itemN,MaxW);
    return 0;
}