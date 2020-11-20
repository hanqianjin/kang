#include "sa_bw_control.h"

sa_BW_Control::sa_BW_Control(user_variable &m_user_variable, user_limit &m_user_limit)
{
    globalUserVariable = &m_user_variable;
    globalUserLimit    = &m_user_limit;
}
sa_BW_Control::~sa_BW_Control()
{
    //delete globalUserLimit;
    //delete globalUserVariable;
}
