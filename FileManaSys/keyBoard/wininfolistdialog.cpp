#include "wininfolistdialog.h"
#include "windialog.h"
//#include "../log/LogError/ErrorLogger.h"
#include <QMap>

#define STR_ERROR_NUM(x)    ((x) > 800 ? (QString("M%1").arg(x, 3, 10, QChar('0'))) : (QString("E%1").arg(x, 3, 10, QChar('0'))))
static QMap<quint32, QString> _ErrorMsg;

WinInfoListDialog *WinInfoListDialog::instance()
{
    static WinInfoListDialog data;
    return &data;
}

void WinInfoListDialog::start()
{
    setStrMsgbyNum();    //注册操作提示及错误信息
    this->hide();
}

void WinInfoListDialog::showMsg(quint32 ErrorNum, QObject *parent)
{
    Q_UNUSED(parent);
//    if(parent != NULL && parent->isWidgetType()) {
//        QWidget *tempParent = static_cast<QWidget *>(parent);
//        tempParent->stackUnder(this);
//    }
    this->raise();
    
    m_ErrorNum = ErrorNum;
    titleLabel->setText(STR_ERROR_NUM(m_ErrorNum));

    if (m_ErrorNum < 800) {
        pictureLabel->setPixmap(QPixmap("../resources/Image/calendar/warning_s.png"));
        if((m_ErrorNum > 200 && m_ErrorNum < 308) || (m_ErrorNum > 650)) {
// #if __arm__
//             ErrorLogger::getInstance().log(m_ErrorNum); //TODO modify
// #endif
        }
    } else {
        pictureLabel->setPixmap(QPixmap("../resources/Image/calendar/status.png"));
        QTimer::singleShot(2000, this, SLOT(close()));
    }

    txtLabel->setText(getStrMsgbyNum(m_ErrorNum));

    show();
}

QString WinInfoListDialog::getStrMsgbyNum(quint32 ErrorNum)
{
    return _ErrorMsg[ErrorNum];
}

void WinInfoListDialog::slotCloseClicked()
{
    this->close();
}

WinInfoListDialog::WinInfoListDialog()
{
    initInfoDialog();
    setUserDefineStyle();

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setGeometry(0, 0, 1024/*F270App->mainWindow()->width()*/, 768/*F270App->mainWindow()->height()*/);
}

void WinInfoListDialog::initInfoDialog()
{
    p_mainFrame = new QFrame(this);
    p_mainFrame->setObjectName("BackgrounFrame");
    p_mainFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    WinStackedLayout *layout = new WinStackedLayout(this);
    layout->addWidget(p_mainFrame,Qt::AlignLeft | Qt::AlignBottom);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    titleLabel = new QLabel(p_mainFrame);
    titleLabel->setObjectName("TitleLabel");
    pictureLabel = new QLabel(p_mainFrame);
    pictureLabel->setObjectName("PictureLabel");

    QPushButton *closeBtn = new QPushButton(p_mainFrame);
    closeBtn->setObjectName("CloseButton");
    closeBtn->setFocusPolicy(Qt::NoFocus);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(slotCloseClicked()));

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(12,0,12,0);
    titleLayout->setSpacing(20);
    titleLayout->addWidget(pictureLabel,0,Qt::AlignCenter);
    titleLayout->addWidget(titleLabel,0,Qt::AlignCenter);
    titleLayout->addSpacerItem(new QSpacerItem(40,59,QSizePolicy::Expanding,QSizePolicy::Fixed));
    titleLayout->addWidget(closeBtn,0,Qt::AlignVCenter);

    txtLabel = new QLabel(p_mainFrame);
    txtLabel->setObjectName("TextLabel");
    txtLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    txtLabel->setWordWrap(true);

    QVBoxLayout * contextLayout = new QVBoxLayout(p_mainFrame);
    contextLayout->setContentsMargins(0,0,0,20);
    contextLayout->setSpacing(0);

    contextLayout->addLayout(titleLayout);
    contextLayout->addSpacing(10);
    contextLayout->addWidget(txtLabel);
    contextLayout->addStretch(300);

}

