#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDebug>

class Personnel
{
public:
    Personnel();
    Personnel(QString,QString,QString,QString,int,int);
    QString getNomPers() {return nom_pers;};
    QString getPrenomPers() {return prenom_pers;};
    QString getId() {return id;};
    QString getFonction() {return fonction;};
    int  getCinPers(){return CIN_pers;};
    int  getTelephonePers(){return telephone_pers;};
    void set_id(QString i) {id = i;};
    void set_prenom(QString p){ prenom_pers = p;} ;
    void set_nom(QString n) {nom_pers= n;} ;
    void set_CIN(int c) {CIN_pers = c;};
    void set_telephone(int t){telephone_pers = t;};
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier() ;
    bool verifierId(int  id);
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel *  trier(QString);
    QSqlQueryModel *  stats();

private:
    QString nom_pers,prenom_pers,id,fonction;
    int CIN_pers,telephone_pers;
};

#endif // PERSONNEL_H

