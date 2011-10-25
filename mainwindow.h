#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <about.h>

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
    void on_action_Exit_triggered();

    void on_cmdGeneruj_clicked();

    void on_action_About_triggered();

    void ustawStatus(QString slowo);

private:
    Ui::MainWindow *ui;
    About *windowAbout;
    void writeSettings();
    void readSettings();
    bool wczytajKody();
    int obliczLuhna(QString lancuch);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
