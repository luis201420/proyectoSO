#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollArea>

#include <vector>
#include <queue>
#include <QRadioButton>
#include <QInputDialog>

#include "startbutton.h"
#include "grafica.h"

struct Process{
    QString id      ;
    QString colour  ;
    int arriveTime  ;
    int serviceTime ;
    int finalTime   ;
    int priority    ;
    int returnTime  ;
    int waitTime    ;
    Process(QString a,QString b,int c,int d,int e,int f,int g,int h){
        id          = a;
        colour      = b;
        arriveTime  = c;
        serviceTime = d;
        finalTime   = e;
        priority    = f;
        returnTime  = g;
        waitTime    = h;
    }
    Process(){
        id          = "" ;
        colour      = "" ;
        arriveTime  = 0 ;
        serviceTime = 0 ;
        finalTime   = 0 ;
        priority    = 0 ;
        returnTime  = 0 ;
        waitTime    = 0 ;
    }
};

class MainWindow:public QWidget
{
    private:
        int sizeW        ;
        int sizeH        ;
        int processNumber;
        int quantum      ;

        Grafica      * graphic      ;

        QScrollArea  * graphic_area ;
        QTextEdit    * text         ;
        StartButton  * button       ;
        QWidget      * counter      ;
        QWidget      * resultCounter;
        QTableWidget * counterTable ;
        QTableWidget * resultTable  ;
        QLabel       * finalresults ;

        QWidget      * options;
        QRadioButton * option1;
        QRadioButton * option2;
        QRadioButton * option3;

        vector<pair<QString,int>> resultsByGrafic      ;
        vector< pair<QString,pair<int,int>> > results  ;
        vector< Process* > processes,processesConst;

    public:
        MainWindow(int w, int h);

        void iniciar ( );
        void llenar  ( );
        void procesar ( );
        void procesar1 ( );
        void mostrar ( );
        void graficar( );

        void procesar2( );
};

#endif // MAINWINDOW_H
