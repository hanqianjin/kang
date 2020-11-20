#ifndef SA_MARKER_CONTROL_H
#define SA_MARKER_CONTROL_H

#include "sa_user_variable.h"
#include "sa_user_limit.h"

class sa_Marker_Control
{
public:
    sa_Marker_Control(user_variable &m_user_variable,user_limit &m_user_limit);
    ~sa_Marker_Control();

    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
};

#endif // SA_MARKER_CONTROL_H