#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("通讯录管理系统");

    setWindowFlags(Qt::Window);

    contactDialog = new ContactDialog(this);
    contactList = new QList<Contact*>();

    QTableWidget *tableWidget = ui->centralwidget->findChild<QTableWidget*>("tableWidget");

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->actionadd, &QAction::triggered, this, [=]() {
       qDebug() << "add";
       contactDialog->setWindowTitle(QString("添加联系人"));
       int status = contactDialog->exec();
       if (status == QDialog::Accepted) {
           Contact *contact = getDialogContact();

           contact->setSeq(contactList->size());

           contactList->insert(contactList->size(), contact);
       }
       contactDialog->clear();

       refreshTable();
    });

    connect(ui->actionedit, &QAction::triggered, this, [=]() {
       qDebug() << "edit";

       Contact *contact = contactList->at(tableWidget->currentRow());

       contactDialog->setName(contact->getName());
       contactDialog->setUnit(contact->getUnit());
       contactDialog->setPhone(contact->getPhone());
       contactDialog->setEmail(contact->getEmail());
       contactDialog->initEditReadOnly(true);

       contactDialog->setWindowTitle(QString("修改联系人"));
       int status = contactDialog->exec();
       if (status == QDialog::Accepted) {
           Contact *item = getDialogContact();

           contactList->replace(contact->getSeq(), item);
       }
       contactDialog->clear();

       refreshTable();
    });

    connect(ui->actiondelete, &QAction::triggered, this, [=]() {
       qDebug() << "deleted";

       qDebug() << "size: " + QString(tableWidget->currentRow());
       contactList->removeAt(tableWidget->currentRow());

       refreshTable();
    });

    connect(ui->centralwidget->findChild<QPushButton*>("resetBtn"), &QPushButton::clicked, this, [=]() {
        QLineEdit *nameSearch = ui->centralwidget->findChild<QLineEdit*>("nameSearch");
        QLineEdit *phoneSearch = ui->centralwidget->findChild<QLineEdit*>("phoneSearch");

        qDebug() << "clear";
        nameSearch->clear();
        phoneSearch->clear();
    });

    connect(ui->centralwidget->findChild<QPushButton*>("searchBtn"), &QPushButton::clicked, this, [=]() {
        qDebug() << "search";
        refreshTable();
    });

    tableWidget->horizontalHeader()->setStretchLastSection(true); // 设置充满表宽度

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    tableWidget->setColumnCount(4);

    readContact();

    refreshTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshTable()
{
    QTableWidget *tableWidget = ui->centralwidget->findChild<QTableWidget*>("tableWidget");

    QLineEdit *nameSearch = ui->centralwidget->findChild<QLineEdit*>("nameSearch");
    QLineEdit *phoneSearch = ui->centralwidget->findChild<QLineEdit*>("phoneSearch");

    QList<Contact*> *filterContactList = new QList<Contact*>();
    for (int i = 0; i < contactList->size(); i ++) {
        Contact *contact = contactList->at(i);

        if (!nameSearch->text().trimmed().isEmpty()) {
            qDebug() << "name search:" << nameSearch->text().trimmed();
            if (contact->getName().isEmpty() | !contact->getName().contains(nameSearch->text().trimmed(), Qt::CaseSensitive)) {
                continue;
            }
            qDebug() << "add name";
        }
        if (!phoneSearch->text().trimmed().isEmpty()) {
            qDebug() << "phone search:" << phoneSearch->text().trimmed();
            if (contact->getPhone().isEmpty() | !contact->getPhone().contains(phoneSearch->text().trimmed(), Qt::CaseSensitive)) {
                continue;
            }
            qDebug() << "add phone";
        }

        filterContactList->insert(filterContactList->size(), contact);

        qDebug() << "show data:" << contact->getName() << ":" << contact->getUnit() << ":" << contact->getPhone() << ":" << contact->getEmail();
    }

    tableWidget->setRowCount(filterContactList->size());

    for (int i = 0; i < filterContactList->size(); i ++) {
        Contact *contact = filterContactList->at(i);

        tableWidget->setItem(i, 0, new QTableWidgetItem(contact->getName()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(contact->getUnit()));
        tableWidget->setItem(i, 2, new QTableWidgetItem(contact->getPhone()));
        tableWidget->setItem(i, 3, new QTableWidgetItem(contact->getEmail()));

        qDebug() << "data:" << contact->getName() << ":" << contact->getUnit() << ":" << contact->getPhone() << ":" << contact->getEmail();
    }

    writeContact();
}

Contact* MainWindow::getDialogContact()
{
    QString name = contactDialog->getName();
    QString unit = contactDialog->getUnit();
    QString phone = contactDialog->getPhone();
    QString email = contactDialog->getEmail();

    Contact *contact = new Contact(name, unit, phone, email);
    return contact;
}

void MainWindow::readContact()
{
    QFile file("contact.txt");
    if (!file.open(QIODevice::ReadOnly))
        return;

    contactList->clear();

    int i = 0;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QList<QByteArray> contactByteList = line.replace("\n", "").split(',');

        qDebug() << "read: " << QString(line) << ":" << contactByteList.size();
        Contact *contact = new Contact(QString(contactByteList.at(0)), QString(contactByteList.at(1)), QString(contactByteList.at(2)), QString(contactByteList.at(3)));
        contact->setSeq(i);

        i ++;
        contactList->insert(i, contact);
    }
    qDebug() << "read complete contact size: " << contactList->size();
}

void MainWindow::writeContact()
{
    QFile file("contact.txt");
    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream out(&file);

    qDebug() << "contact size: " << contactList->size();
    for (int i = 0; i < contactList->size(); i ++) {
        Contact *contact = contactList->at(i);

        QString *contactString = new QString;
        contactString->append(contact->getName()).append(",");
        contactString->append(contact->getUnit()).append(",");
        contactString->append(contact->getPhone()).append(",");
        contactString->append(contact->getEmail()).append("\n");

        qDebug() << contactString->toUtf8();

        out << contactString->toUtf8();
    }

}
