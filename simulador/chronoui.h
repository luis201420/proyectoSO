#ifndef CHRONOUI_H
#define CHRONOUI_H


#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTime>
#include <QTimer>

#include <QDebug>
class ChronoUI : public QWidget
{
  Q_OBJECT

    public:
      ChronoUI(int x,int y,int s,int t,QWidget * p,QString color)
      {
        this->setParent(p);
        this->parent=p;
        this->size = s;
        this->speed=t;
        this->next=NULL;

        this->setGeometry(x,y,this->size,50);

        layout_ = new QHBoxLayout(this);

        layout_->setMargin(0);

        label=new QLabel(this);
        layout_->addWidget(label);
        label->setStyleSheet("background-color:rgb"+color+";");

        layout_->addStretch(this->size);
        this->hide();

      }

      void empezar(int t){
          this->totalSize=t;
          this->show();
          connect(&timer_, SIGNAL(timeout()), SLOT(moveLabel()));
          timer_.start(1000);
      }

      inline void setNext(ChronoUI * n){
          this->next=n;
      }
      inline ChronoUI * getNext(){
          return this->next;
      }


    public slots:
      void moveLabel()
      {
        layout_->setStretch(0, layout_->stretch(0) + this->speed);
        layout_->setStretch(1, layout_->stretch(1) - this->speed);

        this->totalSize+=this->speed;

        if(this->totalSize>=parent->width()){
            parent->resize(parent->width()+10,parent->height());
        }

        if(layout_->stretch(0) >= this->size){
            timer_.stop();
            if(this->next != NULL)this->next->empezar(this->totalSize);
        }
      }

    private:
      QBoxLayout* layout_;
      QTimer timer_;
      QLabel * label;
      ChronoUI * next;
      QWidget * parent;
      int size;
      int speed;
      int totalSize;
};

#endif // CHRONOUI_H
