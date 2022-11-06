#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personnel.h"
#include "connexion.h"
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->tab_personnel->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    QSqlQuery query;
    QString id=ui->id->text();
    QString nom_pers=ui->nom->text();
    QString prenom_pers=ui->prenom->text();
    QString fonction=ui->fonction->text();
    int CIN_pers = ui->cin->text().toInt();
    int telephone_pers = ui->telephone->text().toInt();
   Personnel P (id,nom_pers,prenom_pers,fonction,CIN_pers,telephone_pers);
   bool test= P.ajouter();
       if(test)
       {
           ui->tab_personnel->setModel(P.afficher());
           QMessageBox::information(nullptr, QObject::tr("AJOUT"),
                       QObject::tr("ajout effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else{
           QMessageBox::critical(nullptr, QObject::tr("AJOUT"),
                       QObject::tr("ajout non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);}
}






void MainWindow::on_supprimer_clicked()
{
    //P.set_id(ui->supp->text());
    QString id=ui->supp->text();
    QModelIndex index = ui->tab_personnel->currentIndex();
    id = index.data(Qt::DisplayRole).toString();
    P.set_id(id);
    P.supprimer(id);
    QString test=ui->supp->text();
    if(test!="")
    {

        QMessageBox::information(nullptr, QObject::tr("SUPPRESSION"),
                    QObject::tr("suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_personnel->setModel(P.afficher());
}
    else{
         ui->tab_personnel->setModel(P.afficher());
        QMessageBox::critical(nullptr, QObject::tr("SUPPRESSION"),
                    QObject::tr("suppression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_modifier_clicked()
{
    QString id=ui->id->text();
    QString nom_pers=ui->nom->text();
    QString prenom_pers=ui->prenom->text();
    QString fonction=ui->fonction->text();
    int CIN_pers = ui->cin->text().toInt();
    int telephone_pers = ui->telephone->text().toInt();
    Personnel P (id,nom_pers,prenom_pers,fonction,CIN_pers,telephone_pers);
   if(P.modifier())
   {
            QMessageBox::information(nullptr, QObject::tr("MODIFICATION"),
                        QObject::tr("modification effectuée.\n"), QMessageBox::Cancel);
            ui->tab_personnel->setModel(P.afficher());



   }
   else
   {
      QMessageBox::critical(nullptr, QObject::tr("MODIFICATION"),

                            QObject::tr("modification non effectuée!\n"), QMessageBox::Cancel);
   }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    P.trier(arg1);
    //P.rechercher();
    ui->id->setText(P.getId());
    ui->nom->setText(P.getNomPers());
    ui->prenom->setText(P.getPrenomPers());
    ui->fonction->setText(P.getFonction());
    //ui->cin->setText(P.getCinPers()));
   // ui->telephone->setText(P.getTelephonePers());
}
