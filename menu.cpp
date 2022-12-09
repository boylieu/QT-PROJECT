#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"
#include "gestion_affaire.h"
#include "gestion_rdv.h"
menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    gestion_affaire *ga=new gestion_affaire();
    ga->show();
}

void menu::on_pushButton_2_clicked()
{
    MainWindow *gp=new MainWindow();
    gp->show();
}

void menu::on_pushButton_3_clicked()
{
    gestion_rdv *gr=new gestion_rdv();
    gr->show();
}
