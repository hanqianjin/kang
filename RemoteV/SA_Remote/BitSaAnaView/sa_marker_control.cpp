#include "sa_marker_control.h"

sa_Marker_Control::sa_Marker_Control(user_variable &m_user_variable, user_limit &m_user_limit)
{
    globalUserVariable = &m_user_variable;
    globalUserLimit    = &m_user_limit;
}
sa_Marker_Control::~sa_Marker_Control()
{
    //delete globalUserLimit;
    //delete globalUserVariable;
}
