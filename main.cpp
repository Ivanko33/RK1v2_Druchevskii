#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;



QByteArray fileData;
void ReadFromFile(const char* fileName) {

    QFile f(fileName);
    f.open(QIODevice::ReadOnly);
    if (!f.exists()){
        qDebug()<<"file don't exists";
    }
    if (!f.isOpen()){
        qDebug()<<"file is not open";
    }
    else{
        qDebug()<<"file open-Success";
    }
    fileData = f.readAll();

    f.close();
}

void WriteToFile(const int* ar, int size) {
        ofstream f1;
        f1.open("resulttask1.txt");
        if (!f1.is_open()){
            qDebug()<<"Error";
        }
        else{
            for (int i=0;i<256;i++){
                f1<<i<<"\t"<<char(i)<<"\t"<<ar[i]<<"\n";
            }
        }
}

void task1() {
    ReadFromFile("text.txt");

    int ar[256];
    memset(&ar[0], 0x00, sizeof(int) * 256);

    for (int i = 0; i < fileData.size(); i++) {
        ar[(fileData[i])]++;
    }
   WriteToFile(&ar[0],256);
}





char binNumb[32];
void perevod2(int numDecimal) {
    memset(binNumb, 0x00, 32 * sizeof(int));

    for (int i = 0; i < 32; i++) {
        binNumb[32-i-1] = ((numDecimal & (1 << i))) ? 0x31 : 0x30;
    }
}

void task2() {
    perevod2(7567);
    qDebug() << binNumb;
}






QString perevod3 (char* str){
    QString stroka;
    int count=-1;
    for(int i=3;i<159;i=i+4){
        if(str[i]=='1'){
            stroka+="1";
            count++;
        }
        if(str[i]=='0'){
            stroka+="0";
            count++;
        }
        i++;

    }
    int count1=count;
    unsigned int summa=0;

    for(int i=0;i<=count;i++){
        if (stroka[i]=='1'){

            summa+=pow(2,count1);
            count1-=1;
        }
        if (stroka[i]=='0'){
            count1-=1;
        }
    }
 //   qDebug()<<stroka;
 //   qDebug()<<summa;
    QString strokafin;
    strokafin=QString("%1");
    strokafin=strokafin.arg(summa,32,16);
    return strokafin;

}

void task3(){
    char s[]={"0x31 0x31 0x31 0x31 0x31 0x31 0x31"};
    QString strokafin=perevod3(s);
    QFile f("resulttask3.txt");
    f.open(QIODevice::WriteOnly);
    if (!f.exists()){
        qDebug()<<"resultask3 No exists";
    }
    else{
        QTextStream writeStream(&f);
        writeStream<<(strokafin);
        }

      f.close();
      cout<<"task3 file was written successful"<<endl;
      }





void buildTree(int height){
    int col=1;
    int probel=height-1;
    for(int i=1;i<=height;i++){
        for(int j=1;j<=probel;j++){
            cout<<" ";
        }
        for(int j=1;j<=col;j++){
            cout<<"*";
        }
        cout<<endl;
        col+=2;
        probel-=1;
    }
}

void task4(){
    buildTree(8);
}





QList<float> getAverStr(int* ar, int rows, int cols) {
    QList<float> averStr;

    for (int i = 0; i < rows; i++) {
        float averStr_temp = 0;
        for (int j = 0; j < cols; j++) {
            averStr_temp += ar[i*cols + j] / (float)cols;
        }
        averStr.push_back(averStr_temp);
    }
    return averStr;
}

void task5() {
    int ar[2][4]={{1,2,3,4},{3,4,5,6}};

    QList<float> b=getAverStr(*ar,2,4);
    qDebug()<<b;
}





struct Node  {
    Node* next;
    Node* prev;
    int nameNode;
    static int countNodes;
};
class LinkedList {
    private :
        Node* Head;
        Node* Tail;
    public :
        LinkedList(){
            Head=nullptr;
            Tail=nullptr;
      //      cout<<"list created"<<endl;
        }
        ~LinkedList(){
            while(Head!=nullptr){
                Tail=Head->next;
                delete Head;
                Head=Tail;
            }
        };

        void push_back(int nameNode){
            Node* tempnode=new Node;
            tempnode->nameNode=nameNode;
            tempnode->next=nullptr;
            if(Head==nullptr){


                 tempnode->prev=nullptr;
                 Head=tempnode;
                 Tail=tempnode;
             //    cout<<"first ok"<<endl;

            }
            else{
                tempnode->prev=Tail;
                Tail->next=tempnode;
                Tail=tempnode;
            }
        }
        void print(){
            Node *current = Head;
                    while(current != nullptr)
                    {
                        cout << current->nameNode << endl;
                        current = current->next;
                    }
        }

        void writeToFileFromTail(){
            QFile f("task6.txt");
            f.open(QIODevice::WriteOnly);
            if (!f.exists()){
                qDebug()<<"task6 No exists";
            }
            else{
                QTextStream writeStream(&f);
                Node* current=Tail;
                while(current!=nullptr){
                    writeStream<<(current->nameNode)<<"\n";
                    current=current->prev;
                }
                cout<<"task6 wrote from Tail"<<endl;
              }

           f.close();

        }

