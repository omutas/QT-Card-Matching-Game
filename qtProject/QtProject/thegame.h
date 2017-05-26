#ifndef THEGAME_H
#define THEGAME_H
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <item.h>
#include <player.h>
namespace std {
class theGame
{
public:
    theGame();
    const static int numbOfItems = 15;
    const static int rowSize =5;
    const static int colSize =6;
    int gameId;
    int currPlayerId=0;
    void init();
    void listDistribute();
    void setList();
    bool checkMatch(int firstClicked, int secondClicked,int timeWasted);
    void setPlayers();



    string slotValues[numbOfItems] = {"images/ataturk.jpg","images/einstein.jpeg","images/elvis.jpeg",
                                      "images/fatih.jpg","images/gandhi.jpg","images/hitler.jpg",
                                      "images/jesus.jpg", "images/mandela.jpeg", "images/mark.jpg", "images/monroe.jpg",
                                      "images/mozart.jpg", "images/ronaldo.jpg", "images/steve.jpeg", "images/socrat.jpg",
                                      "images/tarantino.jpg"};
    vector <item> slotItems ;
    vector <player> players ;
    item gameBoard[rowSize][colSize];

};
}
#endif // THEGAME_H
