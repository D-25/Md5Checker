#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWinExtras/QWinTaskbarButton>
#include <QtWinExtras/QWinTaskbarProgress>

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
    void on_fileSelectBrowse_clicked();

    void on_startCheck_clicked();

    void on_abortButton_clicked();

    void disableAll();
    void enableAll();

    void on_action_Settings_triggered();

    void on_action_Open_triggered();

    void on_action_Check_triggered();

    void on_action_OpenCompare_triggered();

private:
    Ui::MainWindow *ui;
    QWinTaskbarButton *taskbarButton;
    QWinTaskbarProgress *taskbarProgress;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // MAINWINDOW_H
