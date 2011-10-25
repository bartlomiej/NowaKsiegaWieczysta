#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Nowa Księga Wieczysta v.%1").arg(QApplication::applicationVersion()));
    ui->statusBar->showMessage(tr("Ready."));
    windowAbout= new About(this);

    wczytajKody();
    readSettings();
    connect(ui->statusBar, SIGNAL(messageChanged(QString)), this, SLOT(ustawStatus(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Exit_triggered()
{
    close();
}

void MainWindow::writeSettings()
{
    QSettings settings("generator-cyfry-kontrolnej", "config");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("sad", ui->cbKodSadu->currentIndex());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("generator-cyfry-kontrolnej", "config");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(361, 148)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    ui->cbKodSadu->setCurrentIndex(settings.value("sad",240).toInt());
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent*)
{
    writeSettings();
}

bool MainWindow::wczytajKody()
{
    QFile file("kodysadow");
    if (!file.open (QFile::ReadOnly))
        return 1;
    QTextStream stream ( &file );
    QString line;
    while( !stream.atEnd() ) {
         line = stream.readLine();
         ui->cbKodSadu->addItem(line);
    }
    file.close();
    return 0;
}

//Algorytm Luhna
int MainWindow::obliczLuhna(QString lancuch)
{
    QString dobreLitery = "ABCDEFGHIJKLMNOPRSTUWYZ";
    int waga[] = {1,3,7,1,3,7,1,3,7,1,3,7};
    int litery[] = {0,1,3};
    int suma = 0;
    int indeks;
    lancuch = lancuch.toUpper();

    for (int i = 0; i < 3; i++)
    {
        indeks = dobreLitery.indexOf(lancuch.mid(litery[i], 1));
        suma += (indeks + 1) * waga[litery[i]];
    }
    if (lancuch.mid(2, 1) >= "A" && lancuch.mid(2, 1) <= "Z")
    {
        indeks = dobreLitery.indexOf(lancuch.mid(2, 1));
        suma += (indeks + 1) * waga[2];
    }
    else
    {
        suma += ((lancuch.mid(2, 1).toInt()) - 0) * waga[2];
    }
    for (int i = 4; i < 12; i++)
    {
        suma += ((lancuch.mid(i, 1).toInt()) - 0) * waga[i];
    }
    suma = suma % 10;
    return suma;
}

void MainWindow::on_cmdGeneruj_clicked()
{
    if(ui->leNumerKsiegi->text().length() < 1)
    {
        ui->statusBar->showMessage(tr("Popraw numer Księgi Wieczystej."));
        return;
    }
    QString tmp = "";
    for (int i=0;i<8-ui->leNumerKsiegi->text().length();i++)
    {
        tmp += "0";
    }
    tmp+=ui->leNumerKsiegi->text();
    ui->leNumerKsiegi->setText(tmp);
    QString wynik;
    wynik.setNum(obliczLuhna(ui->cbKodSadu->currentText().right(4)+ui->leNumerKsiegi->text()));
    ui->leCyfraKontrolna->setText(wynik);
    ui->statusBar->showMessage(tr("Generowanie zakończone."),2000);
}

void MainWindow::on_action_About_triggered()
{
    windowAbout->show();
}

void MainWindow::ustawStatus(QString slowo)
{
   if (slowo == "")
       ui->statusBar->showMessage(tr("Ready."));
}
