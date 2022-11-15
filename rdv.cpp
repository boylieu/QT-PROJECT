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
Rdv::Rdv(int num,int num_salle,int id_perso,QString type,QString etat,QString nom_cit,QString prenom_cit,QString date)
{
this->num=num;
this->num_salle=num_salle;
this->id_perso=id_perso;
this->type=type;
date_rdv=date;
this->etat=etat;
this->nom_cit=nom_cit;
this->prenom_cit=prenom_cit;
}
int Rdv::getnum(){return num;}
int Rdv::getnum_salle(){return num_salle;}
int Rdv::getid_perso(){return id_perso; }
QString Rdv::gettype(){return type;}
QString Rdv::getdate(){return date_rdv;}
QString Rdv::getetat(){return etat;}
QString Rdv::getnom_cit(){return nom_cit;}
QString Rdv::getprenom_cit(){return prenom_cit;}
void Rdv::setnum(int num){this->num=num;}
void Rdv::setnum_salle(int num_salle){this->num_salle=num_salle;}
void Rdv::setid_pero(int id_perso){this->id_perso=id_perso;}
void Rdv::settype(QString type){this->type=type;}
void Rdv::setdate(QString date_rdv){this->date_rdv=date_rdv;}
void Rdv::setetat(QString etat){this->etat=etat;}
void Rdv::setnom_cit(QString nom_cit){this->nom_cit=nom_cit;}
void Rdv::setprenom_cit(QString prenom_cit){this->prenom_cit=prenom_cit;}
bool Rdv::ajouter()
{
    QSqlQuery query;
    QString id_perso_string=QString::number(id_perso);
    QString num_salle_string=QString::number(num_salle);
    QString num_string=QString::number(num);
    query.prepare("INSERT INTO RDV (num, num_salle, etat_rdv, nom_cit, prenom_cit, id, type, date_rdv) "
                  "VALUES (:numero, :numero_s, :etat, :nom, :prenom, :id, :type, :date )");
    query.bindValue(":numero", num_string);
    query.bindValue(":date", date_rdv);
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
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("numero salle"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat rdv"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom citoyen"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prenom citoyen"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("identifiant personnel"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("type rdv"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date"));
    return model;
}
bool Rdv::modifier()
{
    QSqlQuery  query;
    QString id_perso_string=QString::number(id_perso);
    QString num_salle_string=QString::number(num_salle);
    QString num_string=QString::number(num);
    query.prepare("Update RDV set num=:numero, num_salle=:numero_s, etat_rdv=:etat, nom_cit=:nom, prenom_cit=:prenom, id=:id, type=:type, date_rdv=:date where num= :numero ");
    query.bindValue(":numero", num_string);
    query.bindValue(":numero_s", num_salle_string);
    query.bindValue(":etat", etat);
    query.bindValue(":nom", nom_cit);
    query.bindValue(":prenom", prenom_cit);
    query.bindValue(":id", id_perso_string);
    query.bindValue(":type", type);
    query.bindValue(":date", date_rdv);
     return query.exec();
}

QSqlQueryModel * Rdv::rechercherNom(QString nom)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from Rdv where nom_cit like '"+nom+"%' or prenom_cit LIKE '"+nom+"%' ");
    q.addBindValue("%"+ nom +"%");
    q.exec();
    model->setQuery(q);
    return (model);
}
QSqlQueryModel * Rdv::tri_nom()
{
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();
    query.prepare("SELECT * FROM RDV ORDER BY nom_cit");
    query.exec();
    model->setQuery(query);

    return model;
}
QSqlQueryModel * Rdv::tri_num()
{
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();

    query.prepare("SELECT * FROM RDV ORDER BY num");
    query.exec();
    model->setQuery(query);
    return model;
}
QSqlQueryModel * Rdv::tri_prenom()
{
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();

    query.prepare("SELECT * FROM RDV ORDER BY prenom_cit");
    query.exec();
    model->setQuery(query);
    return model;
}
