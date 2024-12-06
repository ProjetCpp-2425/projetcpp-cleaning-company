#include"mainwindow.h"
#include"ui_mainwindow.h"
#include<QMainWindow>
#include<QMessageBox>
#include "Client.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

#include<QSqlTableModel>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtQuick>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{Client client;
    ui->setupUi(this);
    ui->tableView_2->setModel(client.afficher());
    /*ui->comboBoxTri->addItem("NOM_Client");
    connect(ui->comboBoxTri, SIGNAL(currentIndexChanged(int)), this, SLOT(trierClients()));*/
    ui->comboBoxTri->addItem("Nom");
       ui->comboBoxTri->addItem("Prénom");
       ui->comboBoxTri->addItem("Méthode de paiement");

       connect(ui->lineEditRecherche, &QLineEdit::textChanged, this, [this]() {
           QString texte = ui->lineEditRecherche->text();
           QString critere = ui->comboBoxRecherche->currentData().toString();

           Client client;
           QSqlQueryModel* model = client.rechercherParCritereEtTexte( critere, texte);

           ui->tableView_2->setModel(model); });


           // Ajouter les options de recherche dans le QComboBox
           ui->comboBoxRecherche->addItem("NOM_Client", "NOM_Client");
           ui->comboBoxRecherche->addItem("PRENOM_Client", "PRENOM_Client");
           ui->comboBoxRecherche->addItem("TYPE", "TYPE");

           int ret = A.connect_arduino();
           switch (ret) {
           case 0:
               qDebug() << "Arduino est disponible et connecté au port :" << A.getarduino_port_name();
               break;
           case 1:
               qDebug() << "Arduino est disponible mais pas connecté au port :" << A.getarduino_port_name();
               break;
           case -1:
               qDebug() << "Arduino n'est pas disponible";
               break;
           }

           // Connecter le signal de réception de données Arduino au slot update_label
           QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));
       }



       void MainWindow::update_label() {
           // Ajouter les données reçues au tampon
           dataBuffer += A.read_from_arduino();
           qDebug() << "Données reçues d'Arduino :" << dataBuffer;

           // Vérifier si le tampon contient une ligne complète se terminant par '\n'
           int newlineIndex = dataBuffer.indexOf('\n');
           if (newlineIndex != -1) {
               // Extraire le message complet
               QString completeMessage = dataBuffer.left(newlineIndex).trimmed();
               dataBuffer.remove(0, newlineIndex + 1);

               // Décider d'envoyer automatiquement '1' ou '0' selon le message reçu
               if (completeMessage == "AUTHORIZED") {
                   A.write_to_arduino("1"); // Envoyer "1" pour allumer la LED verte
                   qDebug() << "Commande '1' envoyée à Arduino automatiquement.";
                   ui->statusLabel->setText("Carte autorisée !");
               } else if (completeMessage == "DENIED") {
                   A.write_to_arduino("0"); // Envoyer "0" pour allumer la LED rouge
                   qDebug() << "Commande '0' envoyée à Arduino automatiquement.";
                   ui->statusLabel->setText("Carte refusée !");
               }

       }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_modifier_2_clicked()
{
    QItemSelectionModel *select = ui->tableView_2->selectionModel();
       if (!select->hasSelection()) {
           QMessageBox::critical(this, "Error", "Please select a row to modify.");
           return;
       }

       // Get the selected row index and extract the ID from the model
       int row = select->currentIndex().row();
       int id = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 0)).toInt();
       if (!Etmp.checkIfidExists(id)) {
               QMessageBox::warning(this, "ID Not Found", "The ID does not exist. Please enter a valid ID.");
               return;
           }

           Client c = Etmp.getclientByid(id);
           ui->CIN_Clientm->setText(QString::number(c.getCIN_client()));
           ui->Nom_Clientm->setText(c.getNOM_client());
           ui->PRENOM_Clientm->setText(c.getPRENOM_client());
           ui->DATES_Clientm->setDate(c.getDATES_Client());
           ui->METHODEP_Clientm->setCurrentText(c.getMETHODEP_Client());
           ui->TYPEm->setCurrentText(c.getTYPE());
           ui->ADRESSE_Clientm->setText(c.getADRESSE_Client());
           ui->NUMC_Clientm->setText(c.getNUMC_Client());



}


