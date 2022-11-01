#ifndef Prisonniers_H
#define Prisonniers_H
#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QDateEdit>
#include <QDebug>

class Prisonniers
{
public:
    Prisonniers();
    Prisonniers(QString,QString,QString,QString,int,int);
    QString getNomPriso() {return nom_priso;};
    QString getPrenomPriso() {return prenom_priso;};
    QString getIdpriso() {return id_priso;};
    QString getcrime() {return crime;};
    int  getCinPers(){return CIN_priso;};
    int  getAge(){return age;};
    void set_id_priso(QString i) {id_priso = i; };
    void set_prenom_priso(QString p) {prenom_priso = p; } ;
    void set_nom_priso(QString n) {nom_priso = n; };
    void set_CIN_priso(int c) {CIN_priso = c; };
    void set_Age(int a) {age = a; };
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier() ;

private:
    QString nom_priso,prenom_priso,id_priso,crime;
    int CIN_priso,age;
};

#endif // Prisonniers_H

