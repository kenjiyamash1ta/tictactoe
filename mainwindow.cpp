#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <algorithm>
#include <random>
#include <QDebug>
#include <QSettings>

QSettings settings("set.ini", QSettings::IniFormat);
std::vector<int> playerBox = {};
std::vector<int> botBox = {};
std::vector<int> emptyBox = {};

std::vector<std::pair<int,int>> WinWithoutStep = {
    {1,2},{1,3},{2,3}, {4,5},{5,6},{6,4}, {7,8},{8,9},{7,9},
    {1,4},{1,7},{7,4}, {2,5},{2,8},{5,8}, {3,6},{3,9},{6,9},
    {1,5},{1,9},{5,9}, {3,5},{3,7},{5,7}
};

std::vector<int> BreakWin = {
    3,2,1, 6,4,5, 9,7,8,
    7,4,1, 8,5,2, 9,6,3,
    9,5,1, 7,5,3
};

int totalMoves;
bool isGameOver;
int YouScore;
int AiScore;
QLineEdit *result;



void checkWin();
void removeElement(int n);




//констуктор

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    isGameOver = false;

    emptyBox = {1,2,3,4,5,6,7,8,9};

    playerBox = {};

    botBox = {};

    totalMoves = 0;
    YouScore = 0;
    AiScore = 0;
    ui->oneone->setText("");
    ui->onetwo->setText("");
    ui->onethree->setText("");
    ui->twoone->setText("");
    ui->twotwo->setText("");
    ui->twothree->setText("");
    ui->threeone->setText("");
    ui->threetwo->setText("");
    ui->threethree->setText("");

    ui->You->setText(QString::number(settings.value("YOUScore", 0).toInt()));
    ui->AI->setText(QString::number(settings.value("AIScore", 0).toInt()));
    result = ui->Result;
    result->setText("");


    ui->HardCheck->setStyleSheet("QCheckBox:checked { color: green; }");
}
//деструктор
MainWindow::~MainWindow()
{
    settings.setValue("AIScore", AiScore);
    settings.setValue("YOUScore", YouScore);
    delete ui;
}



//событие кнопки
void MainWindow::on_NewGame_clicked()
{
    isGameOver = false;

    emptyBox = {1,2,3,4,5,6,7,8,9};

    playerBox = {};

    botBox = {};

    totalMoves = 0;

    ui->oneone->setText("");
    ui->onetwo->setText("");
    ui->onethree->setText("");
    ui->twoone->setText("");
    ui->twotwo->setText("");
    ui->twothree->setText("");
    ui->threeone->setText("");
    ui->threetwo->setText("");
    ui->threethree->setText("");

    ui->You->setText(QString::number(YouScore));
    ui->AI->setText(QString::number(AiScore));

    result->setText("");
}

//проверка пустоты ячейки
bool isEmptyBox(int n){


    if(isGameOver) return false;

    auto it = std::find(emptyBox.begin(), emptyBox.end(), n);
    if (it != emptyBox.end()) {
        emptyBox.erase(it);

        totalMoves++;

        return true;
    }
    return false;
}

//удаление элемента
void removeElement(int n){
    auto it = std::find(emptyBox.begin(), emptyBox.end(), n);
    if (it != emptyBox.end()) {
        emptyBox.erase(it);
    }
}

//проверка победы
void MainWindow::checkWin()
{


        if(
            (ui->oneone->text() == "O" && ui->onetwo->text() == "O" && ui->onethree->text() == "O") ||
            (ui->oneone->text() == "O" && ui->twotwo->text() == "O" && ui->threethree->text() == "O") ||
            (ui->oneone->text() == "O" && ui->twoone->text() == "O" && ui->threeone->text() == "O") ||
            (ui->onetwo->text() == "O" && ui->twotwo->text() == "O" && ui->threetwo->text() == "O") ||
            (ui->onethree->text() == "O" && ui->twothree->text() == "O" && ui->threethree->text() == "O") ||
            (ui->onethree->text() == "O" && ui->twotwo->text() == "O" && ui->threeone->text() == "O") ||
            (ui->twoone->text() == "O" && ui->twotwo->text() == "O" && ui->twothree->text() == "O") ||
            (ui->threeone->text() == "O" && ui->threetwo->text() == "O" && ui->threethree->text() == "O")
        ){
            qDebug() << "Вы победили!";
            isGameOver = true;
            YouScore++;
            result->setText("Вы победили!");
        }



        else if(
            (ui->oneone->text() == "X" && ui->onetwo->text() == "X" && ui->onethree->text() == "X") ||
            (ui->oneone->text() == "X" && ui->twotwo->text() == "X" && ui->threethree->text() == "X") ||
            (ui->oneone->text() == "X" && ui->twoone->text() == "X" && ui->threeone->text() == "X") ||
            (ui->onetwo->text() == "X" && ui->twotwo->text() == "X" && ui->threetwo->text() == "X") ||
            (ui->onethree->text() == "X" && ui->twothree->text() == "X" && ui->threethree->text() == "X") ||
            (ui->onethree->text() == "X" && ui->twotwo->text() == "X" && ui->threeone->text() == "X") ||
            (ui->twoone->text() == "X" && ui->twotwo->text() == "X" && ui->twothree->text() == "X") ||
            (ui->threeone->text() == "X" && ui->threetwo->text() == "X" && ui->threethree->text() == "X")
            ){
            qDebug() << "Победил компьютер";
            isGameOver = true;
            AiScore++;
            result->setText("Победил компьютер((");
        }



        else if(totalMoves == 9){
            qDebug() << "Ничья";
            isGameOver = true;
            result->setText("Ничья");
        }

}