        void writeToFileFromHead(){

            QFile f("task6.txt");
            f.open(QIODevice::WriteOnly);
            if (!f.exists()){
                qDebug()<<"task6 No exists";
            }
            else{
                QTextStream writeStream(&f);
                Node* current=Head;
                while(current!=nullptr){
                    writeStream<<(current->nameNode)<<"\n";
                    current=current->next;
                }
                cout<<"task6 wrote from Head"<<endl;
              }

           f.close();

        }
        void insert(int nameNode, int position){
            Node* tempnode=new Node;
            tempnode->nameNode=nameNode;
            Node* currnode= Head;
            int count =1;
            for (int i=1; i<position-1 && currnode->next!=nullptr;i++ ){
                currnode=currnode->next;
                count++;
            }
            if (position - count >1 || position <1){
                qDebug()<<"Wrong position";
                return;
            }
            else{
                if (position==1){
                    tempnode->prev=nullptr;
                    tempnode->next=Head;
                    Head->prev=tempnode;
                    Head=tempnode;

                }
                else{
                    if(currnode->next==nullptr){
                        tempnode->next=nullptr;
                        tempnode->prev=Tail;
                        Tail->next=tempnode;

                        Tail=tempnode;
                    }
                    else{
                        tempnode->next=currnode->next;
                        currnode->next=tempnode;
                        tempnode->prev=currnode;

                   }
                }
           }
        }
};


void task6(){
    LinkedList s;
    s.push_back(45);
    s.push_back(34);
    s.push_back(32);
    s.writeToFileFromHead();
 //   s.writeToFileFromTail();
}



void task7(){
    LinkedList s;
    s.push_back(45);
    s.push_back(34);
    s.push_back(32);
    s.insert(10000,2);
}


class StudentInfo {
        private :
            tuple<QString /*фамилия*/,QString /*имя*/,char* /*№ студ билета*/> info;
            QMap<QString/*название предмета*/, QPair<QList<int> /*список оценок*/, float /*средняя оценка*/>> subjMark;
        public :
            StudentInfo(){
                get<0>(info)="Druchevskii";
                get<1>(info)="Ivan";
                get<2>(info)="1234";
            }
            StudentInfo(QString surname, QString name,char* number){
                get<0>(info)=surname;
                get<1>(info)=name;
               get<2>(info)=number;
            }

            int addMark(const QString& subjName, int mark){
                int count=0;
                for (QMap<QString,QPair<QList<int>,float>>::iterator iter=subjMark.begin();iter!=subjMark.end();iter++){
                    if (iter.key()==subjName){
                       count++;
                       iter.value().first.append(mark);
                       float l=iter.value().first.size();
                       float summa=0;
                       for (int i=0;i<l;i++){
                          summa+=(iter.value().first[i]/l);
                       }
                       iter.value().second=summa;
                       cout<<" 0-predmet est,ocenka dobavlema"<<endl;
                       return 0;
                    }
                }
                if (count==0){
                    cout<<"1-predmet net"<<endl;
                    return 1;
                }


            }



            int addSubj(const QString& subjName){
             //    int count=0;
                for (QMap<QString,QPair<QList<int>,float>>::iterator iter=subjMark.begin();iter!=subjMark.end();iter++){
                     if (iter.key()==subjName){
                         cout<<"1-Predmet est"<<endl;
                         return 1;
                     }
                 }
                QPair<QList<int>,float> pair;
                subjMark.insert(subjName,pair);
                cout<<"0-Predmet dobavlen"<<endl;
                return 0;
            }

            float getAverMark(const QString& subjName){
                for (QMap<QString,QPair<QList<int>,float>>::iterator iter=subjMark.begin();iter!=subjMark.end();iter++){
                    if (iter.key()==subjName){
                        return iter.value().second;
                    }
                }
            }

            void printInfoStudent(){
                QString surname = get<0>(info);
                QString name = get<1>(info);
                QString number = get<2>(info);
                    cout<<surname.toStdString()<<"\t"<<name.toStdString()<<"\t"<<number.toStdString()<<endl;
                    QMap<QString,QPair<QList<int>,float>>::iterator iter;
                    for(QMap<QString,QPair<QList<int>,float>>::iterator iter=subjMark.begin();iter!=subjMark.end();iter++)
                    {
                        QString pr = iter.key();
                        cout<<pr.toStdString()<<"\t";
                        foreach(int valu,iter.value().first)
                        {
                            cout <<"\t"<< valu;
                        }
                        getAverMark(iter.key());
                        cout<<"\t"<<" average - "<<iter.value().second;
                        cout<<endl;

                    }
            }

            void writeAllInfoToFile(){
                QFile f("result_task8.txt");
                f.open(QIODevice::WriteOnly);
                if (!f.exists()){
                    qDebug()<<"resultask3 No exists";
                }
                else{
                    QTextStream writeStream(&f);
                    writeStream<<"["<<get<0>(info)<<"]"<<"\t"<<"["<<get<1>(info)<<"]"<<" "<<":"<<" "<<"["<<get<2>(info)<<"]"<<"\n";
                     for (QMap<QString,QPair<QList<int>,float>>::iterator iter=subjMark.begin();iter!=subjMark.end();iter++){
                        writeStream<<"["<<iter.key()<<"]"<<" "<<":"<<" ";
                        foreach(int valu,iter.value().first){
                            writeStream<<"["<<valu<<"]"<<", ";
                        }
                        writeStream<<"--"<<iter.value().second<<"\n";
                     }
               }

              f.close();
            }
    };

void task8(){
    StudentInfo student;
    student.addSubj("Math");
    student.addMark("Math",3);
    student.addMark("Math",4);
    student.addMark("Mаth",5);
    student.writeAllInfoToFile();
}


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"rus");
    QCoreApplication a(argc, argv);

    task1();

    task2();

    task3();

    task4();

    task5();

    task6();

    task7();

    task8();



    return 0;
}
