#include "sa_dialog_allsetup.h"
#include "ui_sa_dialog_allsetup.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"
#include "sa_dialog_ch_std.h"
#include "sa_dialog_warning.h"
SA_Dialog_AllSetup::SA_Dialog_AllSetup(controlInterface *interface, user_variable *puser_variable,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SA_Dialog_AllSetup)
{
    mControl = interface;
    globalUserVariable = puser_variable;
    initialPAction = globalUserVariable->PrimaryAction;

    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    mTrIndex = mControl->getTraceSelect();
    mInputDialog = NULL;
    mChannelInput = NULL;
    lastWidget = curWidget = 0;

    //setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint/*| Qt::Widget*/ | Qt::Dialog);
    ui->setupUi(this);

    initMap();
    //initWidget();
    initDisplay();
    this->hide();

}
void SA_Dialog_AllSetup::initWidget()
{
    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode)
    {
        ui->Freq_Center->setVisible(false);
        ui->Freq_Start->setVisible(false);
        ui->Freq_Stop->setVisible(false);
        ui->Span->setVisible(false);
        ui->Span_Full->setVisible(false);
        ui->Span_Zero->setVisible(false);
        ui->Span_Last->setVisible(false);
        ui->Channel_STD->setVisible(false);
        ui->Channel_Num->setVisible(false);
        ui->Channel_Step->setVisible(false);
        ui->Channel_Type->setVisible(false);
        ui->Atten->setVisible(false);
        ui->Atten_Value->setVisible(false);
        ui->Auto_SweepTime->setVisible(false);
        ui->Sweep_Time->setVisible(false);
        ui->RBW_Freq->setVisible(false);
        ui->RBW_Btn->setVisible(false);
        ui->VBW_Freq->setVisible(false);
        ui->VBW_Btn->setVisible(false);
        ui->VBW_RBW->setVisible(false);
        ui->Trace_Select->setVisible(false);
        ui->Trace_View->setVisible(false);
        ui->Trace_AllOn->setVisible(false);
        ui->Trace_Type->setVisible(false);
        ui->Trace_AllClear->setVisible(false);
        ui->Detectors->setVisible(false);
        ui->Marker_To->setVisible(false);
        ui->Limit_Select->setVisible(false);
        ui->Limit_Toggle->setVisible(false);
        ui->Limit_Edge_Toggle->setVisible(false);
        ui->Limit_Edge->setVisible(false);
        ui->Limit_Test->setVisible(false);
        ui->Limit_Type->setVisible(false);
        ui->Limit_AllClear->setVisible(false);
        ui->Freq_Count->setVisible(false);
        //Freq
        ui->line->setGeometry(121,60,137,3);
        ui->Freq_Step->move(119,66);
        ui->Freq_Offset->move(119,131);
        //Ampt
        ui->Title_Ampt->move(269,30);
        ui->line_4->move(269,61);
        ui->Auto_Scale->move(269,66);
        ui->Ref_Level->move(269,131);
        ui->Scale_Division->move(269,196);
        ui->Preamp->move(269,261);
        ui->Ref_Offset->move(269,326);
        ui->Scale_Unit->move(269,391);
        ui->value_Unit->setPopupPotion(SA_BOTTOM,-ui->value_Unit->x(),0);
        //Sweep
        ui->Title_Sweep->move(419,30);
        ui->line_6->move(419,61);
        ui->Sweep_Mode->move(419,66);
        ui->Sweep_Once->move(419,131);
        //BW
        ui->Title_Bw->move(569,30);
        ui->line_5->move(569,61);
        //Trigger
        ui->Title_Trigger->move(719,30);
        ui->line_3->move(719,61);
        ui->Trigger_Source->move(719,66);
        ui->Trigger_SubMenu->move(719,131);
        //Trace
        ui->Title_Trace->move(869,30);
        ui->line_2->move(869,61);
        ui->Average_Toggle->move(869,66); //Ave toggle
        ui->Average_Toggle->setVisible(true);

        ui->Average->move(869,131);

        //Marker
        ui->Title_Marker->setParent(ui->widget);
        ui->line_7->setParent(ui->widget);
        ui->Marker_Select->setParent(ui->widget);
        ui->Marker_View->setParent(ui->widget);
        ui->Marker_AllOn->setParent(ui->widget);
        ui->Marker_Type->setParent(ui->widget);
        ui->Noise_Marker->setParent(ui->widget);
        ui->Freq_Count->setParent(ui->widget);


        ui->Title_Marker->move(1019,30);
        ui->line_7->move(1019,61);
        ui->Marker_Select->move(1019,66);
        ui->Marker_View->move(1019,131);
        ui->Marker_AllOn->move(1019,196);
        ui->Marker_Type->move(1019,261);
        ui->Noise_Marker->move(1019,326);
        ui->Freq_Count->move(1019,391);
        ui->pb_prePage->setVisible(false);
        ui->pb_nextPage->setVisible(false);

        ui->Freq_Step->setFocus();
    }
    else if(SA_SPECTRUM_EMISSION_MASK_MODE == mMode)
    {
        ui->Freq_Center->setVisible(true);
        ui->Freq_Start->setVisible(false);
        ui->Freq_Stop->setVisible(false);
        ui->Span->setVisible(false);
        ui->Span_Full->setVisible(false);
        ui->Span_Zero->setVisible(false);
        ui->Span_Last->setVisible(false);
        ui->Channel_STD->setVisible(false);
        ui->Channel_Num->setVisible(false);
        ui->Channel_Step->setVisible(false);
        ui->Channel_Type->setVisible(false);
        ui->Atten->setVisible(false);
        ui->Atten_Value->setVisible(false);
        ui->Auto_SweepTime->setVisible(false);
        ui->Sweep_Time->setVisible(false);
        ui->RBW_Freq->setVisible(true);
        ui->RBW_Btn->setVisible(false);
        ui->VBW_Freq->setVisible(false);
        ui->VBW_Btn->setVisible(false);
        ui->VBW_RBW->setVisible(false);
        ui->Trace_Select->setVisible(false);
        ui->Trace_View->setVisible(false);
        ui->Trace_AllOn->setVisible(false);
        ui->Trace_Type->setVisible(true);
        ui->Detectors->setVisible(true);
        ui->Average->setVisible(true);
        ui->Freq_Count->setVisible(false);
        ui->Trace_AllClear->setVisible(false);
        ui->Marker_To->setVisible(false);
        ui->Limit_Select->setVisible(false);
        ui->Limit_Toggle->setVisible(false);
        ui->Limit_Edge_Toggle->setVisible(false);
        ui->Limit_Edge->setVisible(false);
        ui->Limit_Test->setVisible(false);
        ui->Limit_Type->setVisible(false);
        ui->Limit_AllClear->setVisible(false);
        //Freq
        ui->line->setGeometry(121,60,137,3);
        ui->Freq_Center->move(119,66);
        ui->Freq_Step->move(119,131);
        ui->Freq_Offset->move(119,196);
        //Ampt
        ui->Title_Ampt->move(269,30);
        ui->line_4->move(269,61);
        ui->Auto_Scale->move(269,66);
        ui->Ref_Level->move(269,131);
        ui->Scale_Division->move(269,196);
        ui->Preamp->move(269,261);
        ui->Ref_Offset->move(269,326);
        ui->Scale_Unit->move(269,391);
        ui->value_Unit->setPopupPotion(SA_BOTTOM,-ui->value_Unit->x(),0);
        //Sweep
        ui->Title_Sweep->move(419,30);
        ui->line_6->move(419,61);
        ui->Sweep_Mode->move(419,66);
        ui->Sweep_Once->move(419,131);
        //BW
        ui->Title_Bw->move(569,30);
        ui->line_5->move(569,61);
        ui->RBW_Freq->move(569,66);
        //Trigger
        ui->Title_Trigger->move(719,30);
        ui->line_3->move(719,61);
        ui->Trigger_Source->move(719,66);
        ui->Trigger_SubMenu->move(719,131);
        //Trace
        ui->Title_Trace->move(869,30);
        ui->line_2->move(869,61);
        ui->Average_Toggle->setVisible(false);

        ui->Trace_Type->move(869,66);
        ui->Detectors->move(869,131);
        ui->Average->move(869,196);
        ui->value_Detectors->setPopupPotion(SA_BOTTOM,-ui->value_Unit->x(),0);
        //Marker
        ui->Title_Marker->setParent(ui->widget);
        ui->line_7->setParent(ui->widget);
        ui->Marker_Select->setParent(ui->widget);
        ui->Marker_View->setParent(ui->widget);
        ui->Marker_AllOn->setParent(ui->widget);
        ui->Marker_Type->setParent(ui->widget);
        ui->Noise_Marker->setParent(ui->widget);
        ui->Freq_Count->setParent(ui->widget);

        ui->Title_Marker->move(1019,30);
        ui->line_7->move(1019,61);
        ui->Marker_Select->move(1019,66);
        ui->Marker_View->move(1019,131);
        ui->Marker_AllOn->move(1019,196);
        ui->Marker_Type->move(1019,261);
        ui->Noise_Marker->move(1019,326);
        ui->Freq_Count->move(1019,391);
        ui->pb_prePage->setVisible(false);
        ui->pb_nextPage->setVisible(false);

        ui->Freq_Center->setFocus();
    }
    else if(SA_CHNLPOWER_MEASURE_MODE == mMode ||\
             SA_OCCUPIED_BW_MEASURE_MODE == mMode)
    {
        //Freq
        ui->Freq_Center->setVisible(true);
        ui->Freq_Start->setVisible(false);
        ui->Freq_Stop->setVisible(false);
        ui->Span->setVisible(true);
        ui->Span_Full->setVisible(true);
        ui->Span_Zero->setVisible(false);
        ui->Span_Last->setVisible(true);
        ui->Channel_STD->setVisible(false);
        ui->Channel_Num->setVisible(false);
        ui->Channel_Step->setVisible(false);
        ui->Channel_Type->setVisible(false);
        //Ampt
        ui->Atten->setVisible(true);
        ui->Atten_Value->setVisible(true);

        ui->Auto_SweepTime->setVisible(true);
        ui->Sweep_Time->setVisible(true);
        //bw
        ui->RBW_Freq->setVisible(true);
        ui->RBW_Btn->setVisible(true);
        ui->VBW_Freq->setVisible(true);
        ui->VBW_Btn->setVisible(true);
        ui->VBW_RBW->setVisible(true);
        //Trace
        ui->Trace_Select->setVisible(false);
        ui->Trace_View->setVisible(false);
        ui->Trace_AllOn->setVisible(false);
        ui->Trace_Type->setVisible(true);
        ui->Trace_AllClear->setVisible(false);
        ui->Detectors->setVisible(true);
        ui->Average_Toggle->setVisible(false);
        //Marker
        ui->Marker_To->setVisible(false);
        ui->Limit_Select->setVisible(false);
        ui->Limit_Toggle->setVisible(false);
        ui->Limit_Edge_Toggle->setVisible(false);
        ui->Limit_Edge->setVisible(false);
        ui->Limit_Test->setVisible(false);
        ui->Limit_Type->setVisible(false);
        ui->Limit_AllClear->setVisible(false);
        ui->Freq_Count->setVisible(false);
        //Freq
        ui->line->setGeometry(121,60,137,3);
        ui->Freq_Center->move(119,66);
        ui->Freq_Step->move(119,131);
        ui->Freq_Offset->move(119,196);
        ui->Span->move(119,261);
        ui->Span_Full->move(119,326);
        ui->Span_Last->move(119,391);
        //Ampt
        ui->Title_Ampt->move(269,30);
        ui->line_4->move(269,61);
        ui->Auto_Scale->move(269,66);
        ui->Ref_Level->move(269,131);
        ui->Scale_Division->move(269,196);
        ui->Atten->move(269,261);
        ui->Atten_Value->move(269,326);
        ui->Preamp->move(269,391);
        ui->Ref_Offset->move(269,456);
        ui->Scale_Unit->move(269,521);
        ui->value_Unit->setPopupPotion(SA_TOP,-ui->value_Unit->x(),0);
        //Sweep
        ui->Title_Sweep->move(419,30);
        ui->line_6->move(419,61);
        ui->Auto_SweepTime->move(419,66);
        ui->Sweep_Time->move(419,131);
        ui->Sweep_Mode->move(419,196);
        ui->Sweep_Once->move(419,261);
        //BW
        ui->Title_Bw->move(569,30);
        ui->line_5->move(569,61);
        ui->RBW_Freq->move(569,66);
        ui->RBW_Btn->move(569,131);
        ui->VBW_Freq->move(569,196);
        ui->VBW_Btn->move(569,261);
        ui->VBW_RBW->move(569,326);
        //Trigger
        ui->Title_Trigger->move(719,30);
        ui->line_3->move(719,61);
        ui->Trigger_Source->move(719,66);
        ui->Trigger_SubMenu->move(719,131);
        //Trace
        ui->Title_Trace->move(869,30);
        ui->line_2->move(869,61);
        ui->Trace_Type->move(869,66);
        ui->Detectors->move(869,131);
        ui->Average->move(869,196);

        //Marker
        ui->Title_Marker->setParent(ui->widget);
        ui->line_7->setParent(ui->widget);
        ui->Marker_Select->setParent(ui->widget);
        ui->Marker_View->setParent(ui->widget);
        ui->Marker_AllOn->setParent(ui->widget);
        ui->Marker_Type->setParent(ui->widget);
        ui->Noise_Marker->setParent(ui->widget);
        ui->Freq_Count->setParent(ui->widget);

        ui->Title_Marker->move(1019,30);
        ui->line_7->move(1019,61);
        ui->Marker_Select->move(1019,66);
        ui->Marker_View->move(1019,131);
        ui->Marker_AllOn->move(1019,196);
        ui->Marker_Type->move(1019,261);
        ui->Noise_Marker->move(1019,326);
        ui->Freq_Count->move(1019,391);
        ui->pb_prePage->setVisible(false);
        ui->pb_nextPage->setVisible(false);

        ui->Freq_Center->setFocus();
    }
    else if(SA_ACP_MEASURE_MODE == mMode ||\
            SA_MULTI_ACP_MODE == mMode)
    {
        //Freq
        ui->Freq_Center->setVisible(true);
        ui->Freq_Start->setVisible(false);
        ui->Freq_Stop->setVisible(false);
        ui->Span->setVisible(true);
        ui->Span_Full->setVisible(true);
        ui->Span_Zero->setVisible(false);
        ui->Span_Last->setVisible(true);
        ui->Channel_STD->setVisible(false);
        ui->Channel_Num->setVisible(false);
        ui->Channel_Step->setVisible(false);
        ui->Channel_Type->setVisible(false);
        //Ampt
        ui->Atten->setVisible(true);
        ui->Atten_Value->setVisible(true);

        ui->Auto_SweepTime->setVisible(true);
        ui->Sweep_Time->setVisible(true);
        //bw
        ui->RBW_Freq->setVisible(true);
        ui->RBW_Btn->setVisible(true);
        ui->VBW_Freq->setVisible(true);
        ui->VBW_Btn->setVisible(true);
        ui->VBW_RBW->setVisible(true);
        //Trace
        ui->Trace_Select->setVisible(true);

        ui->Trace_View->setVisible(true);
        ui->Trace_AllOn->setVisible(false);
        ui->Trace_Type->setVisible(true);
        ui->Trace_AllClear->setVisible(false);
        ui->Detectors->setVisible(true);
        ui->Average_Toggle->setVisible(false);
        //Marker
        ui->Marker_To->setVisible(false);
        ui->Limit_Select->setVisible(false);
        ui->Limit_Toggle->setVisible(false);
        ui->Limit_Edge_Toggle->setVisible(false);
        ui->Limit_Edge->setVisible(false);
        ui->Limit_Test->setVisible(false);
        ui->Limit_Type->setVisible(false);
        ui->Limit_AllClear->setVisible(false);
        ui->Freq_Count->setVisible(false);
        //Freq
        ui->line->setGeometry(121,60,137,3);
        ui->Freq_Center->move(119,66);
        ui->Freq_Step->move(119,131);
        ui->Freq_Offset->move(119,196);
        ui->Span->move(119,261);
        ui->Span_Full->move(119,326);
        ui->Span_Last->move(119,391);
        //Ampt
        ui->Title_Ampt->move(269,30);
        ui->line_4->move(269,61);
        ui->Auto_Scale->move(269,66);
        ui->Ref_Level->move(269,131);
        ui->Scale_Division->move(269,196);
        ui->Atten->move(269,261);
        ui->Atten_Value->move(269,326);
        ui->Preamp->move(269,391);
        ui->Ref_Offset->move(269,456);
        ui->Scale_Unit->move(269,521);
        ui->value_Unit->setPopupPotion(SA_TOP,-ui->value_Unit->x(),0);
        //Sweep
        ui->Title_Sweep->move(419,30);
        ui->line_6->move(419,61);
        ui->Auto_SweepTime->move(419,66);
        ui->Sweep_Time->move(419,131);
        ui->Sweep_Mode->move(419,196);
        ui->Sweep_Once->move(419,261);
        //BW
        ui->Title_Bw->move(569,30);
        ui->line_5->move(569,61);
        ui->RBW_Freq->move(569,66);
        ui->RBW_Btn->move(569,131);
        ui->VBW_Freq->move(569,196);
        ui->VBW_Btn->move(569,261);
        ui->VBW_RBW->move(569,326);
        //Trigger
        ui->Title_Trigger->move(719,30);
        ui->line_3->move(719,61);
        ui->Trigger_Source->move(719,66);
        ui->Trigger_SubMenu->move(719,131);
        //Trace
        ui->Title_Trace->move(869,30);
        ui->line_2->move(869,61);
        ui->Trace_Select->move(869,66);
        ui->Trace_View->move(869,131);
        ui->Trace_Type->move(869,196);
        ui->Detectors->move(869,261);
        ui->Average->move(869,326);


        QListView* view = qobject_cast<QListView *>(ui->value_Trace->view());
        view->setRowHidden(3, true);
        view->setRowHidden(4, true);
        view->setRowHidden(5, true);
        //Marker
        ui->Title_Marker->setParent(ui->widget);
        ui->line_7->setParent(ui->widget);
        ui->Marker_Select->setParent(ui->widget);
        ui->Marker_View->setParent(ui->widget);
        ui->Marker_AllOn->setParent(ui->widget);
        ui->Marker_Type->setParent(ui->widget);
        ui->Noise_Marker->setParent(ui->widget);
        ui->Freq_Count->setParent(ui->widget);

        ui->Title_Marker->move(1019,30);
        ui->line_7->move(1019,61);
        ui->Marker_Select->move(1019,66);
        ui->Marker_View->move(1019,131);
        ui->Marker_AllOn->move(1019,196);
        ui->Marker_Type->move(1019,261);
        ui->Noise_Marker->move(1019,326);
        ui->Freq_Count->move(1019,391);
        ui->pb_prePage->setVisible(false);
        ui->pb_nextPage->setVisible(false);

        ui->Freq_Center->setFocus();
    }
    else
    {
        ui->Freq_Count->setVisible(true);
        ui->Freq_Center->setVisible(true);
        ui->Freq_Start->setVisible(true);
        ui->Freq_Stop->setVisible(true);
        ui->Span->setVisible(true);
        ui->Span_Full->setVisible(true);
        ui->Span_Zero->setVisible(true);
        ui->Span_Last->setVisible(true);
        ui->Channel_STD->setVisible(true);
        ui->Channel_Num->setVisible(true);
        ui->Channel_Step->setVisible(true);
        ui->Channel_Type->setVisible(true);
        ui->Atten->setVisible(true);
        ui->Atten_Value->setVisible(true);
        ui->Auto_SweepTime->setVisible(true);
        ui->Sweep_Time->setVisible(true);
        ui->RBW_Freq->setVisible(true);
        ui->RBW_Btn->setVisible(true);
        ui->VBW_Freq->setVisible(true);
        ui->VBW_Btn->setVisible(true);
        ui->VBW_RBW->setVisible(true);
        ui->Trace_Select->setVisible(true);
        ui->Trace_View->setVisible(true);
        ui->Trace_AllOn->setVisible(true);
        ui->Trace_Type->setVisible(true);
        ui->Trace_AllClear->setVisible(true);
        ui->Detectors->setVisible(true);
        ui->Marker_To->setVisible(true);
        ui->Limit_Select->setVisible(true);
        ui->Limit_Toggle->setVisible(true);
        ui->Limit_Edge_Toggle->setVisible(true);
        ui->Limit_Edge->setVisible(true);
        ui->Limit_Test->setVisible(true);
        ui->Limit_Type->setVisible(true);
        ui->Limit_AllClear->setVisible(true);
        //Freq

        ui->line->setGeometry(121,60,287,3);
        ui->Freq_Step->move(119,261);
        ui->Freq_Offset->move(119,326);

        ui->Span->move(119,391);
        ui->Span_Full->move(119,456);
        ui->Span_Last->move(119,521);

        //Ampt
        ui->Title_Ampt->move(419,30);
        ui->line_4->move(421,61);
        ui->Auto_Scale->move(419,66);
        ui->Ref_Level->move(419,131);
        ui->Scale_Division->move(419,196);
        ui->Atten->move(419,261);
        ui->Atten_Value->move(419,326);
        ui->Preamp->move(419,391);
        ui->Ref_Offset->move(419,456);
        ui->Scale_Unit->move(419,521);
        ui->value_Unit->setPopupPotion(SA_TOP,-ui->value_Unit->x(),0);
        //Sweep
        ui->Title_Sweep->move(569,30);
        ui->line_6->move(569,61);
        ui->Auto_SweepTime->move(569,66);
        ui->Sweep_Time->move(569,131);
        ui->Sweep_Mode->move(569,196);
        ui->Sweep_Once->move(569,261);
        //BW
        ui->Title_Bw->move(719,30);
        ui->line_5->move(721,61);

        ui->RBW_Freq->move(719,66);
        ui->RBW_Btn->move(719,131);
        ui->VBW_Freq->move(719,196);
        ui->VBW_Btn->move(719,261);
        ui->VBW_RBW->move(719,326);
        //Trigger
        ui->Title_Trigger->move(869,30);
        ui->line_3->move(871,61);
        ui->Trigger_Source->move(869,66);
        ui->Trigger_SubMenu->move(869,131);
        //Trace
        ui->Title_Trace->move(1019,30);
        ui->line_2->move(1021,61);
        ui->Trace_Select->move(1021,66);
        ui->Trace_View->move(1021,131);
        ui->Trace_Type->move(1021,261);
        ui->Average->move(1019,326);
        ui->Detectors->move(1019,456);
        QListView* view = qobject_cast<QListView *>(ui->value_Trace->view());
        view->setRowHidden(3, false);
        view->setRowHidden(4, false);
        view->setRowHidden(5, false);
        //Marker
        ui->Title_Marker->setParent(ui->widget_2);
        ui->line_7->setParent(ui->widget_2);
        ui->Marker_Select->setParent(ui->widget_2);
        ui->Marker_View->setParent(ui->widget_2);
        ui->Marker_AllOn->setParent(ui->widget_2);
        ui->Marker_Type->setParent(ui->widget_2);
        ui->Noise_Marker->setParent(ui->widget_2);
        ui->Freq_Count->setParent(ui->widget_2);

        ui->Title_Marker->move(119,30);
        ui->line_7->move(121,61);
        ui->Marker_Select->move(119,66);
        ui->Marker_View->move(119,131);
        ui->Marker_AllOn->move(119,196);
        ui->Marker_Type->move(119,261);
        ui->Noise_Marker->move(119,391);
        ui->Freq_Count->move(119,456);
        ui->pb_prePage->setVisible(true);
        ui->pb_nextPage->setVisible(true);


        ui->Average_Toggle->setVisible(false);
        ui->Freq_Center->setFocus();
    }
}
SA_Dialog_AllSetup::~SA_Dialog_AllSetup()
{
    digitInputClose();
    channelInputClose();
    delete ui;
}
/**
 * @brief  Close digit input dialog.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
void SA_Dialog_AllSetup::digitInputClose()
{
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    return;
}
void SA_Dialog_AllSetup::channelInputClose()
{
    if(mChannelInput)
    {
        disconnect(mChannelInput,SIGNAL(destroyed),this,SLOT(on_CHfinishEntry()));
        delete mChannelInput;
        mChannelInput = NULL;
    }
    return;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_AllSetup::initMap()
{     
    qint32 size;
    mWidgetList.insert(SA_ALLSET_CENTERFREQ,ui->Freq_Center);
    mWidgetList.insert(SA_ALLSET_SPAN,ui->Span);
    mWidgetList.insert(SA_ALLSET_STARTFREQ,ui->Freq_Start);
    mWidgetList.insert(SA_ALLSET_STOPFREQ,ui->Freq_Stop);
    mWidgetList.insert(SA_ALLSET_SPANFULL,ui->Span_Full);
    mWidgetList.insert(SA_ALLSET_SPANZERO,ui->Span_Zero);
    mWidgetList.insert(SA_ALLSET_SPANLAST,ui->Span_Last);
    mWidgetList.insert(SA_ALLSET_FREQSTEP,ui->Freq_Step);
    mWidgetList.insert(SA_ALLSET_FREQOFFSET,ui->Freq_Offset);
    mWidgetList.insert(SA_ALLSET_CHANNELSTD,ui->Channel_STD);
    mWidgetList.insert(SA_ALLSET_CHANNELNUM,ui->Channel_Num);
    mWidgetList.insert(SA_ALLSET_CHANNELSTEP,ui->Channel_Step);
    mWidgetList.insert(SA_ALLSET_CHANNELTYPE,ui->Channel_Type);

    mWidgetList.insert(SA_ALLSET_AUTOSCALE,ui->Auto_Scale);
    mWidgetList.insert(SA_ALLSET_REFLEVEL,ui->Ref_Level);
    mWidgetList.insert(SA_ALLSET_ATTEN,ui->Atten);
    mWidgetList.insert(SA_ALLSET_ATTENVALUE,ui->Atten_Value);
    mWidgetList.insert(SA_ALLSET_PREAMP,ui->Preamp);
    mWidgetList.insert(SA_ALLSET_REFOFFSET,ui->Ref_Offset);
    mWidgetList.insert(SA_ALLSET_DIVISION,ui->Scale_Division);
    mWidgetList.insert(SA_ALLSET_UNIT,ui->Scale_Unit);

    mWidgetList.insert(SA_ALLSET_AUTOSWEEPTIME,ui->Auto_SweepTime);
    mWidgetList.insert(SA_ALLSET_SWEEPTIME,ui->Sweep_Time);
    mWidgetList.insert(SA_ALLSET_SWEEPONCE,ui->Sweep_Once);
    mWidgetList.insert(SA_ALLSET_MODE,ui->Sweep_Mode);

    mWidgetList.insert(SA_ALLSET_RBW,ui->RBW_Freq);
    mWidgetList.insert(SA_ALLSET_AUTORBW,ui->RBW_Btn);
    mWidgetList.insert(SA_ALLSET_VBW,ui->VBW_Freq);
    mWidgetList.insert(SA_ALLSET_AUTOVBW,ui->VBW_Btn);
    mWidgetList.insert(SA_ALLSET_VBW_RBW,ui->VBW_RBW);

    mWidgetList.insert(SA_ALLSET_TRIGGER_SOURCE,ui->Trigger_Source);

    mWidgetList.insert(SA_ALLSET_TRIGGER_VIEDO_LEVEL,ui->Video_Level);
    mWidgetList.insert(SA_ALLSET_TRIGGER_VIEDO_SLOPE,ui->Video_Slope);
    mWidgetList.insert(SA_ALLSET_TRIGGER_VIEDO_DELAYON,ui->Video_DelayOn);
    mWidgetList.insert(SA_ALLSET_TRIGGER_VIEDO_DELAYTIME,ui->Video_DelayTime);
    mWidgetList.insert(SA_ALLSET_TRIGGER_EXTERNAL_LEVEL,ui->External_Level);
    mWidgetList.insert(SA_ALLSET_TRIGGER_EXTERNAL_SLOPE,ui->External_Slope);
    mWidgetList.insert(SA_ALLSET_TRIGGER_EXTERNAL_DELAYON,ui->External_DelayOn);
    mWidgetList.insert(SA_ALLSET_TRIGGER_EXTERNAL_DELAYTIME,ui->External_DelayTime);
    mWidgetList.insert(SA_ALLSET_TRIGGER_PER_TIME,ui->Peri_Timer);
    mWidgetList.insert(SA_ALLSET_TRIGGER_PER_DELAYON,ui->Peri_DelayOn);
    mWidgetList.insert(SA_ALLSET_TRIGGER_PER_DELAYTIME,ui->Peri_DelayTime);
    mWidgetList.insert(SA_ALLSET_TRIGGER_RFBURST_LEVEL,ui->RFBurst_Level);
    mWidgetList.insert(SA_ALLSET_TRIGGER_RFBURST_SLOPE,ui->RFBurst_Slope);
    mWidgetList.insert(SA_ALLSET_TRIGGER_RFBURST_DELAYON,ui->RFBurst_DelayOn);
    mWidgetList.insert(SA_ALLSET_TRIGGER_RFBURST_DELAYTIME,ui->RFBurst_DelayTime);

    mWidgetList.insert(SA_ALLSET_TRACESELECT,ui->Trace_Select);
    mWidgetList.insert(SA_ALLSET_TRACEVIEW,ui->Trace_View);
    mWidgetList.insert(SA_ALLSET_TRACETYPE,ui->Trace_Type);
    mWidgetList.insert(SA_ALLSET_DETECTORS,ui->Detectors);
    mWidgetList.insert(SA_ALLSET_AVERAGE,ui->Average_Toggle);
    mWidgetList.insert(SA_ALLSET_AVERAGEVALUE,ui->Average);
    mWidgetList.insert(SA_ALLSET_TRACEALLON,ui->Trace_AllOn);
    mWidgetList.insert(SA_ALLSET_TRACEALLCLEAR,ui->Trace_AllClear);

    mWidgetList.insert(SA_ALLSET_MARKERSELECT,ui->Marker_Select);
    mWidgetList.insert(SA_ALLSET_MARKERVIEW,ui->Marker_View);
    mWidgetList.insert(SA_ALLSET_MARKERTYPE,ui->Marker_Type);
    mWidgetList.insert(SA_ALLSET_MARKERALLON,ui->Marker_AllOn);
    mWidgetList.insert(SA_ALLSET_FREQCOUNT,ui->Freq_Count);
    mWidgetList.insert(SA_ALLSET_NOISEMARKER,ui->Noise_Marker);
    mWidgetList.insert(SA_ALLSET_MARKERTO,ui->Marker_To);

    mWidgetList.insert(SA_ALLSET_LIMITSELECT,ui->Limit_Select);
    mWidgetList.insert(SA_ALLSET_LIMIT,ui->Limit_Toggle);
    mWidgetList.insert(SA_ALLSET_LIMITEDGE,ui->Limit_Edge_Toggle);
    mWidgetList.insert(SA_ALLSET_LIMITEDGEVALUE,ui->Limit_Edge);
    mWidgetList.insert(SA_ALLSET_LIMITTEST,ui->Limit_Test);
    mWidgetList.insert(SA_ALLSET_LIMITTYPE,ui->Limit_Type);
    mWidgetList.insert(SA_ALLSET_LIMITALLCLEAR,ui->Limit_AllClear);

    size = mWidgetList.size();
    for(qint32 i = 0; i < size;i++)
    {
        connect(mWidgetList.value(i),SIGNAL(clicked()),this,SLOT(on_widgetclicked()));
        connect(mWidgetList.value(i),SIGNAL(focusIn()),this,SLOT(on_widgetFocus()));
    }
    mInputWidget<<SA_ALLSET_CENTERFREQ<<SA_ALLSET_SPAN<<SA_ALLSET_STARTFREQ;
    mInputWidget<<SA_ALLSET_STOPFREQ<<SA_ALLSET_FREQSTEP<<SA_ALLSET_FREQOFFSET<<SA_ALLSET_CHANNELNUM;
    mInputWidget<<SA_ALLSET_REFLEVEL<<SA_ALLSET_ATTENVALUE<<SA_ALLSET_REFOFFSET<<SA_ALLSET_DIVISION;
    mInputWidget<<SA_ALLSET_SWEEPTIME<<SA_ALLSET_AVERAGEVALUE<<SA_ALLSET_LIMITEDGEVALUE;
    mInputWidget<<SA_ALLSET_TRIGGER_VIEDO_LEVEL<<SA_ALLSET_TRIGGER_VIEDO_DELAYTIME<<SA_ALLSET_TRIGGER_EXTERNAL_LEVEL<<SA_ALLSET_TRIGGER_EXTERNAL_DELAYTIME;
    mInputWidget<<SA_ALLSET_TRIGGER_PER_TIME<<SA_ALLSET_TRIGGER_PER_DELAYTIME<<SA_ALLSET_TRIGGER_RFBURST_LEVEL<<SA_ALLSET_TRIGGER_RFBURST_DELAYTIME;

    ui->value_Unit->setPopupPotion(SA_TOP,-ui->value_Unit->x(),0);
    ui->value_MarkerSelect->setPopupPotion(SA_BOTTOM,-ui->value_MarkerSelect->x(),0);
    ui->value_Trace->setPopupPotion(SA_BOTTOM,-ui->value_Trace->x(),0);
    ui->value_TraceType->setPopupPotion(SA_BOTTOM,-ui->value_TraceType->x(),0);
    ui->value_Detectors->setPopupPotion(SA_BOTTOM/*SA_TOP*/,-ui->value_Detectors->x(),0);
    ui->value_VBW->setPopupPotion(SA_BOTTOM,-ui->value_VBW->x(),0);
    ui->value_RBW->setPopupPotion(SA_BOTTOM,-ui->value_RBW->x(),0);
    ui->value_VBW_RBW->setPopupPotion(SA_BOTTOM,-ui->value_VBW_RBW->x(),0);
    ui->value_LimitSelect->setPopupPotion(SA_BOTTOM,-ui->value_LimitSelect->x(),0);
    ui->value_MarkerTo->setPopupPotion(SA_BOTTOM,-ui->value_MarkerTo->x(),0);
    ui->value_TriggerSource->setPopupPotion(SA_BOTTOM,-ui->value_TriggerSource->x(),0);
    return ;
}
void SA_Dialog_AllSetup::on_widgetFocus()
{
    qint32 index;
    SA_ClickedWidget* widget = qobject_cast<SA_ClickedWidget*>(sender());
    index = mWidgetList.key(widget,-1);
    if(curWidget != index)
    {
        lastWidget = curWidget;
        curWidget = index;
        refreshFocus();
    }
    return;
}
void SA_Dialog_AllSetup::on_widgetclicked()
{
    SA_Dialog_Warning *message;
    qint32 index;
    bool status ;
    SA_ClickedWidget* widget = qobject_cast<SA_ClickedWidget*>(sender());
    index = mWidgetList.key(widget,-1);
    lastWidget = curWidget;
    curWidget = index;

    if(index == -1)
    {
        return ;
    }
    if(!mInputWidget.contains(curWidget))
    {
        digitInputClose();
    }
    if(index >=SA_ALLSET_CENTERFREQ && index <=SA_ALLSET_CHANNELTYPE)
    {
        globalUserVariable->PrimaryAction = SA_FREQUENCY;
    }else if(index >=SA_ALLSET_AUTOSCALE && index <=SA_ALLSET_UNIT)
    {
        globalUserVariable->PrimaryAction = SA_AMPLITUDE;
    }
    switch (index)
    {
    case SA_ALLSET_CENTERFREQ:
        showInputDialog(SA_INPUT_FREQ_CENTER);
        break;
    case SA_ALLSET_SPAN:
        showInputDialog(SA_INPUT_FREQ_SPAN);
        break;
    case SA_ALLSET_STARTFREQ:
        showInputDialog(SA_INPUT_FREQ_START);
        break;
    case SA_ALLSET_STOPFREQ:
        showInputDialog(SA_INPUT_FREQ_STOP);
        break;
    case SA_ALLSET_SPANFULL:
        ui->pb_FullSpan->setChecked(true);
        mControl->setFullSpan();
        break;
    case SA_ALLSET_SPANZERO:
        ui->pb_ZeroSpan->setChecked(true);
        mControl->setZeroSpan();
        break;
    case SA_ALLSET_SPANLAST:
        ui->pb_LastSpan->setChecked(true);
        mControl->setLastSpan();
        break;
    case SA_ALLSET_FREQSTEP:
        showInputDialog(SA_INPUT_FREQ_CF);
        break;
    case SA_ALLSET_FREQOFFSET:
        showInputDialog(SA_INPUT_FREQ_OFFSET);
        break;
    case SA_ALLSET_CHANNELSTD:
        digitInputClose();
        mChannelInput = new SA_Dialog_CH_Std(mControl,globalUserVariable,this);
        mChannelInput->setFocusPolicy(Qt::NoFocus);
        mChannelInput->setGeometry(0,0,this->width(),this->height());
        connect(mChannelInput,SIGNAL(destroyed()  ),this,SLOT(on_CHfinishEntry()),Qt::DirectConnection);
        mChannelInput->show();
        break;
    case SA_ALLSET_CHANNELNUM:
        if(mControl->getCHStandard()<0)
        {
            digitInputClose();
            break;
        }

        showInputDialog(SA_INPUT_CH_NUM);
        break;
    case SA_ALLSET_CHANNELSTEP:
        showInputDialog(SA_INPUT_CH_STEP);
        break;
    case SA_ALLSET_CHANNELTYPE:
        status = ui->Channel_Uplink->isChecked();
        mControl->setCommuDirection(status);
        break;
    case SA_ALLSET_AUTOSCALE:
        ui->pb_AutoScale->setChecked(true);
        mControl->setAutoScale();
        break;
    case SA_ALLSET_REFLEVEL:
        showInputDialog(SA_INPUT_REF_LEVEL);
        break;
    case SA_ALLSET_ATTEN:
        status = ui->Atten_Auto->isChecked();
        mControl->setAttenStatus(!status);
        break;
    case SA_ALLSET_ATTENVALUE:
        showInputDialog(SA_INPUT_ATTEN);
        break;
    case SA_ALLSET_PREAMP:
        status = ui->btn_Preamp->isChecked();
        status = !status;
        ui->btn_Preamp->setChecked(status);
        mControl->setPreampStatus(status);
        break;
    case SA_ALLSET_REFOFFSET:
        showInputDialog(SA_INPUT_REF_OFFSET);
        break;
    case SA_ALLSET_DIVISION:
        showInputDialog(SA_INPUT_SCALEDIV);
        break;
    case SA_ALLSET_UNIT:
        ui->value_Unit->showPopup();
        break;
    case SA_ALLSET_AUTOSWEEPTIME:
        ui->pb_AutoScale->setChecked(true);
        status = ui->SweepTime_Auto->isChecked();
        status = !status;
        mControl->setAutoSweepTimeStatus(status);
        break;
    case SA_ALLSET_SWEEPTIME:
        showInputDialog(SA_INPUT_SWEEP_TIME);
        break;
    case SA_ALLSET_MODE:
        if(ui->Sweep_Conti->isChecked())
        {
            status = SA_SINGLE;
            mControl->setSuspendFunc(0);
        }else
        {
            status = SA_CONT;
        }
        mControl->setSweepType(status);
        break;
    case SA_ALLSET_SWEEPONCE:
        ui->pb_SweepOnce->setChecked(true);
        mControl->setSweepType(SA_SINGLE);
        break;
    case SA_ALLSET_RBW:
        ui->value_RBW->showPopup();
        break;
    case SA_ALLSET_AUTORBW:
        if(ui->RBW_Auto->isChecked())
        {
            status = SA_MANUAL;
        }else
        {
            status = SA_AUTO;
        }
        mControl->setAutoRbwStatus(status);
        break;
    case SA_ALLSET_VBW:
        ui->value_VBW->showPopup();
        break;
    case SA_ALLSET_AUTOVBW:
        if(ui->VBW_Auto->isChecked())
        {
            status = SA_MANUAL;
        }else
        {
            status = SA_AUTO;
        }
        mControl->setAutoRbwStatus(status);
        break;
    case SA_ALLSET_VBW_RBW:
        ui->value_VBW_RBW->showPopup();
        break;
    case SA_ALLSET_TRIGGER_SOURCE:
        ui->value_TriggerSource->showPopup();
        break;
    case SA_ALLSET_TRIGGER_VIEDO_SLOPE:
        if(ui->pb_Video_Pos->isChecked())
        {
            status = SA_NEGATIVE;
        }else
        {
            status = SA_POSITIVE;
        }
        mControl->setTriggerSlope(status);
        break;
    case SA_ALLSET_TRIGGER_EXTERNAL_SLOPE:
        if(ui->pb_External_Pos->isChecked())
        {
            status = SA_NEGATIVE;
        }else
        {
            status = SA_POSITIVE;
        }
        mControl->setTriggerSlope(status);
        break;
    case SA_ALLSET_TRIGGER_RFBURST_SLOPE:
        if(ui->pb_RFBurst_Pos->isChecked())
        {
            status = SA_NEGATIVE;
        }else
        {
            status = SA_POSITIVE;
        }
        mControl->setTriggerSlope(status);
        break;
    case SA_ALLSET_TRIGGER_VIEDO_DELAYON:
        status = ui->value_Video_DelayOn->isChecked();
        status = !status;
        ui->value_Video_DelayOn->setChecked(status);
        mControl->setTriggerDelayStatus(status);
        break;
    case SA_ALLSET_TRIGGER_EXTERNAL_DELAYON:
        status = ui->value_External_DelayOn->isChecked();
        status = !status;
        ui->value_External_DelayOn->setChecked(status);
        mControl->setTriggerDelayStatus(status);
        break;
    case SA_ALLSET_TRIGGER_PER_DELAYON:
        status = ui->value_Peri_DelayOn->isChecked();
        status = !status;
        ui->value_Peri_DelayOn->setChecked(status);
        mControl->setTriggerDelayStatus(status);
        break;
    case SA_ALLSET_TRIGGER_RFBURST_DELAYON:
        status = ui->value_RFBurst_DelayOn->isChecked();
        status = !status;
        ui->value_RFBurst_DelayOn->setChecked(status);
        mControl->setTriggerDelayStatus(status);
        break;
    case SA_ALLSET_TRIGGER_VIEDO_LEVEL:
    case SA_ALLSET_TRIGGER_EXTERNAL_LEVEL:
    case SA_ALLSET_TRIGGER_RFBURST_LEVEL:
        showInputDialog(SA_INPUT_TRIGGER_LEVEL);
        break;
    case SA_ALLSET_TRIGGER_PER_TIME:
        showInputDialog(SA_INPUT_TRIGGER_PERTIMER);
        break;
    case SA_ALLSET_TRIGGER_VIEDO_DELAYTIME:
    case SA_ALLSET_TRIGGER_EXTERNAL_DELAYTIME:
    case SA_ALLSET_TRIGGER_PER_DELAYTIME:
    case SA_ALLSET_TRIGGER_RFBURST_DELAYTIME:
        showInputDialog(SA_INPUT_TRIGGER_DELAY_VALUE);
        break;
    case SA_ALLSET_TRACESELECT:
        ui->value_Trace->showPopup();
        break;
    case SA_ALLSET_TRACEVIEW:
        if(ui->btn_TraceView->isChecked())
        {
           status = SA_OFF;
        }else
        {
            status = SA_ON;
        }
        ui->btn_TraceView->setChecked(status);
        mControl->setTraceViewStatus(status,mTrIndex);
        if(status)
            mControl->setTraceSelect(mTrIndex);
        else {
            for(qint32 i = TRACE_CNT_TOTAL - 1;i>= 0;i--)
            {
                if(mControl->getTraceViewStatus(i) == SA_ON)
                {
                    mControl->setTraceSelect(i);
                    break;
                }
            }
        }
        break;
    case SA_ALLSET_TRACETYPE:
        ui->value_TraceType->showPopup();
        break;
    case SA_ALLSET_DETECTORS:
        if(ui->value_Detectors->isEnabled())
            ui->value_Detectors->showPopup();
        break;
    case SA_ALLSET_TRACEALLON:
        ui->pb_TraceAllOn->setChecked(true);
        for(qint32 i =0 ;i<TRACE_CNT_TOTAL;i++)
        {
            mControl->setTraceViewStatus(SA_ON,i);
        }
        break;
    case SA_ALLSET_TRACEALLCLEAR:
        //waring popup
        message =new SA_Dialog_Warning("Notice","Are you sure to clear all traces?",this);
        message->setWindowFlags(Qt::Window|Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        if(message->exec() != QDialog::Accepted)
        {
            return;
        }
        ui->pb_TraceAllClear->setChecked(true);
        mControl->setTraceSelect(0);
        for(qint32 i =0 ;i<TRACE_CNT_TOTAL;i++)
        {
            mControl->setTraceViewStatus(SA_OFF,i);
            mControl->setTraceType(SA_CLEAR_WRITE ,i);
            mControl->setTraceAverageStatus(SA_OFF,i);
        }
        break;
    case SA_ALLSET_AVERAGE:
        if(ui->btn_Average->isChecked())
        {
            status = SA_OFF;
        }else
        {
            status = SA_ON;
        }
        mControl->setTraceAverageStatus(status);
        break;

    case SA_ALLSET_AVERAGEVALUE:
        showInputDialog(SA_INPUT_AVERAGE_COUNT);
        break;
    case SA_ALLSET_MARKERSELECT:
        ui->value_MarkerSelect->showPopup();
        break;
    case SA_ALLSET_MARKERVIEW:
        if(ui->btn_MarkerView->isChecked())
        {
            status = SA_OFF;
        }else
        {
            status = SA_ON;
        }
        mControl->setMarkerViewStatus(status);
        break;
    case SA_ALLSET_MARKERTYPE:
        if(ui->Marker_Normal->isChecked())
        {
            status = DELTA;
        }else
        {
            status = REF;
        }
        mControl->setMarkerType(status);
        break;
    case SA_ALLSET_MARKERALLON:
        ui->pb_MkrAllOn->setChecked(true);
        for(qint32 i = 0;i<MARKER_TOTAL_CNT;i++)
        {
            if(!mControl->getMarkerViewStatus(i))
            {
                mControl->setMarkerViewStatus(SA_ON,i);
            }
        }
        break;
    case SA_ALLSET_MARKERTO:
        ui->value_MarkerTo->showPopup();
        break;
    case SA_ALLSET_FREQCOUNT:
        if(ui->btn_FreqCount->isChecked())
        {
            status = SA_OFF;
        }else
        {
            status = SA_ON;
        }
        mControl->setMarkerFreqCountStatus(status);
        //Tony 19-12-19
        if(!mControl->getMarkerFreqCountStatus())
        {
            //ui->pb_FreqCount->setChecked(false);
            mControl->setMarkerFreqCountStatus(SA_OFF);
        }
        else
        {
            //ui->pb_FreqCount->setChecked(true);
            mControl->setMarkerFreqCountStatus(SA_ON);

            mControl->setMarkerViewStatus(SA_ON);
        }
        break;
    case SA_ALLSET_NOISEMARKER:
        if(ui->btn_NoiseMarker->isChecked())
        {
            status = SA_OFF;
        }else
        {
            status = SA_ON;
        }
        mControl->setMarkerNoiseStatus(status);
        break;
     case SA_ALLSET_LIMITSELECT:
        ui->value_LimitSelect->showPopup();
        break;
    case SA_ALLSET_LIMIT:
        if(ui->Value_Limit_Toggle->isChecked())
        {
            status = SA_OFF;
        }else
        {
            status = SA_ON;
        }
        mControl->setLimitLineStatus(status);
       break;
    case SA_ALLSET_LIMITEDGE:
        if(ui->value_Limit_Edge_Toggle->isChecked())
        {
            status = SA_OFF;
        }else
        {
            status = SA_ON;
        }
        mControl->setLimitEdgeStatus(status);
       break;
    case SA_ALLSET_LIMITEDGEVALUE:
       showInputDialog(SA_LIMIT_EDGE);
       break;
    case SA_ALLSET_LIMITTEST:
        if(ui->Value_Limit_Test->isChecked())
        {
            status = SA_OFF;
        }else
        {
            status = SA_ON;
        }
        mControl->setLimitTestStatus(status);
       break;
    case SA_ALLSET_LIMITTYPE:
        if(ui->btn_Upper->isChecked())
        {
            status = LOWER;
        }else
        {
            status = UPPER;
        }
        mControl->setLimitType(status);
       break;
    case SA_ALLSET_LIMITALLCLEAR:
        qint32 status = 0;
        for(qint32 i=0;i<LIMIT_SELECTSUM;i++)
        {
           if(mControl->globalUserLimit->gTotalDot[i] != 0)
           {
               status = 1;
               break;
           }
        }
        if(status){
            SA_Dialog_Warning message("Notice","Are you sure to delete all limits?",this);
            message.setWindowFlags(Qt::Window |Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
            if(message.exec() != QDialog::Accepted)
            {
                return;
            }

            mControl->setDeleteLimitAll();
            ui->pb_LimitAllDelete->setChecked(true);
        }
       break;
    }
    initDisplay();
}
/**
 * @brief  Widget clicked event.
 * @param  void
 * @author Tony
 * @since 2018-12-26
*/
void SA_Dialog_AllSetup::on_clicked()
{
    qint32 index;
    SA_ClickedWidget* widget = qobject_cast<SA_ClickedWidget*>(sender());
    index = mWidgetList.key(widget,-1);
    if(index == -1)
    {
        return ;
    }
    switch (index) {
    case SA_INPUT_MANUAL_RBW:
        if(!ui->RBW_Manual->isChecked())
        {
            ui->RBW_Manual->setChecked(true);
            mControl->setAutoRbwStatus(false);
        }
        break;
    case SA_INPUT_MANUAL_VBW:
        if(!ui->VBW_Manual->isChecked())
        {
            ui->VBW_Manual->setChecked(true);
            mControl->setAutoVbwStatus(false);
        }
        break;
    default:
        break;
    }
    showInputDialog(index);
    return ;
}

/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_AllSetup::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
        mInputDialog->initDisplay(index);
    }
    else
    {
        mInputDialog = new SA_Dialog_DigitInput(mControl,globalUserVariable,index,this);
        mInputDialog->setFocusPolicy(Qt::NoFocus);
        mInputDialog->move(mapToGlobal(QPoint(0,46)).x(),mapToGlobal(QPoint(0,46)).y());
        connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        mInputDialog->show();
    }
    return ;
}
/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_AllSetup::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;

   if(mWidgetList.contains(index)||index == SA_INPUT_TRIGGER_LEVEL||\
           index == SA_INPUT_TRIGGER_PERTIMER|| index == SA_INPUT_TRIGGER_DELAY_VALUE)
        initDisplay();
    return ;
}
/**
 * @brief  Init the display.
 * @param  void
 * @author Tony
 * @since 2018-01-03
*/
void SA_Dialog_AllSetup::initDisplay()
{
    //ui->stackedWidget->setCurrentIndex(0);
    refreshFreq();
    refreshAmpt();
    refreshSweepTime();
    refreshBW();
    refreshTrigger();
    refreshTrace();
    refreshMarker();
    refreshLimit();
    refreshFocus();
    ui->pb_FullSpan->setVisible(false);
    ui->pb_ZeroSpan->setVisible(false);
    ui->pb_LastSpan->setVisible(false);
    ui->pb_AutoScale->setVisible(false);
    ui->pb_SweepOnce->setVisible(false);
    ui->pb_TraceAllClear->setVisible(false);
    ui->pb_TraceAllOn->setVisible(false);
    ui->pb_MkrAllOn->setVisible(false);
    ui->pb_LimitAllDelete->setVisible(false);
    return ;
}

