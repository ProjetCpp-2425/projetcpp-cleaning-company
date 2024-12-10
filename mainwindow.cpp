#include "mainwindow.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "ui_mainwindow.h"
#include "graphiquewidget.h"
=======
#include "qsqlerror.h"
#include "ui_mainwindow.h"
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
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
<<<<<<< HEAD
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
=======
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>

#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "statistique.h"
#include "sms.h"
#include <QTextCharFormat>

>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
<<<<<<< HEAD
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
=======
#include <QFileDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QtCharts>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
   ui->setupUi(this);
   this->setEnabled(true);
   ui-> nom ->setEnabled(true);
   ui-> id->setEnabled(true);
   ui->salaire ->setEnabled(true);
   ui-> prenom->setEnabled(true);
   ui-> date->setEnabled(true);
   ui->poste ->setEnabled(true);
   ui->comboBox->addItem("Prenom", "prenom");
   ui->comboBox->addItem("poste", "poste");
   ui->comboBox->addItem("Salaire", "salaire");
   reminderTimer = new QTimer(this);
   connect(reminderTimer, &QTimer::timeout, this, &MainWindow::checkReminders);
   reminderTimer->start(60000); // Vérifie les rappels toutes les 60 secondes

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::trierEmploye);

    connect(ui->exporterPDFButton, &QToolButton::clicked, this, &MainWindow::exporterEnPDF);
    connect(ui->button_stat, &QPushButton::clicked, this, &MainWindow::on_stat_employes_clicked);
    connect(ui->sendEmailButton, &QPushButton::clicked, this, &MainWindow::sendEmail);
    connect(ui->btnSendAttachment, &QPushButton::clicked, this, &MainWindow::sendEmailWithAttachment);
    connect(ui->addReminderButton, &QPushButton::clicked, this, &MainWindow::addReminder);
    connect(ui->showRemindersButton, &QPushButton::clicked, this, &MainWindow::showReminders);



    afficherEmploye();
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa




<<<<<<< HEAD
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
=======

}


MainWindow::~MainWindow() {
    delete ui;
}

// Fonction pour ajouter un employe
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
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
<<<<<<< HEAD
    checkQuery.prepare("SELECT COUNT(*) FROM Services WHERE id = :id");
=======
    checkQuery.prepare("SELECT COUNT(*) FROM Employes WHERE id = :id");
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
    checkQuery.bindValue(":id", id);
    checkQuery.exec();

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Erreur", "L'ID existe déjà. Veuillez entrer un ID unique.");
        return;
    }

<<<<<<< HEAD
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
=======
    // Si toutes les vérifications sont passées, ajout de l'employe
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    double salaire = ui->salaire->value();
    QString date_embauche = ui->date->text();
    QString poste = ui->poste->text();

    Employe Employe(id, nom, prenom,salaire, poste,date_embauche );
    bool test = Employe.ajouter();
    if (test) {
        QMessageBox::information(this, "Succès", "Employe ajouté avec succès.");
        afficherEmploye();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du Employe.");
    }
}

// Fonction pour modifier un employe
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
void MainWindow::on_modifier_clicked() {
    int id = ui->id->text().toInt();

    // Vérifiez si l'ID existe
    if (id == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide pour modifier.");
        return;
    }

<<<<<<< HEAD
    // Récupérer le service existant avec l'ID donné
      Services serviceExistant = Services::getById(id);
=======
    // Récupérer l'Employe existant avec l'ID donné
    Employe EmployeExistant = Employe::getById(id);
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa

    // Mise à jour uniquement des champs modifiés
    QString nom = ui->nom->text();
    if (!nom.isEmpty()) {
<<<<<<< HEAD
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
=======
        EmployeExistant.setNom(nom);
    }

    QString prenom = ui->prenom->text();
    if (!prenom.isEmpty()) {
        EmployeExistant.setPrenom(prenom);
    }

    double salaire = ui->salaire->value();
    if (salaire != EmployeExistant.getSalaire()) {
        EmployeExistant.setSalaire(salaire);
    }

    QString date_embauche = ui->date->text();
    if (!date_embauche.isEmpty()) {
        // Formater la date pour s'assurer qu'elle est correcte
        QDate date = QDate::fromString(date_embauche, "yyyy-MM-dd");
        if (date.isValid()) {
            // Convertir la QDate en QString dans un format qui convient pour Oracle
            QString formattedDate = date.toString("yyyy-MM-dd");
            EmployeExistant.setDate_embauche(formattedDate);
        } else {
            QMessageBox::warning(this, "Erreur", "Format de la date invalide.");
            return;
        }
    }

    QString poste = ui->poste->text();
    if (!poste.isEmpty()) {
        EmployeExistant.setPoste(poste);
    }

    // Appeler la méthode de mise à jour
    if (EmployeExistant.modifier(id)) {
        QMessageBox::information(this, "Succès", "Employé modifié avec succès.");
        afficherEmploye();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de l'employé.");
    }
}



