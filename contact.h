#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

class Contact
{
public:
    Contact();

    Contact(QString name, QString unit, QString phone, QString email);

    int getSeq();
    QString getName();
    QString getUnit();
    QString getPhone();
    QString getEmail();
    void setSeq(int seq);
    void setName(QString name);
    void setUnit(QString unit);
    void setPhone(QString phone);
    void setEmail(QString email);

private:
    int seq;
    QString name;
    QString unit;
    QString phone;
    QString email;

};

#endif // CONTACT_H
