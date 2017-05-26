#include "cardmatchgame.h"

using namespace std;
cardMatchGame::cardMatchGame(QWidget *parent) : QDialog(parent)
{

    gameLabel = new QLabel(tr("Game No: "));
    highScoreLabel = new QLabel(tr("Highest Score: "));
    score = new QLabel(tr("Score"));
    timeLabel = new QLabel(tr("Time"));
    player1Name = new QLabel(tr("Player 1"));
    player1Score = new QLabel(tr("0"));
    player1Time = new QLabel(tr("0"));
    player2Name = new QLabel(tr("Player 2"));
    player2Score = new QLabel(tr("0"));
    player2Time = new QLabel(tr("0"));

    newGameButton = new QPushButton(tr("New Game"));

    previousButton = new QPushButton(tr("Previous Results"));
    nextButton = new QPushButton(tr("Next Results"));
    previousButton->setDisabled(true);
    nextButton->setDisabled(true);

    connect(newGameButton,SIGNAL(clicked()),this,SLOT(newGameClicked()));
    connect(previousButton,SIGNAL(clicked()),this,SLOT(prevGameClicked()));
    connect(nextButton,SIGNAL(clicked()),this,SLOT(nextGameClicked()));

    QVBoxLayout *startLeftLayout = new QVBoxLayout;
    startLeftLayout->addWidget(gameLabel);
    startLeftLayout->addWidget(highScoreLabel);

    QVBoxLayout *startRightLayout = new QVBoxLayout;
    startRightLayout->addWidget(newGameButton);
    startRightLayout->addWidget(previousButton);
    startRightLayout->addWidget(nextButton);
    startRightLayout->addStretch();

    QHBoxLayout *topRightLayout = new QHBoxLayout;
    topRightLayout->addLayout(startLeftLayout);
    topRightLayout->addLayout(startRightLayout);

    QGridLayout *scoreTable = new QGridLayout;
    scoreTable->addWidget(player1Name,0,1);
    scoreTable->addWidget(player2Name,0,2);
    scoreTable->addWidget(score,1,0);
    scoreTable->addWidget(player1Score,1,1);
    scoreTable->addWidget(player2Score,1,2);
    scoreTable->addWidget(timeLabel,2,0);
    scoreTable->addWidget(player1Time,2,1);
    scoreTable->addWidget(player2Time,2,2);

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addLayout(scoreTable);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(topLeftLayout);
    topLayout->addLayout(topRightLayout);

    QWidget *top = new QWidget;
    top->setLayout(topLayout);
    top->setMaximumHeight(100);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(top);
    mainLayout->setAlignment(top,Qt::AlignTop);
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Card Match Game"));
    //setFixedHeight(sizeHint().height());
}
/**
 * @brief cardMatchGame::newGameClicked ends the current game and creates a new game
 */
void cardMatchGame::newGameClicked(){

    theGame *createdGame = new theGame();
    clickedItems.clear();
    itemButtons.clear();
    timeHolder.clear();
    createdGame->init();
    createdGame->gameId=gameCounter;
    currentGame=createdGame;
    gameLabel->setText(QString("Game No: %1").arg(createdGame->gameId));
    updateScore();
    player1Score->setText(QString("%1").arg(createdGame->players[0].score));
    player2Score->setText(QString("%1").arg(createdGame->players[1].score));
    player1Time->setText(QString("%1").arg(createdGame->players[0].totalTime));
    player2Time->setText(QString("%1").arg(createdGame->players[1].totalTime));
    highScoreLabel->setText(QString("High Score: %1").arg(highScore));
    player1Name->setStyleSheet("QLabel { color : red; font-weight:900 }");
    player2Name->setStyleSheet("QLabel { color : #000 ;font-weight:700 }");

    signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(itemClicked(int)));
    for(int i=0;i<5;i++){
        for (int j = 0; j < 6; j++) {
            QPixmap pixmap("images/question.png");
            QIcon buttonIcon(pixmap);
            cardButton1 = new QPushButton();
            cardButton1->setIcon(buttonIcon);
            cardButton1->setIconSize(QSize(80,80));
            cardButton1->setFixedSize(QSize(80,80));
            itemButtons.push_back(cardButton1);
            connect(cardButton1,SIGNAL(clicked()),signalMapper,SLOT(map()));
            signalMapper->setMapping(cardButton1,i*6+j);
            bottomLayout->addWidget( cardButton1,i,j );

        }

    }

    gamesPlayed.push_back(createdGame);
    showResultsCounter=gameCounter;
    gameCounter++;
    if(showResultsCounter>1)previousButton->setDisabled(false);

}
/**
 * @brief cardMatchGame::updateScore update user score labels and high score labels on each move
 */
