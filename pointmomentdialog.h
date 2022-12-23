#ifndef POINTMOMENTDIALOG_H
#define POINTMOMENTDIALOG_H

#include <QDialog>
#include <easydiag.h>

namespace Ui {
class PointMomentDialog;
}

class PointMomentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PointMomentDialog(double &beamL, QWidget *parent = nullptr);
    ~PointMomentDialog();
    PointMoment moment[1];

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PointMomentDialog *ui;
};

#endif // POINTMOMENTDIALOG_H
