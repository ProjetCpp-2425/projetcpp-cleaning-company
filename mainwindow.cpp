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
MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent),ui(new Ui::MainWindow),meteoService(new MeteoService(this))//, networkManager(new QNetworkAccessManager(this))
{
   ui->setupUi(this);
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

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::trierServices);
    connect(ui->exporterPDFButton, &QToolButton::clicked, this, &MainWindow::exporterEnPDF);
 //connect(ui->boutonstatistique, &QPushButton::clicked, this, &MainWindow::mettreAJourStatistiques);


    connect(meteoService, &MeteoService::meteoRecue, this, [this](double temperature, QString description) {
        qDebug() << "Météo reçue ! Température :" << temperature << "°C, Description :" << description;
        bool pluiePrevue = description.contains("rain", Qt::CaseInsensitive);
        ajusterPlanification(description, temperature, pluiePrevue); });
         meteoService->getMeteoActuelle("paris");
         /*recommandationsModel = new QStandardItemModel(this);
         recommandationsModel->setHorizontalHeaderLabels({"Service", "Recommandation"});

         ui->tableViewRecommandations->setModel(recommandationsModel);
         ui->tableViewRecommandations->resizeColumnsToContents();

          connect(ui->btnAnalyserTendances, &QPushButton::clicked, this, &MainWindow::analyserTendances);*/


        // Mettre à jour les statistiques
        mettreAJourStatistiques();
update();




afficherServices();


}

MainWindow::~MainWindow() {
    delete ui;
   // delete networkManager;
}

// Fonction pour ajouter un service
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
}

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
/*void MainWindow::analyserTendances() {
    // URL de l'API
    QString apiUrl = "https://serpapi.com/search?engine=google_trends&q=cleaning&apikey=3bd9d0941485d77b78eeb619d30acd0f461fa71eb900a2a62a0d9abb83458174";
    QUrl url = QUrl::fromUserInput(apiUrl);

    if (!url.isValid()) {
        QMessageBox::warning(this, "Erreur URL", "L'URL fournie est invalide.");
        return;
    }

    QNetworkRequest request(url);

    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onTrendsDataReceived);

    networkManager->get(request); // Envoi de la requête GET
}

void MainWindow::onTrendsDataReceived(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(this, "Erreur API", "Impossible de récupérer les tendances : " + reply->errorString());
        reply->deleteLater();
        return;
    }

    // Traitement des données JSON reçues
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject rootObject = doc.object();
    QJsonArray trends = rootObject["trending_searches"].toArray(); // Adapter selon la structure JSON

    afficherRecommandations(trends);  // Affichage des tendances dans le tableau

    reply->deleteLater();  // Nettoyer la réponse
}

void MainWindow::afficherRecommandations(const QJsonArray &tendances) {
    // Vider les recommandations existantes
    recommandationsModel->clear();
    recommandationsModel->setHorizontalHeaderLabels({"Service", "Recommandation"});

    foreach (const QJsonValue &trend, tendances) {
        QString motCle = trend.toObject()["API"].toString(); // Adapter selon la structure JSON
        QString recommandation;

        // Mapping des mots-clés de tendance vers des services de nettoyage
        if (motCle.contains("House", Qt::CaseInsensitive)) {
            recommandation = "Nettoyage intérieur";
        } else if (motCle.contains("Garden", Qt::CaseInsensitive)) {
            recommandation = "Nettoyage jardin";
        } else {
            recommandation = "Service non identifié";
        }

        QList<QStandardItem *> items;
        items.append(new QStandardItem(recommandation));
        items.append(new QStandardItem(motCle));

        recommandationsModel->appendRow(items);
    }

    ui->tableViewRecommandations->resizeColumnsToContents();
    QMessageBox::information(this, "Tendances actuelles", "Les recommandations basées sur les tendances ont été mises à jour.");
}*/