/**
 * @brief  Refresh unit information.
 * @param  void.
 * @author Tony
 * @since 2018-01-04
*/
void SA_Dialog_AllSetup::refreshUnit()
{
    qint32 mUnit;
    mUnit = mControl->getAmpUnit();
    ui->value_Unit->blockSignals(true);
    switch (mUnit) {
    case SA_DBM:
        ui->value_Unit->setCurrentIndex(0);
        break;
    case SA_DBV:
        ui->value_Unit->setCurrentIndex(1);
        break;
    case SA_DBMV:
        ui->value_Unit->setCurrentIndex(2);
        break;
    case SA_DBUV:
        ui->value_Unit->setCurrentIndex(3);
        break;
    case SA_VOLT:
        ui->value_Unit->setCurrentIndex(4);
        break;
    case SA_WATTS:
        ui->value_Unit->setCurrentIndex(5);
        break;
    default:
        break;
    }
    ui->value_Unit->blockSignals(false);
    return ;
}
/**
 * @brief  Refresh trigger type information.
 * @param  void.
 * @author Tony
 * @since 2018-01-04
*/
void SA_Dialog_AllSetup::refreshTrigger()
{
    qint32 mode;
    qreal value;
    qint32 status;
    QString strInfo;
    mode = mControl->getTriggerMode();
    ui->value_TriggerSource->blockSignals(true);
    ui->value_TriggerSource->setCurrentIndex(mode);
    ui->value_TriggerSource->blockSignals(false);

    ui->Trigger_SubMenu->setCurrentIndex(mode);
    switch (mode) {
    case SA_TRIGGER_FREE_RUN:

        break;
    case SA_TRIGGER_VIDEO:
        value = mControl->getTriggerLevel(SA_TRIGGER_VIDEO);
        strInfo = mControl->globalUserVariable->amptTransformToQstring(SA_DBM,value);
        ui->value_Video_Level->setText(strInfo);

        status = mControl->getTriggerSlope(SA_TRIGGER_VIDEO);
        if(status){
            ui->pb_Video_Pos->setChecked(true);
        }else{
            ui->pb_Video_Neg->setChecked(true);
        }

        status = mControl->getTriggerDelayStatus(SA_TRIGGER_VIDEO);
        ui->value_Video_DelayOn->setChecked(status);
        if(status)
            ui->value_Video_DelayOn->setText("On");
        else
            ui->value_Video_DelayOn->setText("Off");
        value = mControl->getTriggerDelayValue(SA_TRIGGER_VIDEO);
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->value_Video_DelayTime->setText(strInfo);
        break;
    case SA_TRIGGER_EXTERNAL:
        value = mControl->getTriggerLevel(SA_TRIGGER_EXTERNAL);
        strInfo = mControl->globalUserVariable->amptTransformToQstring(SA_VOLT,value);
        ui->value_External_Level->setText(strInfo);

        status = mControl->getTriggerSlope(SA_TRIGGER_EXTERNAL);
        if(status){
            ui->pb_External_Pos->setChecked(true);
        }else{
            ui->pb_External_Neg->setChecked(true);
        }

        status = mControl->getTriggerDelayStatus(SA_TRIGGER_EXTERNAL);
        ui->value_External_DelayOn->setChecked(status);
        if(status) ui->value_External_DelayOn->setText("On");
        else ui->value_External_DelayOn->setText("Off");
        value = mControl->getTriggerDelayValue(SA_TRIGGER_EXTERNAL);
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->value_External_DelayTime->setText(strInfo);
        break;
    case SA_TRIGGER_PERIODIC_TIMER:
        value = mControl->getTriggerPerTimer();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->value_Peri_Timer->setText(strInfo);

        status = mControl->getTriggerDelayStatus(SA_TRIGGER_PERIODIC_TIMER);
        ui->value_Peri_DelayOn->setChecked(status);
        if(status) ui->value_Peri_DelayOn->setText("On");
        else ui->value_Peri_DelayOn->setText("Off");
        value = mControl->getTriggerDelayValue(SA_TRIGGER_PERIODIC_TIMER);
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->value_Peri_DelayTime->setText(strInfo);
        break;
    case SA_TRIGGER_RF_BURST:
        value = mControl->getTriggerLevel(SA_TRIGGER_RF_BURST);
        strInfo = mControl->globalUserVariable->amptTransformToQstring(SA_DBM,value);
        ui->value_RFBurst_Level->setText(strInfo);

        status = mControl->getTriggerSlope(SA_TRIGGER_RF_BURST);
        if(status){
            ui->pb_RFBurst_Pos->setChecked(true);
        }else{
            ui->pb_RFBurst_Neg->setChecked(true);
        }

        status = mControl->getTriggerDelayStatus(SA_TRIGGER_RF_BURST);
        ui->value_RFBurst_DelayOn->setChecked(status);
        if(status) ui->value_RFBurst_DelayOn->setText("On");
        else ui->value_RFBurst_DelayOn->setText("Off");
        value = mControl->getTriggerDelayValue(SA_TRIGGER_RF_BURST);
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->value_RFBurst_DelayTime->setText(strInfo);
        break;
    case SA_TRIGGER_GPS:

        break;
    default:
        break;
    }

    return ;
}

