#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analisadorlexico.h"
namespace Ui {
class MainWindow;
}
class QAction;
class QTableWidget;
class QTableWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Token_clicked();

    void on_Analisar_clicked();

    void on_inserirToken_clicked();

private:
    QAction *removeAction;
    QTableWidget *tableWidget;
    QTableWidgetItem *tableWidgetItem;
    Ui::MainWindow *ui;
    //SecDialog *secdialog;

};

#endif // MAINWINDOW_H
