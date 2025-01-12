
#include <vector>
#include <string>

class PD{
private:
    struct Player{
        std::vector<int> hist;      //previous choices
        int d;                      //number of defects
        int c;                      //number of cooperations
        int score;                  //individuals score
        std::string strat;          //current employed strategy
    };

    Player P1, P2, P3;      

public:
    //constructors
    PD();
    PD(std::string s1, std::string s2, std::string s3);
    PD(int s1, int s2, int s3);

    //strategies
    int allDefect() const;
    int allCooperate() const;
    int random() const;
    int goByMajority(int round, const Player &P1, const Player & P2, const Player & P3 ) const;
    int toughTfT(int round, const Player &P1, const Player & P2) const ;
    int softTfT(int round, const Player &P1, const Player & P2) const;
    int ATFT(int round, const Player &P1, const Player & P2 , double r) const;

    //ascessors
    void printDecisions(std::ostream &os) const;        //outputs contents of hist to stream os
    void printScores(std::ostream &os) const;           //outputs all player's scores to stream os
    int getScoresP1() const;        //returns player 1's score
    int getScoresP2() const;        //returns player 2's score
    int getScoresP3() const;        //returns player 3's score
    
    //modifiers
    void addScore(int c1, int c2, int c3);    //calculates each player's score affter a round
    void callStrat(int strat, Player &m, Player &o1, Player &o2, int r);    //returns the appropriate choice given player m's assigned strategy
    void emptyHist();       //clears hist and sets d,c, and choice to zero 
 
    //helper functions
    std::string cypher(int i) const;            //converts integer 1 through 7 to appropriate strategy string name
    int decypher(std::string strat) const;      //converts strategy string name to appropriate int

    //play game
    void play(std::string strat1, std::string strat2, std::string strat3, int rounds);      //player 1-3 startegies and number of iterated games 

};


//////////////////////////////////////////
// cypher key:                          //
// 1 = allDefect                        //
// 2 = allCooperate                     //
// 3 = random                           //
// 4 = goByMajority                     //
// 5 = softTfT                          //
// 6 = toughTfT                         //
// 7 = adpativeTfT/ATFT                 //
//////////////////////////////////////////

