#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    FileSystem = new QFileSystemModel(this);
    FileSystem->setFilter(QDir::QDir::AllEntries);
    FileSystem->setRootPath("");
    ui->NavigationTool->setModel(FileSystem);

    TxtNamesBuf = new QStringList;
    GraphsToCountPaths = new DataGraphTable;

    FirstReader.SetTxtsSource(TxtNamesBuf);
    FirstReader.SetNumericGraphsDest(GraphsToCountPaths);

    ReadyPathsMatrics = new DataGraphTable;

    FirstPathFinder.SetToGetGraphFromThere(GraphsToCountPaths);
    FirstPathFinder.SetToPutPathsMatrixHere(ReadyPathsMatrics);

   QString FolderPath = "WorkSpace/PathMatrix/";


   FirstWriter.SetGraphPathMatrixToWrite(ReadyPathsMatrics);
   FirstWriter.SetPathToFolderInWichToSafe(FolderPath);

    FirstReader.MakeReaderThread();
    FirstPathFinder.MakePathFinderThread();
    FirstWriter.MakeWriterThread();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    QStringList FileNames = QFileDialog::getOpenFileNames(this,tr("Open Txt"), "WorkSpace/TestGraphs/", tr("Text files (*.txt)"));
    foreach(QString CurrentFileName,FileNames)
    {
        TxtNamesBuf->push_back(CurrentFileName);
    }

}


void MainWindow::on_NavigationTool_doubleClicked(const QModelIndex &index)
{
    QListView* GoToFile = (QListView*)sender();
    QFileInfo NextFile = FileSystem->fileInfo(index);
    if(NextFile.fileName() == "..")                 //если даблклик на ".."
    {
        QDir GoToDirectory = NextFile.dir();
        GoToDirectory.cd("../");
        GoToFile->setRootIndex(FileSystem->index(GoToDirectory.absolutePath()));

    }
    else if(NextFile.fileName() == ".") //если даблклик на "."
    {
            GoToFile->setRootIndex(FileSystem->index(""));
    }
    else if(NextFile.isDir())
    {
        GoToFile->setRootIndex(index);
    }
    else if(NextFile.fileName().endsWith(".txt", Qt::CaseInsensitive)) //если даблклик на "*.txt"
    {

         QFile CurrentFile(NextFile.absoluteFilePath());
         if(CurrentFile.open(QIODevice::ReadOnly))                  //если открылся
         {
             int VertexNum;
             QTextStream TextToRead(&CurrentFile);
             TextToRead>>VertexNum;
             if(VertexNum<=0)                                      //если содержит поврежденный граф
             {
                 QMessageBox GraphCorrupted;
                 GraphCorrupted.setWindowTitle("Граф поврежден"); ;
                 GraphCorrupted.setInformativeText("Граф поврежден. Открытие невозможно!");
                 GraphCorrupted.setStandardButtons(QMessageBox::Close);
                 GraphCorrupted.setWindowIcon(QIcon("Icons/Eror.png"));
                 GraphCorrupted.exec();
             }
             else
             {
                 QStandardItemModel* MatrixModel = new QStandardItemModel(VertexNum,VertexNum,this);
                 ui->tableView->setModel(MatrixModel);
                 for(int i=0;i<VertexNum;i++)
                 {
                     for(int j = 0;j<VertexNum;j++)
                     {
                         int MatrixValue;
                         TextToRead>>MatrixValue;
                         QModelIndex IndexToMatrixValue  = MatrixModel->index(i,j,QModelIndex());
                         MatrixModel->setData(IndexToMatrixValue,MatrixValue);
                     }
                 }
             }
         }
         else                                                       //если не открылся
         {
            QMessageBox UnsucsessfulOpen;
            UnsucsessfulOpen.setWindowTitle("Не удалось открыть");
            UnsucsessfulOpen.setInformativeText("Выбранный файл не удалось открыть");
            UnsucsessfulOpen.setStandardButtons(QMessageBox::Close);
            UnsucsessfulOpen.setWindowIcon(QIcon("Icons/Eror.png"));
            UnsucsessfulOpen.exec();
         }
    }
}

