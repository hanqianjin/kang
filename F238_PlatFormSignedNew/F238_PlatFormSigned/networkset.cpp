#include "networkset.h"
#include "ui_networkset.h"
#include "shmengine.h"
#include <QDebug>
#include  <QHostAddress>
#include  <QNetworkInterface>
#include <qvalidator.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <QThread>
#include "multicommu/scpiport_internet.h"
#include "plugin/iplineedit.h"
#include "plugin/smkeyboard.h"
#include "plugin/pltkeyboard.h"
#include "module/wificonnect.h"
static QList<SSIDInfo> scan_list;
extern ScpiPort_internet   *g_pPortInterNet;
networkset::networkset(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::networkset)
{
    setWindowFlags(Qt::WindowDoesNotAcceptFocus);

    ui->setupUi(this);
    QRegExp rx("(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");

    ui->lineEdit->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_2->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_3->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_4->setValidator(new QRegExpValidator(rx, this));

    ui->lineEdit_5->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_6->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_7->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_8->setValidator(new QRegExpValidator(rx, this));

    ui->lineEdit_9->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_10->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_11->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_12->setValidator(new QRegExpValidator(rx, this));

    IPsetup = new QMap<IPLineEdit*,qint32>;
    IPsetup->insert(ui->lineEdit,1);
    IPsetup->insert(ui->lineEdit_4,2);
    IPsetup->insert(ui->lineEdit_5,3);
    IPsetup->insert(ui->lineEdit_6,4);

    IPsetup->insert(ui->lineEdit_2,5);
    IPsetup->insert(ui->lineEdit_9,6);
    IPsetup->insert(ui->lineEdit_7,7);
    IPsetup->insert(ui->lineEdit_8,8);

    IPsetup->insert(ui->lineEdit_3,9);
    IPsetup->insert(ui->lineEdit_12,10);
    IPsetup->insert(ui->lineEdit_10,11);
    IPsetup->insert(ui->lineEdit_11,12);

    mKeyBoard = new SmKeyBoard(this);
    mKeyBoard->hide();

    mPltKeyBoard = new pltKeyBoard(this);

    mPltKeyBoard->move(mapToGlobal(QPoint(1,333)).x(),mapToGlobal(QPoint(1,333)).y());
    mPltKeyBoard->hide();

    for(qint32 i=0;i<12;i++)
    {
        connect(IPsetup->keys().at(i),SIGNAL(ipEvent(qint32)),this,SLOT(on_ipEvent(qint32)));
    }

    QValidator* validator = new QIntValidator(1025, 65534, this);
    ui->lineEdit_14->setValidator(validator);

    initWifiWidget();

    mWifiTimer = new QTimer();
    connect(mWifiTimer,SIGNAL(timeout()),this,SLOT(on_wifiTimeout()));
#ifdef USB_SPEED_TEST
    mUSB = new testUSB();
    connect(mUSB,SIGNAL(testOnce(QString,QString)),this,SLOT(on_USBtest(QString,QString)));
    connect(mUSB,SIGNAL(StatusUpdated(qint32)),this,SLOT(on_USBstatus(qint32)));
    on_USBstatus(mUSB->getUSBstatus());
    ui->lblrS->setVisible(false);
    ui->lblrSpeed->setVisible(false);
    ui->lblwS->setVisible(false);
    ui->lblwSpeed->setVisible(false);
#endif
}


networkset::~networkset()
{    
    delete mWifiTimer;
    delete mPltKeyBoard;
    delete mKeyBoard;
    delete IPsetup;
    delete ui;
}

void networkset::SetPluginProperty(const char* name, QString value)
{
    mPltKeyBoard->setProperty(name,value);
    mKeyBoard->setProperty(name,value);
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-09}
*/
void networkset::ReflesGpsLabelStatus(qint32 istatus)
{
    //when on
    if(istatus)
    {
        QString strLatitude = "";
        QString strLongtitude = "";
        //Latitude
        strLatitude = QString(QLatin1String(shmengine::getsingleshm()->pshm_sysinfo->GPSLatitude));
        strLatitude = ChangeGPSDisFormat(strLatitude);
        this->ui->label_2->setText(strLatitude);
//        this->ui->label_2->setText(QString(QLatin1String(shmengine::getsingleshm()->pshm_sysinfo->GPSLatitude)));
        //Elevation
        this->ui->label_7->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->GPSElevation) + " m");
        //Gps Speed
        this->ui->label_9->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->GpsSpeedKmh) + " km/h");
        //Satellites in use
        this->ui->label_30->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->GPSSatelliteNum));
        //Operation Mode
        if(shmengine::getsingleshm()->pshm_sysinfo->GpsOperMode >= PTY1 && shmengine::getsingleshm()->pshm_sysinfo->GpsOperMode <= PTY3)
        {
            this->ui->label_32->setText(GpsOperMod[shmengine::getsingleshm()->pshm_sysinfo->GpsOperMode]);
        }
        else
        {
            this->ui->label_32->setText("-- --");
        }
        //Longtitude
        strLongtitude = QString(QLatin1String(shmengine::getsingleshm()->pshm_sysinfo->GPSLongitude));
        strLongtitude = ChangeGPSDisFormat(strLongtitude);
        this->ui->label_37->setText(strLongtitude);
