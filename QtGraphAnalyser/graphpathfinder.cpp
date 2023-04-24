#include "graphpathfinder.h"
#include <QtDeikstraAlgorythm/qtdeikstraalgorythm.h>

//_________________GRAPHPATHFINDER___________________
void GraphPathFinder::BuildPathsMatrix(DataGraphTable* GetGraphFromThere,DataGraphTable* PutPathsMatrixHere)
{
    while(true)
    {
         if(GetGraphFromThere==NULL) //проверки подключения источника/приемника в
         {              //вызывающем классе, если передано NULL - не подключены
            continue;
         }
         if(PutPathsMatrixHere==NULL)
         {
            continue;
         }
         if(!GetGraphFromThere->GetEmpty())
         {
             qDebug()<<"Got One!";
             GraphTable GraphToProcess = GetGraphFromThere->GetDataFromFront();
             if(GraphToProcess.VertexNumber!=-1)
             {
                  qDebug()<<"Graphs to process length = "<<GraphToProcess.VertexNumber;
                 GraphTable NewGraphTable;
                 NewGraphTable.VertexNumber = GraphToProcess.VertexNumber;
                 NewGraphTable.Array.resize(NewGraphTable.VertexNumber*NewGraphTable.VertexNumber);
                 for(int i=0;i<NewGraphTable.VertexNumber;i++)
                 {
                     QtDeikstraAlgorythm GraphProcessor;
                     QVector<int> FromFunc = GraphProcessor.DeikstraAlgorythm(NewGraphTable.VertexNumber,GraphToProcess.Array,i);
                     for(int j =0;j<NewGraphTable.VertexNumber;j++)
                     {
                         NewGraphTable.Array[i*NewGraphTable.VertexNumber + j]= FromFunc[j];
                         qDebug()<<"PM= "<<NewGraphTable.Array[i*NewGraphTable.VertexNumber+j];

                     }
                 }
                 PutPathsMatrixHere->PushDataToBot(NewGraphTable);
             }
             else
             {
                 GraphTable NewGraphTable;
                 NewGraphTable.VertexNumber = -1;
                 NewGraphTable.Array.resize(1);
                 NewGraphTable.Array[0]=-1;
                 PutPathsMatrixHere->PushDataToBot(NewGraphTable);
             }
        }
    }
}

//________________GRAPHPATHFINDERINITIALISER_______________
void GraphPathFinderInitializer::Process()
{
    GraphPathFinderToWorkFromThread = new GraphPathFinder();
    if(GraphPathFinderToWorkFromThread == NULL)
    {
        emit finished(false);
        return;
    }
    GraphPathFinderToWorkFromThread->BuildPathsMatrix(GetGraphFromThere,PutPathsMatrixHere);
    emit finished(true);
}
void GraphPathFinderInitializer::SetToGetGraphGromThere(DataGraphTable* Source)
{
    GetGraphFromThere = Source;
}
void GraphPathFinderInitializer::SetToPutPathsMatrixHere(DataGraphTable* Dest)
{
    PutPathsMatrixHere = Dest;
}


//________________GRAPHPATHFINDERTHREADCREATOR_____________

 void GraphPathFinderThreadCreator::MakePathFinderThread()
 {
     GraphPathFinderInitializer* CurrentInitialiser = new GraphPathFinderInitializer;
     CurrentInitialiser->SetToGetGraphGromThere(GetGraphFromThere);
     CurrentInitialiser->SetToPutPathsMatrixHere(PutPathsMatrixHere);\
     QThread* thread = new QThread;
     CurrentInitialiser->moveToThread(thread);
     connect(thread,&QThread::started,CurrentInitialiser,&GraphPathFinderInitializer::Process);
     connect(CurrentInitialiser,&GraphPathFinderInitializer::finished,CurrentInitialiser,&QObject::deleteLater);
     connect (thread,&QThread::finished,thread,&QObject::deleteLater);
     thread->start();
 }

 void GraphPathFinderThreadCreator::SetToGetGraphFromThere(DataGraphTable* Source)
 {
     GetGraphFromThere= Source;
 }
 void GraphPathFinderThreadCreator::SetToPutPathsMatrixHere(DataGraphTable* Dest)
 {
     PutPathsMatrixHere = Dest;
 }
