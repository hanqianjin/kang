#include "savedialog.h"
#include "ui_savedialog.h"
#include "../keyBoard/englishkeyboard.h"
#include "../globaldef.h"
#include <QDir>
#include <QDebug>
#include <QRegExp>
SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog),
    m_configureInfo(new ConfigureInfo(this)),
    m_stateBox(new StateBox(this)),
    m_fileType(FILE_TYPE_STATE),
    m_moduleType(MODULE_TYPE_NONE)
{
    m_configureInfo->hide();
    m_stateBox->move(-380, -320);
    m_stateBox->hide();
    ui->setupUi(this);
    init();
}

SaveDialog::~SaveDialog()
{
    m_fileTypeMap.clear();
    blockSignals(true);
    delete ui;
}

void SaveDialog::init()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
    setModal(true);
    move(365, 300);
    connect(ui->okBtn, &QPushButton::clicked, this,&SaveDialog::onOkClicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &SaveDialog::onCancelClicked);
    connect(ui->fileNameBtn, &QPushButton::clicked, this, &SaveDialog::onFileNameClicked);
    connect(ui->clearBtn, &QPushButton::clicked, this, &SaveDialog::onClearClicked);
    //connect(m_stateBox, &StateBox::stateboxClosed, this, &SaveDialog::onStateboxClosed);
    //connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));

    setStyleSheet("background-color: rgb(245, 245, 245);");

    ui->clearBtn->setStyleSheet("QPushButton{background-color: rgb(233, 233, 233);}\
                                    QPushButton:pressed {background-color: rgb(245, 193, 65);}");
    ui->frame->setStyleSheet("background-color: rgb(0, 0, 0);QPushButton{};border: 2px solid transparent;"\
                             "font-size:16px; font-weight:bold;color: rgb(0, 0, 0);");

    ui->fileNameBtn->setStyleSheet("font-size:30px; font-weight:bold;color: rgb(240, 179, 29);text-align:left;");

    ui->okBtn->setStyleSheet("background-color: rgb(13, 94, 144);font-size:18px;color: rgb(250, 250, 250);");

    ui->cancelBtn->setStyleSheet("");
    ui->cancelBtn->setStyleSheet("QPushButton{background-color: rgb(7, 7, 7);font-size:18px;color: rgb(250, 250, 250);}\
                                    QPushButton:pressed {background-color: rgb(245, 193, 65);}");
    ui->pathLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    ui->pathLabel->setStyleSheet("background-color: rgb(229, 229, 229);");

    m_fileTypeMap.insert(FILE_TYPE_STATE, "/UserData/State/");
    m_fileTypeMap.insert(FILE_TYPE_STATE_AND_DATA, "/UserData/Data/");
    m_fileTypeMap.insert(FILE_TYPE_SCREEN_IMAGE, "/UserData/Screen/");
    m_fileTypeMap.insert(FILE_TYPE_MEASURE_DATA, "/UserData/MeasureData/");
    m_fileTypeMap.insert(FILE_TYPE_LIMIT, "/UserData/Limit/");


    m_fileSuffixMap.insert(FILE_TYPE_STATE, ".state");
    m_fileSuffixMap.insert(FILE_TYPE_STATE_AND_DATA, ".trace");
    m_fileSuffixMap.insert(FILE_TYPE_SCREEN_IMAGE, ".png");
    m_fileSuffixMap.insert(FILE_TYPE_MEASURE_DATA, ".csv");
    m_fileSuffixMap.insert(FILE_TYPE_LIMIT, ".csv");

    m_moduleSuffixMap.insert(MODULE_TYPE_NONE, ".trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_RF, ".trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_MODU, ".trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_OTA, ".trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_PVT, ".trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_CAT, ".trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_CCDF, ".trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_AUTO, ".trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_BEAM, ".trace");

    setSavePath(m_fileType);
}

void SaveDialog::onClearClicked()
{
    m_fileName = "";
    ui->fileNameBtn->setText("");
}

void SaveDialog::onFileNameClicked()
{
    EnglishKeyboard keyPad;
    keyPad.reset(20, m_fileName);
    if (keyPad.exec() == QDialog::Accepted)
    {
        //int errorCode = 0;
        QString text = keyPad.getInputStr();
        ui->fileNameBtn->setText(text);
        m_fileName = text;
    }
}

void SaveDialog::setSavePath(QString path)
{
    m_path = path;
    QDir dir;
    if (false == dir.mkpath(m_path))
    {
        qDebug() << "mkpath failed!!! path= " << m_path;
    }
}

void SaveDialog::setSavePath(int fileType)
{
    m_fileType = fileType;
    QString pathStr = m_fileTypeMap.value(fileType, "");
    if(pathStr.isEmpty())
    {
        qDebug() << "path is error!! ";
        return;
    }
    QString topPath;
#if __arm__
    topPath = "/app";
#else
    topPath = QDir::homePath();
#endif
    ui->pathLabel->setText(pathStr);
    pathStr = topPath + pathStr;
    setSavePath(pathStr);
    m_fileSuffix = m_fileSuffixMap.value(fileType, "");
    m_fileName = "";
    ui->fileNameBtn->setText("");
}

void SaveDialog::setModuleType(int type)
{
    m_moduleType = type;
    //m_fileSuffixMap[FILE_TYPE_STATE_AND_DATA] = m_moduleSuffixMap.value(m_moduleType,".trace");
}

void SaveDialog::setCompType(int type)
{
    if (type == COMP_TYPE_FDD)
    {
    }
    else if (type == COMP_TYPE_TDD)
    {
    }
    else if (type == COMP_TYPE_NR)
    {
    }
}

