/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                bitsa.cpp
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2018/12/05
** Descriptions:             the main class of the plugin,used to control all the UI show and FPGA control
**
*********************************************************************************************************/

#include "bitsa.h"
#include "ui_bitsa.h"
#include <QDir>
#include <QDebug>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <QGraphicsOpacityEffect>
#include <math.h>
#include <QTime>
#include <QMouseEvent>
#include <QKeyEvent>
#include "sa_clickedwidget.h"
#include "sa_stdafx.h"
#include "sa_dialog_digitinput.h"
#include "sa_dialog_allsetup.h"
#include <QThread>
#include "sa_dialog_freqsetup.h"
#include "sa_dialog_amptsetup.h"
#include "sa_dialog_displaysetup.h"
#include "sa_dialog_bwsetup.h"
#include "sa_dialog_triggersetup.h"
#include "sa_dialog_tracesetup.h"
#include "sa_dialog_markersetup.h"
#include "sa_dialog_measuresetup.h"
#include "sa_dialog_markersingle.h"
#include "sa_dialog_limit.h"

#include "sa_dialog_ch_std.h"
#include "sa_clickedlabel.h"
#include "sa_dialog_quicksave.h"

#include "sa_dialog_chnlpowerset.h"
#include "sa_dialog_acpset.h"
#include "sa_dialog_occpdset.h"
#include "sa_dialog_specem.h"
#include "sa_dialog_spurem.h"
#include "bitsa.h"
#include "safilemanager.h"

struct GUI_DRAW_SET SA_guiDrawSet;
struct WATTS_UNIT SA_watts_unit;
SA_Dialog_AllSetup *mAllSetDialog;
SA_Dialog_FreqSetup *wFreqSetup;
SA_Dialog_AmptSetup *wAmptSetup;
SA_Dialog_DisplaySetup *wSweepSetup;
SA_Dialog_BWSetup *wBwSetup;
SA_Dialog_TriggerSetup *wTriggerSetup;
SA_Dialog_TraceSetup  *wTraceSetup;
SA_Dialog_MarkerSetup *wMarkerSetup;
SA_Dialog_Limit *wLimitSetup;
SA_Dialog_MeasureSetup *wMeasureSetup;
SA_Dialog_MarkerSingle *wMarkerSingle;

sa_dialog_chnlpowerset *wChnlpowerset;
sa_dialog_occpdset *wOccpdset;
sa_dialog_acpset *wAcpset;
SA_Dialog_SpecEM *wSpecEM;
SA_Dialog_SpurEM *wSpurEM;

pthread_mutex_t SA_lockobj;

//int SA_homeuiHandle = 0;
//int SA_syncHandle = 0;//212
//int SA_guiHandle = 0;
bool bParaLoad = false;
BitSA::BitSA(QWidget *parent) :
    QWidget(parent),
    singparamflag(0)
{
    pthread_mutex_init(&SA_lockobj,NULL);
    pBitSA = new Ui::BitSA();
    pBitSA->setupUi(this);
    pBitSA->buttomMarker->setVisible(false);
    m_user_variable = new user_variable();
    this->setWindowFlags(Qt::FramelessWindowHint);  // Remove Window Captionbar
    setAttribute(Qt::WA_DeleteOnClose);
    initPointer();

    initTableWidget();
    initTableInfoWidget();

    //Johnson Zero Restrain Cal
    pcontrolInterface->setZeroRestrainFromFile();

    connect(pcontrolInterface,SIGNAL(signalModeChange()),this,SLOT(slotOperateTable()));
#if SMALL_LARGE_PIXMAP_IMAGE
    psa_UIRefresh_Control->smallPixmap = psa_UIRefresh_Control->smallPixmap.scaled(1025,648,Qt::IgnoreAspectRatio,Qt::FastTransformation);
#endif
    //Johnson 190529
    connect(psa_UIRefresh_Control,SIGNAL(refreshMeasureSet()),this,SLOT(measureModeParaRefresh()));
    //Tony for remote
    connect(psa_UIRefresh_Control,SIGNAL(refreshRemote(QString)),pcontrolInterface,SIGNAL(sendSCPIcmd(QString)));
    //************init sa status,Johnson 190605
    initWidget();
    initVariable();
    //Tony 0619 for refresh ui after init variable
    initInfo();
    //set qss mode for indoor,outdoor or night;
    this->setProperty("status",qssMode[pcontrolInterface->GetDisplayMode()]);
    setMenuProperty("status",qssMode[pcontrolInterface->GetDisplayMode()]);
    connect(pcontrolInterface,SIGNAL(infoRefresh(qint32,qint32)),this,SLOT(on_infoRefresh(qint32,qint32)));
    qDebug()<<"SA initial success.......";

//    if((SA_homeuiHandle = semget(SA_HOME_UI_SHOW_KEY,1,IPC_CREAT | 0660))<0)

}

BitSA::~BitSA()
{
    if(psa_Amplitude_Control)
    {
        delete psa_Amplitude_Control;
        psa_Amplitude_Control = NULL;
    }
    if(psa_UIRefresh_Control)
    {
        delete psa_UIRefresh_Control;
        psa_UIRefresh_Control = NULL;
    }
    if(mSetupDialog)
    {
        mSetupDialog = 0;
    }
    if(wFreqSetup)
    {
        delete wFreqSetup;
        wFreqSetup = 0;
    }
    if(wAmptSetup)
    {
        delete wAmptSetup;
        wAmptSetup = 0;
    }
    if(wSweepSetup)
    {
        delete wSweepSetup;
        wSweepSetup = 0;
    }
    if(wBwSetup)
    {
        delete wBwSetup;
        wBwSetup = 0;
    }
    if(wTriggerSetup)
    {
        delete wTriggerSetup;
        wTriggerSetup = 0;
    }
    if(wTraceSetup)
    {
        delete wTraceSetup;
        wTraceSetup = 0;
    }
    if(wMarkerSetup)
    {
        delete wMarkerSetup;
        wMarkerSetup = 0;
    }
    if(wLimitSetup)
    {
        delete wLimitSetup;
        wLimitSetup = 0;
    }
    if(wMeasureSetup)
    {
        delete wMeasureSetup;
        wMeasureSetup = 0;
    }
    if(wMarkerSingle)
    {
        delete wMarkerSingle;
        wMarkerSingle = 0;
    }
    if(wChnlpowerset)
    {
        delete wChnlpowerset;
        wChnlpowerset = 0;
    }
    if(wOccpdset)
    {
        delete wOccpdset;
        wOccpdset = 0;
    }
    if(wAcpset)
    {
        delete wAcpset;
        wAcpset = 0;
    }
    if(wSpecEM)
    {
        delete wSpecEM;
        wSpecEM = 0;
    }
    if(wSpurEM)
    {
        delete wSpurEM;
        wSpurEM = 0;
    }

    if(pACPTable)
    {
        delete pACPTable;
        pACPTable = NULL;
    }
    if(pChannelPowerTable)
    {
        delete pChannelPowerTable;
        pChannelPowerTable = NULL;
    }
    if(pMarkerTable)
    {
        delete pMarkerTable;
        pMarkerTable = NULL;
    }
    if(pOccupiedXdBTable)
    {
        delete pOccupiedXdBTable;
        pOccupiedXdBTable = NULL;
    }
    if(pSpectrumEMTable)
    {
        delete pSpectrumEMTable;
        pSpectrumEMTable = NULL;
    }
    if(pControlACPTable)
    {
        delete pControlACPTable;
        pControlACPTable = NULL;
    }
    if(pControlChannelPowerTable)
    {
        delete pControlChannelPowerTable;
        pControlChannelPowerTable = NULL;
    }
    if(pControlMarkerTable)
    {
        delete pControlMarkerTable;
        pControlMarkerTable = NULL;
    }
    if(pControlpOccupiedXdBTable)
    {
        delete pControlpOccupiedXdBTable;
        pControlpOccupiedXdBTable = NULL;
    }
    if(pControlSpectrumEMTable)
    {
        delete pControlSpectrumEMTable;
        pControlSpectrumEMTable = NULL;
    }


    if(mBtnGroup)
    {
        delete mBtnGroup;
        mBtnGroup = NULL;
    }
    if(pBitSA)
    {
        delete pBitSA;
        pBitSA = NULL;
    }

    //*****must delete after all dialog deleted,because every dialog uses the three parameter
    if(pcontrolInterface)
    {
        delete pcontrolInterface;
        pcontrolInterface = NULL;
    }
    if(globalUserLimit)
    {
        delete globalUserLimit;
        globalUserLimit = NULL;
    }
    if(m_user_variable)
    {
        delete m_user_variable;
        m_user_variable = NULL;
    }
}

void BitSA::LoadFilePara(QString mPath)
{
    qint32 successFlag;
    //load file
    pcontrolInterface->blockSignals(true);
    successFlag = pcontrolInterface->loadFile(mPath);
    pcontrolInterface->SetMeasureItems(m_user_variable->currentMode);
    pcontrolInterface->blockSignals(false);
    initInfo();
    adjustRect();
    graphRefreshFunc();
    if(m_user_variable->loadFileType == SA_FILE)
    {
        loadFlag = 1;
    }else
    {
        loadFlag = 0;
    }
    mFileManager->onLoadFinished(successFlag);
    //    pcontrolInterface->setSuspendFunc(0);
    //    pcontrolInterface->TraceSuspendFunc(m_user_variable->traceSusFlag);
}

void BitSA::saveFilePara(QString mPath,/*FILE_TYPE*/qint32 mFileType)
{
    qint32 successFlag;
    //save File
    if(mFileType == 1)
    {
        successFlag = pcontrolInterface->setSaveState(mPath);
    }else if(mFileType == 2)
    {
        successFlag= pcontrolInterface->setSaveTrace(mPath);
    }
    mFileManager->onSaveFinished(successFlag);
    return ;
}

void BitSA::quickSaveFilePara(QString mPath,qint32 mFileType)
{
    qint32 successFlag;
    //save File
    if(mFileType == 1)
    {
        successFlag = pcontrolInterface->setSaveState(mPath);
    }else if(mFileType == 2)
    {
        successFlag = pcontrolInterface->setSaveTrace(mPath);
    }
    mFileManager->onFastSaveFinished(successFlag);
    return ;
}

void BitSA::on_fastSaveDialogClosed()
{
    pcontrolInterface->setSuspendFunc(0);
}

void BitSA::on_fileManagerWidgetClosed()
{
    if(loadFlag)
    {
        pcontrolInterface->setSuspendFunc(true);
    }else
    {
        pcontrolInterface->setSuspendFunc(0);
    }
}


/**
 * @brief BitSA::initPointer
 * @note  initialize pointers defined in .h file
 */
void BitSA::initPointer()
{
    //************initialize pointer
    globalUserLimit = new user_limit(*m_user_variable);
    pcontrolInterface = new controlInterface(*m_user_variable,*globalUserLimit);
    //pparaSaveLoad = new paraSaveLoad(*globalUserLimit,*m_user_variable);
    psa_UIRefresh_Control = new sa_UIRefresh_Control(*m_user_variable,*globalUserLimit);
    psa_Amplitude_Control = new sa_Amplitude_Control(*m_user_variable,*globalUserLimit);
    connect(psa_UIRefresh_Control,SIGNAL(infoRefresh(qint32)),this,SLOT(refreshMarker(qint32)),Qt::DirectConnection);
    connect(psa_UIRefresh_Control,SIGNAL(infoRefresh(qint32)),this,SLOT(refreshBtnFocus(qint32)));
}
/**
 * @brief BitSA::initTableWidget
 * @note  initialize customed tablewidget
 */
void BitSA::initTableWidget()
{
    initTableWidgetValue();
    connect(pBitSA->tableWidget,SIGNAL(editFinish()),this,SLOT(getLimitDot()));
    connect(pBitSA->tableWidget,SIGNAL(contenJudge()),this,SLOT(judgeTableContent()));
    pBitSA->tableWidget->hide();
    pBitSA->tableWidget->move(GRID_START_X+50,GRID_START_Y-30);
    pBitSA->tableWidget->horizontalHeader()->resizeSection(0,TABLEWIDGET_HEADER_LENGTH);
    pBitSA->tableWidget->horizontalHeader()->resizeSection(1,TABLEWIDGET_HEADER_LENGTH);
    pBitSA->tableWidget->resize(TABLEWIDGET_WIDTH,GRID_HEIGHT);
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    pBitSA->tableWidget->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(TABLEWIDGET_OPACITY);
}

/**
 * @brief BitSA::initDrive
 * @note  write control code to drive program
 */
void BitSA::initDrive()
{
    //********write control code to drive program
    QFile f("/sys/devices/soc0/43000000.ps7-lcdc/pl_bg/bg_flag");
    if(!f.open(QIODevice::WriteOnly)){
        qDebug()<<"Open file fail!";
    }
    else{
        f.write("1");
        f.close();
        qDebug()<<"after show!";
    }
}
/**
 * @brief BitSA::initVariable
 * @note  initialize all variables related with UI show
 */
void BitSA::initVariable()
{
#if 0
    m_user_variable->markerSettingInitFunc();
    if(pparaSaveLoad->setVariable(&gGlobalParam))
    {
        pcontrolInterface->LoadParamControl();
        pcontrolInterface->LoadParapcontrolInterface(currentMode);
    }
    m_user_variable->currentMode = SA_SPAN_MODE;
    globalUserLimit->caculateLimitTotalLine();
#else
    //*********variable init
    if(-1 != pcontrolInterface->PltLoadConditions())
    {
        pcontrolInterface->blockSignals(true);
        pcontrolInterface->LoadParamControl();
        // //Tony 0619 for set measure mode status after load
        //pcontrolInterface->SetMeasureItems(m_user_variable->currentMode);
        pcontrolInterface->blockSignals(false);
        FullStatus = m_user_variable->FullStatus;
        if(m_user_variable->pbLeftHideChecked) pBitSA->pb_left_hide->setChecked(true);
        else pBitSA->pb_left_hide->setChecked(false);

        //Tony 190704
        m_user_variable->gMsFirstFlag = 0;
        //Tony 190701  init marker count
        SA_guiDrawSet.markerOnCount = 0;
        for (qint32 i = 0; i < MARKER_TOTAL_CNT; i++)
        {
            if (m_user_variable->gMarkerView[i] == SA_ON)
                ++SA_guiDrawSet.markerOnCount ;
        }
        bTableWidgetInitComplete = false;
        //runBtnFunction(m_user_variable->gCurrentWorkState);
        mBtnGroup->button(m_user_variable->gCurrentWorkState)->setChecked(true);
        //slotOperateTable();//Because its parent is not show now ,so tablewidget can not be show here

    }
    else m_user_variable->currentMode = SA_SPAN_MODE;
#endif
}

/**
 * @brief BitSA::initTableInfoWidget
 */
void BitSA::initTableInfoWidget()
{
#if 0
    pBottomInfoWidget = NULL;
    pBottomInfoMarker = NULL;
    pBottomInfoControlWidget = NULL;
    pBottomInfoMarkerControl = NULL;
#else
    
    pACPTable = new sa_widget_ACPTable(*pcontrolInterface,*m_user_variable,*globalUserLimit,this);
    pACPTable->setGeometry(CenterDrawRect.x(),CenterDrawRect.y() + CenterDrawRect.height(),
                           CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,ACP_TABLE_HEIGHT);
    pACPTable->hide();


    pChannelPowerTable = new sa_widget_ChannelPowerTable(*pcontrolInterface,*m_user_variable,*globalUserLimit,this);
    pChannelPowerTable->setGeometry(CenterDrawRect.x(),CenterDrawRect.y() + CenterDrawRect.height(),
                                    CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,CHANNELPOWER_TABLE_HEIGHT);
    pChannelPowerTable->hide();


    pMarkerTable = new sa_widget_markerTable(*pcontrolInterface,*m_user_variable,*globalUserLimit,this);
    pMarkerTable->setGeometry(CenterDrawRect.x(),CenterDrawRect.y() + CenterDrawRect.height(),
                              CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,MARKER_TABLE_HEIGHT);
    pMarkerTable->hide();


    pOccupiedXdBTable = new sa_widget_OccupiedXdBTable(*m_user_variable,*globalUserLimit,this);
    pOccupiedXdBTable->setGeometry(CenterDrawRect.x(),CenterDrawRect.y() + CenterDrawRect.height(),
                                   CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,OCCUPIED_TABLE_HEIGHT);
    pOccupiedXdBTable->hide();


    pMultiACPTable = new sa_widget_MultiACPTable(*pcontrolInterface,*m_user_variable,*globalUserLimit,this);
    pMultiACPTable->setGeometry(CenterDrawRect.x(),CenterDrawRect.y() + CenterDrawRect.height(),
                                CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,MULTIACP_TABLE_HEIGHT);
    pMultiACPTable->hide();


    pSpectrumEMTable = new sa_widget_SpectrumEMTable(*pcontrolInterface,*m_user_variable,*globalUserLimit,this);
    pSpectrumEMTable->setGeometry(CenterDrawRect.x(),CenterDrawRect.y() + CenterDrawRect.height(),
                                  CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,SPECEM_TABLE_HEIGHT);
    pSpectrumEMTable->hide();


    pSpuriousEMTable = new sa_widget_SpuriousEMTable(*pcontrolInterface,*m_user_variable,*globalUserLimit,this);
    pSpuriousEMTable->setGeometry(CenterDrawRect.x(),CenterDrawRect.y() + CenterDrawRect.height(),
                                  CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,SPECEM_TABLE_HEIGHT);
    pSpuriousEMTable->hide();


    pControlACPTable = new sa_ControlWidget_ACPTable(*m_user_variable,this);
    pControlACPTable->setGeometry(CenterDrawRect.x() + CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,CenterDrawRect.y() + CenterDrawRect.height(),
                                  RIGHT_CONTROLWIDGET_WIDTH,ACP_TABLE_HEIGHT);
    pControlACPTable->hide();
    connect(pControlACPTable,SIGNAL(signalHideTable(quint32)),this,SLOT(slotHideTable(quint32)));


    pControlChannelPowerTable = new sa_controlWidget_ChnlTable(*m_user_variable,this);
    pControlChannelPowerTable->setGeometry(CenterDrawRect.x() + CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,CenterDrawRect.y() + CenterDrawRect.height(),
                                           RIGHT_CONTROLWIDGET_WIDTH,CHANNELPOWER_TABLE_HEIGHT);
    pControlChannelPowerTable->hide();
    connect(pControlChannelPowerTable,SIGNAL(signalHideTable(quint32)),this,SLOT(slotHideTable(quint32)));


    pControlMarkerTable = new sa_controlWidget_MarkerTable(*m_user_variable,this);
    pControlMarkerTable->setGeometry(CenterDrawRect.x() + CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,CenterDrawRect.y() + CenterDrawRect.height(),
                                     RIGHT_CONTROLWIDGET_WIDTH,ACP_TABLE_HEIGHT);
    pControlMarkerTable->hide();
    connect(pControlMarkerTable,SIGNAL(signalHideTable(quint32)),this,SLOT(slotHideTable(quint32)));


    pControlpOccupiedXdBTable = new sa_controlWidget_OccupiedXdBTable(*m_user_variable,this);
    pControlpOccupiedXdBTable->setGeometry(CenterDrawRect.x() + CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,CenterDrawRect.y() + CenterDrawRect.height(),
                                           RIGHT_CONTROLWIDGET_WIDTH,CHANNELPOWER_TABLE_HEIGHT);
    pControlpOccupiedXdBTable->hide();
    connect(pControlpOccupiedXdBTable,SIGNAL(signalHideTable(quint32)),this,SLOT(slotHideTable(quint32)));


    pControlMultiACPTable = new sa_ControlWidget_MultiACPTable(*m_user_variable,this);
    pControlMultiACPTable->setGeometry(CenterDrawRect.x() + CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,CenterDrawRect.y() + CenterDrawRect.height(),
                                       RIGHT_CONTROLWIDGET_WIDTH,MULTIACP_TABLE_HEIGHT);
    pControlMultiACPTable->hide();
    connect(pControlMultiACPTable,SIGNAL(signalHideTable(quint32)),this,SLOT(slotHideTable(quint32)));


    pControlSpectrumEMTable = new sa_ControlWidget_SpectrumEMTable(*m_user_variable,this);
    pControlSpectrumEMTable->setGeometry(CenterDrawRect.x() + CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,CenterDrawRect.y() + CenterDrawRect.height(),
                                         RIGHT_CONTROLWIDGET_WIDTH,SPECEM_TABLE_HEIGHT);
    pControlSpectrumEMTable->hide();
    connect(pControlSpectrumEMTable,SIGNAL(signalHideTable(quint32)),this,SLOT(slotHideTable(quint32)));


    pControlSpuriousEMTable = new sa_ControlWidget_SpuriousEMTable(*m_user_variable,this);
    pControlSpuriousEMTable->setGeometry(CenterDrawRect.x() + CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,CenterDrawRect.y() + CenterDrawRect.height(),
                                         RIGHT_CONTROLWIDGET_WIDTH,SPECEM_TABLE_HEIGHT);
    pControlSpuriousEMTable->hide();
    connect(pControlSpuriousEMTable,SIGNAL(signalHideTable(quint32)),this,SLOT(slotHideTable(quint32)));

#endif
}


