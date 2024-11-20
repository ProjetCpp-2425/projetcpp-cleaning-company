#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStandardItem>
#include <QMainWindow>
#include "services.h"
#include "meteoservices.h"
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
    void afficherServices();
void on_rechercher_clicked();
QString getDescriptionForService(const QString &nomService);
void recevoirPrevisionsMeteo(const QString &condition, double temperature, bool pluiePrevue);
    void ajusterPlanification(const QString &condition, double temperature, bool pluiePrevue);
    void rafraichirTableauServices();
    void mettreAJourDisponibilite(bool disponible, const QString &motCle);
void trierServices();
void exporterEnPDF();
//void analyserTendances(); // Slot pour analyser les tendances
    //void onTrendsDataReceived(QNetworkReply *reply);
public:
     void mettreAJourStatistiques();

private:
    Ui::MainWindow *ui;
    Services serviceActuel;
    int servicesDisponibles;
    int servicesIndisponibles;
    MeteoService *meteoService;
   /* QStandardItemModel *recommandationsModel; // Modèle pour afficher les recommandations
       QNetworkAccessManager *networkManager; // Pour envoyer les requêtes réseau
       void afficherRecommandations(const QJsonArray &tendances);*/

    QMap<QString, int> calculerDisponibilite();
};

#endif // MAINWINDOW_H