void MainWindow::on_ButtonClearFile_clicked()
{
    QStandardItemModel* NullModel = new QStandardItemModel(0,0,this);
    ui->tableView->setModel(NullModel); //замещаем Model на другую, с отсутствующей размерностью
}

void MainWindow::on_ButtonSaveFile_clicked()
{
    QString PathToSave = QFileDialog::getSaveFileName(this, tr("Save Current Graph Table .txt"), "WorkSpace/",tr("Text files (*.txt)"));
    if(PathToSave!="")
    {
        int VertexNum = ui->tableView->model()->rowCount();
        QFile FileToSaveCurrentGraphMatrix(PathToSave);
        if(FileToSaveCurrentGraphMatrix.open(QIODevice::WriteOnly| QIODevice::Append))
        {
             QTextStream TextToWrite(&FileToSaveCurrentGraphMatrix);
             if(VertexNum>0)
             {
                    TextToWrite<<VertexNum<<endl;
                    for(int i=0;i<VertexNum;i++)
                    {
                        for(int j=0;j<VertexNum;j++)
                        {
                            TextToWrite<<ui->tableView->model()->index(i,j).data().toInt()<<" "; //получаем по индексам элемент матрицы и записываем в файл
                        }
                    }
                    TextToWrite<<endl;
             }
             else
             {
                 QMessageBox UnsucsessfulCorruptedSave;
                 UnsucsessfulCorruptedSave.setWindowTitle("Не удалось сохранить");
                 UnsucsessfulCorruptedSave.setInformativeText("Текущий файл не удалось сохранить, он поврежден");
                 UnsucsessfulCorruptedSave.setStandardButtons(QMessageBox::Close);
                 UnsucsessfulCorruptedSave.setWindowIcon(QIcon("Icons/Eror.png"));
                 UnsucsessfulCorruptedSave.exec();
             }

        }
        else
        {
            QMessageBox UnsucsessfulSave;
            UnsucsessfulSave.setWindowTitle("Не удалось сохранить");
            UnsucsessfulSave.setInformativeText("Текущий файл не удалось сохранить");
            UnsucsessfulSave.setStandardButtons(QMessageBox::Close);
            UnsucsessfulSave.setWindowIcon(QIcon("Icons/Eror.png"));
            UnsucsessfulSave.exec();
        }
    }
    else
    {
        QMessageBox UnsucsessfulSave;
        UnsucsessfulSave.setWindowTitle("Не удалось сохранить");
        UnsucsessfulSave.setInformativeText("Текущий файл не удалось сохранить");
        UnsucsessfulSave.setStandardButtons(QMessageBox::Close);
        UnsucsessfulSave.setWindowIcon(QIcon("Icons/Eror.png"));
        UnsucsessfulSave.exec();
    }
}

void MainWindow::on_ButtonOpenFile_2_clicked()
{
       QInputDialog GetVertexNum;
       int VertexNum = GetVertexNum.getInt(this,"Введите количество вершин","Количество вершин",0,1,1000,1);
       if(VertexNum>=0)
       {
           QStandardItemModel* NewModel = new QStandardItemModel(VertexNum,VertexNum,this);
           ui->tableView->setModel(NewModel);
       }
       else
       {
           QMessageBox UnsucsessfulCorruptedCreate;
           UnsucsessfulCorruptedCreate.setWindowTitle("Не удалось создать");
           UnsucsessfulCorruptedCreate.setInformativeText("Файл не удалось создать");
           UnsucsessfulCorruptedCreate.setStandardButtons(QMessageBox::Close);
           UnsucsessfulCorruptedCreate.setWindowIcon(QIcon("Icons/Eror.png"));
           UnsucsessfulCorruptedCreate.exec();
       }

}

void MainWindow::on_action_3_triggered()
{
    Help* NewHelp = new Help(this);
    NewHelp->exec();
}

void MainWindow::on_action_4_triggered()
{
    About* NewAbout = new About(this);
    NewAbout->exec();
}

