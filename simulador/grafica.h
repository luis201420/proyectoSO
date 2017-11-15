#ifndef GRAFICA_H
#define GRAFICA_H

#include <QWidget>

#include <utility>

#include "chronoui.h"

using namespace std;

class Grafica:public QWidget
{
    private:
        ChronoUI * head;
        QLabel * line;
        int proporcion;
        int speed;
        int posX;
        int posY;

    public:
        Grafica(int x, int y, int w, int h);
        void insertProcess(pair<QString,int> process);
        void comenzar();
};

#endif // GRAFICA_H
