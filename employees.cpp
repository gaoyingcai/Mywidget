#include "employees.h"
#include "ui_employees.h"
//添加头文件
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


Employees::Employees(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employees)
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
    else
    {
        qDebug() << "Succeed to connect database." ;
    }

    //创建表格
    QSqlQuery sql_query;


//    string sqltext="select count (*) from tablename";
//    SqlConnection sqlcon=new SqlConnection(connectionStr);
//    sqlcon.open();
//    SqlCommand sqlcmd=new SqlCommand(sqltext,sqlcon);
//    int rows=(int)sqlcmd.ExecuteScalar();
//    sqlcon.close();
//    sqlcmd.Dispose();




    //查询数据
    sql_query.exec("select * from employees");
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        QStringList nameList;
        while(sql_query.next())
        {
            QString name = sql_query.value(1).toString();
            nameList.append(name);
        }

        QStringList horHeader;
        horHeader<<"姓名";
        ui->tableWidget-> setHorizontalHeaderLabels(horHeader);
        ui->tableWidget->setRowCount(nameList.size());
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setWindowTitle("员工列表");
        ui->tableWidget->resize(200, 150);  //设置表格

        for(int i=0;i<nameList.size();i++){
            QString name = nameList[i];
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(name));
        }

        ui->tableWidget->show();
    }


    //关闭数据库
    database.close();
}

Employees::~Employees()
{
    delete ui;
}

void Employees::on_pushButton_clicked()
{
    QString input = ui->textEdit->toPlainText();
    qDebug()<<"hello "<<input<<"!"<<endl;
    if(input.length()>0){

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
        QString sql_string = QString("INSERT INTO employees (name) VALUES(\"%1\")").arg(input);
        qDebug() << "sql_string" << sql_string;
        if(!sql_query.exec(sql_string))
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            ui->textEdit->clear();
            qDebug() << "inserted SUCCESS!";
            //查询数据
            sql_query.exec("select * from employees");
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                QStringList nameList;
                while(sql_query.next())
                {
                    qDebug()<<QString("x:%1").arg(sql_query.size());
                    QString name = sql_query.value(1).toString();
                    qDebug()<<"hello "<<name<<"!"<<endl;
                    nameList.append(name);
                }
                QStringList horHeader;
                horHeader<<"姓名";
                ui->tableWidget-> setHorizontalHeaderLabels(horHeader);
                ui->tableWidget->setRowCount(nameList.size());
                ui->tableWidget->setColumnCount(1);
                ui->tableWidget->setWindowTitle("员工列表");
                ui->tableWidget->resize(200, 150);  //设置表格

                for(int i=0;i<nameList.size();i++){
                    QString name = nameList[i];
                    ui->tableWidget->setItem(i,0,new QTableWidgetItem(name));
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

void Employees::on_pushButton_2_clicked()
{
//    //删除员工

//    //添加员工
//    //建立并打开数据库
//    QSqlDatabase database;
//    database = QSqlDatabase::addDatabase("QSQLITE");
//    database.setDatabaseName("MyDataBase.db");
//    if (!database.open())
//    {
//    qDebug() << "Error: Failed to connect database." << database.lastError();
//    }
//    else
//    {
//    qDebug() << "Succeed to connect database." ;
//    }

//    QSqlQuery sql_query;

//    //删除数据
//    sql_query.exec("delete from student where id = 1");
//    if(!sql_query.exec())
//    {
//        qDebug()<<sql_query.lastError();
//    }
//    else
//    {
//        qDebug()<<"deleted!";
//    }

}
