#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_label_8_linkActivated(const QString &link)
{
    ui->label_8->setOpenExternalLinks(true);
}

void About::on_label_2_linkActivated(const QString &link)
{
    ui->label_2->setOpenExternalLinks(true);
}

void About::on_label_7_linkActivated(const QString &link)
{
    ui->label_7->setOpenExternalLinks(true);
}
