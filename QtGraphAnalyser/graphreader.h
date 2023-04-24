#ifndef GRAPHREADER_H
#define GRAPHREADER_H
#include "sharedstructs.h"


class GraphReader :public QObject //класс, методом которого граф переводится из текстового вида в массив цифр (структура GraphTable)
{
    Q_OBJECT
    public:
    void ReadGraph(QStringList* TxtsToConvert,DataGraphTable* GraphsToPushInQueue); // метод получает на вход указатель на список текстовых переменных
                                                                                        // где хранятся названия всех файлов которые надо обработать
};                                                                                      // и указатель на очередь струтур, куда закидываем результат чтения

class GraphReaderInitialiser:public QObject // класс, проверяющий корректность работы GraphReader'а
{                                           // и запускающий его,также содержит указатели для него
    Q_OBJECT
    private:
    GraphReader* ReaderToWorkFromThread;
    QStringList* TxtsToConvert = NULL;
    DataGraphTable* GraphsToPushInQueue = NULL;
    public:
    void SetTxtsSource(QStringList* Source);
    void SetNumericGraphsDest(DataGraphTable* Dest);
    public slots:
        void Process();
    signals:
        void finished(bool);
};
class GraphReaderThreadCreator:public QObject // класс запускающий QraphInitialiser в отдельном потоке
{
    Q_OBJECT
    private:
    QStringList* TxtsToConvert = NULL;
    DataGraphTable* GraphsToPushInQueue = NULL;
    public:
    void SetTxtsSource(QStringList* Source);
    void SetNumericGraphsDest(DataGraphTable* Dest);
    void MakeReaderThread();
};

#endif // GRAPHREADER_H
