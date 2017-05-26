#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>

#include <analisadorSintatico.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Divide as entradas
    std::vector<std::string> tokenizar(std::string, char *);

private slots:
    void on_inserirGramatica_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
