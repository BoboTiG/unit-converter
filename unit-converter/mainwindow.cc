
/*!
 * \file mainwindow.cc
 * \brief Main window for Unit converter.
 * \author BoboTiG
 * \date 2013.07.15
 *
 * Copyleft ((C)) 2013 BoboTiG
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Center the window
    QRect availableGeometry(QApplication::desktop()->availableGeometry());
    move((availableGeometry.width() - width()) / 2,
         (availableGeometry.height() - height()) / 2);

    ui->inputLineEdit->setValidator(new QDoubleValidator());

    // Units
    all_units();
    std::map<QString, QString>::const_iterator itr;
    for ( itr = units_name.begin(); itr != units_name.end(); ++itr ) {
        ui->unitBox->addItem((*itr).second, (*itr).first);
    }
    fill_lists(0);
}

MainWindow::~MainWindow() {
    delete ui;
}


/**
 * @brief All units belong to us.
 *        https://fr.wikipedia.org/wiki/Unit%C3%A9_de_base_du_syst%C3%A8me_international
 *        https://fr.wikipedia.org/wiki/Conversion_des_unités
 * @date 2013/07/15
 */
void MainWindow::all_units() {
    std::map<QString, double> tmp_v;
    std::map<QString, QString> tmp_n;
    QString name;

    // Available units ---------------------------------------------------------
    units_name["mass"] = tr("Mass") + " (M)";
    units_name["time"] = tr("Time") + " (s)";

    // Mass: equivalence for 1kg -----------------------------------------------
    tmp_v.clear(); tmp_n.clear();
    tmp_v["kg"]        = 1.0;              name = tr("kilogram");                    tmp_n[name] = "kg";
    tmp_v["g"]         = 1.0e-3;           name = tr("gram");                        tmp_n[name] = "g";
    tmp_v["Y"]         = 1.0e-9;           name = tr("gamma");                       tmp_n[name] = "Y";
    tmp_v["gr"]        = 64.79891e-5;      name = tr("grain");                       tmp_n[name] = "gr";
    tmp_v["ct"]        = 200.0e-6;         name = tr("carat [metric]");              tmp_n[name] = "ct";
    tmp_v["kt"]        = 205.196548333e-6; name = tr("carat");                       tmp_n[name] = "kt";
    tmp_v["oz"]        = 28.349523125e-3;  name = tr("ounce [avoirdupois]");         tmp_n[name] = "oz";
    tmp_v["oz"]        = 31.1034768e-3;    name = tr("ounce");                       tmp_n[name] = "oz";
    tmp_v["lb"]        = 0.45359237;       name = tr("pound [avoirdupois]");         tmp_n[name] = "lb";
    tmp_v["sh cwt"]    = 45.359237;        name = tr("short hundredweight, cental"); tmp_n[name] = "sh cwt";
    tmp_v["long cwt"]  = 50.80234544;      name = tr("long hundredweight");          tmp_n[name] = "long cwt";
    tmp_v["q"]         = 100.0;            name = tr("quintal");                     tmp_n[name] = "q";
    tmp_v["kip"]       = 453.59237;        name = tr("kip");                         tmp_n[name] = "kip";
    tmp_v["sh tn"]     = 907.18474;        name = tr("short ton");                   tmp_n[name] = "sh tn";
    tmp_v["t"]         = 1000.0;           name = tr("tonne");                       tmp_n[name] = "t";
    tmp_v["long tn"]   = 1016.0469088;     name = tr("long ton");                    tmp_n[name] = "long tn";
    tmp_v["Da"]        = 1.66054e-27;      name = tr("dalton");                      tmp_n[name] = "Da";
    tmp_v["u, uma"]    = 1.66054e-27;      name = tr("atomic mass unit");            tmp_n[name] = "u, uma";
    units_values["mass"] = tmp_v; units["mass"] = tmp_n;

    // Time: equivalence for 1s ------------------------------------------------
    tmp_v.clear(); tmp_n.clear();
    tmp_v["s"]    = 1.0;             name = tr("second");        tmp_n[name] = "s";
    tmp_v["m"]    = 60.0;            name = tr("minute");        tmp_n[name] = "m";
    tmp_v["h"]    = 3600.0;          name = tr("hour");          tmp_n[name] = "h";
    tmp_v["d"]    = 24 * 3600.0;     name = tr("day");           tmp_n[name] = "d";
    tmp_v["y"]    = 31556952;        name = tr("year");          tmp_n[name] = "y";
    tmp_v["tP"]   = 1.351211818e-43; name = tr("Planck time");   tmp_n[name] = "tP";
    units_values["time"] = tmp_v; units["time"] = tmp_n;
}


/**
 * @brief Fill lists for a given unit.
 * @date 2013/07/15
 */
void MainWindow::fill_lists(const int index) {
    unit = ui->unitBox->itemData(index, Qt::UserRole).toString();

    // Clear lists and input
    ui->inputBox->clear();
    ui->convertBox->clear();
    ui->inputLineEdit->clear();

    QString tmp;
    std::map<QString, QString>::const_iterator itr;
    for ( itr = units[unit].begin(); itr != units[unit].end(); ++itr ) {
        tmp = QString("%1 (%2)").arg((*itr).first, (*itr).second);
        ui->inputBox->addItem(tmp, (*itr).second);
        ui->convertBox->addItem(tmp, (*itr).second);
    }
}


/**
 * @brief An unit has beed chosen. Fill input and converted comboBoxes.
 * @date 2013/07/12
 */
void MainWindow::on_unitBox_currentIndexChanged(int index) {
    fill_lists(index);
}


/**
 * @brief Convert input. This action could be actionned by pressing ENTER into the
 *        input field, when refresh icon is pressed or when an unit is changed.
 * @date 2013/07/15
 */
void MainWindow::convert() {
    double value = ui->inputLineEdit->text().toDouble();
    QString from = ui->inputBox->itemData(ui->inputBox->currentIndex(), Qt::UserRole).toString();
    QString to = ui->convertBox->itemData(ui->convertBox->currentIndex(), Qt::UserRole).toString();
    double result = value * units_values[unit][from] / units_values[unit][to];

    ui->convertlineEdit->setText(QString::number(result));
}
void MainWindow::on_inputLineEdit_returnPressed() {
    convert();
}
void MainWindow::on_inputLineEdit_lostFocus() {
    convert();
}
void MainWindow::on_inputButton_clicked() {
    convert();
}
void MainWindow::on_inputBox_currentIndexChanged(int index) {
    Q_UNUSED(index);
    convert();
}
void MainWindow::on_convertBox_currentIndexChanged(int index) {
    Q_UNUSED(index);
    convert();
}


/**
 * @brief Switch units and call convert to update result.
 * @date 2013/07/12
 */
void MainWindow::on_pushButton_clicked() {
    int from = ui->inputBox->currentIndex();
    int to = ui->convertBox->currentIndex();

    ui->inputBox->setCurrentIndex(to);
    ui->convertBox->setCurrentIndex(from);
    convert();
}
