#include "switchbutton.h"

/* 说明:自定义开关按钮控件实现文件
 * 功能:用来控制配置文件的开关设置
 * 作者:刘典武  QQ:517216493
 * 时间:2013-12-19  检查:2014-1-10
 */
SwitchButton::SwitchButton(QWidget *parent): QPushButton(parent)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    isCheck = false;
    styleOn = "background-image: url(:/image/btncheckon.png); border: 0px;";
    styleOff = "background-image: url(:/image/btncheckoff.png); border: 0px;";

    setFocusPolicy(Qt::NoFocus);
    setFixedSize(87, 28); //不允许变化大小
    setStyleSheet(styleOff);//设置当前样式
    connect(this, SIGNAL(clicked()), this, SLOT(ChangeOnOff()));
}

void SwitchButton::ChangeOnOff()
{
    if (isCheck) {
        setStyleSheet(styleOff);
        isCheck = false;
    } else {
        setStyleSheet(styleOn);
        isCheck = true;
    }
}

//设置当前选中状态
void SwitchButton::SetCheck(bool isCheck)
{
    if (this->isCheck != isCheck) {
        this->isCheck = !isCheck;
        ChangeOnOff();
    }
}
