#include "applicationview.h"
#include "./ui_applicationview.h"

ApplicationView::ApplicationView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ApplicationView)
{
    ui->setupUi(this);
}

ApplicationView::~ApplicationView()
{
    delete ui;
}


void ApplicationView::on_generateMazePushButton_clicked()
{
    ui->mazeWidget->update();
}

