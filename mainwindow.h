#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "personnel.h"
#include "arduino.h"
#include <QMainWindow>
#include"QPdfWriter"
#include"QDesktopServices"
#include <QComboBox>
#include <QPixmap>

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
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_pdf_clicked();

    void on_rechercher_clicked ();

    void on_trier_clicked ();

    void on_comboBox_activated(const QString &arg1);

    void on_sms_clicked();

    void update_label();

    void on_arduino_clicked();

private:
    Ui::MainWindow *ui;
    QByteArray data;
    Personnel P;
    Arduino A;
};
#endif // MAINWINDOW_H
