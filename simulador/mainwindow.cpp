#include "mainwindow.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

MainWindow::MainWindow(int w,int h)
{
    this->resize(w,h);

    this->sizeW=w;
    this->sizeH=h;

    srand (time(NULL));

/** ------------------------TEXTO------------------------- **/

    QLabel *label = new QLabel(this);
    QHBoxLayout *layout = new QHBoxLayout();
    label->setText("Numero de Procesos: ");
    layout->addWidget(label);

    int posTextX=(0.04)*(this->sizeH);
    int posTextY=(0.02)*(this->sizeW);
    int textWidth=120;
    int textHeight=15;

    label->setGeometry(posTextX,posTextY,textWidth,textHeight);

/** -----------------------TEXT EDIT----------------------- **/

    this->text = new QTextEdit();
    this->text->setParent(this);
    this->text->setGeometry((posTextX+textWidth),(posTextY-5),60,30);
    this->text->setStyleSheet("background-color:#FFFFFF;");

/** ------------------------BUTTON-------------------------- **/

    this->button = new StartButton(this,((posTextX+textWidth)+70),((posTextY-5)));

/** ---------------------- OPTIONS -------------------------- **/
    this->options = new QWidget(this);
    this->options->setGeometry((posTextX+textWidth)-90,(posTextY-5)+40,200,72);

    this->option1 = new QRadioButton("FCFS", this->options);       this->option1->setGeometry(0, 0,200,24);
    this->option2 = new QRadioButton("SJF", this->options);       this->option2->setGeometry(0,24,200,24);
    this->option3 = new QRadioButton("Round Robin", this->options);this->option3->setGeometry(0,48,200,24);


/** -----------------MOSTRADOR DE DATOS--------------------- **/

    this->counter = new QWidget(this);
    this->counter->setGeometry(posTextX+30,(posTextY+textHeight+100),(0.4*this->sizeW),(0.5*this->sizeH));
    this->counter->setStyleSheet("background-color:#FFFFFF;");

/** -----------------------TABLE---------------------------- **/
    this->counterTable= new QTableWidget(counter);
    this->counterTable->setColumnCount(4);
    this->counterTable->resize(counter->width(),counter->height());
    QStringList tableHeader1;
    tableHeader1<<"ID Proceso"<<"Tiempo llegada"<<"Duracion"<<"Color";
    this->counterTable->setHorizontalHeaderLabels(tableHeader1);
    this->counterTable->horizontalHeader()->setStretchLastSection(true);

/** -----------------PANEL DE RESULTADOS---------------------- **/

    this->resultCounter = new QWidget(this);
    this->resultCounter->setGeometry((posTextX+(0.4*this->sizeW)+100),(posTextY+textHeight+100),(0.4*this->sizeW),(0.5*this->sizeH));
    this->resultCounter->setStyleSheet("background-color:#FFFFFF;");

/** ------------------------TABLE------------------------------ **/
    this->resultTable = new QTableWidget(resultCounter);
    this->resultTable->setColumnCount(4);
    this->resultTable->resize(resultCounter->width(),resultCounter->height());
    QStringList tableHeader2;
    tableHeader2<<"ID Proceso"<<"Tiempo Retorno"<<"Tiempo Final"<<"Tiempo Espera";
    this->resultTable->setHorizontalHeaderLabels(tableHeader2);
    this->resultTable->horizontalHeader()->setStretchLastSection(true);



/** -----------------------GRAFICA------------------------ **/

    this->graphic=new Grafica(w/20,3*(h/4),w*0.9,h/6);
    this->graphic->setStyleSheet("background-color:white;");

    this->graphic_area = new QScrollArea(this);

    this->graphic_area->setGeometry(w/20,3*(h/4),w*0.9,h/6);
    this->graphic_area->setWidget(this->graphic);
    this->graphic_area->setWidgetResizable(false);
    this->graphic_area->show();

/** -----MOSTRADOR DE RESULTADOS FINALES DEL ALGORITMO---- **/

    this->finalresults = new QLabel(this);
    this->finalresults->setGeometry((posTextX+(0.4*this->sizeW)+100),(posTextY-10),(0.4*this->sizeW),50);
}

