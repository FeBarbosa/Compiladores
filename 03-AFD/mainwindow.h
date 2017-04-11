#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_gerarPosFixa_clicked();

    void on_gerarAFN_clicked();

    void on_gerarAFD_clicked();

private:
    void setupTableItems();

    QAction *removeAction;
    QTableWidget *tableWidget;
    QTableWidget *tableWidget_2;
    QTableWidget *tableWidget_3;
    QTableWidgetItem *tableWidgetItem;
    QTableWidgetItem *tableWidgetItem_2;
    QTableWidgetItem *tableWidgetItem_3;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