//        this->ui->label_37->setText(QString(QLatin1String(shmengine::getsingleshm()->pshm_sysinfo->GPSLongitude)));
        //PRN number
        this->ui->label_33->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->GpsPrnNumber));
        //UTC Date
        this->ui->label_40->setText(QString(QLatin1String(shmengine::getsingleshm()->pshm_sysinfo->GPSDate)));
        //Gps Direction
        this->ui->label_41->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->GpsDirection) + " deg");
        //Satellites in view
        this->ui->label_42->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->GPSInView));
        //Gps Quality
        if(shmengine::getsingleshm()->pshm_sysinfo->GPSStatus >= PTY0 && shmengine::getsingleshm()->pshm_sysinfo->GPSStatus <= PTY3)
        {
            this->ui->label_43->setText(GpsQos[shmengine::getsingleshm()->pshm_sysinfo->GPSStatus]);
        }
        else
        {
            this->ui->label_43->setText("-- --");
        }
        //UTC
        this->ui->label_44->setText(QString(QLatin1String(shmengine::getsingleshm()->pshm_sysinfo->GPSTime)));
    }
    else
    {
        this->ui->label_2->setText("-- --");
        this->ui->label_7->setText("-- --");
        this->ui->label_9->setText("-- --");
        this->ui->label_30->setText("-- --");
        this->ui->label_32->setText("-- --");
        this->ui->label_37->setText("-- --");
        this->ui->label_33->setText("-- --");
        this->ui->label_40->setText("-- --");
        this->ui->label_41->setText("-- --");
        this->ui->label_42->setText("-- --");
        this->ui->label_43->setText("-- --");
        this->ui->label_44->setText("-- --");
    }
}

void networkset::on_blutoothofbtn_clicked()
{
    *pltnet.bluswi = !*pltnet.bluswi;
    if(*pltnet.bluswi)
    {
        BlueStyleOn();
        SetBlutoothOn(true);
    }
    else
    {
        BlueStyleOff();
        SetBlutoothOn(false);
    }
    
    shmengine::getsingleshm()->pshm_sysconf->bluetwitch = *pltnet.bluswi;
    return;
}

void networkset::on_wifiofbtn_clicked()
{
    *pltnet.wifiswi = !*pltnet.wifiswi;
    shmengine::getsingleshm()->pshm_sysconf->wifiswitch = *pltnet.wifiswi;
    shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_WIFI);
    QThread::usleep(50000);
    if(*pltnet.wifiswi)
    {
        WifiStyleOn();
        //open wifi
        SetWifiOn(true);
    }
    else
    {
        WifiStyleOff();
        //close wifi
        SetWifiOn(false);
    }

    return;
}

void networkset::on_gpsbtn_clicked()
{  
    if(*pltnet.gpswi)
    {
        *pltnet.gpswi = !*pltnet.gpswi;
        QThread::msleep(PLTQUERY);
        shmengine::getsingleshm()->pshm_sysconf->Gpswitch = *pltnet.gpswi;
        shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_GPSWitch);
    }
    else
    {
        shmengine::getsingleshm()->pshm_sysconf->Gpswitch = !*pltnet.gpswi;
        shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_GPSWitch);
        QThread::msleep(PLTQUERY);
        *pltnet.gpswi = !*pltnet.gpswi;
    }

    if(*pltnet.gpswi)
    {
        GpsStyleOn();
    }
    else
    {
        GpsStyleOff();
    }
    return;
}

