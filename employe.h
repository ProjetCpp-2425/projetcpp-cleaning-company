#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employe
{ QString nom , prenom , poste ,date_embauche  ;
    int id  ;
    float  salaire;

public:
    // Constructeurs
    Employe();
    Employe(int id, const QString& nom,const QString& prenom,  float salaire, const QString& poste, const QString& date_embauche);

    // Getters
    int getId() const;
    QString getNom() const;
    QString getDate_embauche() const;
    float getSalaire() const;
    QString getPrenom() const;
    QString getPoste() const;

    // Setters
    void setId(int id);
    void setNom(const QString& nom);
    void setDate_embauche(const QString& date_embauche);
    void setSalaire(float salaire);
    void setPrenom(const QString& prenom);
    void setPoste(const QString& poste);

    // Méthodes CRUD
    bool existeDeja(int id);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(int id);
    bool supprimer(int id);
static Employe getById(int id);
QSqlQueryModel* rechercher(const QString& critere);
QSqlQueryModel* trierParCritere(const QString& critere);
};
#endif // SERVICES_H
