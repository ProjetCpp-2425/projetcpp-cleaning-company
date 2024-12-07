#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphiquewidget.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QSqlError>
#include <QFileDialog>
#include<QSqlTableModel>
#include<QStandardItemModel>
#include "arduinomanager.h"
#include "services.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    // Connecter les boutons aux actions correspondantes
    connect(ui->pushButtonemployes, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->pushButtonservices, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->pushButtontransactions, &QPushButton::clicked, this, &MainWindow::showLoginPage);

    connect(ui->pushButtonmateriels, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->pushButtonclients, &QPushButton::clicked, this, &MainWindow::showLoginPage);
    connect(ui->pushButtonfournisseurs, &QPushButton::clicked, this, &MainWindow::showLoginPage);

    connect(ui->pushButton_login, &QPushButton::clicked, this, &MainWindow::validateLogin);
    connect(ui->deconnexion, &QPushButton::clicked, this, &MainWindow::showhomepage);
    this->setEnabled(true);
    ui-> nom ->setEnabled(true);
    ui-> id->setEnabled(true);
    ui->doubleSpinBoxprix ->setEnabled(true);
    ui-> duree->setEnabled(true);
    ui-> disponibilite->setEnabled(true);
    ui->etat ->setEnabled(true);
    ui->comboBox->addItem("Disponibilité", "disponibilite");
    ui->comboBox->addItem("État", "etat");
    ui->comboBox->addItem("Coût", "prix");




    // Connexion à l'Arduino via un port série (exemple: COM3)

     connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
             this, &MainWindow::trierServices);
     connect(ui->exporterPDFButton, &QToolButton::clicked, this, &MainWindow::exporterEnPDF);


 meteoService = new MeteoService(this);
     connect(meteoService, &MeteoService::meteoRecue, this, [this](double temperature, QString description) {
         qDebug() << "Météo reçue ! Température :" << temperature << "°C, Description :" << description;
         bool pluiePrevue = description.contains("rain", Qt::CaseInsensitive);
         ajusterPlanification(description, temperature, pluiePrevue); });
          meteoService->getMeteoActuelle("AMSTERDAM");


           mettreAJourStatistiques();
           update();
           afficherServices();
           //envoyerServicesDisponiblesActifs();
}

MainWindow::~MainWindow()
{
delete ui;
delete meteoService;
}

void MainWindow::showLoginPage()
{
    // Afficher la page de login dans le QStackedWidget
    ui->stackedWidget->setCurrentIndex(1); // 1 correspond à la page de login
}

void MainWindow::validateLogin()
{
    QString username = ui->LineEdit_username->text();
    QString password = ui->LineEdit_password->text();

    if (username == "admin" && password == "services") {
        QMessageBox::information(this, "Succès", "Connexion réussie !");
       ui->stackedWidget->setCurrentIndex(2);  // Retourner à la page principale



    } else {
        QMessageBox::warning(this, "Échec", "Nom d'utilisateur ou mot de passe incorrect.");
        ui->stackedWidget->setCurrentIndex(0);
    }
}
void MainWindow::showhomepage() {
 ui->stackedWidget->setCurrentIndex(0) ;}
void MainWindow::on_ajouter_clicked() {
    // Récupération de l'ID
    int id = ui->id->text().toInt();

    // Vérification que l'ID est un entier positif
    if (id <= 0) {
        QMessageBox::warning(this, "Erreur de saisie", "L'ID doit être un entier positif.");
        return;
    }

    // Vérification d'unicité
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM Services WHERE id = :id");
    checkQuery.bindValue(":id", id);
    checkQuery.exec();

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Erreur", "L'ID existe déjà. Veuillez entrer un ID unique.");
        return;
    }

    // Si toutes les vérifications sont passées, ajout du service
    QString nom = ui->nom->text();
    QString duree = ui->duree->text();
    double prix = ui->doubleSpinBoxprix->value();
    QString disponibilite = ui->disponibilite->text();
    QString etat = ui->etat->text();

    Services service(id, nom, duree, prix, disponibilite, etat);
    bool test = service.ajouter();
    if (test) {
        QMessageBox::information(this, "Succès", "Service ajouté avec succès.");
        afficherServices();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du service.");
    }
mettreAJourStatistiques();
}

