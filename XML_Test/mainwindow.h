#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tinyxml/tinyxml.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    long getFileSize(const char* FileName);
    TiXmlElement* FindElement(TiXmlElement* rootElement, const char* ElementName);

    //函数功能 ： 遍历XML文件，打印所有节点的name 属性值
    bool PrintXmlText(TiXmlElement* rootElement);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
