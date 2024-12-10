#ifndef MAINWINDOW_H
#define MAINWINDOW_H
<<<<<<< HEAD
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>

#include <QMainWindow>
#include "services.h"
#include "meteoservices.h"
//#include "arduinomanager.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
=======

#include <QMainWindow>
#include "employe.h"
#include <QMap>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
<<<<<<< HEAD
    void showLoginPage();  // Naviguer vers la page de login
    void validateLogin();  // Valider les identifiants
void showhomepage();
void on_ajouter_clicked();
void on_modifier_clicked();
void on_supprimer_clicked();
void afficherServices();
void on_rechercher_clicked();
QString getDescriptionForService(const QString &nomService);
void recevoirPrevisionsMeteo(const QString &condition, double temperature, bool pluiePrevue);
void ajusterPlanification(const QString &condition, double temperature, bool pluiePrevue);
void rafraichirTableauServices();
void mettreAJourDisponibilite(bool disponible, const QString &motCle);
void trierServices();
void exporterEnPDF();

public:
     void mettreAJourStatistiques();
private:
    Ui::MainWindow *ui;
    Services serviceActuel;
    int servicesDisponibles;
    int servicesIndisponibles;
    MeteoService *meteoService;
//    QNetworkAccessManager *networkManager;



    QMap<QString, int> calculerDisponibilite();
    //ArduinoManager *arduino;
=======
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
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
};

#endif // MAINWINDOW_H

