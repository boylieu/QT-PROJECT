#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "rdv.h"
#include <QString>
#include <QIntValidator>
#include "connection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->le_num->setValidator( new QIntValidator(0, 999, this));
   ui->tab_rdv->setModel(R.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bt_ajouter_clicked()
{
    int num=ui->le_num->text().toInt();
    int num_salle=ui->le_numsalle->text().toInt();
    int id_perso=ui->le_code->text().toInt();
   QString type=ui->le_type->text();
    //QString date=ui->la_date->text();
    QString etat=ui->le_etat->text();
    QString nom_cit=ui->le_nom->text();
    QString prenom_cit=ui->le_prenom->text();
    Rdv R(num,num_salle,id_perso,type,etat,nom_cit,prenom_cit);
  bool test=R.ajouter();
  if(test)
  {
      QMessageBox::information(nullptr, QObject::tr("OK"),
                  QObject::tr("Ajout  effectue.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else

  QMessageBox::information(nullptr, QObject::tr("NOT OK"),
              QObject::tr("Ajout non effectue.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);
  ui->tab_rdv->setModel(R.afficher());
}



void MainWindow::on_rdv_supp_clicked()
{
    Rdv R;
    R.setnum(ui->le_supp->text().toInt());
  bool test=R.supprimer(R.getnum());
  if(test)
  {
      QMessageBox::information(nullptr, QObject::tr("OK"),
                  QObject::tr("suppresion  effectue.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else

  QMessageBox::information(nullptr, QObject::tr("NOT OK"),
              QObject::tr("suppresion non effectue.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);
   ui->tab_rdv->setModel(R.afficher());
}


void MainWindow::on_bt_mod_clicked()
{
     QModelIndex index = ui->tab_rdv->currentIndex();
      QString num = index.data(Qt::DisplayRole).toString();
       QString etat = ui->tab_rdv->model()->index(index.row(), 2).data(Qt::DisplayRole).toString();
       ui->etat_modif->setText(etat);
        QString type = ui->tab_rdv->model()->index(index.row(), 6).data(Qt::DisplayRole).toString();
        ui->type_modif->setText(type);
         QString nom = ui->tab_rdv->model()->index(index.row(), 3).data(Qt::DisplayRole).toString();
         ui->nom_modif->setText(nom);
          QString prenom = ui->tab_rdv->model()->index(index.row(), 4).data(Qt::DisplayRole).toString();
          ui->prenom_modif->setText(prenom);
           QString num_rdv = ui->tab_rdv->model()->index(index.row(), 0).data(Qt::DisplayRole).toString();
           ui->num_rdv_modif->setText(num_rdv);
            QString num_s = ui->tab_rdv->model()->index(index.row(), 1).data(Qt::DisplayRole).toString();
            ui->num_s_modif->setText(num_s);
            QString id = ui->tab_rdv->model()->index(index.row(), 5).data(Qt::DisplayRole).toString();
            ui->id_modif->setText(id);
}

void MainWindow::on_confirmer_clicked()
{
    int num=ui->num_rdv_modif->text().toInt();
    int num_salle=ui->num_s_modif->text().toInt();
    int id_perso=ui->id_modif->text().toInt();
   QString type=ui->type_modif->text();
    //QString date=ui->la_date->text();
    QString etat=ui->etat_modif->text();
    QString nom_cit=ui->nom_modif->text();
    QString prenom_cit=ui->le_prenom->text();
    Rdv R(num,num_salle,id_perso,type,etat,nom_cit,prenom_cit);
   bool test=R.modifier(num);
   if(test)
   {
       QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("modification  effectue.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   }
   else

   QMessageBox::information(nullptr, QObject::tr("NOT OK"),
               QObject::tr("modification non effectue.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);


     ui->tab_rdv->setModel(R.afficher());

}
