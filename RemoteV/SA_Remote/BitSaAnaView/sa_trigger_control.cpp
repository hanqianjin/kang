#include "sa_trigger_control.h"

sa_Trigger_Control::sa_Trigger_Control(user_variable &m_user_variable, user_limit &m_user_limit)
{
    globalUserVariable = &m_user_variable;
    globalUserLimit    = &m_user_limit;

}
sa_Trigger_Control::~sa_Trigger_Control()
{
    //delete globalUserLimit;
    //delete globalUserVariable;
}

