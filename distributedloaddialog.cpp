#include "distributedloaddialog.h"
#include "ui_distributedloaddialog.h"

#include "easydiag.h"

DistributedLoadDialog::DistributedLoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DistributedLoadDialog)
{
    ui->setupUi(this);

    ui->q1SpinBox->setDecimals(4);
    ui->q1SpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->q1SpinBox->setMinimum(std::numeric_limits<double>::max()*(-1));
    ui->q2SpinBox->setDecimals(4);
    ui->q2SpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->q2SpinBox->setMinimum(std::numeric_limits<double>::max()*(-1));
    ui->distanceSpinBox->setDecimals(4);
    ui->distanceSpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->distanceSpinBox->setMinimum(0);
    ui->lengthSpinBox->setDecimals(4);
    ui->lengthSpinBox->setMaximum(std::numeric_limits<double>::max());
    ui->lengthSpinBox->setMinimum(0);
}

DistributedLoadDialog::~DistributedLoadDialog()
{
    delete ui;
}

void DistributedLoadDialog::on_buttonBox_accepted()
{
    load[0] = DistributedLoad(ui->q1SpinBox->value(),ui->q2SpinBox->value(),ui->distanceSpinBox->value(),ui->lengthSpinBox->value());
}

