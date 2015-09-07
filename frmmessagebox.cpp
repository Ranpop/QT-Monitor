#include "frmmessagebox.h"
#include "ui_frmmessagebox.h"
#include "iconhelper.h"
#include "myhelper.h"
#include "myapp.h"

frmMessageBox::frmMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMessageBox)
{
    ui->setupUi(this);
    this->InitStyle();
}

frmMessageBox::~frmMessageBox()
{
    delete ui;
}

void frmMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void frmMessageBox::InitStyle()
{
    this->setProperty("Form", true);
    //窗体居中显示
    myHelper::FormInCenter(this, myApp::DeskWidth, myApp::DeskHeight);
    this->mousePressed = false;
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置图形字体
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    //关联关闭按钮
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

void frmMessageBox::SetMessage(QString msg, int type)
{
    if (type == 0) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/info.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText("提示");
    } else if (type == 1) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/question.png);");
        ui->lab_Title->setText("询问");
    } else if (type == 2) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/error.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText("错误");
    }

    ui->labInfo->setText(msg);
    this->setWindowTitle(ui->lab_Title->text());
}

void frmMessageBox::on_btnOk_clicked()
{
    done(1);
    this->close();
}
