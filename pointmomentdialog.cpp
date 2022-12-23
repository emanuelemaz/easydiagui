#include "pointmomentdialog.h"
#include "ui_pointmomentdialog.h"

#include "easydiag.h"

PointMomentDialog::PointMomentDialog(double &beamL, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointMomentDialog)
{
    ui->setupUi(this);

    ui->doubleSpinBox->setDecimals(4);
    ui->doubleSpinBox_2->setDecimals(4);

    ui->doubleSpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->doubleSpinBox_2->setMaximum(beamL);

    ui->doubleSpinBox->setMinimum(std::numeric_limits<double>::max()*(-1));
    ui->doubleSpinBox_2->setMinimum(0);

}

PointMomentDialog::~PointMomentDialog()
{
    delete ui;
}

void PointMomentDialog::on_buttonBox_accepted()
{
    moment[0] = PointMoment(ui->doubleSpinBox->value(), ui->doubleSpinBox_2->value());
}

