
#include "Client.h"
#include<QString>
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QtCore>
#include<QtCore/Qt>
#include<QColor>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QPdfWriter>
#include <QPrinter>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextTable>
#include <QTextBlockFormat>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QTextCursor>
#include <QSqlRecord>
#include <QPrinter>
#include <QStandardPaths>
#include <QDebug>
#include <QPdfWriter>
#include <QSqlRecord>
#include <QMap>
#include <algorithm>
#include <QSqlError>
#include<QSqlTableModel>
#include <QStyledItemDelegate>


Client::Client(int CIN_Client,QString NOM_Client,QString PRENOM_Client,QDate DATEA_Client,QString METHODEP_Client,QString TYPE,QString ADRESSE_Client,QString NUMC_Client,QByteArray image_data,QString image_name)
{
    this->CIN_Client=CIN_Client;
    this->NOM_Client=NOM_Client;
    this->PRENOM_Client=PRENOM_Client;
    this->DATES_Client=DATEA_Client;
    this->METHODEP_Client=METHODEP_Client;
    this->TYPE=TYPE;
    this->ADRESSE_Client=ADRESSE_Client;
    this->NUMC_Client=NUMC_Client;
    this->image_data=image_data ;
    this->image_name=image_name;
}

bool Client::ajouter() {




    QSqlQuery query;
    query.prepare("INSERT INTO clients( CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, DATES_CLIENT, METHODEP_CLIENT, TYPE, ADRESSE_CLIENT, NUMC_CLIENT, image_data,image_name) "
                  "VALUES (:CIN_Client, :NOM_Client, :PRENOM_Client, :DATES_Client, :METHODEP_Client, :TYPE, :ADRESSE_Client, :NUMC_Client,:image_data, :image_name)");

    query.bindValue(":CIN_Client", QString::number(CIN_Client));
    query.bindValue(":NOM_Client", NOM_Client);
    query.bindValue(":PRENOM_Client", PRENOM_Client);
    query.bindValue(":DATES_Client", DATES_Client);
    query.bindValue(":METHODEP_Client", METHODEP_Client);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":ADRESSE_Client", ADRESSE_Client);
    query.bindValue(":NUMC_Client", NUMC_Client);
    query.bindValue(":image_data", image_data);

    query.bindValue(":image_name", image_name);




    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête SQL :" << query.lastError().text();
        return false;
    }
qDebug() << "Client ajouté avec succès.";
    return true;
}



bool Client::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("delete from clients where CIN_Client=:id");
    query.bindValue(":id",res);
    return query.exec();
}



QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM clients");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN_Client"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_Client"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEA_Client"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("METHODEP_Client"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("ADRESSE_Client"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("NUMC_Client"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("image_data"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("image_name"));


    return model;
}



Client Client::getclientByid(int id)
 {
     QSqlQuery query;
     Client client;

     query.prepare("SELECT * FROM clients WHERE CIN_Client= :id");
     query.bindValue(":id", id);
     if (query.exec() && query.next()) {
         // Remplir l'objet client
     } else {
         qDebug() << "Erreur ou aucun client trouvé pour l'ID :" << query.lastError().text();
     }


     if(query.exec() && query.next())
     {
         client.set_CIN_Client(query.value(0).toInt());
         client.set_NOM_Client(query.value(1).toString());
         client.set_PRENOM_Client(query.value(2).toString());
         client.set_DATES_client(query.value(3).toDate());
         client.set_METHODEP_client(query.value(4).toString());
         client.set_TYPE(query.value(5).toString());
         client.set_ADRESSE_client(query.value(6).toString());
         client.set_NUMC_Client(query.value(7).toString());

     }

     return client;
 }
 bool Client::checkIfidExists(int id)
 {
     QSqlQuery query;
         query.prepare("SELECT CIN_Client FROM clients WHERE CIN_Client = :id");
         query.bindValue(":id", id);

         if (query.exec() && query.next()) {

             return true;
         } else {
             QMessageBox::warning(nullptr, "Database Error", "Error checking ID existence: " + query.lastError().text());
             return false;
         }
 }
 bool Client::modifier(int CIN_Client,QString NOM_Client,QString PRENOM_Client,QDate DATES_Client,QString METHODEP_Client,QString TYPE,QString ADRESSE_Client,QString NUMC_Client)
 {
     QSqlQuery query;
     QString res=QString::number(CIN_Client);

     query.prepare("update clients set NOM_CLIENT=:NOM_CLIENT,PRENOM_CLIENT=:PRENOM_CLIENT,DATES_CLIENT=:DATES_CLIENT,METHODEP_CLIENT=:METHODEP_CLIENT,TYPE=:TYPE,ADRESSE_CLIENT=:ADRESSE_CLIENT,NUMC_CLIENT=:NUMC_CLIENT where CIN_Client=:id");
     query.bindValue(":id",res);
     query.bindValue(":NOM_CLIENT",NOM_Client);
     query.bindValue(":PRENOM_CLIENT",PRENOM_Client);
     query.bindValue(":DATES_CLIENT",DATES_Client);
     query.bindValue(":METHODEP_CLIENT",METHODEP_Client);
     query.bindValue(":TYPE",TYPE);
     query.bindValue(":ADRESSE_CLIENT",ADRESSE_Client);
     query.bindValue(":NUMC_CLIENT",NUMC_Client);

     if (!query.exec()) {
             qDebug() << "Erreur dans la requête UPDATE :" << query.lastError().text();
             return false;}
     return true;
 }






















 void Client::exportToPDF(const QString& filePath, QAbstractItemModel* model) {
        if (!model) {
            QMessageBox::warning(nullptr, "Export Failed", "No data available to export.");
            return;
        }

        // Créer un document QTextDocument pour le contenu du PDF
        QTextDocument doc;
        QString htmlContent;

        // Titre du document
        htmlContent += "<h1 style='text-align: center;'>Client List</h1>";
        htmlContent += "<hr/>";  // Ligne séparatrice

        // Créer le tableau HTML pour les données
        htmlContent += "<table border='1' cellpadding='4' cellspacing='0' width='100%'>"
                       "<tr>"
                       "<th>CIN</th>"
                       "<th>Name</th>"
                       "<th>Surname</th>"
                       "<th>Date</th>"
                       "<th>Payment Method</th>"
                       "<th>Type</th>"
                       "<th>Address</th>"
                       "<th>Phone Number</th>"
                       "</tr>";

        // Remplir le tableau avec les données du modèle
        for (int row = 0; row < model->rowCount(); ++row) {
            htmlContent += "<tr>";
            for (int col = 0; col < model->columnCount(); ++col) {
                QString cellData = model->data(model->index(row, col)).toString();
                htmlContent += "<td>" + cellData + "</td>";
            }
            htmlContent += "</tr>";
        }
        htmlContent += "</table>";

        // Ajouter le contenu HTML au document
        doc.setHtml(htmlContent);

        // Configurer l'imprimante pour la sortie en PDF
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);
        printer.setPageSize(QPageSize(QPageSize::A4));

        // Imprimer le document en PDF
        doc.print(&printer);

        // Message de confirmation
        QMessageBox::information(nullptr, "Export Successful", "The PDF file has been saved to: " + filePath);
    }








 QSqlQueryModel* Client::getMethodStatistics() {
     QSqlQueryModel* model = new QSqlQueryModel();

     QSqlQuery query;
     query.prepare("SELECT METHODEP_Client, COUNT(*) as method_count "
                   "FROM clients "
                   "GROUP BY METHODEP_Client");

     if (query.exec()) {
         model->setQuery(query);
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("METHODEP_Client"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("method_count"));
         return model;
     } else {
         qDebug() << "Erreur lors de la récupération des statistiques des méthodes :"
                  << query.lastError().text();
         return nullptr;
     }
 }















 QSqlQueryModel* Client::trier(const QString& critere) {
     QSqlQueryModel* model = new QSqlQueryModel();
     QSqlQuery query;

     // Construire la requête SQL en fonction du critère
     QString queryStr = QString("SELECT CIN_Client, NOM_Client, PRENOM_Client, DATES_Client, "
                                 "METHODEP_Client, TYPE, ADRESSE_Client, NUMC_Client "
                                 "FROM clients "
                                 "ORDER BY %1 ASC").arg(critere);

     // Exécuter la requête
     if (query.exec(queryStr)) {
         model->setQuery(query);
     } else {
         QMessageBox::warning(nullptr, "Erreur SQL", "Erreur lors du tri : " + query.lastError().text());
     }

     return model;
 }





 QSqlQueryModel* Client::rechercherParCritereEtTexte(const QString& critere, const QString& texte) {
     QSqlQuery query;

     // Construire la requête SQL dynamique selon le critère choisi
     QString queryStr = "SELECT * FROM clients WHERE " + critere + " LIKE :texte";

     query.prepare(queryStr);
     query.bindValue(":texte", "%" + texte + "%");

     QSqlQueryModel* model = new QSqlQueryModel();
     if (query.exec()) {
         model->setQuery(query);
     } else {
         qDebug() << "Error in query:" << query.lastError().text();
     }
     return model;
 }


 QByteArray Client::processImageWithDialog(QString& selectedImagePath) {
         // Ouvre une boîte de dialogue pour sélectionner une image
         QString imagePath = QFileDialog::getOpenFileName(
             nullptr,
             QObject::tr("Select Image"),
             QCoreApplication::applicationDirPath(),
             QObject::tr("Image Files (*.jpg *.jpeg *.png)")
         );

         // Vérifiez si un fichier a été sélectionné
         if (imagePath.isEmpty()) {
             qWarning() << "No image selected.";
             return QByteArray();
         }

         // Mettre à jour le chemin sélectionné
         selectedImagePath = imagePath;

         // Charger l'image sélectionnée
         QPixmap image(imagePath);
         if (image.isNull()) {
             qWarning() << "Invalid image or unsupported format.";
             return QByteArray();
         }

         // Sauvegarder les données de l'image en Base64
         QBuffer imageBufferData;
         if (imageBufferData.open(QIODevice::ReadWrite)) {
             image.save(&imageBufferData, "JPG");
         } else {
             qWarning() << "Failed to open buffer for image processing.";
             return QByteArray();
         }

         QByteArray finalDataToSave = imageBufferData.buffer().toBase64();
         return finalDataToSave;
     }
















 void Client::exportClientsByServiceTypeToPDF(const QString& filePath, const QString& serviceType) {
     if (serviceType.isEmpty()) {
         QMessageBox::warning(nullptr, "Export Failed", "No service type selected.");
         return;
     }

     QSqlQuery query;
     query.prepare("SELECT CIN_Client, NOM_Client, PRENOM_Client, DATES_Client, METHODEP_Client, TYPE, ADRESSE_Client, NUMC_Client "
                   "FROM clients WHERE TYPE = :serviceType");
     query.bindValue(":serviceType", serviceType);

     if (!query.exec()) {
         QMessageBox::critical(nullptr, "Database Error", query.lastError().text());
         return;
     }

     // Vérifier si des résultats sont retournés
     if (!query.next()) {
         QMessageBox::information(nullptr, "No Data", QString("No clients found for the service type: %1").arg(serviceType));
         return;
     }

     // Créer un document QTextDocument pour le contenu du PDF
     QTextDocument doc;
     QString htmlContent;

     // Titre du document
     htmlContent += QString("<h1 style='text-align: center;'>Clients List for Service Type: %1</h1>").arg(serviceType);
     htmlContent += "<hr/>";

     // Créer le tableau HTML
     htmlContent += "<table border='1' cellpadding='4' cellspacing='0' width='100%'>"
                    "<tr>"
                    "<th>CIN</th>"
                    "<th>Name</th>"
                    "<th>Surname</th>"
                    "<th>Date</th>"
                    "<th>Payment Method</th>"
                    "<th>Type</th>"
                    "<th>Address</th>"
                    "<th>Phone Number</th>"
                    "</tr>";

     // Remplir le tableau avec les données de la requête
     query.first(); // Revenir au premier résultat
     do {
         htmlContent += "<tr>";
         htmlContent += "<td>" + query.value("CIN_Client").toString() + "</td>";
         htmlContent += "<td>" + query.value("NOM_Client").toString() + "</td>";
         htmlContent += "<td>" + query.value("PRENOM_Client").toString() + "</td>";
         htmlContent += "<td>" + query.value("DATES_Client").toDate().toString("yyyy-MM-dd") + "</td>";
         htmlContent += "<td>" + query.value("METHODEP_Client").toString() + "</td>";
         htmlContent += "<td>" + query.value("TYPE").toString() + "</td>";
         htmlContent += "<td>" + query.value("ADRESSE_Client").toString() + "</td>";
         htmlContent += "<td>" + query.value("NUMC_Client").toString() + "</td>";
         htmlContent += "</tr>";
     } while (query.next());

     htmlContent += "</table>";

     // Ajouter le contenu HTML au document
     doc.setHtml(htmlContent);

     // Configurer l'imprimante pour la sortie en PDF
     QPrinter printer(QPrinter::HighResolution);
     printer.setOutputFormat(QPrinter::PdfFormat);
     printer.setOutputFileName(filePath);
     printer.setPageSize(QPageSize(QPageSize::A4));

     // Imprimer le document en PDF
     doc.print(&printer);

     // Message de confirmation
     QMessageBox::information(nullptr, "Export Successful", "The PDF file has been saved to: " + filePath);
 }


