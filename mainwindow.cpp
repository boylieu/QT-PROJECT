#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personnel.h"
#include "smtp.h"
#include "connexion.h"
#include "arduino.h"
#include <QMessageBox>
#include <QApplication>
#include <QtPrintSupport>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino();
        switch(ret)
        {
        case(0):qDebug()<<"arduino is available and connected to :"<<A.getarduino_port_name();
            break;
        case(1):qDebug()<<"arduino is available but not connected to :"<<A.getarduino_port_name();
            break;
        case(-1):qDebug()<<"arduino is not available";
        }

     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

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
   if((id=="")&&(nom_pers=="")&&(prenom_pers=="")&&(fonction=="")&&(CIN_pers==0)&&(telephone_pers==0))
                {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                QObject::tr("Veuillez remplir les champs"), QMessageBox::Ok);
                 }
   else if(id == "")
                {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                QObject::tr("Veuillez sasir l'identifiant"), QMessageBox::Ok);

                }
   else if(nom_pers =="")
                   {
                       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                   QObject::tr("Veuillez saisir le nom"), QMessageBox::Ok);

                   }
   else if(prenom_pers =="")
                   {
                       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                   QObject::tr("Veuillez saisir le prenom"), QMessageBox::Ok);

                   }
   else if(fonction =="")
      {
          QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                      QObject::tr("Veuillez saisir la fonction"), QMessageBox::Ok);

      }
   else if(CIN_pers ==0)
                   {
                       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                   QObject::tr("Veuillez saisir le CIN"), QMessageBox::Ok);

                   }

   else if(telephone_pers==0)
                   {
                       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                   QObject::tr("Veuillez saisir le numero "), QMessageBox::Ok);

                   }

             else {
   if(P.modifier(id))
   {
            QMessageBox::information(nullptr, QObject::tr("Modification"),
                        QObject::tr("modification effectuée.\n"), QMessageBox::Cancel);
            ui->tab_personnel->setModel(P.afficher());



   }
   else
   {
      QMessageBox::critical(nullptr, QObject::tr("Modification"),

                            QObject::tr("modification non effectuée\n"), QMessageBox::Cancel);
      ui->id->setText("");
      ui->nom->setText("");
      ui->prenom->setText("");
      ui->fonction->setText("");
      ui->cin->setText("");
      ui->telephone->setText("");
   }
}}


void MainWindow::on_rechercher_clicked()
{
    QString id =ui->recherche->text();
    bool test =  P.rechercher(id);
    if (test)
    ui->tab_recherche->setModel(P.rechercher(id));
}


void MainWindow::on_trier_clicked()
{ ui->tab_personnel->setModel(P.trierId());}

void MainWindow::on_pdf_clicked()
{
Personnel P;
QString text=P.exporter();
ui->print->setText(text);
QPrinter printer ;
printer.setPrinterName("imprimante");
QPrintDialog dialog (&printer,this);
if(dialog.exec()==QDialog::Rejected) return ;
ui->print->print(&printer);
}

void MainWindow::on_sms_clicked()
{
    Smtp* smtp = new Smtp("nadine.benabdallah@esprit.tn", "211JFT4266", "smtp.gmail.com", 465);

    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    QString a=ui->recvr->text();

    QString b=ui->subject->text();

    QString c=ui->mail->text();



    smtp->sendMail("nadine.benabdallah@esprit.tn", a , b,c);
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    Personnel P;
      QSqlQueryModel * modal = new QSqlQueryModel();
      QSqlQuery * qry = new QSqlQuery();
      if (arg1=="ID")
      {
       qry->prepare("Select * from PERSONNEL order by ID ");
       qry->exec();
       modal->setQuery(*qry);
       ui->tab_personnel->setModel(modal);
       ui->tab_personnel->show();
      }
     else if (arg1=="CIN")
      {
       qry->prepare("Select * from PERSONNEL order by CIN_pers");
       qry->exec();
       modal->setQuery(*qry);
       ui->tab_personnel->setModel(modal);
       ui->tab_personnel->show();
      }

}


void MainWindow::update_label()
{
    QString data=A.read_from_arduino();
    if(data=="3")
        ui->label_c->setText("CLOSED");
    else if (data<"3")
         ui->label_c->setText("ENTER");
}

void MainWindow::on_arduino_clicked()
{
    A.write_to_arduino("s");
}
