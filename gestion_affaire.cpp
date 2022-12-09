#include "gestion_affaire.h"
#include "ui_gestion_affaire.h"
#include "affaire.h"
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


gestion_affaire::gestion_affaire(QWidget *parent)
    :     QMainWindow(parent)
    , ui(new Ui::gestion_affaire)
{
    ui->setupUi(this);
   ui->tableView->setModel(aff.afficher());
   affaire afff;
  ui->comboBox_2->addItems(afff.afficher_ID_PER());
  ui->comboBox_3->addItems(afff.afficher_ID_PRI());
  int ret =A.connect_arduino();//lancer la connection to arduino
  switch (ret) {

  case(0):qDebug()<<"arduino is available and connect to : "<<A.getarduino_port_name();
      break;
  case(1):qDebug()<<"arduino is available and not  connect to : "<<A.getarduino_port_name();
      break;
  case(-1):qDebug()<<"arduino is not available ";
      break;

  }
  QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(updatelabel()));
}

void gestion_affaire::updatelabel()
{
    data=A.read_from_arduino();
    if(data!="0"){
        QMessageBox::information(this,"NOTIFICATIONS","S'IL VOUS PLAIT CONSULTER VOTRE BOITE DE NOTIFICATIONS.");
     if (data=="2")
     {aff.ajoutdate();

        ui->label_6->setText("Il y a du gaz dans la salle activer le sonor");//afficher on si les données reçues par arduino est 1
     }

    else if(data=="3")

           ui->label_6->setText("il y a plus de gaz dans la salle deactiver le sonor !");
}
}
gestion_affaire::~gestion_affaire()
{
    delete ui;
}


void gestion_affaire::on_ajouter_clicked()
{


    QString num_aff=ui->num_aff->text();
    QString id_perso =ui->comboBox_2->currentText();
    QString id_priso =ui->comboBox_3->currentText();
    QString type_aff=ui->type_aff->text();
    QString dates=ui->dates->text();
    affaire aff(num_aff,id_perso,id_priso, type_aff,dates);

    bool test= aff.ajouter();
    if(test)
    {  ui->tableView->setModel(aff.afficher());
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("ajouter successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("ajouter failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}



void gestion_affaire::on_suprimer_clicked()
{
    affaire AFF ;
    QString x =ui->label_4->text();
    bool test=AFF.supprimer(x);

        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("Ok"),
                                     QObject::tr("delete effectué.\n",
                                                 "click Cancel to exist."), QMessageBox::Cancel);
        }else{
            QMessageBox::information(nullptr, QObject::tr("not ok"),
                                     QObject::tr("delete non effectué.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
        }
         ui->tableView->setModel(aff.afficher());


}

void gestion_affaire::on_tableView_activated(const QModelIndex &index)
{
       QString val = ui->tableView->model()->data(index).toString();

       QSqlQuery query;
        query.prepare("select * from AFFAIRES_JURIDIQUES where NUM_AFF =:val ");
        query.bindValue(":val", val);

       if (query.exec())
       {
           while (query.next())
           {
               //int id=ui->comboBox_2currentText().toInt();

               ui->label_4->setText(query.value(0).toString());
               ui->comboBox_2->clear();
               ui->comboBox_3->clear();

               ui->comboBox_2->addItems(aff.selectid(query.value(0).toString().toInt()));
               ui->comboBox_3->addItems(aff.selectidpri(query.value(0).toString().toInt()));

               ui->comboBox_2->addItems(aff.Addidper(query.value(0).toString().toInt()));
               ui->comboBox_3->addItems(aff.Addidpri(query.value(0).toString().toInt()) );
               ui->type_aff->setText(query.value(3).toString());
               ui->dates->setText(query.value(4).toString());
           }
       }
       else
       {
           QMessageBox::critical(this ,tr("error::"),query.lastError().text());
       }

}

void gestion_affaire::on_modifier_clicked()
{
    QString num_aff=ui->label_4->text();
    QString id_perso =ui->comboBox_2->currentText();
    QString id_priso =ui->comboBox_3->currentText();
    QString type_aff=ui->type_aff->text();
    QString dates=ui->dates->text();

    affaire aff(num_aff,id_perso,id_priso, type_aff,dates);
   bool test=aff.modifier();
    QMessageBox msgBox;
    if(test)
      {  msgBox.setText("Modifier avec succes.");
        ui->tableView->setModel(aff.afficher());
    }
    else
        msgBox.setText("Echec de modification");
      msgBox.exec();
}

void gestion_affaire::on_comboBox_activated(const QString &arg1)
{
   affaire aff;
   QSqlQueryModel * modal = new QSqlQueryModel();
   QSqlQuery * qry = new QSqlQuery();
   if (arg1=="num_aff")
   {
    qry->prepare("Select * from AFFAIRES_JURIDIQUES order by NUM_AFF ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->show();
   }
  else if (arg1=="type")
   {
    qry->prepare("Select * from AFFAIRES_JURIDIQUES order by TYPE_AFF");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->show();
   }

   else if (arg1=="date")
   {
    qry->prepare("Select * from AFFAIRES_JURIDIQUES order by DATES ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->show();
   }
}

void gestion_affaire::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    affaire aff;
    QString inputValue,filtrerChecked;
    inputValue=ui->lineEdit->text();
    ui->tableView->setModel(aff.rechercherdynamique(inputValue,"TYPE_AFF"));
}

void gestion_affaire::on_pushButton_3_clicked()
{
        aff.pdf();
}
void gestion_affaire::makePlot_Type()
{
    QVector<double> x3(aff.dist_type_sum()), y3(20);
    for (int i=0; i<x3.size(); ++i)
    {
      x3[i] = i+1;

    }
    for (int i=0; i<y3.size(); ++i)
    {
      y3[i] = i+1;

    }

    QCPBars *bars1 = new QCPBars(ui->customPlot2->xAxis, ui->customPlot2->yAxis);
    bars1->setWidth(2/(double)x3.size());
    bars1->setData(x3, gestion_affaire::Statistique_Type());
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(200, 40, 60, 170));
    ui->customPlot2->replot();


    // move bars above graphs and grid below bars:
    ui->customPlot2->addLayer("abovemain", ui->customPlot2->layer("main"), QCustomPlot::limAbove);
    ui->customPlot2->addLayer("belowmain", ui->customPlot2->layer("main"), QCustomPlot::limBelow);
    ui->customPlot2->xAxis->grid()->setLayer("belowmain");
    ui->customPlot2->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    QVector<double> Ticks;
    for (int j=1;j<aff.dist_type_sum()+1;j++){
        Ticks<<j;

    }
    QVector<QString> labels;
    for (int i=0;i<aff.dist_type_sum();i++){
        labels<<aff.count_type()[i];
    }
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(Ticks,labels);
    ui->customPlot2->xAxis->setTicker(textTicker);
    ui->customPlot2->xAxis->setSubTicks(false);
    ui->customPlot2->xAxis->setTickLength(0,4);
    ui->customPlot2->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot2->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot2->xAxis->setTickPen(QPen(Qt::transparent, 1));
    ui->customPlot2->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot2->xAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot2->yAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot2->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot2->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot2->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot2->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot2->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot2->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot2->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot2->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot2->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot2->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot2->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot2->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(10, 50, 80));
    plotGradient.setColorAt(1, QColor(10, 20, 50));
    ui->customPlot2->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(10, 50, 80));
    axisRectGradient.setColorAt(1, QColor(0, 0, 30));
    ui->customPlot2->axisRect()->setBackground(axisRectGradient);

    ui->customPlot2->rescaleAxes();
    ui->customPlot2->xAxis->setRange(0, 7);
    ui->customPlot2->yAxis->setRange(0, 10);
}
QVector<double> gestion_affaire::Statistique_Type()
{
    QSqlQuery q;
    QVector<double> stat(aff.dist_type_sum());


    q.prepare("SELECT TYPE_AFF FROM AFFAIRES_JURIDIQUES");
    q.exec();
    while (q.next())
    {
        for (int i=0;i<aff.dist_type_sum();i++){
        if (q.value(0)==aff.count_type()[i]){
            stat[i]++;
        }
       }
    }

    return stat;
}

