/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                BVTableWidget.cpp
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2018/09/05
** Descriptions:             customized class inherited from QTableWidget,be used to Limit Edit module
**
*********************************************************************************************************/
#include "bvtablewidget.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QHeaderView>
#include <QApplication>

BVTableWidget::BVTableWidget(BIT_FREQ_INFO *freqinfo, ctrlmana *mctrlmana, QWidget* parent, Qt::WindowFlags f):
    QTableWidget(parent),
    gfreqinfo(freqinfo),
    gctrlmana(mctrlmana)
{
    connect(this->horizontalHeader(),SIGNAL(sectionClicked(qint32)),this,SLOT(headerClicked(qint32)));
    initTableWidgetValue();

    memset(dFreq,0,sizeof(qreal)*1000);
    memset(dAmplitude,0,sizeof(qreal)*1000);
}
/**
* reset all parameter
* @param[in] void
* @return    void
*/
void BVTableWidget::resetAllParam(void)
{
    memset(newDataString,0,sizeof(char)*20);
    blNumberInput = false;
    blFirstIn = true;
    blDotInput = false;
    bUpdateLimit = true;
    currentRowIndex = 0;
    currentColumnIndex = 0;
}
/**
* process key 0 to key 9
* @param[in] buffer     char
* @param[in] string     QString
* @param[in] tableItem  QTableWidgetItem
* @return    void
* @not
*/
void BVTableWidget::numberProcess(char *number, QString qShowStr,QTableWidgetItem *widgetItem)
{
    if(blFirstIn){
        memset(newDataString,0,sizeof(newDataString));
        strcpy(newDataString,number);
        blDotInput = false;
        blFirstIn = false;
    }
    else
    {
        strncat(newDataString,number,1);
    }
    blNumberInput = true;

    qShowStr = QString("%1").arg(newDataString);
    widgetItem = new QTableWidgetItem(qShowStr);
    setItem(currentRow(),currentColumn(),widgetItem);
    currentRowIndex = currentRow();
    currentColumnIndex = currentColumn();
    bUpdateLimit  = false;
}
/**
* process left key
* @param[in] void
* @return    void
* @not
*/
void BVTableWidget::leftKeyProcess(void)
{
    QString strValue;

    blNumberInput = false;
    blFirstIn     = true;
    blDotInput    = false;
    bUpdateLimit  = false;

    qint32 columnIndex = currentColumn();
    qint32 rowIndex    = currentRow();
    if(columnIndex == 0 && rowIndex > 0){
        QTableWidgetItem *widgetItem = item(rowIndex-1,1);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        judgeTableContent(this,gfreqinfo->gstartfreq,gfreqinfo->gstopfreq,false);

        sortAllItems();
        setCurrentCell(rowIndex-1,1);
        currentRowIndex = currentRow();
        currentColumnIndex = currentColumn();
    }
    else if(columnIndex == 1){
        QTableWidgetItem *widgetItem = item(rowIndex,0);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        judgeTableContent(this,gfreqinfo->gstartfreq,gfreqinfo->gstopfreq,false);

        setCurrentCell(rowIndex,0);
        currentRowIndex = currentRow();
        currentColumnIndex = currentColumn();
    }
}
/**
* process right key
* @param[in] void
* @return    void
* @not
*/
void BVTableWidget::rightKeyProcess(void)
{
    QString strValue;

    blNumberInput = false;
    blFirstIn     = true;
    blDotInput    = false;
    bUpdateLimit  = false;

    qint32 totalRow    = rowCount();
    qint32 columnIndex = currentColumn();
    qint32 rowIndex    = currentRow();
    if(columnIndex == 0){
        QTableWidgetItem *widgetItem = item(rowIndex,1);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        judgeTableContent(this,gfreqinfo->gstartfreq,gfreqinfo->gstopfreq,false);

        setCurrentCell(rowIndex,1);
        currentRowIndex = currentRow();
        currentColumnIndex = currentColumn();
    }
    else if(columnIndex == 1 && rowIndex + 1 < totalRow){
        QTableWidgetItem *widgetItem = item(rowIndex+1,0);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        judgeTableContent(this,gfreqinfo->gstartfreq,gfreqinfo->gstopfreq,false);

        sortAllItems();
        setCurrentCell(rowIndex+1,0);
        currentRowIndex = currentRow();
        currentColumnIndex = currentColumn();
    }
}
/**
* process up key
* @param[in] void
* @return    void
* @not
*/
void BVTableWidget::upKeyProcess(void)
{
    QString strValue;

    blNumberInput = false;
    blFirstIn     = true;
    blDotInput    = false;
    bUpdateLimit  = false;

    qint32 columnIndex = currentColumn();
    qint32 rowIndex    = currentRow();
    if(rowIndex > 0){
        QTableWidgetItem *widgetItem = item(rowIndex-1,columnIndex);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        judgeTableContent(this,gfreqinfo->gstartfreq,gfreqinfo->gstopfreq);

        sortAllItems();
        setCurrentCell(rowIndex-1,columnIndex);
        currentRowIndex = currentRow();
        currentColumnIndex = currentColumn();
    }
}
/**
* process down key
* @param[in] void
* @return    void
* @not
*/
void BVTableWidget::downKeyProcess(void)
{
    QString strValue;

    blNumberInput = false;
    blFirstIn     = true;
    blDotInput    = false;
    bUpdateLimit  = false;

    qint32 totalRow    = rowCount();
    qint32 columnIndex = currentColumn();
    qint32 rowIndex    = currentRow();
    if(totalRow <= 1) return;
    if(rowIndex < totalRow-1){
        QTableWidgetItem *widgetItem = item(rowIndex+1,columnIndex);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        judgeTableContent(this,gfreqinfo->gstartfreq,gfreqinfo->gstopfreq);

        sortAllItems();
        setCurrentCell(rowIndex+1,columnIndex);

        currentRowIndex = currentRow();
        currentColumnIndex = currentColumn();
    }
}
/**
* process dot key
* @param[in] string QString
* @param[in] widgetItem QTableWidgetItem
* @return    void
* @not
*/
void BVTableWidget::dotKeyProcess(QString qShowStr, QTableWidgetItem *widgetItem)
{
    blDotInput = strrchr(newDataString,'.');
    if(!blDotInput&&blNumberInput&&strcmp(newDataString,"-")){
        strncat(newDataString, "." , 1);
        blDotInput = true;
    }

    qShowStr = QString("%1").arg(newDataString);
    widgetItem = new QTableWidgetItem(qShowStr);

    setItem(currentRow(),currentColumn(),widgetItem);
    currentRowIndex = currentRow();
    currentColumnIndex = currentColumn();
    bUpdateLimit  = false;
}
/**
* process Esc key
* @param[in] void
* @return    void
* @not
*/
void BVTableWidget::espKeyProcess(void)
{
    emit editFinish();
    this->close();
}
/**
* process Enter key
* @param[in] void
* @return    void
* @not
*/
void BVTableWidget::enterKeyProcess(void)
{
    char cTmpValue[20];
    memset(cTmpValue,0,sizeof(char)*20);

    blNumberInput       = false;
    blFirstIn           = true;
    blDotInput          = false;
    bUpdateLimit        = true;

    currentColumnIndex = currentColumn();
    currentRowIndex    = currentRow();

    judgeTableContent(this,gfreqinfo->gstartfreq,gfreqinfo->gstopfreq);

    sortAllItems();
    setCurrentCell(currentRowIndex,currentColumnIndex);
    getTableWidgetValue();
}
/**
* process minus key
* @param[in] string QString
* @param[in] widgetItem QTableWidgetItem
* @return    void
* @not
*/
void BVTableWidget::minusKeyProcess(QString qShowStr, QTableWidgetItem *widgetItem)
{
    if(blFirstIn){
        memset(newDataString,0,sizeof(newDataString));
        strcpy(newDataString,"-");
        blDotInput = false;
        blFirstIn = false;
        blNumberInput = true;
    }
    else{
        if (blNumberInput == false){
            strncat(newDataString, "-" , 1);
            blNumberInput = true;
        }
        else{
            if(strlen(newDataString) == 1&&strcmp(newDataString,"-") == 0){
                memset(newDataString,0,sizeof(char)*20);
                blNumberInput = false;
            }
            else{
                if(strchr(newDataString,'.')){
                    qreal DataNumber = atof(newDataString);
                    if(DataNumber>0){
                        for(qint32 i = strlen(newDataString)-1;i>=0;i--){
                            newDataString[i+1] = newDataString[i];
                        }
                        newDataString[0] = '-';
                    }
                    else if(DataNumber<0){
                        for(qint32 i = 0;i<strlen(newDataString);i++){
                            newDataString[i] = newDataString[i+1];
                        }
                    }
                }
                else{
                    qint32 DataNumber = atoi(newDataString);
                    sprintf(newDataString,"%d",-DataNumber);
                }
            }
        }
    }

    qShowStr = QString("%1").arg(newDataString);
    widgetItem = new QTableWidgetItem(qShowStr);
    setItem(currentRow(),currentColumn(),widgetItem);
    currentRowIndex = currentRow();
    currentColumnIndex = currentColumn();
    bUpdateLimit  = false;
}
/**
* process backspace key
* @param[in] string QString
* @param[in] widgetItem QTableWidgetItem
* @return    void
* @not
*/
void BVTableWidget::backSpaceKeyProcess(QString qShowStr, QTableWidgetItem *widgetItem)
{
    qint32 strLen = 0;
    char backupStr[21] = {'\0',};

    strLen = strlen(newDataString);
    if (strLen > 0) {
        strcpy (backupStr, newDataString);
        memset(newDataString, 0, sizeof(newDataString));
        strncpy(newDataString, backupStr, strLen -1);
      }

    if (!strlen(newDataString)){
      blNumberInput = false;
      blDotInput = false;
      blFirstIn  = true;
      bUpdateLimit = true;
    }

    qShowStr = QString("%1").arg(newDataString);
    widgetItem = new QTableWidgetItem(qShowStr);
    setItem(currentRow(),currentColumn(),widgetItem);
    currentRowIndex = currentRow();
    currentColumnIndex = currentColumn();
}
/**
* process all input key
* @param[in] event
* @return    void
*/
void BVTableWidget::keyPressEvent(QKeyEvent *event)
{
    QString qShowStr;
    QTableWidgetItem *widgetItem;

    if(currentRowIndex != currentRow() || currentColumnIndex != currentColumn()) blFirstIn = true;
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }
    switch(event->key()){
    case Qt::Key_0:           numberProcess("0",qShowStr,widgetItem);    break;
    case Qt::Key_1:           numberProcess("1",qShowStr,widgetItem);    break;
    case Qt::Key_2:           numberProcess("2",qShowStr,widgetItem);    break;
    case Qt::Key_3:           numberProcess("3",qShowStr,widgetItem);    break;
    case Qt::Key_4:           numberProcess("4",qShowStr,widgetItem);    break;
    case Qt::Key_5:           numberProcess("5",qShowStr,widgetItem);    break;
    case Qt::Key_6:           numberProcess("6",qShowStr,widgetItem);    break;
    case Qt::Key_7:           numberProcess("7",qShowStr,widgetItem);    break;
    case Qt::Key_8:           numberProcess("8",qShowStr,widgetItem);    break;
    case Qt::Key_9:           numberProcess("9",qShowStr,widgetItem);    break;
    case Qt::Key_Minus:
    case Qt::Key_F2:          minusKeyProcess(qShowStr,widgetItem);      break;
    case Qt::Key_Period:      dotKeyProcess(qShowStr,widgetItem);        break;
    case Qt::Key_Right:
    case Qt::Key_F7:          rightKeyProcess();                         break;
    case Qt::Key_Left:
    case Qt::Key_F6:          leftKeyProcess();                          break;
    case Qt::Key_Up:
    case Qt::Key_F8:          upKeyProcess();                            break;
    case Qt::Key_Down:
    case Qt::Key_F9:          downKeyProcess();                          break;
    case Qt::Key_Return:
    case Qt::Key_Enter:       enterKeyProcess();                         break;
    case Qt::Key_Escape:      espKeyProcess();                           break;
    case Qt::Key_Backspace:   backSpaceKeyProcess(qShowStr,widgetItem);  break;
    default:  break;
  }
}
/**
* calibrate table content
* @param[in] widgetItem QTableWidgetItem
* @param[in] start Frequency
* @param[in] stop Frequency
* @param[in] judge Flag
* @return    void
* @not
*/
void BVTableWidget::judgeTableContent(QTableWidget *tableWidget, qreal startFreq, qreal stopFreq, bool bFlag)
{
    QString strValue;
    char cTmpValue[20];
    char cItemValue[20];
    QTableWidgetItem *tableWidgetItem;

    if(tableWidget->rowCount() == 0) return;

    char currFrqValue[20];
    memset(currFrqValue,0,sizeof(char)*20);
    char currAmpValue[20];
    memset(currAmpValue,0,sizeof(char)*20);

    tableWidgetItem = tableWidget->item(0,0);
    strValue = tableWidgetItem->text();
    qsnprintf(currFrqValue,sizeof(currFrqValue),"%s",strValue.toUtf8().constData());

    tableWidgetItem = tableWidget->item(0,1);
    strValue = tableWidgetItem->text();
    qsnprintf(currAmpValue,sizeof(currAmpValue),"%s",strValue.toUtf8().constData());

    if(bFlag)
    {
        //Judge if it is neccesary to delete the dot who the same frequency
        for(qint32 i = 1;i<tableWidget->rowCount();i++)
        {
            char FreqValue[20];
            memset(FreqValue,0,sizeof(FreqValue));
            char AmpValue[20];
            memset(AmpValue,0,sizeof(AmpValue));

            tableWidgetItem = tableWidget->item(i,0);
            strValue = tableWidgetItem->text();
            qsnprintf(FreqValue,sizeof(FreqValue),"%s",strValue.toUtf8().constData());

            tableWidgetItem = tableWidget->item(i,1);
            strValue = tableWidgetItem->text();
            qsnprintf(AmpValue,sizeof(AmpValue),"%s",strValue.toUtf8().constData());

            if(0 == atof(currFrqValue) - atof(FreqValue)&& 0 == atof(currAmpValue) - atof(AmpValue))
            {
                tableWidget->removeRow(0);
                break;
            }
        }
    }


    //Judge Frequency
    for(qint32 i = 0;i<tableWidget->rowCount();i++)
    {
        memset(cTmpValue,0,sizeof(char)*20);
        memset(cItemValue,0,sizeof(cItemValue));

        //Freq
        tableWidgetItem = tableWidget->item(i,0);
        strValue = tableWidgetItem->text();
        qsnprintf(cItemValue,sizeof(cItemValue),"%s",strValue.toUtf8().constData());

        if(atof(cItemValue)*1000000 < startFreq)
        {
            sprintf(cTmpValue,"%.2f",startFreq/1000000.);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            tableWidget->setItem(i,0,tableWidgetItem);
        }
        else if(atof(cItemValue)*1000000 > stopFreq)
        {
            sprintf(cTmpValue,"%.2f",stopFreq/1000000.);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            tableWidget->setItem(i,0,tableWidgetItem);
        }

        // Judge Amplitude
        tableWidgetItem = tableWidget->item(i,1);
        strValue = tableWidgetItem->text();
        qsnprintf(cItemValue,sizeof(cItemValue),"%s",strValue.toUtf8().constData());

        if(atof(cItemValue) - BIT_TABLEWIDGET_AMP_MIN< 0.) {
            sprintf(cTmpValue,"%.2f",BIT_TABLEWIDGET_AMP_MIN);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            tableWidget->setItem(i,1,tableWidgetItem);
        }
        else if(atof(cItemValue) - BIT_TABLEWIDGET_AMP_MAX > 0.) {
            sprintf(cTmpValue,"%.2f",BIT_TABLEWIDGET_AMP_MAX);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            tableWidget->setItem(i,1,tableWidgetItem);
        }
    }
}
/**
* process mousePress event
* @param[in] event
* @return    void
*/
void BVTableWidget::mousePressEvent(QMouseEvent *event)
{
    emit tabelClicked();
    QTableWidgetItem *tableItem = itemAt(event->x(),event->y());
    qint32 currentMousePressRow = row(tableItem);
    qint32 currentMousePressColumn = column(tableItem);
    if(currentRowIndex != currentMousePressRow) {
        sortAllItems();
        setCurrentCell(currentMousePressRow,currentMousePressColumn);

        blNumberInput = false;
        blFirstIn     = true;
        blDotInput    = false;
        currentRowIndex = currentMousePressRow;
        currentColumnIndex = currentMousePressColumn;

        judgeTableContent(this,gfreqinfo->gstartfreq,gfreqinfo->gstopfreq);
    }
    else if(currentColumnIndex != (unsigned int)currentMousePressColumn){
        setCurrentCell(currentMousePressRow,currentMousePressColumn);

        blNumberInput = false;
        blFirstIn     = true;
        blDotInput    = false;
        currentRowIndex = currentMousePressRow;
        currentColumnIndex = currentMousePressColumn;

        judgeTableContent(this,gfreqinfo->gstartfreq,gfreqinfo->gstopfreq,false);
    }
}
/**
* process header clicked
* @param[in] column index
* @return    void
*/
void BVTableWidget::headerClicked(qint32 index)
{
    if (index != 0)
    {
        horizontalHeader()->setSortIndicatorShown(false);
        return;
    }
    static bool bSortAsc = true;

    Qt::SortOrder order = bSortAsc ? (Qt::AscendingOrder) : (Qt::DescendingOrder);
    horizontalHeader()->setSortIndicatorShown(true);
    horizontalHeader()->setSortIndicator(index, order);

    bSortAsc = !bSortAsc;
}
/**
* get table conent
* @param[in] void
* @return    void
*/
void BVTableWidget::getTableWidgetValue(void)
{
    QString strFreq,strAmplitude;
    QTableWidgetItem *widgetItem;

    if(!rowCount()){
        for(qint32 i = 0;i<gctrlmana->gLimitPointCnt[gctrlmana->gLimitSelect];i++)
        {
//            gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][i] = 0.;
//            gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][i] = 0.;

//            globalUserLimit->limitXAxisCalculatorFunc((unsigned long long)(gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][i]*MHZ),i,globalUserLimit->gLimitSelect);
//            globalUserLimit->LatestLimitYAxisCalculatorFunc(gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][i],i,globalUserLimit->gLimitSelect);
        }
        gctrlmana->gLimitPointCnt[gctrlmana->gLimitSelect] = 0;
    }
    else {
        gctrlmana->gLimitPointCnt[gctrlmana->gLimitSelect] = rowCount();
        for(qint32 i = 0;i<rowCount();i++){
            widgetItem = item(i,0);
            strFreq = widgetItem->text();
            gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][i] = strFreq.toDouble();

            widgetItem = item(i,1);
            strAmplitude = widgetItem->text();
            gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][i] = strAmplitude.toDouble();
      }

        //sort
        for(qint32 i = 0;i<rowCount();i++){
            for(qint32 j = i+1;j<rowCount();j++){
                if(gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][i]>gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][j]){
                    qreal tmp = 0.;
                    tmp = gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][i];
                    gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][i] = gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][j];
                    gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][j] = tmp;

                    tmp = gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][i];
                    gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][i] = gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][j];
                    gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][j] = tmp;
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
void BVTableWidget::initTableWidgetValue(void)
{
    QString strFreq;
    QString strAmplitude;

    qint32 rowNum = rowCount();

    for(qint32 i = rowNum-1;i>=0;i--){
        removeRow(i);
    }

    for(qint32 i = 0;i<gctrlmana->gLimitPointCnt[gctrlmana->gLimitSelect];i++)
    {
        strFreq = QString::number(gctrlmana->gLimitFreq[gctrlmana->gLimitSelect][i],'f',6);
        QTableWidgetItem *freqItem = new QTableWidgetItem(strFreq);
        strAmplitude = QString::number(gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][i],'f',2);
        QTableWidgetItem *amplitudeItem = new QTableWidgetItem(strAmplitude);

        insertRow(i);
        setItem(i,0,freqItem);
        setItem(i,1,amplitudeItem);
    }

    resetAllParam();
}
/**
* sort all items in QTableWidget
* @param[in] viod
* @return    void
*/
void BVTableWidget::sortAllItems(void)
{
    QString strFreq,strAmplitude;
    QTableWidgetItem *widgetItem;

    memset(dFreq,0,sizeof(qreal)*1000);
    memset(dAmplitude,0,sizeof(qreal)*1000);

    //get All Items
    for(qint32 i = 0;i<rowCount();i++){
        widgetItem = item(i,0);
        strFreq = widgetItem->text();
        dFreq[i] = strFreq.toDouble();

        widgetItem = item(i,1);
        strAmplitude = widgetItem->text();
        dAmplitude[i] = strAmplitude.toDouble();
    }

    //sort
    for(qint32 i = 0;i<rowCount();i++){
        for(qint32 j = i+1;j<rowCount();j++){
            if(dFreq[i] >= dFreq[j]){
                qreal tmp = 0.;
                tmp = dFreq[i];
                dFreq[i] = dFreq[j];
                dFreq[j] = tmp;

                tmp = dAmplitude[i];
                dAmplitude[i] = dAmplitude[j];
                dAmplitude[j] = tmp;
            }
        }
    }

    //delete All Items
    qint32 rowNum = rowCount();
    for(qint32 i = rowNum-1;i>=0;i--){
        removeRow(i);
    }

    //reset All Item
    for(qint32 i = 0;i<rowNum;i++){
        strFreq = QString::number(dFreq[i],'f',2);
        QTableWidgetItem *freqItem = new QTableWidgetItem(strFreq);
        strAmplitude = QString::number(dAmplitude[i],'f',2);
        QTableWidgetItem *amplitudeItem = new QTableWidgetItem(strAmplitude);

        insertRow(i);
        setItem(i,0,freqItem);
        setItem(i,1,amplitudeItem);
    }

    //setCurrentCell(0,0);
}
