#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <random>
#include <vector>
//using namespace std;
int pop = 1000,itemN,MaxW;
struct data{
    int value = 0,weight = 0,index = -1;
}Data[5000],Score[1000];

void read_file(int *itemN)
{
    std::ifstream inFile;
    inFile.open("Example Set.txt");

    if (!inFile) {
        std::cerr << "Unable to open file datafile.txt";
        std::exit(1);   // call system to stop
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

std::default_random_engine dRandom;

int randGenerate(int start, int end)
{
    std::uniform_int_distribution<int> genenNum(start, end - 1);

    return genenNum(dRandom);
}

void random(int *item,int divide)
{
    int gene = 0;
        for(int j = 0; j < itemN; j++)
            item[j] = 0;
        for(int j = 0; j < itemN/divide; j++)
        {
            gene = randGenerate(0, 2);
            item[randGenerate(0,itemN)] = 1;
            // cout << item[j];
        }
        // cout <<"\n";

}

void randomMU(int *item)
{
    int mutation_rate = 5;
    int x = randGenerate(0,101);
    if(x<mutation_rate){
        int check = randGenerate(0,itemN);
        if(item[check] == 1){
            item[check] = 0;
        }
        else{
            item[check] = 1;
        }
    }
}

void random_choice(int *item,int timess){
    // srand (timess+time(NULL));
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
    for(quota=0 ; quota < itemN/2 ; quota++){
        luckyNumber = rand() % itemN;
        if(item[luckyNumber]==1){
            quota--;
        }
        item[luckyNumber] = 1;
        // cout << luckyNumber << "\n";
    }
    // cout << "\n";
}
void printData(int *item){
    for(int i=0 ; i < itemN ; i++)
        std::cout << item[i];
    std::cout << "\n";
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
    std::sort(Score, Score + pop , compareTwoPop);
}

// void Mutation(int *item){
//      srand (time(NULL));
//      int temp = rand() % pop;
//      random_choice(item[temp],temp);
// }

int main(){
    
    int bestone = -1,bestweight = -1 , count = 0;
    read_file(&itemN);
    int item[pop][itemN];
    int divide = 1;
    std::vector <long> Graph;
    for(int timess = 0 ; timess < pop ; timess ++)
        random(item[timess],divide);
    while(count < 10000 || bestone == 0){
        srand (time(NULL)+count);
        // cout << "Generation : " << gen++ << "\n";

        // for(int timess = 0 ; timess < pop ; timess ++)
        //     random_choice(item[timess],timess);
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
        int RankingStart = pop*1/100;
        for(int timess = RankingStart ; timess < pop-1 ; timess += 2){ // Uniform
            uniformCross(item[Score[timess].index],item[Score[timess+1].index]);
        }

        // Mutation
        
        for(int timess = pop-1 ; timess > pop*70/100 ; timess--){
//             srand (timess+time(NULL));
            randomMU(item[Score[timess].index]);
//            random(item[Score[timess].index],divide);
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
        }
//        else if (bestone == Score[0].value){
//            if(bestweight < Score[0].weight){
//                bestweight = Score[0].weight;
//                count = 0;
//            }
//        }
        else{
            count++;
        }
        if(Score[0].weight > MaxW){
            divide++;
        }
        else divide = 1;
        std::cout << "Ans : Value = " << bestone << " Weight = " << Score[0].weight << "\nEncode : ";
        Graph.push_back(bestone);
        // printData(item[Score[0].index]);
    }
    std::cout << "Ans : Value = " << bestone << " Weight = " << Score[0].weight << "\n";
    // Write File
    std::ofstream myfile("testWrite.txt");
    long int wowza=1;
    for(auto i=0; i < Graph.size(); i++)
        myfile << wowza++ << " " << Graph[i] << "\n";
    myfile.close();

    return 0;
}
