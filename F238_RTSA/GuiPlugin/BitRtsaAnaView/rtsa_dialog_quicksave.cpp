#include "rtsa_dialog_quicksave.h"
#include "ui_rtsa_dialog_quicksave.h"
#include "rtsa_define.h"
#include "rtsa_dialog_warning.h"
#include "rtsa_dialog_error.h"

RtSa_Dialog_QuickSave::RtSa_Dialog_QuickSave(QWidget *parent, qint32 DisplayMode) :
    QDialog(parent),
    mParent(parent),
    ui(new Ui::RtSa_Dialog_QuickSave),
    mDisplayMode(DisplayMode)
{
    ui->setupUi(this);
    initVariable();
    initDisplay();
    initWidget();
    initFunc();
//    ui->widget->setProperty("status",rtsa_qssMode[mDisPlayMode]);
//    ui->widget->setStyle(QApplication::style());
    setAttribute(Qt::WA_DeleteOnClose);
    setProperty("status",rtsa_qssMode[mDisplayMode]);
    if(mDisplayMode != 2)
    {
        ui->pb_clear->setText("");
    }
    mKeyBoard = new RtSa_dialog_virtualkeyboard(this);
//    initStyleString();
    mKeyBoard->setGeometry(QRect(30, 100, 950, 290));
    mKeyBoard->setProperty("status",rtsa_qssMode[mDisplayMode]);
//    setKeyBoardStyle();
//    this->setProperty("status",rtsa_qssMode[mDisPlayMode]);
}

RtSa_Dialog_QuickSave::~RtSa_Dialog_QuickSave()
{
    delete ui;
}
void RtSa_Dialog_QuickSave::keyPressEvent(QKeyEvent *event)
{
    ui->inputEdit->setFocus();
    qint32 keyValue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }
//    QString keyText = event->text();
    switch (keyValue) {
    case Qt::Key_Escape:
        this->close();
        return;
    case Qt::Key_Shift:
        QApplication::sendEvent(mParent,event);
        return;
    case Qt::Key_Backspace:
        backSpace();
        return;
    case Qt::Key_Delete:
        clearAll();
        return;
    case Qt::Key_CapsLock:
        QApplication::sendEvent(/*ui->widget_2*/mKeyBoard,event);
//        QApplication::sendEvent(ui->widget_2,event);
        return;
    case Qt::Key_Return:
        on_pb_ok_clicked();
        return;
    case Qt::Key_Control:
    case Qt::Key_Alt:
    case Qt::Key_Tab:
    case Qt::Key_Up:
    case Qt::Key_Down:

        return;
    default:
//        ui->inputEdit->setCursorPosition(2);
//        ui->inputEdit->insert(keyText);
        if(keyValue>=0x20 && keyValue<=0x7E)
        {
            ui->inputEdit->setFocus();
            QApplication::sendEvent(ui->inputEdit,event);
        }
        break;
    }
}

void RtSa_Dialog_QuickSave::initVariable()
{
    savePath = RTSA_DEFAULT_SCREENSHOTS_PATH;
    strInput = getDefaultFileName(savePath);
    //Ensure that folders exist
    QDir mDir(savePath);
    if(!mDir.exists())
    {
        mDir.mkpath(savePath);
    }

}

void RtSa_Dialog_QuickSave::initDisplay()
{
    ui->inputEdit->setText(strInput);
}

void RtSa_Dialog_QuickSave::initWidget()
{
    qint32 x,y;
    x = (1280 - this->width())/2;
    y = (800 - this->height())/2;
    this->move(x,y);
//    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint | Qt::Dialog);
    ui->inputEdit->setFocus();
    ui->inputEdit->setSelection(0,10);
}

void RtSa_Dialog_QuickSave::initFunc()
{
    mScreenShots = ((QWidget*)mParent->parent())->grab(QRect(RTSA_SCREEN_CAPTURE_STARTX, RTSA_SCREEN_CAPTURE_STARTY, RTSA_SCREEN_CAPTURE_WIDTH, RTSA_SCREEN_CAPTURE_HEIGHT));
    return;
}

