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

    ui->doubleSpinBox->setDecimals(4);
    ui->doubleSpinBox->setMaximum(ctx.beam.length);
    ui->doubleSpinBox->setMinimum(0);

    lCtx = ctx;

    std::pair<std::vector<double>,std::vector<double>> xyH = ctx.getHpair();
    std::pair<std::vector<double>,std::vector<double>> xyT = ctx.getTpair();
    std::pair<std::vector<double>,std::vector<double>> xyM = ctx.getMpair();

    yHmin = *std::min_element(xyH.second.begin(), xyH.second.end());
    yHmax = *std::max_element(xyH.second.begin(), xyH.second.end());
    yTmin = *std::min_element(xyT.second.begin(), xyT.second.end());
    yTmax = *std::max_element(xyT.second.begin(), xyT.second.end());
    yMmin = *std::min_element(xyM.second.begin(), xyM.second.end());
    yMmax = *std::max_element(xyM.second.begin(), xyM.second.end());

    std::pair<std::vector<double>,std::vector<double>> beamPoints = std::make_pair(std::vector<double>{0,ctx.beam.length}, std::vector<double>{0,0});

    ui->diagHPlot->addGraph();
    ui->diagHPlot->graph(0)->setData(QVector<double>(beamPoints.first.begin(), beamPoints.first.end()), QVector<double>(beamPoints.second.begin(), beamPoints.second.end()));
    ui->diagHPlot->addGraph();
    ui->diagHPlot->graph(1)->setData(QVector<double>(xyH.first.begin(),xyH.first.end()), QVector<double>(xyH.second.begin(),xyH.second.end()));
    ui->diagHPlot->graph(0)->setPen(QPen(QColor(102,161,130), 2));
    ui->diagHPlot->replot();
    ui->diagTPlot->rescaleAxes(true);
    ui->diagHPlot->xAxis->setLabel("Beam");
    ui->diagHPlot->yAxis->setLabel("Axial force");
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
    ui->diagMPlot->yAxis->setLabel("Bending moment");
    ui->diagMPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

DiagView::~DiagView()
{
    delete ui;
}

void DiagView::on_doubleSpinBox_valueChanged(double x)
{
    ui->axialIn->setText(QString::fromStdString(std::to_string(lCtx.pointH(x))));
    ui->shearIn->setText(QString::fromStdString(std::to_string(lCtx.pointV(x))));
    ui->momentIn->setText(QString::fromStdString(std::to_string(lCtx.pointM(x)*(-1))));
}


void DiagView::on_saveH_clicked()
{
    ui->diagHPlot->xAxis->setRange(-lCtx.beam.length*0.2, lCtx.beam.length*1.2);
    ui->diagHPlot->yAxis->setRange(1.2 * yHmin, 1.2 * yHmax );
    ui->diagHPlot->savePdf("axial.pdf", 600, 600, QCP::epNoCosmetic);
}

void DiagView::on_saveT_clicked()
{
    ui->diagTPlot->xAxis->setRange(-lCtx.beam.length*0.2, lCtx.beam.length*1.2);
    ui->diagTPlot->yAxis->setRange(1.2 * yTmin, 1.2 * yTmax );
    ui->diagTPlot->savePdf("shear.pdf", 600, 600, QCP::epNoCosmetic);

}

void DiagView::on_saveM_clicked()
{
    ui->diagMPlot->xAxis->setRange(-lCtx.beam.length*0.2, lCtx.beam.length*1.2);
    ui->diagMPlot->yAxis->setRange(1.2 * yMmin, 1.2 * yMmax );
    ui->diagMPlot->savePdf("moment.pdf", 600, 600, QCP::epNoCosmetic);
}

