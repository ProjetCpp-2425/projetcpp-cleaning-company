#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Transaction
{
    int id_transaction;
    int montant;
    QDate date_transaction;
    QString type_transaction;
    QString statut_transaction;

public:
    Transaction() {}
    Transaction(int, float, QDate, QString, QString);

    int getIdTransaction() { return id_transaction; }
    float getMontant() { return montant; }
    QDate getDateTransaction() { return date_transaction; }
    QString getTypeTransaction() { return type_transaction; }
    QString getStatutTransaction() { return statut_transaction; }

    void setIdTransaction(int id) { id_transaction = id; }
    void setMontant(float m) { montant = m; }
    void setDateTransaction(QDate date) { date_transaction = date; }
    void setTypeTransaction(QString t) { type_transaction = t; }
    void setStatutTransaction(QString s) { statut_transaction = s; }

    bool ajouterTransaction();
    bool modifierTransaction(int id_transaction, float montant, QDate date_transaction, QString type_transaction, QString statut_transaction);
    bool supprimerTransaction(int id_transaction);

    QSqlQueryModel* afficherTransactions();
    QSqlQueryModel* afficherTransactions(QString &sortColumn);

    // Declaration of rechercheById function
    QSqlQueryModel* rechercheById(int id);
    QSqlQueryModel* rechercheByMontant(int montant);
    QSqlQueryModel* rechercheByDate(const QString& date);

    QList<QDate> getFutureTransactionDates();
};

#endif // TRANSACTION_H