/**
 * @brief  Refresh trace information.
 * @param  void.
 * @author Tony
 * @since 2018-01-04
*/
void SA_Dialog_AllSetup::refreshTrace()
{
    qint32 status;
    qreal value;
    QString strGab;
    qint32 mTraceIndex,mTraceType,mDetectors;
    mTraceIndex = mTrIndex;
    mTraceType = mControl->getTraceType(mTraceIndex);
    mDetectors = mControl->getDetectorMode();
    ui->value_Trace->blockSignals(true);
    ui->value_TraceType->blockSignals(true);
    ui->value_Detectors->blockSignals(true);
    ui->value_Trace->setCurrentIndex(mTraceIndex);
    ui->value_TraceType->setCurrentIndex(mTraceType);
    if(mDetectors == 0) mDetectors = 4;
    ui->value_Detectors->setCurrentIndex(mDetectors);
    ui->value_Trace->blockSignals(false);
    ui->value_TraceType->blockSignals(false);
    ui->value_Detectors->blockSignals(false);
    status = mControl->getTraceViewStatus(mTraceIndex);
    ui->value_Detectors->setEnabled(true);
    for(qint32 i=0;i<MARKER_TOTAL_CNT;i++)
    {
        if(mControl->getMarkerNoiseStatus(i) == SA_ON)
        {
            ui->value_Detectors->setEnabled(false);
            break;
        }
    }
    //Trace view
    if(status == SA_ON)
    {
        ui->btn_TraceView->setChecked(true);
    }else
    {
        ui->btn_TraceView->setChecked(false);
    }
    //Average  on or off
    status = mControl->getTraceAverageStatus(mTraceIndex);
    if(status == SA_ON)
    {
        ui->btn_Average->setChecked(true);
    }else
    {
        ui->btn_Average->setChecked(false);
    }
    //Average value
    value = mControl->getTraceAverageCount(mTraceIndex);
    strGab =QString::number(value);
    ui->value_Average->setText(strGab);
    return ;
}
/**
 * @brief  Refresh marker information.
 * @param  void.
 * @author Tony
 * @since 2018-01-04
*/
void SA_Dialog_AllSetup::refreshMarker()
{
    qint32 mMarkerType,mMarkerIndex;
    qint32 status;
    //Marker Select
    mMarkerIndex = mControl->getMarkerSelect();
    ui->value_MarkerSelect->blockSignals(true);
    ui->value_MarkerSelect->setCurrentIndex(mMarkerIndex);
    ui->value_MarkerSelect->blockSignals(false);
    //Marker View
    status = mControl->getMarkerViewStatus(mMarkerIndex);
    if(status == SA_ON)
    {
        ui->btn_MarkerView->setChecked(true);
    }
    else
    {
        ui->btn_MarkerView->setChecked(false);
    }
    //Marker Type
    mMarkerType = mControl->getMarkerType(mMarkerIndex);
    if(mMarkerType == REF)
    {
        ui->Marker_Normal->setChecked(true);
    }else if(mMarkerType == DELTA)
    {
        ui->Marker_Delta->setChecked(true);
    }
    //Marker Freq count
    status = mControl->getMarkerFreqCountStatus(mMarkerIndex);
    if(status == SA_ON)
    {
        ui->btn_FreqCount->setChecked(true);
    }else
    {
        ui->btn_FreqCount->setChecked(false);
    }
    //Noise Marker
    status = mControl->getMarkerNoiseStatus(mMarkerIndex);
    if(status == SA_ON)
    {
        ui->btn_NoiseMarker->setChecked(true);
    }else
    {
        ui->btn_NoiseMarker->setChecked(false);
    }
    return ;
}
/**
 * @brief  Refresh Limit information.
 * @param  void.
 * @author Tony
 * @since 2018-03-27
*/
void SA_Dialog_AllSetup::refreshLimit()
{
    qreal value;
    qint32 index,status;
    //Limit select
    index = mControl->getLimitSelect();
    ui->value_LimitSelect->blockSignals(true);
    ui->value_LimitSelect->setCurrentIndex(index);
    ui->value_LimitSelect->blockSignals(false);
    //Limit view
    status = mControl->getLimitLineStatus();
    if(status == SA_ON)
    {
        ui->Value_Limit_Toggle->setChecked(true);
    }else
    {
        ui->Value_Limit_Toggle->setChecked(false);
    }

    //limit test
    status = mControl->getLimitTestStatus();
    if(status == SA_ON)
    {
        ui->Value_Limit_Test->setChecked(true);
    }else
    {
        ui->Value_Limit_Test->setChecked(false);
    }
    //limit edge toggle
    status = mControl->getLimitEdgeStatus();
    if(status == SA_ON)
    {
        ui->value_Limit_Edge_Toggle->setChecked(true);
    }else
    {
        ui->value_Limit_Edge_Toggle->setChecked(false);
    }
    //Limit edge value
    value = mControl->getLimitEdgeValue();
    ui->Value_Limit_Edge->setText(QString::number(value,'f',2)+" dB");
    //limit type
    status = mControl->getLimitType();
    if(status == UPPER)
        ui->btn_Upper->setChecked(true);
    else
        ui->btn_Lower->setChecked(true);



    return ;
}