/**
 * @brief BitSA::getLimitDot
 */
void BitSA::getLimitDot()
{
    //on_escButton_clicked();
}

/**
 * @brief BitSA::judgeTableContent
 */
void BitSA::judgeTableContent(/*QTableWidget *tableWidget, unsigned long long startFreq, unsigned long long stopFreq*/)
{
    //Johnson 1008 Add
    QString strValue;
    char cTmpValue[20];
    char cItemValue[20];
    QTableWidgetItem *tableWidgetItem;

    //**********************Johnson 1107*******************
    if(pBitSA->tableWidget->rowCount() == 0) return;

    char currFrqValue[20];
    memset(currFrqValue,0,sizeof(char)*20);
    char currAmpValue[20];
    memset(currAmpValue,0,sizeof(char)*20);

    tableWidgetItem = pBitSA->tableWidget->item(0,0);
    strValue = tableWidgetItem->text();
    qsnprintf(currFrqValue,sizeof(currFrqValue),"%s",strValue.toUtf8().constData());
    tableWidgetItem = pBitSA->tableWidget->item(0,1);
    strValue = tableWidgetItem->text();
    qsnprintf(currAmpValue,sizeof(currAmpValue),"%s",strValue.toUtf8().constData());

    for(int i = 1;i<pBitSA->tableWidget->rowCount();i++) {
        char FreqValue[20];
        memset(FreqValue,0,sizeof(FreqValue));
        char AmpValue[20];
        memset(AmpValue,0,sizeof(AmpValue));

        tableWidgetItem = pBitSA->tableWidget->item(i,0);
        strValue = tableWidgetItem->text();
        qsnprintf(FreqValue,sizeof(FreqValue),"%s",strValue.toUtf8().constData());
        tableWidgetItem = pBitSA->tableWidget->item(i,1);
        strValue = tableWidgetItem->text();
        qsnprintf(AmpValue,sizeof(AmpValue),"%s",strValue.toUtf8().constData());

        if(atof(currFrqValue) - atof(FreqValue) == 0  && atof(currAmpValue) - atof(AmpValue) == 0) {
            pBitSA->tableWidget->removeRow(0);
            break;
        }
    }
    //*****************************************************

    for(int i = 0;i<pBitSA->tableWidget->rowCount();i++) {
        memset(cTmpValue,0,sizeof(char)*20);
        memset(cItemValue,0,sizeof(cItemValue));

        //Freq
        tableWidgetItem = pBitSA->tableWidget->item(i,0);
        strValue = tableWidgetItem->text();
        qsnprintf(cItemValue,sizeof(cItemValue),"%s",strValue.toUtf8().constData());

        if(atof(cItemValue)*1000000 < m_user_variable->gStartFreq) {
            sprintf(cTmpValue,"%.2f",m_user_variable->gStartFreq/1000000.);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            pBitSA->tableWidget->setItem(i,0,tableWidgetItem);
        }
        else if(atof(cItemValue)*1000000 > m_user_variable->gStopFreq) {
            sprintf(cTmpValue,"%.2f",m_user_variable->gStopFreq/1000000.);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            pBitSA->tableWidget->setItem(i,0,tableWidgetItem);
        }
        else {
            tableWidgetItem = new QTableWidgetItem(QString::number(atof(cItemValue),'f',2));
            pBitSA->tableWidget->setItem(i,0,tableWidgetItem);
        }

        //Amplitude
        tableWidgetItem = pBitSA->tableWidget->item(i,1);
        strValue = tableWidgetItem->text();
        qsnprintf(cItemValue,sizeof(cItemValue),"%s",strValue.toUtf8().constData());

        if(atof(cItemValue) - TABLEWIDGET_AMP_MIN< 0.) {
            sprintf(cTmpValue,"%.2f",TABLEWIDGET_AMP_MIN);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            pBitSA->tableWidget->setItem(i,1,tableWidgetItem);
        }
        else if(atof(cItemValue) - TABLEWIDGET_AMP_MAX > 0.) {
            sprintf(cTmpValue,"%.2f",TABLEWIDGET_AMP_MAX);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            pBitSA->tableWidget->setItem(i,1,tableWidgetItem);
        }
        else {
            tableWidgetItem = new QTableWidgetItem(QString::number(atof(cItemValue),'f',2));
            pBitSA->tableWidget->setItem(i,1,tableWidgetItem);
        }
    }
}
/**
* get table conent
* @param[in] void
* @return    void
*/
void BitSA::getTableWidgetValue(void)
{
    QString strFreq,strAmplitude;
    QTableWidgetItem *widgetItem;

    if(!pBitSA->tableWidget->rowCount()){
        for(int i = 0;i<globalUserLimit->gTotalDot[globalUserLimit->gLimitSelect];i++){
            globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i] = 0.;
            globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i] = 0.;

            globalUserLimit->limitXAxisCalculatorFunc((unsigned long long)(globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i]*SA_MHZ),i,globalUserLimit->gLimitSelect);
            globalUserLimit->LatestLimitYAxisCalculatorFunc(globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i],i,globalUserLimit->gLimitSelect);
        }
        globalUserLimit->gTotalDot[globalUserLimit->gLimitSelect] = 0;
    }
    else {
        globalUserLimit->gTotalDot[globalUserLimit->gLimitSelect] = pBitSA->tableWidget->rowCount();
        for(int i = 0;i<pBitSA->tableWidget->rowCount();i++){
            widgetItem = pBitSA->tableWidget->item(i,0);
            strFreq = widgetItem->text();
            globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i] = strFreq.toDouble();

            widgetItem = pBitSA->tableWidget->item(i,1);
            strAmplitude = widgetItem->text();
            globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i] = strAmplitude.toDouble();
        }

        //sort
        for(int i = 0;i<pBitSA->tableWidget->rowCount();i++){
            for(int j = i+1;j<pBitSA->tableWidget->rowCount();j++){
                if(globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i]>globalUserLimit->gFreq[globalUserLimit->gLimitSelect][j]){
                    qreal tmp = 0.;
                    tmp = globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i];
                    globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i] = globalUserLimit->gFreq[globalUserLimit->gLimitSelect][j];
                    globalUserLimit->gFreq[globalUserLimit->gLimitSelect][j] = tmp;

                    tmp = globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i];
                    globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i] = globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][j];
                    globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][j] = tmp;
                }
            }
        }
    }
}
/**
* initialize tableWidget content
* @param[in] viod
* @return    void
*/
void BitSA::initTableWidgetValue(void)
{
    QString strFreq;
    QString strAmplitude;

    int rowNum = pBitSA->tableWidget->rowCount();

    for(int i = rowNum-1;i>=0;i--){
        pBitSA->tableWidget->removeRow(i);
    }

    for(int i = 0;i<globalUserLimit->gTotalDot[globalUserLimit->gLimitSelect];i++){
        strFreq = QString::number(globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i],'f',2);
        QTableWidgetItem *freqItem = new QTableWidgetItem(strFreq);
        strAmplitude = QString::number(globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i],'f',2);
        QTableWidgetItem *amplitudeItem = new QTableWidgetItem(strAmplitude);

        pBitSA->tableWidget->insertRow(i);
        pBitSA->tableWidget->setItem(i,0,freqItem);
        pBitSA->tableWidget->setItem(i,1,amplitudeItem);
    }

    pBitSA->tableWidget->resetAllParam();
}
void BitSA::traceAverageProcessFunction(qint32 traceNo)
{
    int i = 0;
    if(1 == m_user_variable->greAvager[traceNo])
    {
        //re average data
        memcpy(m_user_variable->gBitTraceAverage[traceNo],m_user_variable->gOriginalMeasureVal,sizeof(qreal) * m_user_variable->gSweepTracePoint );
        m_user_variable->gAverageNo[traceNo] = 0;//Johnson 190417
        m_user_variable->greAvager[traceNo] = 0;

        //Johnson 190412
        #if 0
        SA_sm_config_sweep->uAllSweepCompleteFlag = 0;
        #endif

    }

    //Johnson 190430
    if(m_user_variable->gAverageNo[traceNo] == m_user_variable->gAverageCount[traceNo] - 1)
    {
        #if 0
        SA_sm_config_sweep->uAllSweepCompleteFlag = 1;
        #endif
    }

    if(m_user_variable->gAverageNo[traceNo] >= m_user_variable->gAverageCount[traceNo])//Johnson 190417
    {
        m_user_variable->gAverageNo[traceNo] = m_user_variable->gAverageCount[traceNo];
        //Johnson 190412
        //SA_sm_config_sweep->uAllSweepCompleteFlag = 1;
    }
    if(pcontrolInterface->getCurrentMode() != SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        for(i = 0; i < m_user_variable->gSweepTracePoint; i++)
        {
            ////Johnson 190417
            if(traceNo == 0)
                *(m_user_variable->gBitTraceAverage[traceNo] + i) = (*(m_user_variable->gBitTraceAverage[traceNo]+i) * m_user_variable->gAverageNo[traceNo] + (*(m_user_variable->gOriginalMeasureVal+i) /*- 10*/)) / (m_user_variable->gAverageNo[traceNo] + 1);
            else if(traceNo == 1)
                *(m_user_variable->gBitTraceAverage[traceNo] + i) = (*(m_user_variable->gBitTraceAverage[traceNo]+i) * m_user_variable->gAverageNo[traceNo] + (*(m_user_variable->gOriginalMeasureVal+i) /*- 5*/)) / (m_user_variable->gAverageNo[traceNo] + 1);
            else if(traceNo == 2)
                *(m_user_variable->gBitTraceAverage[traceNo] + i) = (*(m_user_variable->gBitTraceAverage[traceNo]+i) * m_user_variable->gAverageNo[traceNo] + (*(m_user_variable->gOriginalMeasureVal+i) /*- 2*/)) / (m_user_variable->gAverageNo[traceNo] + 1);
            else if(traceNo == 3)
                *(m_user_variable->gBitTraceAverage[traceNo] + i) = (*(m_user_variable->gBitTraceAverage[traceNo]+i) * m_user_variable->gAverageNo[traceNo] + (*(m_user_variable->gOriginalMeasureVal+i) /*+ 2*/)) / (m_user_variable->gAverageNo[traceNo] + 1);
            else if(traceNo == 4)
                *(m_user_variable->gBitTraceAverage[traceNo] + i) = (*(m_user_variable->gBitTraceAverage[traceNo]+i) * m_user_variable->gAverageNo[traceNo] + (*(m_user_variable->gOriginalMeasureVal+i) /*+ 5*/)) / (m_user_variable->gAverageNo[traceNo] + 1);
            else if(traceNo == 5)
                *(m_user_variable->gBitTraceAverage[traceNo] + i) = (*(m_user_variable->gBitTraceAverage[traceNo]+i) * m_user_variable->gAverageNo[traceNo] + (*(m_user_variable->gOriginalMeasureVal+i) /*+ 10*/)) / (m_user_variable->gAverageNo[traceNo] + 1);
        }
        memcpy(m_user_variable->gTraceMeasureVal[traceNo],m_user_variable->gBitTraceAverage[traceNo],sizeof(qreal) * m_user_variable->gSweepTracePoint);
    }
    refreshTrace(SA_INFO_TRACE_CURAVE);
    if(pcontrolInterface->getCurrentMode() == SA_SPECTRUM_EMISSION_MASK_MODE ||\
            pcontrolInterface->getCurrentMode() == SA_SPURIOUS_EMISSION_MASK_MODE)
    {
        if(m_user_variable->gMsComplete)
        {
            m_user_variable->gAverageNo[traceNo]++;
        }
    }
    else
    {
        if(m_user_variable->gMsComplete/*SA_sm_config_sweep->uSweepCompleteFlag*/)
        {
            m_user_variable->gAverageNo[traceNo]++;
        }
    }
}

void BitSA::presetStatesProcess()
{
    //Johnson 190822
    if(pcontrolInterface->bDefaultStatesPreset)
    {
        FullStatus = m_user_variable->FullStatus;
        if(m_user_variable->pbLeftHideChecked) pBitSA->pb_left_hide->setChecked(true);
        else pBitSA->pb_left_hide->setChecked(false);

        m_user_variable->gMsFirstFlag = 0;
        SA_guiDrawSet.markerOnCount = 0;
        for (qint32 i = 0; i < MARKER_TOTAL_CNT; i++)
        {
            if (m_user_variable->gMarkerView[i] == SA_ON)
                ++SA_guiDrawSet.markerOnCount ;
        }
        bTableWidgetInitComplete = false;
        mBtnGroup->button(m_user_variable->gCurrentWorkState)->setChecked(true);

        pcontrolInterface->bDefaultStatesPreset = false;
    }
}

