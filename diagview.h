#ifndef DIAGVIEW_H
#define DIAGVIEW_H

#include <QDialog>
#include "easydiag.h"

namespace Ui {
class DiagView;
}

class DiagView : public QDialog
{
    Q_OBJECT

public:
    DiagView(Context &ctx, QWidget *parent = nullptr);
    ~DiagView();

    Context lCtx;

private slots:
    void on_doubleSpinBox_valueChanged(double arg1);

    void on_saveH_clicked();

    void on_saveT_clicked();

    void on_saveM_clicked();

private:
    Ui::DiagView *ui;
    double yHmin, yHmax, yTmin, yTmax, yMmin, yMmax;
};

#endif // DIAGVIEW_H