int MainWindow::checkStep()
{
    if(playerBox.size() < 2) return -1;
    for (size_t i = 0; i < WinWithoutStep.size(); ++i) {
        if (std::find(playerBox.begin(), playerBox.end(), WinWithoutStep[i].first) != playerBox.end() &&
            std::find(playerBox.begin(), playerBox.end(), WinWithoutStep[i].second) != playerBox.end() &&
            std::find(playerBox.begin(), playerBox.end(), BreakWin[i]) == playerBox.end() &&
            std::find(botBox.begin(), botBox.end(), BreakWin[i]) == botBox.end()){
            return BreakWin[i];}
    }
    return -1;
}


//логика хода ИИ
void MainWindow::AImove(){

    int Move = -1;

    if(isGameOver) return;


    if(totalMoves >= 9){
        return;
    }

    if(ui->HardCheck->isChecked()){
    Move = checkStep();
    }

    if(Move == -1){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, emptyBox.size()-1);

    int randomIndex = dis(gen);
    Move = emptyBox[randomIndex];
    }

    switch(Move)
    {
    case 1:
        ui->oneone->setText("X");
        botBox.push_back(1);
        removeElement(1);
        break;
    case 2:
        ui->onetwo->setText("X");
        botBox.push_back(2);
        removeElement(2);
        break;
    case 3:
        ui->onethree->setText("X");
        botBox.push_back(3);
        removeElement(3);
        break;
    case 4:
        ui->twoone->setText("X");
        botBox.push_back(4);
        removeElement(4);
        break;
    case 5:
        ui->twotwo->setText("X");
        botBox.push_back(5);
        removeElement(5);
        break;
    case 6:
        ui->twothree->setText("X");
        botBox.push_back(6);
        removeElement(6);
        break;
    case 7:
        ui->threeone->setText("X");
        botBox.push_back(7);
        removeElement(7);
        break;
    case 8:
        ui->threetwo->setText("X");
        botBox.push_back(8);
        removeElement(8);
        break;
    case 9:
        ui->threethree->setText("X");
        botBox.push_back(9);
        removeElement(9);
        break;
    }

    totalMoves++;
    qDebug() << "Ход ИИ: " << Move;


    MainWindow::checkWin();
}

//нажание на поля
void MainWindow::on_oneone_clicked()
{

    if(isEmptyBox(1)){
        playerBox.push_back(1);
        ui->oneone->setText("O");
        MainWindow::checkWin();
        AImove();
    }
}

void MainWindow::on_onetwo_clicked()
{
    if(isEmptyBox(2)){
        playerBox.push_back(2);
        ui->onetwo->setText("O");
        MainWindow::checkWin();
        AImove();
    }
}

void MainWindow::on_onethree_clicked()
{
    if(isEmptyBox(3)){
        playerBox.push_back(3);
        ui->onethree->setText("O");
        MainWindow::checkWin();
        AImove();
    }
}

void MainWindow::on_twoone_clicked()
{
    if(isEmptyBox(4)){
        playerBox.push_back(4);
        ui->twoone->setText("O");
        MainWindow::checkWin();
        AImove();
    }
}

void MainWindow::on_twotwo_clicked()
{
    if(isEmptyBox(5)){
        playerBox.push_back(5);
        ui->twotwo->setText("O");
        MainWindow::checkWin();
        AImove();
    }
}

void MainWindow::on_twothree_clicked()
{
    if(isEmptyBox(6)){
        playerBox.push_back(6);
        ui->twothree->setText("O");
        MainWindow::checkWin();
        AImove();
    }
}


void MainWindow::on_threeone_clicked()
{
    if(isEmptyBox(7)){
        playerBox.push_back(7);
        ui->threeone->setText("O");
        MainWindow::checkWin();
        AImove();
    }
}


void MainWindow::on_threetwo_clicked()
{
    if(isEmptyBox(8)){
        playerBox.push_back(8);
        ui->threetwo->setText("O");
        MainWindow::checkWin();
        AImove();
    }
}


void MainWindow::on_threethree_clicked()
{
    if(isEmptyBox(9)){
        playerBox.push_back(9);
        ui->threethree->setText("O");
        MainWindow::checkWin();
        AImove();
    }
}

void MainWindow::on_reset_clicked()
{
    isGameOver = false;

    emptyBox = {1,2,3,4,5,6,7,8,9};

    playerBox = {};

    botBox = {};

    totalMoves = 0;

    ui->oneone->setText("");
    ui->onetwo->setText("");
    ui->onethree->setText("");
    ui->twoone->setText("");
    ui->twotwo->setText("");
    ui->twothree->setText("");
    ui->threeone->setText("");
    ui->threetwo->setText("");
    ui->threethree->setText("");

    AiScore = 0;
    YouScore = 0;
    settings.setValue("AIScore", AiScore);
    settings.setValue("YOUScore", YouScore);
    ui->You->setText(QString::number(YouScore));
    ui->AI->setText(QString::number(AiScore));

    result->setText("");
}

