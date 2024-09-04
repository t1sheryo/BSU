#include "gamewindow.h"
#include "ui_gamewindow.h"

gameWindow::gameWindow(QWidget *parent)
    : QWidget(parent),
    checkButton("Проверить!", this){

    table = new QTableWidget(0, 2, this);
    setWindowTitle("Быки и коровы");

    QGridLayout *layer = new QGridLayout(this);
    this->setLayout(layer);

    QPushButton* startButton = new QPushButton("Новая игра", this);
    QPushButton* hideShowScoresButton = new QPushButton("Рекорды", this);

    numberInput.setValidator(new QIntValidator(this));

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //table->setMaximumWidth(600);
    table->setEnabled(false);
    //table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layer->addWidget(startButton, 0, 0);
    layer->addWidget(&statusMessage, 0, 1);
    layer->addWidget(hideShowScoresButton, 0, 2);

    layer->addWidget(new QLabel("введи число", this), 1, 0);
    layer->addWidget(&numberInput, 1, 1);
    layer->addWidget(&checkButton, 1, 2);

    layer->addWidget(table, 2, 0, 1, 3);

    connect(startButton, SIGNAL(clicked()), SLOT(gameStart()));
    connect(&checkButton, SIGNAL(clicked()), SLOT(check()));
    connect(hideShowScoresButton, SIGNAL(clicked()), SLOT(hideShowScores()));

    record = new Record();

    checkButton.setEnabled(false);
    numberInput.setEnabled(false);
    table->setEnabled(false);
}

void gameWindow::gameStart() {
    statusMessage.setText("Идет игра...");
    numberInput.setEnabled(true);
    checkButton.setEnabled(true);
    table->setEnabled(true);

    numberInput.clear();
    while (table->rowCount() > 0) {
        table->removeRow(0);
    }

    int value = 1234; //1000 + rand()%9000;
    computerNumber = QString::number(value);
}

int gameWindow::countBetween(QChar what, QString where, int from, int to) {
    int count = 0;

    for (int i = from; i < to; ++i) {
        if (where[i] == what)
            count++;
    }

    return count;
}

void gameWindow::countBullsAndCows(QString a, QString b, int& Cows, int& Bulls) {
    Bulls = 0;
    Cows = 0;

    QChar space(' ');

    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == b[i]) {
            Bulls++;
            b[i] = space;
            a[i] = space;
        }
    }

    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == ' ')
            continue;

        int countLeft = countBetween(a[i], a, 0, i);
        int countInComputerNumber = b.count(a[i]);

        if (countInComputerNumber != 0 && countLeft <= countInComputerNumber)
            Cows++;
    }
}

void gameWindow::check(){
    count++;
    QString num = numberInput.text();
    int number = num.toInt();
    if(number > 9999 || number < 1000){
        QMessageBox::information(this, "FAIL", "Incorrect number!");
        numberInput.clear();
        return;
    }
    int cows = 0, bulls = 0;
    countBullsAndCows(computerNumber, num, cows, bulls);
    table->insertRow(table->rowCount());
    table->setItem(tries, 0, new QTableWidgetItem(QString(num)));
    QString res = "Быков: " + QString::number(bulls) + "; Коров: " + QString::number(cows);
    table->setItem(tries, 1, new QTableWidgetItem(QString(res)));
    tries++;
    if(num == computerNumber) gameStop();
}

void gameWindow::gameStop(){
    QMessageBox::information(this, "GAME IS OVER", "YOU FOUND THE CORRECT NUMBER!");
    bool ok;
    QString username = QInputDialog::getText(this, "Введите свое имя", "Введите текст", QLineEdit::Normal, QString(), &ok);
    computerNumber = "";
    statusMessage.setText("Игра закончена!");
    record->add(username, count);
    count = 0;
    tries = 0;
}

void gameWindow::hideShowScores(){
    record->refill();
}

// gameWindow::~gameWindow()
// {
//     delete ui;
// }
