#include "mainwindow.h"
#include <thread>
#include "OptionLists.h"
#include<iostream>
#include "UtilityFunctions.h"
#include<fstream>
#include<QTextEdit>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ComplaintType->addItems(ComplaintTypes);
    on_Refresh_clicked();
    //QPixmap image(" ");
    //imageLabel->setPixmap(image);
    //imageLabel->setParent();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_SubmitButton_clicked()
{
    std::string ProblemType =  ui->ComplaintType->currentText().toStdString();
    std::string Description =  ui->ProblemDesc->toPlainText().toStdString();
    std::string USN = ui->USNTextBox->text().toStdString();
    std::string Contact = ui->Contact->text().toStdString();
    bool Public = ui->PublicCheckBox->isChecked();
    std::string Query;

    bool bValidData = MakeInsertQuery(Problem("",ProblemType, Description, "",USN,Contact,0,"",Public), Query);

    if(bValidData)
    {
        ui->ComplaintType->setCurrentText("");
        ui->ProblemDesc->setText("");
        ui->USNTextBox->setText("");
        ui->Contact->setText("");
        ui->PublicCheckBox->setChecked(0);
        std::fstream file;
        file.open("QueryToRun.txt", std::fstream::out | std::fstream::trunc);
        file<<Query;
        file.close();
        std::cout<<Query<<std::endl;
        system("Test.exe");
        EraseFile("ResultStatus.txt");
    }

}


void MainWindow::on_Refresh_clicked()
{
    std::string Query = "select* from problems;", result ;
    std::fstream file;
    file.open("QueryToRun.txt", std::fstream::out | std::fstream::trunc);
    file<<Query;
    file.close();
    system("Test.exe");
    if(WaitForResult())
    {
        result = ReadFile("Result.txt");
        EraseFile("Result.txt");
        EraseFile("ResultStatus.txt");
        std::vector<Problem> List;
        ParseQueryResult(List, result);
    }
}

