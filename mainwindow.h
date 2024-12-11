#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <Client.h>

//service
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
#include "employe.h"
#include "materiel.h"
#include "transaction.h"
#include "fournisseur.h"
#include "Arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlQueryModel* verifierStockFaible(int seuil);


private slots:
    void on_modifier_4_clicked();



void on_map_2_clicked();
//service
public slots:
    void on_toolButton_statistiques_clicked();
    void on_toolButton_pdf_clicked();

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

    void on_pushButtonservices_clicked();

    void on_pushButtonclients_clicked();

    void on_label_48_linkActivated(const QString &link);

    void on_pushButton_3_clicked();

    void on_pushButton_26_clicked();

    void on_empbut_2_clicked();

    void on_cliebut_2_clicked();

    void on_fournbut_2_clicked();

    void on_materbut_2_clicked();

    void on_transabut_2_clicked();

    void on_servbut_2_clicked();

    void on_pushButtonRecherche_2_clicked();

    void on_ajouter_4_clicked();

    void on_supprimer_4_clicked();

    void on_comboBoxTri_2_currentIndexChanged(int index);

    void on_modifier_7_clicked();

    void on_exportButton_3_clicked();
    void onImageCellDoubleClicked(const QModelIndex& index);
    void on_stat_methods_clicked();
    void on_exportButton_clicked();

    void trierEmploye();
    void exporterEnPDFF();
    void sendEmail();
    void sendEmailWithAttachment();
    void afficherEmploye();
    void on_rechercher_emp_clicked();
    void on_ajouter_3_clicked();
    void on_modifier_6_clicked();
    void on_supprimer_3_clicked();
    void on_button_stat_clicked();
    void addReminder();
    void showReminders();
    void checkReminders();
    void verifierStockFaible();
    //   void ajouterDansHistorique();

     /*  void enregistrerHistorique(const QString &action, int idMateriel, const QString &qualite, int quantite,
                                      const QString &type, const QDate &dateAchat, double prixAchat,

                                  const QDate &dateVente, double prixVente);

   */


    void on_pushButton_ajouter_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_rechercher_clicked();

    void on_pushButton_trier_clicked();

    void on_pushButton_notification_clicked();
    void highlightFutureTransactionDates();
    void populateClientComboBox();
    void update_label();
    void update_label1();
    void update_label2();

    void onSearchCriterionChanged(int index);

    void on_rechercher_2_clicked();
    void onComboBoxSelectionChanged(int index);

    void on_exportStatistique_clicked();

    void on_exportButton_2_clicked();

    void on_pushButton_ajouter_2_clicked();
    bool handleTransaction(int receivedCode);

    void on_pushButton_modifier_2_clicked();

    void on_pushButton_supprimer_2_clicked();

    void on_afficher_clicked();

    void on_pushButton_clicked();

    void on_supp_clicked();

    void on_modifier_5_clicked();

    void on_rechercher_3_clicked();

    void on_pushButton_4_clicked();
    void checkUpcomingArrivals();
    void updateCalendarWithArrivals();
    void showStatistics();

    void on_pushButton_ExportPDF_clicked();

    void on_calendarWidget_2_selectionChanged();

public:
     void mettreAJourStatistiques();
     void clearInputFields();
     void addDataToTableViewfournisseurCalander(const QList<QMap<QString, QString>>& dataList);
     void highlightReservationDates();


     ///
private:
    Client currentClient;
    Ui::MainWindow *ui;
    Client Etmp;
    //service
    Services serviceActuel;
    int servicesDisponibles;
    int servicesIndisponibles;
    MeteoService *meteoService;
    //QNetworkAccessManager *networkManager;
    QMap<QString, int> calculerDisponibilite();
    //ArduinoManager *arduino;
    //emlpoye
    Employe EmployeActuel;
    QMap<int, QString> employeeReminders; // Clé : ID employé, Valeur : Texte du rappel
    QTimer* reminderTimer;
    Materiel materiel;
    Transaction transaction;
    //fournisseur
    fournisseur tfournisseur;     // Gestion des fournisseurs
    QTimer *alertTimer;           // Timer pour les alertes automatiques
    QString dataBuffer;           // Tampon pour les données Arduino
    QCalendarWidget *calendar;    // Widget pour afficher le calendrier
    bool sortAscending = true;
    QStandardItemModel *model;
    void exportToPDF();
    Arduino A,A1,A2;
    QString data;



signals:
    void setLocationMarking(QVariant,QVariant);
    void setCenterPosition(QVariant,QVariant);




};
#endif // MAINWINDOW_H