QString SA_Dialog_AllSetup::amptTransformToQstring(qint32 unit,qreal value)
{
    QString strvalue;
    char str[20];
    switch (unit) {
    case SA_DBM:
        strvalue = QString::number(value, 'f', 2) + " dBm";  // Double to String
        break;
    case SA_DBMV:
        strvalue = QString::number((value + dBmVFix), 'f', 2) + " dBmV" ;  // Double to String
        break;
    case SA_DBUV:
        strvalue = QString::number((value + dBuVFix), 'f', 2) + " dBuV";  // Double to String
        break;
    case SA_VOLT:
        dbmToVoltCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case SA_WATTS:
        dbmToWattsCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case SA_DBV:
        strvalue = QString::number((value + dBVFix), 'f', 2) + " dBV" ;  // Double to String
        break;
    default:
        break;
    }
    return strvalue;
}

//Tony 1022 Add
void SA_Dialog_AllSetup::dbmToVoltCalculatorAndDisplayFunc(char *label, double _level)
{
    double voltGab = 0.;
    double calculator = 0.;

    calculator = pow(10, _level / 10.);
    voltGab = 1000000. * pow(50 * calculator * 0.001, 0.5);//uv

    //Johnson 0919 Change
    if(voltGab >= 1000000000.){
        sprintf(label, "%.2f kV", (double) voltGab / 1000000000.);
    }
    else if (/*_level <= 20. &&*/ voltGab >= 1000000.) {
        sprintf(label, "%.2f V", (double) voltGab / 1000000.);
    } else if (voltGab < 1000000. && voltGab >= 1000.) {
        sprintf(label, "%.2f mV", (double) voltGab / 1000.);
    } else if (voltGab < 1000. && voltGab >= 1.) {
        sprintf(label, "%.2f uV", (double) voltGab);
    } else if (voltGab < 1. && voltGab >= 0.001) {
        sprintf(label, "%.2f nV", (double) voltGab * 1000);
    } else if (voltGab < 0.001 && voltGab >= 0.000001) {
        sprintf(label, "%.2f pV", (double) voltGab * 1000000.);
    } else if (voltGab < 0.000001 && voltGab >= 0.000000001) {
        sprintf(label, "%.2f fV", (double) voltGab * 1000000000.);
    } else if (voltGab < 0.000000001 && voltGab >= 0.000000000001) {
        sprintf(label, "%.2f aV", (double) voltGab * 1000000000000.);
    } else if (voltGab < 0.000000000001 && voltGab >= 0.000000000000001) {
        sprintf(label, "%.2f zV", (double) voltGab * 1000000000000000.);
    } else if (voltGab < 0.000000000000001 && voltGab >= 0.000000000000000001) {
        sprintf(label, "%.2f yV", (double) voltGab * 1000000000000000000.);
    } else {
        sprintf(label, "%.2f", (double) voltGab * 1000000000000000000000.);
    }
    return;
}
//Tony 1022 Add
void SA_Dialog_AllSetup::dbmToWattsCalculatorAndDisplayFunc(char *label, double _level)
{
    double wattsGab = 0.;

    wattsGab = pow(10, _level / 10.);

    if (wattsGab >= 1000) {						// W
        sprintf(label, "%.2f W", (double)wattsGab / 1000.0);
    }  else if (wattsGab >= 1) {					// mW
        sprintf(label, "%.2f mW", (double)wattsGab);
    }  else if (wattsGab >= 0.001) {				// uW
        sprintf(label, "%.2f uW", (double)wattsGab * 1000.0);
    }  else if (wattsGab >= 0.000001) {			// nW
        sprintf(label, "%.2f nW", (double)wattsGab * 1000000.0);
    } else if (wattsGab >= 0.000000001) {			// pW
        sprintf(label, "%.2f pW", (double)wattsGab * 1000000000.0);
    } else if (wattsGab >= 0.000000000001) {		// fW
        sprintf(label, "%.2f fW", (double)wattsGab * 1000000000000.0);
    } else {                                                    	// aW
        sprintf(label, "%.2f aW", (double)wattsGab * 1000000000000000.0);
    }
}

