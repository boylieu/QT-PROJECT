#include "personnel.h"
#include <QDebug>

 Personnel:: Personnel()

{
id="";
nom_pers="";
prenom_pers="";
fonction = "";
CIN_pers = 0;
telephone_pers=0;
}


 Personnel::Personnel ( QString id ,QString nom_pers,QString prenom_pers , QString fonction , int CIN_pers , int telephone_pers)
{
  this->id=id;
  this->nom_pers=nom_pers;
  this->prenom_pers=prenom_pers;
  this -> fonction = fonction ;
  this -> CIN_pers = CIN_pers;
  this -> telephone_pers = telephone_pers;
}


bool Personnel::ajouter()
{
QSqlQuery query;
//QString res= QString::number(id);
query.prepare("INSERT INTO personnel (ID, NOM_PERS, PRENOM_PERS,FONCTION, CIN_PERS , TELEPHONE_PERS ) "
                    "VALUES (:id, :nom_pers, :prenom_pers, :fonction, :CIN_pers, :telephone_pers)");
query.bindValue(":id", id);
query.bindValue(":nom_pers", nom_pers);
query.bindValue(":prenom_pers", prenom_pers);
query.bindValue(":fonction", fonction);
query.bindValue(":CIN_pers", CIN_pers);
query.bindValue(":telephone_pers", telephone_pers);

return    query.exec();
}

QSqlQueryModel *  Personnel::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from  personnel");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fonction"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));
    return model;
}


bool Personnel::supprimer (QString idd)
{
QSqlQuery query;
//QString res= QString::number(idd);
query.prepare("Delete from  personnel where ID = :id ");
query.bindValue(":id", idd);
return query.exec();
}



bool  Personnel::modifier()
{
    QSqlQuery query;

       query.prepare("UPDATE  personnel NOM_PERS =:nom_pers, PRENOM_PERS =:prenom_pers ,FONCTION=:fonction , CIN_PERS =:CIN_pers , TELEPHONE_PERS =:telephone_pers WHERE ID=:id");
       query.bindValue(":id", id);
       query.bindValue(":nom_pers", nom_pers);
       query.bindValue(":prenom_pers", prenom_pers);
       query.bindValue(":fonction", fonction);
       query.bindValue(":CIN_pers", CIN_pers);
       query.bindValue(":telephone_pers", telephone_pers);

    return query.exec();
}

QSqlQueryModel * Personnel:: trier(QString)
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from  personnel");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fonction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));

    return model;
}
