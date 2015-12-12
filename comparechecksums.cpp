#include "comparechecksums.h"
#include <iostream>
#include <QObject>
#include <QDebug>
#include <QRegularExpression>
#include "dialogstyle.h"

int inputCheckHEX(QString input)
{

    /*
     * Usage:
     *
     * if (inputCheckHEX(input) == 0)
     * {
     *      do something.
     * }
     *
     * Please note, when it fails return 0.
     */

    int HEXisOK = 1;

    //check if the original string is a correct HEX string - now working!
    QRegularExpression hexMatcher("^[0-9A-F]{6}$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = hexMatcher.match(input);
    if (match.hasMatch())
    {
        HEXisOK = 0;
    }

    //check if original string is smaller or bigger than 32 chars

    if(input.length() != 32){

        HEXisOK = 0;
    }

    return HEXisOK;

}

int comparationStart(QString original, QString checked)
{
    // To keep code clean.

    /*
     * Usage:
     *
     * if (comparationStart(original, checked) == 1)
     * {
     *      do something.
     * }
     *
     */

    int comparationSuccess = 0;

    if (original == checked)
    {
        comparationSuccess = 1;

        dialogStyle_info(QObject::tr("Risultati della comparazione"), QObject::tr("Il controllo è riuscito: i due valori sono uguali."));
    }
    else
    {
       dialogStyle_info(QObject::tr("Risultati della comparazione"), QObject::tr("<b>I due valori non combaciano.</b><br/><br/>Originale: %1<br/>File analizzato: %2<br/><br/>"
                           "Utilizzare questo File potrebbe portare a risultati indesiderati: riscaricare il File se necessario fino a quando il controllo non riesce.").arg(original, checked));
    }


    return comparationSuccess;
}