// Fonction pour supprimer un Employe
void MainWindow::on_supprimer_clicked() {
    int id = ui->id->text().toInt();
    EmployeActuel.setId(id);

    if (EmployeActuel.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Employe supprimé avec succès.");
        afficherEmploye();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du Employe.");
    }
}

// Fonction pour afficher tous les Employe dans le QTableView
void MainWindow::afficherEmploye()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model = EmployeActuel.afficher();
    ui->tableViewEmploye->setModel(model);
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
}


void MainWindow::on_rechercher_clicked() {
    QString critere = ui->champRecherche->text();  // champRecherche est l'input utilisateur pour recherche

<<<<<<< HEAD
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
=======
    // Appeler la fonction de recherche de la classe Employe
    Employe Employe;
    QSqlQueryModel* model = Employe.rechercher(critere);

    // Mettre à jour la vue tableau avec les résultats
    ui->tableViewEmploye->setModel(model);
}
void MainWindow::trierEmploye() {
 Employe Employe;   QString critereTri = ui->comboBox->currentData().toString();
    QSqlQueryModel* model = Employe.trierParCritere(critereTri);
    ui->tableViewEmploye->setModel(model);
}

void MainWindow::exporterEnPDF() {
    QString cheminFichier = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", "", "PDF Files (*.pdf);;All Files (*)");

    if (cheminFichier.isEmpty()) {
        return; // Si l'utilisateur annule l'action
    }

    QPdfWriter writer(cheminFichier);
    writer.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&writer);

    int yPosition = 100; // Position de départ sur la page

    // Ajout du titre
    painter.drawText(100, yPosition, "Liste des Employe");
    yPosition += 50;

    // Parcourir le tableau des Employe et écrire chaque ligne dans le PDF
    for (int row = 0; row < ui->tableViewEmploye->model()->rowCount(); ++row) {
        QString ligneTexte;
        for (int col = 0; col < ui->tableViewEmploye->model()->columnCount(); ++col) {
            ligneTexte += ui->tableViewEmploye->model()->data(ui->tableViewEmploye->model()->index(row, col)).toString() + "  ";
        }
        painter.drawText(100, yPosition, ligneTexte);
        yPosition += 30;
    }

    painter.end();

    QMessageBox::information(this, "Exportation réussie", "Le tableau des Employe a été exporté en PDF avec succès.");
}
void MainWindow::on_stat_employes_clicked()
{
    // Récupérer la valeur saisie par l'utilisateur pour filtrer les postes
    QString userInput = ui->input->text().trimmed();

    // Construire la requête SQL avec ou sans filtre
    QString queryStr;
    if (userInput.isEmpty()) {
        // Pas de filtre, récupérer tous les postes
        queryStr = "SELECT POSTE FROM EMPLOYES";
    } else {
        // Appliquer un filtre pour récupérer uniquement les postes correspondants
        queryStr = "SELECT POSTE FROM EMPLOYES WHERE POSTE LIKE '%" + userInput + "%'";
    }

    QSqlQuery query;

    // Exécuter la requête et gérer les erreurs
    if (!query.exec(queryStr)) {
        qDebug() << "Erreur SQL : " << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les postes des employés : " + query.lastError().text());
        return;
    }

    // QMap pour stocker la fréquence des postes
    QMap<QString, int> posteFrequency;

    // Remplir le QMap avec les résultats de la requête
    while (query.next()) {
        QString poste = query.value(0).toString();
        if (!poste.isEmpty()) {
            posteFrequency[poste] += 1;
        }
    }

    // Si aucune donnée n'est trouvée, afficher un message
    if (posteFrequency.isEmpty()) {
        QMessageBox::information(this, "Aucune donnée", "Aucun poste correspondant trouvé dans la base de données.");
        return;
    }

    // Trier les postes par fréquence décroissante
    QList<QString> sortedPoste = posteFrequency.keys();
    std::sort(sortedPoste.begin(), sortedPoste.end(), [&posteFrequency](const QString &a, const QString &b) {
        return posteFrequency[a] > posteFrequency[b];
    });

    // Créer un QBarSet pour représenter les fréquences
    QBarSet *set = new QBarSet("Postes");

    // Ajouter les fréquences au QBarSet
    foreach (const QString &poste, sortedPoste) {
        int freq = posteFrequency[poste];
        *set << freq;
    }

    // Créer une série de barres et y ajouter le QBarSet
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Créer un graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Postes des Employés");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Créer un axe X pour les catégories (postes)
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QStringList categories;
    foreach (const QString &poste, sortedPoste) {
        categories << poste;
    }
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Créer un axe Y pour les fréquences
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Fréquence");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Créer un affichage pour le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Afficher le graphique dans une nouvelle fenêtre
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    QWidget *chartWindow = new QWidget();
    chartWindow->setLayout(layout);
    chartWindow->setWindowTitle("Statistiques des Postes des Employés");
    chartWindow->resize(800, 600);
    chartWindow->show();
}
void MainWindow::sendEmail() {

    // Récupérer les informations saisies par l'utilisateur

    QString recipient = ui->mail_3->text(); // Email du destinataire



    if (recipient.isEmpty()) {

        QMessageBox::warning(this, "Erreur", "Veuillez saisir l'adresse email du destinataire.");

        return;

    }



    // Validation de l'adresse email avec QRegularExpression

    QRegularExpression emailRegex("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");

    QRegularExpressionMatch match = emailRegex.match(recipient);

    if (!match.hasMatch()) {

        QMessageBox::warning(this, "Erreur", "L'adresse email saisie est invalide.");

        return;

    }



    // Initialiser le manager réseau

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);



    // Préparer la requête HTTP vers l'API Postmark

    QNetworkRequest request(QUrl("https://api.postmarkapp.com/email"));


    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader("X-Postmark-Server-Token", "3cc747ff-11b1-4a4a-95cb-e7b9f2a36b7e"); // Votre token API



    // Construire le contenu de l'email

    QJsonObject emailObject ;

    emailObject["From"] = "mohammedamine.jaibi@esprit.tn" ;

    emailObject["To"] = recipient; // Adresse email du destinataire

    emailObject["Subject"] = "Email de test depuis Qt et Postmark"; // Sujet de l'email

    emailObject["TextBody"] = "Bonjour,\nCeci est un test envoyé avec Qt et Postmark."; // Contenu texte de l'email



    QJsonDocument emailDoc(emailObject);



    // Envoyer la requête POST

    QNetworkReply *reply = manager->post(request, emailDoc.toJson());



    // Gérer la réponse de l'API

    connect(reply, &QNetworkReply::finished, this, [reply]() {

        if (reply->error() == QNetworkReply::NoError) {

            QMessageBox::information(nullptr, "Succès", "Email envoyé avec succès !");

        } else {

            QMessageBox::critical(nullptr, "Erreur", "Échec de l'envoi de l'email : " + reply->errorString());

        }

        reply->deleteLater();

    });

};
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QBuffer>
#include <QJsonArray>

