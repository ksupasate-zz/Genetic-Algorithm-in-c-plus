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
    inFile.open("Set1.txt");

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

// Returns the maximum value that
// can be put in a knapsack of capacity W
int knapSack(int MaxW, data arr[], int n)
{

	// Base Case
	if (n == 0 || MaxW == 0)
		return 0;

	// If weight of the nth item is more
	// than Knapsack capacity W, then
	// this item cannot be included
	// in the optimal solution
	if (arr[n-1].weight > MaxW)
		return knapSack(MaxW, arr, n - 1);

	// Return the maximum of two cases:
	// (1) nth item included
	// (2) not included
	else
		return max(
			arr[n-1].value
				+ knapSack(MaxW - arr[n-1].weight,
						arr, n - 1),
			knapSack(MaxW, arr , n - 1));
}

// Driver code
int main()
{
    read_file();
	// int val[] = { 55, 10, 47,5,4,50,8,61,85,87 };
	// int wt[] = { 95,4,60,32,23,72,80,62,65,46 };
	// int MaxW = 269;
	// int n = sizeof(arr.value) / sizeof(arr[0].value);
	cout << knapSack(MaxW, arr , itemN);
	return 0;
}

// This code is contributed by rathbhupendra
