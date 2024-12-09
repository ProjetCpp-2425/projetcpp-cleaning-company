#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "transaction.h"
#include <QMainWindow>
#include "arduino.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void clearInputFields();

private slots:
    void on_exportButton_clicked();
    void on_exportStatistique_clicked();
    void on_rechercher_clicked();
    void highlightFutureTransactionDates();
    void onComboBoxSelectionChanged(int index);
    void onSearchCriterionChanged(int index);
    void populateClientComboBox();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();
    void update_label();
    bool handleTransaction(int receivedCode);

private:
    Ui::MainWindow *ui;
    Transaction transaction;
    Arduino A;
     QString data;

};

#endif // MAINWINDOW_H

