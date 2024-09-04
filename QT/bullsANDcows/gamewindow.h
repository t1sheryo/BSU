#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include "record.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QTableView>
#include <QHeaderView>

QT_BEGIN_NAMESPACE
namespace Ui {
class gameWindow;
}
QT_END_NAMESPACE

class gameWindow : public QWidget {
    Q_OBJECT
public:
    explicit gameWindow(QWidget *parent = 0);

private slots:
    void gameStart();
    void gameStop();
    void check();
    void countBullsAndCows(QString a, QString b, int& bows, int& bulls);
    void hideShowScores();
private:
    int countBetween(QChar what, QString where, int from, int to);
private:
    Ui::gameWindow *ui;
    QLineEdit numberInput;
    QLabel statusMessage;
    QPushButton checkButton;
    QTableWidget* table;
    QString computerNumber;
    Record* record;
    int tries = 0;
    int count = 0;
};

#endif // GAMEWINDOW_H