QString SaveDialog::getFile()
{
    QString file(m_path + m_fileName + m_fileSuffix);
    return file;
}

bool SaveDialog::writeData(const QString &data)
{
    if(m_fileName == "")
    {
        qDebug() << "fileName is empty!!";
        return false;
    }
    QFile file(m_path + m_fileName + m_fileSuffix);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "can not open File";
        return false;
    }
    QDataStream out(&file);
    out << data;
    file.close();

    return true;
}

void SaveDialog::onSaveFile(QString file, int fileType)
{
    Q_UNUSED(file);
    setSavePath(fileType);
}

void SaveDialog::onFastSaveFinished(bool result)
{
    if(result)
    {
        close();
        //m_stateBox->raise();
         //m_stateBox->showMessage("Fast Save Successfully", true, 3000);
    }
    else
    {
        m_configureInfo->initFastSaveFailed();
        if(m_configureInfo->exec() == QDialog::Rejected)
        {
            qDebug() << "fast save failed.";
            return;
        }
    }

}

void SaveDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
    {
        emit pressShift();
//        hide();
        close();
        return;
    }
    if(event->key() == Qt::Key_PowerOff)
    {
        emit pressPowerOff();
        return;
    }

    QDialog::keyPressEvent(event);
}

void SaveDialog::showEvent(QShowEvent *event)
{
    setDefaultFileName();
    QDialog::showEvent(event);
}

void SaveDialog::setDefaultFileName()
{
    QString filePrefix;
    switch (m_fileType)
    {
    case FILE_TYPE_STATE:
        filePrefix = "State_";
        break;
    case FILE_TYPE_STATE_AND_DATA:
        switch (m_moduleType) {
        case MODULE_TYPE_NONE:
            filePrefix = "Trace_";
            break;
        case MODULE_TYPE_RF:
            filePrefix = "Rf_";
            break;
        case MODULE_TYPE_MODU:
            filePrefix = "Modu_";
            break;
        case MODULE_TYPE_OTA:
            filePrefix = "Ota_";
            break;
        case MODULE_TYPE_PVT:
            filePrefix = "Pvt_";
            break;
        case MODULE_TYPE_CAT:
            filePrefix = "Cat_";
            break;
        case MODULE_TYPE_CCDF:
            filePrefix = "Ccdf_";
            break;
        case MODULE_TYPE_AUTO:
            filePrefix = "Auto_";
            break;
        case MODULE_TYPE_BEAM:
            filePrefix = "Beam_";
            break;
        case MODULE_TYPE_EIRP:
            filePrefix = "Eirp_";
            break;
        case MODULE_TYPE_ROUTEMAP:
            filePrefix = "RouteMap_";
            break;
        default:
            break;
        }
        break;
    case FILE_TYPE_SCREEN_IMAGE:
        filePrefix = "Screen_";
        break;
    case FILE_TYPE_MEASURE_DATA:
        filePrefix = "MeasR_";
        break;
    case FILE_TYPE_LIMIT:
        filePrefix = "Limit_";
        break;
    default:
        break;
    }

    QDir dir;
    //qDebug() << m_path;
    dir.setPath(m_path);

    dir.setFilter(QDir::Files);
    QStringList filters;
    QString fileFormat;

    fileFormat = filePrefix + "[0-9][0-9][0-9][0-9]" + m_fileSuffix;
    filters << fileFormat;
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();
    QString regExp;
    regExp = filePrefix + "([0-9][0-9][0-9][0-9])" + m_fileSuffix;
    QRegExp rx(regExp);
    QList<int> fileNumList;
    foreach (QFileInfo fileInfo, list)
    {
        rx.indexIn(fileInfo.fileName(), 0);
        //qDebug() << rx.cap(1);
        fileNumList.append(rx.cap(1).toInt());
    }
    m_fileName = filePrefix +  QString("%1").arg(getFileNum(fileNumList), 4, 10, QChar('0'));
    ui->fileNameBtn->setText(m_fileName);
}

int SaveDialog::getFileNum(QList<int> &fileNumList)
{
    if (fileNumList.isEmpty())
    {
        return 0;
    }

    if(fileNumList.count() >= 10000)
    {
        return 9999;
    }
    qSort(fileNumList.begin(), fileNumList.end());
    if (9999 != fileNumList.last())
    {
        return fileNumList.last() + 1;
    }

    for(int i = 0; i < fileNumList.count(); ++i)
    {
        if (i != fileNumList[i])
        {
            return i;
        }
    }
    qDebug()<< "get fileNum error!";
    return 9999;
}

void SaveDialog::onOkClicked()
{
    QString text = m_fileName;
    QRegExp reg("^[^';\"*/:<>?￥|\\?]+$");
    reg.setCaseSensitivity(Qt::CaseInsensitive);
    if (!reg.exactMatch(text) || (text.startsWith(".")) || (text.startsWith(" ")) || text.isEmpty())
    {
        m_configureInfo->initKeyPadFastSaveFile();
        m_configureInfo->raise();
        if(m_configureInfo->exec() == QDialog::Rejected)
        {
            qDebug() << "Incorrect input character string.";
            return;
        }
    }
    QString  fullName(m_path + m_fileName + m_fileSuffix);
    if (QFile::exists(fullName))
    {
        m_configureInfo->initSaveNameExist(m_fileName);
        if (m_configureInfo->exec() == QDialog::Rejected)
        {
            return;
        }
        QFile::remove(fullName);
    }
    emit fastSaveFileSig(fullName, m_fileType);
    //accept();

}

void SaveDialog::onCancelClicked()
{
    m_fileName = "";
    ui->fileNameBtn->setText("");
    reject();
}

void SaveDialog::onStateboxClosed()
{
    close();
}
