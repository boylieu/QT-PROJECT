#include "rdv.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include<QObject>
Rdv::Rdv()
{
num=0 ;
num_salle=0 ;
id_perso=0 ;
type=" ";
//date=" ";
etat=" ";
nom_cit=" ";
prenom_cit=" ";
}
Rdv::Rdv(int num,int num_salle,int id_perso,QString type,QString etat,QString nom_cit,QString prenom_cit)
{
this->num=num;
this->num_salle=num_salle;
this->id_perso=id_perso;
this->type=type;
//this->date=date;
this->etat=etat;
this->nom_cit=nom_cit;
this->prenom_cit=prenom_cit;
}

int Rdv::getnum(){return num;}
int Rdv::getnum_salle(){return num_salle;}
int Rdv::getid_perso(){return id_perso; }
QString Rdv::gettype(){return type;}
//QString Rdv::getdate(){return date;}
QString Rdv::getetat(){return etat;}
QString Rdv::getnom_cit(){return nom_cit;}
QString Rdv::getprenom_cit(){return prenom_cit;}
void Rdv::setnum(int num){this->num=num;}
void Rdv::setnum_salle(int num_salle){this->num_salle=num_salle;}
void Rdv::setid_pero(int id_perso){this->id_perso=id_perso;}
void Rdv::settype(QString type){this->type=type;}
//void Rdv::setdate(QString date){this->date=date;}
void Rdv::setetat(QString etat){this->etat=etat;}
void Rdv::setnom_cit(QString nom_cit){this->nom_cit=nom_cit;}
void Rdv::setprenom_cit(QString prenom_cit){this->prenom_cit=prenom_cit;}
bool Rdv::ajouter()
{
    QSqlQuery query;
    QString id_perso_string=QString::number(id_perso);
    QString num_salle_string=QString::number(num_salle);
    QString num_string=QString::number(num);
    query.prepare("INSERT INTO RDV (num, num_salle, etat_rdv, nom_cit, prenom_cit, id, type) "
                  "VALUES (:numero, :numero_s, :etat, :nom, :prenom, :id, :type )");
    query.bindValue(":numero", num_string);
   // query.bindValue(":date", date);
    query.bindValue(":numero_s", num_salle_string);
    query.bindValue(":etat", etat);
    query.bindValue(":nom", nom_cit);
    query.bindValue(":prenom", prenom_cit);
    query.bindValue(":id", id_perso_string);
    query.bindValue(":type", type);
     return query.exec();
}
bool Rdv::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from RDV where num=:id") ;
    query.bindValue(0,num);

    return  query.exec();
}
QSqlQueryModel* Rdv::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM RDV");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("numero rdv"));
       // model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("numero salle"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat rdv"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom citoyen"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prenom citoyen"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("identifiant personnel"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("type rdv"));


    return model;
}
bool Rdv::modifier(int num)
{
    QSqlQuery  Q1;
    QString id_perso_string=QString::number(id_perso);
    QString num_salle_string=QString::number(num_salle);
    QString num_string=QString::number(num);
    Q1.prepare("update RDV set num=:numero, num_salle=:numero_s, etat_rdv=:etat, nom_cit=:nom, prenom_cit=:prenom, id=:id, type=:type");
    Q1.bindValue(":numero", num_string);
   // query.bindValue(":date", date);
    Q1.bindValue(":numero_s", num_salle_string);
    Q1.bindValue(":etat", etat);
    Q1.bindValue(":nom", nom_cit);
    Q1.bindValue(":prenom", prenom_cit);
    Q1.bindValue(":id", id_perso_string);
    Q1.bindValue(":type", type);
     return Q1.exec();
}