void SA_Dialog_AllSetup::on_value_Unit_currentIndexChanged(qint32 index)
{
    switch (index) {
    case 0:
        mControl->setAmpUnit(SA_DBM);
        break;
    case 1:
        mControl->setAmpUnit(SA_DBV);
        break;
    case 2:
        mControl->setAmpUnit(SA_DBMV);
        break;
    case 3:
        mControl->setAmpUnit(SA_DBUV);
        break;
    case 4:
        mControl->setAmpUnit(SA_VOLT);
        break;
    case 5:
        mControl->setAmpUnit(SA_WATTS);
        break;
    default:
        break;
    }
    initDisplay();
    return ;
}


void SA_Dialog_AllSetup::on_Sweep_Conti_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setSweepType(!checked);
        mControl->setSuspendFunc(0);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_Sweep_Single_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setSweepType(checked);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_RBW_Auto_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setAutoRbwStatus(checked);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_RBW_Manual_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setAutoRbwStatus(!checked);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_VBW_Auto_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setAutoVbwStatus(checked);
    }
    initDisplay();
    return ;
}

void SA_Dialog_AllSetup::on_VBW_Manual_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setAutoVbwStatus(!checked);
    }
    initDisplay();
    return;
}
//Limit
void SA_Dialog_AllSetup::on_value_LimitSelect_currentIndexChanged(qint32 index)
{
    mControl->setLimitSelect(index);
    refreshLimit();
    return ;
}
//Trace
void SA_Dialog_AllSetup::on_value_Trace_currentIndexChanged(qint32 index)
{
    //mControl->setTraceSelect(index);
    mTrIndex = index;
    if(SA_ON == mControl->getTraceViewStatus(mTrIndex))
    {
       mControl->setTraceSelect(mTrIndex);
    }
    refreshTrace();
    return ;
}

