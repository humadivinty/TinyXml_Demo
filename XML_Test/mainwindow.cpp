#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

long MainWindow::getFileSize(const char *FileName)
{
    FILE* tmpFile = fopen(FileName, "rb");
    if(tmpFile)
    {
        fseek(tmpFile, 0, SEEK_END);
        long fileSize = ftell(tmpFile);
        fclose(tmpFile);
        tmpFile = NULL;
        qDebug()<<fileSize;
        return fileSize;
    }
    else
    {
        qDebug()<<"open file failed.";
        return 0;
    }

}

TiXmlElement *MainWindow::FindElement(TiXmlElement *rootElement, const char *ElementName)
{
    if(rootElement == NULL || ElementName == NULL)
    {
        return NULL;
    }
    return NULL;
}

bool MainWindow::PrintXmlText(TiXmlElement *rootElement)
{
    if(rootElement == NULL)
    {
        return false;
    }
    if(rootElement->Attribute("name"))
    {
//        if(strcmp(rootElement->Attribute("name"), "CommGatewayEx") == 0)
//        {
//            qDebug()<<"find The element and the value is.";
//            TiXmlElement* tmpElement =  rootElement->FirstChildElement();
//            qDebug()<<tmpElement->GetText();
//            tmpElement->FirstChild()->SetValue("172.18.100.138");
//        }
        qDebug()<<rootElement->Attribute("name");
    }
    TiXmlElement* firstChild = rootElement->FirstChildElement();
    if(firstChild)
    {
        PrintXmlText(firstChild);
    }
    TiXmlElement* SiblingNode = rootElement->NextSiblingElement();
    if(SiblingNode)
    {
        PrintXmlText(SiblingNode);
    }
    return true;
}

void MainWindow::on_pushButton_clicked()
{
    QString qstrFilePath;
    qstrFilePath = QFileDialog::getOpenFileName();
    qDebug()<<qstrFilePath;
    ui->lineEdit->setText(qstrFilePath);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString qstrFileName = ui->lineEdit->text();
    char chFileName[260] = {0};
    sprintf(chFileName, "%s",qstrFileName.toStdString().c_str());
    qDebug()<<chFileName;

    long iFileSize = getFileSize(chFileName);
    qDebug()<<"FIle size = "<<iFileSize;
    char* pchXML = new char[iFileSize+1];
    memset(pchXML, 0, iFileSize+1);

    FILE* file_XML = fopen(chFileName, "rb");
    if(file_XML)
    {
        size_t size_Read =  fread(pchXML, 1, iFileSize, file_XML);
        pchXML[iFileSize]= 0;
        qDebug()<<"read size = "<<size_Read;
        fclose(file_XML);
        file_XML = NULL;
    }

    TiXmlDocument cXmlDoc;
    if(cXmlDoc.Parse(pchXML))
        //if(cXmlDoc.LoadFile(chFileName))
    {

        TiXmlElement* pSectionElement = cXmlDoc.RootElement();
        if(pSectionElement)
        {
            qDebug()<<"find the 'HvParamDoc' element.";
            PrintXmlText(pSectionElement);
        }
        else
        {
            qDebug()<<"find element failed.";
        }
    }
    else
    {
        qDebug()<<"parse failed";
    }

    TiXmlPrinter cTiPrint;
    cXmlDoc.Accept(&cTiPrint);


    qDebug()<<"origeSize = "<<iFileSize+1<< "final Size = "<<cTiPrint.Size();
    if(iFileSize+1 < cTiPrint.Size())
    {
        delete []pchXML;
        pchXML = NULL;
        pchXML = new char[cTiPrint.Size()];
        memset(pchXML, 0, cTiPrint.Size());
    }
    else
    {
        memset(pchXML, 0, iFileSize+1);
    }
    memcpy(pchXML,cTiPrint.CStr(), cTiPrint.Size() );

    FILE* file_L = fopen("./178.xml", "wb+");
    if(file_L)
    {
        size_t size_Read =  fwrite(pchXML, 1, cTiPrint.Size(), file_L);
        qDebug()<<"read size = "<<size_Read;
        fclose(file_L);
        file_L = NULL;
    }

}