void BitSA::graphRefreshFunc()
{
    pthread_mutex_lock(&SA_lockobj);
    //Tony 190701
    if(this->isHidden() && !bTableWidgetInitComplete)
    {
        pthread_mutex_unlock(&SA_lockobj);
        return;
    }
    pcontrolInterface->ZeroRestrainCelibrate();//Johnson 190423

    //Johnson 190621
    if(m_user_variable->gMarkerFreqCount[m_user_variable->gMarkerSelect])
        m_user_variable->gFreqCount = pcontrolInterface->getFreqCount(m_user_variable->gSignalFreq + m_user_variable->gfreqOffset,
                                                                  m_user_variable->gFsr,m_user_variable->gRbw);

    presetStatesProcess();

    if(!bTableWidgetInitComplete)
    {
        pcontrolInterface->SetMeasureItems(m_user_variable->currentMode);
        slotOperateTable();
        bTableWidgetInitComplete = true;
    }
    if(!pcontrolInterface->getSuspendFunc())
    {
        //at first
        if(m_user_variable->gMsFirstFlag)
        {
            if(pcontrolInterface->getCurrentMode()==SA_SPECTRUM_EMISSION_MASK_MODE ||
                    pcontrolInterface->getCurrentMode()==SA_SPURIOUS_EMISSION_MASK_MODE)
            {
                #if 0
                if(SA_sm_config_sweep->SweepType == SA_CONT)
                {
                    SA_sm_config_sweep->SweepType = SA_SINGLE;
                }
                #endif
               m_user_variable->gMsComplete = 1;
               //SA_sm_config_sweep->uSweepCompleteFlag = 1;
               #if 0
               SA_sm_config_sweep->uAllSweepCompleteFlag = 1;
               #endif
               if(pcontrolInterface->getCurrentMode()==SA_SPECTRUM_EMISSION_MASK_MODE)
               {
                    singparamflag = 1;
               }
            }
#if 0
            if(pcontrolInterface->getCurrentMode()==SA_SPECTRUM_EMISSION_MASK_MODE)
            {
                psa_UIRefresh_Control->refreshPixmap();
                repaint(CenterDrawRect);
                bottomInfoShow();

                if(!setParaForSEM())
                {
                    pthread_mutex_unlock(&SA_lockobj);
                    return;
                }
                pthread_mutex_unlock(&SA_lockobj);
                return;
            }else if(pcontrolInterface->getCurrentMode()==SA_SPURIOUS_EMISSION_MASK_MODE)
            {
                psa_UIRefresh_Control->refreshPixmap();
                repaint(CenterDrawRect);
                bottomInfoShow();

                if(!setParaForSpurEM())
                {
                    pthread_mutex_unlock(&SA_lockobj);
                    return;
                }

                pthread_mutex_unlock(&SA_lockobj);
                return;
            }
#endif
        }
        processRawData();
    }
    psa_Amplitude_Control->AutoAttenTrackControl();
    if(globalUserLimit->gLimitLine[0] == SA_OFF && globalUserLimit->gLimitLine[1] == SA_OFF &&
            globalUserLimit->gLimitLine[2] == SA_OFF && globalUserLimit->gLimitLine[3] == SA_OFF &&
            globalUserLimit->gLimitLine[4] == SA_OFF && globalUserLimit->gLimitLine[5] == SA_OFF)
        psa_UIRefresh_Control->refreshCurves(false);
    else
    {
        psa_UIRefresh_Control->refreshCurves(true);
    }
    if(pcontrolInterface->getPeakTrackStatus())
    {
        pcontrolInterface->searchPeak();
    }
    psa_UIRefresh_Control->refreshPixmap();
#if GLOBAL_REPAINT_OPEN
    repaint(CenterDrawRect);
#else
    repaint(CenterDrawRect.x() + DRAW_GRID_START_X,CenterDrawRect.y() + DRAW_GRID_START_Y,
            CenterDrawRect.width() -SA_LEFTDIS -SA_RIGHTDIS,CenterDrawRect.height()-SA_TOPDIS - SA_BOTTOMDIS);
#endif
    bottomInfoShow();
    //if current mode is specEM && uSpecEMCompleteOnce

    if(m_user_variable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        if((!pcontrolInterface->getSuspendFunc()) && m_user_variable->gMsComplete)
        {
            #if 0
            SA_sm_config_sweep->uSweepCompleteFlag = 0;
            #endif
            if(m_user_variable->gMeasureStatus == SA_ON)
            {
                if(pcontrolInterface->getTraceAverageStatus() == SA_ON)
                {
                    #if 0
                    if(SA_sm_config_sweep->uAllSweepCompleteFlag == 1 || m_user_variable->gMsFirstFlag)
                    #endif
                    if(1)
                    {
                        if(!setParaForSEM())
                        {
                            m_user_variable->gMsComplete = 0;
                            pthread_mutex_unlock(&SA_lockobj);
                            return;
                        }
                        #if 0
                        SA_sm_config_sweep->uAllSweepCompleteFlag = 0;
                        #endif
                        if(m_user_variable->gMeasureStatus == SA_ON)
                        {
                            m_user_variable->gAverageNo[0] = 0;
                            m_user_variable->greAvager[0] = 1;
                        }
                    }
                    else
                    {
                        DelayFunc(50);
                        //if(SA_sm_config_sweep->SweepType == SA_SWEEP_OFF)
                        {
                            #if 0
                            SA_sm_config_sweep->SweepType = SA_SINGLE;
                            #endif
                        }
                    }
                }
                else
                {
                    if(!setParaForSEM())
                    {
                        m_user_variable->gMsComplete = 0;
                        pthread_mutex_unlock(&SA_lockobj);
                        return;
                    }
                }
            }
            m_user_variable->gMsComplete = 0;
        }
    }
    else if(m_user_variable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
    {
        if((!pcontrolInterface->getSuspendFunc()) && m_user_variable->gMsComplete)
        {
            #if 0
            SA_sm_config_sweep->uSweepCompleteFlag = 0;
            #endif
            if(m_user_variable->gMeasureStatus == SA_ON)
            {
                if(pcontrolInterface->getTraceAverageStatus(0) == SA_ON)
                {
                    #if 0
                    if(SA_sm_config_sweep->uAllSweepCompleteFlag == 1 || m_user_variable->gMsFirstFlag)
                    #endif
                    if(1)
                    {
                        if(!setParaForSpurEM())
                        {
                            pthread_mutex_unlock(&SA_lockobj);
                            return;
                        }
                        if(m_user_variable->gMeasureStatus == SA_ON)
                        {
                            m_user_variable->gAverageNo[0] = 0;
                            m_user_variable->greAvager[0] = 1;
                        }
                    }else
                    {
                        DelayFunc(100);
                        //if(SA_sm_config_sweep->SweepType == SA_SWEEP_OFF)
                        {
                            #if 0
                            SA_sm_config_sweep->SweepType = SA_SINGLE;
                            #endif
                        }
                    }
                }else
                {
                    if(!setParaForSpurEM())
                    {
                        pthread_mutex_unlock(&SA_lockobj);
                        return;
                    }
                }
            }
        }

        if(suspendFlag)
        {
            suspendFlag = false;
            if(SA_SPUREM_AVE_EXP == pcontrolInterface->getSpurEMAveType() && SA_CONT == pcontrolInterface->getSweepType())
            {
                pcontrolInterface->setMeasureStatus(SA_OFF);
            }
        }
    }else
    {
        //Set flag for sweep complete flag
        if(m_user_variable->gMsComplete/*SA_sm_config_sweep->uSweepCompleteFlag*/)
        {
            m_user_variable->gMsComplete = 0;
            #if 0
            SA_sm_config_sweep->uSweepCompleteFlag = 0;
            #endif
        }
    }
    /*
    if(m_user_variable->gMsFirstFlag)
    {
        if(pcontrolInterface->getCurrentMode()== SA_SPECTRUM_EMISSION_MASK_MODE ||
                pcontrolInterface->getCurrentMode()==SA_SPURIOUS_EMISSION_MASK_MODE)
        {
           SA_sm_config_sweep->SweepType = SA_SINGLE;
        }
    }*/
    pthread_mutex_unlock(&SA_lockobj);
    return;

}

void BitSA::refreshSpecEMData()
{
    qint32 lowerStart,upperStart,lowerStop,upperStop;
    qreal freq,halfspanFreq,setpFreq;
    qint32 index = m_user_variable->gSpecEMSweepIndex;

    qint32 startIndex[2],stopIndex[2];
    qint32 dataCnt = 0;  //The count of data segment  1 means a section,2 means two sections
    //    if(singparamflag == 1)//need clear status
    //    {
    //        m_user_variable->gSpecEMSweepIndex = 0;
    //        SA_sm_config_sweep->uSpecEMCompleteOnce = 0;
    //    }else if(singparamflag == 2)
    //    {

    //    }else if(singparamflag == 3)
    //    {

    //    }

    //flag of complete data
    //    if(SA_sm_config_sweep->uSpecEMCompleteOnce)
    //    {
    //        setParaForSEM();
    //        SA_sm_config_sweep->uSpecEMCompleteOnce = 0;
    //    }


    halfspanFreq= m_user_variable->gSpanFreq/2;
    setpFreq = 2 * halfspanFreq/(NUM_SWEEP_POINT-1);
    //Calculate the start and end  position
    if(index == 0)
    {
        freq = halfspanFreq  - m_user_variable->gSpecEMData[index].start;
        lowerStart = freq / setpFreq;
        if(lowerStart*setpFreq != freq)
        {
            lowerStart = lowerStart + 1;
        }

        freq = halfspanFreq  + m_user_variable->gSpecEMData[index].start;
        lowerStop = freq / setpFreq;
        if(lowerStop * setpFreq == freq)
        {
            lowerStop = lowerStop - 1;
        }

        dataCnt = 1;
        startIndex[0] = startIndex[1] = lowerStart;
        stopIndex[0]  = stopIndex[1]  = lowerStop;
    }else
    {
        freq = halfspanFreq  - m_user_variable->gSpecEMData[index-1].stop;
        lowerStart = freq / setpFreq;
        if(lowerStart*setpFreq != freq)
        {
            lowerStart = lowerStart + 1;
        }
        freq = halfspanFreq  - m_user_variable->gSpecEMData[index-1].start;
        lowerStop = freq / setpFreq;
        if(lowerStop * setpFreq == freq)
        {
            lowerStop = lowerStop - 1;
        }

        freq = halfspanFreq  + m_user_variable->gSpecEMData[index-1].start;
        upperStart = freq / setpFreq;
        if(upperStart*setpFreq != freq)
        {
            upperStart = upperStart + 1;
        }
        freq = halfspanFreq  + m_user_variable->gSpecEMData[index-1].stop;
        upperStop = freq / setpFreq;
        if(upperStop * setpFreq == freq)
        {
            upperStop = upperStop - 1;
        }
        //Need special treatment
        if(upperStop == m_user_variable->gTracePoint-2)
            upperStop = m_user_variable->gTracePoint-1;
        dataCnt = 2;
        startIndex[0] = lowerStart;
        stopIndex[0]  = lowerStop;
        startIndex[1] = upperStart;
        stopIndex[1]  = upperStop;
    }

    //processing raw data
    int i = 0;
    int k = 0;
    if(singparamflag == 1)
    {
        m_user_variable->gSpecEMSweepIndex = 0; //from 0 start
        for(qint32 i = 0; i< NUM_SWEEP_POINT;i++)
        {
            m_user_variable->gOriginalMeasureVal[i] = m_user_variable->lowLevel - m_user_variable->gRefOffset;
        }
        for(qint32 i = 0;i<TRACE_CNT_TOTAL;i++)
        {
            if(m_user_variable->gTraceType[i] != SA_VIEW)
            {
                memcpy( m_user_variable->gTraceMeasureVal[i], m_user_variable->gOriginalMeasureVal, sizeof(qreal) * m_user_variable->gSweepTracePoint );
            }
        }
        singparamflag = 0;
    }
    else if(singparamflag == 2)//Hold the curve
    {
        singparamflag = 0;
    }
    else if(singparamflag == 3)//Refresh draw curve
    {
        for (i = 0; i < NUM_TRACE; i++ )
        {
            switch (m_user_variable->gTraceType[i])
            {
            case SA_CLEAR_WRITE:
            case SA_TRACE_AVE:
            case SA_MAX_HOLD:
            case SA_MIN_HOLD:
                for(qint32 id = 0;id<dataCnt;id++)
                {
                    for (qint32 k = startIndex[id]; k <= stopIndex[id]; k++)
                    {
                        m_user_variable->gTraceMeasureVal[i][k] = m_user_variable->gOriginalMeasureVal[k];
                    }
                }
            }
        }
        for(qint32 i = 0;i < TRACE_CNT_TOTAL;i++)
        {
            m_user_variable->gAverageNo[i] = 0;
            m_user_variable->greAvager[i] = 1;
        }
        refreshTrace(SA_INFO_TRACE_CURAVE);
        singparamflag = 0;
    }
    else
    {
        for (i = 0; i < NUM_TRACE; i++ )
        {
            if(m_user_variable->gTraceView[i] == SA_OFF)
                continue;
            switch (m_user_variable->gTraceType[i])
            {
            case SA_CLEAR_WRITE:
            case SA_TRACE_AVE:
                if (m_user_variable->gTraceAverage[i] == SA_ON)
                {
                    for(qint32 id = 0;id<dataCnt;id++)
                    {
                        for (k = startIndex[id]; k <= stopIndex[id]; k++)
                        {
                            m_user_variable->gBitTraceAverage[i][k] = (m_user_variable->gBitTraceAverage[i][k] * m_user_variable->gAverageNo[i] + (m_user_variable->gOriginalMeasureVal[k])) / (m_user_variable->gAverageNo[i] + 1);
                            m_user_variable->gTraceMeasureVal[i][k] = m_user_variable->gBitTraceAverage[i][k];
                        }
                    }
                    traceAverageProcessFunction(i);
                }
                else
                {
                    for(qint32 id = 0;id<dataCnt;id++)
                    {
                        for (k = startIndex[id]; k <= stopIndex[id]; k++)
                        {
                            m_user_variable->gTraceMeasureVal[i][k] = m_user_variable->gOriginalMeasureVal[k];
                        }
                    }

                }
                break;
            case SA_MAX_HOLD:
                for(qint32 id = 0;id<dataCnt;id++)
                {
                    for (k = startIndex[id]; k <= stopIndex[id]; k++)
                    {
                        if (m_user_variable->gTraceMeasureVal[i][k] < m_user_variable->gOriginalMeasureVal[k])
                        {
                            m_user_variable->gTraceMeasureVal[i][k] = m_user_variable->gOriginalMeasureVal[k];
                        }
                    }
                }
                break;
            case SA_MIN_HOLD:
                for(qint32 id = 0;id<dataCnt;id++)
                {
                    for (k = startIndex[id]; k <= stopIndex[id]; k++)
                    {
                        if (m_user_variable->gTraceMeasureVal[i][k] > m_user_variable->gOriginalMeasureVal[k])
                        {
                            m_user_variable->gTraceMeasureVal[i][k] = m_user_variable->gOriginalMeasureVal[k];
                        }
                    }
                }
                break;
            case SA_VIEW:

                break;
            }
        }
    }
}

void BitSA::processRawData()
{
    if(m_user_variable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        if(m_user_variable->gMsComplete)
            refreshSpecEMData();
        return;
    }
    int i = 0;
    int k = 0;
    if(singparamflag == 1)
    {
        for(qint32 i = 0; i< NUM_SWEEP_POINT;i++)
        {
            m_user_variable->gOriginalMeasureVal[i] = m_user_variable->lowLevel - m_user_variable->gRefOffset;
        }
        for(qint32 i = 0;i<TRACE_CNT_TOTAL;i++)
        {
            if(m_user_variable->gTraceType[i] != SA_VIEW)
            {
                memcpy(m_user_variable->gTraceMeasureVal[i], m_user_variable->gOriginalMeasureVal, sizeof(qreal) * m_user_variable->gSweepTracePoint);
            }
        }
        singparamflag = 0;
    }
    else if(singparamflag == 2)//Hold the curve
    {
        singparamflag = 0;
    }
    else if(singparamflag == 3)//Refresh draw curve
    {
        for (i = 0; i < NUM_TRACE; i++ )
        {
            switch (m_user_variable->gTraceType[i])
            {
            case SA_CLEAR_WRITE:
            case SA_TRACE_AVE:
            case SA_MAX_HOLD:
            case SA_MIN_HOLD:
                #if 0
                SA_sm_config_sweep->uMinMaxHoldComplete = 0;
                #endif
                m_user_variable->uMinMaxHoldReadComplete = 0;
                memcpy(m_user_variable->gTraceMeasureVal[i], m_user_variable->gOriginalMeasureVal, sizeof(qreal) * m_user_variable->gSweepTracePoint );
                break;
            }
        }
        for(qint32 i = 0;i < TRACE_CNT_TOTAL;i++)
        {
            m_user_variable->gAverageNo[i] = 0;
            m_user_variable->greAvager[i] = 1;
        }
        refreshTrace(SA_INFO_TRACE_CURAVE);
        singparamflag = 0;
    }
    else
    {
        for (i = 0; i < NUM_TRACE; i++ )
        {
            if(m_user_variable->gTraceView[i] == SA_OFF)
                continue;
            switch (m_user_variable->gTraceType[i])
            {
            case SA_CLEAR_WRITE:
            case SA_TRACE_AVE:
                if (m_user_variable->gTraceAverage[i] == SA_ON)
                {
                    traceAverageProcessFunction(i);
                }
                else
                {
                    memcpy( m_user_variable->gTraceMeasureVal[i], m_user_variable->gOriginalMeasureVal, sizeof(qreal) * m_user_variable->gSweepTracePoint );
                }
                break;
            case SA_MAX_HOLD:
                #if 0
                if(!SA_sm_config_sweep->uMinMaxHoldComplete)
                #endif
                if(1)
                {
                    memcpy( m_user_variable->gTraceMeasureVal[i], m_user_variable->gOriginalMeasureVal, sizeof(qreal) * m_user_variable->gSweepTracePoint );
                }
                else
                {
                    if(!m_user_variable->uMinMaxHoldReadComplete)
                    {
                        memcpy( m_user_variable->gTraceMeasureVal[i], m_user_variable->gOriginalMeasureVal, sizeof(qreal) * m_user_variable->gSweepTracePoint );
                        m_user_variable->uMinMaxHoldReadComplete = 1;
                    }
                    else
                    {
                        for (k = 0; k < m_user_variable->gSweepTracePoint; k++)
                        {
                            if (m_user_variable->gTraceMeasureVal[i][k] < m_user_variable->gOriginalMeasureVal[k])
                            {
                                m_user_variable->gTraceMeasureVal[i][k] = m_user_variable->gOriginalMeasureVal[k];
                            }
                        }
                    }
                }

                break;
            case SA_MIN_HOLD:
                #if 0
                if(!SA_sm_config_sweep->uMinMaxHoldComplete)
                #endif
                if(1)
                {
                    memcpy( m_user_variable->gTraceMeasureVal[i], m_user_variable->gOriginalMeasureVal, sizeof(qreal) * m_user_variable->gSweepTracePoint );
                }
                else
                {
                    if(!m_user_variable->uMinMaxHoldReadComplete)
                    {
                        memcpy( m_user_variable->gTraceMeasureVal[i], m_user_variable->gOriginalMeasureVal, sizeof(qreal) * m_user_variable->gSweepTracePoint );
                        m_user_variable->uMinMaxHoldReadComplete = 1;
                    }
                    else
                    {
                        for (k = 0; k < m_user_variable->gSweepTracePoint; k++)
                        {
                            if (m_user_variable->gTraceMeasureVal[i][k] > m_user_variable->gOriginalMeasureVal[k])
                            {
                                m_user_variable->gTraceMeasureVal[i][k] = m_user_variable->gOriginalMeasureVal[k];
                            }
                        }
                    }
                }

                break;
            case SA_VIEW:
                //                memcpy( m_user_variable->gTraceMeasureVal[i], m_user_variable->gOriginalMeasureVal, sizeof(qreal) * m_user_variable->gSweepTracePoint);
                break;
            }
        }
    }
}

#if SMALL_LARGE_PIXMAP_IMAGE
void BitSA::setPixmap(bool bSmall)
{
    m_user_variable->bSmallCanvas = bSmall;
    if(bSmall)
    {
        repaint(LARGEDRAW_START_X,LARGEDRAW_START_Y,LARGEDRAW_WIDTH,LARGEDRAW_HEIGHT);
    }
    else
    {
        repaint(SMALLDRAW_START_X,SMALLDRAW_START_Y,SMALLDRAW_WIDTH,SMALLDRAW_HEIGHT);
    }
    psa_UIRefresh_Control->refreshRelativePara();
}
void BitSA::setImage(bool bSmall)
{
    m_user_variable->bSmallCanvas = bSmall;
    psa_UIRefresh_Control->refreshRelativePara();
}
#endif

void BitSA::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    pBitSA->tableWidget->resize(TABLEWIDGET_WIDTH,m_user_variable->gridYPos[GRIDY_LENGTH-1]-GRID_START_Y);

    if(reflag)
    {

    }
    else
    {
        painter.drawPixmap(CenterDrawRect,psa_UIRefresh_Control->mPixmap);
    }
#if 1
    //    if(m_user_variable->bSmallCanvas)
    //    {
    #if SMALL_LARGE_PIXMAP_IMAGE
    //        painter.drawPixmap(SMALLDRAW_START_X,SMALLDRAW_START_Y,psa_UIRefresh_Control->smallPixmap);
    #endif
    //    }
    //    else
    //    {
    ////        pBitSA->topButtonBar->hide();
    ////        pBitSA->groupBox_3->hide();
    ////        pBitSA->groupBox_4->hide();
    #if SMALL_LARGE_PIXMAP_IMAGE
    //        painter.drawPixmap(LARGEDRAW_START_X,LARGEDRAW_START_Y,psa_UIRefresh_Control->largePixmap);
    #endif
    //    }
#else
    if(bSmallImage)
    {
        painter.drawImage(SMALLDRAW_START_X,SMALLDRAW_START_Y,psa_UIRefresh_Control->smallImage);
    }
    else
    {
        painter.drawImage(LARGEDRAW_START_X,LARGEDRAW_START_Y,psa_UIRefresh_Control->largeImage);
    }
    //painter.drawImage(0,0,image);//Johnson 0622 test 3 and test1

    //**********Johnson 0820 use the imageData to constructor the QImage and show the image test2**********
    painter.drawImage(GRID_START_X,GRID_START_Y,imageFromData);
    painter.fillRect(QRectF(62,107,GRID_START_X-60,632),Qt::black);
    painter.fillRect(QRectF(GRID_START_X,107,PAINTAREA_WIDTH-GRID_START_X,GRID_START_Y-107),Qt::black);
    painter.fillRect(QRectF(GRID_START_X,GRID_START_Y+GRID_HEIGHT,806-60,632-GRID_HEIGHT-(GRID_START_Y-107)),Qt::black);
    painter.fillRect(QRectF(GRID_START_X+GRID_WIDTH,GRID_START_Y,PAINTAREA_WIDTH-(GRID_START_X+GRID_WIDTH),632-(GRID_START_Y-107)),Qt::black);
    drawGrid(&painter);
    //***********************************************************************************************
#endif

}
void BitSA::mousePressEvent(QMouseEvent *event)
{
    SA_Dialog_MarkerSetup* mMarkerSetup;
    if(event->x() >= CenterDrawRect.x() && event->y() >= CenterDrawRect.y())
    {
        psa_UIRefresh_Control->mousePressReflect(event->x() - CenterDrawRect.x(),event->y() - CenterDrawRect.y(),m_user_variable->bSmallCanvas);
        //        on_refreshMarkerInfo();
        if(mSetupDialog && m_user_variable->PrimaryAction == SA_MARKER)
        {
            mMarkerSetup = (SA_Dialog_MarkerSetup*)mSetupDialog;
            mMarkerSetup->refreshDisplay();
        }
    }
}
void BitSA::mouseMoveEvent(QMouseEvent *event)
{
    SA_Dialog_MarkerSetup* mMarkerSetup;
    if(event->x() >= CenterDrawRect.x() && event->y() >= CenterDrawRect.y())
    {
        psa_UIRefresh_Control->mouseMoveReflect(event->x() - CenterDrawRect.x(),event->y() - CenterDrawRect.y(),m_user_variable->bSmallCanvas);
        if(mSetupDialog && m_user_variable->PrimaryAction == SA_MARKER)
        {
            mMarkerSetup = (SA_Dialog_MarkerSetup*)mSetupDialog;
            mMarkerSetup->refreshDisplay();
        }
    }

    #if 0
    if(1 == SA_sm_config_sweep->ListenState)
    #endif
    {
        psa_UIRefresh_Control->refreshPixmap();
        repaint(CenterDrawRect);
    }
}
void BitSA::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->x() >= SMALLDRAW_START_X && event->y() >= SMALLDRAW_START_Y)
        psa_UIRefresh_Control->mouseRealseReflect(event->x() - SMALLDRAW_START_X,event->y() - SMALLDRAW_START_Y,m_user_variable->bSmallCanvas);
}

