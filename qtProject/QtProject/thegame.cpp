#include "thegame.h"
using namespace std;
theGame::theGame()
{

}

void theGame::init(){
    setList();
    listDistribute();
    setPlayers();
}

void theGame::listDistribute(){
    srand(time(0));
    int posItem;
    for(int i=0; i<rowSize; i++){
        for(int j=0; j<colSize; j++){
            if(slotItems.size()>1) posItem= rand()%(slotItems.size());
            else posItem=0;
            slotItems[posItem].incCount();
            gameBoard[i][j]= slotItems[posItem];
            if(!slotItems[posItem].isAvailable){
                slotItems.erase(slotItems.begin()+posItem);

            }
        }
    }
}

void theGame::setList(){
    for(int i = 0; i<numbOfItems;i++){
        slotItems.push_back(item(slotValues[i]));
        //cout<< slotItems[i].value<<endl;
    }
}

bool theGame::checkMatch(int _firstClicked, int _secondClicked,int timeWasted){
    int firstRow=_firstClicked/colSize;
    int firstCol=_firstClicked%colSize;
    int secondRow=_secondClicked/colSize;
    int secondCol=_secondClicked %colSize;
    item firstItem = gameBoard[firstRow][firstCol];
    item secondItem=gameBoard[secondRow][secondCol];
    players[currPlayerId].totalTime+=timeWasted;
    if(firstItem.value==secondItem.value&& _firstClicked!=_secondClicked){
        firstItem.isMatched=true;
        secondItem.isMatched=true;
        players[currPlayerId].score++;
        currPlayerId = (currPlayerId+1)%2;
        return true;

    }
    currPlayerId = (currPlayerId+1)%2;
    return false;

}

void theGame::setPlayers(){
    players.push_back(player("Player1"));
    players.push_back(player("Player2"));
}