void networkset::on_netsetbtn_clicked()
{
    //this->setCursor(Qt::WaitCursor);
    g_pPortInterNet->closeBitConn();
    QString tempaddr = ui->lineEdit->text()+"."+ui->lineEdit_4->text()+"."
            +ui->lineEdit_5->text()+"."+ui->lineEdit_6->text();
    if(!SetIPAddress(tempaddr))
    {
        //this->setCursor(Qt::ArrowCursor);
        return;
    }
    tempaddr = ui->lineEdit_2->text()+"."+ui->lineEdit_9->text()+"."
            +ui->lineEdit_7->text()+"."+ui->lineEdit_8->text();
    if(!SetMaskAddress(tempaddr))
    {
//        this->setCursor(Qt::ArrowCursor);
        return;
    }
    tempaddr = ui->lineEdit_3->text()+"."+ui->lineEdit_12->text()+"."
            +ui->lineEdit_10->text()+"."+ui->lineEdit_11->text();
    if(!SetGateWayAddress(tempaddr))
    {
//        this->setCursor(Qt::ArrowCursor);
        return;
    }
    g_pPortInterNet->buildBitConn();
//    this->setCursor(Qt::ArrowCursor);
}

bool networkset::SetIPAddress(QString ipaddr)
{
    const char *p = ipaddr.toStdString().data();
    sprintf(pltnet.ipName,"%s",p);
    ipName = ipaddr;
    QString mIpAddress;
    QString mMaskAddress;
    QList<QNetworkInterface>  list  =  QNetworkInterface::allInterfaces();
    for(qint32  i=0;  i<list.count();  i++)
    {
        QNetworkInterface  interface  =  list.at(i);
        QList<QNetworkAddressEntry>  entryList  =  interface.addressEntries();

        foreach(QNetworkAddressEntry  ipv4entry,  entryList){
            if  (ipv4entry.ip().toIPv4Address())
            {
                strHostName  =  interface.name();
                mIpAddress  =  ipv4entry.ip().toString();
                mMaskAddress  =  ipv4entry.netmask().toString();
            }
        }
    }
    QString  cmd  =  QString("ifconfig  ")  +  strHostName  +  QString("  ")  +  ipName;
    std::string  str  =  cmd.toStdString();
    const  char*  pCmd  =  str.c_str();
    qint32  error  =  system(pCmd);
    if(error != -1 && WIFEXITED(error) && !WEXITSTATUS(error))
    {
        return true;
    }
    else
    {        
        qCritical("16");
        setNoticePara(PTY1,PTY3,16,PLT_EXCE_SOURCE);
        shmengine::getsingleshm()->pshm_pltnotic->noticode = GetNoticeCode();
        return false;
    }
}

bool networkset::SetMaskAddress(QString strMask)
{
    const char *p = strMask.toStdString().data();
    sprintf(pltnet.strmaskName,"%s",p);
    QString cmd;
    cmd = QString("ifconfig ") + strHostName + QString(" netmask ") + strMask;
    std::string str = cmd.toStdString();
    const char* pCmd = str.c_str();
    qint32 error = system(pCmd);
    if(error != -1 && WIFEXITED(error) && !WEXITSTATUS(error))
    {
        return true;
    }
    else
    {
        qCritical("17");
        setNoticePara(PTY1,PTY3,17,PLT_EXCE_SOURCE);
        shmengine::getsingleshm()->pshm_pltnotic->noticode = GetNoticeCode();
        return false;
    }
}

bool networkset::SetGateWayAddress(QString strGateWay)
{
    //! del cur gateway before set
    const char *p = strGateWay.toStdString().data();
    sprintf(pltnet.strGateWayName,"%s",p);
    DelPreGateWay();
    strGateWayName = strGateWay;
    QString cmd;
    cmd = QString("route add default gw ") + strGateWay;
    std::string str = cmd.toStdString();
    const char* pCmd = str.c_str();
    qint32 error = system(pCmd);
    if(error != -1 && WIFEXITED(error) && !WEXITSTATUS(error))
    {
        return true;
    }
    else
    {
        qCritical("18");
        setNoticePara(PTY1,PTY3,18,PLT_EXCE_SOURCE);
        shmengine::getsingleshm()->pshm_pltnotic->noticode = GetNoticeCode();
        return false;
    }
}

void networkset::SetIpBtnWord(QString str)
{
    QStringList mlist = str.split('.');
    this->ui->lineEdit->setText(mlist.at(0));
    this->ui->lineEdit_4->setText(mlist.at(1));
    this->ui->lineEdit_5->setText(mlist.at(2));
    this->ui->lineEdit_6->setText(mlist.at(3));
}

void networkset::SetMaskBtnWord(QString str)
{
    QStringList mlist = str.split('.');
    this->ui->lineEdit_2->setText(mlist.at(0));
    this->ui->lineEdit_9->setText(mlist.at(1));
    this->ui->lineEdit_7->setText(mlist.at(2));
    this->ui->lineEdit_8->setText(mlist.at(3));
}

