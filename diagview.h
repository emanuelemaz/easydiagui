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

private:
    Ui::DiagView *ui;
};

#endif // DIAGVIEW_H