void WinInfoListDialog::setUserDefineStyle()
{
    p_mainFrame->setStyleSheet("QFrame#BackgrounFrame{"\
                               "min-width:722px;"\
                               "max-width:722px;"\
                               "min-height:250;"\
                               "border: 1px solid #D3D3D3;"\
                               "background-color:rgb(255,255,255);"\
                               "background-image:url(Image/relay/title_bg.png);"\
                               "background-repeat:repeat-x;"\
                               "background-position: top left;"\
                               "background-origin: content;"\
                               "border-top-left-radius:5px;"\
                               "border-top-right-radius:5px;}"\
        "QPushButton#CloseButton{"\
        "min-width:34px;"\
        "max-width:34px;"\
        "width:34px;"\
        "height:34px;"\
        "background-image:url(Image/relay/close_normal.png);"\
        "background-repeat: no-repeat;"\
        "background-position:center;"\
        "border:none;}"\
        "QLabel#TitleLabel{"\
        "color:rgb(255,255,255);"\
        "font-size:32px;}"\
        "QLabel#TextLabel{"\
        "color:black;"\
        "margin-top:30px;"\
        "margin-bottom:30px;"\
        "margin-left:20px;"\
        "font-size:28px;}"\
        "QPushButton{"\
        "width:124px;"\
        "height:52px;"\
        "font-size:24px;"\
        "color:white;"\
        "background-color:none;"\
        "background-image:url(Image/relay/button_normal.png);"\
        "background-repeat:no-repeat;"\
        "background-position:center;"\
        "border:none;}"\
        "QPushButton:pressed{"\
        "background-image:url(Image/relay/button_pressed.png);}");
}