void networkset::SetGateBtnWord(QString str)
{
    QStringList mlist = str.split('.');
    this->ui->lineEdit_3->setText(mlist.at(0));
    this->ui->lineEdit_12->setText(mlist.at(1));
    this->ui->lineEdit_10->setText(mlist.at(2));
    this->ui->lineEdit_11->setText(mlist.at(3));
}

void networkset::GpsStyleOn()
{
    QString mstr = "#networkset[pltdismode=\"indoor\"] ";
    QString qstr = QString("QPushButton{background-image: url(:/bit/image/btn_radio_on_w90.png);border-style: flat;\
                           background-color: transparent;}\n");
QString mstr1 = "#networkset[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{background-image: url(:/bit/image/night_On.png);border-style: flat;\
                        background-color: transparent;}\n");
this->ui->gpsbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
}

void networkset::GpsStyleOff()
{
    QString mstr = "#networkset[pltdismode=\"indoor\"] ";
    QString qstr = QString("QPushButton{background-image: url(:/bit/image/btn_radio_off_w90.png);border-style: flat;\
                           background-color: transparent;}\n");
QString mstr1 = "#networkset[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{background-image: url(:/bit/image/night_Off.png);border-style: flat;\
                        background-color: transparent;}\n");
this->ui->gpsbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
}

void networkset::WifiStyleOn()
{
    ui->lblWifiLIst->setVisible(true);
    ui->pb_wifi_refresh->setVisible(true);
    ui->tableWidget->setVisible(true);
    ui->lblCurWifi->setVisible(true);
    QString mstr = "#networkset[pltdismode=\"indoor\"] ";
    QString qstr = QString("QPushButton{background-image: url(:/bit/image/btn_radio_on_w90.png);border-style: flat;\
                           background-color: transparent;}\n");
QString mstr1 = "#networkset[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{background-image: url(:/bit/image/night_On.png);border-style: flat;\
                        background-color: transparent;}\n");
this->ui->wifiofbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
}

void networkset::WifiStyleOff()
{
    ui->lblWifiLIst->setVisible(false);
    ui->pb_wifi_refresh->setVisible(false);
    ui->tableWidget->setVisible(false);
    ui->lblCurWifi->setVisible(false);
    QString mstr = "#networkset[pltdismode=\"indoor\"] ";
    QString qstr = QString("QPushButton{background-image: url(:/bit/image/btn_radio_off_w90.png);border-style: flat;\
                           background-color: transparent;}\n");
QString mstr1 = "#networkset[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{background-image: url(:/bit/image/night_Off.png);border-style: flat;\
                        background-color: transparent;}\n");
this->ui->wifiofbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
}

void networkset::BlueStyleOn()
{
    QString mstr = "#networkset[pltdismode=\"indoor\"] ";
    QString qstr = QString("QPushButton{background-image: url(:/bit/image/btn_radio_on_w90.png);border-style: flat;\
                           background-color: transparent;}\n");
QString mstr1 = "#networkset[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{background-image: url(:/bit/image/night_On.png);border-style: flat;\
                        background-color: transparent;}\n");
this->ui->blutoothofbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
}

void networkset::BlueStyleOff()
{
    QString mstr = "#networkset[pltdismode=\"indoor\"] ";
    QString qstr = QString("QPushButton{background-image: url(:/bit/image/btn_radio_off_w90.png);border-style: flat;\
                           background-color: transparent;}\n");
QString mstr1 = "#networkset[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{background-image: url(:/bit/image/night_Off.png);border-style: flat;\
                        background-color: transparent;}\n");
this->ui->blutoothofbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note UNDO ACTION
 * @since {2019-09-18}
*/
bool networkset::SetWifiSwitchAction(qint32 iswitch)
{
  if(iswitch)
    {
      WifiStyleOn();
    }
  else
    {
      WifiStyleOff();
    }
  shmengine::getsingleshm()->pshm_sysconf->wifiswitch = iswitch;
  shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_WIFI);
  return true;
}

//UNDO ACTION
bool networkset::SetWifiMibAction(QString mibstr)
{
  ui->lineEdit_13->setText(mibstr);
  return true;
}

//UNDO ACTION
bool networkset::SetBltSwitchAction(qint32 iswitch)
{
  if(iswitch)
    {
      BlueStyleOn();
    }
  else
    {
      BlueStyleOff();
    }
  shmengine::getsingleshm()->pshm_sysconf->bluetwitch = iswitch;
  return true;
}

