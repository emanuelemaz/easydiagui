#include "diagview.h"
#include "ui_diagview.h"
#include "easydiag.h"

#include <QMessageBox>

#include <QVector>

DiagView::DiagView(Context &ctx, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagView)
{
    ui->setupUi(this);
    std::pair<std::vector<double>,std::vector<double>> xyH = ctx.getHpair();
    std::pair<std::vector<double>,std::vector<double>> xyT = ctx.getTpair();
    std::pair<std::vector<double>,std::vector<double>> xyM = ctx.getMpair();
    std::pair<std::vector<double>,std::vector<double>> beamPoints = std::make_pair(std::vector<double>{0,ctx.beam.length}, std::vector<double>{0,0});

    ui->diagHPlot->addGraph();
    ui->diagHPlot->graph(0)->setData(QVector<double>(beamPoints.first.begin(), beamPoints.first.end()), QVector<double>(beamPoints.second.begin(), beamPoints.second.end()));
    ui->diagHPlot->addGraph();
    ui->diagHPlot->graph(1)->setData(QVector<double>(xyH.first.begin(),xyH.first.end()), QVector<double>(xyH.second.begin(),xyH.second.end()));
    ui->diagHPlot->graph(0)->setPen(QPen(QColor(102,161,130), 2));
    ui->diagHPlot->replot();
    ui->diagHPlot->rescaleAxes(true);
    ui->diagHPlot->xAxis->setLabel("Beam");
    ui->diagHPlot->yAxis->setLabel("Shear force");
    ui->diagHPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->diagTPlot->addGraph();
    ui->diagTPlot->graph(0)->setData(QVector<double>(beamPoints.first.begin(), beamPoints.first.end()), QVector<double>(beamPoints.second.begin(), beamPoints.second.end()));
    ui->diagTPlot->addGraph();
    ui->diagTPlot->graph(1)->setData(QVector<double>(xyT.first.begin(),xyT.first.end()), QVector<double>(xyT.second.begin(),xyT.second.end()));
    ui->diagTPlot->graph(0)->setPen(QPen(QColor(102,161,130), 2));
    ui->diagTPlot->replot();
    ui->diagTPlot->rescaleAxes(true);
    ui->diagTPlot->xAxis->setLabel("Beam");
    ui->diagTPlot->yAxis->setLabel("Shear force");
    ui->diagTPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->diagMPlot->addGraph();
    ui->diagMPlot->graph(0)->setData(QVector<double>(beamPoints.first.begin(), beamPoints.first.end()), QVector<double>(beamPoints.second.begin(), beamPoints.second.end()));
    ui->diagMPlot->addGraph();
    ui->diagMPlot->graph(1)->setData(QVector<double>(xyM.first.begin(),xyM.first.end()), QVector<double>(xyM.second.begin(),xyM.second.end()));
    ui->diagMPlot->graph(0)->setPen(QPen(QColor(102,161,130), 2));
    ui->diagMPlot->replot();
    ui->diagMPlot->rescaleAxes(true);
    ui->diagMPlot->xAxis->setLabel("Beam");
    ui->diagMPlot->yAxis->setLabel("Shear force");
    ui->diagMPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

DiagView::~DiagView()
{
    delete ui;
}