void SA_Dialog_AllSetup::on_value_TraceType_currentIndexChanged(qint32 index)
{
    switch (index)
    {
    case 0:
        mControl->setTraceType(SA_CLEAR_WRITE,mTrIndex);
        break;
    case 1:
        mControl->setTraceType(SA_MAX_HOLD,mTrIndex);
        break;
    case 2:
        mControl->setTraceType(SA_MIN_HOLD,mTrIndex);
        break;
    case 3:
        mControl->setTraceType(SA_VIEW,mTrIndex);
        break;
    case 4:
        mControl->setTraceType(SA_TRACE_AVE,mTrIndex);
        break;
    default:
        break;
    }
    refreshTrace();
    return ;
}

void SA_Dialog_AllSetup::on_value_Detectors_currentIndexChanged(qint32 index)
{
    switch (index)
    {
    case 0:
        mControl->setDetectorMode(SA_AUTO_DETECTOR);
        break;
    case 1:
        mControl->setDetectorMode(SA_POSITIVE_PEAK);
        break;
    case 2:
        mControl->setDetectorMode(SA_NEGATIVE_PEAK);
        break;
    case 3:
        mControl->setDetectorMode(SA_SAMPLE);
        break;
    case 4:
        mControl->setDetectorMode(SA_COMMON);
        break;
    case 5:
        mControl->setDetectorMode(SA_AVERAGE_VOTAGE);
        break;
    case 6:
        mControl->setDetectorMode(SA_RMS);
        break;
    default:
        break;
    }
    return ;
}

void SA_Dialog_AllSetup::on_value_MarkerSelect_currentIndexChanged(qint32 index)
{
    switch (index)
    {
    case 0:
        mControl->setMarkerSelect(SA_M1);
        break;
    case 1:
        mControl->setMarkerSelect(SA_M2);
        break;
    case 2:
        mControl->setMarkerSelect(SA_M3);
        break;
    case 3:
        mControl->setMarkerSelect(SA_M4);
        break;
    case 4:
        mControl->setMarkerSelect(SA_M5);
        break;
    case 5:
        mControl->setMarkerSelect(SA_M6);
        break;
    default:
        break;
    }
    //Tony 19-12-19
    if(!mControl->getMarkerFreqCountStatus())
    {
        //ui->pb_FreqCount->setChecked(false);
        mControl->setMarkerFreqCountStatus(SA_OFF);
    }
    else
    {
        //ui->pb_FreqCount->setChecked(true);
        mControl->setMarkerFreqCountStatus(SA_ON);

        mControl->setMarkerViewStatus(SA_ON);
    }
    mControl->setMarkerNoiseStatus(mControl->getMarkerNoiseStatus());
    refreshMarker();
    return ;
}

void SA_Dialog_AllSetup::mHide()
{
    globalUserVariable->PrimaryAction = initialPAction;
    hide();
    digitInputClose();
    channelInputClose();
    emit mDialogHide();
}
void SA_Dialog_AllSetup::mShow()
{
    //setProperty("status",qssMode[mControl->GetDisplayMode()]);
    //setStyle(QApplication::style());
    qint32 mMode = mControl->getCurrentMode();
    mTrIndex = mControl->getTraceSelect();
    lastWidget = curWidget;
    ui->stackedWidget->setCurrentIndex(1);
        if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode /*||\
                SA_SPECTRUM_EMISSION_MASK_MODE == mMode*/)
    {
        curWidget = SA_ALLSET_FREQSTEP;
    }
    else
    {
        curWidget = SA_ALLSET_CENTERFREQ;
    }
    initWidget();
    initDisplay();
    show();
}
void SA_Dialog_AllSetup::on_pb_cancel_clicked()
{
    mHide();
    return;
}

void SA_Dialog_AllSetup::on_Marker_Select_clicked()
{
    lastWidget = curWidget;
    curWidget = SA_ALLSET_MARKERSELECT;
    refreshFocus();
    ui->value_MarkerSelect->showPopup();
    return;
}

void SA_Dialog_AllSetup::on_Scale_Unit_clicked()
{
    lastWidget = curWidget;
    curWidget = SA_ALLSET_UNIT;
    refreshFocus();
    ui->value_Unit->showPopup();
    return;
}


void SA_Dialog_AllSetup::on_RBW_Freq_clicked()
{
    lastWidget = curWidget;
    curWidget = SA_ALLSET_RBW;
    refreshFocus();
    ui->value_RBW->showPopup();
    return;
}

void SA_Dialog_AllSetup::on_VBW_Freq_clicked()
{
    lastWidget = curWidget;
    curWidget = SA_ALLSET_VBW;
    refreshFocus();
    ui->value_VBW->showPopup();
    return;
}

void SA_Dialog_AllSetup::on_VBW_RBW_clicked()
{
    lastWidget = curWidget;
    curWidget = SA_ALLSET_VBW_RBW;
    refreshFocus();
    ui->value_VBW_RBW->showPopup();
    return;
}

void SA_Dialog_AllSetup::on_Trace_Select_clicked()
{
    lastWidget = curWidget;
    curWidget = SA_ALLSET_TRACESELECT;
    refreshFocus();
    ui->value_Trace->showPopup();
    return;
}

void SA_Dialog_AllSetup::on_Trace_Type_clicked()
{
    lastWidget = curWidget;
    curWidget = SA_ALLSET_TRACETYPE;
    refreshFocus();
    ui->value_TraceType->showPopup();
    return;
}

void SA_Dialog_AllSetup::on_Limit_Select_clicked()
{
    lastWidget = curWidget;
    curWidget = SA_ALLSET_LIMIT;
    refreshFocus();
    ui->value_LimitSelect->showPopup();
    return;
}

void SA_Dialog_AllSetup::on_Detectors_clicked()
{
    lastWidget = curWidget;
    curWidget = SA_ALLSET_DETECTORS;
    refreshFocus();
    if(ui->value_Detectors->isEnabled())
        ui->value_Detectors->showPopup();
    return;
}

/**
 * @brief  Key press Event.
 * @param  event
 * @author Tony
 * @since 2019-03-29
 **/
