/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                sa_tablerefresh_control.cpp
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2019/03/01
** Descriptions:             used to realize the table refresh of marker,SA_ACP,channel power ,Multi SA_ACP and occupied XdB
**
*********************************************************************************************************/

#include "bitsa.h"
#include "ui_bitsa.h"


/**
 * @brief BitSA::slotOperateTable
 * @note  SLOT
 */
void BitSA::slotOperateTable()
{
    initMenuWidget();

    emit MesPlatTitleSig(m_user_variable->currentMode);

    //*******Johnson 190530
#if 1
    refreshMeasure(SA_INFO_MEASURE);
#else
    initInfo();
#endif
    refreshMkrTable();
}

/**
 * @brief BitSA::refreshMkrTable
 * @param
 * @note refresh buttom table
 */
#include <QDebug>
void BitSA::refreshMkrTable()
{
    if(m_user_variable->currentMode == SA_SPAN_MODE || FullStatus)
    {
        /*
        SA_guiDrawSet.markerOnCount = 0;
        for (qint32 i = 0; i < MARKER_TOTAL_CNT; i++)
        {
            if (m_user_variable->gMarkerView[i] == SA_ON)
                ++SA_guiDrawSet.markerOnCount ;
        }
        */
        if(SA_guiDrawSet.markerOnCount > 0)
        {
            pBitSA->buttomMarker->show();
        }
        pACPTable->hide();
        pChannelPowerTable->hide();
        pMarkerTable->hide();
        pOccupiedXdBTable->hide();
        pMultiACPTable->hide();
        pSpectrumEMTable->hide();
        pSpuriousEMTable->hide();

        pControlACPTable->hide();
        pControlChannelPowerTable->hide();
        pControlpOccupiedXdBTable->hide();
        pControlMarkerTable->hide();
        pControlMultiACPTable->hide();
        pControlSpectrumEMTable->hide();
        pControlSpuriousEMTable->hide();
    }
    else
    {
        pBitSA->buttomMarker->hide();
        if(m_user_variable->currentMode == SA_ACP_MEASURE_MODE)
        {
            pACPTable->show();
            pChannelPowerTable->hide();
            pOccupiedXdBTable->hide();
            pMultiACPTable->hide();
            pSpectrumEMTable->hide();
            pSpuriousEMTable->hide();

            pControlACPTable->show();
            pControlChannelPowerTable->hide();
            pControlpOccupiedXdBTable->hide();
            pControlMultiACPTable->hide();
            pControlSpectrumEMTable->hide();
            pControlSpuriousEMTable->hide();
        }
        else if(m_user_variable->currentMode == SA_CHNLPOWER_MEASURE_MODE)
        {
            pChannelPowerTable->show();
            pACPTable->hide();
            pOccupiedXdBTable->hide();
            pMultiACPTable->hide();
            pSpectrumEMTable->hide();
            pSpuriousEMTable->hide();

            pControlChannelPowerTable->show();
            pControlACPTable->hide();
            pControlpOccupiedXdBTable->hide();
            pControlMultiACPTable->hide();
            pControlSpectrumEMTable->hide();
            pControlSpuriousEMTable->hide();
        }
        else if(m_user_variable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE)
        {
            pOccupiedXdBTable->show();
            pACPTable->hide();
            pChannelPowerTable->hide();
            pMultiACPTable->hide();
            pSpectrumEMTable->hide();
            pSpuriousEMTable->hide();

            pControlpOccupiedXdBTable->show();
            pControlACPTable->hide();
            pControlChannelPowerTable->hide();
            pControlMultiACPTable->hide();
            pControlSpectrumEMTable->hide();
            pControlSpuriousEMTable->hide();
        }
        else if(m_user_variable->currentMode == SA_MULTI_ACP_MODE)
        {
            pMultiACPTable->show();
            pACPTable->hide();
            pChannelPowerTable->hide();
            pOccupiedXdBTable->hide();
            pSpectrumEMTable->hide();
            pSpuriousEMTable->hide();

            pControlMultiACPTable->show();
            pControlACPTable->hide();
            pControlChannelPowerTable->hide();
            pControlpOccupiedXdBTable->hide();
            pControlSpectrumEMTable->hide();
            pControlSpuriousEMTable->hide();
        }else if(m_user_variable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
        {
            pSpectrumEMTable->show();
            pACPTable->hide();
            pChannelPowerTable->hide();
            pOccupiedXdBTable->hide();
            pMultiACPTable->hide();
            pSpuriousEMTable->hide();

            pControlSpectrumEMTable->show();
            pControlACPTable->hide();
            pControlChannelPowerTable->hide();
            pControlpOccupiedXdBTable->hide();
            pControlMultiACPTable->hide();
            pControlSpuriousEMTable->hide();
        }else if(m_user_variable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {
            pACPTable->hide();
            pChannelPowerTable->hide();
            pOccupiedXdBTable->hide();
            pMultiACPTable->hide();
            pSpectrumEMTable->hide();
            pSpuriousEMTable->show();

            pControlACPTable->hide();
            pControlChannelPowerTable->hide();
            pControlpOccupiedXdBTable->hide();
            pControlMultiACPTable->hide();
            pControlSpectrumEMTable->hide();
            pControlSpuriousEMTable->show();
        }

        if(m_user_variable->gMarkerDisplay == MKR_TABLE)
        {
            pMarkerTable->show();
            pControlMarkerTable->show();
        }
        else
        {
            pMarkerTable->hide();
            pControlMarkerTable->hide();
        }
    }

    setTablePosition();
    /*repaint();*/
}


/**
 * @brief BitSA::slotHideTable
 * @param tableID
 * @note SLOT
 */
void BitSA::slotHideTable(quint32 tableID)
{
    switch(tableID)
    {
    case SA_MARKER_TABLE:       pMarkerTable->hide();       break;
    case SA_ACP_TABLE:          pACPTable->hide();          break;
    case SA_CHANNELPOWER_TABLE: pChannelPowerTable->hide(); break;
    case SA_OCCUPIEDXDB_TABLE:  pOccupiedXdBTable->hide();  break;
    case SA_MULTIACP_TABLE:     pMultiACPTable->hide();     break;
    case SA_SPECTRUM_EM_TABLE:  pSpectrumEMTable->hide();     break;
    case SA_SPURIOUS_EM_TABLE:  pSpuriousEMTable->hide();     break;
    default: break;
    }

    setTablePosition();
}

/**
 * @brief BitSA::bottomInfoShow
 * @note control table show
 */
void BitSA::bottomInfoShow()
{
#if 0
    qint32 widgetTableStartX = 0;
    qint32 widgetTableStartY = 0;
    qint32 widgetTableWidth  = 0;
    qint32 widgetTableHeight = 0;
    if(m_user_variable->currentMode == SA_SPAN_MODE || FullStatus)
    {
        //if(m_user_variable->lastMode == m_user_variable->currentMode) return;
        adjustRect();//central area must refresh before table widget show or hide,otherwise it will blink.

        bottomInfoClose();
        bottomInfoMarkerClose();
    }
    else
    {
        pBitSA->buttomMarker->hide();

        if(m_user_variable->lastMode != m_user_variable->currentMode ||
           (!pBottomInfoMarker && m_user_variable->gMarkerDisplay == MKR_TABLE))
        {
            adjustRect();//central area must refresh before table widget show or hide,otherwise it will blink.

            bottomInfoClose();
            bottomInfoMarkerClose();
        }

        if(!pBottomInfoWidget)
        {
            switch(m_user_variable->currentMode)
            {
            case  SA_CHNLPOWER_MEASURE_MODE:
                bottomInfoClose();
                pBottomInfoWidget = new sa_widget_ChannelPowerTable(*m_user_variable,*globalUserLimit,this);
#if 0
                widgetTableStartY = NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY + CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT;
                widgetTableHeight = CHANNELPOWER_TABLE_HEIGHT;

                if(pBitSA->pb_left_hide->isChecked())//hide the left area
                {
                    widgetTableStartX = NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX;
                    widgetTableWidth  = LEFTWIDGET_HIDE_TABLE_WIDTH;
                }
                else//show the left area
                {
                    widgetTableStartX = NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX;
                    widgetTableWidth  = LEFTWIDGET_SHOW_TABLE_WIDTH;
                }
#else
                if(m_user_variable->gMarkerDisplay == MKR_TABLE)
                {
                    widgetTableStartX = CenterDrawRect.x();
                    widgetTableStartY = CenterDrawRect.y() + CenterDrawRect.height() + MARKER_TABLE_HEIGHT;
                    widgetTableHeight = CHANNELPOWER_TABLE_HEIGHT;
                    widgetTableWidth  = CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH;
                }
                else
                {
                    widgetTableStartX = CenterDrawRect.x();
                    widgetTableStartY = CenterDrawRect.y() + CenterDrawRect.height();
                    widgetTableHeight = CHANNELPOWER_TABLE_HEIGHT;
                    widgetTableWidth  = CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH;
                }
#endif
                pBottomInfoWidget->setGeometry(widgetTableStartX,widgetTableStartY,widgetTableWidth,widgetTableHeight);
                ((sa_widget_ChannelPowerTable *)pBottomInfoWidget)->setPixmapSize(widgetTableWidth,widgetTableHeight);
                break;
            case  SA_ACP_MEASURE_MODE:
                bottomInfoClose();
                pBottomInfoWidget = new sa_widget_ACPTable(*m_user_variable,*globalUserLimit,this);
                pBottomInfoControlWidget = new sa_ControlWidget_ACPTable(*m_user_variable,this);
#if 0
                widgetTableStartY = NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY + ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT;
                widgetTableHeight = ACP_TABLE_HEIGHT;

                if(pBitSA->pb_left_hide->isChecked())//hide the left area
                {
                    widgetTableStartX = NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX;
                    widgetTableWidth  = LEFTWIDGET_HIDE_TABLE_WIDTH;
                }
                else//show the left area
                {
                    widgetTableStartX = NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX;
                    widgetTableWidth  = LEFTWIDGET_SHOW_TABLE_WIDTH;
                }
#else
                if(m_user_variable->gMarkerDisplay == MKR_TABLE)
                {setAttribute(Qt::WA_DeleteOnClose);
                    setAttribute(Qt::WA_TranslucentBackground, true);
                    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
                    widgetTableStartX = CenterDrawRect.x();
                    widgetTableStartY = CenterDrawRect.y() + CenterDrawRect.height() + MARKER_TABLE_HEIGHT;
                    widgetTableHeight = ACP_TABLE_HEIGHT;
                    widgetTableWidth  = CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH;
                }
                else
                {
                    widgetTableStartX = CenterDrawRect.x();
                    widgetTableStartY = CenterDrawRect.y() + CenterDrawRect.height();
                    widgetTableHeight = ACP_TABLE_HEIGHT;
                    widgetTableWidth  = CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH;
                }
#endif

                pBottomInfoWidget->setGeometry(widgetTableStartX,widgetTableStartY,widgetTableWidth,widgetTableHeight);
                pBottomInfoControlWidget->setGeometry(widgetTableStartX + widgetTableWidth,widgetTableStartY,
                                                      RIGHT_CONTROLWIDGET_WIDTH,widgetTableHeight);
                ((sa_widget_ACPTable *)pBottomInfoWidget)->setPixmapSize(widgetTableWidth,widgetTableHeight);
                break;
            case  SA_OCCUPIED_BW_MEASURE_MODE:
                bottomInfoClose();
                pBottomInfoWidget = new sa_widget_OccupiedXdBTable(*m_user_variable,*globalUserLimit,this);

#if 0
                widgetTableStartY = NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY + OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT;
                widgetTableHeight = OCCUPIED_TABLE_HEIGHT;

                if(pBitSA->pb_left_hide->isChecked())//hide the left area
                {
                    widgetTableStartX = NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX;
                    widgetTableWidth  = LEFTWIDGET_HIDE_TABLE_WIDTH;
                }
                else//show the left area
                {
                    widgetTableStartX = NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX;
                    widgetTableWidth  = LEFTWIDGET_SHOW_TABLE_WIDTH;
                }
#else
                if(m_user_variable->gMarkerDisplay == MKR_TABLE)
                {
                    widgetTableStartX = CenterDrawRect.x();
                    widgetTableStartY = CenterDrawRect.y() + CenterDrawRect.height() + MARKER_TABLE_HEIGHT;
                    widgetTableHeight = OCCUPIED_TABLE_HEIGHT;
                    widgetTableWidth  = CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH;
                }
                else
                {
                    widgetTableStartX = CenterDrawRect.x();
                    widgetTableStartY = CenterDrawRect.y() + CenterDrawRect.height();
                    widgetTableHeight = OCCUPIED_TABLE_HEIGHT;
                    widgetTableWidth  = CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH;
                }
#endif

                pBottomInfoWidget->setGeometry(widgetTableStartX,widgetTableStartY,widgetTableWidth,widgetTableHeight);
                ((sa_widget_OccupiedXdBTable *)pBottomInfoWidget)->setPixmapSize(widgetTableWidth,widgetTableHeight);
                break;
            default:
                return;
                break;
            }
            if(pBottomInfoWidget) pBottomInfoWidget->show();
            if(pBottomInfoControlWidget)
            {
                connect(pBottomInfoControlWidget,SIGNAL(destroyed()),this,SLOT(on_bottomInfoDestroyed()));
                pBottomInfoControlWidget->show();
            }
        }

        if(pBottomInfoWidget)
        {
            switch(m_user_variable->currentMode)
            {
            case SA_CHNLPOWER_MEASURE_MODE:
                ((sa_widget_ChannelPowerTable *)pBottomInfoWidget)->refreshChannelPowerTable();
                break;
            case SA_ACP_MEASURE_MODE:
                ((sa_widget_ACPTable *)pBottomInfoWidget)->refreshAcpTable();
                break;
            case SA_OCCUPIED_BW_MEASURE_MODE:
                ((sa_widget_OccupiedXdBTable *)pBottomInfoWidget)->refreshOccupiedXdBTable();
                break;
            }
        }

        if(!pBottomInfoMarker && m_user_variable->gMarkerDisplay == MKR_TABLE)
        {
            bottomInfoMarker();
        }
        if(pBottomInfoMarker)
            ((sa_widget_markerTable *)pBottomInfoMarker)->refreshMarkerTable();
    }

    m_user_variable->lastMode = m_user_variable->currentMode;
#else
    /*bool bHideLeftArea = false;
    //hide the left area
    if(pBitSA->pb_left_hide->isChecked()) bHideLeftArea = true;
    else bHideLeftArea = false;*/

    if(!pACPTable->isHidden()) pACPTable->refreshAcpTable();
    else if(!pChannelPowerTable->isHidden()) pChannelPowerTable->refreshChannelPowerTable();
    else if(!pOccupiedXdBTable->isHidden()) pOccupiedXdBTable->refreshOccupiedXdBTable();
    else if(!pMultiACPTable->isHidden()) pMultiACPTable->refreshMultiAcpTable();
    else if(!pSpectrumEMTable->isHidden())
    {
        if( m_user_variable->gMsComplete /*|| m_user_variable->gMsFirstFlag*/)
            pSpectrumEMTable->refreshSpectrumEMTable();
    }
    else if(!pSpuriousEMTable->isHidden())
    {
        if(m_user_variable->gMeasureStatus == SA_OFF)
        {
            pSpuriousEMTable->refreshSpuriousEMTable();
        }else
        {
        if( m_user_variable->gMsComplete /*|| m_user_variable->gMsFirstFlag*/)
            pSpuriousEMTable->refreshSpuriousEMTable();
    }
    }
    if(!pMarkerTable->isHidden()) pMarkerTable->refreshMarkerTable();
#endif
}

/**
 * @brief BitSA::setTablePosition
 * @note set the table position of marker,acp,channel power and occupied XdB
 */
void BitSA::setTablePosition()
{
    qint32 widgetTableStartX = 0;
    qint32 widgetTableStartY = 0;
    qint32 widgetTableWidth  = 0;
    qint32 widgetTableHeight = 0;

    adjustRect();//central area must refresh before table widget show or hide,otherwise it will blink.

    if(m_user_variable->gMarkerDisplay == MKR_TABLE && !pMarkerTable->isHidden())
        widgetTableStartY = CenterDrawRect.y() + CenterDrawRect.height() + MARKER_TABLE_HEIGHT;
    else
        widgetTableStartY = CenterDrawRect.y() + CenterDrawRect.height();

    widgetTableStartX = CenterDrawRect.x();
    widgetTableWidth  = CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH;

    if(!pACPTable->isHidden())
    {
        widgetTableHeight = ACP_TABLE_HEIGHT;

        pACPTable->setGeometry(widgetTableStartX,widgetTableStartY,widgetTableWidth,widgetTableHeight);
        pACPTable->setPixmapSize(widgetTableWidth,widgetTableHeight);

        pControlACPTable->setGeometry(widgetTableStartX + widgetTableWidth,widgetTableStartY,
                                              RIGHT_CONTROLWIDGET_WIDTH,widgetTableHeight);
    }
    else if(!pChannelPowerTable->isHidden())
    {
        widgetTableHeight = CHANNELPOWER_TABLE_HEIGHT;

        pChannelPowerTable->setGeometry(widgetTableStartX,widgetTableStartY,widgetTableWidth,widgetTableHeight);
        pChannelPowerTable->setPixmapSize(widgetTableWidth,widgetTableHeight);

        pControlChannelPowerTable->setGeometry(widgetTableStartX + widgetTableWidth,widgetTableStartY,
                                              RIGHT_CONTROLWIDGET_WIDTH,widgetTableHeight);
    }
    else if(!pOccupiedXdBTable->isHidden())
    {
        widgetTableHeight = OCCUPIED_TABLE_HEIGHT;

        pOccupiedXdBTable->setGeometry(widgetTableStartX,widgetTableStartY,widgetTableWidth,widgetTableHeight);
        pOccupiedXdBTable->setPixmapSize(widgetTableWidth,widgetTableHeight);


        pControlpOccupiedXdBTable->setGeometry(widgetTableStartX + widgetTableWidth,widgetTableStartY,
                                              RIGHT_CONTROLWIDGET_WIDTH,widgetTableHeight);
    }
    else if(!pMultiACPTable->isHidden())
    {
        widgetTableHeight = MULTIACP_TABLE_HEIGHT;

        pMultiACPTable->setGeometry(widgetTableStartX,widgetTableStartY,widgetTableWidth,widgetTableHeight);
        pMultiACPTable->setPixmapSize(widgetTableWidth,widgetTableHeight);


        pControlMultiACPTable->setGeometry(widgetTableStartX + widgetTableWidth,widgetTableStartY,
                                              RIGHT_CONTROLWIDGET_WIDTH,widgetTableHeight);
    }else if(!pSpectrumEMTable->isHidden())
    {
        widgetTableHeight = SPECEM_TABLE_HEIGHT;

        pSpectrumEMTable->setGeometry(widgetTableStartX,widgetTableStartY,widgetTableWidth,widgetTableHeight);
        pSpectrumEMTable->setPixmapSize(widgetTableWidth,widgetTableHeight);


        pControlSpectrumEMTable->setGeometry(widgetTableStartX + widgetTableWidth,widgetTableStartY,
                                              RIGHT_CONTROLWIDGET_WIDTH,widgetTableHeight);
    }else if(!pSpuriousEMTable->isHidden())
    {
        widgetTableHeight = SPECEM_TABLE_HEIGHT;

        pSpuriousEMTable->setGeometry(widgetTableStartX,widgetTableStartY,widgetTableWidth,widgetTableHeight);
        pSpuriousEMTable->setPixmapSize(widgetTableWidth,widgetTableHeight);


        pControlSpuriousEMTable->setGeometry(widgetTableStartX + widgetTableWidth,widgetTableStartY,
                                              RIGHT_CONTROLWIDGET_WIDTH,widgetTableHeight);
    }

    if(!pMarkerTable->isHidden())
    {
        pMarkerTable->setGeometry(CenterDrawRect.x(),CenterDrawRect.y() + CenterDrawRect.height(),
                                       CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,MARKER_TABLE_HEIGHT);
        pMarkerTable->setPixmapSize(CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,MARKER_TABLE_HEIGHT);

        pControlMarkerTable->setGeometry(CenterDrawRect.x() + CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,
                                         CenterDrawRect.y() + CenterDrawRect.height(),RIGHT_CONTROLWIDGET_WIDTH,MARKER_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::bottomInfoClose
 */
void BitSA::bottomInfoClose()
{
    if(pBottomInfoWidget)
    {
        disconnect(pBottomInfoControlWidget,SIGNAL(destroyed()),this,SLOT(on_bottomInfoDestroyed()));
        delete pBottomInfoWidget;
        pBottomInfoWidget = NULL;
        delete pBottomInfoControlWidget;
        pBottomInfoControlWidget = NULL;

        //m_user_variable->currentMode = SA_SPAN_MODE;
    }
}

/**
 * @brief BitSA::on_bottomInfoDestroyed
 */
void BitSA::on_bottomInfoDestroyed()
{
    if(pBottomInfoWidget)
    {
        pBottomInfoWidget->hide();
        pBottomInfoControlWidget->hide();

        /*disconnect(pBottomInfoControlWidget,SIGNAL(destroyed()),this,SLOT(on_bottomInfoDestroyed()));
        delete pBottomInfoWidget;
        pBottomInfoWidget = NULL;
        pBottomInfoControlWidget = NULL;*/

        //m_user_variable->currentMode = SA_SPAN_MODE;
    }
}

/**
 * @brief BitSA::bottomInfoMarker
 */
void BitSA::bottomInfoMarker()
{
   if(!pBottomInfoMarker)
    {
        bottomInfoMarkerClose();
        pBottomInfoMarker = new sa_widget_markerTable(*pcontrolInterface,*m_user_variable,*globalUserLimit,this);
#if 0
        if(pBitSA->pb_left_hide->isChecked())//hide the left area
        {
            pBottomInfoMarker->setGeometry(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,
                                           NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY + CHANNELPOWER_MARKERTABLE_SHOW_CENTERAREA_HEIGHT,
                                           LEFTWIDGET_HIDE_TABLE_WIDTH,MARKER_TABLE_HEIGHT);
            ((sa_widget_markerTable *)pBottomInfoMarker)->setPixmapSize(LEFTWIDGET_HIDE_TABLE_WIDTH - TABLEWIDGET_RIGHTMARGIN,
                                                                        MARKER_TABLE_HEIGHT);
        }
        else//show the left area
        {
            pBottomInfoMarker->setGeometry(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,
                                           NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY + CHANNELPOWER_MARKERTABLE_SHOW_CENTERAREA_HEIGHT,
                                           LEFTWIDGET_SHOW_TABLE_WIDTH,MARKER_TABLE_HEIGHT);
            ((sa_widget_markerTable *)pBottomInfoMarker)->setPixmapSize(LEFTWIDGET_SHOW_TABLE_WIDTH - TABLEWIDGET_RIGHTMARGIN,MARKER_TABLE_HEIGHT);
        }
#else
        pBottomInfoMarker->setGeometry(CenterDrawRect.x(),CenterDrawRect.y() + CenterDrawRect.height(),
                                       CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,MARKER_TABLE_HEIGHT);
        ((sa_widget_markerTable *)pBottomInfoMarker)->setPixmapSize(CenterDrawRect.width() - RIGHT_CONTROLWIDGET_WIDTH,MARKER_TABLE_HEIGHT);
#endif
        connect(pBottomInfoMarker,SIGNAL(destroyed()),this,SLOT(on_bottomInfoMarkerDestroyed()));
        pBottomInfoMarker->show();
    }
}

/**
 * @brief BitSA::bottomInfoMarkerClose
 */
void BitSA::bottomInfoMarkerClose()
{
    if(pBottomInfoMarker)
    {
        disconnect(pBottomInfoMarker,SIGNAL(destroyed()),this,SLOT(on_bottomInfoMarkerDestroyed()));
        delete pBottomInfoMarker;
        pBottomInfoMarker = NULL;

        //m_user_variable->gMarkerDisplay = MKR_ONLY;
    }
}

/**
 * @brief BitSA::on_bottomInfoMarkerDestroyed
 */
void BitSA::on_bottomInfoMarkerDestroyed()
{
    if(pBottomInfoMarker)
    {
        disconnect(pBottomInfoMarker,SIGNAL(destroyed()),this,SLOT(on_bottomInfoMarkerDestroyed()));
        pBottomInfoMarker = NULL;

        m_user_variable->gMarkerDisplay = MKR_ONLY;
    }
}

/**
 * @brief BitSA::setCenterRect
 * @param x
 * @param y
 * @param w
 * @param h
 */
void BitSA::setCenterRect(qint32 x,qint32 y,qint32 w,qint32 h)
{
    CenterDrawRect.setRect(x,y,w,h);
    psa_UIRefresh_Control->setPixmapSize(w,h);
    return;
}

/**
 * @brief BitSA::setCenterRect_pbLeftShow_ChnlPowerMode
 * @note set central area rectangle when the left widget is show and the measure is channel power
 */
void BitSA::setCenterRect_pbLeftShow_ChnlPowerMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pChannelPowerTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,CHANNELPOWER_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                              CHANNELPOWER_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + CHANNELPOWER_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                              CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + CHANNELPOWER_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pChannelPowerTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                          CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + CHANNELPOWER_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftShow_ACPMode
 * @note set central area rectangle when the left widget is show and the measure is SA_ACP
 */
void BitSA::setCenterRect_pbLeftShow_ACPMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pACPTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,ACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,ACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + ACP_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + ACP_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pACPTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + ACP_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftShow_MultiACPMode
 * @note set central area rectangle when the left widget is show and the measure is Multi SA_ACP
 */
void BitSA::setCenterRect_pbLeftShow_MultiACPMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pMultiACPTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + MULTIACP_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + MULTIACP_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pMultiACPTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + MULTIACP_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftHide_SpectrumEMMode
 * @note set central area rectangle when the left widget is hide and the measure is spectrum emission mask
 */
void BitSA::setCenterRect_pbLeftHide_SpectrumEMMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pSpectrumEMTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,SPECEM_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,SPECEM_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                              SPECEM_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + SPECEM_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                              SPECEM_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + SPECEM_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pSpectrumEMTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,SPECEM_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                          SPECEM_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + SPECEM_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftShow_SpectrumEMMode
 * @note set central area rectangle when the left widget is show and the measure is spectrum emission mask
 */
void BitSA::setCenterRect_pbLeftShow_SpectrumEMMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pSpectrumEMTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,SPECEM_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,SPECEM_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                              SPECEM_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + SPECEM_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                              SPECEM_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + SPECEM_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pSpectrumEMTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,SPECEM_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                          SPECEM_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + SPECEM_TABLE_HEIGHT);
    }
}



/**
 * @brief BitSA::setCenterRect_pbLeftHide_SpuriousEMMode
 * @note set central area rectangle when the left widget is hide and the measure is spectrum emission mask
 */
void BitSA::setCenterRect_pbLeftHide_SpuriousEMMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pSpuriousEMTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,SPUR_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,SPUR_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                              SPUR_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + SPECEM_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                              SPUR_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + SPECEM_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pSpuriousEMTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,SPUR_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                          SPUR_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + SPECEM_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftShow_SpuriousEMMode
 * @note set central area rectangle when the left widget is show and the measure is spectrum emission mask
 */
void BitSA::setCenterRect_pbLeftShow_SpuriousEMMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pSpuriousEMTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,SPUR_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,SPUR_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                              SPUR_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + SPUR_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                              SPUR_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + SPUR_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pSpuriousEMTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,SPUR_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                          SPUR_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + SPUR_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftShow_OccuXdBMode
 * @note set central area rectangle when the left widget is show and the measure is Occupied XdB
 */
void BitSA::setCenterRect_pbLeftShow_OccuXdBMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pOccupiedXdBTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,OCCUPIEDBW_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                              OCCUPIEDBW_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + OCCUPIED_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                              OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + OCCUPIED_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pOccupiedXdBTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,
                          OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + OCCUPIED_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftHide_ChnlPowerMode
 * @note set central area rectangle when the left widget is hide and the measure is channel power
 */
void BitSA::setCenterRect_pbLeftHide_ChnlPowerMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pChannelPowerTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,CHANNELPOWER_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                              CHANNELPOWER_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + CHANNELPOWER_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                              CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + CHANNELPOWER_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pChannelPowerTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                          CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + CHANNELPOWER_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftHide_ACPMode
 * @note set central area rectangle when the left widget is hide and the measure is SA_ACP
 */
void BitSA::setCenterRect_pbLeftHide_ACPMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pACPTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,ACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,ACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + ACP_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + ACP_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pACPTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + ACP_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftHide_OccuXdBMode
 * @note set central area rectangle when the left widget is hide and the measure is Occupied XdB
 */
void BitSA::setCenterRect_pbLeftHide_OccuXdBMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pOccupiedXdBTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,OCCUPIEDBW_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                              OCCUPIEDBW_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + OCCUPIED_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                              OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + OCCUPIED_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pOccupiedXdBTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,
                          OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + OCCUPIED_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::setCenterRect_pbLeftHide_MultiACPMode
 * @note set central area rectangle when the left widget is hide and the measure is Multi SA_ACP
 */
void BitSA::setCenterRect_pbLeftHide_MultiACPMode()
{
    if(m_user_variable->gMarkerDisplay == MKR_TABLE)
    {
        if(!pMultiACPTable->isHidden())
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
            }
        }
        else
        {
            if(!pMarkerTable->isHidden())
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT + MULTIACP_TABLE_HEIGHT);
            }
            else
            {
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + MULTIACP_TABLE_HEIGHT);
            }
        }
    }
    else
    {
        if(!pMultiACPTable->isHidden())
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
        else
            setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                          NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,MULTIACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT + MULTIACP_TABLE_HEIGHT);
    }
}

