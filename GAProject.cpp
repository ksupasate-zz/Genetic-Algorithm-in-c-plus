#include <iostream>
#include <fstream>
using namespace std;
struct data{
    int value,weight;
};

void read_file()
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
    int itemN,MaxW;
    inFile >> itemN;
    inFile >> MaxW;
    int i = 0;
    while (inFile) {
        inFile >> Data[i].value >> Data[i++].weight;
    }
    for(i = 0; i < itemN; i++){
        cout << Data[i].value << " " << Data[i].weight << "\n";
    }
    inFile.close();
}

int main(){   
    read_file();
    return 0;
}
