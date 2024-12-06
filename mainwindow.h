#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <Client.h>
#include<Arduino.h>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_modifier_2_clicked();

    void on_modifier_4_clicked();

    void on_ajouter_2_clicked();

    void on_supprimer_2_clicked();

    void on_comboBoxTri_currentIndexChanged(int index);

    void on_rechercherParNom_clicked();

    void on_exportToPDF_clicked();


    void on_stat_methods_clicked();


void addImagesToTableView(QTableView* tableView, QSqlQueryModel* model, int imageColumnIndex);



void on_btnUploadPhoto_clicked();
void afficherPhoto(const QByteArray& imageBytes) ;
void on_comboBox_currentIndexChanged(int index);

void on_btnRecherche_clicked();

void on_comboBoxCritere_currentIndexChanged(int index);

void on_criterComboBox_currentIndexChanged(int index);

void on_rechercheButton_clicked();

void on_criterComboBox_currentTextChanged(const QString &arg1);

void on_pushButtonRecherche_clicked();

void on_lineEditRecherche_textChanged(const QString &arg1);
void update_label();
private:
Client currentClient;
QTimer *alertTimer;
    Ui::MainWindow *ui;
    Client Etmp;
    QByteArray dataBuffer;
    Arduino A;

signals:
    void setLocationMarking(QVariant,QVariant);
    void setCenterPosition(QVariant,QVariant);
};
#endif // MAINWINDOW_H
