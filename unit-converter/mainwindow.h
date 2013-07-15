
/*!
 * \file mainwindow.h
 * \brief Main window headers for Unit converter.
 * \author BoboTiG
 * \date 2013.07.15
 *
 * Copyleft ((C)) 2013 BoboTiG
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QApplication>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    #include <QCleanlooksStyle>
#endif


// Project homepage
static const char WEBSITE[] = "http://bobotig.fr/&ref=unit-converter";


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void fill_lists(QString unit);
    void convert();
    void all_units();
    void on_unitBox_currentIndexChanged(int index);
    void on_inputLineEdit_returnPressed();
    void on_inputButton_clicked();
    void on_inputLineEdit_lostFocus();
    void on_inputBox_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_convertBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    std::map<QString, std::map<QString, QString> > units;
    std::map<QString, QString> units_name;
    std::map<QString, std::map<QString, double> > units_values;
    QString unit;
};


#endif // MAINWINDOW_H
