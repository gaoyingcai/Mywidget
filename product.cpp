#include "product.h"
#include "ui_product.h"
//添加头文件
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

Product::Product(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Product)
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
    QSqlQuery sql_query;

    //查询数据
    sql_query.exec("select * from product");
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        QStringList nameList;
        QStringList priceList;
        while(sql_query.next())
        {
            QString name = sql_query.value(1).toString();
            nameList.append(name);
            QString price = sql_query.value(2).toString();
            priceList.append(price);

        }

        QStringList horHeader;
        horHeader<<"产品"<<"价格";
        ui->tableWidget-> setHorizontalHeaderLabels(horHeader);
        ui->tableWidget->setRowCount(nameList.size());
        ui->tableWidget->setColumnCount(2);
        ui->tableWidget->setWindowTitle("产品列表");
        ui->tableWidget->resize(200, 150);  //设置表格

        for(int i=0;i<nameList.size();i++){
            QString name = nameList[i];
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(name));

            QString price = priceList[i];
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(price));
        }

        ui->tableWidget->show();
    }


    //关闭数据库
    database.close();
}

Product::~Product()
{
    delete ui;
}

void Product::on_pushButton_clicked()
{

    QString nameInput = ui->textEdit->toPlainText();
    qDebug()<<"nameInput "<<nameInput<<"!"<<endl;
    double priceInput = ui->textEdit_2->toPlainText().toDouble();
    qDebug()<<"priceInput "<<priceInput<<"!"<<endl;

    if(nameInput.length()>0 && priceInput>0){

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
        QString sql_string = QString("INSERT INTO product (name, price) VALUES(\"%1\",%2)").arg(nameInput).arg(priceInput);
        qDebug() << "sql_string" << sql_string;
        if(!sql_query.exec(sql_string))
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            ui->textEdit->clear();
            ui->textEdit_2->clear();
            qDebug() << "inserted SUCCESS!";
            //查询数据
            sql_query.exec("select * from product");
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                QStringList nameList;
                QStringList priceList;
                while(sql_query.next())
                {
                    QString name = sql_query.value(1).toString();
                    nameList.append(name);
                    QString price = sql_query.value(2).toString();
                    priceList.append(price);
                }
                QStringList horHeader;
                horHeader<<"产品"<<"价格";
                ui->tableWidget-> setHorizontalHeaderLabels(horHeader);
                ui->tableWidget->setRowCount(nameList.size());
                ui->tableWidget->setColumnCount(2);
                ui->tableWidget->setWindowTitle("产品列表");
                ui->tableWidget->resize(200, 150);  //设置表格

                for(int i=0;i<nameList.size();i++){
                    QString name = nameList[i];
                    ui->tableWidget->setItem(i,0,new QTableWidgetItem(name));
                    QString price = priceList[i];
                    ui->tableWidget->setItem(i,1,new QTableWidgetItem(price));
                }
                ui->tableWidget->show();
            }
            //关闭数据库
            database.close();
        }
    }else{
        //请输入员工姓名
    }
}
