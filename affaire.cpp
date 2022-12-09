#include "affaire.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QString>
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
#include "gestion_affaire.h"
#include "ui_gestion_affaire.h"

affaire::affaire(QString num_aff ,QString id_perso ,QString id_priso , QString type_aff , QString dates)
{
this->num_aff=num_aff;
this->id_perso=id_perso;
this->id_priso=id_priso;
this->type_aff=type_aff;
this->dates=dates;
}
bool affaire :: ajouter()
{ QSqlQuery query;

    query.prepare("insert into AFFAIRES_JURIDIQUES(NUM_AFF,ID_PERSO,ID_PRISO, TYPE_AFF ,DATES) values (:NUM_AFF,:ID_PERSO,:ID_PRISO,:TYPE_AFF,:DATE)");
    query.bindValue(":NUM_AFF",num_aff);
    query.bindValue(":ID_PERSO",id_perso);
    query.bindValue(":ID_PRISO",id_priso);
    query.bindValue(":TYPE_AFF",type_aff);
    query.bindValue(":DATE",dates);

    return query.exec();

}
QSqlQueryModel * affaire :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select NUM_AFF,ID_PERSO,ID_PRISO,TYPE_AFF,DATES from AFFAIRES_JURIDIQUES");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_AFF"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_PERSO"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID_PRISO"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("TYPE_AFF"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATES"));
return model;
}
bool affaire :: supprimer(QString num_aff)
{
    QSqlQuery query;

    query.prepare("Delete from AFFAIRES_JURIDIQUES where NUM_AFF= :NUM_AFF");
    query.bindValue(0,num_aff);
    return query.exec();
}
bool  affaire::modifier()
{
    QSqlQuery query;

       query.prepare("UPDATE AFFAIRES_JURIDIQUES SET ID_PERSO =:ID_PERSO ,ID_PRISO=:ID_PRISO , TYPE_AFF =:TYPE_AFF ,DATES =:DATES WHERE NUM_AFF=:NUM_AFF");
       query.bindValue(":NUM_AFF", num_aff);
       query.bindValue(":ID_PERSO", id_perso);
       query.bindValue(":ID_PRISO", id_priso);
       query.bindValue(":TYPE_AFF", type_aff);
       query.bindValue(":DATES", dates);

    return query.exec();
}

QSqlQueryModel* affaire::rechercherdynamique(QString input, QString filtrer)
{
    QSqlQueryModel * modal=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM AFFAIRES_JURIDIQUES WHERE "+filtrer+" LIKE '%' || :inputValue || '%'");
    query.bindValue(":inputValue",input);
    query.exec();
    modal->setQuery(query);
    return modal;

}

QStringList affaire :: afficher_ID_PER()
{
    QStringList rfid;

    QSqlQuery query;
    query.prepare("select ID_PERSO from PERSONNEL");
    if(query.exec()){
         while( query.next() ) {
             rfid.append(query.value( 0 ).toString());
         }
    }
    return rfid;
}
QStringList affaire :: afficher_ID_PRI()
{
    QStringList affi;

    QSqlQuery query;
    query.prepare("select ID_PRISO from PRISONNIER");
    if(query.exec()){
         while( query.next() ) {
             affi.append(query.value( 0 ).toString());
         }
    }
    return affi;
}

QStringList affaire :: selectid(int nA)
{
    QStringList affi;

    QSqlQuery query;
    query.prepare("SELECT ID_PERSO FROM AFFAIRES_JURIDIQUES WHERE NUM_AFF =:nA");
    query.bindValue(":nA",nA);

    if(query.exec()){
         while( query.next() ) {
             affi.append(query.value( 0 ).toString());
         }
    }
    return affi;
}
QStringList affaire :: selectidpri(int nA)
{
    QStringList affi;

    QSqlQuery query;
    query.prepare("SELECT ID_PRISO FROM AFFAIRES_JURIDIQUES WHERE NUM_AFF =:nA");
    query.bindValue(":nA",nA);

    if(query.exec()){
         while( query.next() ) {
             affi.append(query.value( 0 ).toString());
         }
    }
    return affi;
}


