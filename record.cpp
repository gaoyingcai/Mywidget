#include "record.h"
#include "ui_record.h"
//添加头文件
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


//QMap<QString, QString> employeesMap;
//QMap<QString, QString> productMap;

Record::Record(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Record)
{
    ui->setupUi(this);

    //建立并打开数据库
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }

    //创建表格
    QSqlQuery sql_query1;

    //查询数据
    sql_query1.exec("select * from employees");
    if(!sql_query1.exec())
    {
        qDebug()<<sql_query1.lastError();
    }
    else
    {
        ui->comboBox->clear();
        while(sql_query1.next())
        {
            QString name = sql_query1.value(1).toString();
            ui->comboBox->addItem(name);
//            QString id = sql_query1.value(0).toString();
//            employeesMap.insert(name,id);
        }
    }


    QSqlQuery sql_query2;
    sql_query2.exec("select * from product");
    if(!sql_query2.exec())
    {
        qDebug()<<sql_query2.lastError();
    }
    else
    {
        while(sql_query2.next())
        {
            QString name = sql_query2.value(1).toString();
            ui->comboBox_2->addItem(name);
//            QString id = sql_query2.value(0).toString();
//            productMap.insert(name,id);
        }
    }

    //关闭数据库
    database.close();

    ui->dateEdit->setDate(QDate::currentDate());
}

Record::~Record()
{
    delete ui;
}

void Record::on_pushButton_clicked()
{   
    QString date = ui->dateEdit->date().toString("yyyyMMdd");
//    QString em_id = employeesMap[ui->comboBox->currentText()];
//    QString pr_id = productMap[ui->comboBox_2->currentText()];
    QString em_id = ui->comboBox->currentText();
    QString pr_id = ui->comboBox_2->currentText();
    QString pr_count = ui->textEdit->toPlainText();



    if(ui->textEdit->toPlainText().length()>0){

        //添加员工
        //建立并打开数据库
        QSqlDatabase database;
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        if (!database.open())
        {
            qDebug() << "Error: Failed to connect database." << database.lastError();
        }

        //创建表格
        QSqlQuery sql_query;
        QString sql_string = QString("INSERT OR REPLACE INTO record (add_time, em_name, pr_name, count) VALUES(%1,\"%2\",\"%3\",%4)").arg(date).arg(em_id).arg(pr_id).arg(pr_count);
        qDebug() << "sql_string" << sql_string;
        if(!sql_query.exec(sql_string))
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            ui->textEdit->clear();
            qDebug() <<"inster success";
        }
        database.close();
    }else{
        //请输入数量
    }





}

void Record::on_dateEdit_editingFinished()
{

}
