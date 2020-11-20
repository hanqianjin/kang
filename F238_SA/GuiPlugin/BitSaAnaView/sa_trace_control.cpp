#include "sa_trace_control.h"

sa_Trace_Control::sa_Trace_Control(user_variable &m_user_variable, user_limit &m_user_limit)
{
    globalUserVariable = &m_user_variable;
    globalUserLimit    = &m_user_limit;
}
sa_Trace_Control::~sa_Trace_Control()
{
    //delete globalUserLimit;
    //delete globalUserVariable;
}
