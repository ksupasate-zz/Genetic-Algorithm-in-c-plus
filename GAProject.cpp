#include <iostream>
#include <fstream>
using namespace std;
struct data{
    int value,weight;
};

void read_file()
{
    struct data;
    int sum = 0;
    int x;
    ifstream inFile;
    inFile.open("Example Set.txt");

    if (!inFile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
    }

    while (inFile >> x) {
        sum = sum + 1;
    }
    sum = sum/2;

    for(int i = 0; i < sum; i++){
        cin >> "%d %d\n",data[i].value,data[i].weight;
    }

    inFile.close();
    cout << "Sum = " << sum << endl; 
}

int main(){   
    cout << "Hello World";
    read_file();
    return 0;
}
