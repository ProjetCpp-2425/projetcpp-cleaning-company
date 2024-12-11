#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QString>

class Statistique {
public:
    Statistique();

    // Function to export statistics to a PDF file
    void exportToPdf(const QString &fileName);

private:
    // Function to generate HTML content for the PDF export
    QString generateHtmlContent();

    // Functions to generate specific parts of the statistics HTML
    QString getPaymentStatistics() ;
    QString getMonthlyTransactionStatistics();
    QString getAdditionalStatistics() ;
};

#endif // STATISTIQUE_H
