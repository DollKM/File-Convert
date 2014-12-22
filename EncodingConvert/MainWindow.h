#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExis);
    bool convertFile(const QString& src,const QString& dst);
private slots:
    void on_checkBox_clicked();
    
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
