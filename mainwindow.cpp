#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "rdv.h"
#include <QString>
#include <QIntValidator>
#include "connection.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include "smtp.h"
#include <QPdfWriter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QVector2D>
#include <QVector>
#include <QCalendarWidget>
#include<QDesktopServices>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QDateTime>
#include <QPrinter>
#include "stat_combo.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->le_num->setValidator( new QIntValidator(0, 999, this));
   ui->tab_rdv->setModel(R.afficher());
   ui->combo_box_nom->addItem("num rdv");
           ui->combo_box_nom->addItem("nom");
           ui->combo_box_nom->addItem("prenom");
           ui->calendarWidget->setMinimumDate(QDate(2006, 6, 19));
           ui->calendarWidget->setMaximumDate(QDate(2023, 7, 3));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::get_d ()const
{
    return ui->la_date->date().toString("dd.MM.yyyy");
}
void MainWindow::on_bt_ajouter_clicked()
{
    int num=ui->le_num->text().toInt();
    int num_salle=ui->le_numsalle->text().toInt();
    int id_perso=ui->le_code->text().toInt();
    QString type=ui->le_type->text();
    QString date_rdv=get_d();
    QString etat=ui->le_etat->text();
    QString nom_cit=ui->le_nom->text();
    QString prenom_cit=ui->le_prenom->text();
    Rdv R(num,num_salle,id_perso,type,etat,nom_cit,prenom_cit,date_rdv);
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

void MainWindow::on_confirmer_clicked()
{
    int num=ui->le_num->text().toInt();
    int num_salle=ui->le_numsalle->text().toInt();
    int id_perso=ui->le_code->text().toInt();
   QString type=ui->le_type->text();
    QString date_rdv=get_d();
    QString etat=ui->le_etat->text();
    QString nom_cit=ui->le_nom->text();
    QString prenom_cit=ui->le_prenom->text();
    Rdv R(num,num_salle,id_perso,type,etat,nom_cit,prenom_cit,date_rdv);
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

void MainWindow::on_rech_textChanged(const QString &arg1)
{
    ui->tab_rdv->setModel(R.rechercherNom(arg1));
}





void MainWindow::on_combo_box_nom_currentTextChanged(const QString &arg1)
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




void MainWindow::on_PDF_clicked()
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

void MainWindow::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp("benabbes.soumaya@esprit.tn", "211JFT9175", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QString a=ui->rcpt->text();
    QString b=ui->subject->text();
    QString c=ui->msg->toPlainText();

    smtp->sendMail("benabbes.soumaya@esprit.tn", a , b,c);
}
/* QChart * Rdv ::stat(){
QSqlQuery q,q1,q2,q3,q4,q5;
   q.exec("Select * from RDV");
   int tot=0;
   while (q.next())
       tot++;
  qDebug() << "total =" << tot;
   q1.prepare("Select * from RDV where num = :num ");
   q1.bindValue(":num","numero rendez-vous");
   q1.exec();

   int tot_don=0;
   while (q1.next())
       tot_don++;
qDebug() << "pourcentage client =" << tot_don;
   qreal pour_Vetments=(tot_don100)/tot;

   q2.prepare("Selectfrom billet where classement = :nom  ");
   q2.bindValue(":nom","classe affaires");
   q2.exec();
   int tot_event=0;
   while (q2.next())
       tot_event++;

   qreal pour_Voiture=(tot_event100)/tot;

   q3.prepare("Select from billet where classement = :nom  ");
   q3.bindValue(":nom","classe eco");
   q3.exec();
   int tot_dep=0;
   while (q3.next())
       tot_dep++;
   qreal pour_supermarche=(tot_dep100)/tot;



   QPieSeriesseries = new QPieSeries();
    series->append("premiere classe",pour_Vetments);
    series->append("classe affaires",pour_Voiture);
    series->append("classe eco",pour_supermarche);

    QPieSlice slice0= series->slices().at(0);
    slice0->setLabelVisible();
    QPieSliceslice1 = series->slices().at(1);

    slice1->setLabelVisible();

    slice1->setBrush(Qt::green);

    QPieSlice slice2= series->slices().at(2);
    slice2->setLabelVisible();
     slice2->setBrush(Qt::red);

    QChartchart = new QChart();
    chart->addSeries(series);
    chart->setTitle("classement des billet");
    chart->legend()->hide();



   return chart;
}
*/

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
ui->dateEdit->setDate(date);
QString dat=ui->dateEdit->text();
QSqlQuery qry;
qry.prepare("select * from RDV ");
if(qry.exec())
{
    while(qry.next())
    {

if(qry.value(7).toString()==dat)
{
        ui->le_num->setText(qry.value(0).toString());
        ui->le_nom->setText(qry.value(3).toString());
        ui->le_prenom->setText(qry.value(4).toString());
        ui->le_code->setText(qry.value(5).toString());
        ui->le_type->setText(qry.value(6).toString());

}//fin if
}//fin while
}//fin if qry
}

void MainWindow::on_stat_clicked()
{
    s = new stat_combo();

  s->setWindowTitle("statistique ComboBox");
  s->choix_bar();
  s->show();
}
