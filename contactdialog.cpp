#include "contactdialog.h"
#include "ui_contactdialog.h"

ContactDialog::ContactDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactDialog)
{
    ui->setupUi(this);
}

ContactDialog::~ContactDialog()
{
    delete ui;
}

QString ContactDialog::getName()
{
    return ui->nameEdit->text().trimmed();
}

QString ContactDialog::getUnit()
{
    return ui->unitEdit->text().trimmed();
}

QString ContactDialog::getPhone()
{
    return ui->phoneEdit->text().trimmed();
}

QString ContactDialog::getEmail()
{
    return ui->emailEdit->text().trimmed();
}

void ContactDialog::setName(QString name) {
    ui->nameEdit->setText(name);
}

void ContactDialog::setUnit(QString unit) {
    ui->unitEdit->setText(unit);
}

void ContactDialog::setPhone(QString phone) {
    ui->phoneEdit->setText(phone);
}

void ContactDialog::setEmail(QString email) {
    ui->emailEdit->setText(email);
}

void ContactDialog::clear()
{
    ui->nameEdit->clear();
    ui->unitEdit->clear();
    ui->phoneEdit->clear();
    ui->emailEdit->clear();
}
