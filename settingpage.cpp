#include <QDebug>
#include <QSettings>

#include "settingpage.h"
#include "ui_settingpage.h"
#include "dialogstyle.h"

SettingPage::SettingPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingPage)
{
    ui->setupUi(this);

    loadSettings();
}

SettingPage::~SettingPage()
{
    delete ui;
}

void SettingPage::loadSettings()
{
    QSettings settings("D-25" ,"MD5Checker");

    // int ciao = settings.value("test", 5).toInt();
    // ui->progressBar->setValue(ciao);

    // LANGUAGE
    int languageSelected = settings.value("language", 0).toInt();
    ui->sCombo_Language->setCurrentIndex(languageSelected);

    // BYTECHECK
    QString byteCheckSelected = settings.value("byteCheck", 262144).toString();
    ui->combo_Bytecheck->setCurrentText(byteCheckSelected);

    // FROZENSTATUS
    bool getFrozenStatus = settings.value("applyFrozenStatus", 0).toBool();

    if (getFrozenStatus == false)
    {
        ui->check_freezeStatus->setChecked(false);
    }

    else
    {
        ui->check_freezeStatus->setChecked(true);
    }


}

void SettingPage::writeSetting()
{
    QSettings settings("D-25", "MD5Checker");

    // settings.setValue("test", ui->spinBox->value());

    settings.setValue("language", ui->sCombo_Language->currentIndex());

    /*
     * LANGUAGE LIST
     * 0. Based on system settings
     * 1. Italian
     * 2. English
     *
     */

    settings.setValue("byteCheck", ui->combo_Bytecheck->currentText());

    if (ui->check_freezeStatus->isChecked())
    {
        settings.setValue("applyFrozenStatus", true);
    }

    else
    {
        settings.setValue("applyFrozenStatus", false);
    }

}

void SettingPage::on_showInfo_byteCheck_clicked()
{
    dialogStyle_info(ui->label_Bytecheck->text(), tr("Consente di impostare la velocità dell'analisi, a seconda del blocco di byte analizzato."
                                                  "<ul><li>Se selezioni un numero troppo basso, l'analisi richiederà più tempo, ma potrebbe risultare più accurata.</li>"
                                                  "<li>Se invece selezioni un numero troppo alto, l'analisi richiederà meno tempo, ma verranno utilizzate più risorse. Non tutti i Computer potrebbero supportare un elevato numero di byte.</li>"
                                                  "<li>L'opzione di Default offre un buon mix tra affidabilità e velocità.</li>"
                                                  "<li>Generalmente ti accorgerai della differenza solo se analizzi file di grandi dimensioni.</li>"
                                                  "<li>Se il tuo Computer è lento, aumentare il numero di Byte potrebbe aumentare anche il tempo o portare addirittura al blocco del programma.</li></ul>"));
}

void SettingPage::on_info_freezeStatus_clicked()
{
    dialogStyle_info(ui->check_freezeStatus->text(), tr("Applica lo status <b>NON RISPONDE</b> al programma durante una lunga analisi."
                                                        "<ul><li>L'analisi potrebbe risultare più veloce.</li>"
                                                        "<li>Non avrai la possibilità di verificare se l'applicazione si blocca realmente.</li>"
                                                        "<li>Lo status di congelamento si toglierà automaticamente una volta terminata l'analisi, e il programma tornerà a funzionare normalmente.</li>"
                                                        "<li>Il sistema potrebbe consigliare di chiudere l'applicazione: nella maggior parte dei casi, dovresti rifiutare.</li>"
                                                        "<li>Lo status di congelamento verrà applicato solo quando analizzerai File molto grandi.</li>"
                                                        "<li>Con lo status di congelamento, non potrai annullare un'analisi avviata. Tuttavia, ti sarà chiesta una conferma prima di iniziare l'analisi.</li>"
                                                        "<li>Applicare questo status <i>non</i> danneggerà i File analizzati.</li>"
                                                        "<li>Con lo Status di Congelamento attivo, non potrai sapere a che percentuale si trova l'operazione.</li></ul>"));
}

void SettingPage::on_settings_Cancel_clicked()
{
    this->close();
    qDebug() << "Forgotten changed Settings.";
}

void SettingPage::on_settings_OK_clicked()
{
    QSettings settings("D-25", "MD5Checker");

    int languageSelected = settings.value("language", 0).toInt();
    writeSetting();
    int languageSelectedCHECK = settings.value("language", 0).toInt();

    if (languageSelectedCHECK != languageSelected)
    {
        dialogStyle_info(tr("Riavvia l'applicazione per applicare la nuova lingua.<br/>Please restart application to change language."), 0);
    }

    this->close();
    qDebug() << "Settings saved to: " << settings.fileName();
}

// RESET SETTINGS BUTTONS.

void SettingPage::on_reset_Language_clicked()
{
    ui->sCombo_Language->setCurrentIndex(0);
}

void SettingPage::on_reset_byteCheck_clicked()
{
    ui->combo_Bytecheck->setCurrentText("262144");
}

void SettingPage::on_reset_freezeStatus_clicked()
{
    ui->check_freezeStatus->setChecked(false);
}
