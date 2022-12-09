#include "gestion_rdv.h"
#include "ui_gestion_rdv.h"
#include "rdv.h"
#include "smtp.h"
#include <QMessageBox>
#include <QIntValidator>
#include<QMessageBox>
#include <QTableWidget>
#include<QFileInfo>
#include<QTextStream>
#include <QRadioButton>
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QPainter>
#include<QFileDialog>
#include<QTextDocument>
#include <QTextEdit>
#include<QVariant>
#include "qcustomplot.h"
#include "Excel.h"
#include <QDialog>

gestion_rdv::gestion_rdv(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_rdv)
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

     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label));
       ui->le_num->setValidator( new QIntValidator(0, 999, this));
       ui->tab_rdv->setModel(R.afficher());
       ui->combo_box_nom->addItem("num rdv");
               ui->combo_box_nom->addItem("nom");
               ui->combo_box_nom->addItem("prenom");
               ui->calendarWidget->setMinimumDate(QDate(2006, 6, 19));
               ui->calendarWidget->setMaximumDate(QDate(2023, 7, 3));

}

gestion_rdv::~gestion_rdv()
{
    delete ui;
}


void gestion_rdv::on_bt_ajouter_clicked()
{
    int num=ui->le_num->text().toInt();
    int num_salle=ui->le_numsalle->text().toInt();
    int id_perso=ui->le_code->text().toInt();
    QString type=ui->le_type->text();
    //QString date_rdv=get_d();
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



void gestion_rdv::on_rdv_supp_clicked()
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


void gestion_rdv::on_bt_mod_clicked()
{
     QModelIndex index = ui->tab_rdv->currentIndex();
      QString num = index.data(Qt::DisplayRole).toString();
       QString etat = ui->tab_rdv->model()->index(index.row(), 2).data(Qt::DisplayRole).toString();
       ui->le_etat->setText(etat);
        QString type = ui->tab_rdv->model()->index(index.row(), 6).data(Qt::DisplayRole).toString();
        ui->le_type->setText(type);
         QString nom = ui->tab_rdv->model()->index(index.row(), 3).data(Qt::DisplayRole).toString();
         ui->le_nom->setText(nom);
          QString prenom = ui->tab_rdv->model()->index(index.row(), 4).data(Qt::DisplayRole).toString();
          ui->le_prenom->setText(prenom);
           QString num_rdv = ui->tab_rdv->model()->index(index.row(), 0).data(Qt::DisplayRole).toString();
           ui->le_num->setText(num_rdv);
            QString num_s = ui->tab_rdv->model()->index(index.row(), 1).data(Qt::DisplayRole).toString();
            ui->le_numsalle->setText(num_s);
            QString id = ui->tab_rdv->model()->index(index.row(), 5).data(Qt::DisplayRole).toString();
            ui->le_code->setText(id);
}

void gestion_rdv::on_confirmer_clicked()
{
    int num=ui->le_num->text().toInt();
    int num_salle=ui->le_numsalle->text().toInt();
    int id_perso=ui->le_code->text().toInt();
   QString type=ui->le_type->text();
    //QString date_rdv=get_d();
    QString etat=ui->le_etat->text();
    QString nom_cit=ui->le_nom->text();
    QString prenom_cit=ui->le_prenom->text();
    Rdv R(num,num_salle,id_perso,type,etat,nom_cit,prenom_cit);
   bool test=R.modifier();
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

void gestion_rdv::on_rech_textChanged(const QString &arg1)
{
    ui->tab_rdv->setModel(R.rechercherNom(arg1));
}





void gestion_rdv::on_combo_box_nom_currentTextChanged(const QString &arg1)
{
    QString name=ui->combo_box_nom->currentText();
             if(name=="num rdv")
             {
                  ui->tab_rdv->setModel(R.tri_num());
             }
             else if( name=="nom")
             {
                    ui->tab_rdv->setModel(R.tri_nom());

             }
             else
             {
               ui->tab_rdv->setModel(R.tri_prenom());
             }
    }




void gestion_rdv::on_PDF_clicked()
{
    QModelIndex index = ui->tab_rdv->currentIndex();
       QString num = index.data(Qt::DisplayRole).toString();
       QString etat = ui->tab_rdv->model()->index(index.row(), 2).data(Qt::DisplayRole).toString();
       QString type = ui->tab_rdv->model()->index(index.row(), 6).data(Qt::DisplayRole).toString();
       QString nom = ui->tab_rdv->model()->index(index.row(), 3).data(Qt::DisplayRole).toString();
       QString prenom = ui->tab_rdv->model()->index(index.row(), 4).data(Qt::DisplayRole).toString();
       QString num_rdv = ui->tab_rdv->model()->index(index.row(), 0).data(Qt::DisplayRole).toString();
       QString num_s = ui->tab_rdv->model()->index(index.row(), 1).data(Qt::DisplayRole).toString();
       QString id = ui->tab_rdv->model()->index(index.row(), 5).data(Qt::DisplayRole).toString();
       QString filename = "C:/Users/Soumaya/pdf rdv/" + nom + " " + prenom + ".pdf";
       QPrinter printer;
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setOutputFileName(filename);
       QPainter painter;
       QFont logoname("Corbel Light", 25, QFont::Bold), title("Bahnschrift Light", 25, QFont::Bold), f("Aria", 18, QFont::Bold), f1("Arial", 15);
           if (! painter.begin(&printer)) { // failed to open file
               qWarning("failed to open file, is it writable?");
           }
                   painter.setFont(title);
                   painter.drawText(200, 180, "Information des rendez-vous");
                   painter.setFont(f1);
                   painter.setPen(Qt::red);
                   painter.drawText(80, 250, "numero redez-vous:  ");
                   painter.drawText(80, 300, "numero de la salle:  ");
                   painter.drawText(80, 350, "etat du rendez-vous: ");
                   painter.drawText(80, 400, "nom du citoyen:  ");
                   painter.drawText(80, 450, "prenom du citoyen:  ");
                   painter.drawText(80, 500, "type du rendez-vous:  ");
                   painter.drawText(80, 550, "id du personnel:  ");
                   painter.setFont(f1);
                   painter.setPen(Qt::black);
                   painter.drawText(350, 250, num);
                   painter.drawText(350, 300, num_s);
                   painter.drawText(350, 350, etat);
                   painter.drawText(350, 400, nom);
                   painter.drawText(350, 450, prenom);
                   painter.drawText(350, 500, type);
                   painter.drawText(350, 550, id);

                   painter.end();
                   QMessageBox::information(nullptr, QObject::tr("Gestion-Des-Rendez-vous"),
                                                     QObject::tr(" PDF a été crée avec succes!\n"
                                                                 "Taper sur cancel pour fermer."), QMessageBox::Cancel);
}

void gestion_rdv::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp("benabbes.soumaya@esprit.tn", "211JFT9175", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QString a=ui->rcpt->text();
    QString b=ui->subject->text();
    QString c=ui->msg->toPlainText();

    smtp->sendMail("benabbes.soumaya@esprit.tn", a , b,c);
}

/*void gestion_rdv::on_stat_clicked()
{
    s = new stat_combo();

  s->setWindowTitle("statistique ComboBox");
  s->choix_bar();
  s->show();
}
void gestion_rdv::update_label()
{
    data=A.read_from_arduino();
    if(data=="1")
        ui->label_c->setText("presence");
    else if (data=="0")
         ui->label_cc->setText("pas presence");
}*/
void gestion_rdv::on_confsalle_clicked()
{
   /* Rdv R;
    int num=ui->cap->text().toInt();
    int c=R.salle(num); */
    A.write_to_arduino("s");

}


void gestion_rdv::on_pushButton_clicked()
{
    QModelIndex index = ui->tab_rdv->currentIndex();
      QString num = index.data(Qt::DisplayRole).toString();
      QString num_s = ui->tab_rdv->model()->index(index.row(), 1).data(Qt::DisplayRole).toString();
      ui->test->setText(num_s);
data=A.read_from_arduino();
ui->cap->setText(data);
QString ca=ui->test->text();
if(data==ca)
{
    ui->let->setText("busy");
    A.write_to_arduino("b");
}
}
