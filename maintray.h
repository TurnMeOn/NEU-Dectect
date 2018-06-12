#ifndef MAINTRAY_H
#define MAINTRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <netcontroller.h>
#include <optionswindow.h>
#include <QSettings>
#include <QMessageBox>
#include <QTimer>
#include <QApplication>
#include <QFile>
#include <QDebug>

class MainTray: public QSystemTrayIcon
{
    Q_OBJECT
public:
    MainTray(QByteArray username, QByteArray password, QObject *parent = Q_NULLPTR);
    ~MainTray();
    enum TrafficState{Normal, Over, Nearly };

private:
    QMenu *menu, *infoMenu, *settingsMenu;
    QAction *loginAction, *logoutAction, *autoLogin, *optionsAction, *aboutAction, *quitAction;
    QAction *mbAction, *timeAction, *balanceAction, *ipAction, *bootAction, *muteAction;
    NetController *netctrl;
    QSettings settings;
    OptionsWindow opWindow;
    QTimer *autoLoginTimer; //自动重连定时器
    QFile *logFile;
    QTextStream *logOut;

    bool isForceLogout = false;
    bool isForceLogin = false;
    bool hasWarned = false;

    NetController::State currentState = NetController::Unknown;  //当前状态
    TrafficState trafficstate = Normal;

    void showToolTip(NetController::State state);
    void handleActivated(QSystemTrayIcon::ActivationReason reason);//处理左键单击、双击
    void showOptions(); //显示选项窗口
    void showAbout();   //显示关于窗口
    void setAutoStart(bool set);

    QByteArray user, passwd;
    int totalTraffic;
    int msgDur = 500;   //通知持续时间
    int checkInterval = 1000;   //查询状态定时器周期


signals:
    void exit();

private slots:
    void updateUserInfo(QByteArray id, QByteArray pass, int traffic);
    void handleState(NetController::State state);
    void handleInfo(QString mb, QString sec, QString balance, QString ip);
    void writeLog(QString content);

};

#endif // MAINTRAY_H
