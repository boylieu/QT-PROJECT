#ifndef RDV_H
#define RDV_H
#include <QString>
#include <QSqlQueryModel>
class Rdv
{
public:
    Rdv();
    Rdv(int,int,int,QString,QString,QString,QString);
    int getnum();
    int getnum_salle();
    int getid_perso();
    QString gettype();
    //QString getdate();
    QString getetat();
    QString getnom_cit();
    QString getprenom_cit();
    void setnum(int);
    void setnum_salle(int);
    void setid_pero(int);
    void settype(QString);
    //void setdate(QString);
    void setetat(QString);
    void setnom_cit(QString);
    void setprenom_cit(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int );


private:
    int num;
    int num_salle;
    int id_perso;
    QString type,etat,nom_cit,prenom_cit ;



};

#endif // RDV_H
