#include "mainwindow.h"
#include <QApplication>
#include "space.h"

void * root = NULL;

void * getRoot(){
    return root;
}

void setRoot(void* r){
    root = (space*)r;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
