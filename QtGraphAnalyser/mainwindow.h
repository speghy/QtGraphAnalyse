#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QInputDialog>
#include <QIcon>
#include "graphreader.h"
#include "graphpathfinder.h"
#include "graphwriter.h"
#include "help.h"
#include "about.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_action_triggered();

    void on_NavigationTool_doubleClicked(const QModelIndex &index);

    void on_ButtonClearFile_clicked();

    void on_ButtonSaveFile_clicked();

    void on_ButtonOpenFile_2_clicked();

    void on_action_3_triggered();

    void on_action_4_triggered();



private:
    Ui::MainWindow *ui;
    QStringList* TxtNamesBuf;
    DataGraphTable* GraphsToCountPaths;
    DataGraphTable* ReadyPathsMatrics;
    GraphReaderThreadCreator FirstReader;
    GraphPathFinderThreadCreator FirstPathFinder;
    GraphWriterThreadCreator FirstWriter;
    QString* PathToSaveFolder;
    QFileSystemModel* FileSystem;

};

#endif // MAINWINDOW_H