void networkset::DelPreGateWay()
{
    QString pCmd;
    if(strGateWayName.isEmpty())
        return;
    qint32 ret = 0;
    char* cmd;

    pCmd = QString("route del default gw ") + strGateWayName;
    QByteArray ba = pCmd.toLatin1();
    cmd = ba.data();
    ret = system(cmd);
    if(ret < 0)
    {
        perror("route error");
        return;
    }
    return;
}

void networkset::SetGpsSwitch(qint32 iswitch)
{
    if(iswitch != PTY0 && iswitch != PTY1)
        return;

    if(!iswitch)
    {
        //when close first not read
        *pltnet.gpswi = iswitch;
        QThread::msleep(PLTQUERY);
        shmengine::getsingleshm()->pshm_sysconf->Gpswitch = iswitch;
        shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_GPSWitch);
    }
    else
    {
        //when open first enable
        shmengine::getsingleshm()->pshm_sysconf->Gpswitch = iswitch;
        shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_GPSWitch);
        QThread::msleep(PLTQUERY);
        *pltnet.gpswi = iswitch;
    }

    if(*pltnet.gpswi)
    {
        GpsStyleOn();
    }
    else
    {
        GpsStyleOff();
    }
    return;
}

bool networkset::SetIPAddressEx(QString ipaddr)
{
    SetIpBtnWord(ipaddr);
    g_pPortInterNet->closeBitConn();
    if(!SetIPAddress(ipaddr))
    {
        return false;
    }
    g_pPortInterNet->buildBitConn();
    return true;
}

bool networkset::SetMaskAddressEx(QString strMask)
{
    SetMaskBtnWord(strMask);
    g_pPortInterNet->closeBitConn();
    if(!SetMaskAddress(strMask))
    {
        return false;
    }
    g_pPortInterNet->buildBitConn();
    return true;
}

bool networkset::SetGateWayAddressEx(QString strGateWay)
{
    SetGateBtnWord(strGateWay);
    g_pPortInterNet->closeBitConn();
    if(!SetGateWayAddress(strGateWay))
    {
        return false;
    }
    g_pPortInterNet->buildBitConn();
    return true;
}

bool networkset::SetLanPort(qint32 port)
{
    if(port < 1025 || port > 65534)
    {
        return false;
    }
    ui->lineEdit_14->setText(QString::number(port));
    g_pPortInterNet->closeBitConn();
    *pltnet.port = port;
    g_pPortInterNet->buildBitConn();
    return true;
}

bool networkset::SetWifiSwitch(qint32 iswitch)
{
  if(iswitch != PTY0 && iswitch != PTY1)
    return false;
  *pltnet.wifiswi = iswitch;
  return SetWifiSwitchAction(*pltnet.wifiswi);
}

bool networkset::SetWifiMib(QString mibstr)
{
  const char *p = mibstr.toStdString().data();
  sprintf(pltnet.strwifimib,"%s",p);
  return SetWifiMibAction(mibstr);
}

bool networkset::SetBltSwitch(qint32 iswitch)
{
  if(iswitch != PTY0 && iswitch != PTY1)
    return false;
  *pltnet.bluswi = iswitch;
  return SetBltSwitchAction(*pltnet.bluswi);
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-23}
*/
void networkset::SetGpsBtn(qint32 *iIndex)
{
    if(!*iIndex)
    {
        //when close first not read
        pltnet.gpswi = iIndex;
        QThread::msleep(PLTQUERY);
        shmengine::getsingleshm()->pshm_sysconf->Gpswitch = *iIndex;
        shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_GPSWitch);
    }
    else
    {
        //when open first enable
        shmengine::getsingleshm()->pshm_sysconf->Gpswitch = *iIndex;
        shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_GPSWitch);
        QThread::msleep(PLTQUERY);
        pltnet.gpswi = iIndex;
    }

    if(*pltnet.gpswi)
    {
        GpsStyleOn();
    }
    else
    {
        GpsStyleOff();
    }
    return;
}

void networkset::SetIpBtn(char *p)
{
    pltnet.ipName = p;
    QString mstr = QString(QLatin1String(p));
    SetIpBtnWord(mstr);
    g_pPortInterNet->closeBitConn();
    if(!SetIPAddress(mstr))
    {
        return;
    }
}

void networkset::SetMaskBtn(char *p)
{
    pltnet.strmaskName = p;
    QString mstr = QString(QLatin1String(p));
    SetMaskBtnWord(mstr);
    g_pPortInterNet->closeBitConn();
    if(!SetMaskAddress(mstr))
    {
        return;
    }
}

void networkset::SetGateBtn(char *p)
{
    pltnet.strGateWayName = p;
    strGateWayName = QString(QLatin1String(p));
    SetGateBtnWord(strGateWayName);
    g_pPortInterNet->closeBitConn();
    if(!SetGateWayAddress(strGateWayName))
    {
        return;
    }
    g_pPortInterNet->buildBitConn();
}

