// materiel.cpp
#include "materiel.h"
#include <QDebug>
#include <QSqlError>

Materiel::Materiel(int id_materiel, QString qualite, int quantite, QString type,
                   float prix_achat, float prix_vente, QDate date_achat, QDate date_vente)
{
    this->id_materiel = id_materiel;
    this->qualite = qualite;
    this->quantite = quantite;
    this->type = type;
    this->prix_achat = prix_achat;
    this->prix_vente = prix_vente;
    this->date_achat = date_achat;
    this->date_vente = date_vente;
}




bool Materiel::ajouter()
{
    QSqlQuery query;

    // Préparation de la requête SQL
    query.prepare("INSERT INTO materiels (id_materiel, qualite, quantite, type, date_achat, prix_achat, date_vente, prix_vente) "
                  "VALUES (:id_materiel, :qualite, :quantite, :type, :date_achat, :prix_achat, :date_vente, :prix_vente)");

    // Associer les valeurs des champs aux variables de la requête
    query.bindValue(":id_materiel", id_materiel);
    query.bindValue(":qualite", qualite);
    query.bindValue(":quantite", quantite);
    query.bindValue(":type", type);
    query.bindValue(":date_achat", date_achat);
    query.bindValue(":prix_achat", prix_achat);
    query.bindValue(":date_vente", date_vente);
    query.bindValue(":prix_vente", prix_vente);

    // Exécuter la requête et retourner le succès ou l'échec
    return query.exec();
}
bool Materiel::modifier(int id_materiel, QString qualite, int quantite,
                        QString type, float prix_achat, float prix_vente,
                        QDate date_achat, QDate date_vente)
{
    QSqlQuery query;

    // Préparation de la requête SQL
    query.prepare("UPDATE materiels SET qualite = :qualite, quantite = :quantite, "
                  "type = :type, prix_achat = :prix_achat, prix_vente = :prix_vente, "
                  "date_achat = :date_achat, date_vente = :date_vente "
                  "WHERE id_materiel = :id_materiel");

    // Associer les valeurs des champs aux variables de la requête
    query.bindValue(":id_materiel", id_materiel);
    query.bindValue(":qualite", qualite);
    query.bindValue(":quantite", quantite);
    query.bindValue(":type", type);
    query.bindValue(":prix_achat", prix_achat);
    query.bindValue(":prix_vente", prix_vente);
    query.bindValue(":date_achat", date_achat);
    query.bindValue(":date_vente", date_vente);

    // Exécuter la requête et retourner le succès ou l'échec
    bool success = query.exec();

    if (success) {
        qDebug() << "Materiel avec l'ID" << id_materiel << "modifié avec succès.";
    } else {
        qDebug() << "Échec de la modification du matériel avec l'ID" << id_materiel;
        qDebug() << "Erreur :" << query.lastError().text();
    }

    return success;
}


bool Materiel::supprimer(int id_materiel)
{
    QSqlQuery query;

    // Préparer la requête SQL pour supprimer un enregistrement par ID
    query.prepare("DELETE FROM materiels WHERE id_materiel = :id_materiel");
    query.bindValue(":id_materiel", id_materiel);

    bool success = query.exec();

    if (success) {
        if (query.numRowsAffected() > 0) {
            qDebug() << "Suppression réussie pour le matériel avec ID :" << id_materiel;
            return true;
        } else {
            qDebug() << "Aucun matériel trouvé avec l'ID :" << id_materiel;
            return false;
        }
    } else {
        qDebug() << "Échec de la suppression du matériel avec l'ID :" << id_materiel;
        qDebug() << "Erreur SQL :" << query.lastError().text();
        return false;
    }
}
QSqlQueryModel* Materiel::verifierStockFaible(int seuil)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT id_materiel, qualite, type, quantite "
                  "FROM materiels WHERE quantite <= :seuil");
    query.bindValue(":seuil", seuil);

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Erreur lors de la vérification des stocks faibles :"
                 << query.lastError().text();
    }

    return model;
}