void BitSA::keyPressEvent(QKeyEvent *event)
{
    qint32 priAction = m_user_variable->PrimaryAction;
    qreal stepValue,curValue;
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            emit KeyEventSig(Qt::Key_PowerOff);
        return;
    }
    if(event->key() == Qt::Key_Escape)
    {
        if(m_user_variable->gRunMode == SA_REMOTE && m_user_variable->gLockStatus != SA_ON)
        {
            //to tell platform convert to local state from remote
            if(!event->isAutoRepeat())
            {
                emit KeyEventSig(Qt::Key_Escape);
            }
            return;
        }else if(m_user_variable->gRunMode != SA_REMOTE && m_user_variable->gLockStatus == SA_ON)
        {
            if(!event->isAutoRepeat())
            {
                emit KeyEventSig(Qt::Key_Escape + 2);
//                pBitSA->rightButton4->setChecked(false);
//                m_user_variable->gLockStatus = SA_OFF;
            }
            return;
        }else if(m_user_variable->gRunMode == SA_REMOTE && m_user_variable->gLockStatus == SA_ON)
        {
            if(!event->isAutoRepeat())
            {
                emit KeyEventSig(Qt::Key_Escape + 3);
//                pBitSA->rightButton4->setChecked(false);
//                m_user_variable->gLockStatus == SA_OFF;
            }
            return;
        }
    }
    if(m_user_variable->gRunMode == SA_REMOTE || m_user_variable->gLockStatus == SA_ON)
    {
        if(event->key()==Qt::Key_Escape)
        {
            //to tell platform convert to local state from remote
            if(!event->isAutoRepeat())
                emit KeyEventSig(Qt::Key_Escape);
        }
        return;
    }

    if(mSetupDialog && event->key() == Qt::Key_Shift)
    {
        menuClose();
    }
    else if(mSetupDialog && !((priAction == SA_MARKER || \
                               priAction == SA_MARKER_TAB) && (event->key() == Qt::Key_F3 ||event->key() == Qt::Key_F4 || \
                                                               event->key() == Qt::Key_F5 ||event->key() == Qt::Key_F6 || \
                                                               event->key() == Qt::Key_F7 ||event->key() == Qt::Key_F8 || \
                                                               event->key() == Qt::Key_Up ||event->key() == Qt::Key_Down || \
                                                               event->key() == Qt::Key_Right ||event->key() == Qt::Key_Left)))
    {
        mSetupDialog->setFocus();
        QCoreApplication::sendEvent(mSetupDialog, event);
        return;
    }
    switch (event->key())
    {
    case Qt::Key_Shift:
        if(m_user_variable->bShiftKeyPressed)
            m_user_variable->bShiftKeyPressed = false;
        else
            m_user_variable->bShiftKeyPressed = true;
        break;
    case Qt::Key_0://System
        if(m_user_variable->bShiftKeyPressed)
        {
            on_rightButton8_clicked();
            //m_user_variable->bShiftKeyPressed = false;
        }
        break;
    case Qt::Key_1:
        if(m_user_variable->bShiftKeyPressed)
        {
            showMenu(SA_FREQ_DIALOG);
            mBtnGroup->button(SA_FREQ_DIALOG)->setChecked(true);
            //m_user_variable->bShiftKeyPressed = false;
        }
        break;
    case Qt::Key_2:
        if(m_user_variable->bShiftKeyPressed)
        {
            on_rightButton9_clicked();
            //m_user_variable->bShiftKeyPressed = false;
        }

        break;
    case Qt::Key_3:
        if(m_user_variable->bShiftKeyPressed)
        {
            showMenu(SA_AMPT_DIALOG);
            mBtnGroup->button(SA_AMPT_DIALOG)->setChecked(true);
            //m_user_variable->bShiftKeyPressed = false;
        }
        break;
    case Qt::Key_4:
        if(m_user_variable->bShiftKeyPressed)
        {
            showMenu(SA_MEASURE_DIALOG);
            mBtnGroup->button(SA_MEASURE_DIALOG)->setChecked(true);
            //m_user_variable->bShiftKeyPressed = false;
        }
        break;
    case Qt::Key_5:
        if(m_user_variable->bShiftKeyPressed)
        {
            showMenu(SA_DISPLAY_DIALOG);
            mBtnGroup->button(SA_DISPLAY_DIALOG)->setChecked(true);
            //m_user_variable->bShiftKeyPressed = false;
        }
        break;
    case Qt::Key_6:
        if(m_user_variable->bShiftKeyPressed)
        {
            showMenu(SA_MEASUREPARASET_DIALOG);
            mBtnGroup->button(SA_MEASUREPARASET_DIALOG)->setChecked(true);
            //m_user_variable->bShiftKeyPressed = false;
        }

        break;
    case Qt::Key_7:
        if(m_user_variable->bShiftKeyPressed)
        {
            showMenu(SA_LIMIT_DIALOG);
            mBtnGroup->button(SA_LIMIT_DIALOG)->setChecked(true);
            //m_user_variable->bShiftKeyPressed = false;
        }
        break;
    case Qt::Key_8://Save
        if(m_user_variable->bShiftKeyPressed)
        {
            // showMenu(SA_MEASURE_DIALOG);
            // mBtnGroup->button(SA_MEASURE_DIALOG)->setChecked(true);
            //m_user_variable->bShiftKeyPressed = false;
            on_rightButton6_clicked();
        }

        break;
    case Qt::Key_9://Marker
        if(m_user_variable->bShiftKeyPressed)
        {
            showMenu(SA_MARKER_DIALOG);
            mBtnGroup->button(SA_MARKER_DIALOG)->setChecked(true);
            //m_user_variable->bShiftKeyPressed = false;
        }
        break;
    case Qt::Key_F2:
    case Qt::Key_Minus: //Preset
        qDebug()<<"enter key_f2 ";
        if(m_user_variable->bShiftKeyPressed)
        {
            qDebug()<<"enter load circle ";
            // showMenu(SA_MARKER_DIALOG);
            // mBtnGroup->button(SA_MARKER_DIALOG)->setChecked(true);
            m_user_variable->bShiftKeyPressed = false;

            //Johnson 190822
            emit PltAllPresetSig();
            //pcontrolInterface->PresetDefaultStates();
        }
        break;
    case Qt::Key_Period://Trace
        if(m_user_variable->bShiftKeyPressed)
        {
            showMenu(SA_TRACE_DIALOG);
            mBtnGroup->button(SA_TRACE_DIALOG)->setChecked(true);
            //m_user_variable->bShiftKeyPressed = false;
        }
        break;
    case Qt::Key_F3://clockwise //Johnson 0629 0726
        if(priAction == SA_SWEEP)
        {
            if(m_user_variable->gAutoSweepTime == SA_OFF)
            {
                curValue = m_user_variable-> gSweepTime;
                stepValue = m_user_variable->getTimeUnit(curValue);
                curValue += stepValue;
                pcontrolInterface->setSweepTime(curValue);
            }
        }
        else if(priAction == SA_AMPLITUDE)
        {
            curValue = m_user_variable-> gRefLevel;
            stepValue = 0.01;
            curValue += stepValue;
            pcontrolInterface->setRefLevel(curValue);
        }
        else if(priAction == SA_FREQUENCY)
        {
            curValue = pcontrolInterface->getCenterFreq();
            stepValue = pcontrolInterface->getCFFreq();
            curValue += stepValue;
            pcontrolInterface->setCenterFreq(curValue);
        }
        else
        {
            psa_UIRefresh_Control->keyPressReflect(event->key());
        }
        break;
    case Qt::Key_F4:
        if(priAction == SA_SWEEP)
        {
            if(m_user_variable->gAutoSweepTime == SA_OFF)
            {
                curValue = m_user_variable-> gSweepTime;
                stepValue = m_user_variable->getTimeUnit(curValue);
                curValue -= stepValue;
                pcontrolInterface->setSweepTime(curValue);
            }
        }
        else if(priAction == SA_AMPLITUDE){
            curValue = m_user_variable-> gRefLevel;
            stepValue = 0.01;
            curValue -= stepValue;
            pcontrolInterface->setRefLevel(curValue);
        }
        else if(priAction == SA_FREQUENCY)
        {
            curValue = pcontrolInterface->getCenterFreq();
            stepValue = pcontrolInterface->getCFFreq();
            curValue -= stepValue;
            pcontrolInterface->setCenterFreq(curValue);
        }
        else
        {
            psa_UIRefresh_Control->keyPressReflect(event->key());
        }
        break;
    case Qt::Key_F1:
    case Qt::Key_F5:
    case Qt::Key_Up:
    case Qt::Key_F8:
    case Qt::Key_Down:
    case Qt::Key_F9:
    case Qt::Key_Right:
    case Qt::Key_F7:
    case Qt::Key_F6://left
    case Qt::Key_Left:
        psa_UIRefresh_Control->keyPressReflect(event->key());
        break;

    default:
        break;
    }
    priAction = m_user_variable->PrimaryAction;
    SA_Dialog_FreqSetup* mFreqSetup;
    SA_Dialog_AmptSetup* mAmptSetup;
    SA_Dialog_MarkerSetup* mMarkerSetup;
    SA_Dialog_MarkerSingle* mMarkerTabSetup;
    if(event->key() == Qt::Key_F4 || event->key() == Qt::Key_F3)
    {
        switch (priAction) {
        case SA_SWEEP:

            break;
        case SA_FREQUENCY:
            on_infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_CENTER);
            if(mSetupDialog)
            {
                mFreqSetup = (SA_Dialog_FreqSetup*)mSetupDialog;
                mFreqSetup->refreshEditDisplay(SA_INPUT_FREQ_CENTER);
            }
            break;
        case SA_AMPLITUDE:
            if(mSetupDialog)
            {
                mAmptSetup = (SA_Dialog_AmptSetup*)mSetupDialog;
                mAmptSetup->refreshEditDisplay(SA_INPUT_REF_LEVEL);
            }
            break;
        default: //Marker
            if(mSetupDialog && m_user_variable->PrimaryAction == SA_MARKER)
            {
                mMarkerSetup = (SA_Dialog_MarkerSetup*)mSetupDialog;
                mMarkerSetup->refreshMarkerEdit();
            }
            on_refreshMarkerInfo();
            break;
        }
    }
    if(event->key() == Qt::Key_F4 || event->key() == Qt::Key_F3)
    {
        #if 0
        if(1 == SA_sm_config_sweep->ListenState)
        #endif
        {
            if(SA_SINGLE == m_user_variable->gSweepType)
            {
                psa_UIRefresh_Control->refreshPixmap();
                repaint(CenterDrawRect);
            }
        }
    }

    return;
}

/**
 * @brief  Initialization widget.
 * @param  void
 * @return void
 * @author Tony
 * @since 2018-12-18
*/

