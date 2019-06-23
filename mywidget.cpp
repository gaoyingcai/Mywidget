#include "mywidget.h"
#include "ui_mywidget.h"
//添加头文件
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "employees.h"
#include "product.h"
#include "record.h"

#include <qdir.h>
#include <QDesktopServices>
#include <QUrl>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{


    //建立并打开数据库


//    QDate begin_date = QDate::currentDate().addMonths(-1).addDays(1);//一个月前
    QDate begin_date = QDate::currentDate();//默认显示当天
    QDate end_date = QDate::currentDate();


    int days = begin_date.daysTo(end_date)+1;//算上最后一天
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
    QSqlQuery pr_sql_query;
    QSqlQuery em_sql_query;
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(days+4);
    ui->tableWidget->setWindowTitle("QTableWidget & Item");
    ui->tableWidget->resize(400, 300);  //设置表格
    //查询数据
    pr_sql_query.exec("select * from product");
    em_sql_query.exec("select * from employees");
    QStringList emNameList;
    QStringList prNameList;
    QStringList prPriceList;
    int em_count = 0;
    int pr_count = 0;
    QStringList verHeader;
    QStringList horHeader;
    if(!em_sql_query.exec() || !pr_sql_query.exec())
    {
        qDebug()<<pr_sql_query.lastError();
    }
    else
    {
        horHeader<<"姓名"<<"产品";
        for(int i=0;i<days;i++){
          horHeader<<begin_date.addDays(i).toString("yyyy-MM-dd");
        }
        horHeader<<"合计数量"<<"合计金额";


        while(pr_sql_query.next())
        {
            QString pr_name = pr_sql_query.value(1).toString();
            prNameList.append(pr_name);
            QString pr_price = pr_sql_query.value(2).toString();
            prPriceList.append(pr_price);
            pr_count++;
        }
        while(em_sql_query.next())
        {
            horHeader<<QString("%1").arg(em_count);
            QString emName = em_sql_query.value(1).toString();
            emNameList.append(emName);
            em_count++;
        }
    }


    ui->tableWidget->setRowCount(em_count*pr_count);
    ui->tableWidget->setVerticalHeaderLabels(verHeader);
    ui->tableWidget-> setHorizontalHeaderLabels(horHeader);
    for(int i=0;i<emNameList.size();i++){
        ui->tableWidget->setSpan(pr_count*i, 0, pr_count, 1);
        QString emName = emNameList[i];
        ui->tableWidget->setItem(pr_count*i,0,new QTableWidgetItem(emName));
        for(int j=0;j<prNameList.size();j++){
            QString prName = prNameList[j];
            qDebug() << "************";
            ui->tableWidget->setItem(pr_count*i+j,1,new QTableWidgetItem(prName));

            QSqlQuery re_sql_query;
            QString re_sql_query_string = QString("select * from record where em_name=\"%1\" and pr_name=\"%2\" and add_time >= %3 and add_time <= %4 order by add_time asc").arg(emName).arg(prName).arg(begin_date.toString("yyyyMMdd")).arg(end_date.toString("yyyyMMdd"));

            if(!re_sql_query.exec(re_sql_query_string))
            {
                qDebug() << re_sql_query.lastError();
            }
            else
            {
                int n = 2;//从零开始 第二格之后的是数量
                int total_count = 0;
                while(re_sql_query.next())
                {
                    QString re_count = re_sql_query.value(4).toString();
                    qDebug() << "***" << re_count << "sql_string" << re_sql_query_string;
                    ui->tableWidget->setItem(pr_count*i+j,n,new QTableWidgetItem(re_count));
                    total_count += re_count.toInt();
                    n++;
                }
                //合计
                ui->tableWidget->setItem(pr_count*i+j,n,new QTableWidgetItem(QString::number(total_count)));
                //合计金额
                QString pr_price = prPriceList[j];
                ui->tableWidget->setItem(pr_count*i+j,n+1,new QTableWidgetItem(QString::number(total_count*pr_price.toDouble())));
            }



        }
    }
    ui->tableWidget->show();

    //关闭数据库
    database.close();


    ui->begin_dateEdit->setDate(begin_date);
    ui->end_dateEdit->setDate(end_date);

}

MyWidget::~MyWidget()
{
    delete ui;
}