// Nouvelle méthode pour envoyer un email avec pièce jointe
void MainWindow::sendEmailWithAttachment() {

    // Récupérer les informations saisies par l'utilisateur
    QString recipient = ui->mail_3->text(); // Email du destinataire
    if (recipient.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir l'adresse email du destinataire.");
        return;
    }

    // Validation de l'adresse email
    QRegularExpression emailRegex("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    if (!emailRegex.match(recipient).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "L'adresse email saisie est invalide.");
        return;
    }

    // Sélectionner une pièce jointe
    QString filePath = QFileDialog::getOpenFileName(this, "Sélectionner une pièce jointe", "", "Tous les fichiers (*.*)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun fichier sélectionné.");
        return;
    }

    // Lire le fichier en tant que base64
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible de lire le fichier sélectionné.");
        return;
    }
    QByteArray fileData = file.readAll();
    QString encodedFile = fileData.toBase64();
    file.close();

    // Extraire le nom du fichier
    QString fileName = QFileInfo(filePath).fileName();

    // Initialiser le manager réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Préparer la requête HTTP vers l'API Postmark
    QNetworkRequest request(QUrl("https://api.postmarkapp.com/email"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-Postmark-Server-Token", "3cc747ff-11b1-4a4a-95cb-e7b9f2a36b7e"); // Remplace avec ton token API

    // Construire l'email avec pièce jointe
    QJsonObject emailObject;
    emailObject["From"] = "mohammedamine.jaibi@esprit.tn"; // Adresse email expéditeur
    emailObject["To"] = recipient;
    emailObject["Subject"] = "Email avec pièce jointe depuis Qt";
    emailObject["TextBody"] = "Bonjour,\nCeci est un email envoyé avec une pièce jointe.";

    // Ajouter la pièce jointe
    QJsonArray attachments;
    QJsonObject attachment;
    attachment["Name"] = fileName;
    attachment["Content"] = QString(encodedFile);
    attachment["ContentType"] = "application/octet-stream"; // Type MIME par défaut
    attachments.append(attachment);

    emailObject["Attachments"] = attachments;

    QJsonDocument emailDoc(emailObject);

    // Envoyer la requête POST
    QNetworkReply *reply = manager->post(request, emailDoc.toJson());

    // Gérer la réponse de l'API
    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(nullptr, "Succès", "Email avec pièce jointe envoyé avec succès !");
        } else {
            QMessageBox::critical(nullptr, "Erreur", "Échec de l'envoi de l'email : " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::addReminder() {
    int employeeId = ui->employeeIdReminder->text().toInt(); // ID de l'employé
    QString reminderText = ui->reminderText->text();         // Texte du rappel

    if (employeeId == 0 || reminderText.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID valide et un texte de rappel.");
        return;
    }

    employeeReminders.insert(employeeId, reminderText);
    QMessageBox::information(this, "Succès", "Rappel ajouté avec succès !");
}
void MainWindow::showReminders() {
    QString reminders;

    for (auto it = employeeReminders.begin(); it != employeeReminders.end(); ++it) {
        reminders += QString("Employé ID: %1\nRappel: %2\n\n").arg(it.key()).arg(it.value());
    }

    if (reminders.isEmpty()) {
        reminders = "Aucun rappel enregistré.";
    }

    QMessageBox::information(this, "Rappels", reminders);
}
void MainWindow::checkReminders() {
    if (!employeeReminders.isEmpty()) {
        QMessageBox::information(this, "Rappels", "Il y a des rappels en attente. Consultez-les !");
    }
}


>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa

=======
    ui->tab_transaction->setModel(transaction.afficherTransactions());

    ui->date_transaction->setDate(QDate::currentDate());
    ui->code->setVisible(false);
    // Surligner les dates de transaction futures
    highlightFutureTransactionDates();
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(onSearchCriterionChanged(int)));
    populateClientComboBox();
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxSelectionChanged(int)));
    int verif_arduino = A.connect_arduino();
            switch(verif_arduino){
            case(0):qDebug()<<"arduino is available and connected to :" << A.getArduinoPortName();
                break;
            case(1):qDebug()<<"arduino is available but not connected to :" << A.getArduinoPortName();
                break;
            case(-1):qDebug()<<"arduino is not available" ;
                break;
            }
        QObject::connect(A.getSerial(),SIGNAL(readyRead()),this,SLOT(update_label()));

}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_label()
{
    // Append incoming data to a buffer
    data += A.readFromArduino();
    qDebug() << "Données reçues d'Arduino :" << data;
    int newlineIndex = data.indexOf('\n');
    if (newlineIndex != -1) {

        QString message = data.left(newlineIndex);
        bool conversionOk = false;
        int receivedCode = message.toInt(&conversionOk);

        if (conversionOk) {
            if(handleTransaction(receivedCode)){
                A.write_arduino("ok\n");
                data ="";
                QMessageBox::information(this, "Succès", "La transaction a été ajoutée avec succès!");
            }
            else{
                A.write_arduino("no\n");
                data ="";
                QMessageBox::warning(this, "Erreur", "Le code client est incorrect.");
            }
        } else {
            ui->label->setText("Code invalide reçu d'Arduino");
        }
    }
}

