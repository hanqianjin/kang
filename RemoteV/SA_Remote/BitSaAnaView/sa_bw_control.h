#ifndef SA_BW_CONTROL_H
#define SA_BW_CONTROL_H

#include "sa_user_variable.h"
#include "sa_user_limit.h"

class sa_BW_Control
{
public:
    sa_BW_Control(user_variable &m_user_variable,user_limit &m_user_limit);
    ~sa_BW_Control();

    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
};

#endif // SA_BW_CONTROL_H