//员工
void MyWidget::on_pushButton_3_clicked()
{
    Employees em;
    em.exec();
}
//产品
void MyWidget::on_pushButton_2_clicked()
{
    Product pro;
    pro.exec();
}
//记账(条件为日期,员工,数量)
void MyWidget::on_pushButton_clicked()
{
    Record rec;
    rec.exec();
}

void MyWidget::on_pushButton_4_clicked()
{
    qDebug() << "Succeed to connect database.1" ;


    //建立并打开数据库
//    QDate begin_date = QDate::currentDate().addMonths(-1).addDays(1);//一个月前
    QDate begin_date = ui->begin_dateEdit->date();//默认显示当天
    QDate end_date = ui->end_dateEdit->date();


    int days = begin_date.daysTo(end_date)+1;//算上最后一天
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
    QSqlQuery pr_sql_query;
    QSqlQuery em_sql_query;
//    ui->setupUi(this);
//    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(days+4);
    ui->tableWidget->clear();
//    ui->tableWidget->setWindowTitle("QTableWidget & Item");
//    ui->tableWidget->resize(400, 300);  //设置表格

    //查询数据
    pr_sql_query.exec("select * from product");
    em_sql_query.exec("select * from employees");
    QStringList emNameList;
    QStringList prNameList;
    QStringList prPriceList;
    int em_count = 0;
    int pr_count = 0;
    QStringList verHeader;
    QStringList horHeader;
    if(!em_sql_query.exec() || !pr_sql_query.exec())
    {
        qDebug()<<pr_sql_query.lastError();
    }
    else
    {
        horHeader<<"姓名"<<"产品";
        for(int i=0;i<days;i++){
          horHeader<<begin_date.addDays(i).toString("yyyy-MM-dd");
        }
        horHeader<<"合计数量"<<"合计金额";


        while(pr_sql_query.next())
        {
            QString pr_name = pr_sql_query.value(1).toString();
            prNameList.append(pr_name);
            QString pr_price = pr_sql_query.value(2).toString();
            prPriceList.append(pr_price);
            pr_count++;
        }
        while(em_sql_query.next())
        {
            horHeader<<QString("%1").arg(em_count);
            QString emName = em_sql_query.value(1).toString();
            emNameList.append(emName);
            em_count++;
        }
    }


    ui->tableWidget->setRowCount(em_count*pr_count);
    ui->tableWidget->setVerticalHeaderLabels(verHeader);
    ui->tableWidget-> setHorizontalHeaderLabels(horHeader);
    for(int i=0;i<emNameList.size();i++){
        ui->tableWidget->setSpan(pr_count*i, 0, pr_count, 1);
        QString emName = emNameList[i];
        ui->tableWidget->setItem(pr_count*i,0,new QTableWidgetItem(emName));
        for(int j=0;j<prNameList.size();j++){
            QString prName = prNameList[j];
            qDebug() << "************";
            ui->tableWidget->setItem(pr_count*i+j,1,new QTableWidgetItem(prName));

            QSqlQuery re_sql_query;
            QString re_sql_query_string = QString("select * from record where em_name=\"%1\" and pr_name=\"%2\" and add_time >= %3 and add_time <= %4 order by add_time asc").arg(emName).arg(prName).arg(begin_date.toString("yyyyMMdd")).arg(end_date.toString("yyyyMMdd"));

            if(!re_sql_query.exec(re_sql_query_string))
            {
                qDebug() << re_sql_query.lastError();
            }
            else
            {
                int total_count = 0;
                while(re_sql_query.next())
                {
                    QString re_count = re_sql_query.value(4).toString();
                    QString addTimeString = re_sql_query.value(1).toString();
                    QDate addTime = QDate::fromString(addTimeString, "yyyyMMdd");
                    qDebug() << "addTime:" <<addTimeString;
                    int columes = begin_date.daysTo(addTime)+2; //第几列  时间戳加上前两列  再加上当天
                    ui->tableWidget->setItem(pr_count*i+j,columes,new QTableWidgetItem(re_count));
                    total_count += re_count.toInt();
                }
                //合计数量
                ui->tableWidget->setItem(pr_count*i+j,days+3-1,new QTableWidgetItem(QString::number(total_count)));
                //合计金额
                QString pr_price = prPriceList[j];
                qDebug() << "******price******"<<pr_price;
                ui->tableWidget->setItem(pr_count*i+j,days+3,new QTableWidgetItem(QString::number(total_count*pr_price.toDouble())));
            }



        }
    }
    ui->tableWidget->show();
    //关闭数据库
    database.close();

    ui->begin_dateEdit->setDate(begin_date);
    ui->end_dateEdit->setDate(end_date);
}

