#include "services.h"
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

// Constructeurs
Services::Services() : id(0), prix(0.0) {}
Services::Services(int id, const QString& nom, const QString& duree, float prix, const QString& disponibilite, const QString& etat)
    : nom(nom), disponibilite(disponibilite), etat(etat), duree(duree), id(id), prix(prix)
{}

// Getters
int Services::getId() const { return id; }
QString Services::getNom() const { return nom; }
QString Services::getDuree() const { return duree; }
float Services::getPrix() const { return prix; }
QString Services::getDisponibilite() const { return disponibilite; }
QString Services::getEtat() const { return etat; }

// Setters
void Services::setId(int id) { this->id = id; }
void Services::setNom(const QString& nom) { this->nom = nom; }
void Services::setDuree(const QString& duree) { this->duree = duree; }
void Services::setPrix(float prix) { this->prix = prix; }
void Services::setDisponibilite(const QString& disponibilite) { this->disponibilite = disponibilite; }
void Services::setEtat(const QString& etat) { this->etat = etat; }

// Ajouter un service dans la base de données
bool Services::existeDeja(int id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM services WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}
bool Services::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO SERVICES (ID, NOM, DUREE,ETAT, DISPONIBILITE, PRIX) "
                  "VALUES (:id, :nom, :duree, :etat, :disponibilite, :prix)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":duree", duree);
    query.bindValue(":prix", prix);
    query.bindValue(":disponibilite", disponibilite);
    query.bindValue(":etat", etat);


    return query.exec();
}

// Afficher tous les services
QSqlQueryModel* Services::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Services");
    return model;
}


Services Services::getById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Services WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Si l'ID est trouvé, on récupère les données du service
        int serviceId = query.value("id").toInt();
        QString nom = query.value("nom").toString();
        QString duree = query.value("duree").toString();
        double prix = query.value("prix").toDouble();
        QString disponibilite = query.value("disponibilite").toString();
        QString etat = query.value("etat").toString();

        // Retourne un objet Services avec les données récupérées
        return Services(serviceId, nom, duree, prix, disponibilite, etat);
    }

    // Si aucun service n'est trouvé, retourner un objet invalide
    return Services();  // Assurez-vous que le constructeur par défaut crée un service invalide
}

// Modifier un service
bool Services::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE SERVICES SET NOM = :nom, DUREE = :duree, PRIX = :prix, "
                  "DISPONIBILITE= :disponibilite, ETAT = :etat WHERE ID= :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":duree", duree);
    query.bindValue(":prix", prix);
    query.bindValue(":disponibilite", disponibilite);
    query.bindValue(":etat", etat);

    return query.exec();
}

// Supprimer un service
bool Services::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM SERVICES WHERE ID= :id");
    query.bindValue(":id", id);

    return query.exec();
}
QSqlQueryModel* Services::rechercher(const QString& critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Préparer la requête SQL avec un critère de recherche dynamique
    query.prepare("SELECT * FROM services WHERE nom LIKE :critere OR id = :id_critere OR disponibilite LIKE : disponible");
    query.bindValue(":critere", "%" + critere + "%");
    query.bindValue(":id_critere", critere.toInt());
    query.bindValue(":disponible", "%disponible%");

    // Exécution de la requête et vérification des erreurs
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de recherche:" << query.lastError().text();
    } else {
        // Si la requête réussit, on la passe au modèle
        model->setQuery(query);
    }

    // Vérification des résultats
    if (model->rowCount() == 0) {
        qDebug() << "Aucun résultat trouvé pour le critère de recherche:" << critere;
    } else {
        qDebug() << "Résultats trouvés pour le critère de recherche:" << critere;
    }

    return model;
}
QSqlQueryModel* Services::trierParCritere(const QString& critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Construire la requête SQL en fonction du critère de tri
    QString queryString = QString("SELECT * FROM services ORDER BY %1 ASC").arg(critere);
    query.prepare(queryString);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de tri:" << query.lastError().text();
    } else {
        model->setQuery(query);
    }

    return model;
}

