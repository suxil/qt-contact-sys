#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class ContactDialog;
}

class ContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactDialog(QWidget *parent = nullptr);
    ~ContactDialog();

    QString getName();
    QString getUnit();
    QString getPhone();
    QString getEmail();
    void setName(QString name);
    void setUnit(QString unit);
    void setPhone(QString phone);
    void setEmail(QString email);
    void clear();
    void initEditReadOnly(bool readOnly);

private:
    Ui::ContactDialog *ui;
};

#endif // CONTACTDIALOG_H