// Fonction pour modifier un service
void MainWindow::on_modifier_clicked() {
    int id = ui->id->text().toInt();

    // Vérifiez si l'ID existe
    if (id == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide pour modifier.");
        return;
    }

    // Récupérer le service existant avec l'ID donné
      Services serviceExistant = Services::getById(id);

    // Mise à jour uniquement des champs modifiés
    QString nom = ui->nom->text();
    if (!nom.isEmpty()) {
        serviceExistant.setNom(nom);
    }

    QString duree = ui->duree->text();
    if (!duree.isEmpty()) {
        serviceExistant.setDuree(duree);
    }

    double prix = ui->doubleSpinBoxprix->value();
    if (prix != serviceExistant.getPrix()) {
        serviceExistant.setPrix(prix);
    }

    QString disponibilite = ui->disponibilite->text();
    if (!disponibilite.isEmpty()) {
        serviceExistant.setDisponibilite(disponibilite);
    }

    QString etat = ui->etat->text();
    if (!etat.isEmpty()) {
        serviceExistant.setEtat(etat);
    }

    // Appeler la méthode de mise à jour
    if (serviceExistant.modifier(id)) {
        QMessageBox::information(this, "Succès", "Service modifié avec succès.");
        afficherServices();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du service.");
    }
mettreAJourStatistiques();
}


// Fonction pour supprimer un service
void MainWindow::on_supprimer_clicked() {
    int id = ui->id->text().toInt();
    serviceActuel.setId(id);

    if (serviceActuel.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Service supprimé avec succès.");
        afficherServices();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du service.");
    }
mettreAJourStatistiques();}

// Fonction pour afficher tous les services dans le QTableView
void MainWindow::afficherServices()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model = serviceActuel.afficher();
    ui->tableViewServices->setModel(model);
}


void MainWindow::on_rechercher_clicked() {
    QString critere = ui->champRecherche->text();  // champRecherche est l'input utilisateur pour recherche

    // Appeler la fonction de recherche de la classe Services
    Services service;
    QSqlQueryModel* model = service.rechercher(critere);

    // Mettre à jour la vue tableau avec les résultats
    ui->tableViewServices->setModel(model);
}
void MainWindow::trierServices() {
 Services service;   QString critereTri = ui->comboBox->currentData().toString();
    QSqlQueryModel* model = service.trierParCritere(critereTri);
    ui->tableViewServices->setModel(model);
}
QString MainWindow::getDescriptionForService(const QString &nomService) {
    // Définir les descriptions par défaut en fonction du nom du service
    if (nomService == "desinfection") {
        return "Service de désinfection complet pour les usines, en tenant compte des zones à haut risque. Désinfection des surfaces, équipements et zones sensibles.";
    } else if (nomService == "maison") {
        return "Service de nettoyage approfondi de la maison, y compris le lavage des sols, des fenêtres et des surfaces. Un service de qualité pour rendre votre maison impeccable.";
    } else if (nomService == "résidence") {
        return "Service de nettoyage pour les résidences, en veillant à l'entretien des espaces de vie et des zones communes, avec une attention particulière aux détails.";
    } else if (nomService == "chantier") {
        return "Nettoyage de fin de chantier, incluant l'enlèvement des débris, la poussière, et la préparation des locaux pour leur utilisation.";
       } else if (nomService == "usine") {
               return "Service de nettoyage pour les usines , en veillant à l'entretien des machines et de la propreté des espaces communs , avec une attention particulière aux détails.";
    } else if (nomService == "jardin") {
            return "Service de nettoyage pour les jardins u , en veillant à l'entretien du jardin et de la propreté de l' espace, avec une attention particulière aux détails.";

     } else if (nomService == "fenetre") {
    return "Service de nettoyage pour les fenetres , qui garantit des vitres parfaitement transparentes et propres, avec une attention particulière aux détails.";
   } else {
        return "Service non défini. Veuillez contacter le support pour plus d'informations.";
    }
}


