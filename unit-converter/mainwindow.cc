#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Centrage de la fenêtre
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
    fill_lists(ui->unitBox->itemData(0, Qt::UserRole).toString());
    unit = ui->unitBox->itemData(0, Qt::UserRole).toString();
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

    // Available units ---------------------------------------------------------
    units_name["mass"] = "Mass (M)";

    // Mass: equivalence for 1kg -----------------------------------------------
    tmp_v.clear(); tmp_n.clear();
    tmp_v["kg"]        = 1.0;              tmp_n[tr("kilogram")] = "kg";
    tmp_v["g"]         = 1.0e-3;           tmp_n[tr("gram")] = "g";
    tmp_v["Y"]         = 1.0e-9;           tmp_n[tr("gamma")] = "Y";
    tmp_v["gr"]        = 64.79891e-5;      tmp_n[tr("grain")] = "gr";
    tmp_v["ct"]        = 200.0e-6;         tmp_n[tr("carat [metric]")] = "ct";
    tmp_v["kt"]        = 205.196548333e-6; tmp_n[tr("carat")] = "kt";
    tmp_v["oz"]        = 28.349523125e-3;  tmp_n[tr("ounce [avoirdupois]")] = "oz";
    tmp_v["oz"]        = 31.1034768e-3;    tmp_n[tr("ounce")] = "oz";
    tmp_v["lb"]        = 0.45359237;       tmp_n[tr("pound [avoirdupois]")] = "lb";
    tmp_v["sh cwt"]    = 45.359237;        tmp_n[tr("short hundredweight, cental")] = "sh cwt";
    tmp_v["long cwt"]  = 50.80234544;      tmp_n[tr("long hundredweight")] = "long cwt";
    tmp_v["q"]         = 100.0;            tmp_n[tr("quintal [metric]")] = "q";
    tmp_v["kip"]       = 453.59237;        tmp_n[tr("kip")] = "kip";
    tmp_v["sh tn"]     = 907.18474;        tmp_n[tr("short ton")] = "sh tn";
    tmp_v["t"]         = 1000.0;           tmp_n[tr("tonne")] = "t";
    tmp_v["long tn"]   = 1016.0469088;     tmp_n[tr("long ton")] = "long tn";
    tmp_v["Da"]        = 1.66054e-27;      tmp_n[tr("dalton")] = "Da";
    tmp_v["u, uma"]    = 1.66054e-27;      tmp_n[tr("atomic mass unit")] = "u, uma";
    units_values["mass"] = tmp_v;          units["mass"] = tmp_n;
}


/**
 * @brief Fill lists for a given unit.
 * @date 2013/07/15
 */
void MainWindow::fill_lists(QString chosen_unit) {
    std::map<QString, QString>::const_iterator itr;
    if ( unit != chosen_unit ) {
        unit = chosen_unit;
        QString tmp;
        for ( itr = units[unit].begin(); itr != units[unit].end(); ++itr ) {
            tmp = QString("%1 (%2)").arg((*itr).first, (*itr).second);
            ui->inputBox->addItem(tmp, (*itr).second);
            ui->convertBox->addItem(tmp, (*itr).second);
        }
    }
}


/**
 * @brief An unit has beed chosen. Fill input and converted comboBoxes.
 * @date 2013/07/12
 */
void MainWindow::on_unitBox_currentIndexChanged(int index) {
    fill_lists(ui->unitBox->itemData(index, Qt::UserRole).toString());
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