/**
 * @brief BitSA::adjustRect
 * @note adjust central area rectangle
 */
void BitSA::adjustRect()
{
    //Tony 190802 M
    /*
    if(m_user_variable->PrimaryAction == SA_MARKER_TAB && mSetupDialog)
    {
        showMarkerTableIcon(SA_ON);
    }
    */
    if(FullStatus) // Full Screen
    {
        this->setGeometry(0,0,1280,765);
        pBitSA->topButtonBar->hide();
        pBitSA->leftWidget->hide();
        //pBitSA->buttomMarker->hide();
        pBitSA->rightButtonBar->setGeometry(FULLSCREEN_RIGHTBUTTONBAR_STARTX,FULLSCREEN_RIGHTBUTTONBAR_STARTY,
                                            FULLSCREEN_RIGHTBUTTONBAR_WIDTH,FULLSCREEN_RIGHTBUTTONBAR_HEIGHT);
        if(pBitSA->buttomMarker->isHidden())
        {
            setCenterRect(FULLSCREEN_CENTERAREA_STARTX,FULLSCREEN_CENTERAREA_STARTY,
                          FULLSCREEN_CENTERAREA_WIDTH,FULLSCREEN_CENTERAREA_HEIGHT);
            pBitSA->buttomMarker->setGeometry(255,641,942,72);

        }
        else
        {
            setCenterRect(0,0,1198,694);
            pBitSA->buttomMarker->setGeometry(1,693,1196,72);
            //Tony 190802 M
            // showMarkerTableIcon(SA_OFF);
        }
    }
    else
    {
        this->setGeometry(1,52,1278,713);

        pBitSA->topButtonBar->show();
        pBitSA->leftWidget->show();
        pBitSA->rightButtonBar->setGeometry(NOTFULLSCREEN_RIGHTBUTTONBAR_STARTX,NOTFULLSCREEN_RIGHTBUTTONBAR_STARTY,
                                            NOTFULLSCREEN_RIGHTBUTTONBAR_WIDTH,NOTFULLSCREEN_RIGHTBUTTONBAR_HEIGHT);
        if(pBitSA->pb_left_hide->isChecked())
        {
            pBitSA->leftWidget->setGeometry(1,65,20,648);
            pBitSA->leftInfoWidget->hide();

            if(!pBitSA->buttomMarker->isHidden())
            {
                pBitSA->buttomMarker->setGeometry(1,641,1196,72);
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,SA_SPAN_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                if(m_user_variable->currentMode == SA_SPAN_MODE)
                {
                    setCenterRect(NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY,
                                  NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH,SA_SPAN_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
                }
                else
                {
                    if(m_user_variable->currentMode == SA_CHNLPOWER_MEASURE_MODE)
                    {
                        setCenterRect_pbLeftHide_ChnlPowerMode();
                    }
                    else if(m_user_variable->currentMode == SA_ACP_MEASURE_MODE)
                    {
                        setCenterRect_pbLeftHide_ACPMode();
                    }
                    else if(m_user_variable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE)
                    {
                        setCenterRect_pbLeftHide_OccuXdBMode();
                    }
                    else if(m_user_variable->currentMode == SA_MULTI_ACP_MODE)
                    {
                        setCenterRect_pbLeftHide_MultiACPMode();
                    }else if(m_user_variable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
                    {
                        setCenterRect_pbLeftHide_SpectrumEMMode();
                    }else if(m_user_variable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
                    {
                        setCenterRect_pbLeftHide_SpuriousEMMode();
                    }
                }
            }
        }
        else
        {
            pBitSA->leftWidget->setGeometry(1,65,274,648);
            pBitSA->leftInfoWidget->show();
            if(!pBitSA->buttomMarker->isHidden())
            {
                pBitSA->buttomMarker->setGeometry(255,641,942,72);
                setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                              NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,SA_SPAN_MARKERTABLE_SHOW_CENTERAREA_HEIGHT);
            }
            else
            {
                if(m_user_variable->currentMode == SA_SPAN_MODE)
                {
                    setCenterRect(NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX,NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY,
                                  NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH,SA_SPAN_MARKERTABLE_HIDE_CENTERAREA_HEIGHT);
                }
                else
                {
                    if(m_user_variable->currentMode == SA_CHNLPOWER_MEASURE_MODE)
                    {
                        setCenterRect_pbLeftShow_ChnlPowerMode();
                    }
                    else if(m_user_variable->currentMode == SA_ACP_MEASURE_MODE)
                    {
                        setCenterRect_pbLeftShow_ACPMode();
                    }
                    else if(m_user_variable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE)
                    {
                        setCenterRect_pbLeftShow_OccuXdBMode();
                    }
                    else if(m_user_variable->currentMode == SA_MULTI_ACP_MODE)
                    {
                        setCenterRect_pbLeftShow_MultiACPMode();
                    }else if(m_user_variable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
                    {
                        setCenterRect_pbLeftShow_SpectrumEMMode();
                    }else if(m_user_variable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
                    {
                        setCenterRect_pbLeftShow_SpuriousEMMode();
                    }
                }
            }
        }
    }

    if(pcontrolInterface->getSweepType() == SA_SINGLE || pcontrolInterface->getTraceType() == SA_VIEW)
    {
        psa_UIRefresh_Control->refreshPixmap();
        repaint(CenterDrawRect);
    }
}