void MainWindow::on_modifier_4_clicked()
{

           int id=ui->CIN_Clientm->text().toInt();
           QString nom=ui->Nom_Clientm->text();
           QString prenom=ui->PRENOM_Clientm->text();
           QDate date=ui->DATES_Clientm->date();
           QString methode=ui->METHODEP_Clientm->currentText();
           QString type=ui->TYPEm->currentText();
           QString adresse=ui->ADRESSE_Clientm->text();
           QString numc=ui->NUMC_Clientm->text();




           Client client = Etmp.getclientByid(id);
           bool test=Etmp.modifier(id,nom,prenom,date,methode,type,adresse,numc);
                       if (test)
                       {
                           ui->tableView_2->setModel(Etmp.afficher());
                           QMessageBox::information(nullptr, QObject::tr("ok"),
                                       QObject::tr("modification effectue.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
                       }
                       else
                           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                       QObject::tr("modification non effectue.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_ajouter_2_clicked()
{
    int CIN_Client = ui->CIN_Client_2->text().toInt();
    QString NOM_Client = ui->Nom_Client_2->text();
    QString PRENOM_Client = ui->PRENOM_Client_2->text();
    QDate DATES_Client = ui->DATES_Client_2->date();
    QString METHODEP_Client = ui->METHODEP_Client_2->currentText();
    QString type = ui->TYPE_2->currentText();
    QString adresse = ui->ADRESSE_Client_2->text();
    QString numc = ui->NUMC_Client_2->text();

    if (currentClient.getIMAGE_Client().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Aucune photo n'est associée au client. Veuillez charger une photo.");
            return;
        }

    // Créer un objet Client avec tous les paramètres
    Client C(CIN_Client, NOM_Client, PRENOM_Client, DATES_Client, METHODEP_Client, type, adresse, numc, currentClient.getPhotoPath());

    if (C.ajouter()) {
        ui->tableView_2->setModel(C.afficher());
        QMessageBox::information(this, "Succès", "Le client a été ajouté avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le client.");
    }
}




void MainWindow::on_supprimer_2_clicked()
{
    QItemSelectionModel *select = ui->tableView_2->selectionModel();
    if (!select->hasSelection()) {
        QMessageBox::critical(this, "Error", "Please select a row to delete.");
        return;
    }

    // Get the selected row index and extract the ID from the model
    int row = select->currentIndex().row();
    int id = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 0)).toInt();
    Client e=Etmp.getclientByid(id);
    if (e.getCIN_client()!=id){
       QMessageBox::critical(this, "Error", "This ID doesn't exist!");
    }else
    {
        bool test=Etmp.supprimer(id);
        if (test)
        {
            ui->tableView_2->setModel(Etmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("suppression effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("suppression non effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_2->setModel(Etmp.afficher());


    }
}


void MainWindow::on_comboBoxTri_currentIndexChanged(int index )
{

    Client client;

        // Définir le critère en fonction du choix de l'utilisateur
        QString critere;
        switch (index) {
            case 0:
                critere = "NOM_Client";  // Tri par Nom
                break;
            case 1:
                critere = "PRENOM_Client";  // Tri par Prénom
                break;
            case 2:
                critere = "METHODEP_Client";  // Tri par Méthode de paiement
                break;
            default:
                critere = "NOM_Client";  // Par défaut, trier par Nom
                break;
        }

        // Appeler la méthode de tri et obtenir le modèle de données
        QSqlQueryModel* model = client.trier(critere);

        // Mettre à jour le QTableView avec le modèle trié
        ui->tableView_2->setModel(model);
    }



















 void MainWindow::on_exportToPDF_clicked()   {
        QString filenameCriterion = "clients";  // Nom de base du fichier

        // Construire le nom du fichier avec la date
        QString filename = filenameCriterion + "_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf";
        QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", filename, "*.pdf");

        if (filePath.isEmpty()) {
            return;  // Si l'utilisateur annule, sortir de la fonction
        }

        // Récupérer le modèle associé à la vue
        QAbstractItemModel* model = ui->tableView_2->model();
        if (!model) {
            QMessageBox::critical(this, "Error", "No data available in the table to export.");
            return;
        }

        // Appeler la méthode exportToPDF via l'objet Client
        Client client;
        client.exportToPDF(filePath, model);
    }



































/*void MainWindow::on_stat_methods_clicked()
{


        // Obtenez les statistiques des méthodes
        Client client;
        QSqlQueryModel* model = client.getMethodStatistics();

        if (!model) {
            QMessageBox::critical(this, "Erreur", "Impossible de récupérer les statistiques.");
            return;
        }

        // Préparez les données pour le graphique
        QPieSeries* series = new QPieSeries();
        qreal total = 0;
        QMap<QString, qreal> methodCounts;

        for (int i = 0; i < model->rowCount(); ++i) {
            QString method = model->data(model->index(i, 0)).toString();
            qreal count = model->data(model->index(i, 1)).toDouble();
            methodCounts.insert(method, count);
            total += count;
        }

        // Ajoutez les données dans la série
        for (auto it = methodCounts.begin(); it != methodCounts.end(); ++it) {
            qreal percentage = (it.value() / total) * 100;
            QString label = it.key() + " (" + QString::number(percentage, 'f', 2) + "%)";
            series->append(label, it.value());
        }

        // Créez le graphique
        QChart* chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des Méthodes de Paiement");
        chart->setTheme(QChart::ChartThemeLight);
        chart->legend()->setAlignment(Qt::AlignRight);

        // Affichez le graphique dans un QChartView
        QChartView* chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Remplacez le contenu existant dans le widget par le graphique
        if (ui->widget_methods->layout()) {
            QLayoutItem* item;
            while ((item = ui->widget_methods->layout()->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete ui->widget_methods->layout();
        }

        QVBoxLayout* layout = new QVBoxLayout(ui->widget_methods);
        layout->addWidget(chartView);
        ui->widget_methods->setLayout(layout);

        delete model; // Libérez la mémoire du modèle
    }

*/











void MainWindow::on_btnUploadPhoto_clicked()
{

        // Ouvrir un dialogue de fichier pour sélectionner une image
        QString filePath = QFileDialog::getOpenFileName(this, "Sélectionner une photo", "", "Images (*.png *.jpg *.jpeg)");

        if (!filePath.isEmpty()) {
            // Stocker temporairement le chemin de la photo
            currentClient.setPhotoPath(filePath);

            // Charger l'image dans le QLabel pour un aperçu
            QPixmap pixmap(filePath);
            ui->IMAGE_Client_2->setPixmap(pixmap.scaled(ui->IMAGE_Client_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            QByteArray imageBytes = currentClient.convertPhotoToByteArray(filePath);

                    if (!imageBytes.isEmpty()) {
                        currentClient.setIMAGE_Client(imageBytes);  // Stocker les données binaires dans l'objet Client
                        currentClient.setPhotoPath(filePath);    }



            QMessageBox::information(this, "Photo Chargée", "La photo a été sélectionnée avec succès.");
        } else {
            QMessageBox::warning(this, "Erreur", "Aucune photo sélectionnée.");
        }

    }


void MainWindow::afficherPhoto(const QByteArray& imageBytes) {
    QPixmap pixmap;
    pixmap.loadFromData(imageBytes);

    if (!pixmap.isNull()) {
        ui->IMAGE_Client_2->setPixmap(pixmap.scaled(ui->IMAGE_Client_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger la photo.");
    }
}



















void MainWindow::on_pushButtonRecherche_clicked()
{
        QString texte = ui->lineEditRecherche->text();  // Récupérer le texte saisi
        QString critere = ui->comboBoxRecherche->currentData().toString();  // Récupérer la colonne sélectionnée

        Client client;
        QSqlQueryModel* model = client.rechercherParCritereEtTexte(critere, texte);  // Recherche filtrée

        ui->tableView_2->setModel(model);  // Afficher les résultats
    }