void MainWindow::populateClientComboBox() {
    // Clear the combo box first
    ui->clienbox->clear();

    // Query the database to fetch client IDs
    QSqlQuery query;
    query.prepare("SELECT ID FROM clients");

    if (query.exec()) {
        // Loop through the result and add each ID to the combo box
        while (query.next()) {
            QString id_client = query.value(0).toString();
            ui->clienbox->addItem(id_client);
        }
        qDebug() << "Client IDs successfully added to the combo box.";
    } else {
        // Handle query errors
        qDebug() << "Failed to fetch client IDs: " << query.lastError().text();
    }
}

void MainWindow::onSearchCriterionChanged(int index)
{

    QString selectedCriterion = ui->comboBox_2->itemText(index);


    if (selectedCriterion == "Id") {
        ui->recherche->setPlaceholderText("Entrez un ID");
        ui->recherche->setValidator(new QIntValidator(1, INT_MAX, this));
    } else if (selectedCriterion == "Montant") {
        ui->recherche->setPlaceholderText("Entrez un montant");
        ui->recherche->setValidator(new QIntValidator(0, INT_MAX, this));
    } else if (selectedCriterion == "Date") {
        ui->recherche->setPlaceholderText("Entrez une date (yyyy-MM-dd)");
        ui->recherche->setValidator(nullptr);
    } else {
        ui->recherche->setPlaceholderText("");
        ui->recherche->setValidator(nullptr);
    }
    ui->recherche->clear();
}

