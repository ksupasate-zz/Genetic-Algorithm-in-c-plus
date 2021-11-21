#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

struct data{
    int value,weight;
};

void read_file(int *itemN)
{
    struct data Data[5000];
    int sum = 0;
    int x;
    ifstream inFile;
    inFile.open("Example Set.txt");

    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    int MaxW;
    inFile >> *itemN >> MaxW;
    int i = 0;
    while (inFile) {
        inFile >> Data[i].value >> Data[i].weight;
        i++;
    }
    for(i = 0; i < *itemN; i++){
        cout << Data[i].value << " " << Data[i].weight << "\n";
    }
    inFile.close();
}

void random_choice(int *itemN)
{
    int randombi;
    for (int j = 0; j < 10; j++)
    {
        cout << j+1 << ".) ";
        srand (j+time(NULL));
        for(int i = 0; i < *itemN; i++){
            cout << rand() % 2;
        }
        cout << "\n";
    }
}



int main(){  
    int itemN;
    read_file(&itemN);
    int item[10][itemN];
    random_choice(&itemN);
    cout << itemN;
    return 0;
}