void SA_Dialog_AllSetup::keyPressEvent(QKeyEvent *event)
{
  qint32 keyvalue = event->key();
  if(event->key() == Qt::Key_PowerOff)
  {
      if(!event->isAutoRepeat())
          QApplication::sendEvent(this->parent(),event);
      return;
  }
  switch (keyvalue) {
  case Qt::Key_F3:
  case Qt::Key_F4:
      if(mInputDialog)
          digitInputClose();
      break;
  case Qt::Key_Escape:
      if(mInputDialog)
          digitInputClose();
      else if(mChannelInput)
      {
          channelInputClose();
      }
      else
          mHide();
      return;
  case Qt::Key_Shift:
      if(globalUserVariable->bShiftKeyPressed)
          globalUserVariable->bShiftKeyPressed = false;
      else
          globalUserVariable->bShiftKeyPressed = true;
      mHide();
      return;
  default:
      break;
  }
  if(mInputDialog)
  {
      QCoreApplication::sendEvent(mInputDialog, event);
      return;
  }
  if(!mWidgetList.contains(curWidget) || curWidget < 0)
      return;
  switch(keyvalue){
  case Qt::Key_0:
  case Qt::Key_1:
  case Qt::Key_2:
  case Qt::Key_3:
  case Qt::Key_4:
  case Qt::Key_5:
  case Qt::Key_6:
  case Qt::Key_7:
  case Qt::Key_8:
  case Qt::Key_9:
  case Qt::Key_F2:
  case Qt::Key_Minus:
  case Qt::Key_Period:
      if(mInputWidget.contains(curWidget))
      {
          if(!mInputDialog) mWidgetList.value(curWidget)->clicked();
          if(mInputDialog)  QCoreApplication::sendEvent(mInputDialog, event);
      }
      break;
  case Qt::Key_F4:
      getKnobValue(CLOCKWISE);
      break;
  case Qt::Key_F3:
      getKnobValue(ANTICLOCKWISE);
      break;
  case Qt::Key_Up:
  case Qt::Key_Left:
      //focusControl(SA_UP);
      break;
  case Qt::Key_Down:
  case Qt::Key_Right:
      //focusControl(SA_DOWN);
      break;
  default:
      if(mInputDialog) QApplication::sendEvent(mInputDialog,event);
      break;
  }
  return ;
}
void SA_Dialog_AllSetup::getKnobValue(qint32 mode)
{
    qint32 intVal,intStep;
    qreal mFreqStep,mFreqValue;
    qreal mStep,mValue;
    mFreqStep = mControl->getCFFreq();
    switch (curWidget)
    {
    case SA_ALLSET_CENTERFREQ:
        mFreqValue = mControl->getCenterFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        //if(mFreqValue < 0) mFreqValue=0;
        mControl->setCenterFreq(mFreqValue);
        break;
    case SA_ALLSET_STARTFREQ:
        mFreqValue = mControl->getStartFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        //if(mFreqValue < 0) mFreqValue=0;
         mControl->setStartFreq(mFreqValue);
        break;
    case SA_ALLSET_STOPFREQ:
        mFreqValue = mControl->getStopFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        //if(mFreqValue < 0) mFreqValue=0;
        mControl->setStopFreq(mFreqValue);
        break;
    case SA_ALLSET_FREQSTEP:

        break;
    case SA_ALLSET_FREQOFFSET:
        mFreqValue = mControl->getFreqOffset();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        if(mFreqValue < 0) mFreqValue=0;
        mControl->setFreqOffset(mFreqValue);
        break;
    case SA_ALLSET_SPAN:
        mFreqValue = mControl->getSpan();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        if(mFreqValue < 0) mFreqValue=0;
        mControl->setSpan(mFreqValue);
        break;
    case SA_ALLSET_CHANNELNUM:
        intStep = mControl->getChannelNumStep();
        intVal = mControl->getChannelNumber();
        if(mControl->getCHStandard()<0)
        {
            return;;
        }
        if(mode)
            intVal += intStep;
        else
            intVal -= intStep;
        if(intVal < 0) intVal=0;
        mControl->setChannelNumber(intVal);
        break;
    case SA_ALLSET_CHANNELSTEP:
        intStep =1;
        intVal = mControl->getChannelNumStep();
        if(mode)
            intVal += intStep;
        else
            intVal -= intStep;
        if(intVal < 0) intVal=0;
        mControl->setChannelNumStep(intVal);
        break;
    case SA_ALLSET_REFLEVEL:
        mStep = REF_STEP;
        mValue=mControl->getRefLevel();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setRefLevel(mValue);
        break;
    case SA_ALLSET_REFOFFSET:
        mStep = REF_STEP;
        mValue=mControl->getRefOffset();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setRefOffset(mValue);
        break;
    case SA_ALLSET_DIVISION:
        mStep = SCALE_STEP;
        mValue=mControl->getScaleDiv();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setScaleDiv(mValue);
        break;
    case SA_ALLSET_ATTENVALUE:
        if(mControl->getAttenStatus())
            mControl->setAttenStatus(SA_MANUAL);
        mStep = ATTEN_STEP;
        mValue=mControl->getAttenValue();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setAttenValue(mValue);
        break;
    case SA_ALLSET_SWEEPTIME:
        mValue = mControl->getSweepTime();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        if(mValue < 0) mValue=0;
        mControl->setSweepTime(mValue);
        break;
    case SA_ALLSET_AVERAGEVALUE:
        mStep = 1;
        mValue=mControl->getTraceAverageCount();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setTraceAverageCount(mValue,mTrIndex);
        break;
    case SA_ALLSET_LIMITEDGEVALUE:
        mStep = 0.1;
        mValue = mControl->getLimitEdgeValue();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        if(mValue < 0)
            mValue = 0;
        mControl->setLimitEdgeValue(mValue);
        break;
    }

    initDisplay();
}

qreal SA_Dialog_AllSetup::getTimeStep(qreal time)
{
    qreal mStep;
    if((time * SA_KHZ ) < 1)//ns
    {
        mStep = (qreal)1/SA_MHZ ;//Johnson 190918
    }
    else if((time * SA_KHZ) >= 1 && time < 1)//us
    {
        mStep = (qreal)1/SA_KHZ ;//Johnson 190918
    }
    else if(time >= 1 && time < SA_KHZ)//ms
    {
        mStep = 1 ;
    }
    else if(time >= SA_KHZ)//s
    {
        mStep = SA_KHZ ;
    }
    return mStep;
}
void SA_Dialog_AllSetup::focusControl(qint32 dir)
{
    qint32 index;
    if(dir == SA_UP)
    {
        index = curWidget - 1;
        if(index == 44)
        {
            ui->stackedWidget->setCurrentIndex(1);
        }
    }
    else if(dir == SA_DOWN)
    {
        index = curWidget + 1;
        if(index == 45)
        {
            ui->stackedWidget->setCurrentIndex(2);
        }
    }

    if(index < 0)
    {
        index = 0;
    }else if(index >= SA_ALLSET_COUNT)
    {
        index = SA_ALLSET_COUNT;
    }
    lastWidget = curWidget;
    curWidget = index;

    refreshFocus();
}
void SA_Dialog_AllSetup::refreshFreq()
{
    QString strGab,strTmp;
    qreal   value,offsetvalue;
    qint32  minus = 0;

    //Center Freq
    value = mControl->getCenterFreq();
    if(value < 0)
    {
        minus = 1;
        value *= -1;
    }
    strGab = globalUserVariable->freqValueToQstring(value);
    if(minus)
    {
        strGab = QString("-%1").arg(strGab);
    }
    ui->value_CenterFreq->setText(strGab);
    //Start Freq
    value = mControl->getStartFreq();
    if(value < 0)
    {
        minus = 1;
        value *= -1;
    }
    strGab = globalUserVariable->freqValueToQstring(value);
    if(minus)
    {
        strGab = QString("-%1").arg(strGab);
    }
    ui->value_StartFreq->setText(strGab);
    //Stop Freq
    value = mControl->getStopFreq();
    if(value < 0)
    {
        minus = 1;
        value *= -1;
    }
    strGab = globalUserVariable->freqValueToQstring(value);
    if(minus)
    {
        strGab = QString("-%1").arg(strGab);
    }
    ui->value_StopFreq->setText(strGab);
    //Freq Step
    value = mControl->getCFFreq();
    strGab = globalUserVariable->freqValueToQstring(value);
    ui->value_FreqStep->setText(strGab);
    //span
    value = mControl->getSpan();
    strGab = globalUserVariable->freqValueToQstring(value);
    ui->value_Span->setText(strGab);
    //Freq Offset
    value = mControl->getFreqOffset();
    if(value < 0)
    {
        minus = 1;
        value *= -1;
    }
    strGab = globalUserVariable->freqValueToQstring(value);
    if(minus)
    {
        strGab = QString("-%1").arg(strGab);
    }
    ui->value_FreqOffset->setText(strGab);
    //channel standard
    if(globalUserVariable->gTecIndex<0)
    {
        strGab = "None";
    }else
    {
        strTmp = QString(mChStand[globalUserVariable->gTecIndex].name);
        strGab = strTmp;
    }
    ui->value_Channel->setText(strGab);
    //channel number
    if(globalUserVariable->gTecIndex<0)
    {
        strGab = "None";
    }else
    {
        value = mControl->getChannelNumStep();
        strGab = QString::number(value);
        value = globalUserVariable->CalculateChannelNum();
        strGab = QString::number(value);
    }
    ui->value_ChannelNum->setText(strGab);
    //channel step
//    if(globalUserVariable->gTecIndex<0)
//    {
//        strGab = "None";
//    }else
//    {
//        value = globalUserVariable->gChannelStep;
//        strGab = globalUserVariable->freqValueToQstring(value);
//    }
    value = mControl->getChannelNumStep();
    strGab = QString::number(value);
    ui->value_ChannelStep->setText(strGab);

    if(mControl->getCommuDirection() == SA_UPLINK)
    {
        ui->Channel_Uplink->setChecked(true);
    }else
    {
        ui->Channel_Downlink->setChecked(true);
    }
    if(globalUserVariable->gZeroSpanAction == SA_ON)
    {
        if(ui->Trigger_SubMenu->isHidden())
        {
            ui->Trigger_SubMenu->setVisible(true);
            ui->Trigger_Source->setVisible(true);
        }
    }else
    {
        if(!ui->Trigger_SubMenu->isHidden())
        {
            ui->Trigger_SubMenu->setVisible(false);
            ui->Trigger_Source->setVisible(false);
        }
    }
}

void SA_Dialog_AllSetup::refreshAmpt()
{
    QString strGab;
    qreal   value;
    qint32  status;
    //Ref Level
    value = mControl->getRefLevel();
    strGab = amptTransformToQstring(mControl->getAmpUnit(),value);
    ui->value_Ref_Level->setText(strGab);
    //Ref Offset
    value = mControl->getRefOffset();
    strGab = QString::number(value,'f',2)+" dB";
    ui->value_RefOffset->setText(strGab);
    //Scale Div
    value = mControl->getScaleDiv();
    strGab = QString::number(value,'f',2)+" dB";
    ui->value_Scale->setText(strGab);
    //Atten Value
    value = mControl->getAttenValue();
    strGab = QString::number(value)+" dB";
    ui->value_AttenValue->setText(strGab);
    //Atten Auto
    status = mControl->getAttenStatus();
    if(status == SA_AUTO)
    {
        ui->Atten_Auto->setChecked(true);
    }else if(status == SA_MANUAL)
    {
        ui->Atten_Manual->setChecked(true);
    }
    //Unit
    refreshUnit();
    //Preamp status
    status = mControl->getPreampStatus();
    ui->btn_Preamp->setChecked(status);

}

void SA_Dialog_AllSetup::refreshSweepTime()
{
    QString strGab;
    qreal   value;
    qint32  status;
    //Sweep Time
    value = mControl->getSweepTime();
    strGab = globalUserVariable->TimeTransformToQstring(value);
    ui->value_SweepTime->setText(strGab);
    //Auto Sweep Time
    status = mControl->getAutoSweepTimeStatus();
    if(status == SA_AUTO)
    {
        ui->SweepTime_Auto->setChecked(true);
    }else if(status == SA_MANUAL)
    {
        ui->SweepTime_Manual->setChecked(true);
    }
    //Sweep Type
    value = mControl->getSweepType();
    if(value == SA_CONT)
    {
        ui->Sweep_Conti->setChecked(true);
    }else if(value ==SA_SINGLE)
    {
        ui->Sweep_Single->setChecked(true);
    }
}

void SA_Dialog_AllSetup::refreshBW()
{
    qint32  status;

    qreal VbwtoRbw;
    qint32 mRBW,mVBW;
    qint32 indexRBW,indexVBW,indexRatio;
    if(mControl->getCurrentMode() == SA_SPECTRUM_EMISSION_MASK_MODE){
        mRBW = mControl->getSpecEMRefRbw();
    }else
    {
        mRBW = mControl->getRbwValue();
    }

    mVBW = mControl->getVbwValue();
    VbwtoRbw = mControl->getVbwtoRbw();
    indexRBW = RbwVbwCompare(mRBW);
    indexVBW = RbwVbwCompare(mVBW);
    indexRatio = RatioCompare(VbwtoRbw);
    if(indexRBW < 0)
    {
        indexRBW = sizeof(SA_u32BWTable) -1;
    }
    if(indexVBW < 0)
    {
        indexVBW = sizeof(SA_u32BWTable) -2;
    }
    ui->value_RBW->blockSignals(true);
    ui->value_VBW->blockSignals(true);
    ui->value_VBW_RBW->blockSignals(true);
    ui->value_RBW->setCurrentIndex(indexRBW);
    ui->value_VBW->setCurrentIndex(indexVBW-1);
    ui->value_VBW_RBW->setCurrentIndex(indexRatio);
    ui->value_RBW->blockSignals(false);
    ui->value_VBW->blockSignals(false);
    ui->value_VBW_RBW->blockSignals(false);

    status = mControl->getRbwStatus();
    if(status == SA_AUTO)
    {
        ui->RBW_Auto->setChecked(true);
    }else
    {
        ui->RBW_Manual->setChecked(true);
    }

    status = mControl->getVbwStatus();
    if(status == SA_AUTO)
    {
        ui->VBW_Auto->setChecked(true);
    }else
    {
        ui->VBW_Manual->setChecked(true);
    }
}