void networkset::SetPortBtn(qint32 *iport)
{
    pltnet.port = iport;
    this->ui->lineEdit_14->setText(QString::number(*iport));
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-18}
*/
void networkset::SetRemoteBtn(qint32 *iIndex)
{
  pltnet.premotemode = iIndex;
  if(PTY0 == *iIndex)
    {
      this->ui->label_5->setText(tr("Ethernet Configration"));
      this->ui->stackedWidget->setCurrentIndex(PTY0);
      this->ui->pushButton_7->setChecked(true);
    }
  else if(PTY1 == *iIndex)
    {
      this->ui->label_5->setText(tr("Bluetooth Configration"));
      this->ui->stackedWidget->setCurrentIndex(PTY1);
      this->ui->pushButton_8->setChecked(true);
    }
  else
    {
      this->ui->label_5->setText(tr("Wi-Fi Configuration "));
      this->ui->stackedWidget->setCurrentIndex(PTY2);
      this->ui->pushButton_9->setChecked(true);
    }
  return;
}

void networkset::SetWifiSwitchBtn(qint32 *iswitch)
{
  pltnet.wifiswi = iswitch;
  SetWifiSwitchAction(*pltnet.wifiswi);
  return;
}

void networkset::SetWifiMibBtn(char *p)
{
  pltnet.strwifimib = p;
  QString mstr = QString(QLatin1String(p));
  SetWifiMibAction(mstr);
  return;
}

void networkset::SetBltSwitchBtn(qint32 *iswitch)
{
  pltnet.bluswi = iswitch;
  SetBltSwitchAction(*pltnet.bluswi);
  return;
}

void networkset::keyPressEvent(QKeyEvent *event)
{
    qint32 keyVal = event->key();
    if(keyVal == Qt::Key_Escape)
    {
        //use “isHidden()” to ensure form hiding
        if(!mKeyBoard->isHidden())
        {
            mKeyBoard->hide();
            return;
        }

        if(!mPltKeyBoard->isHidden())
        {
            mPltKeyBoard->hide();
            return;
        }
    }
    return QWidget::keyPressEvent(event);
}

void networkset::showKeyBoard()
{
    //qApp->focusChanged();
    IPLineEdit* edit = qobject_cast<IPLineEdit*>(sender());
    qint32 editID = IPsetup->value(edit);
    if(editID<=4)
    {
        mKeyBoard->move(522,86);
        mKeyBoard->setTitle("IP Address");
    }else if(editID<=8)
    {
        mKeyBoard->move(522,150);
        mKeyBoard->setTitle("Net Mask");
    }else
    {
        mKeyBoard->move(522,214);
        mKeyBoard->setTitle("Gateway");
    }
    if(!mKeyBoard->isVisible())
    {
        mKeyBoard->show();
    }
}

void networkset::hideKeyBoard()
{
    if(mKeyBoard->isVisible())
    {
        mKeyBoard->hide();
    }
}
void networkset::on_ipEvent(qint32 type)
{
    IPLineEdit* edit = qobject_cast<IPLineEdit*>(sender());
    qint32 editID = IPsetup->value(edit);
    qint32 remainder = editID % 4;
    if(editID<1) //ID number starts at 1
    {
        return;
    }
    switch (type)
    {
    case 0://IPLineEdit::IP_NEXT_EDIT
        if(remainder != 0)
        {
            if(edit->text()=="") edit->setText("0");
            IPsetup->key(editID + 1)->setFocus();
        }
        break;
    case 1://IPLineEdit::IP_PREV_EDIT
        if(remainder != 1)
        {
            if(edit->text()=="") edit->setText("0");
            IPsetup->key(editID - 1)->setFocus();
        }
        break;
    case 2://IPLineEdit::IP_FINISH_EDIT:
        if(edit->text()=="") edit->setText("0");
        hideKeyBoard();
        break;
    case 3://IPLineEdit::IP_SHOW_KEYBOARD:
        showKeyBoard();
        break;
    default:
        break;
    }
}

void networkset::on_pushButton_7_clicked()
{
  *pltnet.premotemode = PTY0;
  this->ui->label_5->setText(tr("Ethernet Configration"));
  this->ui->stackedWidget->setCurrentIndex(PTY0); 
}

void networkset::on_pushButton_8_clicked()
{
  *pltnet.premotemode = PTY1;
  this->ui->label_5->setText(tr("Bluetooth Configration"));
  this->ui->stackedWidget->setCurrentIndex(PTY1);
}

