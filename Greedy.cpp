#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
using namespace std;
int pop = 10,itemN,MaxW;
struct data{
    int value = 0,weight = 0;
}arr[5000];

// struct Item {
// 	int value, weight;

// 	// Constructor
// 	Item(int value, int weight)
// 		: value(value), weight(weight)
// 	{
// 	}
// };

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


// Comparison function to sort Item
// according to val/weight ratio
bool cmp(struct data a, struct data b)
{
	double r1 = (double)a.value / a.weight;
	double r2 = (double)b.value / b.weight;
	return r1 > r2;
}

// Main greedy function to solve problem
double fractionalKnapsack(struct data arr[],
						int N, int itemN)
{
	// Sort Item on basis of ratio
	sort(arr, arr + itemN, cmp);

	// Current weight in knapsack
	int curWeight = 0;

	// Result (value in Knapsack)
	double finalvalue = 0.0;

	// Looping through all Items
	for (int i = 0; i < itemN; i++) {

		// If adding Item won't overflow,
		// add it completely
		if (curWeight + arr[i].weight <= N) {
			curWeight += arr[i].weight;
			finalvalue += arr[i].value;
		}

		// If we can't add current Item,
		// add fractional part of it
		else {
			int remain = N - curWeight;
			finalvalue += arr[i].value
						* ((double)remain
							/ arr[i].weight);

			break;
		}
	}

	// Returning final value
	return finalvalue;
}

// Driver Code
int main()
{
    read_file();
	// Weight of knapsack
	// int N = MaxW;

	// Given weights and values as a pairs
	// data arr[] = { { 100, 10 },
	// 			{ 280, 40 },
	// 			{ 120, 20 },
	// 			{ 120, 24 } };

	// int size = sizeof(arr) / sizeof(arr[0]);
	// Function Call
    cout << arr[1].value;
    cout << arr[1].weight;
    
	cout << "Maximum profit earned = "
		<< fractionalKnapsack(arr, MaxW, itemN);
	return 0;
}