qint32 SA_Dialog_AllSetup::RatioCompare(qreal ratio)
{
    qreal min,max;
    qint32 mSize = ui->value_VBW_RBW->count();
    max = ui->value_VBW_RBW->itemText(0).toDouble();
    min = ui->value_VBW_RBW->itemText(mSize - 1).toDouble();
    if(ratio >= max)
    {
        return 0;
    }else if(ratio <= min)
    {
        return mSize - 1;
    }
    for(qint32 i = 0;i < mSize-2; i++)
    {
        max = ui->value_VBW_RBW->itemText(i).toDouble();
        min = ui->value_VBW_RBW->itemText(i+1).toDouble();
        if(ratio < max && 2 * ratio >= (max + min))
            return i;
        else if(2 * ratio < (max + min) &&  ratio >= min)
            return i+1;
    }
    return 0;
}

qint32 SA_Dialog_AllSetup::RbwVbwCompare(qint32 value)
{
    qint32 mSize = sizeof(SA_u32BWTable)/4;
    for(qint32 i = 0;i < mSize ; i++)
    {
        if(SA_u32BWTable[i] == value)
            return i;
    }

    return -1;

}

void SA_Dialog_AllSetup::refreshFocus()
{
    QString strQss;
    if(lastWidget<0 || curWidget <0)
        return;
    strQss = QString("#%1{border:0px flat rgba(162,115,0,1);}").arg(mWidgetList.value(lastWidget)->objectName());
    mWidgetList.value(lastWidget)->setStyleSheet(strQss);

    strQss = QString("#%1{border:2px solid rgba(162,115,0,1);}").arg(mWidgetList.value(curWidget)->objectName());
    mWidgetList.value(curWidget)->setStyleSheet(strQss);

    mWidgetList.value(curWidget)->setFocus();
    this->repaint();
}
void SA_Dialog_AllSetup::on_value_Detectors_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_DETECTORS;
    refreshFocus();
}
void SA_Dialog_AllSetup::on_value_Unit_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_UNIT;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_value_RBW_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_RBW;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_value_VBW_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_VBW;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_value_VBW_RBW_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_VBW_RBW;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_value_Trace_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_TRACESELECT;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_value_TraceType_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_TRACETYPE;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_value_MarkerSelect_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_MARKERSELECT;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_value_LimitSelect_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_LIMITSELECT;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_Channel_Uplink_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setCommuDirection(SA_UPLINK);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_Channel_Downlink_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setCommuDirection(SA_DOWNLINK);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_btn_Preamp_clicked(bool checked)
{
    digitInputClose();
    mControl->setPreampStatus(checked);
    refreshFreq();
    return ;
}

void SA_Dialog_AllSetup::on_btn_Preamp_toggled(bool checked)
{
    if(checked)
    {
        ui->btn_Preamp->setText("On");
    }else
    {
        ui->btn_Preamp->setText("Off");
    }
}

void SA_Dialog_AllSetup::on_value_RBW_currentIndexChanged(qint32 index)
{
    qint32 mSize = sizeof(SA_u32BWTable)/4;
    if(index >= mSize)
    {
        return;
    }
    mControl->setAutoRbwStatus(false);

    if(mControl->getCurrentMode() == SA_SPECTRUM_EMISSION_MASK_MODE){
        mControl->setSpecEMRefRbw(SA_u32BWTable[index]);
    }else
    {
        mControl->setRbwValue(SA_u32BWTable[index]);
    }


    refreshBW();
}

void SA_Dialog_AllSetup::on_value_VBW_currentIndexChanged(qint32 index)
{
    qreal vbw;//rbw,ratio;
    qint32 mSize = sizeof(SA_u32BWTable)/4;
    if(index >= (mSize - 1))
    {
        return;
    }
    vbw = SA_u32BWTable[index+1];
    //rbw = mControl->getRbwValue();
    //ratio = (qreal)vbw/rbw;
    mControl->setAutoVbwStatus(false);
    mControl->setVbwValue(vbw);
    //mControl->setVbwtoRbw(ratio);
    refreshBW();
}

void SA_Dialog_AllSetup::on_value_VBW_RBW_currentIndexChanged(qint32 index)
{
    qreal ratio,RBW,VBW ;
    QString text;
    text = ui->value_VBW_RBW->currentText();
    ratio = text.toDouble();
    RBW = mControl->getRbwValue();
//    VBW = RBW * ratio;
    mControl->setVbwtoRbw(ratio);
    mControl->setVbwValue(RBW);
    refreshBW();
}

void SA_Dialog_AllSetup::on_Value_Limit_Toggle_clicked(bool checked)
{
    digitInputClose();
    mControl->setLimitLineStatus(checked);
    refreshLimit();
    return;
}

void SA_Dialog_AllSetup::on_Value_Limit_Toggle_toggled(bool checked)
{
    if(checked)
    {
        ui->Value_Limit_Toggle->setText("On");
    }else
    {
        ui->Value_Limit_Toggle->setText("Off");
    }
}

void SA_Dialog_AllSetup::on_value_Limit_Edge_Toggle_clicked(bool checked)
{
    digitInputClose();
    mControl->setLimitEdgeStatus(checked);
    refreshLimit();
    return;
}

void SA_Dialog_AllSetup::on_value_Limit_Edge_Toggle_toggled(bool checked)
{
    if(checked)
    {
        ui->value_Limit_Edge_Toggle->setText("On");
    }else
    {
        ui->value_Limit_Edge_Toggle->setText("Off");
    }
}


void SA_Dialog_AllSetup::on_Value_Limit_Test_clicked(bool checked)
{
    digitInputClose();
    mControl->setLimitTestStatus(checked);
    refreshLimit();
    return;
}

void SA_Dialog_AllSetup::on_Value_Limit_Test_toggled(bool checked)
{
    if(checked)
    {
        ui->Value_Limit_Test->setText("On");
    }else
    {
        ui->Value_Limit_Test->setText("Off");
    }
    return;
}

void SA_Dialog_AllSetup::on_btn_Upper_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setLimitType(UPPER);
    }
    return;
}

void SA_Dialog_AllSetup::on_btn_Lower_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setLimitType(LOWER);
    }
    return;
}

void SA_Dialog_AllSetup::on_btn_MarkerView_clicked(bool checked)
{
    digitInputClose();
    mControl->setMarkerViewStatus(checked);
    refreshMarker();
    return;
}

void SA_Dialog_AllSetup::on_btn_MarkerView_toggled(bool checked)
{
    if(checked)
    {
        ui->btn_MarkerView->setText("On");
    }else
    {
        ui->btn_MarkerView->setText("Off");
    }
    return;
}

void SA_Dialog_AllSetup::on_Marker_Normal_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setMarkerType(REF);
    }
    refreshMarker();
    return;
}

void SA_Dialog_AllSetup::on_Marker_Delta_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setMarkerType(DELTA);
    }
    refreshMarker();
    return;
}

void SA_Dialog_AllSetup::on_btn_FreqCount_clicked(bool checked)
{
    digitInputClose();
    mControl->setMarkerFreqCountStatus(checked);
    if(checked)
    {
        if(!mControl->getMarkerViewStatus()) mControl->setMarkerViewStatus(SA_ON);
    }
    refreshMarker();
    return;
}

void SA_Dialog_AllSetup::on_btn_FreqCount_toggled(bool checked)
{
    if(checked)
    {
        ui->btn_FreqCount->setText("On");
    }else
    {
        ui->btn_FreqCount->setText("Off");
    }
    return;
}

void SA_Dialog_AllSetup::on_btn_NoiseMarker_clicked(bool checked)
{
    digitInputClose();
    mControl->setMarkerNoiseStatus(checked);
    refreshMarker();
    refreshTrace();
    return;
}

void SA_Dialog_AllSetup::on_btn_NoiseMarker_toggled(bool checked)
{
    if(checked)
    {
        ui->btn_NoiseMarker->setText("On");
    }else
    {
        ui->btn_NoiseMarker->setText("Off");
    }
    return;
}

void SA_Dialog_AllSetup::on_btn_TraceView_clicked(bool checked)
{
    digitInputClose();
    mControl->setTraceViewStatus(checked,mTrIndex);
    if(checked)
        mControl->setTraceSelect(mTrIndex);
    else {
        for(qint32 i = TRACE_CNT_TOTAL - 1;i>= 0;i--)
        {
            if(mControl->getTraceViewStatus(i) == SA_ON)
            {
                mControl->setTraceSelect(i);
                break;
            }
        }
    }
    refreshTrace();
    return;
}

void SA_Dialog_AllSetup::on_btn_TraceView_toggled(bool checked)
{
    if(checked)
    {
        ui->btn_TraceView->setText("On");
    }else
    {
        ui->btn_TraceView->setText("Off");
    }
    return;
}

void SA_Dialog_AllSetup::on_btn_Average_clicked(bool checked)
{
    digitInputClose();
    mControl->setTraceAverageStatus(checked,mTrIndex);
    refreshTrace();
    return;
}

void SA_Dialog_AllSetup::on_btn_Average_toggled(bool checked)
{
    if(checked)
    {
        ui->btn_Average->setText("On");
    }else
    {
        ui->btn_Average->setText("Off");
    }
    return;
}

void SA_Dialog_AllSetup::on_CHfinishEntry()
{
    disconnect(mChannelInput,SIGNAL(destroyed()),this,SLOT(on_CHfinishEntry()));
    mChannelInput = NULL;

    initDisplay();
    return ;
}

void SA_Dialog_AllSetup::on_Atten_Auto_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setAttenStatus(SA_AUTO);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_Atten_Manual_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setAttenStatus(SA_MANUAL);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_pb_nextPage_clicked()
{
    if(mInputDialog)
        digitInputClose();
    else if(mChannelInput)
    {
        channelInputClose();
    }
    lastWidget = curWidget;
    curWidget = SA_ALLSET_MARKERSELECT;
    refreshFocus();
    ui->stackedWidget->setCurrentIndex(2);
}

void SA_Dialog_AllSetup::on_pb_prePage_2_clicked()
{
    if(mInputDialog)
        digitInputClose();
    else if(mChannelInput)
    {
        channelInputClose();
    }
    lastWidget = curWidget;
    curWidget = 0;
    refreshFocus();
    ui->stackedWidget->setCurrentIndex(1);
}

void SA_Dialog_AllSetup::on_SweepTime_Auto_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setAutoSweepTimeStatus(SA_AUTO);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_SweepTime_Manual_clicked(bool checked)
{
    digitInputClose();
    if(checked)
    {
        mControl->setAutoSweepTimeStatus(SA_MANUAL);
    }
    initDisplay();
    return;
}

void SA_Dialog_AllSetup::on_value_MarkerTo_currentIndexChanged(qint32 index)
{
    digitInputClose();
    switch (index) {
    case 0:
        mControl->setMarkerToStart();
        break;
    case 1:
        mControl->setMarkerToCF();
        break;
    case 2:
        mControl->setMarkerToStop();
        break;
    }
    refreshMarker();
    return ;
}

void SA_Dialog_AllSetup::on_value_MarkerTo_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_MARKERTO;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_value_TriggerSource_clicked()
{
    digitInputClose();
    lastWidget = curWidget;
    curWidget = SA_ALLSET_TRIGGER_SOURCE;
    refreshFocus();
}

void SA_Dialog_AllSetup::on_value_TriggerSource_currentIndexChanged(qint32 index)
{
    mControl->setTriggerMode(index);
    refreshTrigger();
    return ;
}


void SA_Dialog_AllSetup::on_value_External_DelayOn_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerDelayStatus(checked);
    refreshTrigger();
    return;
}

void SA_Dialog_AllSetup::on_value_Peri_DelayOn_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerDelayStatus(checked);
    refreshTrigger();
    return;
}

void SA_Dialog_AllSetup::on_value_RFBurst_DelayOn_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerDelayStatus(checked);
    refreshTrigger();
    return;
}

void SA_Dialog_AllSetup::on_value_Video_DelayOn_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerDelayStatus(checked);
    refreshTrigger();
    return ;
}

void SA_Dialog_AllSetup::on_pb_Video_Pos_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerSlope(checked);
    refreshTrigger();
    return;
}

void SA_Dialog_AllSetup::on_pb_Video_Neg_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerSlope(!checked);
    refreshTrigger();
}

void SA_Dialog_AllSetup::on_pb_External_Pos_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerSlope(checked);
    refreshTrigger();
}
void SA_Dialog_AllSetup::on_pb_External_Neg_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerSlope(!checked);
    refreshTrigger();
}

void SA_Dialog_AllSetup::on_pb_RFBurst_Pos_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerSlope(checked);
    refreshTrigger();
}

void SA_Dialog_AllSetup::on_pb_RFBurst_Neg_clicked(bool checked)
{
    digitInputClose();
    mControl->setTriggerSlope(!checked);
    refreshTrigger();
}


