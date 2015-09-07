#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>

/* 说明:自定义开关按钮控件头文件
 * 功能:用来控制配置文件的开关设置
 * 作者:刘典武  QQ:517216493
 * 时间:2013-12-19  检查:2014-1-10
 */
class SwitchButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = 0);

    //获取当前选中状态
    bool GetCheck() const {
        return isCheck;
    }

    //设置当前选中状态
    void SetCheck(bool isCheck);

private:
    bool isCheck;
    QString styleOn;
    QString styleOff;

signals:

private slots:
    void ChangeOnOff();

};

#endif //SWITCHBUTTON_H
