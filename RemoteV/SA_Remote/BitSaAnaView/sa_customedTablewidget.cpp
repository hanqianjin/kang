/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                clickabletablewidget.cpp
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2018/09/05
** Descriptions:             customized class inherited from QTableWidget,be used to Limit Edit module
**
*********************************************************************************************************/

#include "sa_customedTablewidget.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QHeaderView>

ClickableTableWidget::ClickableTableWidget(QWidget* parent, Qt::WindowFlags f): QTableWidget(parent),
    mParent(parent)
{
    connect(this->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(headerClicked(int)));
//    initTableWidgetValue();

    memset(dFreq,0,sizeof(double)*1000);
    memset(dAmplitude,0,sizeof(double)*1000);
}
/**
* reset all parameter
* @param[in] void
* @return    void
*/
void ClickableTableWidget::resetAllParam(void)
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
* @notify
*/
void ClickableTableWidget::numberProcess(char *number, QString qShowStr,QTableWidgetItem *widgetItem)
{
    if(blFirstIn){
        memset(newDataString,0,sizeof(newDataString));
        strcpy(newDataString,number);
        blDotInput = false;
        blFirstIn = false;
    }
    else /*if(!strlen(newDataString)||strcmp(newDataString,number))*/{
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
void ClickableTableWidget::leftKeyProcess(void)
{
    QString strValue;

    blNumberInput = false;
    blFirstIn     = true;
    blDotInput    = false;
    bUpdateLimit  = false;

    int columnIndex = currentColumn();
    int rowIndex    = currentRow();
    if(columnIndex == 0 && rowIndex > 0){
        QTableWidgetItem *widgetItem = item(rowIndex-1,1);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        //judgeTableContent(this,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq,false);
        emit contenJudge();

        sortAllItems();
        setCurrentCell(rowIndex-1,1);
        currentRowIndex = currentRow();
        currentColumnIndex = currentColumn();
    }
    else if(columnIndex == 1){
        QTableWidgetItem *widgetItem = item(rowIndex,0);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

       // judgeTableContent(this,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq,false);
        emit contenJudge();

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
void ClickableTableWidget::rightKeyProcess(void)
{
    QString strValue;

    blNumberInput = false;
    blFirstIn     = true;
    blDotInput    = false;
    bUpdateLimit  = false;

    int totalRow    = rowCount();
    int columnIndex = currentColumn();
    int rowIndex    = currentRow();
    if(columnIndex == 0){
        QTableWidgetItem *widgetItem = item(rowIndex,1);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        //judgeTableContent(this,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq,false);
        emit contenJudge();

        setCurrentCell(rowIndex,1);
        currentRowIndex = currentRow();
        currentColumnIndex = currentColumn();
    }
    else if(columnIndex == 1 && rowIndex + 1 < totalRow){
        QTableWidgetItem *widgetItem = item(rowIndex+1,0);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        //judgeTableContent(this,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq,false);
        emit contenJudge();

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
void ClickableTableWidget::upKeyProcess(void)
{
    QString strValue;

    blNumberInput = false;
    blFirstIn     = true;
    blDotInput    = false;
    bUpdateLimit  = false;

    int columnIndex = currentColumn();
    int rowIndex    = currentRow();
    if(rowIndex > 0){
        QTableWidgetItem *widgetItem = item(rowIndex-1,columnIndex);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

       // judgeTableContent(this,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
        emit contenJudge();

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
void ClickableTableWidget::downKeyProcess(void)
{
    QString strValue;

    blNumberInput = false;
    blFirstIn     = true;
    blDotInput    = false;
    bUpdateLimit  = false;

    int totalRow    = rowCount();
    int columnIndex = currentColumn();
    int rowIndex    = currentRow();
    if(totalRow <= 1) return;
    if(rowIndex < totalRow-1){
        QTableWidgetItem *widgetItem = item(rowIndex+1,columnIndex);
        strValue = QString("%1").arg(widgetItem->text());
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        //judgeTableContent(this,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
        emit contenJudge();

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
void ClickableTableWidget::dotKeyProcess(QString qShowStr, QTableWidgetItem *widgetItem)
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
void ClickableTableWidget::espKeyProcess(void)
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
void ClickableTableWidget::enterKeyProcess(void)
{
    char cTmpValue[20];
    memset(cTmpValue,0,sizeof(char)*20);

    blNumberInput       = false;
    blFirstIn           = true;
    blDotInput          = false;
    bUpdateLimit        = true;

    currentColumnIndex = currentColumn();
    currentRowIndex    = currentRow();

    //judgeTableContent(this,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
    emit contenJudge();

    sortAllItems();
    setCurrentCell(currentRowIndex,currentColumnIndex);
}
/**
* process minus key
* @param[in] string QString
* @param[in] widgetItem QTableWidgetItem
* @return    void
* @not
*/
void ClickableTableWidget::minusKeyProcess(QString qShowStr, QTableWidgetItem *widgetItem)
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
                    double DataNumber = atof(newDataString);
                    if(DataNumber>0){
                        for(int i = strlen(newDataString)-1;i>=0;i--){
                            newDataString[i+1] = newDataString[i];
                        }
                        newDataString[0] = '-';
                    }
                    else if(DataNumber<0){
                        for(int i = 0;i<strlen(newDataString);i++){
                            newDataString[i] = newDataString[i+1];
                        }
                    }
                }
                else{
                    int DataNumber = atoi(newDataString);
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
void ClickableTableWidget::backSpaceKeyProcess(QString qShowStr, QTableWidgetItem *widgetItem)
{
    int strLen = 0;
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
void ClickableTableWidget::keyPressEvent(QKeyEvent *event)
{
    QCoreApplication::sendEvent(mParent, event);
    return;
    //
    QString qShowStr;
    QTableWidgetItem *widgetItem;

    if(currentRowIndex != currentRow() || currentColumnIndex != currentColumn()) blFirstIn = true;

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
void ClickableTableWidget::judgeTableContent(QTableWidget *tableWidget, unsigned long long startFreq, unsigned long long stopFreq, bool bFlag)
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

    if(bFlag) {
        //Judge if it is neccesary to delete the dot who the same frequency
        for(int i = 1;i<tableWidget->rowCount();i++) {
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

            if(0 == atof(currFrqValue) - atof(FreqValue)&& 0 == atof(currAmpValue) - atof(AmpValue)) {
                tableWidget->removeRow(0);
                break;
            }
        }
    }


    //Judge Frequency
    for(int i = 0;i<tableWidget->rowCount();i++) {
        memset(cTmpValue,0,sizeof(char)*20);
        memset(cItemValue,0,sizeof(cItemValue));

        //Freq
        tableWidgetItem = tableWidget->item(i,0);
        strValue = tableWidgetItem->text();
        qsnprintf(cItemValue,sizeof(cItemValue),"%s",strValue.toUtf8().constData());

        if(atof(cItemValue)*1000000 < startFreq) {
            sprintf(cTmpValue,"%.2f",startFreq/1000000.);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            tableWidget->setItem(i,0,tableWidgetItem);
        }
        else if(atof(cItemValue)*1000000 > stopFreq) {
            sprintf(cTmpValue,"%.2f",stopFreq/1000000.);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            tableWidget->setItem(i,0,tableWidgetItem);
        }

        // Judge Amplitude
        tableWidgetItem = tableWidget->item(i,1);
        strValue = tableWidgetItem->text();
        qsnprintf(cItemValue,sizeof(cItemValue),"%s",strValue.toUtf8().constData());

        if(atof(cItemValue) - TABLEWIDGET_AMP_MIN< 0.) {
            sprintf(cTmpValue,"%.2f",TABLEWIDGET_AMP_MIN);
            strValue = QString("%1").arg(cTmpValue);
            tableWidgetItem = new QTableWidgetItem(strValue);
            tableWidget->setItem(i,1,tableWidgetItem);
        }
        else if(atof(cItemValue) - TABLEWIDGET_AMP_MAX > 0.) {
            sprintf(cTmpValue,"%.2f",TABLEWIDGET_AMP_MAX);
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
/*
void ClickableTableWidget::mousePressEvent(QMouseEvent *event)
{
    QTableWidgetItem *tableItem = itemAt(event->x(),event->y());
    int currentMousePressRow = row(tableItem);
    int currentMousePressColumn = column(tableItem);
    if(currentRowIndex != currentMousePressRow) {
        sortAllItems();
        setCurrentCell(currentMousePressRow,currentMousePressColumn);

        blNumberInput = false;
        blFirstIn     = true;
        blDotInput    = false;
        currentRowIndex = currentMousePressRow;
        currentColumnIndex = currentMousePressColumn;

        //judgeTableContent(this,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
        emit contenJudge();
    }
    else if(currentColumnIndex != currentMousePressColumn){
        setCurrentCell(currentMousePressRow,currentMousePressColumn);

        blNumberInput = false;
        blFirstIn     = true;
        blDotInput    = false;
        currentRowIndex = currentMousePressRow;
        currentColumnIndex = currentMousePressColumn;

        //judgeTableContent(this,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq,false);
        emit contenJudge();
    }
    return QWidget::mousePressEvent(event);
}
*/
/**
* process header clicked
* @param[in] column index
* @return    void
*/
void ClickableTableWidget::headerClicked(int index)
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
* sort all items in QTableWidget
* @param[in] viod
* @return    void
*/
void ClickableTableWidget::sortAllItems(void)
{
    QString strFreq,strAmplitude;
    QTableWidgetItem *widgetItem;

    memset(dFreq,0,sizeof(double)*1000);
    memset(dAmplitude,0,sizeof(double)*1000);

    //get All Items
    for(int i = 0;i<rowCount();i++){
        widgetItem = item(i,0);
        strFreq = widgetItem->text();
        dFreq[i] = strFreq.toDouble();

        widgetItem = item(i,1);
        strAmplitude = widgetItem->text();
        dAmplitude[i] = strAmplitude.toDouble();
    }

    //sort
    for(int i = 0;i<rowCount();i++){
        for(int j = i+1;j<rowCount();j++){
            if(dFreq[i] >= dFreq[j]){
                double tmp = 0.;
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
    int rowNum = rowCount();
    for(int i = rowNum-1;i>=0;i--){
        removeRow(i);
    }

    //reset All Item
    for(int i = 0;i<rowNum;i++){
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
/**
* get table conent
* @param[in] void
* @return    void
*/

#if 0
/**
* initialize tableWidget content
* @param[in] viod
* @return    void
*/
void ClickableTableWidget::initTableWidgetValue(void)
{
    QString strFreq;
    QString strAmplitude;

    int rowNum = rowCount();

    for(int i = rowNum-1;i>=0;i--){
        removeRow(i);
    }


    for(int i = 0;i<globalUserLimit->gTotalDot[globalUserLimit->gLimitSelect];i++){
        strFreq = QString::number(globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i],'f',2);
        QTableWidgetItem *freqItem = new QTableWidgetItem(strFreq);
        strAmplitude = QString::number(globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i],'f',2);
        QTableWidgetItem *amplitudeItem = new QTableWidgetItem(strAmplitude);

        insertRow(i);
        setItem(i,0,freqItem);
        setItem(i,1,amplitudeItem);
    }

    resetAllParam();
}


/**
* get table conent
* @param[in] void
* @return    void
*/
void ClickableTableWidget::getTableWidgetValue(void)
{
    QString strFreq,strAmplitude;
    QTableWidgetItem *widgetItem;
//    globalUserLimit
    if(!rowCount())
    {
        for(int i = 0;i<globalUserLimit->gTotalDot[globalUserLimit->gLimitSelect];i++)
        {
            globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i] = 0.;
            globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i] = 0.;

            globalUserLimit->limitXAxisCalculatorFunc((unsigned long long)(globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i]*SA_MHZ),i,globalUserLimit->gLimitSelect);
            globalUserLimit->LatestLimitYAxisCalculatorFunc(globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i],i,globalUserLimit->gLimitSelect);
        }
        globalUserLimit->gTotalDot[globalUserLimit->gLimitSelect] = 0;
    }
    else {
        globalUserLimit->gTotalDot[globalUserLimit->gLimitSelect] = rowCount();
        for(int i = 0;i<rowCount();i++){
            widgetItem = item(i,0);
            strFreq = widgetItem->text();
            globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i] = strFreq.toDouble();

            widgetItem = item(i,1);
            strAmplitude = widgetItem->text();
            globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i] = strAmplitude.toDouble();
      }

        //sort
        for(int i = 0;i<rowCount();i++){
            for(int j = i+1;j<rowCount();j++){
                if(globalUserLimit->gFreq[globalUserLimit->gLimitSelect][i]>globalUserLimit->gFreq[globalUserLimit->gLimitSelect][j]){
                    double tmp = 0.;
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
#endif
void ClickableTableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    return QTableWidget::mouseReleaseEvent(event);//将该事件传给父类处理;
}