void MyWidget::on_downloadBtn_clicked()
{
    //先打开数据库
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









    // 获取当前日期
   QDateTime current_date_time =QDateTime::currentDateTime();
   QString current_date =current_date_time.toString("yyyy/MM/dd");
   QString filePath = "./record/" + current_date;
   QString fileName = "record.csv";

   QDir tempDir;
   //临时保存程序当前路径
   QString currentDir = tempDir.currentPath();
   //如果filePath路径不存在，创建它
   if(!tempDir.exists(filePath))
   {
       qDebug()<<QObject::tr("不存在该路径")<<endl;
       tempDir.mkpath(filePath);
   }

   QFile *tempFile = new QFile;
   //将程序的执行路径设置到filePath下
   tempDir.setCurrent(filePath);
   //此时，路径下没有fileName文件，使用下面代码在当前路径下创建文件

   if(!tempFile->exists(fileName))
   {
       qDebug()<<"创建文件";
       tempFile->setFileName(fileName);
   }

   QFile file(tempDir.currentPath()+"/"+fileName);
   file.open(QIODevice::ReadOnly | QIODevice::WriteOnly);

   //开始写数据**********************************************************************************************



   QString headerString = "姓名,产品";


   QDate begin_date = ui->begin_dateEdit->date();//默认显示当天
   QDate end_date = ui->end_dateEdit->date();


   int days = begin_date.daysTo(end_date)+1;//算上最后一天

   //创建表格
   QSqlQuery pr_sql_query;
   QSqlQuery em_sql_query;

   ui->tableWidget->setColumnCount(days+4);
   ui->tableWidget->clear();

   //查询数据
   pr_sql_query.exec("select * from product");
   em_sql_query.exec("select * from employees");
   QStringList emNameList;
   QStringList prNameList;
   QStringList prPriceList;
   int em_count = 0;
   int pr_count = 0;
   if(!em_sql_query.exec() || !pr_sql_query.exec())
   {
       qDebug()<<pr_sql_query.lastError();
   }
   else
   {
       for(int i=0;i<days;i++){
         headerString.append(","+begin_date.addDays(i).toString("yyyy-MM-dd"));
       }
       headerString.append(",合计数量,合计金额");
       file.write(headerString.toUtf8());

       while(pr_sql_query.next())
       {
           QString pr_name = pr_sql_query.value(1).toString();
           prNameList.append(pr_name);
           QString pr_price = pr_sql_query.value(2).toString();
           prPriceList.append(pr_price);
           pr_count++;
       }
       while(em_sql_query.next())
       {
           QString emName = em_sql_query.value(1).toString();
           emNameList.append(emName);
           em_count++;
       }
   }
   for(int i=0;i<emNameList.size();i++){
       QString emName = emNameList[i];
       for(int j=0;j<prNameList.size();j++){
           QString prName = prNameList[j];
           QString lineString = emName+","+prName;
           QSqlQuery re_sql_query;
           QString re_sql_query_string = QString("select * from record where em_name=\"%1\" and pr_name=\"%2\" and add_time >= %3 and add_time <= %4 order by add_time asc").arg(emName).arg(prName).arg(begin_date.toString("yyyyMMdd")).arg(end_date.toString("yyyyMMdd"));
           if(!re_sql_query.exec(re_sql_query_string))
           {
               qDebug() << re_sql_query.lastError();
           }
           else
           {
               int total_count = 0;
               while(re_sql_query.next())
               {
                   QString re_count = re_sql_query.value(4).toString();
                   lineString.append(","+re_count);
                   total_count += re_count.toInt();
               }
               //合计数量
               lineString.append(","+QString::number(total_count));
               //合计金额
               QString pr_price = prPriceList[j];
               lineString.append(","+QString::number(total_count*pr_price.toDouble()));
               file.write("\n");
               file.write(lineString.toUtf8());
           }
       }
   }
   //关闭数据库
   database.close();
   qDebug() << tempDir.currentPath()+"/"+fileName<<endl;
//   QDesktopServices::openUrl(QUrl(tempDir.currentPath()+"/"+fileName));
   QDesktopServices::openUrl(QUrl("/Volumes/data/Documents/"));

   //结束写数据**********************************************************************************************
   file.close();
   tempFile->close();
   //将程序当前路径设置为原来的路径
   tempDir.setCurrent(currentDir);



}