void networkset::on_pushButton_9_clicked()
{
  *pltnet.premotemode = PTY2;
  this->ui->label_5->setText(tr("Wi-Fi Configuration"));
  this->ui->stackedWidget->setCurrentIndex(PTY2);
}

/**
 * @brief setting network port
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-06-27}
*/
void networkset::on_netsetbtn_2_clicked()
{
//  this->setCursor(Qt::WaitCursor);
  g_pPortInterNet->closeBitConn();
  *pltnet.port = this->ui->lineEdit_14->text().toInt();
  *pltnet.port = *pltnet.port < 1025 ? 1025 : *pltnet.port;
  this->ui->lineEdit_14->setText(QString::number(*pltnet.port));
  g_pPortInterNet->buildBitConn();
//  this->setCursor(Qt::ArrowCursor);
}

void networkset::on_lineEdit_14_loseFocus()
{
    *pltnet.port = this->ui->lineEdit_14->text().toInt();
    *pltnet.port = *pltnet.port < 1025 ? 1025 : *pltnet.port;
    this->ui->lineEdit_14->setText(QString::number(*pltnet.port));
    hideKeyBoard();
}

void networkset::on_lineEdit_14_clicked()
{
    mKeyBoard->move(522,276);
    mKeyBoard->setTitle("Port");
    if(!mKeyBoard->isVisible())
    {
        mKeyBoard->show();
    }
    ui->lineEdit_14->selectAll();
}

void networkset::on_wifiCilcked(qint32 wifiId)
{
    wireless_disconnect(netFd);
    netFd = -1;
    //打开wifi连接弹窗
    WifiConnect* wifiDialog = new WifiConnect(pWifiInfo,mPltKeyBoard,this);
    //wifiDialog->move(mapToParent(QPoint(0,0)).x(),mapToParent(QPoint(0,0)).y());
    wifiDialog->move(82,62);
//    mPltKeyBoard->show();
    netFd = wifiDialog->exec();

    StaStatus connectFlag;
    wireless_status(&connectFlag);
    if(connectFlag == STACONNECTED)
    {
        ui->tableWidget->setCurrentCell(wifiId,0);
        mWifiTimer->start(2000);
        ui->lblCurWifi->setText(QString(pWifiInfo->ssid));
    }else
    {
        ui->tableWidget->setCurrentCell(wifiId,1);
        ui->lblCurWifi->setText(QString(""));
    }
//    mPltKeyBoard->hide();
}

void networkset::on_wifiTimeout()
{
    StaStatus connectFlag;
    wireless_status(&connectFlag);
    if(connectFlag == STACONNECTED)
    {
        mWifiTimer->start(2000);
    }else
    {
        mWifiTimer->stop();
        ui->tableWidget->setCurrentCell(0,1);
        ui->lblCurWifi->setText(QString(""));
    }
}
void networkset::initWifiWidget()
{
    ui->label_27->setVisible(false);
    ui->lineEdit_13->setVisible(false);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection);
    //connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(on_wifiCilcked()));

    pWifiInfo = new SSIDInfo();
    netFd = -1;
    //Tony hide wifi scan display for default
//    ui->lblWifiLIst->setVisible(false);
//    ui->pb_wifi_refresh->setVisible(false);
//    ui->tableWidget->setVisible(false);

//    ui->lblBluMode->setVisible(false);
//    ui->pb_AMP->setVisible(false);
//    ui->pb_BLE->setVisible(false);
//    ui->lblDevName->setVisible(false);
//    ui->EditDevName_2->setVisible(false);
    ui->lblBluList->setVisible(false);
    ui->pb_blu_refresh->setVisible(false);
    ui->blu_1->setVisible(false);
    ui->blu_2->setVisible(false);
    ui->blu_3->setVisible(false);
    ui->blu_4->setVisible(false);
    ui->blu_5->setVisible(false);
}

void networkset::SetWifiOn(qint32 isOn)
{
    ui->lblWifiLIst->setVisible(isOn);
    ui->pb_wifi_refresh->setText("");
    ui->pb_wifi_refresh->setVisible(isOn);
    ui->tableWidget->setVisible(isOn);
    ui->lblCurWifi->setVisible(isOn);
#ifdef _linux_238_netctrl
    if(isOn)
    {
        wireless_open();
        wireless_set_sta();
        refreshWifiList();
    }else
    {
        wireless_disconnect(netFd);
        wireless_close();
        mWifiTimer->stop();
    }
#endif
}

