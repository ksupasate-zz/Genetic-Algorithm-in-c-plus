#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
using namespace std;
int pop = 1000,itemN,MaxW;
struct data{
    int value = 0,weight = 0,index = -1;
}Data[5000],Score[1000];

void read_file(int *itemN)
{
    int sum = 0;
    int x;
    ifstream inFile;
    inFile.open("Set1.txt");

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

int rand50()
{
    // rand() function will generate odd or even
    // number with equal probability. If rand()
    // generates odd number, the function will
    // return 1 else it will return 0.
    return rand() & 1;
}
 
// Random Function to that returns 1 with 75%
// probability and 0 with 25% probability using
// Bitwise OR
bool rand75()
{
    return rand50() | rand50();
}

void random_choice(int *item,int timess){
    srand (timess+time(NULL));
    int count = 0,temp;
    // for(int i = 0 ; i < itemN ; i++){
    //     temp = rand() % 2;
    //     if(count < pop/40){
    //         item[i] = temp;
    //         count++;
    //     }else{
    //         item[i] = 0;
    //     }
    //     // cout << rand() % 2;
    // }
    int quota=0,luckyNumber;
    for(int i = 0 ; i < itemN ; i++){
        item[i]=0;
    }
    while(quota <= MaxW){
        luckyNumber = rand() % itemN;
        item[luckyNumber] = 1;
        quota += Data[luckyNumber].weight;
        
        // cout << luckyNumber << "\n";
    }
    // cout << "\n";
}
void printData(int *item){
    for(int i=0 ; i < itemN ; i++)
        cout << item[i];
    cout << "\n";
}

void uniformCross(int *item,int *item2){
    int temp;
    for(int j = 0 ; j < itemN ; j++){
        if(rand()%2){
            temp = item[j];
            item[j] = item2[j];
            item2[j] = temp;
        }
    }
}

void FittingTest(int *item,int n){
    Score[n].value = 0;
    Score[n].weight = 0;
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
    if(a.value == b.value)
        return a.weight < b.weight;
    return a.value > b.value;
}

void RankingSelection(data Score[]){
    sort(Score, Score + pop , compareTwoPop);
}

int main(){  
    int bestone = -1 , count = 0,gen = 1;
    read_file(&itemN);
    int item[pop][itemN];
    while(count < 10000){
        // cout << "Generation : " << gen++ << "\n";

        for(int timess = 0 ; timess < pop ; timess ++)
            random_choice(item[timess],timess);
        // cout << "\n---------- Default Data ----------\n";
        // for(int timess = 0 ; timess < pop ; timess ++)
        //     printData(item[timess]);
        // cout << "\n---------- Fitting Test ----------\n";  
        for(int timess = 0 ; timess < pop ; timess ++)
            FittingTest(item[timess],timess);
        // for(int timess = 0 ; timess < pop ; timess ++)
        //     cout << Score[timess].index+1 << ") Value : " << Score[timess].value << " Weight : " << Score[timess].weight << "\n";
        
        RankingSelection(Score);
        // cout << "\n---------- Ranking Selection ----------\n";
        // for(int timess = 0 ; timess < pop ; timess ++)
        //     cout << Score[timess].index+1 << ") Value : " << Score[timess].value << " Weight : " << Score[timess].weight << "\n";
        
        // cout << "\n---------- Original Ranking -----------\n"; 
        // for(int timess = 0 ; timess < pop ; timess ++)
        //     printData(item[timess]);

        // cout << "\n---------- Uniform Cross ----------\n";
        int RankingStart = pop*2/10;
        for(int timess = RankingStart ; timess < pop-1 ; timess += 2){ // Uniform
            uniformCross(item[Score[timess].index],item[Score[timess+1].index]);
        }
        // for(int timess = 0 ; timess < pop ; timess++)
        //     printData(item[timess]);
            
        // cout << "\n---------- Fitting Test ----------\n";    
        for(int timess = 0 ; timess < pop ; timess ++)
            FittingTest(item[timess],timess);
        
        RankingSelection(Score);
        // for(int timess = 0 ; timess < pop ; timess ++)
        //     cout << Score[timess].index+1 << ") Value : " << Score[timess].value << " Weight : " << Score[timess].weight << "\n";
        // cout << "\n-------------------------------------------------------\n";
        if(bestone < Score[0].value){
            bestone = Score[0].value;
            count = 0;
        }else{
            count++;
        }
    }
<<<<<<< HEAD
    cout << "Ans : Value = " << bestone << " Weight = " << Score[0].weight << "\n Encode : ";
=======
<<<<<<< HEAD
<<<<<<< HEAD
    cout << "Ans : Value = " << bestone << " Weight = " << Score[0].weight << "\nEncode : ";
>>>>>>> 60757f4a991d7b8ec1af9405a2ca068eb00997d4
    printData(item[Score[0].index]);
=======
    cout << "Ans : Value = " << bestone << " Weight = " << Score[0].weight;
>>>>>>> parent of aca1520 (Last3)
=======
    cout << "Ans : Value = " << bestone << " Weight = " << Score[0].weight;
>>>>>>> parent of aca1520 (Last3)
    return 0;
}