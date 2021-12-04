#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;
int pop = 10,itemN,MaxW;
struct data{
    int value = 0,weight = 0;
}arr[5000];

int max(int a, int b) { return (a > b) ? a : b; }

void read_file()
{
    int sum = 0;
    int x;
    ifstream inFile;
    inFile.open("Example Set.txt");

    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    inFile >> itemN >> MaxW;
    int i = 0;
    while (inFile) {
        inFile >> arr[i].value >> arr[i].weight;
        i++;
    }
    // for(i = 0; i < *itemN; i++){
    //     cout << Data[i].value << " " << Data[i].weight << "\n";
    // }
    inFile.close();
}

int knapSack(int MaxW, data arr[], int n)
{

	if (n == 0 || MaxW == 0)
		return 0;
	if (arr[n-1].weight > MaxW)
		return knapSack(MaxW, arr, n - 1);

	else
		return max(
			arr[n-1].value
				+ knapSack(MaxW - arr[n-1].weight,
						arr, n - 1),
			knapSack(MaxW, arr , n - 1));
}

int main()
{
    read_file();

	cout << knapSack(MaxW, arr , itemN);
	return 0;
}

