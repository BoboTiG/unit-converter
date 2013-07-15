
/*!
 * \file main.cc
 * \brief Start of Unit converter.
 * \author BoboTiG
 * \date 2013.07.15
 *
 * Copyleft ((C)) 2013 BoboTiG
 */


#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication gandalf(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTranslator translator;
    translator.load(QString("%1/l10n/%2.qm")
                    .arg(gandalf.applicationDirPath())
                    .arg(QLocale::system().name()));
    gandalf.installTranslator(&translator);

    MainWindow balrog;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    gandalf.setStyle(new QCleanlooksStyle());
#endif
    balrog.show();
    return gandalf.exec();
}
