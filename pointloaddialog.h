#ifndef POINTLOADDIALOG_H
#define POINTLOADDIALOG_H

#include <QDialog>
#include "easydiag.h"
#include <QButtonGroup>

namespace Ui {
class PointLoadDialog;
}

class PointLoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PointLoadDialog(QWidget *parent = nullptr);
    ~PointLoadDialog();

    QButtonGroup *directionSelection;
    std::vector<std::pair<PointLoad,bool>> forces;

private slots:
    void on_buttonBox_accepted();

    void on_angleBox_stateChanged(int arg1);

private:
    Ui::PointLoadDialog *ui;
};

#endif // POINTLOADDIALOG_H
