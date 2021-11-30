#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
int pop = 10;
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

void random_choice(int itemN,int *item)
{
    int randombi;
    for (int j = 0; j < pop; j++)
    {
        srand (j+time(NULL));
        for(int i = 0 ; i < itemN ; i++){
            cout << rand() % 2;
        }
        cout << "\n";
    }
}

// void fitness_test(){
//     for(int i = 0; i < pop; i++){
//         for(int j = 0; j < itemN; j++){
//             if()
//         }    
//     }
// }

int main(){  
    int itemN;
    read_file(&itemN);
    int item[pop][itemN];
    random_choice(itemN, item[0]);
    return 0;
}
