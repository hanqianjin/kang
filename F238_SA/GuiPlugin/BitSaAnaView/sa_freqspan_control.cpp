#include "sa_freqspan_control.h"

sa_FreqSpan_Control::sa_FreqSpan_Control(user_variable &m_user_variable, user_limit &m_user_limit)
{
    globalUserVariable = &m_user_variable;
    globalUserLimit    = &m_user_limit;
}
sa_FreqSpan_Control::~sa_FreqSpan_Control()
{
    //delete globalUserLimit;
    //delete globalUserVariable;
}
