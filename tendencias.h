#ifndef TENDENCIAS_H
#define TENDENCIAS_H

#include <QMainWindow>
#include "qcustomplot.h"



namespace Ui {
class Tendencias;
}

class Tendencias : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tendencias(QWidget *parent = 0);
    ~Tendencias();

    void setupSimpleDemo(QCustomPlot *customPlot);
    void addplot(const QVector<double>& xVoltaje,const QVector<double>& yAmplitude);


    void PlotData(const QVector<double>& yData, int graph);
private slots:

    void titleDoubleClick(QMouseEvent *event, QCPPlotTitle *title);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void removeSelectedGraph();
    void removeAllGraphs();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable);

private:
    Ui::Tendencias *ui;
    void initActionsConnections();




};

#endif // TENDENCIAS_H
