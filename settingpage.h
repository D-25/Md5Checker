#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QDialog>

namespace Ui {
class SettingPage;
}

class SettingPage : public QDialog
{
    Q_OBJECT

public:
    explicit SettingPage(QWidget *parent = 0);
    ~SettingPage();

private slots:
    void on_showInfo_byteCheck_clicked();

    void on_info_freezeStatus_clicked();

    void on_settings_Cancel_clicked();

    void on_settings_OK_clicked();

    void loadSettings();

    void writeSetting();

    void on_reset_Language_clicked();

    void on_reset_byteCheck_clicked();

    void on_reset_freezeStatus_clicked();

private:
    Ui::SettingPage *ui;
};

#endif // SETTINGPAGE_H
