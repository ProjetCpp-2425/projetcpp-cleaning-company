#include "mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
