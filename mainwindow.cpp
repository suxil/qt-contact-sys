#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    contactDialog = new ContactDialog(this);

    connect(ui->actionadd, &QAction::triggered, this, [=]() {
       qDebug() << "add";
       contactDialog->setWindowTitle(QString("添加联系人"));
       int status = contactDialog->exec();
       if (status == QDialog::Accepted) {

           QString name;

       }
       contactDialog->clearMask();
    });

    connect(ui->actionedit, &QAction::triggered, this, [=]() {
       qDebug() << "edit";
       contactDialog->setWindowTitle(QString("修改联系人"));
       int status = contactDialog->exec();
       if (status == QDialog::Accepted) {

           QString name;

       }
       contactDialog->clearMask();
    });

    connect(ui->actiondelete, &QAction::triggered, this, [=]() {
       qDebug() << "deleted";
    });

    QTableWidget * tableWidget = ui->centralwidget->findChild<QTableWidget*>("tableWidget");

    tableWidget->horizontalHeader()->setMinimumHeight(30);
    //tableWidget->resize(350, 200);

    //tableWidget.ho()->setResizeMode(QHeaderView::Stretch);

    QStringList tableHeader;
    tableHeader << "姓名" << "地址";
    tableWidget->setHorizontalHeaderLabels(tableHeader);

    tableWidget->horizontalHeader()->setVisible(true);

    tableWidget->setRowCount(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

