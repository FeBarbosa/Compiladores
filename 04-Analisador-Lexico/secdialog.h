#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>

namespace Ui {
class SecDialog;
}
class QTableWidget;
class QTableWidgetItem;
class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = 0);
    ~SecDialog();

private slots:
    void on_pushButton_clicked();

private:
    QTableWidget *tableWidget;
    QTableWidgetItem *tableWidgetItem;
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
