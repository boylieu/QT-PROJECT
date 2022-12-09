#ifndef GESTION_RDV_H
#define GESTION_RDV_H
#include "ui_gestion_affaire.h"
#include <QFileDialog>

#include <QMainWindow>

#include "rdv.h"

#include <QCalendarWidget>

//#include "stat_combo.h"

#include "arduino.h"

QT_BEGIN_NAMESPACE

namespace Ui { class gestion_rdv; }

QT_END_NAMESPACE



class gestion_rdv : public QMainWindow

{

    Q_OBJECT



public:

    gestion_rdv(QWidget *parent = nullptr);

    ~gestion_rdv();
    Ui::gestion_rdv *ui;





private slots:

    void on_bt_ajouter_clicked();



    //void on_le_num_cursorPositionChanged(int arg1, int arg2);



    //void on_pushButton_3_clicked();



    void on_pushButton_clicked();



    void on_rdv_supp_clicked();



    //void on_bt_aff_clicked();



    void on_bt_mod_clicked();



    void on_confirmer_clicked();



    //void on_rechercher_clicked();



    //void on_le_num_textChanged(const QString &arg1);



    //void on_le_nom_textChanged(const QString &arg1);



    //void on_combo_box_tri_currentIndexChanged(int index);



    //void on_combo_box_prenom_currentIndexChanged(int index);



    void on_combo_box_nom_currentTextChanged(const QString &arg1);



    void on_rech_textChanged(const QString &arg1);



    void on_PDF_clicked();



    //void on_stat_clicked();

        //void sendMail();

        //void mailSent(QString);

       // void browse();

        void on_sendBtn_clicked();

        //QString get_d ()const;

        //void update_label();

        //void on_calendarWidget_clicked(const QDate &date);



        void on_confsalle_clicked();



private:

    Rdv R;

    QStringList files;

    //stat_combo *s;

    QByteArray data;

    Arduino A;

};

#endif // GESTION_RDV_H
