#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QLabel>
#include "mymain.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("TINY扩充语言的语法分析")); //设置程序的标题

    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);//禁止最大化按钮
    setFixedSize(this->width(),this->height());//禁止拖动窗口大小


    /**************在程序底部状态栏显示信息*****************/
    statusLabel = new QLabel;
    statusLabel->setMinimumSize(150,20);//设置标签最小大小
    statusLabel->setFrameShape(QFrame::WinPanel);   //设置标签形状
    statusLabel->setFrameShadow(QFrame::Sunken);    //设置标签阴影
    ui->statusBar->addWidget(statusLabel);
    statusLabel->setText(tr("华南师范大学计算机学院"));
    QLabel * permanent = new QLabel;
    permanent->setFrameStyle(QFrame::Box |QFrame::Sunken);
    permanent->setText(tr("<a href=\"http://www.scnu.edu.cn/\"> SCNU官网</a>"));
    permanent->setTextFormat(Qt::RichText);
    permanent->setOpenExternalLinks(true);
    ui->statusBar->addPermanentWidget(permanent);
     /*************************************************/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked() //t退出程序
{
    QMessageBox box;
    box.setWindowTitle(tr("警告"));
    box.setIcon(QMessageBox::Warning);
    box.setText(tr("确定要退出？"));
    QPushButton * yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
    box.addButton(tr("否(&N)"),QMessageBox::NoRole);

    box.exec();
    if(box.clickedButton()==yesBtn)
         QApplication::exit();
    return ;
}

bool MainWindow::loadFile(const QString &fileName)  //加载文件
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,tr("多文档编辑器"),tr("无法读取文件 %1:\n%2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    curFile = QFileInfo(fileName).canonicalFilePath();
  //  setWindowTitle(curFile);
    return true;
}

void MainWindow::on_pushButton_clicked()  //打开文件
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty()){
        loadFile(fileName);
        ui->textEdit->setVisible(true);
    }
}


bool MainWindow::save(int witchfile)//保存操作
{
    if(witchfile ==1 )
    {
             QString fileName = QFileDialog::getSaveFileName(this,tr("保存源码"),curFile);
             if(fileName.isEmpty())
                 return false;
             saveFile(fileName,witchfile);
            return  saveFile(curFile,witchfile);
    }
    if(witchfile==2)
    {
       QString fileName = QFileDialog::getSaveFileName(this,tr("保存语法树"),curFile_2);
       if(fileName.isEmpty())
             return false;
       return saveFile(fileName,witchfile);
    }
    return false;
}


bool MainWindow::saveFile(const QString &fileName,int witchfile)//保存文件
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,tr("多文档编辑器"),
                             tr("无法写入文件 %1: /n %2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    //鼠标指针变为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(witchfile==1)
     out<<ui->textEdit->toPlainText();
    else if(witchfile==2)
        out<<ui->textEdit_2->toPlainText();
    else
        return false;
    //鼠标恢复原来的状态
    QApplication::restoreOverrideCursor();


    //获取文件的标准路径
    if(witchfile==1)
        curFile = QFileInfo(fileName).canonicalFilePath();
    else if(witchfile==2)
        curFile_2 = QFileInfo(fileName).canonicalFilePath();
    else
        return false;
    return true;
}

void MainWindow::on_pushButton_3_clicked() //保存源码
{
    save(1);
}

void MainWindow::on_pushButton_5_clicked()  //保存语法树
{
    save(2);
}


void MainWindow::on_pushButton_4_clicked()//生成语法树
{
    QFile source_file("SAMPLE.txt");
    source_file.open(QFile::WriteOnly);
    QTextStream out(&source_file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    source_file.close();
    ui->textEdit_2->clear();
    syntree(); //调用语法树生成函数
    QFile file("syntax tree.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream read(&file);
        while(!read.atEnd())
        {
           ui->textEdit_2->append(read.readAll());
        }
    }
 //   ui->textEdit_2->append();

}

void MainWindow::on_action_O_triggered() //状态栏的 文件里的 打开
{
    on_pushButton_clicked();
}

void MainWindow::on_action_triggered()  //状态栏的 文件里的 关闭
{
    on_pushButton_2_clicked();
}

void MainWindow::on_actionVersion_triggered()  //状态栏的 帮助按钮里的 版本信息
{
    QMessageBox box;
    box.setWindowTitle("版本信息");
    box.setIcon(QMessageBox::Information);
    box.setText(tr("版本号：v1.0.1 \n开发时间：2017-11-20~2017-12-22"));
    QPushButton *Ok_Back = box.addButton(tr("好的"),QMessageBox::YesRole);
    box.exec();
    if(box.clickedButton()==Ok_Back)
        return ;
}

void MainWindow::on_action_I_triggered() //状态栏的 帮助按钮里的 开发者信息
{
    QMessageBox box;
    box.setWindowTitle("开发者信息");
    box.setIcon(QMessageBox::Information);
    box.setText(tr("学校：华南师范大学\n学院：计算机学院\n年级：2015级\n学号：20153704061\n姓名：张远忆\n指导老师：黄煜廉"));
    QPushButton *Ok_Back = box.addButton(tr("好的"),QMessageBox::YesRole);
    box.exec();
    if(box.clickedButton()==Ok_Back)
        return ;
}

void MainWindow::on_action_S_triggered()    //状态栏的 文件按钮里的 保存源码
{
    on_pushButton_3_clicked();
}

void MainWindow::on_action_T_triggered()  //状态栏的 文件按钮里的 保存语法树
{
    on_pushButton_5_clicked();
}
