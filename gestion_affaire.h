#ifndef gestion_affaire_H
#define gestion_affaire_H
#include "affaire.h"
#include <QMainWindow>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class gestion_affaire; }
QT_END_NAMESPACE

class gestion_affaire : public QMainWindow
{
    Q_OBJECT

public:
    gestion_affaire(QWidget *parent = nullptr);
    ~gestion_affaire();
 Ui::gestion_affaire *ui;
private slots :
    void on_ajouter_clicked();



    void on_suprimer_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_modifier_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_3_clicked();
    void makePlot_Type();
    QVector<double> Statistique_Type();


    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_2_activated(const QString &arg1);

    void on_customPlot2_customContextMenuRequested(const QPoint &pos);
    void updatelabel();



    void on_pushButtondeactiver_clicked();

    void on_pushButtonactiver_clicked();

private:

    affaire aff;
    Arduino A ;
    QByteArray data;
};
#endif // gestion_affaire_H
