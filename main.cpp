#include "PD.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){

    struct elems{
        int first;
        int second;
        int third;
    };

    PD game1;
    
    int trial=1;
    int total=0;
    int itr=1;
    int rounds=1;
    int reps=5;

    elems results[343*rounds];
    int totals[rounds][7];


    std::ofstream out;
    out.open("results1.txt");
    while(itr<=rounds){
        for (int i=1; i<=7; i++){
            for(int j=1; j<=7; j++){
                for(int k=1; k<=7; k++){
                out<<"Trial "<<trial<<": ("<<game1.cypher(i)<<", "<<game1.cypher(j)<<", "<<game1.cypher(k)<<")\n";
                game1.play(game1.cypher(i), game1.cypher(j), game1.cypher(k),reps);
                results[i].first=game1.getScoresP1();
                total+=game1.getScoresP1();
                results[i].second=game1.getScoresP2();
                results[i].third=game1.getScoresP3();

                game1.printScores(out);
                //out<<"total: "<<" "<<results[i].first+results[i].second+results[i].third<<"\n\n";
                game1.emptyHist();
                trial++;

                }
            }
        totals[itr-1][i-1]=total/reps;
        total=0;
        }
        itr++;
    }

    // for(int i=0; i<10; i++){
    //     out<<"trial "<<i+1<<":\n";
    //     for(int j=0; j<7; j++){
    //         out<<game1.cypher(j+1)<<" strat: "<<totals[i][j]<<"\n";
    //     }
    //     out<<"\n";
    // }

    // double avg=0;

    // for(int i=0; i<7; i++){
    //     for(int j=0; j<rounds; j++){
    //         avg+=totals[j][i];
    //     }
    //     cout<<avg/rounds<<'\t';
    //     avg=0;
    // }

    out.close();


    return 0;
}