bool isNumber(QString a){
    for(int i=0;i<a.size();i++){
        if(a[i]<'0' || a[i]>'9')return false;
    }
    return true;
}

void MainWindow::iniciar()
{
    QString cont=(this->text)->toPlainText();
    QMessageBox msgBox;
    if(cont.isEmpty()){
        msgBox.setText("Asegurese de haber puesto un valor.");
        msgBox.exec();
    }
    else if(isNumber(cont)){
         if(cont.toInt()>100 || cont.toInt()==0){
             msgBox.setText("Asegurese de haber puesto un valor entre [1-100].");
             msgBox.exec();
         }
         else{
             if(this->option1->isChecked() || this->option2->isChecked() || this->option3->isChecked()){
                 this->processNumber=cont.toInt();
                 this->llenar();
                 if(this->option1->isChecked()) this->procesar1();
                 if(this->option2->isChecked()) this->procesar();
                 if(this->option3->isChecked()){
                     bool ok;
                     QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                            tr("Quantum:"), QLineEdit::Normal,
                                                            " ", &ok);
                    if (ok && !text.isEmpty()){
                        if(isNumber(text)){
                            this->quantum=text.toInt();
                            this->procesar2();
                        }
                        else{
                            msgBox.setText("Asegurese de haber ingresado un numero.");
                            msgBox.exec();
                        }
                    }
                 }
             }
             else{
                 msgBox.setText("Asegurese de haber seleccionado un algoritmo planificador.");
                 msgBox.exec();
             }
         }
    }
    else{
        msgBox.setText("El valor puesto es incorrecto.");
        msgBox.exec();
    }
}

void MainWindow::llenar()
{
    this->counterTable->setRowCount(this->processNumber);
    this->processes.clear();
    Process * nuevo1, *nuevo2;

    int r,g,b;
    for(int i=1;i<=(this->processNumber);i++){
        r=(rand() % 155) +100;
        g=(rand() % 155) +100;
        b=(rand() % 155) +100;

        QString id ="P"+QString::number(i);
        int t1=rand() % int(ceil((this->processNumber*2.0)/3.0)+1);
        int t2=(rand() % 10) +1;

        this->counterTable->setItem((i-1), 0, new QTableWidgetItem(id));
        this->counterTable->setItem((i-1), 1, new QTableWidgetItem(QString::number(t1)));
        this->counterTable->setItem((i-1), 2, new QTableWidgetItem(QString::number(t2)));
        this->counterTable->setItem((i-1), 3 ,new QTableWidgetItem());

        this->counterTable->item((i-1), 3)->setBackground(QColor(r,g,b));

        nuevo1=new Process(id,"("+QString::number(r)+","+QString::number(g)+","+QString::number(b)+")",t1,t2,0,0,0,0);
        this->processes.push_back(nuevo1);

        nuevo2=new Process(id,"("+QString::number(r)+","+QString::number(g)+","+QString::number(b)+")",t1,t2,0,0,0,0);
        this->processesConst.push_back(nuevo2);
    }
}

bool verificar(vector<bool> a){
    for(unsigned i=0;i<a.size();i++){
        if(!a[i])return true;
    }
    return false;
}

void FindByTime(vector< Process*> a,int t,vector<Process*>& b){
    b.clear();
    for(unsigned i=0;i<a.size();i++){
        if(a[i]->arriveTime == t){
            b.push_back(a[i]);
        }
    }
}

class Compare
{
public:
    bool operator() (Process* a, Process* b)
    {
        return a->serviceTime > b->serviceTime;
    }
};

bool comp (Process* a, Process* b)
{
    return a->arriveTime < b->arriveTime;
}

void MainWindow::procesar1()
{
    vector< Process*> fifo=this->processes;
    sort(fifo.begin(),fifo.end(),comp);

    int t_actual=0;
    int t_final;
    int t_entrega;
    for(auto i:fifo){
        t_final=t_actual+(i->serviceTime);
        t_entrega=t_final-i->arriveTime;
        this->results.push_back(make_pair((i->id),make_pair(t_final,t_entrega)));
        t_actual=t_final;
        this->resultsByGrafic.push_back(make_pair(i->colour,i->serviceTime));

    }
    this->graficar();
    this->mostrar();


}

