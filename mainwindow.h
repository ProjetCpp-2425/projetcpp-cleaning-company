#ifndef MAINWINDOW_H
#define MAINWINDOW_H
<<<<<<< HEAD
<<<<<<< HEAD
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
=======

#include "transaction.h"
#include <QMainWindow>
#include "arduino.h"
>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
<<<<<<< HEAD
=======

#include <QMainWindow>
#include "employe.h"
#include <QMap>
=======
#include <QMainWindow>
#include <Client.h>
#include<Arduino.h>
>>>>>>> 09fd3e5a0a303ada44e8a58f383005db0699a00f
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

<<<<<<< HEAD
class MainWindow : public QMainWindow {
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
=======
>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

<<<<<<< HEAD
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
=======
    void clearInputFields();

private slots:
    void on_exportButton_clicked();
    void on_exportStatistique_clicked();
    void on_rechercher_clicked();
    void highlightFutureTransactionDates();
    void onComboBoxSelectionChanged(int index);
    void onSearchCriterionChanged(int index);
    void populateClientComboBox();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();
    void update_label();
    bool handleTransaction(int receivedCode);

private:
    Ui::MainWindow *ui;
    Transaction transaction;
    Arduino A;
     QString data;

>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
};

#endif // MAINWINDOW_H

=======
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_modifier_2_clicked();

    void on_modifier_4_clicked();

    void on_ajouter_2_clicked();

    void on_supprimer_2_clicked();

    void on_comboBoxTri_currentIndexChanged(int index);

    void on_rechercherParNom_clicked();

    void on_exportToPDF_clicked();


    void on_stat_methods_clicked();


void addImagesToTableView(QTableView* tableView, QSqlQueryModel* model, int imageColumnIndex);



void on_btnUploadPhoto_clicked();
void afficherPhoto(const QByteArray& imageBytes) ;
void on_comboBox_currentIndexChanged(int index);

void on_btnRecherche_clicked();

void on_comboBoxCritere_currentIndexChanged(int index);

void on_criterComboBox_currentIndexChanged(int index);

void on_rechercheButton_clicked();

void on_criterComboBox_currentTextChanged(const QString &arg1);

void on_pushButtonRecherche_clicked();

void on_lineEditRecherche_textChanged(const QString &arg1);
void update_label();
private:
Client currentClient;
QTimer *alertTimer;
    Ui::MainWindow *ui;
    Client Etmp;
    QByteArray dataBuffer;
    Arduino A;

signals:
    void setLocationMarking(QVariant,QVariant);
    void setCenterPosition(QVariant,QVariant);
};
#endif // MAINWINDOW_H
>>>>>>> 09fd3e5a0a303ada44e8a58f383005db0699a00f
