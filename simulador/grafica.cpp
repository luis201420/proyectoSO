#include "grafica.h"

Grafica::Grafica(int x,int y,int w,int h)
{
    this->head=NULL;

    this->proporcion = 10;
    this->speed =5;
    this->posX = 10;
    this->posY = 10;

    this->setGeometry(x,y,w,h);

    this->line = new QLabel(this);
    this->line->setGeometry(10,60,1000,2);
    this->line->setStyleSheet("background-color:#000000;");
}

void Grafica::insertProcess(pair<QString, int> process)
{

    ChronoUI * nuevo=new ChronoUI(this->posX,this->posY,(process.second)*this->proporcion,this->speed,this,process.first);
    if(this->head==NULL){
        this->head=nuevo;
    }
    else{
        ChronoUI * aux=this->head;
        while(aux->getNext()!=NULL){
            aux=aux->getNext();
        }
        aux->setNext(nuevo);
    }
    this->posX+=((process.second)*this->proporcion);
}

void Grafica::comenzar()
{
    if(this->head!=NULL){
        this->head->empezar(20);
    }
}


