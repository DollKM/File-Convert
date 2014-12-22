#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings set("default");
    ui->lineEdit->setText(set.value("inpath").toString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_clicked()
{
    ui->lineEdit->setText("");
}

void MainWindow::on_pushButton_clicked()
{
    QString path;
    if(ui->checkBox->isChecked())
    {
        path = QFileDialog::getExistingDirectory(this,"",ui->lineEdit->text());
    }
    else
    {
        path = QFileDialog::getOpenFileName(this,"",ui->lineEdit->text());
    }
    if(path != "")
    {
        ui->lineEdit->setText(path);
        QSettings set("default");
        set.setValue("inpath",path);
    }
}

//void findDir(const QString&path,)

void MainWindow::on_pushButton_2_clicked()
{
    QFileInfo info(ui->lineEdit->text());
    copyDirectoryFiles(info.filePath(),info.absolutePath()+"/output",true);
    QMessageBox msg(QMessageBox::Warning,"Finish","convert encode finished!");
    msg.exec();
}
bool MainWindow::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)  
{  
    QDir sourceDir(fromDir);  
    QDir targetDir(toDir);  
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */  
        if(!targetDir.mkdir(targetDir.absolutePath()))  
            return false;  
    }  
  
    QFileInfoList fileInfoList = sourceDir.entryInfoList();  
    foreach(QFileInfo fileInfo, fileInfoList){  
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")  
            continue;  
  
        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */  
            if(!copyDirectoryFiles(fileInfo.filePath(),   
                targetDir.filePath(fileInfo.fileName()),  
                coverFileIfExist))  
                return false;  
        }  
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */  
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){  
                targetDir.remove(fileInfo.fileName());   
            }  
  
            /// 进行文件convert
            if((fileInfo.suffix() == "tjs" ||
                    fileInfo.suffix() == "ks" )
                    && !convertFile(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))
            {
                return false;
            }
        }  
    }  
    return true;  
}  

bool MainWindow::convertFile(const QString& src,const QString& dst)
{
    QFile srcFile,dstFile;  
    QTextStream in,out; 
    srcFile.setFileName(src);  
    srcFile.open(QFile::ReadWrite);  
    in.setDevice(&srcFile);
    in.setCodec(ui->comboBox->currentText().toStdString().c_str());  
    QString tmpstr = in.readAll();  
    
    
    dstFile.setFileName(dst);  
    dstFile.open(QFile::ReadWrite |QFile::Truncate);  
    out.setDevice(&dstFile);  
    out.setCodec(ui->comboBox_2->currentText().toStdString().c_str());  
    out<<tmpstr;  
    srcFile.close();  
    dstFile.close();
    return true;
}

//void MainWindow::copyDir(const QString& path)
//{
//    QFileInfo info(path);
//    if(!info.exists())
//    {
//        return;
//    }
//    qDebug()<<info.absolutePath();
//    QDir dir;
//    dir.mkdir(info.absolutePath()+"/output");
    
//}
