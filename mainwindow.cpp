#include"mainwindow.h"
#include"ui_mainwindow.h"
#include<QMainWindow>
#include<QMessageBox>
#include "Client.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include "employe.h"
#include "services.h"
#include<QSqlTableModel>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtQuick>
#include<QStyledItemDelegate>
#include <QBarSet>
#include <QValueAxis>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include "statistique.h"
class ImageDelegate : public QStyledItemDelegate
{
public:
    ImageDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        if (index.column() == 8) // Adjust column index to your image_data column
        {
            QByteArray imageData = index.data().toByteArray();
            QPixmap pixmap;
            pixmap.loadFromData(QByteArray::fromBase64(imageData));

            if (!pixmap.isNull())
            {
                QRect rect = option.rect;
                QSize size = pixmap.size().scaled(rect.size(), Qt::KeepAspectRatio);
                QPoint center = rect.center() - QPoint(size.width() / 2, size.height() / 2);

                painter->drawPixmap(QRect(center, size), pixmap);
                return;
            }
        }

        QStyledItemDelegate::paint(painter, option, index);
    }
};

void MainWindow::onImageCellDoubleClicked(const QModelIndex& index)
{
    if (index.column() == 8) // Adjust column index for your images
    {
        QByteArray imageData = index.data().toByteArray();
        QPixmap pixmap;
        pixmap.loadFromData(QByteArray::fromBase64(imageData));

        if (!pixmap.isNull())
        {
            QDialog dialog(this);
            dialog.setWindowTitle("Image Preview");

            QLabel* imageLabel = new QLabel(&dialog);
            imageLabel->setPixmap(pixmap.scaled(800, 600, Qt::KeepAspectRatio)); // Scale as needed
            imageLabel->setAlignment(Qt::AlignCenter);

            QVBoxLayout* layout = new QVBoxLayout(&dialog);
            layout->addWidget(imageLabel);

            dialog.exec();
        }
    }
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    //client
    Client client;
    Services service;
    Transaction transaction;
    ui->setupUi(this);
    ui->tableView_5->setModel(client.afficher());

    connect(ui->tableView_5, &QTableView::doubleClicked, this, &MainWindow::onImageCellDoubleClicked);

        ImageDelegate* imageDelegate = new ImageDelegate(this);
                ui->tableView_5->setItemDelegateForColumn(8, imageDelegate);

    /*ui->comboBoxTri->addItem("NOM_Client");
    connect(ui->comboBoxTri, SIGNAL(currentIndexChanged(int)), this, SLOT(trierClients()));*/
    ui->comboBoxTri_2->addItem("Nom");
       ui->comboBoxTri_2->addItem("Prénom");
       ui->comboBoxTri_2->addItem("Méthode de paiement");

       connect(ui->lineEditRecherche_2, &QLineEdit::textChanged, this, [this]() {
           QString texte = ui->lineEditRecherche_2->text();
           QString critere = ui->comboBoxRecherche_2->currentData().toString();

           Client client;
           QSqlQueryModel* model = client.rechercherParCritereEtTexte( critere, texte);

           ui->tableView_5->setModel(model); });


       // Ajouter les options de recherche dans le QComboBox
       ui->comboBoxRecherche_2->addItem("NOM_Client", "NOM_Client");
       ui->comboBoxRecherche_2->addItem("PRENOM_Client", "PRENOM_Client");
       ui->comboBoxRecherche_2->addItem("TYPE", "TYPE");

       connect(ui->stat_methods_2, &QPushButton::clicked, this, &MainWindow::on_stat_methods_clicked);
       connect(ui->exportButton_3, &QPushButton::clicked, this, &MainWindow::on_exportButton_clicked);
       ui->comboBoxServiceType_2->addItems({"chantier", "desinfectation", "maison","usines"}); // Exemples

////////////////////////////
           //service
           ui->gestion->setCurrentIndex(1);
           ui->service->setCurrentIndex(0);
           ui->widget_2->hide();
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

           ui->tableViewServices->setModel(service.afficher());



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
          //employe
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

          connect(ui->exporterPDFButton_2, &QToolButton::clicked, this, &MainWindow::exporterEnPDF);
          connect(ui->button_stat, &QPushButton::clicked, this, &MainWindow::on_button_stat_clicked);
          connect(ui->sendEmailButton, &QPushButton::clicked, this, &MainWindow::sendEmail);
          connect(ui->btnSendAttachment, &QPushButton::clicked, this, &MainWindow::sendEmailWithAttachment);
          connect(ui->addReminderButton, &QPushButton::clicked, this, &MainWindow::addReminder);
          connect(ui->showRemindersButton, &QPushButton::clicked, this, &MainWindow::showReminders);



          afficherEmploye();
         /////////////////////////transaction
          ui->tab_transaction->setModel(transaction.afficherTransactions());

              ui->date_transaction->setDate(QDate::currentDate());
              ui->code->setVisible(false);
              // Surligner les dates de transaction futures
              highlightFutureTransactionDates();
              connect(ui->comboBox_4, SIGNAL(currentIndexChanged(int)), this, SLOT(onSearchCriterionChanged(int)));
              populateClientComboBox();
              connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxSelectionChanged(int)));
              ui->tab_transaction->setModel(transaction.afficherTransactions());

      //////////////////////////////////fournisseur
              calendar = ui->calendarWidget;

              QSqlTableModel *model = new QSqlTableModel(this);
              // Connexion des boutons aux fonctions appropriées
              connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
              connect(ui->afficher, &QPushButton::clicked, this, &MainWindow::on_afficher_clicked);
              connect(ui->supp, &QPushButton::clicked, this, &MainWindow::on_supp_clicked);
              connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifier_clicked);
              connect(ui->rechercher, &QPushButton::clicked, this, &MainWindow::on_rechercher_clicked);
              connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_pushButton_4_clicked);
              connect(ui->pushButton_Statistics, &QPushButton::clicked, this, &MainWindow::showStatistics);



              model->setTable("tableView");  // Replace with your actual table name
              model->select();  // Fetch data from the table

              // Set the model for the QTableView
              ui->tableView->setModel(model);

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

                    ui->tableView->setModel(model);

                    int ret1 = A1.connect_arduino();
                      switch (ret1) {
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
                      QObject::connect(A1.getserial(), SIGNAL(readyRead()), this, SLOT(update_label1()));
                      int ret2 = A2.connect_arduino();
                        switch (ret2) {
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
                      QObject::connect(A2.getserial(),SIGNAL(readyRead()),this,SLOT(update_label2()));



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_exportButton_clicked()
{

        // Déconnecter temporairement le signal si nécessaire (prévention des appels multiples)
        ui->exportButton_3->disconnect();

        // Obtenir le type de service sélectionné depuis la QComboBox
        QString serviceType = ui->comboBoxServiceType_2->currentText();

        // Vérifier qu'un type est sélectionné
        if (serviceType.isEmpty()) {
            QMessageBox::warning(this, "Export Failed", "Please select a service type to export.");
            // Reconnaître le signal
            connect(ui->exportButton_3, &QPushButton::clicked, this, &MainWindow::on_exportButton_clicked);
            return;
        }

        // Définir un nom par défaut basé sur le type de service
        QString defaultFileName = QString("Client_List_%1.pdf").arg(serviceType);

        // Ouvrir la boîte de dialogue avec un nom par défaut
        QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", defaultFileName, "PDF Files (*.pdf)");

        if (filePath.isEmpty()) {
            // Annuler l'opération si aucun fichier n'est sélectionné
            // Reconnaître le signal
            connect(ui->exportButton_3, &QPushButton::clicked, this, &MainWindow::on_exportButton_clicked);
            return;
        }
    Client client;
        // Appeler la méthode d'exportation
        client.exportClientsByServiceTypeToPDF(filePath, serviceType);

        // Confirmer à l'utilisateur
        QMessageBox::information(this, "Export Successful", "The client list has been successfully exported to: " + filePath);

        // Reconnecter le signal après l'exécution
        connect(ui->exportButton_3, &QPushButton::clicked, this, &MainWindow::on_exportButton_clicked);
    }


void MainWindow::on_pushButtonRecherche_2_clicked()
{
    QString texte = ui->lineEditRecherche_2->text();  // Récupérer le texte saisi
    QString critere = ui->comboBoxRecherche_2->currentData().toString();  // Récupérer la colonne sélectionnée

    Client client;
    QSqlQueryModel* model = client.rechercherParCritereEtTexte(critere, texte);  // Recherche filtrée

    ui->tableView_5->setModel(model);  // Afficher les résultats
}



void MainWindow::on_ajouter_4_clicked()
{
    int CIN_Client = ui->CIN_Client_3->text().toInt();
    QString NOM_Client = ui->Nom_Client_3->text();
    QString PRENOM_Client = ui->PRENOM_Client_3->text();
    QDate DATES_Client = ui->DATES_Client_3->date();
    QString METHODEP_Client = ui->METHODEP_Client_3->currentText();
    QString type = ui->TYPE_3->currentText();
    QString adresse = ui->ADRESSE_Client_3->text();
    QString numc = ui->NUMC_Client_3->text();

    QString selectedImagePath;
    QByteArray imageData =Etmp.processImageWithDialog(selectedImagePath);

        // Afficher l'image dans le QLabel
        if (!selectedImagePath.isEmpty() && ui->IMAGE_Client_3 != nullptr) {
            QPixmap pixmap(selectedImagePath);
                if (!pixmap.isNull()) {
                    ui->IMAGE_Client_3->setPixmap(pixmap.scaled(ui->IMAGE_Client_3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
            }
        QFileInfo FileInfo(selectedImagePath);
        QString imagename =FileInfo.fileName();
    // Créer un objet Client avec tous les paramètres
    Client C(CIN_Client, NOM_Client, PRENOM_Client, DATES_Client, METHODEP_Client, type, adresse, numc, imageData,imagename);


    Client clt =Etmp.getclientByid(CIN_Client);

    if (CIN_Client <= 0) {
        QMessageBox::critical(this, "Error", "The CIN cannot be negative or zero!");
    } else if (NOM_Client.isEmpty()) {
        QMessageBox::critical(this, "Error", "The name cannot be empty!");
    } else if (PRENOM_Client.isEmpty()) {
        QMessageBox::critical(this, "Error", "The last name cannot be empty!");
    } else if (METHODEP_Client.isEmpty()) {
        QMessageBox::critical(this, "Error", "The payment method cannot be empty!");
    } else if (type.isEmpty()) {
        QMessageBox::critical(this, "Error", "The type cannot be empty!");
    } else if (adresse.isEmpty()) {
        QMessageBox::critical(this, "Error", "The address cannot be empty!");
    } else {
        // Create the Client object with the provided inputs
        Client newClient(CIN_Client, NOM_Client, PRENOM_Client, DATES_Client, METHODEP_Client, type, adresse, numc, imageData, imagename);
        bool test = newClient.ajouter();
        if (test) {
            ui->tableView_5->setModel(newClient.afficher());
            QMessageBox::information(this, QObject::tr("Success"),
                                     QObject::tr("Client added successfully.\n"
                                                 "Click Cancel to exit."),
                                     QMessageBox::Cancel);
            // Clear input fields
            ui->Nom_Client_3->clear();
            ui->PRENOM_Client_3->clear();
            ui->CIN_Client_3->clear();
            ui->METHODEP_Client_3->clear();
            ui->TYPE_3->clear();
            ui->ADRESSE_Client_3->clear();
            ui->NUMC_Client_3->clear();
            ui->IMAGE_Client_3->clear(); // Clear image preview if applicable
        } else {
            QMessageBox::critical(this, QObject::tr("Error"),
                                  QObject::tr("Failed to add the client.\n"
                                              "Click Cancel to exit."),
                                  QMessageBox::Cancel);
        }
        ui->client->setCurrentIndex(0);
    }

}

void MainWindow::on_supprimer_4_clicked()
{
    QItemSelectionModel *select = ui->tableView_5->selectionModel();
    if (!select->hasSelection()) {
        QMessageBox::critical(this, "Error", "Please select a row to delete.");
        return;
    }

    // Get the selected row index and extract the ID from the model
    int row = select->currentIndex().row();
    int id = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 0)).toInt();
    Client e=Etmp.getclientByid(id);
    if (e.getCIN_client()!=id){
       QMessageBox::critical(this, "Error", "This ID doesn't exist!");
    }else
    {
        bool test=Etmp.supprimer(id);
        if (test)
        {
            ui->tableView_5->setModel(Etmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("suppression effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("suppression non effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_5->setModel(Etmp.afficher());


    }
}


void MainWindow::on_comboBoxTri_2_currentIndexChanged(int index)
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
        ui->tableView_5->setModel(model);
}


void MainWindow::on_modifier_7_clicked()
{
    QItemSelectionModel *select = ui->tableView_5->selectionModel();
       if (!select->hasSelection()) {
           QMessageBox::critical(this, "Error", "Please select a row to modify.");
           return;
       }

       // Get the selected row index and extract the ID from the model
       int row = select->currentIndex().row();
       int id = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 0)).toInt();
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

           ui->client->setCurrentIndex(1);
}


void MainWindow::on_exportButton_3_clicked()
{
    QString filenameCriterion = "clients";  // Nom de base du fichier

    // Construire le nom du fichier avec la date
    QString filename = filenameCriterion + "_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf";
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", filename, "*.pdf");

    if (filePath.isEmpty()) {
        return;  // Si l'utilisateur annule, sortir de la fonction
    }

    // Récupérer le modèle associé à la vue
    QAbstractItemModel* model = ui->tableView_5->model();
    if (!model) {
        QMessageBox::critical(this, "Error", "No data available in the table to export.");
        return;
    }

    // Appeler la méthode exportToPDF via l'objet Client
    Client client;
    client.exportToPDF(filePath, model);
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
                           ui->tableView_5->setModel(Etmp.afficher());
                           QMessageBox::information(nullptr, QObject::tr("ok"),
                                       QObject::tr("modification effectue.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
                       }
                       else
                           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                       QObject::tr("modification non effectue.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
                       ui->client->setCurrentIndex(0);
}






void MainWindow::on_map_2_clicked()
{
   /*QItemSelectionModel *selectionModel = ui->tableView_5->selectionModel();
        QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

        QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_5->model());

        if (model) {
            QSet<int> selectedRows;

            foreach(const QModelIndex &selectedIndex, selectedIndexes) {
                int row = selectedIndex.row();
                if (!selectedRows.contains(row)) {
                    // Access data from the fifth column of the selected row
                    QModelIndex fifthColumnIndex = model->index(row, 6);
                    QVariant cellData = model->data(fifthColumnIndex);

                    // Split the data by comma and trim any whitespace
                    QStringList parties = cellData.toString().split(",", Qt::SkipEmptyParts);
                    if (parties.size() >= 2) {
                        ui->quickWidget_Map_View->setSource(QUrl(QStringLiteral("qrc:/QmlMap.qml")));
                        ui->quickWidget_Map_View->show();

                        auto obje = ui->quickWidget_Map_View->rootObject();
                        connect(this, SIGNAL(setCenterPosition(QVariant, QVariant)), obje, SLOT(setCenterPosition(QVariant, QVariant)));
                        connect(this, SIGNAL(setLocationMarking(QVariant, QVariant)), obje, SLOT(setLocationMarking(QVariant, QVariant)));

                    QString premierePartie = parties[0].trimmed();
                                        QString deuxiemePartie = parties[1].trimmed();
                                        qDebug() << "Première partie:" << premierePartie.toDouble();
                                        qDebug() << "Deuxième partie:" << deuxiemePartie.toDouble();
                                        emit setCenterPosition(premierePartie.toDouble(), deuxiemePartie.toDouble());
                                        emit setLocationMarking(premierePartie.toDouble(), deuxiemePartie.toDouble());
                                    } else {
                                        qDebug() << "La chaîne ne contient pas suffisamment de parties séparées par des virgules.";
                                    }
                                    selectedRows.insert(row);
                                }
                            }
                        }

                        ui->stackedWidget->setCurrentIndex(2);*/

}
//////////////////////////////////
////////////////////////////////services
void MainWindow::showLoginPage()
{
    // Afficher la page de login dans le QStackedWidget
    ui->service->setCurrentIndex(1); // 1 correspond à la page de login
}

void MainWindow::validateLogin()
{
    QString username = ui->LineEdit_username->text();
    QString password = ui->LineEdit_password->text();

    if (username == "admin" && password == "services") {
        QMessageBox::information(this, "Succès", "Connexion réussie !");
       ui->service->setCurrentIndex(2);  // Retourner à la page principale

        ui->widget_2->show();

    } else {
        QMessageBox::warning(this, "Échec", "Nom d'utilisateur ou mot de passe incorrect.");
        ui->service->setCurrentIndex(0);
    }
}
void MainWindow::showhomepage() {
 ui->service->setCurrentIndex(0) ;}
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
        ui->widget_8->setStatistiques(servicesDisponibles, servicesIndisponibles);


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



void MainWindow::on_pushButtonservices_clicked()
{
    ui->gestion->setCurrentIndex(1);
}

void MainWindow::on_pushButtonclients_clicked()
{
    ui->gestion->setCurrentIndex(1);
}

void MainWindow::on_label_48_linkActivated(const QString &link)
{

}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_pushButton_26_clicked()
{
    ui->gestion->setCurrentIndex(1);

}

void MainWindow::on_stat_methods_clicked()
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
        if (ui->widget_methods_2->layout()) {
            QLayoutItem* item;
            while ((item = ui->widget_methods_2->layout()->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete ui->widget_methods_2->layout();
        }

        QVBoxLayout* layout = new QVBoxLayout(ui->widget_methods_2);
        layout->addWidget(chartView);
        ui->widget_methods_2->setLayout(layout);

        delete model; // Libérez la mémoire du modèle
    }








void MainWindow::on_empbut_2_clicked()
{
    ui->gestion->setCurrentIndex(5);
}


void MainWindow::on_cliebut_2_clicked()
{
    ui->gestion->setCurrentIndex(0);
}


void MainWindow::on_fournbut_2_clicked()
{
    ui->gestion->setCurrentIndex(4);
}


void MainWindow::on_materbut_2_clicked()
{
    ui->gestion->setCurrentIndex(2);
}


void MainWindow::on_transabut_2_clicked()
{
    ui->gestion->setCurrentIndex(3);
}


void MainWindow::on_servbut_2_clicked()
{
    ui->gestion->setCurrentIndex(1);
}


//////////////////////employe



void MainWindow::on_ajouter_3_clicked()
{
        // Récupération de l'ID
        int id = ui->id_2->text().toInt();

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
        QString nom = ui->nom_2->text();
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

void MainWindow::on_modifier_6_clicked()
{
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



void MainWindow::on_supprimer_3_clicked()
{
    // Fonction pour supprimer un Employe
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

void MainWindow::on_rechercher_emp_clicked() {
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


void MainWindow::exporterEnPDFF() {
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



void MainWindow::on_button_stat_clicked()
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

//////////////////////////////////////


void MainWindow::on_pushButton_ajouter_clicked()
{
    // Récupérer les données du formulaire
       int id_materiel = ui->lineEdit_id->text().toInt();
       QString qualite = ui->lineEdit_3->text();
       int quantite = ui->lineEdit_5->text().toInt();
       QString type = ui->comboBox_3->currentText(); // Types disponibles : métal, bois
       float prix_achat = ui->lineEdit_2->text().toFloat();
       float prix_vente = ui->lineEdit_4->text().toFloat();
       QDate date_achat = ui->dateTimeEdit->date();
       QDate date_vente = ui->dateTimeEdit_2->date();

       // Configurer les attributs de l'objet Materiel
       materiel.setIdMateriel(id_materiel);
       materiel.setQualite(qualite);
       materiel.setQuantite(quantite);
       materiel.setType(type);
       materiel.setPrixAchat(prix_achat);
       materiel.setPrixVente(prix_vente);
       materiel.setDateAchat(date_achat);
       materiel.setDateVente(date_vente);

       // Appeler la méthode d'ajout et afficher le résultat
       bool success = materiel.ajouter();

       if (success) {
           QMessageBox::information(nullptr, QObject::tr("Succès"),
                                    QObject::tr("Ajout effectué avec succès.\n"
                                                "Cliquez sur Annuler pour quitter."),
                                    QMessageBox::Cancel);
       } else {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                 QObject::tr("Échec de l'ajout.\n"
                                             "Cliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
       }

}


void MainWindow::on_pushButton_modifier_clicked()
{

    int id_materiel = ui->lineEdit_id->text().toInt();
    QString qualite = ui->lineEdit_3->text();
    int quantite = ui->lineEdit_5->text().toInt();
    QString type = ui->comboBox_3->currentText(); // Types disponibles : métal, bois
    float prix_achat = ui->lineEdit_2->text().toFloat();
    float prix_vente = ui->lineEdit_4->text().toFloat();
    QDate date_achat = ui->dateTimeEdit->date();
    QDate date_vente = ui->dateTimeEdit_2->date();

    // Appeler la méthode de modification
    bool success = materiel.modifier(id_materiel, qualite, quantite, type, prix_achat, prix_vente, date_achat, date_vente);

    if (success) {
        QMessageBox::information(this, tr("Succès"), tr("Modification effectuée avec succès."));
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }

}


void MainWindow::on_pushButton_supprimer_clicked()
{
    // Récupérer l'ID à supprimer à partir du champ de saisie
        int id_materiel = ui->lineEdit_id->text().toInt();

        // Appeler la méthode de suppression
        bool success = materiel.supprimer(id_materiel);

        if (success) {
            QMessageBox::information(this, tr("Succès"), tr("Suppression effectuée avec succès."));
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression. Vérifiez l'ID."));
        }

}


void MainWindow::on_pushButton_rechercher_clicked()
{
    // Récupérer la valeur saisie dans lineEdit_11
        QString input = ui->lineEdit_11->text().trimmed(); // Valeur saisie par l'utilisateur
        if (input.isEmpty()) {
            QMessageBox::warning(this, tr("Recherche invalide"),
                                 tr("Veuillez saisir un critère de recherche sous la forme 'champ:valeur'."));
            return;
        }

        // Extraire le champ et la valeur de la saisie
        QStringList parts = input.split(':');
        if (parts.size() != 2) {
            QMessageBox::warning(this, tr("Format incorrect"),
                                 tr("Veuillez saisir la recherche sous la forme 'champ:valeur' (ex: id_materiel:123)."));
            return;
        }

        QString conditionField = parts[0].trimmed();
        QVariant value = parts[1].trimmed();

        // Vérifier si le champ est valide
        if (!(conditionField == "id_materiel" || conditionField == "type" ||
              conditionField == "quantite" || conditionField == "prix_vente")) {
            QMessageBox::warning(this, tr("Champ invalide"),
                                 tr("Le champ spécifié doit être l'un des suivants : id_materiel, type, quantite, prix_vente."));
            return;
        }

        // Construire la requête SQL dynamiquement
        QString queryStr = "SELECT * FROM materiels WHERE " + conditionField + " = :value";

        QSqlQuery query;
        query.prepare(queryStr);
        query.bindValue(":value", value);

        // Exécuter la requête
        if (query.exec()) {
            QSqlQueryModel *model = new QSqlQueryModel(this);
            model->setQuery(query);

            if (model->rowCount() > 0) {
                ui->tableView->setModel(model);
            } else {
                QMessageBox::information(this, tr("Aucun résultat"),
                                         tr("Aucun matériel trouvé pour la valeur spécifiée."));
                ui->tableView->setModel(nullptr); // Effacer l'affichage
            }
        } else {
            QMessageBox::critical(this, tr("Erreur de recherche"),
                                  tr("Échec de l'exécution de la requête : %1")
                                  .arg(query.lastError().text()));
        }

}


void MainWindow::on_pushButton_trier_clicked()
{
    // Récupérer le critère sélectionné dans comboBox_trier
        QString critere = ui->comboBox_trier->currentText();

        // Créer un modèle pour afficher les résultats
        QSqlQueryModel *model = new QSqlQueryModel(this);

        // Vérifier le critère sélectionné
        if (critere == "trier_par_id") {
            model->setQuery("SELECT * FROM materiels ORDER BY id_materiel ASC");
        } else if (critere == "trier_par_quantite") {
            model->setQuery("SELECT * FROM materiels ORDER BY quantite ASC");
        } else if (critere == "trier_par_type") {
            model->setQuery("SELECT * FROM materiels ORDER BY type ASC");
        } else {
            QMessageBox::warning(this, tr("Critère non pris en charge"),
                                 tr("Le critère sélectionné n'est pas implémenté."));
            return;
        }

        // Vérifier les erreurs SQL
        if (model->lastError().isValid()) {
            QMessageBox::critical(this, tr("Erreur de tri"),
                                  tr("Échec de l'exécution de la requête : %1")
                                  .arg(model->lastError().text()));
            return;
        }

        // Mettre à jour le QTableView avec le modèle trié
        ui->tableView->setModel(model);

        // Message de confirmation (facultatif)
        QMessageBox::information(this, tr("Tri effectué"),
                                 tr("Les données ont été triées avec succès par %1.")
                                 .arg(critere));

}

void MainWindow::verifierStockFaible()
{
    int seuil = 10;
    QSqlQueryModel* model = materiel.verifierStockFaible(seuil);

    if (model->rowCount() > 0) {
        QString message = "Les matériaux suivants ont un stock faible :\n";

        for (int i = 0; i < model->rowCount(); ++i) {
            QSqlRecord record = model->record(i);
            int id = record.value("id_materiel").toInt();
            QString qualite = record.value("qualite").toString();
            QString type = record.value("type").toString();
            int quantite = record.value("quantite").toInt();

            message += QString("ID: %1, Qualité: %2, Type: %3, Quantité: %4\n")
                        .arg(id)
                        .arg(qualite)
                        .arg(type)
                        .arg(quantite);
        }

        QMessageBox::warning(this, tr("Stock Faible"), message);
    } else {
        QMessageBox::information(this, tr("Stock Faible"), tr("Aucun matériel avec un stock faible."));
    }
}

void MainWindow::on_pushButton_notification_clicked()
{
    int seuil = 10; // Seuil pour le stock faible
        QSqlQueryModel* model = materiel.verifierStockFaible(seuil);

        if (model->rowCount() > 0) {
            QString message = "Avertissement : Les matériaux suivants ont un stock faible :\n\n";

            for (int i = 0; i < model->rowCount(); ++i) {
                QSqlRecord record = model->record(i);

                // Récupération des colonnes nécessaires
                int id = record.value("id_materiel").toInt();
                QString qualite = record.value("qualite").toString();
                QString type = record.value("type").toString();
                int quantite = record.value("quantite").toInt();

                // Formatage des informations pour le message
                message += QString("- ID: %1, Qualité: %2, Type: %3, Quantité: %4\n")
                            .arg(id)
                            .arg(qualite)
                            .arg(type)
                            .arg(quantite);
            }

            QMessageBox::warning(this, tr("Notification de Stock Faible"), message);
        } else {
            QMessageBox::information(this, tr("Stock Normal"), tr("Tous les stocks sont suffisants."));
        }

}


void MainWindow::on_toolButton_statistiques_clicked()
{
    // Liste fixe des types de matériaux
        QStringList materialTypes = {"metal", "bois", "Plastique"};

        // Créer un QMap pour stocker les données des matériaux
        QMap<QString, int> materials;

        // Préparer une requête SQL
        QSqlQuery query;
        query.prepare("SELECT type, SUM(quantite) AS total_quantity FROM materiels "
                      "WHERE type IN ('metal', 'bois', 'Plastique') GROUP BY type");

        // Exécuter la requête et récupérer les résultats
        if (!query.exec()) {
            QMessageBox::critical(this, "Erreur", "Échec de l'exécution de la requête : " + query.lastError().text());
            return;
        }

        // Remplir le QMap avec les résultats de la requête
        while (query.next()) {
            QString materialType = query.value("type").toString();  // Type de matériau
            int quantity = query.value("total_quantity").toInt();  // Quantité totale

            materials[materialType] = quantity;
        }

        // Ajouter les types manquants avec des quantités nulles
        for (const QString &type : materialTypes) {
            if (!materials.contains(type)) {
                materials[type] = 0;
            }
        }

        // Calculer la somme totale des quantités pour convertir en pourcentage
        int totalQuantity = 0;
        for (const auto &quantity : materials.values()) {
            totalQuantity += quantity;
        }

        if (totalQuantity == 0) {
            QMessageBox::information(this, "Statistiques", "Aucune donnée disponible pour l'analyse.");
            return;
        }

        // Trier les matériaux par pourcentage
        QPieSeries *series = new QPieSeries();
        for (const QString &material : materials.keys()) {
            // Calculer le pourcentage
            double percentage = (static_cast<double>(materials[material]) / totalQuantity) * 100.0;
            series->append(material + QString(" (%1%)").arg(QString::number(percentage, 'f', 1)), percentage);
        }

        // Créer un graphique
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Répartition des matériaux en pourcentages");
        chart->legend()->setAlignment(Qt::AlignBottom);

        // Vue pour afficher le graphique
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Créer une fenêtre pour afficher le graphique
        QMainWindow *chartWindow = new QMainWindow(this);
        chartWindow->setCentralWidget(chartView);
        chartWindow->resize(600, 400);
        chartWindow->setWindowTitle("Statistiques : Matériaux en Pourcentage");
        chartWindow->show();

}


void MainWindow::on_toolButton_pdf_clicked()
{
    // Prompt the user to choose a location and filename for the PDF file
       QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (.pdf);;All Files ()");

       if (filePath.isEmpty()) {
           QMessageBox::warning(this, "No File Selected", "No file was selected to save.");
           return;
       }

       // Ensure the selected file has a .pdf extension
       if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
           filePath += ".pdf";
       }

       // Create a PDF writer to write the content
       QPdfWriter pdfWriter(filePath);
       pdfWriter.setPageSize(QPageSize(QPageSize::A4));
       pdfWriter.setResolution(300);

       // Create a QPainter to draw on the PDF
       QPainter painter(&pdfWriter);
       if (!painter.isActive()) {
           QMessageBox::critical(this, "PDF Error", "Failed to create the PDF.");
           return;
       }

       // Set up fonts and styles for the PDF
           QFont titleFont("Times New Roman", 18, QFont::Bold);
           QFont headerFont("Arial", 12, QFont::Bold);
           QFont contentFont("Arial", 10);

           // Title
           painter.setFont(titleFont);
           painter.setPen(Qt::darkRed); // Dark blue for the title
           painter.drawText(QRect(0, 0, pdfWriter.width(), 50), Qt::AlignCenter, "Service Evaluation Report");


       // Fetch data from the QTableView
       QAbstractItemModel *model = ui->tableView->model();
       if (!model) {
           QMessageBox::critical(this, "Error", "No data available in the table view.");
           return;
       }

       // Start drawing the table
       int rowCount = model->rowCount();
       int columnCount = model->columnCount();
       int topMargin = 60;
       int leftMargin = 10;

       // Set a larger cell width and height for better visibility
       int cellWidth = pdfWriter.width() / columnCount - 5;
       int cellHeight = 40;

       // Draw table header
       painter.setFont(headerFont);
       painter.setBrush(QBrush(QColor("lightblue"))); // Set light blue background for headers
       painter.setPen(Qt::black);

       for (int col = 0; col < columnCount; ++col) {
           QRect cellRect(leftMargin + col * cellWidth, topMargin, cellWidth, cellHeight);
           painter.drawRect(cellRect);
           painter.drawText(cellRect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
       }

       // Draw table rows
       painter.setFont(contentFont);
       painter.setPen(Qt::black);

       for (int row = 0; row < rowCount; ++row) {
           QColor rowColor = (row % 2 == 0) ? Qt::white : QColor("lightgray"); // Alternate row colors
           painter.setBrush(QBrush(rowColor));

           for (int col = 0; col < columnCount; ++col) {
               QRect cellRect(leftMargin + col * cellWidth, topMargin + (row + 1) * cellHeight, cellWidth, cellHeight);
               painter.drawRect(cellRect);
               QString cellText = model->data(model->index(row, col)).toString();
               painter.drawText(cellRect, Qt::AlignCenter, cellText);
           }
       }

       // Finish the PDF
       painter.end();

       // Notify the user that the PDF was saved
       QMessageBox::information(this, "PDF Saved", "The PDF was saved successfully at " + filePath);

}


/*

void MainWindow::enregistrerHistorique(const QString &action, int idMateriel, const QString &qualite, int quantite,
                                       const QString &type, const QDate &dateAchat, double prixAchat,
                                       const QDate &dateVente, double prixVente)
{
    QSqlQuery query;
    query.prepare("INSERT INTO historique (action, id_materiel, qualite, quantite, type, date_achat, prix_achat, date_vente, prix_vente) "
                  "VALUES (:action, :id_materiel, :qualite, :quantite, :type, :date_achat, :prix_achat, :date_vente, :prix_vente)");
    query.bindValue(":action", action);
    query.bindValue(":id_materiel", idMateriel);
    query.bindValue(":qualite", qualite);
    query.bindValue(":quantite", quantite);
    query.bindValue(":type", type);
    query.bindValue(":date_achat", dateAchat);
    query.bindValue(":prix_achat", prixAchat);
    query.bindValue(":date_vente", dateVente);
    query.bindValue(":prix_vente", prixVente);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'enregistrement dans l'historique :" << query.lastError().text();
    } else {
        qDebug() << "Historique enregistré avec succès.";
    }
}
void MainWindow::on_pushButton_historique_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM historique ORDER BY date_action DESC");
    model->setHeaderData(1, Qt::Horizontal, "Action");
    model->setHeaderData(2, Qt::Horizontal, "ID Matériel");
    model->setHeaderData(3, Qt::Horizontal, "Qualité");
    model->setHeaderData(4, Qt::Horizontal, "Quantité");
    model->setHeaderData(5, Qt::Horizontal, "Type");
    model->setHeaderData(6, Qt::Horizontal, "Date Achat");
    model->setHeaderData(7, Qt::Horizontal, "Prix Achat");
    model->setHeaderData(8, Qt::Horizontal, "Date Vente");
    model->setHeaderData(9, Qt::Horizontal, "Prix Vente");

    ui->tableView->setModel(model);
}
*/


////////////////////////////transaction

void MainWindow::update_label()
{// Ajouter les données reçues au tampon
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
            ui->statusLabel_3->setText("Carte autorisée !");
        } else if (completeMessage == "DENIED") {
            A.write_to_arduino("0"); // Envoyer "0" pour allumer la LED rouge
            qDebug() << "Commande '0' envoyée à Arduino automatiquement.";
            ui->statusLabel_3->setText("Carte refusée !");
        }

}
}

void MainWindow::populateClientComboBox() {
    // Clear the combo box first
    ui->clienbox->clear();

    // Query the database to fetch client IDs
    QSqlQuery query;
    query.prepare("SELECT IDCLIENT FROM client");

    if (query.exec()) {
        while (query.next()) {
            QString id_client = query.value(0).toString();
            qDebug() << "ID client trouvé : " << id_client;
            ui->clienbox->addItem(id_client);
        }
        qDebug() << "Client IDs successfully added to the combo box.";
    } else {
        qDebug() << "Failed to fetch client IDs: " << query.lastError().text();
    }
    QStringList clientIds;
    while (query.next()) {
        QString id_client = query.value(0).toString();
        clientIds << id_client;
        ui->clienbox->addItem(id_client);
    }
    qDebug() << "Liste des IDs récupérés : " << clientIds;


}

void MainWindow::onSearchCriterionChanged(int index)
{

    QString selectedCriterion = ui->comboBox_4->itemText(index);


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


void MainWindow::on_rechercher_2_clicked()
{
    // Get the selected search criterion and search input
        QString selectedCriterion = ui->comboBox_4->currentText();
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

void MainWindow::on_exportStatistique_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter les Statistiques en PDF", "", "Fichiers PDF (*.pdf)");
      Statistique stats;
      stats.exportToPdf(fileName);

}


void MainWindow::on_exportButton_2_clicked()
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


void MainWindow::on_pushButton_ajouter_2_clicked()
{
    if (ui->pushButton_ajouter_2->text() == "Ajouter") {
            ui->code->setVisible(true);
            ui->pushButton_ajouter_2->setText("Vérifier");
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

bool MainWindow::handleTransaction(int receivedCode)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENTS WHERE CIN_CLIENT = :code");
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

void MainWindow::on_pushButton_modifier_2_clicked()
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


void MainWindow::on_pushButton_supprimer_2_clicked()
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


void MainWindow::on_afficher_clicked()
{
    ui->tableView->setModel(tfournisseur.afficher()); // Actualisation de la vue
}


void MainWindow::on_pushButton_clicked()
{
    int id = ui->lineEdit_10->text().toInt();
        QString nom = ui->lineEdit_8->text();
        QString prenom = ui->lineEdit_9->text();
        QString type = ui->lineEdit_6->currentText();

        int numero = ui->lineEdit_12->text().toInt();

        fournisseur r(nom, prenom, type, id, numero);

        bool test = r.ajouter();
        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"), QObject::tr("ajout effectué"), QMessageBox::Cancel);

            ui->tableView->setModel(tfournisseur.afficher()); // Actualisation de la vue
            // Nettoyage des champs
            ui->lineEdit_10->clear();
            ui->lineEdit_8->clear();
            ui->lineEdit_9->clear();
            ui->lineEdit_6->setCurrentIndex(-1);

            ui->lineEdit_12->clear();
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr("ajout non effectué"), QMessageBox::Cancel);
        }

}


void MainWindow::on_supp_clicked()
{
    QString nom = ui->lineEdit_7->text();
    QMessageBox msgbox;
    msgbox.setWindowTitle("supprimer");
    msgbox.setText("Voulez-vous supprimer cette fournisseur ?");
    msgbox.setStandardButtons(QMessageBox::Yes);
    msgbox.addButton(QMessageBox::No);

    if (msgbox.exec() == QMessageBox::Yes)
    {
        bool test = tfournisseur.supprimer(nom);
        if (test)
        {
            ui->tableView->setModel(tfournisseur.afficher()); // Actualisation de la vue
            ui->lineEdit_7->clear();
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("supprimer un fournisseur"), QObject::tr("Erreur.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    }
    else
    {
        ui->tableView->setModel(tfournisseur.afficher()); // Actualisation de la vue si l'utilisateur annule
    }

}


void MainWindow::on_modifier_5_clicked()
{
    QString nom = ui->lineEdit_17->text();
    QString prenom = ui->lineEdit_16->text();
    QString type = ui->lineEdit_15->currentText();
    int id = ui->lineEdit_13->text().toInt();
    int numero = ui->lineEdit_14->text().toInt();
    // Vérification que l'ID est fourni avant la modification
    if (nom.isEmpty()) {
        QMessageBox::information(nullptr, QObject::tr("No ID Entered"), QObject::tr("Please enter an ID to modify."), QMessageBox::Ok);
        return;
    }

    bool test = tfournisseur.modifier(nom, prenom, type, id, numero);

    if (test) {
        ui->tableView->setModel(tfournisseur.afficher()); // Actualisation de la vue
        // Nettoyage des champs
        ui->lineEdit_17->clear();
        ui->lineEdit_16->clear();
        ui->lineEdit_15->setCurrentIndex(-1);
        ui->lineEdit_13->clear();
        ui->lineEdit_14->clear();

        QMessageBox::information(nullptr, QObject::tr("Modifier une fournisseur"), QObject::tr("Modification réussie."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Modifier une fournisseur"), QObject::tr("Erreur lors de la modification.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }

}


void MainWindow::on_rechercher_3_clicked()
{
    QString nom = "1";
        QString prenom = "";
        QString type = "";
        int id = 0;
        int numero = 0;


        fournisseur R(nom, prenom, type, id, numero);
        QString cas = ui->lineEdit_19->text();
        R.rechercher(ui->tableView_3, cas);

        if (ui->lineEdit_19->text().isEmpty())
        {
            ui->tableView_3->setModel(R.afficher());
        }

}


void MainWindow::on_pushButton_4_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("numero"));


        ui->tableView_3->setModel(model);

        QSqlQuery query;

        QString orderByClause;

        // Vérification de la colonne de tri choisie
        if (ui->comboBox->currentText() == "id")
            orderByClause = "ORDER BY id ASC";
        else if (ui->comboBox->currentText() == "montant")
            orderByClause = "ORDER BY montant ASC";

        query.prepare("SELECT * FROM fournisseur " + orderByClause);

        if (query.exec() && query.next())
        {
            model->setQuery(query);
            ui->tableView_3->setModel(model);
        }

}
#include <QDate>
#include <QMessageBox>
#include <QSqlQuery>

void MainWindow::checkUpcomingArrivals()
{
    QDate currentDate = QDate::currentDate();
    qDebug() << "Current date:" << currentDate.toString("yyyy-MM-dd");

    QSqlQuery query;
    query.prepare("SELECT nom, date_arrive FROM fournisseur");
    query.exec();

    bool foundUpcomingArrival = false;

    while (query.next()) {
        QString nom = query.value(0).toString();
        QString date_arrive_str = query.value(1).toString();
        QDate dateArrive = QDate::fromString(date_arrive_str, "dd-MM-yyyy");

        qDebug() << "Checking nom:" << nom << "Arrival date:" << dateArrive.toString("yyyy-MM-dd");

        if (currentDate.daysTo(dateArrive) <= 3 && currentDate.daysTo(dateArrive) >= 0) {
            // If the arrival date is within the next 3 days
            QString message = QString("Client with nom %1 has an arrival within 3 days: %2")
                                  .arg(nom)
                                  .arg(dateArrive.toString("yyyy-MM-dd"));
            QMessageBox::information(this, "Upcoming Arrival", message);
            foundUpcomingArrival = true;
            break;  // If you find one upcoming arrival, stop further checks.
        }
    }

    if (!foundUpcomingArrival) {
        QMessageBox::information(this, "No Upcoming Arrivals", "No upcoming arrivals within 3 days.");
    }
}

void MainWindow::showStatistics()
{
    fournisseur r;

    int totalfournisseurs = r.getTotalfournisseurs();

    // Display the results in a message box (you can customize this as needed)
    QString statsMessage = QString("Total fournisseurs: %1\n")
                               .arg(totalfournisseurs);


    QMessageBox::information(this, "Statistics", statsMessage);
}

void MainWindow::exportToPDF()
{
    QString filePath = "C:\\Users\\DELL\\Desktop\\youssef msabah\\Atelier_Connexion\\fournisseur.pdf";
    QPdfWriter writer(filePath);

    // Set A4 page size
    writer.setPageSize(QPageSize::A4);
    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Error", "Failed to start painting the PDF.");
        return;
    }

    // Set the font and pen for the painter
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));

    // Write title on top of the PDF
    painter.drawText(50, 50, "fournisseurs List");

    // Get the model from the QTableView
    QTableView *tableView = ui->tableView;
    QAbstractItemModel *model = tableView->model();  // Get the model

    if (!model) {
        QMessageBox::critical(this, "Error", "No model set for the table view.");
        return;
    }

    // Set starting position for the table data
    int rowHeight = 2000;  // height of each row in the PDF
    int colWidth = 1250;  // width of each column in the PDF
    int startX = 15;    // starting X position for the first column
    int startY = 2000;    // starting Y position for the first row

    // Draw column headers
    for (int col = 0; col < model->columnCount(); ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(startX + (col * colWidth), startY, header);
    }

    // Move the Y position down for the table data
    startY += rowHeight + 5;  // Add extra space between header and data

    // Iterate through the rows and columns of the model to draw the data
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            // Retrieve the data for each cell
            QString text = model->data(model->index(row, col)).toString();

            // Draw the text in the PDF with additional spacing
            painter.drawText(startX + (col * colWidth), startY + (row * rowHeight), text);
        }
    }

    // Draw the table borders (optional for better structure)
    for (int row = 0; row <= model->rowCount(); ++row) {
        painter.drawLine(startX, startY + (row * rowHeight), startX + colWidth * model->columnCount(), startY + (row * rowHeight)); // Horizontal lines
    }
    for (int col = 0; col <= model->columnCount(); ++col) {
        painter.drawLine(startX + (col * colWidth), startY, startX + (col * colWidth), startY + (rowHeight * model->rowCount())); // Vertical lines
    }

    painter.end();  // Finalize PDF writing

    // Notify the user that the PDF was successfully created
    QMessageBox::information(this, "Export Complete", "PDF has been successfully created.");
}




void MainWindow::on_pushButton_ExportPDF_clicked()
{
        exportToPDF();  // Call the exportToPDF function when the button is clicked
}

void MainWindow::updateCalendarWithArrivals()
{
    // Create a calendar widget object if not already created
    QCalendarWidget *calendar = new QCalendarWidget(this);
    calendar->setGridVisible(true);

    // List of arrival dates to highlight
    QStringList arrivalDates = {"24/11/2024", "22/11/2024", "23/11/2024", "31/12/1999"};

    // Loop through each arrival date and highlight on the calendar
    for (const QString &dateStr : arrivalDates) {
        // Convert the string to a QDate
        QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");

        // Check if the date is valid
        if (date.isValid()) {
            QTextCharFormat format;
            format.setBackground(QBrush(QColor(0, 255, 0)));  // Highlight with green background

            // Set the text format for the specific date
            calendar->setDateTextFormat(date, format);
        }
    }

    // Show the calendar widget (you might want to adjust its position)
    calendar->show();
}
/*
void MainWindow::update_label() {
    // Append received data to the buffer
    dataBuffer += A.read_from_arduino();
    qDebug() << "Raw data received from Arduino:" << dataBuffer;

    // Check if the buffer contains a complete message (ending with '\n')
    int newlineIndex = dataBuffer.indexOf('\n');
    while (newlineIndex != -1) { // Process all complete lines
        // Extract and trim the complete message
        QString completeMessage = dataBuffer.left(newlineIndex).trimmed();
        dataBuffer.remove(0, newlineIndex + 1);

        qDebug() << "Complete message received:" << completeMessage;

        // Process the complete message
        if (completeMessage == "AUTHORIZED") {
            int bytes = A.write_to_arduino("1"); // Send "1" to Arduino
            if (bytes != -1) {
                qDebug() << "Sent '1' to Arduino successfully.";
            } else {
                qDebug() << "Failed to send '1' to Arduino.";
            }
            ui->statusLabel->setText("Carte autorisée !");
        } else if (completeMessage == "DENIED") {
            int bytes = A.write_to_arduino("0"); // Send "0" to Arduino
            if (bytes != -1) {
                qDebug() << "Sent '0' to Arduino successfully.";
            } else {
                qDebug() << "Failed to send '0' to Arduino.";
            }
            ui->statusLabel->setText("Carte refusée !");
        } else {
            qDebug() << "Unknown message received: " << completeMessage;
        }

        // Check for more complete lines in the buffer
        newlineIndex = dataBuffer.indexOf('\n');
    }
}
*/
void MainWindow::addDataToTableViewfournisseurCalander(const QList<QMap<QString, QString>>& dataList)
{
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Nom", "Prenom", "type","id","numero"}); // Exemples d'en-têtes

    for (const auto& row : dataList) {
        QList<QStandardItem*> items;
        items << new QStandardItem(row.value("numero_fl"));
        items << new QStandardItem(row.value("nom"));
        model->appendRow(items);
    }

    ui->tableView_4->setModel(model); // Assurez-vous que ce widget existe
}

void MainWindow::highlightReservationDates()
{
fournisseur f;

QList<QDate> reservationDates = f.retrieveReservationDates("fournisseur");

// Create a QTextCharFormat for highlighting
QTextCharFormat format;
format.setBackground(Qt::yellow);  // Highlight with a yellow background
format.setForeground(Qt::black);  // Set text color to black
format.setFontWeight(QFont::Bold);

// Apply formatting to the calendar widget
for (const QDate& date : reservationDates) {
    ui->calendarWidget->setDateTextFormat(date, format);
}
}

void MainWindow::on_calendarWidget_2_selectionChanged()
{
    fournisseur f;
        // Get the selected date from the calendar widget
        QDate selectedDate = ui->calendarWidget->selectedDate();

        // Display the selected date in the line edit
        ui->lineEdit_7->setText(selectedDate.toString("yyyy-MM-dd"));

        // Retrieve fournisseur data for the selected date
        QList<QMap<QString, QString>> dataList = f.retrieveAllCalanderDataAsList("fournisseur", selectedDate);

        // Populate the table view with the retrieved data
        addDataToTableViewfournisseurCalander(dataList);

}

void MainWindow::update_label1() {
    // Append received data to the buffer
    dataBuffer += A1.read_from_arduino();
    qDebug() << "Raw data received from Arduino:" << dataBuffer;

    // Check if the buffer contains a complete message (ending with '\n')
    int newlineIndex = dataBuffer.indexOf('\n');
    while (newlineIndex != -1) { // Process all complete lines
        // Extract and trim the complete message
        QString completeMessage = dataBuffer.left(newlineIndex).trimmed();
        dataBuffer.remove(0, newlineIndex + 1);

        qDebug() << "Complete message received:" << completeMessage;

        // Process the complete message
        if (completeMessage == "AUTHORIZED") {
            int bytes = A1.write_to_arduino("1"); // Send "1" to Arduino
            if (bytes != -1) {
                qDebug() << "Sent '1' to Arduino successfully.";
            } else {
                qDebug() << "Failed to send '1' to Arduino.";
            }
            ui->statusLabel_2->setText("Carte autorisée !");
        } else if (completeMessage == "DENIED") {
            int bytes = A1.write_to_arduino("0"); // Send "0" to Arduino
            if (bytes != -1) {
                qDebug() << "Sent '0' to Arduino successfully.";
            } else {
                qDebug() << "Failed to send '0' to Arduino.";
            }
            ui->statusLabel_2->setText("Carte refusée !");
        } else {
            qDebug() << "Unknown message received: " << completeMessage;
        }

        // Check for more complete lines in the buffer
        newlineIndex = dataBuffer.indexOf('\n');
    }
}
void MainWindow::update_label2() {

// Append incoming data to a buffer
  data += A2.read_from_arduino();
  qDebug() << "Données reçues d'Arduino :" << data;
  int newlineIndex = data.indexOf('\n');
  if (newlineIndex != -1) {

      QString message = data.left(newlineIndex);
      bool conversionOk = false;
      int receivedCode = message.toInt(&conversionOk);

      if (conversionOk) {
          if(handleTransaction(receivedCode)){
              A2.write_to_arduino("ok\n");
              data ="";
              QMessageBox::information(this, "Succès", "La transaction a été ajoutée avec succès!");
          }
          else{
              A2.write_to_arduino("no\n");
              data ="";
              QMessageBox::warning(this, "Erreur", "Le code client est incorrect.");
          }
      } else {
          ui->label->setText("Code invalide reçu d'Arduino");
      }
  }
}
