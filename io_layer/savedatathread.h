#ifndef SAVEIMAGETHREAD_H
#define SAVEIMAGETHREAD_H

#include <QThread>
#include <QVector>
#include "ibasestruct.h"
#include <QMutex>
#include <QDir>
#include <QStringList>

//保存数据线程，定时调用，保存数据至文件
class SaveDataThread : public QThread
{
    Q_OBJECT
    static SaveDataThread* m_pInstacne;
public:
    explicit SaveDataThread(QObject *parent = 0);
    static SaveDataThread* GetInstance();
    ~SaveDataThread();

    void Add(shared_img_st* imgdata);
    void Add(QVector<shared_marker_st>& marker);
    void Add(QVector<shared_line_st>& line);
    void Add(QVector<shared_bracket_st>& bracket);
    void Add(QVector<shared_obstacle_st>& obstacle);
    QString getImgFileName();
    void Stop();
    static bool m_imagePingPang;
    static bool GetImagePingPangStatus();

signals:
   // void imageReady();

public slots:
protected:
    void run();
    void AutoRemoveImageDatas(QString strDir);
    bool removeDirectory(QString dirName);
    void CreateDataFile();
private:
    void SaveImg();
    QVector<shared_img_st*> m_imageBuffer;
    QVector<shared_img_st*> m_imageProcess;
    QMutex mutex_img;

    volatile bool bStop;
    //保存最新的图像路径
    QString m_imageFileNamePing;
    QString m_imageFileNamePang;
    QString m_strDir;
    long m_imgIndex;

    void SaveMarker();
    QVector<shared_marker_st> m_marketInfo;
    QMutex mutex_market;
    QFile fileMarker;

    void SaveLine();
    QVector<shared_line_st> m_lineInfo;
    QMutex mutex_line;
    QFile fileLine;

    void SaveBracket();
    QVector<shared_bracket_st> m_bracketInfo;
    QMutex mutex_bracket;
    QFile fileBracket;

    void SaveObstacle();
    QVector<shared_obstacle_st> m_obstacleInfo;
    QMutex mutex_obstacle;
    QFile fileObstacle;
};

#endif // SAVEIMAGETHREAD_H
