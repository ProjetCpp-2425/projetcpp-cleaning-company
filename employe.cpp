#include "employe.h"
#include <QSqlQueryModel>
#include <QSqlError>


// Constructeurs
Employe::Employe() : id(0), salaire(0.0) {}
Employe::Employe(int id, const QString& nom, const QString& prenom,  float salaire, const QString& poste,const QString& date_embauche)
    : id(id),nom(nom), prenom(prenom), salaire(salaire),poste (poste) ,date_embauche(date_embauche)
{}

// Getters
int Employe::getId() const { return id; }
QString Employe::getNom() const { return nom; }
QString Employe::getDate_embauche() const { return date_embauche; }
float Employe::getSalaire() const { return salaire; }
QString Employe::getPrenom() const { return prenom; }
QString Employe::getPoste() const { return poste; }

// Setters
void Employe::setId(int id) { this->id = id; }
void Employe::setNom(const QString& nom) { this->nom = nom; }
void Employe::setDate_embauche(const QString& date_embauche) { this->date_embauche = date_embauche; }
void Employe::setSalaire(float salaire) { this->salaire = salaire; }
void Employe::setPrenom(const QString& prenom) { this->prenom = prenom; }
void Employe::setPoste(const QString& poste) { this->poste = poste; }

// Ajouter un Employe dans la base de données
bool Employe::existeDeja(int id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Employe WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}
bool Employe::ajouter() {
    QString idt = QString::number(id);
    QSqlQuery query;

    // Correction : Fermeture de la parenthèse après les colonnes
    query.prepare("INSERT INTO EMPLOYES (ID, NOM, PRENOM, SALAIRE, POSTE, DATE_EMBAUCHE) "
                  "VALUES (:id, :nom, :prenom, :salaire, :poste, TO_DATE(:date_embauche, 'YYYY-MM-DD'))");

    // Liaison des valeurs
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":salaire", salaire);
    query.bindValue(":poste", poste);
    query.bindValue(":date_embauche", date_embauche);

    // Exécution de la requête
    return query.exec();
}


// Afficher tous les Employe
QSqlQueryModel* Employe::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employes");
    return model;
}


Employe Employe::getById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Employes WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Si l'ID est trouvé, on récupère les données de l'employe
        int id = query.value("id").toInt();
        QString nom = query.value("nom").toString();
        QString date_embauche = query.value("date_embauche").toString();
        double salaire = query.value("salaire").toDouble();
        QString prenom = query.value("prenom").toString();
        QString poste = query.value("poste").toString();

        // Retourne un objet Employe avec les données récupérées
        return Employe(id, nom, prenom, salaire, poste,date_embauche);
    }

    // Si aucun Employe n'est trouvé, retourner un objet invalide
    return Employe();  // Assurez-vous que le constructeur par défaut crée un service invalide
}

// Modifier un Employe
bool Employe::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYES SET NOM = :nom, PRENOM= :prenom, SALAIRE = :salaire,"
                  "POSTE = :poste ,DATE_EMBAUCHE = TO_DATE:(date_embauche, 'YYYY-MM-DD') WHERE ID= :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":salaire", salaire);
    query.bindValue(":poste", poste);
    query.bindValue(":date_embauche", date_embauche);
    return query.exec();
}

// Supprimer un Employe
bool Employe::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID= :id");
    query.bindValue(":id", id);

    return query.exec();
}
QSqlQueryModel* Employe::rechercher(const QString& critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Préparer la requête SQL avec un critère de recherche dynamique
    query.prepare("SELECT * FROM Employes WHERE nom LIKE :critere OR id = :id_critere");
    query.bindValue(":critere", "%" + critere + "%");
    query.bindValue(":id_critere", critere.toInt());

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
QSqlQueryModel* Employe::trierParCritere(const QString& critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Construire la requête SQL en fonction du critère de tri
    QString queryString = QString("SELECT * FROM Employes ORDER BY %1 ASC").arg(critere);
    query.prepare(queryString);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de tri:" << query.lastError().text();
    } else {
        model->setQuery(query);
    }

    return model;
}
