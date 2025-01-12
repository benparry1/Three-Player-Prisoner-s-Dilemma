#include "PD.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>

int random_gen(int min, int max) {
	static std::random_device device{};
	static std::default_random_engine engine{ device() };
	std::uniform_int_distribution<int> distribution{ min, max };
	return distribution(engine);
}

PD::PD(){
    P1.d=P2.d=P3.d=0;
    P1.c=P2.c=P3.c=0;
    P1.score=P2.score=P3.score=0;
}
PD::PD(std::string s1, std::string s2, std::string s3){
    PD();
    P1.strat=s1;
    P2.strat=s2;
    P3.strat=s3;
}
PD::PD(int s1, int s2, int s3){
    PD();
    P1.strat=cypher(s1);
    P2.strat=cypher(s2);
    P3.strat=cypher(s3);
}
int PD::allDefect() const{
    return 1;
}
int PD::allCooperate() const{
    return 0;
}
int PD::random() const{
    return random_gen(0,1);
}
int PD::goByMajority(int round, const Player &m, const Player & o1, const Player & o2 ) const{
    if(round <=1 )
        return 0;
    if(o1.d > m.c || o2.d > m.c)
        return 1;
    else
        return 0;
}
int PD::toughTfT(int round, const Player &o1, const Player & o2) const{
    if(round<=1)   
        return 0;
    if(o1.hist.back()==1 || o2.hist.back()==1)
        return 1;
    else   
        return 0;
}
int PD::softTfT(int round, const Player &o1, const Player & o2) const{
    if(round<=1)   
        return 0;
    if(o1.hist.back()==1 && o2.hist.back()==1)
        return 1;
    else   
        return 0;
}
int PD::ATFT(int round, const Player &o1, const Player & o2, double r ) const{
    double world =0; 
    if(round<=1)
        return 0;
    if(o1.hist.back()==0 || o1.hist.back()==0){
        world = world +r*(1-world);
    }
    else
        world = world + r*(0-world);

    if(world >=0.5)
        return 0;
    else
        return 1;
}
void PD::printDecisions(std::ostream &os) const{
    os<<"Player 1 ("<<P1.strat<<"):\n";
    for(auto &x : P1.hist){
        os<<x<<'\t';
    }
    os<<"\n\nPlayer 2 ("<<P2.strat<<"):\n";
    for(auto &x: P2.hist){
        os<<x<<'\t';
    }
    os<<"\n\nPlayer 3 ("<<P3.strat<<"):\n";
    for(auto &x: P3.hist){
        os<<x<<'\t';
    }    
    os<<'\n';
}
void PD::printScores(std::ostream &os) const{
    os<<"Player 1: "<<P1.score<<'\n';
    os<<"Player 2: "<<P2.score<<'\n';
    os<<"Player 3: "<<P3.score<<'\n';
}
int PD::getScoresP1() const{
    return P1.score;
}  
int PD::getScoresP2() const{
    return P2.score;
}  
int PD::getScoresP3() const{
    return P3.score;
}  
void PD::play(std::string strat1, std::string strat2, std::string strat3, int rounds){
    P1.strat=strat1;
    P2.strat=strat2;
    P3.strat=strat3;

    for(int i=1; i<=rounds; i++){
        callStrat(decypher(P1.strat), P1, P2, P3, i);
        callStrat(decypher(P2.strat), P2, P1, P3, i);
        callStrat(decypher(P3.strat), P3, P1, P2, i);
        addScore(P1.hist.back(), P2.hist.back(), P3.hist.back());
    }
}
void PD::addScore(int c1, int c2, int c3){
        if(c1==0 && c2==0 && c3==0){
            P1.score+=7;
            P2.score+=7;
            P3.score+=7;
        }
        else if(c1==0 && c2==0 && c3==1){
            P1.score+=3;
            P2.score+=3;
            P3.score+=9;
        }
        else if(c1==0 && c2==1 && c3==0){
            P1.score+=3;
            P2.score+=9;
            P3.score+=3;
        }
        else if(c1==1 && c2==0 && c3==0){
            P1.score+=9;
            P2.score+=3;
            P3.score+=3;
        }
        else if(c1==0 && c2==1 && c3==1){
            P1.score+=5;
            P2.score+=5;
            P3.score+=5;
        }
        else if(c1==1 && c2==0 && c3==1){
            P1.score+=5;
            P2.score+=0;
            P3.score+=5;
        }
        else if(c1==1 && c2==1 && c3==0){
            P1.score+=5;
            P2.score+=5;
            P3.score+=0;
        }
        else if(c1==1 && c2==1 && c3==1){
            P1.score+=1;
            P2.score+=1;
            P3.score+=1;
        }
    
}
void PD::callStrat(int strat, Player &m, Player &o1, Player &o2, int r){
    int choice=0;
    switch (strat){
        case 1:
            m.hist.push_back(allDefect());
            m.d++;
            break;
        case 2: 
            m.hist.push_back(allCooperate());
            m.c++;
            break;
        case 3:
            choice = random();
            m.hist.push_back(choice);
            if (choice==1)
                m.d++;
            else    
                m.c++;
            break;
        case 4:
            choice = goByMajority(r,m,o1,o2);
            m.hist.push_back(choice);
            if(choice==1)
                m.d++;
            else
                m.c++;
            break;
        case 5:
            choice = toughTfT(r,o1,o2);
            m.hist.push_back(choice);
            if(choice==1)
                m.d++;
            else    
                m.c++;
            break;
        case 6:
            choice = softTfT(r,o1,o2);
            m.hist.push_back(choice);
            if(choice==1)
                m.d++;
            else
                m.c++;
            break;
        case 7:
            choice = ATFT(r,o1,o2,0.1);
            m.hist.push_back(choice);
            if(choice == 1)
                m.d++;
            else    
                m.c++;            
            break;
        default:
            std::cout<<"error";
    };
}
void PD::emptyHist(){
    P1.hist.empty();
    P1.score=0;
    P1.d=P1.c=0;
    P2.hist.empty();
    P2.score=0;
    P2.d=P2.c=0;
    P3.hist.empty();
    P3.score=0;
    P3.d=P3.c=0;
}
std::string PD::cypher(int i) const{
    if(i==1)
        return "allDefect";
    else if(i==2)
        return "allCooperate";
    else if(i==3)
        return "random";
    else if(i==4)
        return "goByMajority";
    else if(i==5)
        return "softTfT";
    else if (i==6)
        return "toughTfT";
    else if (i==7)
        return "ATFT";
    else    
        return "error";
}
int PD::decypher(std::string strat) const{
    if(strat=="allDefect")
        return 1;
    else if(strat == "allCooperate")
        return 2;
    else if(strat=="random")
        return 3;
    else if(strat=="goByMajority")
        return 4;
    else if(strat == "softTfT")
        return 5;
    else if (strat == "toughTfT")
        return 6;
    else if (strat=="ATFT")
        return 7;
    else  
        return 0;
}