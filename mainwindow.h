#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMainWindow>
#include "rdv.h"
#include <QCalendarWidget>
#include "stat_combo.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_bt_ajouter_clicked();

    void on_le_num_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_rdv_supp_clicked();

    void on_bt_aff_clicked();

    void on_bt_mod_clicked();

    void on_confirmer_clicked();

    void on_rechercher_clicked();

    void on_le_num_textChanged(const QString &arg1);

    void on_le_nom_textChanged(const QString &arg1);

    void on_combo_box_tri_currentIndexChanged(int index);

    void on_combo_box_prenom_currentIndexChanged(int index);

    void on_combo_box_nom_currentTextChanged(const QString &arg1);

    void on_rech_textChanged(const QString &arg1);

    void on_PDF_clicked();

    void on_stat_clicked();
        void sendMail();
        void mailSent(QString);
        void browse();
        void on_sendBtn_clicked();
        QString get_d ()const;

        void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;
    Rdv R;
    QStringList files;
    stat_combo *s;
};
#endif // MAINWINDOW_H
