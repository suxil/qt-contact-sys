#include "contact.h"

Contact::Contact()
{

}

Contact::Contact(QString name, QString unit, QString phone, QString email)
{
    this->name = name;
    this->unit = unit;
    this->phone = phone;
    this->email = email;
}

int Contact::getSeq()
{
    return seq;
}

QString Contact::getName()
{
    return name;
}

QString Contact::getUnit()
{
    return unit;
}

QString Contact::getPhone()
{
    return phone;
}

QString Contact::getEmail()
{
    return email;
}

void Contact::setSeq(int seq)
{
    this->seq = seq;
}

void Contact::setName(QString name)
{
    this->name = name;
}

void Contact::setUnit(QString unit)
{
    this->unit = unit;
}

void Contact::setPhone(QString phone)
{
    this->phone = phone;
}

void Contact::setEmail(QString email)
{
    this->email = email;
}