void MainWindow::exporterEnPDF() {
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");
       if (fileName.isEmpty()) return;

       // Récupérer les services actifs de la base de données
       QSqlQuery query("SELECT nom, duree, prix, disponibilite FROM services WHERE etat = 'actif'");

       // Préparer le contenu du document PDF
       QString contenu = "<h1>Description des Services Actifs</h1>";
       while (query.next()) {
           QString nomService = query.value("nom").toString();
           QString description = getDescriptionForService(nomService);  // Appel à la fonction pour récupérer la description du service

           contenu += "<p><b>Nom : </b>" + nomService + "<br>";
           contenu += "<b>Durée : </b>" + query.value("duree").toString() + "<br>";
           contenu += "<b>Prix : </b>" + QString::number(query.value("prix").toDouble()) + "<br>";
           contenu += "<b>Disponibilité : </b>" + query.value("disponibilite").toString() + "<br>";
           contenu += "<b>Description : </b>" + description + "</p>";  // Ajouter la description
           contenu += "<hr>";
       }

       // Créer et configurer le document PDF
       QTextDocument document;
       document.setHtml(contenu);
       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setOutputFileName(fileName);
       document.print(&printer);
}
QMap<QString, int> MainWindow::calculerDisponibilite() {
    QMap<QString, int> disponibilite;

    QSqlQuery query;
    query.prepare("SELECT disponibilite, COUNT(*) as count FROM services GROUP BY disponibilite");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return disponibilite;
    }

    while (query.next()) {
        QString dispo = query.value("disponibilite").toString().toLower();
        int count = query.value("count").toInt();

        if (dispo == "disponible") {
            disponibilite["disponible"] += count;
        } else if (dispo == "indisponible") {
            disponibilite["indisponible"] += count;
        }
    }

    qDebug() << "Disponibilité calculée:" << disponibilite; // Log des résultats
    return disponibilite;
}



void MainWindow::mettreAJourStatistiques()
{
    QMap<QString, int> stats = calculerDisponibilite();

        // Mettre à jour les variables membres
        servicesDisponibles = stats.value("disponible", 0);
        servicesIndisponibles = stats.value("indisponible", 0);
        ui->widget_3->setStatistiques(servicesDisponibles, servicesIndisponibles);


        // Forcer le rafraîchissement de la fenêtre pour redessiner
        update();  // Ajoute un événement de redessin
        qDebug() << "Statistiques mises à jour : Disponible =" << servicesDisponibles
                 << ", Indisponible =" << servicesIndisponibles;
}
void MainWindow::recevoirPrevisionsMeteo(const QString &condition, double temperature, bool pluiePrevue) {
     ajusterPlanification(condition, temperature, pluiePrevue);
 }

void MainWindow::ajusterPlanification(const QString &condition, double temperature, bool pluiePrevue) {
    if (pluiePrevue) {
        // Désactiver les services extérieurs
        mettreAJourDisponibilite(false, "fenetre");
        mettreAJourDisponibilite(false, "jardin");

        QMessageBox::information(this, "Planification Dynamique",
                                 "Pluie prévue : les services de 'nettoyage fenêtre' et 'nettoyage jardin' "
                                 "ont été désactivés.");
    } else {
        // Réactiver les services extérieurs si le temps est dégagé
        mettreAJourDisponibilite(true,"fenetre");
        mettreAJourDisponibilite(true, "jardin");

        QMessageBox::information(this, "Planification Dynamique",
                                 QString("Météo actuelle : %1, Température : %2°C.\nLes services extérieurs sont disponibles.")
                                     .arg(condition)
                                     .arg(temperature));
    }

    // Rafraîchir l'affichage du tableau des services
    rafraichirTableauServices();
}
void MainWindow::mettreAJourDisponibilite(bool disponible, const QString &motCle) {
    QSqlQuery query;
    query.prepare("UPDATE services SET disponibilite = :disponibilite WHERE nom LIKE :motCle");
    query.bindValue(":disponibilite", disponible ? "disponible" : "indisponible");
    query.bindValue(":motCle", "%" + motCle + "%");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour des disponibilités : " + query.lastError().text());
    } else {
        qDebug() << "Mise à jour des disponibilités effectuée pour : " << motCle;
    }
}
void MainWindow::rafraichirTableauServices() {
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("services");
    model->select();

    // Définir le modèle pour le tableau
    ui->tableViewServices->setModel(model);
    ui->tableViewServices->resizeColumnsToContents();
}

/*void MainWindow::envoyerServicesDisponiblesActifs()
{


    // Préparer et exécuter la requête SQL
    QSqlQuery query;
    query.prepare("SELECT nom FROM services WHERE etat = 'actif' AND disponibilite = 'disponible'");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête arduino :" << query.lastError().text();
        return;
    }

    // Récupérer les services disponibles et actifs
    QStringList services;
    while (query.next()) {
        services << query.value("nom").toString();
    }

    // Vérifier si des services ont été trouvés
    if (!services.isEmpty()) {
        qDebug() << "Services récupérés:" << services;

        // Envoyer les services à l'Arduino
        if (arduino) {
            arduino->envoyerServices(services);
            qDebug() << "Services envoyés à Arduino:" << services;
        } else {
            qDebug() << "Erreur: Objet Arduino non initialisé.";
        }
    } else {
        qDebug() << "Aucun service disponible ou actif trouvé.";
    }
}*/