void MainWindow::procesar()
{
    vector< Process*> resF;
    vector< Process*> aux=this->processes;
    vector <bool> terminados=vector<bool>(this->processNumber,0);

    priority_queue<Process*, vector<Process*>, Compare> pq;
    Process * aux2;

    int id;

    int t=0,cont=0;
    int t_final;
    int t_entrega;

    while(verificar(terminados)){
        FindByTime(aux,t,resF);
        for(unsigned i=0;i<resF.size();i++){
            pq.push(resF[i]);
        }

        aux2=pq.top();

        //graficar id
        if(((aux2->id).mid(1)).toInt() != (id+1) && t!=0){
            qDebug()<<id+1;
            this->resultsByGrafic.push_back(make_pair(aux[id]->colour,cont));
            cont=0;
        }

        id=((aux2->id).mid(1)).toInt();
        id--;
        if(aux[id]->serviceTime == 0){
            terminados[id]=1;
            t_final=t;
            t_entrega=t-(aux[id]->arriveTime);
            this->results.push_back(make_pair(((this->processes[id])->id),make_pair(t_final,t_entrega)));
            pq.pop();

        }else{
            cont++;
            aux[id]->serviceTime--;
            t++;
        }
    }

    this->resultsByGrafic.push_back(make_pair(aux[id]->colour,cont));
    qDebug()<<this->resultsByGrafic.size();
    this->graficar();
    this->mostrar();
}

void MainWindow::procesar2()
{
    vector< Process*> resF;
    vector< Process*> aux=this->processes;
    vector <bool> terminados=vector<bool>(this->processNumber,0);

    queue<Process*> pq;
    Process * aux2;

    int id;

    int t=0,cont=0;
    int t_final;
    int t_entrega;

    while(verificar(terminados)){
        FindByTime(aux,t,resF);
        for(unsigned i=0;i<resF.size();i++){
            pq.push(resF[i]);
        }

        aux2=pq.front();

        //graficar id
        if(((aux2->id).mid(1)).toInt() != (id+1) && t!=0){
            qDebug()<<id+1;
            this->resultsByGrafic.push_back(make_pair(aux[id]->colour,cont));
            cont=0;
        }

        id=((aux2->id).mid(1)).toInt();
        id--;

        if(aux[id]->serviceTime == 0){
            terminados[id]=1;
            t_final=t;
            t_entrega=t-(aux[id]->arriveTime);
            this->results.push_back(make_pair(((this->processes[id])->id),make_pair(t_final,t_entrega)));
            pq.pop();

        }else{
            if((cont+1)%this->quantum==0){
                pq.pop();
                pq.push(aux[id]);
            }
            else{
                aux[id]->serviceTime--;
            }
            cont++;
            t++;
        }
        qDebug()<<"a";
    }

    this->resultsByGrafic.push_back(make_pair(aux[id]->colour,cont));
    qDebug()<<this->resultsByGrafic.size();
    this->graficar();
    this->mostrar();
}

#include <string>

void MainWindow::mostrar()
{
    this->resultTable->setRowCount(this->processNumber);

    for(unsigned int i=0;i<(this->results.size());i++){

        QString id =(this->results[i]).first;
        int t1=((this->results[i]).second).second;
        int t2=((this->results[i]).second).first;
        int t4=this->processesConst[(id.rightRef(id.length()-1)).toInt()-1]->serviceTime;
        qDebug()<<"id="<<(id.rightRef(id.length()-1)).toInt()-1<<"t4="<<t4;

        this->resultTable->setItem(i, 0, new QTableWidgetItem(id));
        this->resultTable->setItem(i, 1, new QTableWidgetItem(QString::number(t1)));
        this->resultTable->setItem(i, 2, new QTableWidgetItem(QString::number(t2)));
        this->resultTable->setItem(i, 3, new QTableWidgetItem(QString::number(t1-t4)));
    }
}

void MainWindow::graficar()
{
    for(unsigned i=0;i<this->resultsByGrafic.size();i++){
        this->graphic->insertProcess(this->resultsByGrafic[i]);
    }
    this->graphic->comenzar();
}
