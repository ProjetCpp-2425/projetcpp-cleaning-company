#ifndef GRAPHIQUEWIDGET_H
#define GRAPHIQUEWIDGET_H

#include <QWidget>
#include <QPainter>

class GraphiqueWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphiqueWidget(QWidget *parent = nullptr);

    void setStatistiques(int disponibles, int indisponibles);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int servicesDisponibles;
    int servicesIndisponibles;
};

#endif // GRAPHIQUEWIDGET_H
