#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xlsxdocument.h"
#include "datastruct.h"
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonOpen_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this, QString("Please select source XLSX folder..."), QString("./"));
    if(!file_path.isEmpty())
    {
        ui->textEdit->setPlainText(file_path);
    }
}

void MainWindow::on_pushButtonSwitch_clicked()
{
    QString folder = ui->textEdit->toPlainText();
    if(folder.isEmpty())
    {
        QString log = QString("please select a folder!");
        m_log_list.append(log);
        QStringListModel *modelitem = new QStringListModel(m_log_list);
        ui->listView->setModel(modelitem);
        return;
    }

    QStringList file_list;
    QDir dir(folder);
    if(dir.exists())
    {
        //获取所选文件类型过滤器
        QStringList filters;
        //文件过滤
        filters<<QString("*.xlsx");
        //定义迭代器并设置过滤器
        QDirIterator dir_iterator(folder, filters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while(dir_iterator.hasNext())
        {
            dir_iterator.next();
            QFileInfo file_info = dir_iterator.fileInfo();
            QString absolute_file_path = file_info.absoluteFilePath();
            file_list.append(absolute_file_path);
        }
    }

    if(file_list.size() <= 0)
    {
        QString log = QString("not find xlsx to convert!");
        m_log_list.append(log);
        QStringListModel *modelitem = new QStringListModel(m_log_list);
        ui->listView->setModel(modelitem);
        return;
    }


    for (auto item : file_list)
    {
        synergytoepg syn;
        syn.readFromXlsx(item);
        QString xml = item/*item.toLower()*/;
        xml.replace(QString(".xlsx"), QString(".xml"));
        QString log;
        if(syn.writeToXML(xml))
            log = item +QString(" -> ") + xml;
        else
            log = QString("xml write fail: ") + xml;
        m_log_list.append(log);
        QStringListModel *modelitem = new QStringListModel(m_log_list);
        ui->listView->setModel(modelitem);

    }
}

