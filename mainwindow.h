#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pointloaddialog.h"
#include "distributedloaddialog.h"
#include "pointmomentdialog.h"
#include "diagview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Context createCtx();

private slots:
    void on_pointLoadBtn_clicked();
    void on_distributedLoadBtn_clicked();

    void on_pointMomentBtn_clicked();
    void on_diagBtn_clicked();

    void on_beamSpinBox_valueChanged(double arg1);

    void on_clrPl_clicked();

    void on_clrDl_clicked();

    void on_clrPm_clicked();

    void on_clrPlSel_clicked();

    void on_clrDlSel_clicked();

    void on_clrPmSel_clicked();

private:
    Ui::MainWindow *ui;
    PointLoadDialog *pldialog;
    DistributedLoadDialog *dldialog;
    PointMomentDialog *pmdialog;
    DiagView *dview;

    Beam b;
    std::vector<PointLoad> verticalForces;
    std::vector<PointLoad> horizontalForces;
    std::vector<DistributedLoad> distributedLoads;
    std::vector<PointMoment> pointMoments;
};
#endif // MAINWINDOW_H
