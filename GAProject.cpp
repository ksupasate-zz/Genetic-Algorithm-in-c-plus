#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <random>
#include <vector>
int pop = 1000,itemN,MaxW;
struct data{
    int value = 0,weight = 0,index = -1;
}Data[5000],Score[1000];

void read_file(int *itemN)
{
    std::ifstream inFile;
    inFile.open("Set1.txt");

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
    inFile.close();
}

std::default_random_engine dRandom;

int randGenerate(int start, int end)
{
    std::uniform_int_distribution<int> genenNum(start, end - 1);

    return genenNum(dRandom);
}

void random(int *item)
{
    for(int j = 0; j < itemN; j++)
        item[j] = 0;
    for(int j = 0; j < itemN; j++)
        item[randGenerate(0,itemN)] = 1;
}

void randomMU(int *item)
{
    int mutation_rate = 5;
    int x = randGenerate(0,101);
    if(x<mutation_rate){
        int check = randGenerate(0,itemN);
        if(item[check] == 1)
            item[check] = 0;
        else
            item[check] = 1;
    }
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

bool compareTwoPop(data a, data b){
    if(a.value == b.value)
        return a.weight < b.weight;
    return a.value > b.value;
}

void RankingSelection(data Score[]){
    std::sort(Score, Score + pop , compareTwoPop);
}

int main(){
    int bestofthebest=-1,bestoftheWeight=999999999;
    for(int round = 1 ; round <= 5 ; round++){
        int bestone = -1,bestweight = -1 , count = 0,bestTemp;
        read_file(&itemN);
        int item[pop][itemN];
        int divide = 1;
        long int genShow=1;
        std::vector <long> Graph;
        std::cout << "Round : " <<round << "\n===========================================\n";

        for(int timess = 0 ; timess < pop ; timess ++)
            random(item[timess]);

        while(count < 10000 || bestone == 0){

            bestTemp = bestone;
            srand (time(NULL)+count);

            // Fitting Test
            for(int timess = 0 ; timess < pop ; timess ++)
                FittingTest(item[timess],timess);

            // Ranking Selection
            RankingSelection(Score);

            // Uniform Cross
            int RankingStart = pop*1/100;
            for(int timess = RankingStart ; timess < pop-1 ; timess += 2){ // Uniform
                uniformCross(item[Score[timess].index],item[Score[timess+1].index]);
            }

            // Mutation
            for(int timess = pop-1 ; timess > pop*70/100 ; timess--){
                randomMU(item[Score[timess].index]);
            }

            // Fitting Test
            for(int timess = 0 ; timess < pop ; timess ++)
                FittingTest(item[timess],timess);

            // Ranking Selection
            RankingSelection(Score);
            if(bestone < Score[0].value){
                bestone = Score[0].value;
                count = 0;
            }else
                count++;

            if(Score[0].weight > MaxW)
                divide++;
            else 
                divide = 1;

            if(bestone != bestTemp)
                    std::cout << "   Gen : " << genShow << " | Value = " << bestone << " Weight = " << Score[0].weight << "\n";
            else if(count % 1000 == 0)
                std::cout << "   .\n";

            genShow++;
            Graph.push_back(bestone);
        }
        std::cout << "   Finished!!! \n   Gen : " << genShow << " | Value = " << bestone << " Weight = " << Score[0].weight << "\n";

        if(bestofthebest < bestone){
            bestofthebest = bestone;
            bestoftheWeight = Score[0].weight;
        }
            
        std::cout << "===========================================\n";
    }
    std::cout << "\nFinish!!!\nValue = " << bestofthebest << " Weight = " << bestoftheWeight << "\n";
    return 0;
}
