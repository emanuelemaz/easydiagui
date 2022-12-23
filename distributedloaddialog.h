#ifndef DISTRIBUTEDLOADDIALOG_H
#define DISTRIBUTEDLOADDIALOG_H

#include <QDialog>
#include "easydiag.h"

namespace Ui {
class DistributedLoadDialog;
}

class DistributedLoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DistributedLoadDialog(double &beamL, QWidget *parent = nullptr);
    ~DistributedLoadDialog();
    double lbeamL;
    DistributedLoad load[1];

private slots:
    void on_buttonBox_accepted();

    void on_distanceSpinBox_valueChanged(double arg1);

private:
    Ui::DistributedLoadDialog *ui;
};

#endif // DISTRIBUTEDLOADDIALOG_H
