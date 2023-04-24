#ifndef GRAPHWRITER_H
#define GRAPHWRITER_H
#include "sharedstructs.h"
#include <QSettings>

class GraphWriter
{
    public:
    void WriteGraph(DataGraphTable* GetPathsMatrixFromHere,QString PathToFolderInWhichToSave);
};
class GraphWriterInitialiser:public QObject
{
    Q_OBJECT
    private:
    GraphWriter* WriterToWorkFromThread;
    DataGraphTable* GraphPathMatrixToWrite = NULL;
    QString PathToFolderInWhichToSave = NULL;
    public:
    void SetGraphPathMatrixToWrite(DataGraphTable* Source);
    void SetPathToFolderInWichToSave(QString Dest);
    public slots:
        void Process();
    signals:
        void finished(bool);

};

class GraphWriterThreadCreator:public QObject
{
    Q_OBJECT
    private:
    DataGraphTable* GraphPathMatrixToWrite = NULL;
    QString PathToFolderInWhichToSave = NULL;
    public:
    void SetGraphPathMatrixToWrite(DataGraphTable* Source);
    void SetPathToFolderInWichToSafe(QString Dest);
    void MakeWriterThread();
};


#endif // GRAPHWRITER_H
