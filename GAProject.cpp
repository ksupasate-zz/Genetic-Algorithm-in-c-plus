#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
using namespace std;
int pop = 10,itemN,MaxW;
struct data{
    int value = 0,weight = 0,index = -1;
}Data[5000],Score[10];

void read_file(int *itemN)
{
    int sum = 0;
    int x;
    ifstream inFile;
    inFile.open("Example Set.txt");

    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    inFile >> *itemN >> MaxW;
    int i = 0;
    while (inFile) {
        inFile >> Data[i].value >> Data[i].weight;
        i++;
    }
    // for(i = 0; i < *itemN; i++){
    //     cout << Data[i].value << " " << Data[i].weight << "\n";
    // }
    inFile.close();
}

void random_choice(int *item,int timess){
    srand (timess+time(NULL));
    for(int i = 0 ; i < itemN ; i++){
        item[i] = rand() % 2;
        // cout << rand() % 2;
    }
    // cout << "\n";
}

void printData(int *item){
    for(int i=0 ; i < itemN ; i++)
        cout << item[i];
    cout << "\n";
}

void uniformCross(int *item){
    int temp;
    for(int j = 0 ; j < itemN ; j++){
        if(rand()%2){
            temp = item[j];
            item[j] = item[j+pop];
            item[j+pop] = temp;
        }
    }
}

void FittingTest(int *item,int n){
    for(int i=0 ; i < itemN ; i++){
        if(item[i]){
            Score[n].value += Data[i].value;
            Score[n].weight += Data[i].weight;
        }
        Score[n].index = n;
    }
    if(Score[n].weight > MaxW)
        Score[n].value = 0;
}
// void fitness_test(){
//     for(int i = 0; i < pop; i++){
//         for(int j = 0; j < itemN; j++){
//             if()
//         }    
//     }
// }

bool compareTwoPop(data a, data b){
    if (a.value >= b.value)
        return a.value > b.value;
}

void RankingSelection(data Score[]){
    sort(Score, Score + pop , compareTwoPop());
}

int main(){  
    read_file(&itemN);
    int item[pop][itemN];
    for(int timess = 0 ; timess < pop ; timess ++)
        random_choice(item[timess],timess);
    cout << "\n---------- Default Data ----------\n";
    for(int timess = 0 ; timess < pop ; timess ++)
        printData(item[timess]);
    cout << "\n---------- Fitting Test ----------\n";  
    for(int timess = 0 ; timess < pop ; timess ++)
        FittingTest(item[timess],timess);
    for(int timess = 0 ; timess < pop ; timess ++)
        cout << timess+1 << ") Value : " << Score[timess].value << " Weight : " << Score[timess].weight << "\n";
    
    cout << "\n---------- Ranking Selection ----------\n";
    RankingSelection(Score);

    cout << "\n---------- Uniform Cross ----------\n";
    for(int timess = 0 ; timess < pop ; timess += 2) // Uniform
        uniformCross(item[timess]);
    for(int timess = 0 ; timess < pop ; timess ++)
        printData(item[timess]);
    cout << "\n---------- Fitting Test ----------\n";    
    for(int timess = 0 ; timess < pop ; timess ++)
        FittingTest(item[timess],timess);
    for(int timess = 0 ; timess < pop ; timess ++)
        cout << timess+1 << ") Value : " << Score[timess].value << " Weight : " << Score[timess].weight << "\n";
    return 0;
}
