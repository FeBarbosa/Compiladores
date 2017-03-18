#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_gerarPosFixa_clicked();

    void on_gerarAFN_clicked();

    // void cellSelected(int nRow, int nCol);

private:
    Ui::MainWindow *ui;

    /*
        QTableWidget* m_pTableWidget;

        QStringList m_TableHeader;
    */
};

#endif // MAINWINDOW_H
