#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "pointloaddialog.h"
#include "pointloaddialog.h"
#include "pointmomentdialog.h"
#include "diagview.h"

#include <QMessageBox>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->beamSpinBox->setDecimals(4);
    ui->beamSpinBox->setMinimum(std::numeric_limits<double>::max()*(-1));
    ui->beamSpinBox->setMaximum(std::numeric_limits<double>::max());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_beamBtn_clicked()
{
    if (ui->beamSpinBox->value() == 0) {
        QMessageBox::warning(this, "Warning", "The length of the beam must be greater than 0.", QMessageBox::Ok);
    } else {
        b.length = ui->beamSpinBox->value();
        ui->pointLoadBtn->setEnabled(true);
        ui->distributedLoadBtn->setEnabled(true);
        ui->pointMomentBtn->setEnabled(true);
        ui->diagBtn->setEnabled(true);
    }
}


void MainWindow::on_pointLoadBtn_clicked()
{
    pldialog = new PointLoadDialog();
    int result = pldialog->exec();
    if (result == QDialog::Accepted) {
        ui->pointLoadsTbl->setRowCount(0);
        for (std::pair<PointLoad,bool> &f : pldialog->forces) {
            if (f.second == true) {
                verticalForces.push_back(f.first);
            } else {
                horizontalForces.push_back(f.first);
            }
        }
        for (std::vector<PointLoad>::size_type i = 0; i < verticalForces.size(); i++) {
            ui->pointLoadsTbl->insertRow(ui->pointLoadsTbl->rowCount());
            QTableWidgetItem *valueItem = new QTableWidgetItem();
            valueItem->setData(Qt::EditRole, (verticalForces[i].value));
            QTableWidgetItem *distanceItem = new QTableWidgetItem();
            distanceItem->setData(Qt::EditRole, (verticalForces[i].distance));
            QTableWidgetItem *directionItem = new QTableWidgetItem();
            directionItem->setText("Vertical");
            ui->pointLoadsTbl->setItem(ui->pointLoadsTbl->rowCount()-1,0, valueItem);
            ui->pointLoadsTbl->setItem(ui->pointLoadsTbl->rowCount()-1,1, distanceItem);
            ui->pointLoadsTbl->setItem(ui->pointLoadsTbl->rowCount()-1,2, directionItem);
        }
        for (std::vector<PointLoad>::size_type i = 0; i < horizontalForces.size(); i++) {
            ui->pointLoadsTbl->insertRow(ui->pointLoadsTbl->rowCount());
            QTableWidgetItem *valueItem = new QTableWidgetItem();
            valueItem->setData(Qt::EditRole, (horizontalForces[i].value));
            QTableWidgetItem *distanceItem = new QTableWidgetItem();
            distanceItem->setData(Qt::EditRole, (horizontalForces[i].distance));
            QTableWidgetItem *directionItem = new QTableWidgetItem();
            directionItem->setText("Horizontal");
            ui->pointLoadsTbl->setItem(ui->pointLoadsTbl->rowCount()-1,0, valueItem);
            ui->pointLoadsTbl->setItem(ui->pointLoadsTbl->rowCount()-1,1, distanceItem);
            ui->pointLoadsTbl->setItem(ui->pointLoadsTbl->rowCount()-1,2, directionItem);
        }
    }
}


void MainWindow::on_distributedLoadBtn_clicked()
{
    dldialog = new DistributedLoadDialog();
    int result = dldialog->exec();
    if (result == QDialog::Accepted) {
        ui->distributedLoadsTbl->setRowCount(0);
        distributedLoads.push_back(dldialog->load[0]);
        for (std::vector<DistributedLoad>::size_type i = 0; i < distributedLoads.size(); i++) {
            ui->distributedLoadsTbl->insertRow(ui->distributedLoadsTbl->rowCount());
            QTableWidgetItem *q1Item = new QTableWidgetItem();
            q1Item->setData(Qt::EditRole, (distributedLoads[i].q1));
            QTableWidgetItem *q2Item = new QTableWidgetItem();
            q2Item->setData(Qt::EditRole, (distributedLoads[i].q2));
            QTableWidgetItem *distanceItem = new QTableWidgetItem();
            distanceItem->setData(Qt::EditRole, (distributedLoads[i].distance));
            QTableWidgetItem *lengthItem = new QTableWidgetItem();
            lengthItem->setData(Qt::EditRole, (distributedLoads[i].length));;
            ui->distributedLoadsTbl->setItem(ui->distributedLoadsTbl->rowCount()-1,0, q1Item);
            ui->distributedLoadsTbl->setItem(ui->distributedLoadsTbl->rowCount()-1,1, q2Item);
            ui->distributedLoadsTbl->setItem(ui->distributedLoadsTbl->rowCount()-1,2, distanceItem);
            ui->distributedLoadsTbl->setItem(ui->distributedLoadsTbl->rowCount()-1,3, lengthItem);
        }
    }
}


void MainWindow::on_pointMomentBtn_clicked()
{
    pmdialog = new PointMomentDialog();
    int result = pmdialog->exec();
    if (result == QDialog::Accepted) {
        ui->pointMomentsTbl->setRowCount(0);
        pointMoments.push_back(pmdialog->moment[0]);
        for (std::vector<PointMoment>::size_type i = 0; i < pointMoments.size(); i++) {
            ui->pointMomentsTbl->insertRow(ui->pointMomentsTbl->rowCount());
            QTableWidgetItem *valueItem = new QTableWidgetItem();
            valueItem->setData(Qt::EditRole, (pointMoments[i].value));
            QTableWidgetItem *distanceItem = new QTableWidgetItem();
            distanceItem->setData(Qt::EditRole, (pointMoments[i].distance));
            ui->pointMomentsTbl->setItem(ui->pointMomentsTbl->rowCount()-1,0, valueItem);
            ui->pointMomentsTbl->setItem(ui->pointMomentsTbl->rowCount()-1,1, distanceItem);
        }
    }
}

Context MainWindow::createCtx() {
    return Context(b, verticalForces, horizontalForces, distributedLoads, pointMoments);
}


void MainWindow::on_diagBtn_clicked()
{
    Context ctx = createCtx();
    dview = new DiagView(ctx);
    dview->exec();
}

