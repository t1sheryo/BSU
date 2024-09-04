#ifndef RECORD_H
#define RECORD_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>

class Record : public QWidget {
    Q_OBJECT
public:
    explicit Record(QWidget *parent = 0);
    void add(QString name, int count);
    bool isTop(int score);
    void refill();
private:
    //void save();
private:
    //QString filename;
    std::multimap<int, QString, std::less<int> > records;
    QTableWidget* scoreTable;
};

#endif // RECORD_H
