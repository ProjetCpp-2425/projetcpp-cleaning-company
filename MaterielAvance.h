#ifndef MATERIELAVANCE_H
#define MATERIELAVANCE_H

#include <QString>
#include <QDate>

class MaterielAvance {
public:
    // Constructeur
    MaterielAvance(int id, const QString& qualite, int quantite, const QString& type,
                   double prixAchat, double prixVente, const QDate& dateAchat, const QDate& dateVente);

    // Méthodes
    int getQuantite() const;
    QString getType() const;
    double calculerProfitTotal() const;

private:
    int idMateriel;
    QString qualite;
    int quantite;
    QString type;
    double prixAchat;
    double prixVente;
    QDate dateAchat;
    QDate dateVente;
};

#endif // MATERIELAVANCE_H
