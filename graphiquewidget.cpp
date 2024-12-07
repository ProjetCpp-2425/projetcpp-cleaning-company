#include "graphiquewidget.h"

GraphiqueWidget::GraphiqueWidget(QWidget *parent)
    : QWidget(parent), servicesDisponibles(0), servicesIndisponibles(0) {}

void GraphiqueWidget::setStatistiques(int disponibles, int indisponibles) {
    servicesDisponibles = disponibles;
    servicesIndisponibles = indisponibles;
    update(); // Demande un redessin
}

void GraphiqueWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int total = servicesDisponibles + servicesIndisponibles;
    if (total == 0) return; // Rien à dessiner si pas de données

    // Calcul des angles pour le camembert
    qreal angleDisponible = 360.0 * (servicesDisponibles / static_cast<qreal>(total));
    qreal angleIndisponible = 360.0 - angleDisponible;

    // Zone de dessin
    int side = qMin(width(), height()) * 0.8;
    QRect rect((width() - side) / 2, (height() - side) / 2, side, side);

    // Dessiner le camembert
    painter.setBrush(Qt::green);
    painter.drawPie(rect, 0, angleDisponible * 16);
    painter.setBrush(Qt::red);
    painter.drawPie(rect, angleDisponible * 16, angleIndisponible * 16);

    // Légendes
    painter.setPen(Qt::black);
    painter.drawText(10, 20, QString("Disponible: %1").arg(servicesDisponibles));
    painter.setBrush(Qt::green);
    painter.drawRect(10, 10, 10, 10);

    painter.drawText(30, 50, QString("Indisponible: %1").arg(servicesIndisponibles));
    painter.setBrush(Qt::red);
    painter.drawRect(10, 40, 10, 10);
}