void MainWindow::on_rechercher_clicked()
{
    // Get the selected search criterion and search input
    QString selectedCriterion = ui->comboBox_2->currentText();
    QString searchValue = ui->recherche->text();

    // Check if the input is empty
    if (searchValue.isEmpty()) {
        ui->tab_transaction->setModel(transaction.afficherTransactions());
        return;
    }

    QSqlQueryModel *model = nullptr;

    // Perform the search based on the selected criterion
    if (selectedCriterion == "Id") {
        int id = searchValue.toInt(); // Input is already validated as a positive integer
        model = transaction.rechercheById(id);
    }
    else if (selectedCriterion == "Montant") {
        int montant = searchValue.toInt(); // Input is already validated as an integer
        model = transaction.rechercheByMontant(montant);
    }
    else if (selectedCriterion == "Date") {
        QString date = searchValue;


        model = transaction.rechercheByDate(date);
    }
    else {
        QMessageBox::warning(this, "Critère de recherche invalide", "Critère de recherche inconnu sélectionné.");
        return;
    }

    // Handle results
    if (!model) {
        QMessageBox::critical(this, "Erreur de recherche", "Une erreur s'est produite lors de la recherche.");
        return;
    }

    if (model->rowCount() > 0) {
        ui->tab_transaction->setModel(model); // Display the results
    } else {
        QMessageBox::information(this, "Aucun résultat", QString("Aucune transaction trouvée pour %1 : %2")
                                  .arg(selectedCriterion)
                                  .arg(searchValue));
        // Display the full table if no results are found
        ui->tab_transaction->setModel(transaction.afficherTransactions());
    }
}