void networkset::SetBlutoothOn(qint32 isOn)
{
    ui->lblBluMode->setVisible(isOn);
    ui->pb_AMP->setVisible(isOn);
    ui->pb_BLE->setVisible(isOn);
    ui->lblDevName->setVisible(isOn);
    ui->EditDevName_2->setVisible(isOn);
    ui->lblBluList->setVisible(isOn);
    ui->pb_blu_refresh->setVisible(isOn);
    ui->blu_1->setVisible(isOn);
    ui->blu_2->setVisible(isOn);
    ui->blu_3->setVisible(isOn);
    ui->blu_4->setVisible(isOn);
    ui->blu_5->setVisible(isOn);

#ifdef _linux_238_netctrl
    if(isOn)
    {

    }else
    {

    }
#endif
}
void networkset::refreshWifiList()
{
    //refresh wifi list
    //if (current_mode != WIRELESS_STA_MODE)
    //    return;
    ui->pb_wifi_refresh->setText("scanning");
    ui->pb_wifi_refresh->setEnabled(false);
    ui->lblCurWifi->setText(QString(""));
    ui->tableWidget->setEnabled(false);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    qint32 wifiCnt;
    scan_list.clear();
    wireless_scan(deal_scan);
    wifiCnt = scan_list.size();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(wifiCnt);
    for(qint32 i = 0;i< wifiCnt;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString(scan_list.at(i).ssid)));
    }
    ui->pb_wifi_refresh->setText("refresh");
    ui->pb_wifi_refresh->setEnabled(true);
    ui->tableWidget->setEnabled(true);
}

void networkset::on_pb_wifi_refresh_clicked()
{
    refreshWifiList();
}

void networkset::on_EditDevName_clicked()
{
    ui->EditDevName->selectAll();
    //打开键盘
    mPltKeyBoard->show();
}

void networkset::on_EditDevName_loseFocus()
{
    //关闭键盘
    mPltKeyBoard->hide();
}

qint32 networkset::deal_scan(void * pdata)
{
//    static SSIDInfo *data = (SSIDInfo *)pdata;
    scan_list.append(*(SSIDInfo *)pdata);
    return 0;
}

void networkset::on_tableWidget_cellClicked(int row, int column)
{
    pWifiInfo = (SSIDInfo*)(&(scan_list.at(row)));
    on_wifiCilcked(row);
}

void networkset::on_EditDevName_2_clicked()
{
    ui->EditDevName_2->selectAll();
    mPltKeyBoard->show();
}

void networkset::on_EditDevName_2_loseFocus()
{
    mPltKeyBoard->hide();
}


#ifdef USB_SPEED_TEST
void networkset::on_USBtest(QString wSpeed, QString rSpeed)
{
    if(wSpeed == "")
    {
        wSpeed = "-- --";
    }
    if(rSpeed == "")
    {
        rSpeed = "-- --";
    }

    ui->lblwSpeed->setText(wSpeed);
    ui->lblrSpeed->setText(rSpeed);
}

void networkset::on_usbTest_clicked(bool checked)
{
    if(!mUSB->getUSBstatus())
    {
        ui->usbErrorWid->setVisible(true);
        ui->usbTest->setChecked(false);
        ui->lblrS->setVisible(false);
        ui->lblrSpeed->setVisible(false);
        ui->lblwS->setVisible(false);
        ui->lblwSpeed->setVisible(false);
    }else
    {
        mUSB->setTestStatus(checked);
        ui->lblrS->setVisible(checked);
        ui->lblrSpeed->setVisible(checked);
        ui->lblwS->setVisible(checked);
        ui->lblwSpeed->setVisible(checked);
    }
}

void networkset::on_USBstatus(qint32 status)
{
    ui->usbErrorWid->setVisible(!status);
    if(!status)
    {
        ui->usbTest->setChecked(false);
        ui->lblrS->setVisible(false);
        ui->lblrSpeed->setVisible(false);
        ui->lblwS->setVisible(false);
        ui->lblwSpeed->setVisible(false);
    }
}

QString networkset::ChangeGPSDisFormat(QString str)
{
    int nIndex = str.indexOf(' ');
    QString tailPart = str.right(str.length() - nIndex);
    double dbGps = str.left(str.indexOf(' ')).toDouble();
    QString degreePart = QString::number((int)dbGps);
    double FracPart1 = (dbGps - (int)dbGps) * 100;
    QString minutePart = QString::number((int)FracPart1);
    double FracPart2 = (FracPart1 - (int)FracPart1) * 60;
    QString secondPart = QString::number(FracPart2,'f',1);

    return degreePart + QString::fromUtf8("°") + minutePart + "'" + secondPart + "''" + tailPart;
}
#endif
