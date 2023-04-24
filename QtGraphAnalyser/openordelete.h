#ifndef OPENORDELETE_H
#define OPENORDELETE_H

#include <QDialog>

namespace Ui {
class OpenOrDelete;
}

class OpenOrDelete : public QDialog
{
    Q_OBJECT

public:
    explicit OpenOrDelete(QWidget *parent = 0);
    ~OpenOrDelete();

private slots:
    int on_pushButton_clicked();

    int on_pushButton_2_clicked();

private:
    Ui::OpenOrDelete *ui;
};

#endif // OPENORDELETE_H