void MainWindow::highlightFutureTransactionDates()
{
    // Create a default format to reset previous highlights
    QTextCharFormat defaultFormat;

    // Récupérez toutes les dates visibles dans le calendrier
    QDate currentDate = QDate::currentDate();
    QDate minDate = ui->calendarWidget->minimumDate();
    QDate maxDate = ui->calendarWidget->maximumDate();

    // Reset formatting for all dates in the visible range (or use min/max of the widget)
    for (QDate date = minDate; date <= maxDate; date = date.addDays(1)) {
        ui->calendarWidget->setDateTextFormat(date, defaultFormat);
    }

    // Récupérez les futures dates de transaction
    QList<QDate> futureDates = transaction.getFutureTransactionDates();

    // Définir un format spécifique pour les dates futures (exemple : jaune avec texte bleu gras)
    QTextCharFormat format;
    format.setBackground(Qt::yellow);
    format.setForeground(Qt::blue);
    format.setFontWeight(QFont::Bold);

    // Appliquez le format à chaque date dans les futures dates
    for (const QDate &date : futureDates) {
        if (date > currentDate) { // Ensure it's in the future
            ui->calendarWidget->setDateTextFormat(date, format);
        }
    }

    qDebug() << "Futures dates de transaction surlignées dans le calendrier.";
}

void MainWindow::onComboBoxSelectionChanged(int index)
{
    QString sortColumn;

    // Restreindre le tri aux colonnes ID et Montant uniquement
    switch (index) {
        case 0:  // Première option (par exemple, ID)
            sortColumn = "id_transaction";
            break;
        case 1:  // Deuxième option (par exemple, Montant)
            sortColumn = "montant";
            break;
        case 2:
            sortColumn = "date_transaction";
            break;
        default: // Toute autre option (non valide)
            QMessageBox::warning(this, "Tri non valide", "Cette option de tri n'est pas supportée.");
            return;
    }

    qDebug() << "Tri activé sur la colonne : " << sortColumn;

    // Appliquer le tri uniquement si une colonne valide est sélectionnée
    ui->tab_transaction->setModel(transaction.afficherTransactions(sortColumn));
}

void MainWindow::clearInputFields()
{
    ui->id_transaction->clear();
    ui->montant->clear();
    ui->date_transaction->setDate(QDate::currentDate());
    ui->type_transaction->clear();
    ui->statut_transaction->clear();
}

void MainWindow::on_exportStatistique_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter les Statistiques en PDF", "", "Fichiers PDF (*.pdf)");
    Statistique stats;
    stats.exportToPdf(fileName);
}

