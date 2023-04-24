    #ifndef SHAREDSTRUCTS_H
#define SHAREDSTRUCTS_H
#include <QQueue>
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QVector>
#include <QMutex>

struct GraphTable //для передачи графов в виде массивов
{
    int VertexNumber;
    QVector<int> Array;
};
class DataGraphTable:public QObject
{
    Q_OBJECT
    public:
    void PushDataToBot(GraphTable ToPush)
    {
        GraphsToTransport.push_back(ToPush);
    }
    GraphTable GetDataFromFront()
    {
        SecondMutex.tryLock(1);
        GraphTable FirstVectorElement = GraphsToTransport.first();
        GraphsToTransport.pop_front();
        return FirstVectorElement;
        SecondMutex.unlock();
    }
    bool GetEmpty()
    {
        FirstMutex.tryLock(1);
        return GraphsToTransport.empty();
        FirstMutex.unlock();
    }

    private:
    QVector<GraphTable> GraphsToTransport;
    QMutex FirstMutex;
    QMutex SecondMutex;

};


#endif // SHAREDSTRUCTS_H