void WinInfoListDialog::setStrMsgbyNum()
{
    _ErrorMsg.clear();

    //Ⅰ类：设定相关的错误--设定错误
    _ErrorMsg[1] = tr("Incorrect date or time.");   //日期,时间设定错误。
    _ErrorMsg[2] = tr("The setting of the parameter is wrong. Please refer to communication manual.");  //参数设定错误。请参阅通信命令使用说明书。
    _ErrorMsg[3] = tr("The entered value exceeds the set range.");  //输入的数值超过设定范围。
    _ErrorMsg[4] = tr("Incorrect input character string."); //输入的字符串不正确。
    _ErrorMsg[5] = tr("Too many characters.");  //输入的字符串太长。
    _ErrorMsg[6] = tr("The format of the parameter is wrong."); //参数格式错误。
    _ErrorMsg[7] = tr("No character string saved in the clipboard.");   //剪贴板中没有保存字符串。
    _ErrorMsg[8] = tr("The character string saved in the clipboard is too long.");  //剪贴板中保存的字符串太长。
    _ErrorMsg[9] = tr("String's length has exceeded."); //已经到达输入字符串的上限。
    _ErrorMsg[11] = tr("The module does not exist.");    //指定的模块不存在。
    _ErrorMsg[12] = tr("No specified input channel.");   //指定的输入通道不存在。
    _ErrorMsg[13] = tr("Exceeded the number of channels which can be set."); //通道数设定超过允许范围。
    _ErrorMsg[14] = tr("The same channel exist more than one."); //对同一通道设定2次或以上。
    _ErrorMsg[15] = tr("The specified number is set to manual.");    //指定的号码已设定为手动。
    _ErrorMsg[16] = tr("Please specify at least one channel.");  //请至少指定一条通道。
    _ErrorMsg[31] = tr("Invalid input value. (in ascending order)"); //输入值的设定有误(请按照从小到大的顺序设定)。
    _ErrorMsg[41] = tr("No channel specified by formula.");  //运算式中指定的通道不存在。
    _ErrorMsg[42] = tr("MATH expression grammar is incorrect."); //运算式有语法错误。
    _ErrorMsg[43] = tr("Invalid order of operators.");   //运算式的前后关系有错误。
    _ErrorMsg[44] = tr("Please enter valid constant for math expression.");   //运算式使用的运算符太多。
    _ErrorMsg[45] = tr("Nonexistent constant specified in MATH expression.");    //运算常数的记述有错误。
    _ErrorMsg[46] = tr("No switch specified by formula.");  //运算式中指定的SW不存在。
    _ErrorMsg[91] = tr("This username is already registered.");  //相同的用户名已经注册。
    _ErrorMsg[92] = tr("\"quit\" cannot included in the string.");    //不能指定"quit"。
    _ErrorMsg[93] = tr("String including space cannot be specified.");   //不能设定包含空格的字符串。
    _ErrorMsg[94] = tr("NULL cannot be specified."); //不能设定NULL。
    _ErrorMsg[95] = tr("User ID already registered.");   //此用户ID已被使用。
    _ErrorMsg[96] = tr("This user name cannot be specified.");   //不能使用该用户名。
    _ErrorMsg[101] = tr("Duplicated port number.Please enter another port number. ");   //端口号设置重复,请输入其他端口号。
    _ErrorMsg[102] = tr("IP address class error.");   //IP地址不属于A,B,C中的任何一类。
    _ErrorMsg[103] = tr("Masked IP address is all 0s or 1s.");    //IP地址掩码后结果全部是0或1。
    _ErrorMsg[104] = tr("SUBNET mask is incorrect."); //子网掩码的设定不正确。
    _ErrorMsg[105] = tr("The net part of default gateway is not equal to that of IPaddress.");    //默认网关和IP地址的网段不一致。
    _ErrorMsg[106] = tr("More than one address cannot be specified.");    //不能设定多地址。
    _ErrorMsg[107] = tr("Number entered exceeds channel number limit. Please use another command."); //输入的通道数超过一次可读入范围，请使用多个命令。

    //Ⅰ类：设定相关的错误--执行时的错误
    _ErrorMsg[201] = tr("Cannot execute command because other users changed setting.");  //其他用户已变更设定，不能执行。
    _ErrorMsg[202] = tr("This action is not possible because recording or math computation is in progress.");    //正在记录或运算，不能变更或执行。
    _ErrorMsg[203] = tr("This action is not possible because sampling is in progress."); //正在记录，不能变更或执行。
    _ErrorMsg[204] = tr("This action is not possible because math computation is in progress."); //正在运算，不能变更或执行。
    _ErrorMsg[211] = tr("This function is not possible now.");   //该功能此时不能使用。
    _ErrorMsg[212] = tr("This action is not possible because bar code data error.");   //条形码有错误，不能执行。
    _ErrorMsg[213] = tr("This function is not available with invalid user.");    //已锁定的用户不能执行该操作。
    _ErrorMsg[214] = tr("This function is not available with logged out user."); //已注销的用户不能执行该操作。
    _ErrorMsg[221] = tr("This function is not available because input number exceeds the limit.");  //超出可输入个数，不能执行。
    _ErrorMsg[222] = tr("Failed to write information because data sampling  stopped."); //内存数据采样已停止，不能写入信息。
    _ErrorMsg[223] = tr("Failed to write to postscript message area.");  //不在追加信息范围以内。
    _ErrorMsg[224] = tr("Failed to write message outside of data range.");    //不能在数据范围外写入信息。
    _ErrorMsg[225] = tr("Failed to print."); //打印失败。
    _ErrorMsg[226] = tr("This action is not possible because message writing."); //信息写入中，不能执行。
    _ErrorMsg[231] = tr("This action is not possible because saving is in progress.");   //外部存储器正在进行数据保存，不能变更或执行。
    _ErrorMsg[232] = tr("This action is not possible because formatting is in progress.");   //外部存储器正在格式化,不能执行。
    _ErrorMsg[233] = tr("Data save is not possible because of insufficient external memory  capacity.");    //外部存储器的可用空间不足，已中断保存。
    _ErrorMsg[234] = tr("Invalid fileor directory name.");   //文件名或目录名不正确。
    _ErrorMsg[235] = tr("This action is not possible because FTP transmission is in progress."); //正在进行FTP通信，不能变更或执行。
    _ErrorMsg[236] = tr("Cannot take successive snapshots. Wait 10 seconds or more in between snapshots.");  //画面存储不能连续进行。两次执行画面存储操作间隔时间十秒以上。
    _ErrorMsg[242] = tr("End process can't proceed, because setting file is not saved to Media.");   //保存设定文件失败，不能结束。
    _ErrorMsg[243] = tr("Exceeded max number of change.");   //已达到设定变更项目数上限，不能再变更设定。
    _ErrorMsg[244] = tr("Configuration error."); //修改设定失败。
    _ErrorMsg[245] = tr("Execution error, lack of key.");    //未生成密钥，不能执行该操作。
    _ErrorMsg[246] = tr("Failed to process input value.");   //未能正确获取测量值。
    _ErrorMsg[251] = tr("Invalid user name or password.");   //用户名或密码错误。
    _ErrorMsg[252] = tr("The login password is incorrect."); //登录密码错误。
    _ErrorMsg[253] = tr("A user already logged in.");    //已经有用户登录。
    _ErrorMsg[254] = tr("This entry is incorrect."); //输入不正确。
    _ErrorMsg[255] = tr("Password entered is incorrect. ");   //两次输入的密码不一致。
    _ErrorMsg[256] = tr("Same password is not allowed.");   //新密码不能和旧密码相同。
    _ErrorMsg[257] = tr("Password is incorrect.");   //密码错误。
    _ErrorMsg[258] = tr("This function is locked."); //该功能被锁定。
    _ErrorMsg[260] = tr("This user name is not available in this mode.");   //当前用户不能进入该模式。
    _ErrorMsg[261] = tr("User ID or password error.");   //用户ID或密码错误。
    _ErrorMsg[262] = tr("Login failed！Password expired."); //密码已过期，不能登录。
    _ErrorMsg[263] = tr("Password entered should not be the same as the default one.");  //不能设定与初始密码相同的密码。
    _ErrorMsg[264] = tr("This user ID and password combination is already in use."); //已存在相同的用户ID和密码。
    _ErrorMsg[265] = tr("Login inputs are incorrect.");  //输入有误。
    _ErrorMsg[272] = tr("Invalid password!");    //密码无效。
    _ErrorMsg[273] = tr("Invalid user.");    //无效用户。
    _ErrorMsg[274] = tr("Please enter more than 6 characters."); //请输入6位字符以上的密码。
    _ErrorMsg[281] = tr("Failed to calibrate time.");  //超过时间校正范围,无法校正。
    _ErrorMsg[301] = tr("No modules to download the firmware."); //要下载固件的模块不存在。
    _ErrorMsg[302] = tr("Firmware file not found."); //无固件文件。
    _ErrorMsg[303] = tr("Failed to read firmware file.");    //读取固件文件失败。
    _ErrorMsg[304] = tr("Firmware file corrupted .");    //固件文件已损坏。
    _ErrorMsg[305] = tr("Invalid firmware version.");    //固件版本错误。
    _ErrorMsg[306] = tr("Mismatch module type.");    //模块类型不匹配。
    _ErrorMsg[307] = tr("Downloading firmware error."); //下载固件过程中发生错误。

    //Ⅰ类：设定相关的错误--运行错误
    _ErrorMsg[501] = tr("Operation aborted due to external memory error.");
    _ErrorMsg[502] = tr("Not enough free space on external memory.");
    _ErrorMsg[503] = tr("External memory can not be recognized.");
    _ErrorMsg[504] = tr("Media read error.");
    _ErrorMsg[505] = tr("Media write error.");
    _ErrorMsg[506] = tr("Failed to create the file.");
    _ErrorMsg[507] = tr("No file or directory.");
    _ErrorMsg[508] = tr("Format error.");
    _ErrorMsg[509] = tr("Unknown file type.");
    _ErrorMsg[511] = tr("Invalid file or directory operation.");
    _ErrorMsg[512] = tr("The file is already in use. Try again later.");
    _ErrorMsg[514] = tr("No setting files.");
    _ErrorMsg[515] = tr("A template file is abnormal.");
    _ErrorMsg[516] = tr("Some items not set.");
    _ErrorMsg[517] = tr("Media is read-only.");
    _ErrorMsg[518] = tr("Scale image not loaded.");
    _ErrorMsg[519] = tr("Template file not loaded.");
    _ErrorMsg[532] = tr("No data available.");
    _ErrorMsg[536] = tr("No data after the date and time.");
    _ErrorMsg[537] = tr("The specified screen cannot be displayed.");
    _ErrorMsg[539] = tr("No selected data.");
    _ErrorMsg[541] = tr("Printer not connected.");
    _ErrorMsg[542] = tr("Printer busy.");
    _ErrorMsg[551] = tr("Module was detached.");
    _ErrorMsg[552] = tr("Detected newer version module.");
    _ErrorMsg[553] = tr("Unrecognized module.");
    _ErrorMsg[554] = tr("Fatal module error.");
    _ErrorMsg[555] = tr("Non-calibrated module.");
    _ErrorMsg[556] = tr("RJC error module.");
    _ErrorMsg[557] = tr("A/D error module.");
    _ErrorMsg[558] = tr("Activation required for attached modules.");
    _ErrorMsg[570] = tr("The specified file does not exist.");
    _ErrorMsg[571] = tr("The specified folder does not exist.");
    _ErrorMsg[572] = tr("Deletion of the file went wrong.");
    _ErrorMsg[573] = tr("Deletion of the folder went wrong.");
    _ErrorMsg[581] = tr("Specified custom display file does not exist.");
    _ErrorMsg[582] = tr("Invalid custom display file.");
    _ErrorMsg[583] = tr("Image file does not exist.");
    _ErrorMsg[591] = tr("Certification saving error, memory full.");
    _ErrorMsg[592] = tr("Key is broken. Please generate key.");
    _ErrorMsg[601] = tr("Error, already signed in.");
    _ErrorMsg[604] = tr("This file is not allowed to sign record.");
    _ErrorMsg[606] = tr("Request denied, busy while signing in data.");
    _ErrorMsg[607] = tr("Insufficient information to sign in.");

    //Ⅱ类：通信应用相关的错误--Email相关的错误
    _ErrorMsg[651] = tr("IP address is not set or ethernet function is not available.");
    _ErrorMsg[652] = tr("SMTP server is not found.");
    _ErrorMsg[653] = tr("Cannot initiate E-mail transmission.");
    _ErrorMsg[654] = tr("Sender's address rejected by the server.");
    _ErrorMsg[655] = tr("Some recipients' addresses are invalid.");
    _ErrorMsg[656] = tr("SMTP protocol error.");
    _ErrorMsg[657] = tr("Ethernet cable is not connected.");
    _ErrorMsg[658] = tr("Could not connect to SMTP server.");
    _ErrorMsg[660] = tr("E-mail transfer error.");
    _ErrorMsg[671] = tr("Could not connect to POP3 server.");
    _ErrorMsg[672] = tr("Not able to login to the POP3 server.");
    _ErrorMsg[673] = tr("SMTP authentication failed.");
    _ErrorMsg[674] = tr("The server requested an unsupported authentication method.");

    //Ⅱ类：通信应用相关的错误--FTP客户端相关的错误
    _ErrorMsg[691] = tr("IP address is not set or FTP function is not available.");
    _ErrorMsg[692] = tr("FTP control connection error.");
    _ErrorMsg[693] = tr("FTP command was not accepted.");
    _ErrorMsg[695] = tr("FTP data connection error.");
    _ErrorMsg[696] = tr("FTP file transfer error.");
    _ErrorMsg[698] = tr("Connection time-out occurred for FTP.");
    _ErrorMsg[699] = tr("An error occurred for FTP.");

    //Ⅱ类：通信应用相关的错误--SNTP相关错误
    _ErrorMsg[711] = tr("SNTP access failure.");
    _ErrorMsg[712] = tr("SNTP server does not respond.");
    _ErrorMsg[713] = tr("Incorrect SNTP server setting.");
    _ErrorMsg[714] = tr("Invalid SNTP server reply.");
    _ErrorMsg[715] = tr("No time correction because excess time deviation with SNTP server.");

    //Ⅱ类：通信应用相关的错误--DHCP相关的错误
    _ErrorMsg[721] = tr("IP address was released because DHCP setting is invalid.");
    _ErrorMsg[722] = tr("DHCP access failure.");
    _ErrorMsg[723] = tr("Registration of the hostname to the DNS server failed.");
    _ErrorMsg[724] = tr("Deletion of the hostname to the DNS server failed.");

    //Ⅱ类：通信应用相关的错误--其他通信相关的错误
    _ErrorMsg[731] = tr("Connection has been lost.");
    _ErrorMsg[732] = tr("The number of simultaneous connections has been exceeded.");
    _ErrorMsg[733] = tr("Communication has timed-out.");
    _ErrorMsg[781] = tr("Failed to establish encrypted communication.");
    _ErrorMsg[782] = tr("Communcation failed due to certificate.");
    _ErrorMsg[783] = tr("Wrong validity certificate.");

    //Ⅱ类：通信应用相关的错误--安全增强(/AS可选项)时的错误
    _ErrorMsg[760] = tr("Invalid KDC client configuration.");
    _ErrorMsg[761] = tr("Cannot find KDC server.");
    _ErrorMsg[762] = tr("KDC server connection error.");
    _ErrorMsg[763] = tr("Not supported by this machine.");
    _ErrorMsg[764] = tr("Preauthentication failed.");
    _ErrorMsg[765] = tr("The encryption type is not supported by this machine.");
    _ErrorMsg[766] = tr("Failed to receive authentication from KDC server.");
    _ErrorMsg[767] = tr("Change the password.");
    _ErrorMsg[768] = tr("The time difference with the KDC server exceeds the limit.");
    _ErrorMsg[770] = tr("The host principal is not registered.");
    _ErrorMsg[771] = tr("The host principal is invalid.");
    _ErrorMsg[772] = tr("The host password is incorrect.");
    _ErrorMsg[773] = tr("Preauthentication failed.");
    _ErrorMsg[774] = tr("The realm is incorrect.");

    //Ⅲ类：通信固有的错误--执行错误
    _ErrorMsg[351] = tr("Command is too long.");
    _ErrorMsg[352] = tr("Unknown command.");
    _ErrorMsg[353] = tr("This command is not permitted in this user.");
    _ErrorMsg[354] = tr("This command is not permitted in this mode.");
    _ErrorMsg[355] = tr("The option is not installed.");
    _ErrorMsg[356] = tr("This command is not permitted in this setting.");
    _ErrorMsg[357] = tr("Wrong command arguments number.");
    _ErrorMsg[358] = tr("This command does not support a query.");
    _ErrorMsg[361] = tr("Wrong error number.");
    _ErrorMsg[401] = tr("A user name and password is required.");
    _ErrorMsg[402] = tr("Required userID/Password.");
    _ErrorMsg[411] = tr("Exceeded number of selection.");
    _ErrorMsg[412] = tr("No data exists.");

    //Ⅳ类：状态信息
    _ErrorMsg[801] = tr("Execution is completed."); //正常结束
    _ErrorMsg[802] = tr("Please wait a moment...");  //请稍等...
    _ErrorMsg[803] = tr("Saving data to external device...");    //正在向外部存储器中保存数据
    _ErrorMsg[804] = tr("Loading data from external device..."); //正在从外部存储器中读取数据
    _ErrorMsg[805] = tr("Process of saving data to external device stops.");    //外部存储器保存数据被中断
    _ErrorMsg[806] = tr("Data have been saved."); //数据保存完了
    _ErrorMsg[807] = tr("File sorting...");   //文件排序中
    _ErrorMsg[808] = tr("Formatting...");    //正在格式化
    _ErrorMsg[809] = tr("Stop processing...");    //停止处理中
    _ErrorMsg[810] = tr("Loading historical data..."); //历史数据准备中
    _ErrorMsg[811] = tr("All data have been saved."); //没有未保存数据
    _ErrorMsg[812] = tr("External device is connected.");   //外部存储器识别成功
    _ErrorMsg[813] = tr("You can remove your external device.");    //现在可以安全地取出外部存储器了
    _ErrorMsg[814] = tr("External device removed improperly.");    //外部存储器被强制取出
    _ErrorMsg[815] = tr("Failed to connect you external device.");   //外部存储器安装失败
    _ErrorMsg[816] = tr("USB device is connected.");    //USB设备连接成功
    _ErrorMsg[817] = tr("Failed to recognize the USB device.");  //无法识别的USB设备
    _ErrorMsg[818] = tr("Press [MENU] key to login.");   //请使用[MENU]键登录。
    _ErrorMsg[819] = tr("Wrong format media.");  //外部存储器格式不正确
    _ErrorMsg[821] = tr("Ethernet cable is connected.");    //以太网线已连接
    _ErrorMsg[822] = tr("Ethernet cable is disconnected."); //以太网线已断开
    _ErrorMsg[823] = tr("Connecting to the line...");    //正在连接线路
    _ErrorMsg[824] = tr("Sending data file.");   //正在传输测量数据文件
    _ErrorMsg[825] = tr("Executing FTP test.");  //正在进行FTP测试
    _ErrorMsg[826] = tr("Executing e-mail test.");   //正在进行Email发信测试
    _ErrorMsg[827] = tr("Now connecting to SNTPserver...");  //正在连接SNTP服务器...
    _ErrorMsg[828] = tr("Querying to DHCP.");    //正在访问DHCP服务器
    _ErrorMsg[830] = tr("Received ressponse from DHCP.");    //已经收到DHCP服务器的应答
    _ErrorMsg[831] = tr("IP address set.");  //IP地址设定成功
    _ErrorMsg[832] = tr("No hostname registration to DNS server in current settings.");  //该设定不向DNS服务器注册主机名
    _ErrorMsg[833] = tr("Registered hostname to DNS server.");   //向DNS服务器注册主机名成功
    _ErrorMsg[834] = tr("Deleted hostname in DNS server.");  //该主机名已成功从DNS服务器删除
    _ErrorMsg[836] = tr("KDC test connection succeeded.");   //KDC连接测试成功
    _ErrorMsg[837] = tr("Login may be impossible in incorrect KDC client settings.");    //KDC客户端设定不正确可能导致无法登录。
    _ErrorMsg[841] = tr("Now adjusting the time.");  //正在调整时间
    _ErrorMsg[850] = tr("Saving Settings."); //正在变更设定
    _ErrorMsg[851] = tr("Module installed successfully.");   //模块已安装
    _ErrorMsg[852] = tr("Updating I/O module firmware.");    //正在升级I/O模块固件
    _ErrorMsg[853] = tr("System reconstruction in progress.");   //正在重新配置系统
    _ErrorMsg[854] = tr("Executing A/D calibration.");   //正在进行A/D校正
    _ErrorMsg[855] = tr("Initializing...");  //正在初始化
    _ErrorMsg[856] = tr("Writing the A/D calibration value.");   //正在写入A/D校正值
    _ErrorMsg[857] = tr("Resetting the A/D calibration value."); //正在重置A/D校正值
    _ErrorMsg[858] = tr("Detected new modules. Required System Reconfiguration.");//安装了新模块 请重新配置系统
    _ErrorMsg[860] = tr("Please set as recording channel."); //不是记录通道的对象。请在记录通道中设定
    _ErrorMsg[861] = tr("Noise may influence measurement in fast mode.");    //高速模式中,可能由于噪声的影响造成测量值的不稳定
    _ErrorMsg[862] = tr("Please acknowledge all active alarms before stopping this record.");//没有检查报警，如有需要，请执行检查动作
    _ErrorMsg[863] = tr("Changed the recording interval.");  //记录周期的设定已变更
    _ErrorMsg[864] = tr("Setting changes exceeded 50. Not possible to save beyond 100. Please save now.");//设定变更项已超过50项，超过100项则无法保存。 请进行保存。
    _ErrorMsg[865] = tr("\"Relay Action on ACK\" setting of all DO channel will change to \"reset\".");//所有DO通道的报警解除时继电器动作为“复位”
    _ErrorMsg[866] = tr("Not available for electric signature. Please set the certificate.");    //不能进行电子签名，请生成密钥或设定证书。
    _ErrorMsg[867] = tr("Not available for encrypted comm. Please set the certificate.");    //不能加密通信，请生成密钥或设定证书。
    _ErrorMsg[868] = tr("Chattering filter may not function. Please update module to R1.04.01 or later.");//有抖动的脉冲输入可能无法正常工作。请更新模块到R1.04.01或更高版本。
    _ErrorMsg[875] = tr("Failed to display some components.");   //存在无法显示的组件。
    _ErrorMsg[876] = tr("Currently in operation.");  //其他趋势组件正在操作中
    _ErrorMsg[881] = tr("Initialized the measured data and settings.");  //设定条件和测量数据已被初始化
    _ErrorMsg[882] = tr("Initialized the measured data.");   //测量数据已被初始化
    _ErrorMsg[891] = tr("Please restart your device to validate the language.");  //语言已变更。请重启以使变更生效。
    _ErrorMsg[892] = tr("Please reboot the system.");    //请重新启动系统
    _ErrorMsg[893] = tr("The specified channel is not used in the display group.");   //指定的通道没有在显示组中使用

    //Ⅴ类：系统错误
    _ErrorMsg[901] = tr("ROM failure.");
    _ErrorMsg[902] = tr("RAM failure.");
    _ErrorMsg[911] = tr("A/D calibration value error.");
    _ErrorMsg[912] = tr("A/D calibration error.");
    _ErrorMsg[913] = tr("Incorrect number for the A/D calibration.");
    _ErrorMsg[914] = tr("Failed to write A/D calibration value.");
    _ErrorMsg[915] = tr("Failed to load A/D calibration value.");
    _ErrorMsg[921] = tr("Memory acquisition failure.");
    _ErrorMsg[922] = tr("The ethernet module error.");
    _ErrorMsg[923] = tr("A hardware test failed.");
    _ErrorMsg[924] = tr("Low backup battery level .");
    _ErrorMsg[925] = tr("Touch screen failure.");
    _ErrorMsg[951] = tr("Data are not written in the flash memory area for production.");
    _ErrorMsg[952] = tr("A SUM value of the flash memory area for production is incorrect.");
    _ErrorMsg[953] = tr("The reading of the flash memory area for production failed.");
    _ErrorMsg[954] = tr("The writing of the flash memory area for production failed.");
    _ErrorMsg[997] = tr("Insufficient display memory.");
    _ErrorMsg[999] = tr("System error.");

    //Ⅵ类：Web应用程序发出的信息--错误信息
    //Ⅵ类：Web应用程序发出的信息--警告信息
    //Ⅵ类：Web应用程序发出的信息--信息内容

}
