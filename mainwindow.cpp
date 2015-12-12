#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QCryptographicHash>
#include <QFile>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>
#include <QDebug>
#include <QTranslator>

#include "settingpage.h"
#include "dialogstyle.h"
#include "comparechecksums.h"

/*
 * A primordial version of the program.
 * More functions coming soon, just stay tuned.
 * Please.
 *
 * Danilo Civati (http://d-25.net)
 * cdanilo25@gmail.com
 *
 */

bool aborted; // I know, this is ugly.
int Speed = 262144;
int MetodSelect = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //populating the speeds' and Metod combobox
    ui->SpeedSelect->addItem("Lento");
    ui->SpeedSelect->addItem("Medio (Default)");
    ui->SpeedSelect->addItem("Veloce");
    ui->MetodSelect->addItem("MD5");
    ui->MetodSelect->addItem("SHA-1");
    ui->MetodSelect->addItem("SHA-256");

    //setting first combobox's value (default)
    ui->SpeedSelect->setCurrentIndex(1);
    ui->MetodSelect->setCurrentIndex(0);

    ui->checkingBar->setVisible(false);
    ui->abortButton->setVisible(false);

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// disableAll and enableAll was used instead of this.setEnable(false) to
// mantain AbortButton enabled.

void MainWindow::disableAll()
{
    ui->startCheck->setEnabled(false);
    ui->fileSelectLabel->setEnabled(false);
    ui->fileSelectBrowse->setEnabled(false);
    ui->comparationCheck->setEnabled(false);
    ui->comparationString->setEnabled(false);
}

void MainWindow::enableAll()
{
    ui->startCheck->setEnabled(true);
    ui->fileSelectLabel->setEnabled(true);
    ui->fileSelectBrowse->setEnabled(true);
    ui->comparationCheck->setEnabled(true);
    ui->comparationString->setEnabled(true);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event)
{

    QList<QUrl> fileDropped = event->mimeData()->urls();
    QString droppedLocation;

    foreach (QUrl fileDroppedPosition, fileDropped)
    {

        // This will be edited when Batch operations is implemented.
        droppedLocation = fileDroppedPosition.toString();
        qDebug() << "Dropped: " + droppedLocation;

        if (!droppedLocation.contains(QString("file:///"))) // Block all files dropped by unknown position.
        {
            dialogStyle_info(tr("Posizione non valida."), tr("Il file <b>%1</b> possiede "
                                 "una posizione non valida, pertanto è stato ignorato al momento del "
                                 "trascinamento.").arg(droppedLocation));
            break;
        }

        droppedLocation.remove(QString("file:///")); // We need the file:/// prefix to mantain URL-style
                                                     // and block all unknown position.

        ui->fileSelectLocation->setText(droppedLocation);
        ui->startCheck->setEnabled(true);
    }
}

void MainWindow::on_fileSelectBrowse_clicked()
{
    // Open a File Browse dialog and, if a file was selected, the button to start the check become available.

    QString stringFileName = QFileDialog::getOpenFileName(this, tr("Apri"), "", tr("Tutti (*.*)"));
    if (stringFileName.isNull() || stringFileName.isEmpty())
    { }
    else
    {
        ui->startCheck->setEnabled(true);
        ui->fileSelectLocation->setText(stringFileName);
    }
}

void MainWindow::on_startCheck_clicked()
{

    // TODO: better code and more functions.

    // Select file, initialize the byteload and start processing the file, disabling the main window for security purpose.
    // Reached the ending of file, the checksum is showed to user.

    QString fileName = ui->fileSelectLocation->text();
    QString Result;
    QFile fileSelected(fileName);
    QCryptographicHash CheckMD5(QCryptographicHash::Md5);
    QCryptographicHash CheckSha1(QCryptographicHash::Sha1);
    QCryptographicHash CheckSha256(QCryptographicHash::Sha256);

    int byteLoad = Speed;

        fileSelected.open(QFile::ReadOnly);
        aborted = false;
        while(!fileSelected.atEnd())
        {
            switch(MetodSelect) {
            case 0:
                CheckMD5.addData(fileSelected.read(byteLoad));
                QCoreApplication::processEvents();
                break;
            case 1:
                CheckSha1.addData(fileSelected.read(byteLoad));
                QCoreApplication::processEvents();
                break;
            case 2:
                CheckSha256.addData(fileSelected.read(byteLoad));
                QCoreApplication::processEvents();
                break;
            }


            ui->checkInfo->setText(tr("Analisi dell'impronta del file selezionato in corso..."));

            ui->checkingBar->setVisible(true);
            ui->abortButton->setVisible(true);

            disableAll();

            if (aborted == true)
            {
                break; // When AbortButton is pressed, the Checksum process is killed.
            }
            enableAll();

            QByteArray md5Data;

            switch(MetodSelect) {
            case 0:
                md5Data = CheckMD5.result();
                break;
            case 1:
                md5Data = CheckSha1.result();
                break;
            case 2:
                md5Data = CheckSha256.result();
                break;
            }

            QString md5DataHEX = md5Data.toHex();
            Result = md5DataHEX;
         }
            enableAll();
            ui->checkingBar->setVisible(false);
            ui->abortButton->setVisible(false);





        if (aborted == false)
        {
            ui->checkInfo->setText(tr("Impronta del File scelto: %1").arg(Result));

            if (ui->comparationCheck->isChecked())
            {
                comparationStart(ui->comparationString->text(), Result); // Check between two string, one inserted by user.
            }
        }

        else
        {
                ui->checkInfo->setText(tr("Operazione annullata dall'utente."));
        }

        }

void MainWindow::on_abortButton_clicked()
{
    aborted = true;
}

void MainWindow::on_SpeedSelect_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        Speed = 4096;         //slow
        break;

    case 1:
        Speed = 262144;         //default
        break;

    case 2:
        Speed = 524288;         //speedy
        break;
    }

    qDebug() << "Selected Speed : " << Speed;

}

void MainWindow::on_pushButton_clicked()
{
    SettingPage settings;
    settings.exec();
}

void MainWindow::on_MetodSelect_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        MetodSelect = 0;
         qDebug() << "MD5"; //default
        break;

    case 1:
        MetodSelect = 1;
         qDebug() << "SHA-1";
        break;
    case 2:
        MetodSelect = 2;
         qDebug() << "SHA-256";
        break;
    }
}
