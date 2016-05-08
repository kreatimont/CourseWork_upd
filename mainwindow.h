#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "space.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_actionCreate_root_triggered();

    void on_pushButton_1_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_actionEdit_triggered();

    void on_actionAdd_item_triggered();

    void on_actionSave_triggered();

    void on_pushButton_3_clicked();

    void on_treeWidget_clicked(const QModelIndex &index);

    void on_actionRemove_triggered();

    void on_actionLoad_triggered();

    void on_actionClear_tree_triggered();

    void on_actionQueue2_triggered();

    void on_actionHuman_made_triggered();

    void on_actionNatural_triggered();

    void on_actionSave_2_triggered();

    void on_actionQuit_triggered();

    void on_actionHelp_triggered();

    void on_actionQueue3_triggered();

    void on_actionFor_each_star_triggered();

    void on_actionDark_2_triggered();

    void on_actionDefault_2_triggered();

    void on_actionSolirized_triggered();

    void on_actionCourier_New_triggered();

    void on_actionComic_San_triggered();

    void on_treeWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    void setButtonState(bool,bool);

    void show_space();
    void show_star(star *);
    void show_planet(planet *);
    void show_satellite(satellite *);
    void show_tree();

    int selected_lvl();
    int selected_index(int);
};

#endif // MAINWINDOW_H
