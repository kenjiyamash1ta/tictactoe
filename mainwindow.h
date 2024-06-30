#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void checkWin();

    int checkStep();

    void AImove();

    void on_oneone_clicked();

    void on_NewGame_clicked();

    void on_onetwo_clicked();

    void on_onethree_clicked();

    void on_twotwo_clicked();

    void on_twoone_clicked();

    void on_twothree_clicked();

    void on_threeone_clicked();

    void on_threetwo_clicked();

    void on_threethree_clicked();

    void on_reset_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
