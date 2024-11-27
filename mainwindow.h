#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include <QMap>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void afficherEmploye();
void on_rechercher_clicked();
void trierEmploye();void exporterEnPDF();
void on_stat_employes_clicked();
void sendEmail();
void sendEmailWithAttachment();
private:
    Ui::MainWindow *ui;
    Employe EmployeActuel;






private:
    QMap<int, QString> employeeReminders; // Clé : ID employé, Valeur : Texte du rappel
    QTimer* reminderTimer;

private slots:
    void addReminder();
    void showReminders();
    void checkReminders();
};

#endif // MAINWINDOW_H