void BitSA::initWidget(void)
{
    pcontrolInterface->setSuspendFunc(0);
    mDelayTimer = new QTimer();
    mloop = 0;
    modeChangeFlag = 0;
    //    pcontrolInterface->setCenterFreq(m_user_variable->adjustFreqByCHStandar());
    setCenterRect(255,65,943,648);
    loadFlag = 0;
    FullStatus = false;
    reflag = false;
    suspendFlag = false;
    loadstylesheet(0);
    mSetupDialog = NULL;
    mInteDialog = NULL;
    mBtnGroup = new QButtonGroup();
    mBtnGroup->setExclusive(true);
    mBtnGroup->addButton(pBitSA->topButton1,SA_FREQ_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton2,SA_AMPT_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton3,SA_DISPLAY_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton4,SA_BW_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton5,SA_TRIGGER_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton6,SA_TRACE_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton7,SA_MARKER_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton8,SA_LIMIT_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton9,SA_MEASURE_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton10,SA_MEASUREPARASET_DIALOG);
    mBtnGroup->addButton(pBitSA->topButton11,SA_ALL_SETUP_DIALOG);

    //    mBtnGroup->addButton(pBitSA->rightButton1,SA_RIGHTBTN2);
    mBtnGroup->addButton(pBitSA->rightButton2,SA_RIGHTBTN2);
    //    mBtnGroup->addButton(pBitSA->rightButton3,SA_RIGHTBTN3);
    //    mBtnGroup->addButton(pBitSA->rightButton4,SA_RIGHTBTN4);
    //    mBtnGroup->addButton(pBitSA->rightButton5,SA_RIGHTBTN5);
    //    mBtnGroup->addButton(pBitSA->rightButton6,SA_RIGHTBTN6);
    //   mBtnGroup->addButton(pBitSA->rightButton7,SA_QUICKSAVE);
    //    mBtnGroup->addButton(pBitSA->rightButton8,SA_SETUP);
    //mBtnGroup->addButton(pBitSA->rightButton9,SA_HOME);
    //mBtnGroup->addButton(pBitSA->rightButton10,SA_FULL);
    connect(mBtnGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(runBtnFunction(qint32)));

    mBtnMkrGroup = new QButtonGroup();
    mBtnMkrGroup->addButton(pBitSA->pb_marker_1,SA_M1);
    mBtnMkrGroup->addButton(pBitSA->pb_marker_2,SA_M2);
    mBtnMkrGroup->addButton(pBitSA->pb_marker_3,SA_M3);
    mBtnMkrGroup->addButton(pBitSA->pb_marker_4,SA_M4);
    mBtnMkrGroup->addButton(pBitSA->pb_marker_5,SA_M5);
    mBtnMkrGroup->addButton(pBitSA->pb_marker_6,SA_M6);

    QLabel *pMkrLabel[MARKER_TOTAL_CNT];
    for(qint32 i = 0;i < MARKER_TOTAL_CNT;i++)
    {
        pMkrLabel[i] = new QLabel(mBtnMkrGroup->button(i));
        pMkrLabel[i]->setGeometry(00,0,130,50);
        pMkrLabel[i]->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    }
    connect(mBtnMkrGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(runBtnMkrFunction(qint32)));
    on_refreshMarkerInfo();

    connect(pBitSA->widget_Freq,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(pBitSA->widget_Ampt,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(pBitSA->widget_BW,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(pBitSA->widget_Limit,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(pBitSA->widget_Trace,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(pBitSA->widget_Trigger,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(pBitSA->widget_mode,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(pBitSA->widget_Sweep,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));

    mInfoWidget = new QMap<SA_ClickedWidget*,qint32>;
    mInfoWidget->insert(pBitSA->widget_Freq,SA_FREQ_DIALOG);
    mInfoWidget->insert(pBitSA->widget_Ampt,SA_AMPT_DIALOG);
    mInfoWidget->insert(pBitSA->widget_BW,SA_BW_DIALOG);
    mInfoWidget->insert(pBitSA->widget_Limit,SA_LIMIT_DIALOG);
    mInfoWidget->insert(pBitSA->widget_Trace,SA_TRACE_DIALOG);
    mInfoWidget->insert(pBitSA->widget_Trigger,SA_TRIGGER_DIALOG);
    mInfoWidget->insert(pBitSA->widget_mode,SA_MEASURE_DIALOG);
    mInfoWidget->insert(pBitSA->widget_Sweep,SA_DISPLAY_DIALOG);

    mScreenshots = new SA_Dialog_QuickSave(pcontrolInterface,this);
    mAllSetDialog = new SA_Dialog_AllSetup(pcontrolInterface,m_user_variable,this);
    wFreqSetup = new SA_Dialog_FreqSetup(pcontrolInterface,m_user_variable,this);
    wAmptSetup = new SA_Dialog_AmptSetup(pcontrolInterface,m_user_variable,this);
    wSweepSetup = new SA_Dialog_DisplaySetup(pcontrolInterface,m_user_variable,this);
    wBwSetup = new SA_Dialog_BWSetup(pcontrolInterface,m_user_variable,this);
    wTriggerSetup = new SA_Dialog_TriggerSetup(pcontrolInterface,this);
    wTraceSetup = new SA_Dialog_TraceSetup(pcontrolInterface,this);
    wMarkerSetup = new SA_Dialog_MarkerSetup(pcontrolInterface,m_user_variable,this);
    wLimitSetup = new SA_Dialog_Limit(pcontrolInterface,this);
    wMeasureSetup = new SA_Dialog_MeasureSetup(pcontrolInterface,m_user_variable,this);
    wMarkerSingle = new SA_Dialog_MarkerSingle(pcontrolInterface,m_user_variable,this);
    wChnlpowerset = new sa_dialog_chnlpowerset(pcontrolInterface,m_user_variable,this);
    wOccpdset = new sa_dialog_occpdset(pcontrolInterface,m_user_variable,this);
    wAcpset = new sa_dialog_acpset(pcontrolInterface,m_user_variable,this);
    wSpecEM = new SA_Dialog_SpecEM(pcontrolInterface,this);
    wSpurEM = new SA_Dialog_SpurEM(pcontrolInterface,this);


    //mAllSetDialog->setGeometry(mapToGlobal(QPoint(500,1000)).x(),mapToGlobal(QPoint(500,1000)).y(),1010,490);
    //qDebug()<<this->x()<<this->y();
    //mAllSetDialog->setGeometry(0,0,1278,763);
    //mAllSetDialog->move(mapToGlobal(QPoint(500,100)).x(),mapToGlobal(QPoint(100,800)).y());
    wFreqSetup->setGeometry(1,66,252,646);
    wAmptSetup->setGeometry(1,66,252,646);
    wSweepSetup->setGeometry(1,66,252,646);
    wBwSetup->setGeometry(1,66,252,646);
    wTriggerSetup->setGeometry(1,66,252,646);
    wTraceSetup->setGeometry(1,66,252,646);
    wMarkerSetup->setGeometry(1,66,252,646);
    wLimitSetup->setGeometry(1,66,252,646);
    wMeasureSetup->setGeometry(1,66,252,646);
    wChnlpowerset->setGeometry(1,66,252,646);
    wOccpdset->setGeometry(1,66,252,646);
    wAcpset->setGeometry(1,66,252,646);
    wSpecEM->setGeometry(1,66,252,646);
    wSpurEM->setGeometry(1,66,252,646);

    connect(mAllSetDialog,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wFreqSetup,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wAmptSetup,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wSweepSetup,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wBwSetup,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wTriggerSetup,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wTraceSetup,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wMarkerSetup,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wLimitSetup,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wMeasureSetup,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wMarkerSingle,SIGNAL(mDialogHide()),this,SLOT(menuClose()));

    connect(wChnlpowerset,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wOccpdset,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wAcpset,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wSpecEM,SIGNAL(mDialogHide()),this,SLOT(menuClose()));
    connect(wSpurEM,SIGNAL(mDialogHide()),this,SLOT(menuClose()));

    mFileManager = new SAFileManager();
    connect(mFileManager,SIGNAL(loadFileSig(QString)),this,SLOT(LoadFilePara(QString)));
    //connect(mFileManager,SIGNAL(saveFileSig(QString,FILE_TYPE)),this,SLOT(saveFilePara(QString,FILE_TYPE)));
    connect(mFileManager,SIGNAL(saveFileSig(QString,qint32)),this,SLOT(saveFilePara(QString,qint32)));
    connect(mFileManager,SIGNAL(fastSaveFileSig(QString,int)),this,SLOT(quickSaveFilePara(QString,int)));
    connect(mFileManager,SIGNAL(fastSaveDialogClosed()),this,SLOT(on_fastSaveDialogClosed()));
    connect(mFileManager,SIGNAL(fileManagerWidgetClosed()),this,SLOT(on_fileManagerWidgetClosed()));

    return ;
}
void BitSA::initMenuWidget()
{
    wFreqSetup->initWidget();
    wAmptSetup->initWidget();
    wSweepSetup->initWidget();
    wBwSetup->initWidget();
    wTriggerSetup->initWidget();
    wTraceSetup->initWidget();
    wMarkerSetup->initWidget();
    wLimitSetup->initWidget();
    wMeasureSetup->initWidget();
    wMarkerSingle->initWidget();
}

void BitSA::setMenuProperty(const char *name, const QVariant &value)
{
    mAllSetDialog->setProperty(name,value);
    wFreqSetup->setProperty(name,value);
    wAmptSetup->setProperty(name,value);
    wSweepSetup->setProperty(name,value);
    wBwSetup->setProperty(name,value);
    wTriggerSetup->setProperty(name,value);
    wTraceSetup->setProperty(name,value);
    wMarkerSetup->setProperty(name,value);
    wLimitSetup->setProperty(name,value);
    wMeasureSetup->setProperty(name,value);
    wMarkerSingle->setProperty(name,value);
    wChnlpowerset->setProperty(name,value);
    wOccpdset->setProperty(name,value);
    wAcpset->setProperty(name,value);
    wSpecEM->setProperty(name,value);
    wSpurEM->setProperty(name,value);

    pControlACPTable->setProperty("status",value);
    pControlChannelPowerTable->setProperty("status",value);
    pControlpOccupiedXdBTable->setProperty("status",value);
    pControlMultiACPTable->setProperty("status",value);
    pControlSpectrumEMTable->setProperty("status",value);
    pControlSpuriousEMTable->setProperty("status",value);
    pControlMarkerTable->setProperty("status",value);

    pACPTable->setProperty("status",value);
    pChannelPowerTable->setProperty("status",value);
    pOccupiedXdBTable->setProperty("status",value);
    pMultiACPTable->setProperty("status",value);
    pSpectrumEMTable->setProperty("status",value);
    pSpuriousEMTable->setProperty("status",value);
    pMarkerTable->setProperty("status",value);
}

/**
 * @brief  load windows stylesheet,and have three modes
 *         default , night and outdoor mode.
 * @param  stylemode
 * @return void
 * @author Tony
 * @since 2018-12-18
*/
void BitSA::loadstylesheet(int stylemode)
{
    return;
    //1 load qss file,2
    QString filename[3]={":/sa/stylesheet/default.qss",":/sa/stylesheet/outdoor.qss",":/sa/stylesheet/night.qss"};
    QFile qss(filename[stylemode]);
    if(qss.open(QFile::ReadOnly))
    {
        this->setStyleSheet(qss.readAll());
        qss.close();
    }
    return;
}

/**
 * @brief  Hide last bullet windows and show current bullet windows.
 * @param  menuID    menu ID.
 * @return void
 * @author Tony
 * @since 2018-12-20
*/
void BitSA::menuShow(int menuID)
{
    return ;
}


void BitSA::runBtnFunction(qint32 menuID)
{
    switch (menuID)
    {
    case SA_FREQ_DIALOG:
    case  SA_AMPT_DIALOG:
    case  SA_DISPLAY_DIALOG:
    case  SA_BW_DIALOG:
    case  SA_TRIGGER_DIALOG:
    case  SA_TRACE_DIALOG:
    case  SA_MARKER_DIALOG:
    case  SA_LIMIT_DIALOG:
    case  SA_MEASURE_DIALOG:
    case  SA_MEASUREPARASET_DIALOG:
    case  SA_ALL_SETUP_DIALOG:
        showMenu(menuID);
        m_user_variable->gCurrentWorkState = menuID;
        break;
    default:
        return;
        break;
    }
    return ;
}

void BitSA::on_rightButton1_clicked()
{
    m_user_variable->bShiftKeyPressed = false;
    qint32 menuID = pcontrolInterface->getMarkerSelect();
    pcontrolInterface->setPeak();
    if(m_user_variable->currentMode == SA_SPAN_MODE)
        pBitSA->buttomMarker->show();
    on_refreshMarkerInfo();
    adjustRect();
    if(m_user_variable->PrimaryAction == SA_MARKER_TAB && mSetupDialog)
    {
        return;
    }
    pBitSA->buttomMarker->setWindowFlags( Qt::WindowStaysOnTopHint);
    mBtnGroup->button(SA_MARKER_DIALOG)->setChecked(true);
    runBtnMkrFunction(menuID);
    return ;
}

void BitSA::on_rightButton2_clicked()
{   
    qint32 mMode = pcontrolInterface->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode)
        return;
    if(m_user_variable->currentMode == SA_CHNLPOWER_MEASURE_MODE || m_user_variable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE ||
            m_user_variable->currentMode == SA_ACP_MEASURE_MODE || m_user_variable->currentMode == SA_MULTI_ACP_MODE)
        return;
    m_user_variable->bShiftKeyPressed = false;
    pcontrolInterface->setAutoLimit();
    runBtnFunction(SA_LIMIT_DIALOG);
    SA_Dialog_Limit *mLimit = (SA_Dialog_Limit*)mSetupDialog;
    mLimit->refreshTable();

    mBtnGroup->button(SA_LIMIT_DIALOG)->setChecked(true);
    return ;
}

void BitSA::on_rightButton3_clicked()
{
    m_user_variable->bShiftKeyPressed = false;
    pcontrolInterface->setAutoScale(true);
    menuClose();
    runBtnFunction(SA_AMPT_DIALOG);

    mBtnGroup->button(SA_AMPT_DIALOG)->setChecked(true);
    return ;
}

void BitSA::on_rightButton4_clicked()//lock
{
    menuClose();
    qint32 status = pBitSA->rightButton4->isChecked();
    SetScreenLock(status);

    QString strCmd;
    QString iVal = QString::number(status);
    strCmd = QString(":SCREen:LOCK ");
    strCmd += iVal;
    emit pcontrolInterface->sendSCPIcmd(strCmd);
}
void   BitSA::SetScreenLock(qint32 islock)
{
    pBitSA->rightButton4->setChecked(islock);
    m_user_variable->gLockStatus = islock;
    if(islock)
    {
        emit KeyEventSig(Qt::Key_Escape + 1);
    }
    else
    {
        emit KeyEventSig(Qt::Key_Escape + 2);
    }

    m_user_variable->bShiftKeyPressed = false;
}
qint32 BitSA::GetScreenLock()
{
    return m_user_variable->gLockStatus;
}

void BitSA::on_rightButton5_clicked()
{
    menuClose();
    QDialog *transfile =new sa_dialog_transfile(pcontrolInterface,this);
    transfile->exec();
#if 0
    pcontrolInterface->setSuspendFunc(1);
    if(loadFlag) loadFlag = 0;
    mFileManager->showFileManagerWidget();
    mFileManager->m_fileManagerWidget->move(mapToGlobal(mapFromParent(QPoint(1,1))).x(),mapToGlobal(mapFromParent(QPoint(1,1))).y());
#endif
    //    if(loadFlag)
    //    {
    //        pcontrolInterface->setSuspendFunc(true);
    //    }else
    //    {
    //        pcontrolInterface->setSuspendFunc(0);
    //    }
    m_user_variable->bShiftKeyPressed = false;
}
//Save
void BitSA::on_rightButton6_clicked()
{
    menuClose();
    pcontrolInterface->setSuspendFunc(1);
    mFileManager->showSaveDialog();
    mFileManager->m_saveDialog->move(mapToGlobal(QPoint(364,263)).x(),mapToGlobal(QPoint(364,263)).y());
    //pcontrolInterface->setSuspendFunc(0);
    m_user_variable->bShiftKeyPressed = false;
}
//Screen Capture
void BitSA::on_rightButton7_clicked()
{
    m_user_variable->bShiftKeyPressed = false;
    pcontrolInterface->setSuspendFunc(1);
    mScreenshots->init();
    mScreenshots->setGeometry(mapToGlobal(QPoint(135,102)).x(),mapToGlobal(QPoint(135,102)).y(),1010,490);
    mScreenshots->exec();
    repaint();
    pcontrolInterface->setSuspendFunc(0);
}
//System
void BitSA::on_rightButton8_clicked()
{
    m_user_variable->bShiftKeyPressed = false;
    MenuClose();
    emit SysSetSig();
    return ;
}
//Home
void BitSA::on_rightButton9_clicked()
{
    //
    m_user_variable->bShiftKeyPressed = false;
    MenuClose();
    return ;
}
//Zoom
void BitSA::on_rightButton10_clicked()
{
    menuClose();
    setZoomIn();

    //Johnson 190315
    setTablePosition();

    QString strCmd;
    QString iVal = QString::number(FullStatus);
    strCmd = QString(":SCREen:FULL ");
    strCmd += iVal;
    emit pcontrolInterface->sendSCPIcmd(strCmd);
    return ;
}

void BitSA::SetScreenFull(qint32 isFull)
{
    if(!isFull)
    {
        FullStatus = false;
    }
    else
    {
        FullStatus = true;
    }
    adjustRect();
    m_user_variable->FullStatus = FullStatus;
    return;
}
qint32 BitSA::GetScreenFull()
{
    return FullStatus;
}
void BitSA::runBtnMkrFunction(qint32 menuID)
{
    m_user_variable->PrimaryAction = SA_MARKER_TAB;
    m_user_variable->bShiftKeyPressed = false;
    switch (menuID)
    {
    case  SA_M1:
    case  SA_M2:
    case  SA_M3:
    case  SA_M4:
    case  SA_M5:
    case  SA_M6:
        showMkrMenu(menuID);
        break;
    default:
        return;
        break;
    }
    return ;
}
/**
 * @brief  Show menu windows.
 * @param  index    menu ID.
 * @return void
 * @author Tony
 * @since 2019-01-22
*/
void BitSA::showMenu(qint32 index)
{
    if(m_user_variable->gRunMode == SA_REMOTE)
    {
        if(mBtnGroup->button(index))
        {
            mBtnGroup->button(index)->setChecked(true);
        }
    }

    m_user_variable->bShiftKeyPressed = false;
    if(lastMenuID == index && mSetupDialog && !( index == SA_MARKER_DIALOG && pBitSA->buttomMarker->isHidden()))
    {
        return;
    }

    QString strCmd;
    QString iVal = QString::number(index);
    strCmd = QString(":MENU ");
    strCmd += iVal;
    emit pcontrolInterface->sendSCPIcmd(strCmd);


    struct timeval tpstart,tpend;
    float timeuse;


    switch(index)
    {
    case SA_FREQ_DIALOG:
        m_user_variable->PrimaryAction = SA_FREQUENCY;
        menuClose();
        mSetupDialog =  wFreqSetup;
        mInteDialog = wFreqSetup;
        wFreqSetup->initDisplay();
        //mSetupDialog = new SA_Dialog_FreqSetup(pcontrolInterface,m_user_variable,this);
        //mSetupDialog->setGeometry(1,66,252,646);
        break;
    case  SA_AMPT_DIALOG:
        m_user_variable->PrimaryAction = SA_AMPLITUDE;
        menuClose();
        mSetupDialog =  wAmptSetup;
        mInteDialog = wAmptSetup;
        wAmptSetup->initDisplay();
        break;
    case  SA_DISPLAY_DIALOG:
        m_user_variable->PrimaryAction = SA_SWEEP;
        menuClose();
        mSetupDialog =  wSweepSetup;
        mInteDialog = wSweepSetup;
        wSweepSetup->initDisplay();
        break;
    case  SA_BW_DIALOG:
        m_user_variable->PrimaryAction = SA_BW;
        menuClose();
        mSetupDialog =  wBwSetup;
        mInteDialog = wBwSetup;
        wBwSetup->initDisplay();
        break;
    case  SA_TRIGGER_DIALOG:
        m_user_variable->PrimaryAction = SA_TRIGGER;
        menuClose();
        mSetupDialog =  wTriggerSetup;
        mInteDialog = wTriggerSetup;
        wTriggerSetup->initDisplay();
        break;
    case  SA_TRACE_DIALOG:
        m_user_variable->PrimaryAction = SA_TRACE;
        menuClose();
        mSetupDialog =  wTraceSetup;
        mInteDialog = wTraceSetup;
        wTraceSetup->initDisplay();
        break;
    case  SA_MARKER_DIALOG:
        m_user_variable->PrimaryAction = SA_MARKER;
        menuClose();
        mSetupDialog =  wMarkerSetup;
        mInteDialog = wMarkerSetup;
        wMarkerSetup->initDisplay();
        if(m_user_variable->gRunMode != SA_REMOTE)
        {
            mSetupDialog->show();
        }
        pBitSA->buttomMarker->show();
        on_refreshMarkerInfo();
        pBitSA->buttomMarker->setWindowFlags( Qt::WindowStaysOnTopHint);

        //Johnson 0315
        pcontrolInterface->setMarkerDisplay(MKR_TABLE);
        refreshMkrTable();
        //slotOperateTable();
        break;
    case  SA_LIMIT_DIALOG:
        m_user_variable->PrimaryAction = SA_LIMIT;
        menuClose();
        mSetupDialog =  wLimitSetup;
        mInteDialog = wLimitSetup;
        wLimitSetup->initDisplay();
        break;
    case  SA_MEASURE_DIALOG:
        m_user_variable->PrimaryAction = SA_MEASUREMENT;
        menuClose();
        mSetupDialog =  wMeasureSetup;
        mInteDialog = wMeasureSetup;
        wMeasureSetup->initDisplay();
        break;
    case SA_MEASUREPARASET_DIALOG:
        m_user_variable->PrimaryAction = SA_MEASUREMENT;
        menuClose();
        if(m_user_variable->currentMode == SA_CHNLPOWER_MEASURE_MODE)
        {
            mSetupDialog =  wChnlpowerset;
            mInteDialog = wChnlpowerset;
            wChnlpowerset->initDisplay();
        }
        else if(m_user_variable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE)
        {
            mSetupDialog =  wOccpdset;
            mInteDialog = wOccpdset;
            wOccpdset->initDisplay();
        }
        else if(m_user_variable->currentMode == SA_ACP_MEASURE_MODE || m_user_variable->currentMode == SA_MULTI_ACP_MODE)
        {
            mSetupDialog =  wAcpset;
            mInteDialog = wAcpset;
            wAcpset->initDisplay();
        }else if(m_user_variable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
        {
            mSetupDialog =  wSpecEM;
            mInteDialog = wSpecEM;
            wSpecEM->initDisplay();
        }else if(m_user_variable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {
            suspendFlag = true;
            mSetupDialog =  wSpurEM;
            mInteDialog = wSpurEM;
            wSpurEM->initDisplay();
        }
        break;
    case SA_ALL_SETUP_DIALOG:
        m_user_variable->PrimaryAction = SA_MARKER_ALLSET;
        menuClose();
        mSetupDialog = mAllSetDialog;
        if(m_user_variable->gRunMode != SA_REMOTE)
        {
            mAllSetDialog->setGeometry(mapToGlobal(mapFromParent(QPoint(1,0))).x(),mapToGlobal(mapFromParent(QPoint(1,0))).y(),1278,763);
            mAllSetDialog->mShow();
        }
        /*
        if(m_user_variable->bSmallCanvas)
        {
            mSetupDialog->setGeometry(1,66,1196,645);
        }
        else
        {
            mSetupDialog->setGeometry(0,0,1196,this->height());
        }
        emit AllSetSig();
        */
        break;
    case SA_QUICKSAVE:
        return;
        m_user_variable->PrimaryAction = SA_SAVE;
        menuClose();

        pcontrolInterface->setSuspendFunc(1);
        mSetupDialog = new SA_Dialog_QuickSave(pcontrolInterface,this);
        mSetupDialog->setGeometry(mapToGlobal(QPoint(135,102)).x(),mapToGlobal(QPoint(135,102)).y(),1010,490);
        break;
    default:
        return;
        break;
    }
    if(!mSetupDialog)
        return;
    if(FullStatus)
    {
        if(index != SA_ALL_SETUP_DIALOG)
        {
            mSetupDialog->move(1,1);
        }
    }else
    {
        if(index != SA_ALL_SETUP_DIALOG)
        {
            mSetupDialog->move(1,66);
        }
    }

    lastMenuID = index;
    m_user_variable->RefreshTime = TIME_MAX;
    adjustRect();
    if(m_user_variable->gRunMode != SA_REMOTE)
    {
        if(m_user_variable->PrimaryAction == SA_SAVE)
        {
            qobject_cast<QDialog*>(mSetupDialog)->exec();
            repaint();
        }else
        {
   gettimeofday(&tpstart,NULL);
            mSetupDialog->setVisible(true);
            if(pcontrolInterface->getSweepType() == SA_SINGLE)
                repaint();
        }
    }
    gettimeofday(&tpend,NULL);
    timeuse=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000.0;
    qDebug()<<timeuse<<"ms";
}
qint32 BitSA::GetCurMenu()
{
    return lastMenuID;
}

/**
 * @brief  Show marker table windows.
 * @param  index    marker index.
 * @return void
 * @author Tony
 * @since 2019-01-25
*/
void BitSA::showMkrMenu(qint32 index)
{
    menuClose();
    if(lastMenuID == SA_MARKER_TAB && mSetupDialog)
    {
        return;
    }
    lastMenuID = SA_MARKER_TAB;
    pcontrolInterface->setMarkerSelect(index);
    showMarkerTableIcon(SA_ON);
    mSetupDialog = wMarkerSingle;
    wMarkerSingle->initDisplay();
    if(FullStatus)
    {
        mSetupDialog->setGeometry(1,1,252,646);
    }else
    {
        mSetupDialog->setGeometry(1,66,252,646);
    }
    //connect(mSetupDialog,SIGNAL(destroyed()),this,SLOT(on_menuDestroyed()));
    m_user_variable->RefreshTime = TIME_MAX;
    mBtnGroup->button(SA_MARKER_DIALOG)->setChecked(true);
    mSetupDialog->show();
    this->repaint();
}


/**
 * @brief  Zoom in.
 * @param  void
 * @return void
 * @author Tony
 * @since 2019-1-09
*/
void BitSA::setZoomIn()
{
    if(FullStatus)
    {
        FullStatus = false;
    }
    else
    {
        FullStatus = true;
    }
    adjustRect();
    m_user_variable->FullStatus = FullStatus;

    //setPixmap(!m_user_variable->bSmallCanvas);
    //emit ZoomIn(FullStatus);
}
/**
 * @brief  menu dialog close.
 * @param  void
 * @return void
 * @author Tony
 * @since 2019-1-09
*/
void BitSA::menuClose()
{
    if(lastMenuID == SA_MARKER_TAB && mSetupDialog)
            showMarkerTableIcon(SA_OFF);
    if(m_user_variable->PrimaryAction == SA_MARKER)
    {


    }else if(m_user_variable->PrimaryAction == SA_MARKER_TAB)
    {

    }
    else
    {
        if((!pBitSA->buttomMarker->isHidden()) && SA_guiDrawSet.markerOnCount == 0)
        {
            pBitSA->buttomMarker->hide();
            adjustRect();
        }
    }

    if(mSetupDialog)
    {
        if(mAllSetDialog == mSetupDialog)
        {
            if(!mAllSetDialog->isHidden())
                mAllSetDialog->mHide();
            mSetupDialog = NULL;
        }else
        {
            if(mInteDialog)
            {
                //Blocking signal to prevent repeated triggering "menuClose()"
                mSetupDialog->blockSignals(true);
                mInteDialog->hideWidget();
                mSetupDialog->blockSignals(false);
                mInteDialog = NULL;
            }else
            {
                mSetupDialog->hide();
            }
            mSetupDialog = NULL;
        }
        this->setFocus();
        m_user_variable->RefreshTime = TIME_DEFAULT;
    }
    return;
}

/**
 * @brief  Slot function that received information.
 * @param  void
 * @return void
 * @author Tony
 * @since 2019-1-23
*/
void BitSA::on_menuDestroyed()
{
    if(mSetupDialog)
    {
        if(mSetupDialog == mAllSetDialog)
        {
            if(!mAllSetDialog->isHidden())
                mAllSetDialog->mHide();
            disconnect(mAllSetDialog,SIGNAL(mDialogHide()),this,SLOT(on_menuDestroyed()));

        }else{
//            showMarkerTableIcon(SA_OFF);
            if(pcontrolInterface->getSuspendFunc() && m_user_variable->PrimaryAction == SA_SAVE)
            {
                pcontrolInterface->setSuspendFunc(0);
                //                pcontrolInterface->TraceSuspendFunc(m_user_variable->traceSusFlag);
            }
            if(m_user_variable->PrimaryAction == SA_MARKER_TAB)
            {
                showMarkerTableIcon(SA_OFF);
            }
        }
        disconnect(mSetupDialog,SIGNAL(destroyed()),this,SLOT(on_menuDestroyed()));
        m_user_variable->RefreshTime = TIME_DEFAULT;
        this->setFocus();
        mSetupDialog = NULL;
    }
    return;
}
void BitSA::showMarkerTableIcon(qint32 viewStatus)
{
    QString qss = "#BitSA[status  =  \"indoor\"] QPushButton:checked{background-color:rgb(240,179,29);border:1px solid rgba(240,179,29,1);}\
                   #BitSA[status  =  \"outdoor\"] QPushButton:checked{background-color:rgb(244,201,96);border:1px solid rgba(240,179,29,1);}\
                   #BitSA[status  =  \"night\"] QPushButton:checked{background-color:rgb(218,144,22);border:1px solid rgba(218,144,22,1);}";
    QString qss1 = "#BitSA[status  =  \"indoor\"] QPushButton:checked{border:1px solid rgba(240,179,29,1);}\
                   #BitSA[status  =  \"outdoor\"] QPushButton:checked{border:1px solid rgba(240,179,29,1);}\
                   #BitSA[status  =  \"night\"] QPushButton:checked{border:1px solid rgba(218,144,22,1);}";

    qint32 mCurMarker = pcontrolInterface->getMarkerSelect();
    if(viewStatus)
    {
        mBtnMkrGroup->button(mCurMarker)->setStyleSheet(qss);
    }
    else
    {
        for(qint32 i=0;i<MARKER_TOTAL_CNT;i++)
        {
            mBtnMkrGroup->button(i)->setStyleSheet(qss1);
        }
    }
}
/**

 * @brief  Slot function that refresh marker information.
 * @param  void
 * @return void
 * @author Tony
 * @since 2019-1-23
*/
void BitSA::on_refreshMarkerInfo()
{
    SA_Dialog_MarkerSingle* mMarkerTabSetup;
    qint32 mCurMarker = pcontrolInterface->getMarkerSelect();
    if(mSetupDialog && m_user_variable->PrimaryAction == SA_MARKER_TAB)
    {
        mMarkerTabSetup = (SA_Dialog_MarkerSingle*)mSetupDialog;
        mMarkerTabSetup->refreshInfo();
        //        showMarkerTableIcon(SA_OFF);
        //        showMarkerTableIcon(SA_ON);
    }
    if(pBitSA->buttomMarker->isHidden())
        return;
    //    mBtnMkrGroup->button(mCurMarker)->setChecked(true);
    QString strMkr,strFreq,strAmpt;
    qreal value,tmpvalue;
    qint32 minusFlag,unit;
    qreal time,tmpTime;
    if(pcontrolInterface->getTraceViewStatus()){
        for(qint32 i=0;i<MARKER_TOTAL_CNT;i++)
        {
            if(!pcontrolInterface->getMarkerType(i))
            {
                strMkr = QString("<b>M%1</b>").arg(QString::number(i+1));
            }
            else
            {
                strMkr = QString("<b>D%1</b>").arg(QString::number(i+1));
            }
            if(pcontrolInterface->getMarkerViewStatus(i) == SA_ON)
            {
                minusFlag = 0;
                if(pcontrolInterface->getMarkerType(i) == REF)
                {
                    if(!m_user_variable->gSpanMode)
                    {
                        value = pcontrolInterface ->getMarkerRefFreq(i);
                        //value =(qreal)m_user_variable->gMarkerRefPos[i] * m_user_variable->gStepFreq+ m_user_variable->gStartFreq+ m_user_variable->gfreqOffset;
                        if(value < 0)
                        {
                            value *= -1;
                            minusFlag  = 1;
                        }
                        strFreq = m_user_variable->freqValueToQstring(value);
                        if(minusFlag) strFreq = "-" + strFreq;
                        value = (qreal)m_user_variable->gTraceMeasureVal[m_user_variable ->gTraceSelect][m_user_variable->gMarkerRefPos[i]] + m_user_variable ->gRefOffset;
                        strAmpt = m_user_variable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),value);
                    }
                    else
                    {
                        time =pcontrolInterface->getMarkerRefTime(i);
                        strFreq = m_user_variable->TimeTransformToQstring(time);

                        value = (qreal)m_user_variable ->gTraceMeasureVal[m_user_variable ->gTraceSelect][m_user_variable->gMarkerRefPos[i]] + m_user_variable ->gRefOffset;
                        strAmpt = m_user_variable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),value);
                    }
                }
                else
                {
                    if(!m_user_variable->gSpanMode)
                    {
                        minusFlag = 0;
                        value = m_user_variable->gMarkerDeltaFreq[i];
                        tmpvalue = m_user_variable->gMarkerRefFreq[i];
                        value = value - tmpvalue;
                        if(value<0)
                        {
                            value *= -1;
                            minusFlag = 1;
                        }
                        else
                        {
                            minusFlag = 0;
                        }
                        strFreq = m_user_variable->freqValueToQstring(value);
                        if(minusFlag)
                        {
                            strFreq = "-" + strFreq;
                        }
                    }else
                    {
                        time =pcontrolInterface->getMarkerRefTime(i);
                        tmpTime = pcontrolInterface->getMarkerDeltaTime(i);
                        time = tmpTime - time;
                        if(time<0)
                        {
                            time *= -1;
                            minusFlag = 1;
                        }
                        else
                        {
                            minusFlag = 0;
                        }
                        strFreq = m_user_variable->TimeTransformToQstring(time);

                        if(minusFlag) strFreq = "-" + strFreq;
                    }
                    //value = (qreal)m_user_variable ->gTraceMeasureVal[m_user_variable ->gTraceSelect][m_user_variable->gMarkerDeltaPos[i]] + m_user_variable ->gRefOffset;
                    //tmpvalue = m_user_variable->gMarkerTmpRefAmpt[i];
                    unit = pcontrolInterface->getAmpUnit();
                    //value = value - tmpvalue;
                    value = m_user_variable->gMarkerDeltaAmpt[i];
                    if(unit == SA_VOLT)
                    {
                        strAmpt = m_user_variable->amptTransformToQstring(SA_DELTA_VOLT,value);
                    }
                    else if(unit ==SA_WATTS)
                    {
                        strAmpt = m_user_variable->amptTransformToQstring(SA_DELTA_WATTS,value);
                    }
                    else
                    {
                        strAmpt = m_user_variable->amptTransformToQstring(SA_NONE,value);
                    }
                    if(!m_user_variable->gSpanMode)
                    {
                        if(m_user_variable->gMarkerDeltaFreq[i]>m_user_variable->gStopFreq ||
                           m_user_variable->gMarkerDeltaFreq[i]<m_user_variable->gStartFreq)
                        {
                            strAmpt="-- --";
                        }
                    }
                    else
                    {
                        if(m_user_variable->gMarkerDeltaTime[i]>m_user_variable->gSweepTime ||
                           m_user_variable->gMarkerDeltaTime[i]<0)
                        {
                            strAmpt="-- --";
                        }
                    }
                }
            }
            else
            {
                strFreq="-- --";
                strAmpt="-- --";
            }
            mBtnMkrGroup->button(i)->findChild<QLabel*>()->setText(QString("%1<BR>%2<BR>\%3").arg(strMkr,strFreq,strAmpt));
        }
    }else
    {
        strFreq="-- --";
        strAmpt="-- --";
        for(int i=0;i<MARKER_TOTAL_CNT;i++)
        {
            if(!pcontrolInterface->getMarkerType(i))
            {
                strMkr = QString("M%1").arg(QString::number(i+1));
            }
            else
            {
                strMkr = QString("D%1").arg(QString::number(i+1));
            }
            mBtnMkrGroup->button(i)->findChild<QLabel*>()->setText(QString("%1<BR>%2<BR>\%3").arg(strMkr,strFreq,strAmpt));
        }
    }
    return;
}

void   BitSA::SetLeftInfobarDisplay(qint32 isShow)
{
    pBitSA->pb_left_hide->setChecked(!isShow);
    on_pb_left_hide_clicked();
    return;
}

qint32 BitSA::GetLeftInfobarDisplay()
{
    qint32 isShow = !m_user_variable->pbLeftHideChecked;
    return isShow;
}


void BitSA::on_pb_left_hide_clicked()
{
    adjustRect();
    //Johnson 0315
    setTablePosition();
#if 0
    //Johnson 0222
    bottomInfoClose();
    bottomInfoMarkerClose();
#endif
    m_user_variable->pbLeftHideChecked = pBitSA->pb_left_hide->isChecked();

    QString strCmd;
    QString iVal = QString::number(!m_user_variable->pbLeftHideChecked);
    strCmd = QString(":MENU:LINFobar:DISPlay ");
    strCmd += iVal;
    emit pcontrolInterface->sendSCPIcmd(strCmd);
}

void BitSA::on_pb_marker_AllOff_clicked()
{
    SetAllMkrOff();
    return;
}

void   BitSA::SetAllMkrOff()
{
    for(int i = 0 ;i<MARKER_TOTAL_CNT;i++)
    {
        pcontrolInterface->setMarkerViewStatus(SA_OFF,i);
        pcontrolInterface->setMarkerType(REF,i);
    }
    //Johnson 0315
    pcontrolInterface->setMarkerDisplay(MKR_ONLY);
    return;
    on_refreshMarkerInfo();
    winStatus[SA_BUTTOMWIDGET] = 0;

    if(pBitSA->topButton7->isChecked() || FullStatus)
    {

    }
    else
    {
        pBitSA->buttomMarker->hide();
        adjustRect();
    }
    if(mSetupDialog)
    {
        menuClose();
    }
    //Johnson0315
    //slotOperateTable();
    refreshMkrTable();

    QString strCmd;
    strCmd = QString(":MARKer:ALLClear");
    emit pcontrolInterface->sendSCPIcmd(strCmd);
    return;
}

void BitSA::on_infoRefresh(qint32 mType, qint32 mIndex)
{
    qint32 traceType = pcontrolInterface->getTraceType();

    if(pcontrolInterface->getSweepType() == SA_SINGLE)
    {
        if((mType == SA_INFO_FREQ && mIndex == SA_INFO_FREQ_OFFSET) \
                || mType == SA_INFO_MARKER \
                || (mType == SA_INFO_AMPT &&(mIndex == SA_INFO_AMPT_SCALEDIV || mIndex == SA_INFO_AMPT_OFFSET || mIndex == SA_INFO_AMPT_UNIT))\
                || mType == SA_INFO_LIMIT \
                || mType == SA_INFO_SYSTEM &&(mIndex != SA_INFO_SYSTEM_FREQ_REF)\
                || (mType == SA_INFO_TRACE && (mIndex == SA_INFO_TRACE_INDEX || mIndex == SA_INFO_TRACE_VIEW)))
        {
            singparamflag = 2;
        }
        else if(!((mType == SA_INFO_TRACE && mIndex == SA_INFO_TRACE_CURAVE)||\
                  (mType == SA_INFO_SWEEP && mIndex == SA_INFO_SWEEP_MODE)))
        {
            singparamflag = 1;
        }
        //current
        if(!((mType == SA_INFO_TRACE && mIndex ==SA_INFO_TRACE_CURAVE)||\
             (mType == SA_INFO_SWEEP && mIndex == SA_INFO_SWEEP_MODE)))
        {
            graphRefreshFunc();
        }
    }
    else
    {
        if(!((mType == SA_INFO_FREQ && mIndex == SA_INFO_FREQ_OFFSET) || \
             mType == SA_INFO_MARKER \
             || (mType == SA_INFO_AMPT &&(mIndex == SA_INFO_AMPT_SCALEDIV || mIndex == SA_INFO_AMPT_OFFSET || mIndex == SA_INFO_AMPT_UNIT))\
             ||  mType == SA_INFO_LIMIT \
             || (mType == SA_INFO_TRACE && mIndex == SA_INFO_TRACE_INDEX)))
        {
            singparamflag = 3;
        }
    }
    switch (mType)
    {
    case SA_INFO_FREQ:
        refreshFreq(mIndex);
        refreshSweep(SA_INFO_SWEEP_TIME);
        break;
    case SA_INFO_AMPT:
        refreshAmpt(mIndex);
        break;
    case SA_INFO_SWEEP:
        refreshSweep(mIndex);
        break;
    case SA_INFO_BW:
        refreshBw(mIndex);
        refreshSweep(SA_INFO_SWEEP_TIME);
        break;
    case SA_INFO_TRIGGER:
        refreshTrigger(mIndex);
        break;
    case SA_INFO_TRACE:
        refreshTrace(mIndex);
        break;
    case SA_INFO_MARKER:
        refreshMarker(mIndex);
        break;
    case SA_INFO_MEASURE:
        refreshMeasure(mIndex);
        break;
    case SA_INFO_SYSTEM:
        refreshSystem(mIndex);
        break;
    case SA_INFO_LIMIT:
        refreshLimit(mIndex);
        break;
    default:
        break;
    }
}

void BitSA::refreshSystem(qint32 mIndex)
{

    qint32 value;
    QString strInfo;
    QString qssStatus = qssMode[pcontrolInterface->GetDisplayMode()];
    switch (mIndex)
    {
    case SA_INFO_SYSTEM_MODE:
        value = pcontrolInterface->GetLocalRemoteMode();
        if(value == SA_REMOTE)
        {
            menuClose();
            setAttribute(Qt::WA_TransparentForMouseEvents, true);
        }else
        {
            setAttribute(Qt::WA_TransparentForMouseEvents, false);
        }
        break;
    case SA_INFO_SYSTEM_FREQ_REF:
        value = pcontrolInterface->GetSysRefuiStates();
        switch (value) {
        case SA_FREQREF_INTERNAL:
            strInfo = "Internal";
            break;
        case SA_FREQREF_EXTERNAL10:
            strInfo = "External 10MHz";
            break;
        case SA_FREQREF_EXTERNAL13:
            strInfo = "External 13MHz";
            break;
        case SA_FREQREF_EXTERNAL15:
            strInfo = "External 15MHz";
            break;
        case SA_FREQREF_GPS:
            strInfo = "GPS";
            break;
        }
        pBitSA->lblFreqRef->setText(strInfo);
        break;
    case SA_INFO_SYSTEM_SHIFT:
        menuClose();
        break;
    case SA_INFO_SYSTEM_LOCKSTATUS:
        value = pcontrolInterface->GetLcdState();
        if(value)
        {
            if(!pBitSA->rightButton4->isChecked())
            {
                pBitSA->rightButton4->setChecked(true);
            }
        }else
        {
            if(pBitSA->rightButton4->isChecked())
            {
                pBitSA->rightButton4->setChecked(false);
            }
        }
        break;
    case SA_INFO_SYSTEM_DISPLAYMODE:
        if(mSetupDialog)
        {
            mSetupDialog->setProperty("status",qssStatus);
            menuClose();
        }

        mAllSetDialog->setProperty("status",qssStatus);
        mScreenshots->setDisplayMode(qssStatus);
        setMenuProperty("status",qssStatus);
        this->setProperty("status",qssMode[pcontrolInterface->GetDisplayMode()]);
        this->setStyle(QApplication::style());
        break;
    }
}

void BitSA::refreshFreq(qint32 mIndex)
{
    qreal value,valueoffset;
    QString strInfo;
    qint32 minus = 0,index;
    switch (mIndex) {
    case SA_INFO_FREQ_START:
    case SA_INFO_FREQ_STOP:
    case SA_INFO_FREQ_CENTER:
    case SA_INFO_FREQ_SPAN:
    case SA_INFO_FREQ_OFFSET:
    case SA_INFO_CH_STANDARD:
        refreshBw(SA_INFO_BW_RBW_AUTO);
        refreshBw(SA_INFO_BW_RBW_VALUE);
        refreshBw(SA_INFO_BW_VBW_AUTO);
        refreshBw(SA_INFO_BW_VBW_VALUE);
        refreshBw(SA_INFO_BW_IF_OUTPUT);
        //Center freq
        value = pcontrolInterface->getCenterFreq();
        //valueoffset = pcontrolInterface->getFreqOffset();
        //value += valueoffset;
        if(value < 0)
        {
            minus = 1;
            value *= -1;
        }
        strInfo = m_user_variable->freqValueToQstring(value,3);
        if(minus)
        {
            strInfo = QString("-%1").arg(strInfo);
        }

        pBitSA->lblCenterFreqValue->setText(strInfo);
        //break;
        //Channel standard
        index = pcontrolInterface->getCHStandard();
        if(index<0)
            strInfo = "-- --";
        else
        {
            strInfo = QString(mChStand[index].name);
            //            strInfo = strInfo + "-"+m_user_variable->gCHName->at(m_user_variable->gCHIndex);
        }
        pBitSA->lblCHStandardValue->setText(strInfo);
        //Channel number
        if(index < 0)
            strInfo = "-- --";
        else
        {
            strInfo = QString::number(pcontrolInterface->getChannelNumber());
        }
        pBitSA->lblChannelValue->setText(strInfo);
        break;
    default:
        break;
    }
    return;
}
void BitSA::refreshAmpt(qint32 mIndex)
{
    qint32 status;
    qreal value;
    QString strInfo;
    switch (mIndex) {
    case SA_INFO_AMPT_PREAMP:
        status = pcontrolInterface->getPreampStatus();
        switch (status) {
        case SA_OFF:
            strInfo = "Off";
            break;
        case SA_ON:
            strInfo = "On";
            break;
        }
        pBitSA->lblPreampValue->setText(strInfo);

        refreshAmpt(SA_INFO_AMPT_ATTEN);
        break;
    case SA_INFO_AMPT_ATTENTYPE:
        status = pcontrolInterface->getAttenStatus();
        switch (status) {
        case SA_MANUAL:
            strInfo = "Manual";
            break;
        case SA_AUTO:
            strInfo = "Auto";
            break;
        case SA_COUPLE:
            strInfo = "Couple";
            break;
        }
        pBitSA->lblAttenType->setText(strInfo);
        refreshAmpt(SA_INFO_AMPT_ATTEN);
        break;
    case SA_INFO_AMPT_ATTEN:
        value = pcontrolInterface->getAttenValue();
        strInfo = m_user_variable->amptTransformToQstring(SA_NONE,value);
        pBitSA->lblAttenValue->setText(strInfo);
        break;
    case SA_INFO_AMPT_OFFSET:
        value = pcontrolInterface->getRefOffset();
        strInfo = m_user_variable->amptTransformToQstring(SA_NONE,value);
        pBitSA->lblOffsetValue->setText(strInfo);
        break;
    case SA_INFO_AMPT_REF:
        value = pcontrolInterface->getRefOffset();
        strInfo = m_user_variable->amptTransformToQstring(SA_NONE,value);
        pBitSA->lblOffsetValue->setText(strInfo);
        refreshAmpt(SA_INFO_AMPT_ATTEN);
        break;
    case SA_INFO_AMPT_UNIT:
        on_refreshMarkerInfo();
        break;
    case SA_INFO_AMPT_AUTOLIMIT:
        refreshAmpt(SA_INFO_AMPT_PREAMP);
        refreshAmpt(SA_INFO_AMPT_ATTENTYPE);
        refreshAmpt(SA_INFO_AMPT_ATTEN);
        refreshAmpt(SA_INFO_AMPT_OFFSET);
        refreshAmpt(SA_INFO_AMPT_REF);
        break;
    }
    return;
}
void BitSA::refreshSweep(qint32 mIndex)
{
    qint32 status;
    qreal value;
    QString strInfo;
    switch (mIndex) {
    case SA_INFO_SWEEP_MODE:
        status = pcontrolInterface->getSweepType();
        switch (status) {
        case SA_CONT:
            strInfo = "Continuous";
            break;
        case SA_SINGLE:
            strInfo = "Single";
            break;
        }
        pBitSA->lblSweepMode->setText(strInfo);
        break;
    case SA_INFO_SWEEP_TIME:
        value = pcontrolInterface->getSweepTime();
        strInfo =m_user_variable->TimeTransformToQstring(value);
        pBitSA->lblSweepTime->setText(strInfo);
        break;
    }
    return ;
}
void BitSA::refreshBw(qint32 mIndex)
{
    qint32 index;
    qreal value,status;
    QString strInfo;
    switch (mIndex) {
    case SA_INFO_BW_RBW_AUTO:
    case SA_INFO_BW_RBW_VALUE:
    case SA_INFO_BW_VBW_AUTO:
    case SA_INFO_BW_VBW_VALUE:
        status = pcontrolInterface->getRbwStatus();
        if(status==SA_AUTO)
        {
            strInfo = "Auto";
        }else
        {
            strInfo = "Manual";
        }
        pBitSA->lblRBWType->setText(strInfo);

        value = pcontrolInterface->getRbwValue();
        strInfo = m_user_variable->freqValueToQstring(value);
        pBitSA->lblRBWValue->setText(strInfo);

        status = pcontrolInterface->getVbwStatus();
        if(status==SA_AUTO)
        {
            strInfo = "Auto";
        }else
        {
            strInfo = "Manual";
        }
        pBitSA->lblVBWType->setText(strInfo);

        value = pcontrolInterface->getVbwValue();
        strInfo = m_user_variable->freqValueToQstring(value);
        pBitSA->lblVBWValue->setText(strInfo);
        break;
    case SA_INFO_BW_IF_OUTPUT:
        index = pcontrolInterface->getIFOutPut();
        switch (index) {
        case SA_AUTO_IFMODE:
            strInfo = "Off";
            break;
        case SA_10M_IFMODE:
            strInfo = "Narrow 10MHz";
            break;
        case SA_100M_IFMODE:
            strInfo = "Wide 100MHz";
            break;
        }
        pBitSA->lblIFOutPutValue->setText(strInfo);
        break;
    default:
        break;
    }
    return;
}

void BitSA::refreshLimit(qint32 mIndex)
{ 
    qint32 status;
    qint32 limitStatus = 0;
    QString strInfo;
    switch (mIndex) {
    case SA_INFO_LIMIT_VIEW:
        for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
        {
            status = pcontrolInterface->getLimitLineStatus(i);
            if(SA_ON == status)
            {
                limitStatus = 1;
                break;
            }
        }
        if(limitStatus)
        {
            strInfo = "On";
        }else
        {
            strInfo = "Off";
        }
        pBitSA->lblLimitStatus->setText(strInfo);
        break;
    default:
        break;
    }
    return;
}

void BitSA::refreshTrigger(qint32 mIndex)
{
    qint32 mode;
    QString strInfo;
    switch (mIndex) {
    case SA_INFO_TRIGGER_MODE:
        mode = pcontrolInterface->getTriggerMode();
        switch (mode) {
        case SA_TRIGGER_FREE_RUN:
            strInfo="Free Run";
            break;
        case SA_TRIGGER_VIDEO:
            strInfo="Video";
            break;
        case SA_TRIGGER_EXTERNAL:
            strInfo="External";
            break;
        case SA_TRIGGER_PERIODIC_TIMER:
            strInfo="Periodic Timer";
            break;
        case SA_TRIGGER_RF_BURST:
            strInfo="RF Burst";
            break;
        case SA_TRIGGER_GPS:
            strInfo="GPS";
            break;
        default:
            break;
        }
        pBitSA->lblTrigger->setText(strInfo);
        break;
    default:
        break;
    }

}

void BitSA::refreshTrace(qint32 mIndex)
{    
    qint32 traceNo,detectorMode;
    QString strInfo;
    qint32 curAve,cntAve;
    switch (mIndex)
    {
    case SA_INFO_TRACE_CURAVE:
    case SA_INFO_TRACE_AVE:
        traceNo = pcontrolInterface->getTraceSelect();
        curAve = m_user_variable->gAverageNo[traceNo];
        if(pcontrolInterface->getTraceAverageStatus(traceNo) == SA_ON)
            curAve = curAve + 1;
        cntAve = m_user_variable->gAverageCount[traceNo];
        curAve = curAve > cntAve ? cntAve : curAve;
        if(pcontrolInterface->getTraceAverageStatus(traceNo) == SA_ON)
        {
            pBitSA->lblAverageValue->setText(QString("%1%2%3").arg(curAve).arg("/").arg(cntAve));
        }else
        {
            pBitSA->lblAverageValue->setText(QString("%1%2%3").arg("--").arg("/").arg("--"));
        }

        if(pcontrolInterface->getTraceAverageStatus())
        {
            pBitSA->lblAveOn->setText("On");
        }else
        {
            pBitSA->lblAveOn->setText("Off");
        }
        refreshTraceType();
        break;
    case SA_INFO_TRACE_INDEX:
        refreshTraceStatus();
        break;

        on_refreshMarkerInfo();
        break;
    case SA_INFO_TRACE_DETECTOR:
        detectorMode = pcontrolInterface->getDetectorMode();
        switch (detectorMode) {
        case SA_AUTO_DETECTOR:
        case SA_COMMON:
            strInfo = "Normal";
            break;
        case SA_POSITIVE_PEAK:
            strInfo = "Positive Peak";
            break;
        case SA_NEGATIVE_PEAK:
            strInfo = "Negative Peak";
            break;
        case SA_SAMPLE:
            strInfo = "Sample";
            break;
        case SA_AVERAGE_VOTAGE:
            strInfo = "Average Votage";
            break;
        case SA_RMS:
            strInfo = "RMS";
            break;
        default:
            break;
        }
        pBitSA->lblDetectorValue->setText(strInfo);
        break;
    case SA_INFO_TRACE_VIEW:
        traceNo = pcontrolInterface->getTraceSelect();
        on_refreshMarkerInfo();
        refreshTraceStatus();
        break;
    case SA_INFO_TRACE_TYPE:
        refreshTraceType();
        break;
    default:
        break;
    }
}

void BitSA::refreshTraceStatus()
{
    qint32 trace,status,type;
    QString strqss,strbg,strTrace;
    trace = pcontrolInterface->getTraceSelect();
    for(qint32 i=0;i<TRACE_CNT_TOTAL;i++)
    {
        status = pcontrolInterface->getTraceViewStatus(i);
        type = pcontrolInterface->getTraceType(i);
        if(i == trace && SA_ON == status)
        {
            strbg = QString("#lblbgT%1{background-image: url(:/sa/image/T%2_selected_box.png);}\n").arg(QString::number(i+1)).arg(QString::number(i+1));
            strTrace = QString("#lblT%1{image: url(:/sa/image/T%2_bk.png);}\n").arg(QString::number(i+1)).arg(QString::number(i+1));
        }
        else
        {
            strbg = QString("#lblbgT%1{}\n").arg(QString::number(i+1));
            strTrace = QString("#lblT%1{image: url(:/sa/image/T%2_color.png);}\n").arg(QString::number(i+1)).arg(QString::number(i+1));
        }
        strqss = strqss + strbg + strTrace;
    }
    pBitSA->widget_Trace->setStyleSheet(strqss);
    refreshTraceType();
}
void BitSA::refreshTraceType()
{
    qint32 traceNo,traceType,traceView;
    QString strInfo,strQss;
    for(int i=0;i<TRACE_CNT_TOTAL;i++)
    {
        traceNo = pcontrolInterface->getTraceSelect();
        traceType = pcontrolInterface->getTraceType(i);
        traceView = pcontrolInterface->getTraceViewStatus(i);
        switch (traceType)
        {
        case SA_CLEAR_WRITE:
            strInfo = "W";
            break;
        case SA_MAX_HOLD:

            strInfo = "M";
            break;
        case SA_MIN_HOLD:
            strInfo = "_m";
            break;
        case SA_VIEW:
            strInfo = "V";
            break;
        case SA_TRACE_AVE:
            strInfo = "A";
            break;
        }
        if(traceView == SA_ON)
        {
            strQss = QString("#lblTypeT%1{background-image: url(:/sa/image/%2_bk.png);}\n").arg(QString::number(i+1)).arg(strInfo);
        }else if(traceView == SA_OFF)
        {
            strQss = QString("#lblTypeT%1{image: url(:/sa/image/%2_bk_off.png);}\n").arg(QString::number(i+1)).arg(strInfo);
        }
        //Miss the picture of current trace and that is on
        if((i != traceNo)&& (traceView == SA_ON))
        {
            switch (traceType)
            {
            case SA_CLEAR_WRITE:
                strInfo = "W";
                break;
            case SA_MAX_HOLD:
                strInfo = "M";
                break;
            case SA_MIN_HOLD:
                strInfo = "m";
                break;
            case SA_VIEW:
                strInfo = "V";
                break;
            case SA_TRACE_AVE:
                strInfo = "A";
                break;
            }
            switch (i) {
            case TR1:
                pBitSA->lblTypeT1->setText(strInfo);
                pBitSA->lblTypeT1->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            case TR2:
                pBitSA->lblTypeT2->setText(strInfo);
                pBitSA->lblTypeT2->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            case TR3:
                pBitSA->lblTypeT3->setText(strInfo);
                pBitSA->lblTypeT3->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            case TR4:
                pBitSA->lblTypeT4->setText(strInfo);
                pBitSA->lblTypeT4->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            case TR5:
                pBitSA->lblTypeT5->setText(strInfo);
                pBitSA->lblTypeT5->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            case TR6:
                pBitSA->lblTypeT6->setText(strInfo);
                pBitSA->lblTypeT6->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            }
        }else if((i == traceNo)&& (traceView == SA_ON))
        {
            switch (traceType)
            {
            case SA_CLEAR_WRITE:
                strInfo = "W";
                break;
            case SA_MAX_HOLD:
                strInfo = "M";
                break;
            case SA_MIN_HOLD:
                strInfo = "m";
                break;
            case SA_VIEW:
                strInfo = "V";
                break;
            case SA_TRACE_AVE:
                strInfo = "A";
                break;
            }
            switch (i) {
            case TR1:
                pBitSA->lblTypeT1->setText(strInfo);
                pBitSA->lblTypeT1->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            case TR2:
                pBitSA->lblTypeT2->setText(strInfo);
                pBitSA->lblTypeT2->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            case TR3:
                pBitSA->lblTypeT3->setText(strInfo);
                pBitSA->lblTypeT3->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            case TR4:
                pBitSA->lblTypeT4->setText(strInfo);
                pBitSA->lblTypeT4->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            case TR5:
                pBitSA->lblTypeT5->setText(strInfo);
                pBitSA->lblTypeT5->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            case TR6:
                pBitSA->lblTypeT6->setText(strInfo);
                pBitSA->lblTypeT6->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            }
        }else
        {
            switch (i) {
            case TR1:
                pBitSA->lblTypeT1->setText("");
                pBitSA->lblTypeT1->setStyleSheet(strQss);
                break;
            case TR2:
                pBitSA->lblTypeT2->setText("");
                pBitSA->lblTypeT2->setStyleSheet(strQss);
                break;
            case TR3:
                pBitSA->lblTypeT3->setText("");
                pBitSA->lblTypeT3->setStyleSheet(strQss);
                break;
            case TR4:
                pBitSA->lblTypeT4->setText("");
                pBitSA->lblTypeT4->setStyleSheet(strQss);
                break;
            case TR5:
                pBitSA->lblTypeT5->setText("");
                pBitSA->lblTypeT5->setStyleSheet(strQss);
                break;
            case TR6:
                pBitSA->lblTypeT6->setText("");
                pBitSA->lblTypeT6->setStyleSheet(strQss);
                break;
            }
        }
    }

}
void BitSA::refreshMarker(qint32 mIndex)
{
    switch (mIndex) {
    case SA_INFO_MARKER_INDEX:
        if(!pBitSA->buttomMarker->isHidden())
        {
            mBtnMkrGroup->button(pcontrolInterface->getMarkerSelect())->setChecked(true);
        }
//        if(mSetupDialog && m_user_variable->PrimaryAction == SA_MARKER_TAB)
//        {
//            showMarkerTableIcon(SA_OFF);
//            showMarkerTableIcon(SA_ON);
//        }
        //Clicked marker when sweep type is single.
        if(pcontrolInterface->getSweepType() == SA_SINGLE)
        {
            repaint(CenterDrawRect);
        }
        break;
    case SA_INFO_MARKER_VIEW:
        on_refreshMarkerInfo();
        break;
    case SA_INFO_MARKER_VALUE:
        on_refreshMarkerInfo();
        break;
    default:
        break;
    }
    return;
}

void BitSA::refreshBtnFocus(qint32 mIndex)
{
    switch (mIndex)
    {
    case SA_INFO_MARKER_INDEX:
        if(m_user_variable->PrimaryAction != SA_MARKER && m_user_variable->PrimaryAction != SA_MARKER_TAB)
        {
            mBtnGroup->button(SA_MARKER_DIALOG)->setChecked(true);
            m_user_variable->PrimaryAction = SA_MARKER;
            menuClose();
            //this->setFocusPolicy(Qt::StrongFocus);
            this->setFocus();
        }
        break;
    }
}
void BitSA::refreshMeasure(qint32 mIndex)
{
    modeChange();
    qint32 index;
    QString strGab;
    index = m_user_variable->currentMode;
    strGab = QString(SA_MeasureName[index]);
    pBitSA->lblmeasure->setText(strGab);
    switch (index) {
    case SA_SPURIOUS_EMISSION_MASK_MODE:
        //setParaForSpurEM();
        break;
    default:
        break;
    }
    refreshFreq(SA_INFO_FREQ_CENTER);
    refreshAmpt(SA_INFO_AMPT_PREAMP);
    refreshAmpt(SA_INFO_AMPT_ATTENTYPE);
    refreshAmpt(SA_INFO_AMPT_ATTEN);
    refreshAmpt(SA_INFO_AMPT_OFFSET);
    refreshAmpt(SA_INFO_AMPT_UNIT);
    refreshBw(SA_INFO_BW_RBW_AUTO);
    refreshBw(SA_INFO_BW_RBW_VALUE);
    refreshBw(SA_INFO_BW_VBW_AUTO);
    refreshBw(SA_INFO_BW_VBW_VALUE);
    refreshSweep(SA_INFO_SWEEP_MODE);
    refreshSweep(SA_INFO_SWEEP_TIME);
    refreshTrace(SA_INFO_TRACE_DETECTOR);
    refreshSystem(SA_INFO_SYSTEM_FREQ_REF);
    refreshTrigger(SA_INFO_TRIGGER_MODE);
    refreshBw(SA_INFO_BW_IF_OUTPUT);
    refreshLimit(SA_INFO_LIMIT_VIEW);
    refreshTrace(SA_INFO_TRACE_AVE);
    refreshTrace(SA_INFO_TRACE_TYPE);
    refreshTrace(SA_INFO_TRACE_INDEX);
    refreshTrace(SA_INFO_TRACE_VIEW);
    refreshMarker(SA_INFO_MARKER_INDEX);
    refreshMarker(SA_INFO_MARKER_VIEW);
}

void BitSA::initInfo()
{
    refreshMeasure(SA_INFO_MEASURE);

    refreshFreq(SA_INFO_FREQ_CENTER);

    refreshAmpt(SA_INFO_AMPT_PREAMP);
    refreshAmpt(SA_INFO_AMPT_ATTENTYPE);
    refreshAmpt(SA_INFO_AMPT_ATTEN);
    refreshAmpt(SA_INFO_AMPT_OFFSET);
    refreshAmpt(SA_INFO_AMPT_UNIT);

    refreshBw(SA_INFO_BW_RBW_AUTO);
    refreshBw(SA_INFO_BW_RBW_VALUE);
    refreshBw(SA_INFO_BW_VBW_AUTO);
    refreshBw(SA_INFO_BW_VBW_VALUE);

    refreshSweep(SA_INFO_SWEEP_MODE);
    refreshSweep(SA_INFO_SWEEP_TIME);
    refreshTrace(SA_INFO_TRACE_DETECTOR);

    refreshSystem(SA_INFO_SYSTEM_FREQ_REF);
    refreshTrigger(SA_INFO_TRIGGER_MODE);
    refreshBw(SA_INFO_BW_IF_OUTPUT);

    refreshLimit(SA_INFO_LIMIT_VIEW);

    refreshTrace(SA_INFO_TRACE_AVE);
    refreshTrace(SA_INFO_TRACE_TYPE);
    refreshTrace(SA_INFO_TRACE_INDEX);
    refreshTrace(SA_INFO_TRACE_VIEW);
    refreshMarker(SA_INFO_MARKER_INDEX);
    refreshMarker(SA_INFO_MARKER_VIEW);
    return;
}

void BitSA::on_WidgetClicked()
{
    qint32 index;
    SA_ClickedWidget* widget = qobject_cast<SA_ClickedWidget*>(sender());
    index = mInfoWidget->value(widget);
    mBtnGroup->button(index)->setChecked(true);
    runBtnFunction(index);
    return;
}

void BitSA::on_lblAverage_clicked()
{
    runBtnFunction(SA_TRACE_DIALOG);
    return;
}

void BitSA::on_lblAverageValue_clicked()
{
    runBtnFunction(SA_TRACE_DIALOG);
    return;
}

qint32 BitSA::setParaForSEM()
{

    quint32 tempflag = 0;
    qint32 freqIndex = m_user_variable->gSpecEMSweepIndex;
    qreal mRBW,mVBW;

    if(!m_user_variable->gMsFirstFlag)
    {
        freqIndex = (freqIndex +1)%(SA_SPECEM_FREQ_CNT + 1);
        if(freqIndex == 0 && pcontrolInterface->getSweepType() == SA_SINGLE)
        {
            if(pcontrolInterface->getTraceAverageStatus(0) == SA_ON)
            {
                #if 0
                if(SA_sm_config_sweep->uAllSweepCompleteFlag == 1)
                #endif
                {
                    pcontrolInterface->setMeasureStatus(SA_OFF);
                }
            }else
            {
                pcontrolInterface->setMeasureStatus(SA_OFF);
            }
            return true;
        }
    }
    else
    {
        //Tony 19005
        bParaLoad = true;
        pcontrolInterface->blockSignals(true);
        m_user_variable->gIgnoreLimit = 1;
        m_user_variable->gAutoRepeat = 0;
        pcontrolInterface->setAutoRbwStatus(SA_MANUAL);
        pcontrolInterface->setCenterFreq(1800000000LL+m_user_variable->gfreqOffset);
        pcontrolInterface->setSpan(30000000LL);
        pcontrolInterface->setAutoSweepTimeStatus(SA_MANUAL);
        m_user_variable->gAutoRepeat = 1;
        m_user_variable->gIgnoreLimit = 0;
        pcontrolInterface->blockSignals(false);
        bParaLoad = false;
        freqIndex = 0;
        m_user_variable->gMsFirstFlag = 0;
    }

    m_user_variable->gSpecEMSweepIndex = freqIndex;
    switch (freqIndex)
    {
    case 0:
        mRBW =  300000;//m_user_variable->gRbw;
        mVBW =  300000;//m_user_variable->gVbw;
        break;
    default:
        mRBW = m_user_variable->gSpecEMData[freqIndex-1].rbw;
        mVBW = m_user_variable->gSpecEMData[freqIndex-1].vbw;
        break;
    }
    bParaLoad = true;
    pcontrolInterface->blockSignals(true);
    m_user_variable->gIgnoreLimit = 1;
    m_user_variable->gAutoRepeat = 0;
    pcontrolInterface->setRbwValue(mRBW);
    if(mRBW > 50000)
    {
        pcontrolInterface->setSweepTime(120);
    }
    else
    {
        pcontrolInterface->setSweepTime(2000);
    }
    m_user_variable->gAutoRepeat = 1;
    m_user_variable->gIgnoreLimit = 0;
    pcontrolInterface->blockSignals(false);

    bParaLoad = false;
    //SA_Set_config_flag(IXT_SA_ConfigSweep,IXS_SA_PARALOAD);

    DelayFunc(100);
    #if 0
    SA_sm_config_sweep->SweepType = SA_SINGLE;
    #endif
    //Refresh UI
    refreshFreq(SA_INFO_FREQ_CENTER);
    refreshBw(SA_INFO_BW_RBW_AUTO);
    refreshBw(SA_INFO_BW_RBW_VALUE);
    refreshBw(SA_INFO_BW_VBW_AUTO);
    refreshBw(SA_INFO_BW_VBW_VALUE);
    refreshSweep(SA_INFO_SWEEP_TIME);
    return true;
}

qint32 BitSA::setParaForSpurEM()
{
    //pcontrolInterface->setSuspendFunc(1);
    qreal mRBW,mVBW,mStopFreq,mStartFreq,mSweepTime,mAtten,mCenter,span;
    quint64 mSpan;
    //    qint32 mSpurAveType;
    QList <qint32> indexList;
    qint32 freqIndex;
    qint32 cnt = 0;
    //get the index that view is on.
    for(qint32 i = 0;i < SA_SPUREM_RANGE_CNT;i++)
    {
        if(m_user_variable->gSpurEMViewStatus[i] == SA_ON)
        {
            indexList << i;
            cnt++;
        }
    }

    if(cnt<1)
    {
        m_user_variable->gMsFirstFlag = 0;

        pcontrolInterface->setMeasureStatus(SA_OFF);
        /*
        if(pcontrolInterface->getSweepType() == SA_SINGLE)
        {
            pcontrolInterface->setMeasureStatus(SA_OFF);
        }else
        {
            if(pcontrolInterface->getSpurEMAveType() == SA_SPUREM_AVE_EXP)
                pcontrolInterface->setMeasureStatus(SA_OFF);
        }
        */
        return true;
    }

    qint32 lastID;

    if(m_user_variable->gMsFirstFlag)
    {

        freqIndex = indexList.at(0);

        //Tony 0619
        pcontrolInterface->blockSignals(true);
        m_user_variable->gSpurEMCurDrawRangeIndex = 0;
        m_user_variable->gIgnoreLimit = 1;
        m_user_variable->gAutoRepeat = 0;
        bParaLoad = true;
        pcontrolInterface->setAttenStatus(SA_MANUAL);
        pcontrolInterface->setAutoRbwStatus(SA_MANUAL);
        bParaLoad = false;
        m_user_variable->gAutoRepeat = 1;
        m_user_variable->gIgnoreLimit = 0;
        pcontrolInterface->blockSignals(false);

    }
    else
    {
        freqIndex = m_user_variable->gSpurEMCurDrawRangeIndex;
        lastID = indexList.indexOf(freqIndex);
        if(lastID ==(cnt -1))
        {
            if(pcontrolInterface->getSweepType() == SA_SINGLE)
            {
                if(pcontrolInterface->getTraceAverageStatus(0) == SA_ON)
                {
                    #if 0
                    if(SA_sm_config_sweep->uAllSweepCompleteFlag)
                    #endif
                    {
                        pcontrolInterface->setMeasureStatus(SA_OFF);
                        return true;
                    }
                }else
                {
                    pcontrolInterface->setMeasureStatus(SA_OFF);
                    return true;
                }
                return true;

            }else
            {
                if(pcontrolInterface->getSpurEMAveType() == SA_SPUREM_AVE_EXP)
                {
                    pcontrolInterface->setMeasureStatus(SA_OFF);
                    return true;
                }else
                {
                    freqIndex =indexList.at(0);
                }
            }
        }else
        {
            freqIndex = indexList.at(lastID+1);
        }
    }
    mStopFreq = m_user_variable->gSpurEMPara[freqIndex].stopFreq;
    mStartFreq = m_user_variable->gSpurEMPara[freqIndex].startFreq;
    mSweepTime = m_user_variable->gSpurEMPara[freqIndex].SweepTime;
    if(mSweepTime < 100)
    {
        //mSweepTime = 100;
    }
    mRBW = m_user_variable->gSpurEMPara[freqIndex].RBW;
    mVBW = m_user_variable->gSpurEMPara[freqIndex].VBW;
    mAtten = m_user_variable->gSpurEMPara[freqIndex].Atten;

    span = mStopFreq - mStartFreq;
    mSpan = span;
    if((mSpan + 0.1) < span)
    {
        mSpan++;
    }

    mCenter = (mStartFreq + mStopFreq)/2;

    m_user_variable->gAutoRepeat = 0;
    pcontrolInterface->blockSignals(true);
    m_user_variable->gIgnoreLimit = 1;
    bParaLoad = true;
    pcontrolInterface->setRbwValue(mRBW);
    pcontrolInterface->setCenterFreq(mCenter);
    pcontrolInterface->setSpan(mSpan);
    pcontrolInterface->setSweepTime(mSweepTime);
    pcontrolInterface->setAttenValue(mAtten);
    bParaLoad = false;
    m_user_variable->gAutoRepeat = 1;
    m_user_variable->gIgnoreLimit = 0;
    pcontrolInterface->blockSignals(false);

    if(m_user_variable->gMsFirstFlag)
    {
        m_user_variable->gMsFirstFlag = 0;

    }


//    SA_Set_config_flag(IXT_SA_ConfigSweep,IXS_SA_PARALOAD);
    DelayFunc(100);
    #if 0
    SA_sm_config_sweep->SweepType = SA_SINGLE;
    #endif
    m_user_variable->gSpurEMCurDrawRangeIndex = freqIndex;
    m_user_variable->gSpurEMPara[freqIndex].stopFreq = pcontrolInterface->getStopFreq();
    m_user_variable->gSpurEMPara[freqIndex].startFreq = pcontrolInterface->getStartFreq();
    m_user_variable->gSpurEMPara[freqIndex].SweepTime = pcontrolInterface->getSweepTime();
    m_user_variable->gSpurEMPara[freqIndex].RBW = pcontrolInterface->getRbwValue();
    m_user_variable->gSpurEMPara[freqIndex].VBW = pcontrolInterface->getVbwValue();
    m_user_variable->gSpurEMPara[freqIndex].Atten = pcontrolInterface->getAttenValue();

    refreshFreq(SA_INFO_FREQ_CENTER);
    refreshAmpt(SA_INFO_AMPT_ATTEN);
    refreshBw(SA_INFO_BW_RBW_AUTO);
    refreshBw(SA_INFO_BW_RBW_VALUE);
    refreshBw(SA_INFO_BW_VBW_AUTO);
    refreshBw(SA_INFO_BW_VBW_VALUE);
    refreshSweep(SA_INFO_SWEEP_TIME);
    return true;
}

qint32 BitSA::DelayFunc(qint32 timeMs)
{
    //usleep(timeMs*1000);
    QThread::usleep(timeMs*1000);
    return true;
#if 1
    if(modeChangeFlag)
    {
        modeChangeFlag = 0;
        return false;
    }
    if(!this->isActiveWindow())
    {
        return false;
    }
    if(!mloop){
        mloop = new QEventLoop();
    }
//    connect(mDelayTimer,SIGNAL(timeout()),mloop,SLOT(quit));
//    mDelayTimer->start(timeMs);
    QTimer::singleShot(timeMs,mloop,SLOT(quit()));
    mloop->exec(/*QEventLoop::ExcludeUserInputEvents*/);
    if(mloop)
    {
        delete mloop;
        mloop = NULL;
    }
    if(modeChangeFlag)
    {
        modeChangeFlag = 0;
        return false;
    }
    return true;
#endif
}

void BitSA::loopQuit()
{
    if(mloop)
    {
        mloop->quit();
    }
}
//if mode chande and DelayFunc()
void BitSA::modeChange()
{
    modeChangeFlag = 1;
    if(mloop)
    {
        loopQuit();
    }
}
/**
 * @brief setRbwValue
 * @param uRbwValue
 */
void BitSA::setSpecEMBwValue(quint64 uRbwValue,quint64 uVbwValue)
{
    qreal gVbwtoRbw = (qreal)uVbwValue/uRbwValue;

    qreal mminzerotime = 0.;
    quint32 tempflag = 0;

    //*****************send control to FPGA
    bitaloth->ConfigureSweepCoupling(m_user_variable->gAutoRbw,m_user_variable->gRbw,m_user_variable->gAutoVbw,m_user_variable->gVbw,1,m_user_variable->gVbwtoRbw);
    if(m_user_variable->gcheckswitch != m_user_variable->goldcheckswitch)
    {
//        tempflag |= IXS_SA_CheckAciton;
        m_user_variable->goldcheckswitch = m_user_variable->gcheckswitch;
    }
//    SA_sm_config_sweep->RBW = uRbwValue ;
#if USABLE
    SA_sm_config_sweep->RBWAuto = m_user_variable->gAutoRbw;
#endif

#if USABLE
    SA_sm_config_sweep->VBWAuto = m_user_variable->gAutoVbw;
    SA_sm_config_sweep->VBWTORBW = gVbwtoRbw;
    SA_sm_config_sweep->VBWTORBWAuto = m_user_variable->gAutoVbwtoRbw;
#endif

    if(m_user_variable->gSpanMode)
    {
        mminzerotime = bitaloth->GetZeroSpanRbwMinms(NUM_SWEEP_POINT);
        m_user_variable->gZeroSpanTime = m_user_variable->gZeroSpanTime < mminzerotime ? mminzerotime : m_user_variable->gZeroSpanTime;
        m_user_variable->gSweepTime = m_user_variable->gZeroSpanTime;
        bitaloth->GetZeroShmTimes(m_user_variable->gSweepTime,NUM_SWEEP_POINT);
    }
}

void BitSA::on_lblDetectors_clicked()
{
    showMenu(SA_TRACE_DIALOG);
    return;
}

void BitSA::on_lblDetectorValue_clicked()
{
    showMenu(SA_TRACE_DIALOG);
    return;
}

void BitSA::on_lblIFOutPut_clicked()
{
    showMenu(SA_BW_DIALOG);
    return ;
}

void BitSA::on_lblIFOutPutValue_clicked()
{
    showMenu(SA_BW_DIALOG);
    return ;
}

/**
 * @brief BitSA::measureModeParaRefresh
 */
void BitSA::measureModeParaRefresh()
{
    if(m_user_variable->gCurrentWorkState == SA_MEASUREPARASET_DIALOG && mSetupDialog)
    {
        if(m_user_variable->currentMode == SA_CHNLPOWER_MEASURE_MODE)
        {
            qobject_cast<sa_dialog_chnlpowerset *>(mSetupDialog)->refreshEditDisplay();
        }
        else if(m_user_variable->currentMode == SA_ACP_MEASURE_MODE || m_user_variable->currentMode == SA_MULTI_ACP_MODE)
        {
            qobject_cast<sa_dialog_acpset *>(mSetupDialog)->initDisplay();
        }
    }
}

/**
* @brief for plt to call to change ana mode mea item
* @param[in]item:measure index same with plut widget
* @param[in]
* @return
*/
void BitSA::SetMeasureItems(qint32 item)
{
    pcontrolInterface->SetMeasureItems(item);
    return;
}
/**
* @brief for plt to call to tell now running mode
* @param[in]imode: SA_MODE 0, RTSA_MODE 1,INTERF_MODE 2,PM_MODE 3,LTE_FDD_MODE 4,FIVE_G_MODE 5
* @param[in]
* @return
*/
void BitSA::PltCurAnaMode(qint32 imode)
{
    pcontrolInterface->PltCurAnaMode(imode);
    return;
}
/**
* @brief for plt to call to save now running mode and power state
* @param[in]itype:default 0,last 1,user 2
* @param[in]
* @return error<0
*/
qint32 BitSA::PltSavePres(qint32 itype)
{
    qint32 iback = pcontrolInterface->PltSavePres(itype);
    return iback;
}
/**
* @brief for plt to call to save ctrl states
* @param[in]itype:default 0,last 1,user 2
* @param[in]
* @return error<0
*/
qint32 BitSA::PltSaveConditions(qint32 itype)
{
    qint32 iback = pcontrolInterface->PltSaveConditions(itype);
    return iback;
}
/**
* @brief for plt to call to load states
* @param[in]itype:default 0,last 1,user 2
* @param[in]
* @return error<0
*/
qint32 BitSA::PltLoadConditions(qint32 itype)
{
    qint32 iback = pcontrolInterface->PltLoadConditions(itype);
    return iback;
}
/**
* @brief for plt to call to change ui state when other mode do lock action
* @param[in]ilock:unlock 0,lock 1
* @param[in]
* @return
*/
void BitSA::ChangeLcdStateWithNoSig(qint32 ilock)
{
    pcontrolInterface->ChangeLcdStateWithNoSig(ilock);
    return;
}
/**
* @brief for plt to call to close ana pop widget
* @param[in]
* @param[in]
* @return
*/
void BitSA::MenuClose()
{
    menuClose();
    return;
}
/**
* @brief for plt to call to tell ctrl mode
* @param[in]imode:local 0, remote 1
* @param[in]
* @return
*/
void BitSA::SetLocalRemoteMode(qint32 imode)
{
    pcontrolInterface->SetLocalRemoteMode(imode);
    return;
}
/**
* @brief for plt to call to preset factory states
* @param[in]
* @param[in]
* @return
*/
void BitSA::PresetDefaultStates()
{
    pcontrolInterface->PresetDefaultStates();
    return ;
}
/**
* @brief for plt to call to set display mode
* @param[in]imode:indoor 0, outdoor 1 ,night 2
* @param[in]
* @return error<0
*/
void BitSA::SetDisplayMode(qint32 imode)
{
    pcontrolInterface->SetDisplayMode(imode);
    return;
}

/**
* @brief for plt to call to change other ana mode ui states when setting ref
* @param[in]imode:Internal 0, External 10 MHz 1 ,External 13 MHz 2,External 15 MHz 3,GPS 4
* @param[in]
* @return error<0
*/
 void BitSA::SetSysRefuiStates(qint32 itype)
 {
     pcontrolInterface->SetSysRefuiStates(itype);
 }
