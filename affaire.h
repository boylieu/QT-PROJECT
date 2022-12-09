#ifndef AFFAIRE_H
#define AFFAIRE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>

class affaire
{
    QString num_aff;
    QString id_perso;
    QString id_priso;
    QString type_aff;
    QString dates;
public:
    //constructeurs
    affaire(){};
    affaire(QString ,QString ,QString ,QString  , QString);
    ~affaire(){};

    //Getters
    QString getnum_aff(){return num_aff;}
    QString getcode_perso(){return id_perso;}
    QString getid_priso(){return id_priso;}

    QString gettype_aff(){return type_aff;}
    QString getdate(){return dates;}
    void setnum_aff(QString aff){num_aff=aff;}
    void setid_perso(QString perso ){id_perso=perso;}
    void settype_aff(int type){type_aff=type;}
    //fonctionnalites de base relatives a l'entite affaire
    bool ajouter ();
    QSqlQueryModel* afficher();
    bool  supprimer(QString );
    bool modifier();
    QStringList afficher_ID_PER();
    QStringList afficher_ID_PRI();

    QStringList Addidper(int);
    QStringList Addidpri(int);
    QStringList selectid(int);
    QStringList selectidpri(int);
    QStringList count_type();
    int dist_type_sum();
    QSqlQueryModel* afficher_juge(int);


    QSqlQueryModel * rechercherdynamique(QString input,QString filtrer);
    void pdf();

    void ajoutdate();

};

#endif // AFFAIRE_H
