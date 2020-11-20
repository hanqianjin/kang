#ifndef SA_TRIGGER_CONTROL_H
#define SA_TRIGGER_CONTROL_H

#include "sa_user_variable.h"
#include "sa_user_limit.h"

class sa_Trigger_Control
{
public:
    sa_Trigger_Control(user_variable &m_user_variable,user_limit &m_user_limit);
    ~sa_Trigger_Control();

    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
};

#endif // SA_TRIGGER_CONTROL_H
