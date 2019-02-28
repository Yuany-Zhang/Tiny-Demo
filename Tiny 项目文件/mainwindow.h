#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool loadFile(const QString &fileName); //加载文件
    bool save(int witchfile);    //保存操作
    bool saveFile(const QString &fileName,int witchfile); //保存文件

private slots:
    void on_pushButton_2_clicked();     //退出程序

    void on_pushButton_clicked();       //打开源码

    void on_pushButton_3_clicked();     //保存源码

    void on_pushButton_5_clicked();  //保存语法树

    void on_pushButton_4_clicked(); //生成语法树

    void on_action_O_triggered();//状态栏的 文件里的 打开

    void on_action_triggered();//状态栏的 文件里的 关闭

    void on_actionVersion_triggered();//状态栏的 帮助按钮里的 版本信息

    void on_action_I_triggered();//状态栏的 帮助按钮里的 开发者信息

    void on_action_S_triggered(); //状态栏的 文件按钮里的 保存源码

    void on_action_T_triggered();//状态栏的 文件按钮里的 保存语法树

private:
    Ui::MainWindow *ui;
    QString curFile;    //保存当前文件的路径
    QString curFile_2;
    QLabel *statusLabel;    //在状态栏添加一个标签部件用来显示一般的提示信息
};

#endif // MAINWINDOW_H
