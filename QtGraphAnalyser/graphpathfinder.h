#ifndef GRAPHPATHFINDER_H
#define GRAPHPATHFINDER_H
#include "sharedstructs.h"
#include <QProgressBar>
#include <QtDeikstraAlgorythm/QtDeikstraAlgorythm.h>

class GraphPathFinder :public QObject//Класс выполняющий построение матрицы кратчайших путей
{
    Q_OBJECT
    public:
    void BuildPathsMatrix(DataGraphTable* GetGraphFromThere,DataGraphTable* PutPathsMatrixHere);
};


class GraphPathFinderInitializer:public QObject // класс, проверяющий корректность работы GraphPathFinder'а
{                                               // и запускающий его,также содержит указатели для него
    Q_OBJECT
    private:
    GraphPathFinder* GraphPathFinderToWorkFromThread;
    DataGraphTable* GetGraphFromThere = NULL;
    DataGraphTable* PutPathsMatrixHere = NULL;
    QProgressBar* WidgetForFilesInProcessShow;
    public:
    void SetToGetGraphGromThere(DataGraphTable* Source);
    void SetToPutPathsMatrixHere(DataGraphTable* Dest);
    void SetUIWidget(QProgressBar* Widget);
    public slots:
        void Process();
    signals:
        void finished(bool);
};
class GraphPathFinderThreadCreator:public QObject
{
    Q_OBJECT
    private:
    DataGraphTable* GetGraphFromThere = NULL;
    DataGraphTable* PutPathsMatrixHere = NULL;
    QProgressBar* WidgetForFilesInProcessShow;
    public:
    void SetToGetGraphFromThere(DataGraphTable* Source);
    void SetToPutPathsMatrixHere(DataGraphTable* Dest);
    void MakePathFinderThread();
};



#endif // GRAPHPATHFINDER_H
