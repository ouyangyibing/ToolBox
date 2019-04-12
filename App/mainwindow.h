#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPluginLoader;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slot_newInstance();

private:
    Ui::MainWindow *ui;

    QPluginLoader *loader;
};

#endif // MAINWINDOW_H
