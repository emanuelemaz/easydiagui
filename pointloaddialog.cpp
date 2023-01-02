#include "pointloaddialog.h"
#include "ui_pointloaddialog.h"

#include <limits>
#include <QButtonGroup>
#include <cmath>

PointLoadDialog::PointLoadDialog(double &beamL, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointLoadDialog)
{
    ui->setupUi(this);

    ui->angleValue->setDecimals(4);
    ui->doubleSpinBox->setDecimals(4);
    ui->doubleSpinBox_2->setDecimals(4);

    ui->angleValue->setMaximum(std::numeric_limits<double>::max());
    ui->doubleSpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->doubleSpinBox_2->setMaximum(beamL);

    ui->doubleSpinBox->setMinimum(std::numeric_limits<double>::max()*(-1));
    ui->doubleSpinBox_2->setMinimum(0);
    ui->angleValue->setMinimum(0);

    directionSelection = new QButtonGroup();
    directionSelection->setExclusive(true);
    directionSelection->addButton(ui->horizontalBox);
    directionSelection->addButton(ui->verticalBox);
    directionSelection->addButton(ui->angleBox);
    directionSelection->setId(ui->verticalBox,0);
    directionSelection->setId(ui->horizontalBox,1);
    directionSelection->setId(ui->angleBox,2);

    ui->verticalBox->click();
}

PointLoadDialog::~PointLoadDialog()
{        
    delete ui;
}

void PointLoadDialog::on_buttonBox_accepted()
{
    if (directionSelection->checkedId() == 0) {
        forces.push_back(std::make_pair(PointLoad(ui->doubleSpinBox->value(), ui->doubleSpinBox_2->value()), true));
    } else if (directionSelection->checkedId() == 1) {
        forces.push_back(std::make_pair(PointLoad(ui->doubleSpinBox->value(), ui->doubleSpinBox_2->value()), false));
    } else if (directionSelection->checkedId() == 2) {
        forces.push_back(std::make_pair(PointLoad(ui->doubleSpinBox->value()*sin(ui->angleValue->value()*(3.141592654/180)), ui->doubleSpinBox_2->value()), true));
        forces.push_back(std::make_pair(PointLoad(ui->doubleSpinBox->value()*cos(ui->angleValue->value()*(3.141592654/180)), ui->doubleSpinBox_2->value()), false));
    }
}

void PointLoadDialog::on_angleBox_stateChanged(int arg1)
{
    if (arg1==Qt::CheckState::Checked) {
        ui->angleValue->setEnabled(true);
    } else if (arg1==Qt::CheckState::Unchecked) {
        ui->angleValue->setDisabled(true);
    }
}

