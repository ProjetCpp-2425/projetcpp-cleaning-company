#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QDate>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>
#include <QPdfWriter>
#include <QTextDocument>
#include <QTextCursor>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QPdfWriter>
#include <QTextDocument>
#include <QTextCursor>
#include <QStandardPaths>
#include <QObject>
#include <QTableView>  // Inclure QTableView
#include <QSqlQueryModel>  // Si vous utilisez QSqlQueryModel dans votre code
#include <QPixmap>  // Si vous chargez des images avec QPixmap
#include <QByteArray>  // Si vous manipulez des données binaires (comme les images)



class Client
{
private:
    int  CIN_Client;
    QString NOM_Client;
    QString PRENOM_Client;
    QDate DATES_Client;
    QString METHODEP_Client;
    QString TYPE;
    QString ADRESSE_Client;
    QString NUMC_Client;
    QByteArray image_data;
    QString image_name;
public:









    Client(){};
    Client(int, QString, QString, QDate, QString,QString,QString,QString,QByteArray,QString);

    int getCIN_client(){return CIN_Client;}
    QString getNOM_client(){return NOM_Client;}
    QString getPRENOM_client(){return PRENOM_Client;}
    QDate getDATES_Client(){return DATES_Client;}
    QString getMETHODEP_Client(){return METHODEP_Client;}
    QString getTYPE(){return TYPE;}
    QString getADRESSE_Client(){return ADRESSE_Client;}
    QString getNUMC_Client(){return NUMC_Client;}


    void set_CIN_Client(int i){this->CIN_Client=i;}
    void set_NOM_Client( QString n){NOM_Client=n;}
    void set_PRENOM_Client( QString p){PRENOM_Client=p;}
    void set_DATES_client( QDate d){this->DATES_Client=d;}
    void set_METHODEP_client( QString m){METHODEP_Client=m;}
    void set_TYPE( QString t){TYPE=t;}
    void set_ADRESSE_client( QString a){ADRESSE_Client=a;}
    void set_NUMC_Client( QString num){NUMC_Client=num;}
    Client getclientByid(int id);
    bool checkIfidExists(int id);
QSqlQueryModel* getMethodAndServiceStatistics();
void exportClientsByServiceTypeToPDF(const QString& filePath, const QString& serviceType);

        bool ajouter();
        QSqlQueryModel* afficher();
        bool supprimer(int);
        bool modifier(int, QString, QString, QDate,QString,QString,QString,QString);
        QSqlQueryModel* trierParNom();
        QSqlQueryModel* rechercherParNom(const QString &nomRecherche);
        void exportToPDF(const QString& filePath, QAbstractItemModel* model);
      QSqlQueryModel*  getMethodStatistics();
 void displayImagesInTableView(QTableView *tableView);
 QByteArray convertPhotoToByteArray(const QString & filePath) ;
 QSqlQueryModel* trier(const QString& critere);
 QSqlQueryModel* rechercherParCritere(const QString& critere, const QString& valeur);

 QSqlQueryModel* rechercherParCritereEtTexte(const QString& critere, const QString& texte) ;
 QByteArray processImageWithDialog(QString& selectedImagePath) ;

 };
#endif // CLIENT_H
