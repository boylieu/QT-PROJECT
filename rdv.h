#ifndef RDV_H
#define RDV_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
class Rdv
{
public:
    Rdv();
    Rdv(int num,int num_salle,int id_perso,QString type,QString etat,QString nom_cit,QString prenom_cit,QString date);
    int getnum();
    int getnum_salle();
    int getid_perso();
    QString gettype();
    QString getdate();
    QString getetat();
    QString getnom_cit();
    QString getprenom_cit();
    void setnum(int);
    void setnum_salle(int);
    void setid_pero(int);
    void settype(QString);
    void setdate(QString);
    void setetat(QString);
    void setnom_cit(QString);
    void setprenom_cit(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * rechercherNom(QString);
    QSqlQueryModel * tri_num();
    QSqlQueryModel * tri_nom();
     QSqlQueryModel * tri_prenom();
     //QChart * stat();


private:
    int num;
    int num_salle;
    int id_perso;
    QString type,etat,nom_cit,prenom_cit ;
    QString date_rdv;




};

#endif // RDV_H
