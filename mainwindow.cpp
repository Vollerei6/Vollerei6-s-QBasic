#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "fstream"
#include "QMessageBox"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnRunCode, &QPushButton::clicked, this, &MainWindow::onRunClicked);
    connect(ui->btnClearCode, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->btnLoadCode, &QPushButton::clicked, this, &MainWindow::onLoadClicked);
    connect(ui->btnSaveCode, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdLineEdit_editingFinished()
{
    QString cmd = ui->cmdLineEdit->text();
    ui->cmdLineEdit->setText("");

    ui->CodeDisplay->append(cmd);
}

void MainWindow::onRunClicked()
{
    //TODO:获取codeDisplay内的所有代码，按顺序执行程序
}

void MainWindow::onClearClicked()
{
    ui->CodeDisplay->clear();
    ui->textBrowser->clear();
    ui->treeDisplay->clear();
}//清空codeDisplay/textBrowser/treeDisplay

void MainWindow::onLoadClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open");
    //直接调用操作系统的接口，通过图形化界面获取一个文件路径；
    QFile file(fileName);
    //把文件路径传入，构建一个QFile对象
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Failed to open file: " + file.errorString());
        return;
    }//尝试打开文件

    QTextStream stream(&file);//文件流，兼具ifstream和ofstream的读写功能
    QString text = stream.readAll();//读
    ui->CodeDisplay->setPlainText(text);//传入到文本编辑框内
}//从文件加载BASIC代码

void MainWindow::onSaveClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
    //还是读取文件路径，但是支持新建文件
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Failed to save file: " + file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << ui->CodeDisplay->toPlainText();//写入到指定路径的文件
}