void cardMatchGame::updateScore(){
    player1Score->setText(QString("%1").arg(currentGame->players[0].score));
    if(currentGame->players[0].score>highScore){
        highScore=currentGame->players[0].score;
    }
    player2Score->setText(QString("%1").arg(currentGame->players[1].score));
    if(currentGame->players[1].score>highScore){
        highScore=currentGame->players[1].score;

    }
    highScoreLabel->setText((QString("Highest Score: %1").arg(highScore)));
}

/**
 * @brief cardMatchGame::itemClicked makes neccessary operations when the item is clicked
 * @param _clicked clicked items position
 */
void cardMatchGame::itemClicked(int _clicked){
    /**
     * @brief i row position on array
     */
    int i = _clicked/currentGame->colSize;
    /**
     * @brief j column position on array
     */
    int j = _clicked%currentGame->colSize;
    QPixmap pixmap(QString::fromStdString(currentGame->gameBoard[i][j].value));
    QIcon buttonIcon(pixmap);

    itemButtons[_clicked]->setIcon(buttonIcon);

    itemButtons[_clicked]->repaint();

    clickedItems.push_back(_clicked);
    bool isMatched=0;
    /**
     * @brief timeOnClick current time stamp when user clicked
     */
    int timeOnClick = time(0);
    timeHolder.push_back(timeOnClick);


    /**
     * @brief firstButtonIndex item that is clicked first
     */
    int firstButtonIndex = clickedItems[0];
    /**
     * @brief secondButtonIndex item that is clicked second
     */
    int secondButtonIndex = clickedItems[1];


    if(clickedItems.size()==2){
        /**
          * If two items are clicked
          */
        isMatched = currentGame->checkMatch(clickedItems[0],clickedItems[1],(timeHolder[1]-timeHolder[0]));
        for(int wait=0;wait<200000000;wait++);
        if(isMatched){
            updateScore();
            itemButtons[firstButtonIndex]->setDisabled(true);
            itemButtons[secondButtonIndex]->setDisabled(true);

        }
        else{
            /**
             * if the items are not matched, set icon as question.png
             */
            QPixmap pixmap("images/question.png");
            QIcon buttonIcon(pixmap);

            itemButtons[firstButtonIndex]->setIcon(buttonIcon);
            itemButtons[secondButtonIndex]->setIcon(buttonIcon);

        }
        /**
          * updates user total time and set indicator whose turn is active
          */
        player1Time->setText(QString("%1").arg(currentGame->players[0].totalTime));
        player2Time->setText(QString("%1").arg(currentGame->players[1].totalTime));
        if(currentGame->currPlayerId == 0){
            player1Name->setStyleSheet("QLabel { color : red; font-weight:900 }");
            player2Name->setStyleSheet("QLabel { color : #000 ;font-weight:700 }");
        }else{
            player1Name->setStyleSheet("QLabel { color : #000 ;font-weight:700}");
            player2Name->setStyleSheet("QLabel { color : red ;font-weight:900}");
        }
        clickedItems.clear();
        timeHolder.clear();

    }
}
/**
 * @brief cardMatchGame::prevGameClicked makes necessary operations when previous game button is clicked
 */
void cardMatchGame::prevGameClicked(){
    nextButton->setDisabled(false);

    theGame *checkGame = new theGame();
    if(showResultsCounter>1){
        checkGame = gamesPlayed[showResultsCounter-2];
        gameLabel->setText(QString("Game No: %1").arg(checkGame->gameId));
        player1Score->setText(QString("%1").arg(checkGame->players[0].score));
        player2Score->setText(QString("%1").arg(checkGame->players[1].score));
        player1Time->setText(QString("%1").arg(checkGame->players[0].totalTime));
        player2Time->setText(QString("%1").arg(checkGame->players[1].totalTime));
        highScoreLabel->setText(QString("High Score: %1").arg(highScore));
        showResultsCounter--;
    }
    if(showResultsCounter==1){
        previousButton->setDisabled(true);
    }
}
/**
 * @brief cardMatchGame::nextGameClicked makes neccessary operations when next Game button is clicked
 */
void cardMatchGame::nextGameClicked(){
    previousButton->setDisabled(false);

    theGame *checkGame = new theGame();
    if(showResultsCounter<gamesPlayed.size()){
        checkGame = gamesPlayed[showResultsCounter];
        gameLabel->setText(QString("Game No: %1").arg(checkGame->gameId));
        player1Score->setText(QString("%1").arg(checkGame->players[0].score));
        player2Score->setText(QString("%1").arg(checkGame->players[1].score));
        player1Time->setText(QString("%1").arg(checkGame->players[0].totalTime));
        player2Time->setText(QString("%1").arg(checkGame->players[1].totalTime));
        highScoreLabel->setText(QString("High Score: %1").arg(highScore));
        showResultsCounter++;
    }
    if(showResultsCounter==currentGame->gameId){
        nextButton->setDisabled(true);
    }


}
