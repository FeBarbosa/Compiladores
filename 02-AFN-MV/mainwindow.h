#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
//change
class QAction;
class QTableWidget;
class QTableWidgetItem;
//
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
/*change
public slots:
    void averageItems();
    void sumItems();
end*/

private slots:
    void on_gerarPosFixa_clicked();

    void on_gerarAFN_clicked();

private:
    //change
    void setupTableItems();

    QAction *removeAction;
    QTableWidget *tableWidget;
    QTableWidgetItem *tableWidgetItem;
    //
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
