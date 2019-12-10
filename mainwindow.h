#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QTableWidget>
#include <QListWidgetItem>
#include <QList>
#include <QLineEdit>
#include <QPushButton>

#include "contactdialog.h"
#include "contact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void refreshTable();

private:
    Ui::MainWindow *ui;

    ContactDialog *contactDialog;
    QList<Contact*> *contactList;

    Contact* getDialogContact();

};
#endif // MAINWINDOW_H
