#include "transaction.h"
#include <QDebug>
#include <QSqlError>

// Constructor with initialization list
Transaction::Transaction(int id_transaction, float montant, QDate date_transaction, QString type_transaction, QString statut_transaction)
    : id_transaction(id_transaction), montant(montant), date_transaction(date_transaction),
      type_transaction(type_transaction), statut_transaction(statut_transaction)
{
    qDebug() << "Objet Transaction créé avec ID:" << id_transaction
             << ", Montant:" << montant << ", Date:" << date_transaction
             << ", Type:" << type_transaction << ", Statut:" << statut_transaction;
}

bool Transaction::ajouterTransaction()
{
    QSqlQuery query;

    // Prepare the SQL insert statement
    query.prepare("INSERT INTO transaction (id_transaction, montant, date_transaction, type_transaction, status_transaction) "
                  "VALUES (:id_transaction, :montant, :date_transaction, :type_transaction, :statut_transaction)");

    // Bind values
    query.bindValue(":id_transaction", id_transaction);
    query.bindValue(":montant", montant);
    query.bindValue(":date_transaction", date_transaction); // Bind QDate directly
    query.bindValue(":type_transaction", type_transaction);
    query.bindValue(":statut_transaction", statut_transaction);

    bool success = query.exec();
    if (success) {
        qDebug() << "Transaction ajoutée avec succès avec l'ID:" << id_transaction;
    } else {
        qDebug() << "Échec de l'ajout de la transaction avec l'ID:" << id_transaction;
        qDebug() << "Erreur SQL:" << query.lastError().text();
    }
    return success;
}



bool Transaction::modifierTransaction(int id_transaction, float montant, QDate date_transaction, QString type_transaction, QString statut_transaction)
{
    QSqlQuery query;

    // Check if the transaction ID exists
    query.prepare("SELECT COUNT(*) FROM transaction WHERE id_transaction = :id_transaction");
    query.bindValue(":id_transaction", id_transaction);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de l'existence de la transaction:" << query.lastError().text();
        return false;
    }
    query.next();
    if (query.value(0).toInt() == 0) {
        qDebug() << "Transaction avec l'ID" << id_transaction << "n'existe pas.";
        return false;
    }

    // Update the transaction record with TO_DATE for date
    query.prepare("UPDATE transaction SET montant = :montant, date_transaction = TO_DATE(:date_transaction, 'YYYY-MM-DD'), "
                  "type_transaction = :type_transaction, statut_transaction = :statut_transaction "
                  "WHERE id_transaction = :id_transaction");
    query.bindValue(":id_transaction", id_transaction);
    query.bindValue(":montant", montant);
    query.bindValue(":date_transaction", date_transaction.toString("yyyy-MM-dd"));
    query.bindValue(":type_transaction", type_transaction);
    query.bindValue(":statut_transaction", statut_transaction);

    bool success = query.exec();
    if (success) {
        qDebug() << "Transaction avec l'ID" << id_transaction << "modifiée avec succès.";
    } else {
        qDebug() << "Échec de la modification de la transaction avec l'ID" << id_transaction;
        qDebug() << "Erreur:" << query.lastError().text();
    }
    return success;
}

bool Transaction::supprimerTransaction(int id_transaction)
{
    QSqlQuery query;
    query.prepare("DELETE FROM transaction WHERE id_transaction = :id_transaction");
    query.bindValue(":id_transaction", id_transaction);

    bool success = query.exec();

    if (success) {
        if (query.numRowsAffected() > 0) {
            qDebug() << "Transaction supprimée avec succès avec l'ID:" << id_transaction;
            return true;
        } else {
            qDebug() << "Aucune transaction trouvée avec l'ID:" << id_transaction;
            return false;
        }
    } else {
        qDebug() << "Échec de la suppression de la transaction avec l'ID:" << id_transaction;
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Transaction::afficherTransactions()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Execute the query to fetch all transactions
    query.exec("SELECT * FROM transaction");



    // Set the query on the model to display in the view
    model->setQuery("SELECT * FROM transaction");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE DE TRANSACTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));

    return model;
}



QSqlQueryModel* Transaction::afficherTransactions(QString &sortColumn)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Set up the base query
    QString queryString = "SELECT * FROM transaction";

    // Append ORDER BY if a valid sort column is provided
    if (!sortColumn.isEmpty()) {
        queryString += " ORDER BY " + sortColumn;
    }

    model->setQuery(queryString);

    // Set headers as before
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE DE TRANSACTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));

    return model;
}

QSqlQueryModel* Transaction::rechercheById(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Prepare the SQL query
    query.prepare("SELECT * FROM transaction WHERE id_transaction = :id");
    query.bindValue(":id", id);

    // Execute the query and set it on the model if successful
    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE DE TRANSACTION"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError();
        delete model;
        model = nullptr;
    }

    return model;
}
QSqlQueryModel* Transaction::rechercheByMontant(int montant)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Prepare the SQL query
    query.prepare("SELECT * FROM transaction WHERE montant = :montant");
    query.bindValue(":montant", montant);

    // Execute the query and set it on the model if successful
    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE DE TRANSACTION"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError();
        delete model;
        model = nullptr;
    }

    return model;
}

QSqlQueryModel* Transaction::rechercheByDate(const QString& date)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Prepare the SQL query
    query.prepare("SELECT * FROM transaction WHERE TO_CHAR(date_transaction, 'YYYY-MM-DD') = :date");

    // Bind the date without time
    query.bindValue(":date", date);

    // Execute the query
    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("MONTANT"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE DE TRANSACTION"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError();
        delete model;
        model = nullptr;
    }

    return model;
}




QList<QDate> Transaction::getFutureTransactionDates()
{
    QList<QDate> futureDates;
    QSqlQuery query;

    // Use TO_DATE to ensure compatibility with Oracle's date format
    query.prepare("SELECT DISTINCT date_transaction FROM transaction WHERE date_transaction > TO_DATE(:currentDate, 'YYYY-MM-DD')");
    query.bindValue(":currentDate", QDate::currentDate().toString("yyyy-MM-dd"));

    if (query.exec()) {
        while (query.next()) {
            QDate date = query.value(0).toDate();
            futureDates.append(date);
        }
    } else {
        qDebug() << "Erreur lors de la récupération des dates de transaction futures : " << query.lastError();
    }

    return futureDates;
}



