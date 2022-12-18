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
    explicit DistributedLoadDialog(QWidget *parent = nullptr);
    ~DistributedLoadDialog();

    DistributedLoad load[1];

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DistributedLoadDialog *ui;
};

#endif // DISTRIBUTEDLOADDIALOG_H
