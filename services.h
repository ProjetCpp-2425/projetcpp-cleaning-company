#ifndef SERVICES_H
#define SERVICES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Services
{ QString nom , disponibilite , etat ,duree  ;
    int id  ;
    float  prix;

public:
    // Constructeurs
    Services();
    Services(int id, const QString& nom, const QString& duree, float prix, const QString& disponibilite, const QString& etat);

    // Getters
    int getId() const;
    QString getNom() const;
    QString getDuree() const;
    float getPrix() const;
    QString getDisponibilite() const;
    QString getEtat() const;

    // Setters
    void setId(int id);
    void setNom(const QString& nom);
    void setDuree(const QString& duree);
    void setPrix(float prix);
    void setDisponibilite(const QString& disponibilite);
    void setEtat(const QString& etat);

    // Méthodes CRUD
    bool existeDeja(int id);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(int id);
    bool supprimer(int id);
static Services getById(int id);
QSqlQueryModel* rechercher(const QString& critere);
QSqlQueryModel* trierParCritere(const QString& critere);

};
#endif // SERVICES_H