void gestion_affaire::on_pushButton_6_clicked()
{
    gestion_affaire::makePlot_Type();

}

void gestion_affaire::on_pushButton_4_clicked()
{
    int idjuge = ui->lineEdit_2->text().toInt();
    if(ui->lineEdit_2->text()!=""){
        ui->tableView->setModel(aff.afficher_juge(idjuge));
    }
}

void gestion_affaire::on_pushButton_5_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                            tr("Fichiers d'extension Excel (*.xls)"));
            if (fileName.isEmpty())
                return;

            EXCEL obj(fileName, "AFFAIRES_JURIDIQUES", ui->tableView);

            // you can change the column order and
            // choose which colum to export
            obj.addField(0, "NUM_AFF", "number");
            obj.addField(1, "ID_PERSO", "number");
            obj.addField(2, "ID_PRISO", "number");
            obj.addField(3, "TYPE_AFF", "char(20)");
            obj.addField(4, "DATES", "char(20)");

            int retVal = obj.export2Excel();

            if( retVal > 0)
            {
                QMessageBox::information(this, tr("FAIS!"),
                                         QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                         );
            }
}

void gestion_affaire::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{

}

void gestion_affaire::on_comboBox_2_activated(const QString &arg1)
{

}

void gestion_affaire::on_customPlot2_customContextMenuRequested(const QPoint &pos)
{

}
void gestion_affaire::on_pushButtondeactiver_clicked()
{
    ui->pushButtondeactiver->setStyleSheet("QPushButton:pressed { background-color: green}");
    A.write_to_arduino("0");
}

void gestion_affaire::on_pushButtonactiver_clicked()
{
    ui->pushButtonactiver->setStyleSheet("QPushButton:pressed { background-color: green}");
    A.write_to_arduino("1");
}
