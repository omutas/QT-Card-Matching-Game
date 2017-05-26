#ifndef CARDMATCHGAME_H
#define CARDMATCHGAME_H

#include <QtGui>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QStringList>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QHeaderView>
#include "thegame.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


namespace std {
class cardMatchGame : public QDialog
{
    Q_OBJECT

public:
    cardMatchGame(QWidget *parent = 0);


signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
    void newGameClicked();
    void prevGameClicked();
    void nextGameClicked();
    void itemClicked(int clicked);
    void updateScore();

private:
    QLabel *gameLabel;
    QLabel *highScoreLabel;
    QLabel *player1Name;
    QLabel *player2Name;
    QLabel *score;
    QLabel *timeLabel;
    QLabel *player1Score;
    QLabel *player1Time;
    QLabel *player2Score;
    QLabel *player2Time;
    QPushButton *newGameButton;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *cardButton1;
    QSignalMapper *signalMapper;
    QGridLayout *bottomLayout = new QGridLayout;
    //QPushButton *buttons[30];
    vector <theGame*> gamesPlayed;
    vector <QPushButton*> itemButtons;
    vector <int> clickedItems;
    theGame *currentGame;
    int gameCounter=1;
    int showResultsCounter=1;
    int highScore=0;
    vector <int> timeHolder;





};
}


#endif // CARDMATCHGAME_H
