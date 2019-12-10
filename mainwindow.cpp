#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    contactDialog = new ContactDialog(this);
    contactList = new QList<Contact*>();

    QTableWidget *tableWidget = ui->centralwidget->findChild<QTableWidget*>("tableWidget");

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
       contactDialog->setWindowTitle(QString("修改联系人"));
       int status = contactDialog->exec();
       if (status == QDialog::Accepted) {
           Contact *contact = getDialogContact();

           for (int i = 0; i < contactList->size(); i ++) {
               if (contactList->at(i)->getSeq() == contact->getSeq()) {
                   contactList->replace(i, contact);
               }
           }
       }
       contactDialog->clear();

       refreshTable();
    });

    connect(ui->actiondelete, &QAction::triggered, this, [=]() {
       qDebug() << "deleted";

       for (int i = 0; i < contactList->size(); i ++) {
//           if (contactList->at(i).data(0) == contact.seq) {
//               contactList->removeAt(i);
//           }
       }

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

//    tableWidget->horizontalHeader()->setMinimumHeight(30);

    QStringList tableHeader;
    tableHeader << "人名" << "工作单位" << "电话号码" << "E-mail地址";
    tableWidget->setHorizontalHeaderLabels(tableHeader);

    tableWidget->viewport()->update();
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshTable()
{
    QTableWidget *tableWidget = ui->centralwidget->findChild<QTableWidget*>("tableWidget");

    QStringList tableHeader;
    tableHeader << "人名" << "工作单位" << "电话号码" << "E-mail地址";
    tableWidget->setHorizontalHeaderLabels(tableHeader);

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

    tableWidget->setColumnCount(4);
    tableWidget->setRowCount(filterContactList->size());

    for (int i = 0; i < filterContactList->size(); i ++) {
        Contact *contact = filterContactList->at(i);

        tableWidget->setItem(i, 0, new QTableWidgetItem(contact->getName()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(contact->getUnit()));
        tableWidget->setItem(i, 2, new QTableWidgetItem(contact->getPhone()));
        tableWidget->setItem(i, 3, new QTableWidgetItem(contact->getEmail()));

        qDebug() << "data:" << contact->getName() << ":" << contact->getUnit() << ":" << contact->getPhone() << ":" << contact->getEmail();
    }

    tableWidget->viewport()->update();
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
