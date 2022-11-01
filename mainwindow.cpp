#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "prisonniers.h"
#include "connection.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

ui->tab_priso->setModel(pr.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    QString id_priso=ui->id->text();
    QString nom_priso=ui->nom->text();
    QString prenom_priso=ui->prenom->text();
    QString crime=ui->crime->text();
    int age=ui->age->text().toInt();
    int cin_priso=ui->cin->text().toInt();
   Prisonniers pr (id_priso,nom_priso,prenom_priso,crime,age,cin_priso);
   bool test= pr.ajouter();
       if(test)
       {
           ui->tab_priso->setModel(pr.afficher());
           QMessageBox::information(nullptr, QObject::tr("database is open"),
                       QObject::tr("ajouter successful.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
ui->tab_priso->setModel(pr.afficher());
   }
       else{
           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                       QObject::tr("ajouter failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);}
}






void MainWindow::on_pushButton_6_clicked()
{

    QModelIndex index = ui->tab_priso->currentIndex();
      QString id_priso = index.data(Qt::DisplayRole).toString();

    bool test =pr.supprimer(id_priso);
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
ui->tab_priso->setModel(pr.afficher());
}
    else{
         ui->tab_priso->setModel(pr.afficher());
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow:: on_pushButton_2_clicked()
{
    QString id_priso=ui->id->text();
    QString nom_priso=ui->nom->text();
    QString prenom_priso=ui->prenom->text();
    QString crime=ui->crime->text();
    int cin_priso=ui->cin->text().toInt();
    int age=ui->age->text().toInt();
   Prisonniers pr (id_priso,nom_priso,prenom_priso,crime,age,cin_priso);
   if(pr.modifier())
   {
            QMessageBox::information(nullptr, QObject::tr("Modifier un prisonnier"),
                        QObject::tr("Vol modifié.\n"), QMessageBox::Cancel);
            ui->tab_priso->setModel(pr.afficher());



   }
   else
   {
      QMessageBox::critical(nullptr, QObject::tr("Modifier un prisonnier"),

                            QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
      ui->id->setText("");
      ui->nom->setText("");
      ui->prenom->setText("");
      ui->crime->setText("");
      ui->cin->setText("");
      ui->age->setText("");
   }
}







