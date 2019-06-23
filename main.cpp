#include "mywidget.h"
#include <QApplication>
//添加头文件
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    a.setStyle(QStyleFactory::create("fusion"));   //修改风格2步
//    // 这里使用代码来运行 MySQL 数据库
//    QProcess process;
//    process.start("C:/Program Files/MySQL/MySQLServer/bin/mysqld.exe");
//    if (!createConnection()) return 1;


    //建立并打开数据库
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }


    //创建表格
    QSqlQuery sql_query;
    if(!sql_query.exec("create table employees(id INTEGER PRIMARY KEY AUTOINCREMENT, name text UNIQUE)"))
    {
        qDebug() << "Error: Fail to create table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "employees Table created!";
    }


    if(!sql_query.exec("create table product(id INTEGER PRIMARY KEY AUTOINCREMENT, name text UNIQUE, price double)"))
    {
        qDebug() << "Error: Fail to create table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "product Table created!";
    }



    if(!sql_query.exec("create table record(id INTEGER PRIMARY KEY AUTOINCREMENT, add_time date, em_name text, pr_name text, count int)"))
    {
        qDebug() << "Error: Fail to create table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "record Table created!";
    }

    if(!sql_query.exec("CREATE UNIQUE INDEX record_UK ON record(add_time,em_name,pr_name)"))
    {
        qDebug() << "Error: Fail to create UNIQUE."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "record Table created!";
    }









    MyWidget w;
    w.show();

    return a.exec();
}