void MainWindow::on_exportButton_clicked()
{
    // Create a file dialog to choose the location and name of the PDF
    QString fileName = QFileDialog::getSaveFileName(this, "Export to PDF", "", "PDF Files (*.pdf)");

    if (fileName.isEmpty()) {
        return;
    }

    // Create a QTextDocument for constructing the PDF content
    QTextDocument doc;

    // Start building the content
    QString htmlContent;

    // Title of the document
    htmlContent += "<h1 style='text-align: center;'>Transactions List</h1>";
    htmlContent += "<hr/>";  // Line separator

    // Create a simple HTML table structure
    htmlContent += "<table border='1' cellpadding='5' cellspacing='0' width='100%'>";

    // Add the table headers based on Transaction data structure
    htmlContent += "<tr>"
                   "<th>ID</th>"
                   "<th>Amount</th>"
                   "<th>Date</th>"
                   "<th>Type</th>"
                   "<th>Status</th>"
                   "</tr>";

    // Get the model from the table view (ensure it is connected to Transaction data)
    QAbstractItemModel *model = ui->tab_transaction->model();

    // Loop through each row and column to get the data
    for (int row = 0; row < model->rowCount(); ++row) {
        htmlContent += "<tr>";

        QString id_transaction = model->data(model->index(row, 0)).toString();
        QString montant = model->data(model->index(row, 1)).toString();
        QString date_transaction = model->data(model->index(row, 2)).toString();
        QString type_transaction = model->data(model->index(row, 3)).toString();
        QString statut_transaction = model->data(model->index(row, 4)).toString();
    }
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    if (ui->pushButton_ajouter->text() == "Ajouter") {
        ui->code->setVisible(true);
        ui->pushButton_ajouter->setText("Vérifier");
    } else {
        QString enteredCode = ui->code->text();

        bool conversionOk = false;
        int receivedCode = enteredCode.toInt(&conversionOk);

        if (conversionOk) {
            handleTransaction(receivedCode);
            QMessageBox::information(this, "Succès", "La transaction a été ajoutée avec succès!");
        } else {
            QMessageBox::warning(this, "Erreur", "Le code client est incorrect.");
        }
    }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    // Validate the transaction ID input
    int id = ui->id_transaction->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
    }

    // Validate the other inputs
    double montant = ui->montant->text().toDouble();
    if (montant <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un montant valide.");
    }

    QDate date = ui->date_transaction->date();
    if (!date.isValid()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une date valide.");
    }

    QString type = ui->type_transaction->text();
    if (type.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un type de transaction.");
    }

    QString status = ui->statut_transaction->text();
    if (status.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un statut de transaction.");
    }

    // Attempt to modify the transaction in the database
    bool success = transaction.modifierTransaction(id, montant, date, type, status);

    if (success) {
        QMessageBox::information(this, "Succès", "La transaction a été modifiée avec succès !");
        ui->tab_transaction->setModel(transaction.afficherTransactions()); // Refresh the table view
        clearInputFields(); // Clear the input fields
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification de la transaction.");
    }
}


void MainWindow::on_pushButton_supprimer_clicked()
{
    // Retrieve the ID of the transaction to delete
    int id = ui->id_transaction->text().toInt();

    // Validate the ID
    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    // Confirm the deletion with the user
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmation",
        QString("Êtes-vous sûr de vouloir supprimer la transaction avec l'ID %1 ?").arg(id),
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        // Attempt to delete the transaction
        bool success = transaction.supprimerTransaction(id);

        if (success) {
            QMessageBox::information(this, "Succès", "La transaction a été supprimée avec succès !");
            ui->tab_transaction->setModel(transaction.afficherTransactions()); // Refresh the table view
            clearInputFields(); // Clear the input fields
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la suppression de la transaction.");
        }
    }
}


bool MainWindow::handleTransaction(int receivedCode)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENTS WHERE CODE = :code");
    query.bindValue(":code", QString::number(receivedCode));

    if (query.exec() && query.next()) {
        int id = ui->id_transaction->text().toInt();
        double montant = ui->montant->text().toDouble();
        QDate date = ui->date_transaction->date();
        QString type = ui->type_transaction->text();
        QString status = ui->statut_transaction->text();

        transaction.setIdTransaction(id);
        transaction.setMontant(montant);
        transaction.setDateTransaction(date);
        transaction.setTypeTransaction(type);
        transaction.setStatutTransaction(status);

        bool success = transaction.ajouterTransaction();

        if (success) {
            qDebug() << "Transaction ajoutée avec succès!";

            ui->id_transaction->clear();
            ui->montant->clear();
            ui->type_transaction->clear();
            ui->statut_transaction->clear();
            ui->code->clear();
            ui->date_transaction->clear();
            ui->code->setVisible(false);
            ui->tab_transaction->setModel(transaction.afficherTransactions());
            return true;
        } else {
            qDebug() << "Échec de l'ajout de la transaction.";

            QMessageBox::warning(this, "Erreur", "Échec de l'ajout de la transaction.");
            return false;
        }

        ui->code->setVisible(false);
    } else {

        return false;
    }
}
>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