QString RtSa_Dialog_QuickSave::getDefaultFileName(QString mSavePath)
{
    QDir mDir(mSavePath);
    QStringList filter;
    QString tmpFileName,mFileName;
    qint32 defaultIndex;
    filter<<"Trace_[0-9][0-9][0-9][0-9].png";
    mDir.setNameFilters(filter);
    QList<QFileInfo> fileInfo(mDir.entryInfoList(filter));
    if(fileInfo.size()>0)
    {
        tmpFileName = fileInfo.last().fileName();
        defaultIndex = tmpFileName.right(8).left(4).toInt();
        if(defaultIndex < 9999)
            defaultIndex++;
        mFileName = QString("Trace_%1.png").arg(defaultIndex,4,10,QLatin1Char('0'));
    }else
    {
        mFileName = "Trace_0000.png";
    }
    return mFileName;
}

bool RtSa_Dialog_QuickSave::SaveScreenShots()
{
    strInput = ui->inputEdit->text();
    QString filePath = savePath + "/" + strInput;
    qint32 checkID;
    //check file name
    checkID = checkFileName(strInput);
    if(checkID == 1)
    {
        RtSa_Dialog_Error message("Warning","Folder name contains illegal characters!\nPlease create folder with another name.",this,mDisplayMode);
        message.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        message.exec();
        return false;
    }else if(checkID == 2)
    {
        RtSa_Dialog_Error message("Notice","The beginning will cause fill hiding.Continue?",this,mDisplayMode);
        message.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        if(message.exec() != QDialog::Accepted)
        {
            return false;
        }
    }else if(checkID == 3)
    {
        filePath = filePath+".png";
//        SA_Dialog_Warning message("Warning","Illegal suffix name.Whether to continue?",this);
//        message.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//        if(message.exec() != QDialog::Accepted)
//        {
//            return false;
//        }
    }
    QFileInfo file(filePath);
    //file exist
    if(file.isFile())
    {
        RtSa_Dialog_Error message("Notice","The file already exists.Is it covered?",this,mDisplayMode);
        message.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        if(message.exec() != QDialog::Accepted)
        {
            return false;
        }
    }
    if(!mScreenShots.save(filePath,"png"))
    {
        //save faild
        RtSa_Dialog_Error message("Warning","Save failed!\nPlease check memory.",this,mDisplayMode);
        message.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        message.exec();
        return false;
    }
    return true;;
}
/**
 * @brief SA_Dialog_QuickSave::checkFileName
 * @return 0--[legitimate] If the filename is not valid, the return value is greater than 0.
 *         1--Folder name contains illegal characters!
 *         2--'.'is not an appropriate name, whether to continue to use.
 *         3--Illegal suffix name.
 */
qint32 RtSa_Dialog_QuickSave::checkFileName(QString mFile)
{
    qint32 cnt = mFile.size();
    qint32 pos = mFile.lastIndexOf('.');
    QString strSuffix;
    //Folder name contains illegal characters!
    qint32 size = sizeof(RtSa_GucRegularString);
    for(qint32 i = 0;i < size;i++)
    {
        if(mFile.contains(RtSa_GucRegularString[i]))
            return 1;
    }
    //You must type the file name.
    if(mFile.data()[0] == '.')
        return 2;

    strSuffix  = mFile.right(cnt - pos);
    if(strSuffix.toLower() !=".png")
    {
        return 3;
    }
    return 0;
}

void RtSa_Dialog_QuickSave::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void RtSa_Dialog_QuickSave::on_pb_ok_clicked()
{
    if(SaveScreenShots())
    {
        this->close();
        mParent->repaint();
    }
    return;
}

void RtSa_Dialog_QuickSave::on_pb_Cancel_clicked()
{
    this->close();
    return;
}

void RtSa_Dialog_QuickSave::backSpace()
{
    ui->inputEdit->setFocus();
    ui->inputEdit->backspace();
    strInput = ui->inputEdit->text();
    return;
}

void RtSa_Dialog_QuickSave::clearAll()
{
    ui->inputEdit->clear();
    strInput = ui->inputEdit->text();
    ui->inputEdit->setFocus();
    return;
}

void RtSa_Dialog_QuickSave::on_pb_clear_clicked()
{
    clearAll();
    return;
}
