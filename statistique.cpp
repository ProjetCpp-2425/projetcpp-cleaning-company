#include "statistique.h"
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Statistique::Statistique() {}

void Statistique::exportToPdf(const QString &fileName) {
    if (fileName.isEmpty()) {
        return;
    }

    // Create a QTextDocument to construct the PDF content
    QTextDocument doc;
    doc.setHtml(generateHtmlContent());

    // Configure the printer for PDF output
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));

    // Print the document to PDF
    doc.print(&printer);

    // Display a message box to confirm the export
    QMessageBox::information(nullptr, "Exportation Réussie", "Les données statistiques ont été exportées en PDF.");
}

QString Statistique::generateHtmlContent() {
    QString htmlContent;

    // Title of the document
    htmlContent += "<h1 style='text-align: center;'>Données Statistiques des Transactions</h1>";
    htmlContent += "<hr/>";

    // Dynamic Payment Statistics Table
    htmlContent += "<h2>Statistiques des Transactions par Type</h2>";
    htmlContent += getPaymentStatistics();
    htmlContent += "<hr/>";

    // Dynamic Monthly Transaction Statistics Table
    htmlContent += "<h2>Nombre de Transactions par Mois</h2>";
    htmlContent += getMonthlyTransactionStatistics();
    htmlContent += "<hr/>";

    // Additional Data
    htmlContent += "<h2>Statistiques Contextuelles Supplémentaires</h2>";
    htmlContent += getAdditionalStatistics();

    return htmlContent;
}

QString Statistique::getPaymentStatistics() {
    QString html;
    QSqlQuery query;
    query.prepare("SELECT type_transaction, COUNT(*) FROM transaction GROUP BY type_transaction");

    if (query.exec()) {
        html += "<table border='1' cellpadding='5' cellspacing='0' width='100%'>"
                "<tr><th>Type de Transaction</th><th>Nombre</th></tr>";
        while (query.next()) {
            QString typeTransaction = query.value(0).toString();
            int count = query.value(1).toInt();
            html += QString("<tr><td>%1</td><td>%2</td></tr>").arg(typeTransaction).arg(count);
        }
        html += "</table>";
    } else {
        qDebug() << "Error fetching payment statistics";
    }
    return html;
}

QString Statistique::getMonthlyTransactionStatistics() {
    QString html;
    QSqlQuery query;
    query.prepare("SELECT strftime('%m', date_transaction) AS month, COUNT(*) FROM transaction GROUP BY month");

    if (query.exec()) {
        html += "<table border='1' cellpadding='5' cellspacing='0' width='100%'>"
                "<tr><th>Mois</th><th>Nombre de Transactions</th></tr>";
        while (query.next()) {
            QString month = query.value(0).toString();
            int count = query.value(1).toInt();
            html += QString("<tr><td>%1</td><td>%2</td></tr>").arg(month).arg(count);
        }
        html += "</table>";
    } else {
        qDebug() << "Error fetching monthly transaction statistics";
    }
    return html;
}

QString Statistique::getAdditionalStatistics() {
    QString html;
    QSqlQuery query;

    // Average Transaction Amount
    query.prepare("SELECT AVG(montant) FROM transaction");
    if (query.exec() && query.next()) {
        float avgAmount = query.value(0).toFloat();
        html += "<tr><td>Montant Moyen des Transactions</td><td>" + QString::number(avgAmount) + "</td></tr>";
    } else {
        qDebug() << "Error fetching average transaction amount";
    }

    // Most Common Transaction Status
    query.prepare("SELECT statut_transaction, COUNT(*) AS count FROM transaction GROUP BY statut_transaction ORDER BY count DESC LIMIT 1");
    if (query.exec() && query.next()) {
        QString commonStatus = query.value(0).toString();
        html += "<tr><td>Statut de Transaction le Plus Commun</td><td>" + commonStatus + "</td></tr>";
    } else {
        qDebug() << "Error fetching most common transaction status";
    }

    // Additional data could be added here

    html = "<table border='1' cellpadding='5' cellspacing='0' width='100%'>"
           "<tr><th>Catégorie</th><th>Valeur</th></tr>" + html + "</table>";

    return html;
}
