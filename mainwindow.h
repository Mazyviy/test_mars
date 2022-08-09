#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <field.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnDelTrajectories_clicked();
    void on_btnRunCat_clicked();
    void on_btnRunWumpus_clicked();
    void on_btnRunGhost_clicked();
    void on_btnShuffleTraps_clicked();

private:
    Ui::MainWindow *ui;
    Field *field;
};
#endif // MAINWINDOW_H
