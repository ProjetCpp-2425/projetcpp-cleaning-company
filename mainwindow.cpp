#include "mainwindow.h"
#include "qsqlerror.h"
#include "ui_mainwindow.h"
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





}


MainWindow::~MainWindow() {
    delete ui;
}

// Fonction pour ajouter un employe
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
    checkQuery.prepare("SELECT COUNT(*) FROM Employes WHERE id = :id");
    checkQuery.bindValue(":id", id);
    checkQuery.exec();

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Erreur", "L'ID existe déjà. Veuillez entrer un ID unique.");
        return;
    }

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
void MainWindow::on_modifier_clicked() {
    int id = ui->id->text().toInt();

    // Vérifiez si l'ID existe
    if (id == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide pour modifier.");
        return;
    }

    // Récupérer l'Employe existant avec l'ID donné
    Employe EmployeExistant = Employe::getById(id);

    // Mise à jour uniquement des champs modifiés
    QString nom = ui->nom->text();
    if (!nom.isEmpty()) {
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
}


void MainWindow::on_rechercher_clicked() {
    QString critere = ui->champRecherche->text();  // champRecherche est l'input utilisateur pour recherche

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



