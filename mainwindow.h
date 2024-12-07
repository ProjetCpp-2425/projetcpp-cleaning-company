#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
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
};

#endif // MAINWINDOW_H

