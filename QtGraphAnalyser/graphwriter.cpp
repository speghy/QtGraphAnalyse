#include "graphwriter.h"

//_________________GRAPHWRITER___________________
void GraphWriter::WriteGraph(DataGraphTable* GetPathsMatrixFromHere,QString PathToFolderInWhichToSave)
{
    int NumericIdentificatorOfFile;

    QSettings IdSettings("AVoronin","QtGraphAnalyser");
    if(IdSettings.contains("GraphId"))
    {
       NumericIdentificatorOfFile = IdSettings.value("GraphId").toInt();
    }
    else
    {
        IdSettings.setValue("GraphId",0);
        NumericIdentificatorOfFile = 0;
    }

    while(true)
    {

       if(GetPathsMatrixFromHere==NULL)
       {
           continue;
       }
       if(PathToFolderInWhichToSave==NULL)
       {
           continue;
       }
       if(!GetPathsMatrixFromHere->GetEmpty())
       {
           QString SavingName = "Processed_Path_Matrix";
           QString Txt = ".txt";
           GraphTable GraphToWrite = GetPathsMatrixFromHere->GetDataFromFront();

           QString FinalPath = PathToFolderInWhichToSave + SavingName+QString::number(NumericIdentificatorOfFile) + Txt;
           qDebug()<<"Final path = "<<FinalPath;
           QFile FileToSawePathsMatrix(FinalPath);
           if(FileToSawePathsMatrix.open(QIODevice::WriteOnly| QIODevice::Append))
           {
            QTextStream TextToWrite(&FileToSawePathsMatrix);
            if(GraphToWrite.VertexNumber!=-1)   //в случае если файл не битый
            {
                TextToWrite<<GraphToWrite.VertexNumber<<endl;
                for(int i =0;i<GraphToWrite.VertexNumber;i++)
                {
                    for(int j=0;j<GraphToWrite.VertexNumber;j++)
                    {
                        TextToWrite<<GraphToWrite.Array[GraphToWrite.VertexNumber*i + j]<<" ";
                    }
                    TextToWrite<<endl;
                }
            }
            else
            {
                TextToWrite<<"Attemp corrupted, check graph adjacency matrix files"<<endl;
            }
            NumericIdentificatorOfFile++;
            IdSettings.remove("GraphId");
            IdSettings.setValue("GraphId",NumericIdentificatorOfFile);
            FileToSawePathsMatrix.close();
           }
           else
           {
           qDebug()<<"File didn't opened";
           }
       }
    }
}
//________________GRAPHWRITERINITIALISER_______________
void GraphWriterInitialiser::Process()
{
    WriterToWorkFromThread = new GraphWriter();
    if (WriterToWorkFromThread==NULL)
    {
        emit finished(false);
        return;
    }
    WriterToWorkFromThread->WriteGraph(GraphPathMatrixToWrite,PathToFolderInWhichToSave);
    emit finished(true);
}
void GraphWriterInitialiser::SetGraphPathMatrixToWrite(DataGraphTable* Source)
{
    GraphPathMatrixToWrite = Source;
}

void GraphWriterInitialiser::SetPathToFolderInWichToSave(QString Dest)
{
    PathToFolderInWhichToSave = Dest;
}
//________________GRAPHWRITERTHREADCREATOR______________

void GraphWriterThreadCreator::MakeWriterThread()
{
 GraphWriterInitialiser* CurrentInitialiser = new GraphWriterInitialiser();
 CurrentInitialiser->SetGraphPathMatrixToWrite(GraphPathMatrixToWrite);
 CurrentInitialiser->SetPathToFolderInWichToSave(PathToFolderInWhichToSave);
 QThread* thread = new QThread();
 CurrentInitialiser->moveToThread(thread);
 connect(thread,&QThread::started,CurrentInitialiser, &GraphWriterInitialiser::Process);
 connect(CurrentInitialiser,&GraphWriterInitialiser::finished,CurrentInitialiser,&QObject::deleteLater);
 connect(thread,&QThread::finished,thread,&QObject::deleteLater);
 thread->start();
}

void GraphWriterThreadCreator::SetGraphPathMatrixToWrite(DataGraphTable* Source)
{
    GraphPathMatrixToWrite = Source;
}
void GraphWriterThreadCreator::SetPathToFolderInWichToSafe(QString Dest)
{
    PathToFolderInWhichToSave = Dest;
}