QStringList affaire :: Addidper(int nA)
{
    QStringList affi;

    QSqlQuery query;
    query.prepare("SELECT P.ID_PERSO FROM PERSONNEL P inner join AFFAIRES_JURIDIQUES J on P.ID_PERSO != J.ID_PERSO where J.NUM_AFF =:nA");
    query.bindValue(":nA",nA);

    if(query.exec()){
         while( query.next() ) {
             affi.append(query.value( 0 ).toString());
         }
    }
    return affi;
}

QStringList affaire :: Addidpri(int nA)
{

    QStringList affi;

    QSqlQuery query;
    query.prepare("SELECT P.ID_PRISO FROM PRISONNIER P inner join AFFAIRES_JURIDIQUES J on P.ID_PRISO != J.ID_PRISO where J.NUM_AFF =:nA");
    query.bindValue(":nA",nA);

    if(query.exec()){
         while( query.next() ) {
             affi.append(query.value( 0 ).toString());
         }
    }
    return affi;
}

QStringList affaire :: count_type() //eviter les répititions
{
    QStringList typeLi;

    QSqlQuery query;
    query.prepare("SELECT distinct(TYPE_AFF) FROM AFFAIRES_JURIDIQUES");
    if(query.exec()){
         while( query.next() ) {
             typeLi.append(query.value( 0 ).toString());
         }
    }
    return typeLi;
}


int affaire :: dist_type_sum() // somme de les types
{
    int sum=0;

    QSqlQuery query;
    query.prepare("SELECT distinct(TYPE_AFF) FROM AFFAIRES_JURIDIQUES");

    if(query.exec()){
         while( query.next() ) {
             sum++;
         }
    }
    return sum;
}

QSqlQueryModel * affaire :: afficher_juge(int jugeid)
{
QSqlQueryModel * model=new QSqlQueryModel();
QSqlQuery query;
query.prepare("select NUM_AFF,ID_PERSO,ID_PRISO,TYPE_AFF,DATES from AFFAIRES_JURIDIQUES where ID_PERSO=:jugeid");
query.bindValue(":jugeid",jugeid);
query.exec();
model->setQuery(query);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_AFF"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_PERSO"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID_PRISO"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("TYPE_AFF"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATES"));
return model;
}

void affaire :: pdf(){
    gestion_affaire w ;
    QString strStream;
    QTextStream out(&strStream);

     const int rowCount = w.ui->tableView->model()->rowCount();
     const int columnCount = w.ui->tableView->model()->columnCount();
    out <<  "<html>\n"
    "<head>\n"
                     "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                     <<  QString("<title>%1</title>\n").arg("strTitle")
                     <<  "</head>\n"
                     "<body bgcolor=#ffffff link=#5000A0>\n"

                    //     "<align='right'> " << datefich << "</align>"
                     "<center> <H1>Liste des Affaires </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                 // headers
                 out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                 for (int column = 0; column < columnCount; column++)
                     if (!w.ui->tableView->isColumnHidden(column))
                         out << QString("<th>%1</th>").arg(w.ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                 out << "</tr></thead>\n";

                 // data table
                 for (int row = 0; row < rowCount; row++) {
                     out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                     for (int column = 0; column < columnCount; column++) {
                         if (!w.ui->tableView->isColumnHidden(column)) {
                             QString data = w.ui->tableView->model()->data(w.ui->tableView->model()->index(row, column)).toString().simplified();
                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                         }
                     }
                     out << "</tr>\n";
                 }
                 out <<  "</table> </center>\n"
                     "</body>\n"
                     "</html>\n";

           QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
             if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

            QPrinter printer (QPrinter::PrinterResolution);
             printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);

            QTextDocument doc;
             doc.setHtml(strStream);
             doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
             doc.print(&printer);
}
void affaire::ajoutdate()
{
    QSqlQuery query;
    QString id_string=QString::number(1);
    query.prepare("insert into salle(idsalle,datee)values(:id,TO_DATE(sysdate, 'dd/mm/yyyy'))");
    query.bindValue(":NUM_AFF",id_string);
     query.exec();
}
