#include "MaterielAvance.h"

MaterielAvance::MaterielAvance(int id, const QString& qualite, int quantite, const QString& type,
                                 double prixAchat, double prixVente, const QDate& dateAchat, const QDate& dateVente)
    : idMateriel(id), qualite(qualite), quantite(quantite), type(type),
      prixAchat(prixAchat), prixVente(prixVente), dateAchat(dateAchat), dateVente(dateVente) {}

int MaterielAvance::getQuantite() const {
    return quantite;
}

QString MaterielAvance::getType() const {
    return type;
}

double MaterielAvance::calculerProfitTotal() const {
    return (prixVente - prixAchat) * quantite;
}
