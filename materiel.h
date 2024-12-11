// materiel.h
#ifndef MATERIEL_H
#define MATERIEL_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QString>


class Materiel
{
    int id_materiel;
    QString qualite;
    int quantite;
    QString type;
    float prix_achat;
    float prix_vente;
    QDate date_achat;
    QDate date_vente;


public:
    Materiel() {}
    Materiel(int id, QString qualite, int quantite, QString type,
             float prix_achat, float prix_vente,
             QDate date_achat, QDate date_vente);

    // Getters
    int getIdMateriel() { return id_materiel; }
    QString getQualite() { return qualite; }
    int getQuantite() { return quantite; }
    QString getType() { return type; }
    float getPrixAchat() { return prix_achat; }
    float getPrixVente() { return prix_vente; }
    QDate getDateAchat() { return date_achat; }
    QDate getDateVente() { return date_vente; }

    // Setters
    void setIdMateriel(int id) { id_materiel = id; }
    void setQualite(QString q) { qualite = q; }
    void setQuantite(int q) { quantite = q; }
    void setType(QString t) { type = t; }
    void setPrixAchat(float p) { prix_achat = p; }
    void setPrixVente(float p) { prix_vente = p; }
    void setDateAchat(QDate d) { date_achat = d; }
    void setDateVente(QDate d) { date_vente = d; }

    bool ajouter();
    bool modifier(int id_materiel, QString qualite, int quantite,
                 QString type, float prix_achat, float prix_vente,
                 QDate date_achat, QDate date_vente);
    bool supprimer(int id_materiel);
    QSqlQueryModel* afficher();

     QSqlQueryModel* verifierStockFaible(int seuil);
};

#endif // MATERIEL_H
