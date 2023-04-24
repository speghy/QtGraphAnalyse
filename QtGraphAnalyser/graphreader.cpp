#include "graphreader.h"
//_________________GRAPHREADER___________________
void GraphReader::ReadGraph(QStringList *Source,DataGraphTable* Dest)
{  // метод открытия TXT файлов графа
    while(true)
    {
        if(Dest==NULL) //проверки подключения источника/приемника в
        {              //вызывающем классе, если передано NULL - не подключены
            continue;
        }
        if(Source==NULL)
        {
            continue;
        }
        else
        {
            if(Source->empty())
            {
                continue;
            }
            else
            {
                QString PathToFile = Source->takeLast();
                QFile CurrentFile(PathToFile);
                if(CurrentFile.open(QIODevice::ReadOnly))
                {
                   QTextStream TextToRead(&CurrentFile);
                   GraphTable NewGraphTable;
                    int VertexNum=0;

                   TextToRead>>VertexNum;\
                   if(VertexNum<0)                              //Если по какой-то причине введено отрицательное число - зануляем
                   {
                       VertexNum = 0;
                   }
                   NewGraphTable.VertexNumber = VertexNum;      //Если количество вершин не введено
                   if(VertexNum!=0)                             //Граф задан не корректно и игнорируется
                   {                                            //Если VertexNum есть, но нет каких-то цифр
                       for(int i=0;i<VertexNum*VertexNum;i++)   //в матрице они забьются нулями
                       {
                               int InsertedNumber;
                               TextToRead>>InsertedNumber;
                               NewGraphTable.Array.push_back(InsertedNumber);
                               //qDebug()<<InsertedNumber;
                       }
                       qDebug()<<"Pushed One!";
                       Dest->PushDataToBot(NewGraphTable);

                   }
                   else
                   {
                       NewGraphTable.VertexNumber = -1;
                       NewGraphTable.Array.resize(1);
                       NewGraphTable.Array[0]= -1;
                       Dest->PushDataToBot(NewGraphTable);

                   }
                }
            }
        }
    }
}
//________________GRAPHREADERINITIALISER_______________
void GraphReaderInitialiser::Process() // метод запуска чтения графов в отдельном потоке
{
    ReaderToWorkFromThread = new GraphReader();
    if(ReaderToWorkFromThread == NULL) // сигнал finisged сигнализирует о завершении потока
    {                                  // значение false - завершен некорректно
        emit finished(false);          // значение true - завершен корректно
        return;                        // в данный момент никуда не подключен. В дальнейшем подклить к логике завершения программы
    }                                  // для проверки корректности завершения процессов в потоке
    ReaderToWorkFromThread->ReadGraph(TxtsToConvert,GraphsToPushInQueue);
    emit finished(true);
}
void GraphReaderInitialiser::SetTxtsSource(QStringList *Source) // функция передачи указателя на буфер текстовых файлов
{                                                               // нужна чтобы установить соотв. указатель в метод созданного
    TxtsToConvert = Source;                                     // GraphReader'а
}
void GraphReaderInitialiser::SetNumericGraphsDest(DataGraphTable* Dest) // функция передачи указател на буфер файлов графов
{                                                                           // нужна чтобы установить соотв. указатель в метод созданного
    GraphsToPushInQueue = Dest;                                             // GraphReader'а
}
//________________GRAPHREADERTHREADCREATOR______________
void GraphReaderThreadCreator::MakeReaderThread()                           // это нужно по человечески раскоментить
{

    GraphReaderInitialiser* CurrentInitialiser = new GraphReaderInitialiser();
    CurrentInitialiser->SetTxtsSource(TxtsToConvert);
    CurrentInitialiser->SetNumericGraphsDest(GraphsToPushInQueue);
    QThread* thread = new QThread();
    CurrentInitialiser->moveToThread(thread);
    connect(thread,&QThread::started,CurrentInitialiser,&GraphReaderInitialiser::Process);
    connect(CurrentInitialiser,&GraphReaderInitialiser::finished,CurrentInitialiser,&QObject::deleteLater);
    connect(thread,&QThread::finished,thread,&QObject::deleteLater);
    thread->start();
}
void GraphReaderThreadCreator::SetTxtsSource(QStringList *Source)
{
    TxtsToConvert = Source;
}
void GraphReaderThreadCreator::SetNumericGraphsDest(DataGraphTable* Dest)
{
    GraphsToPushInQueue = Dest;
}
