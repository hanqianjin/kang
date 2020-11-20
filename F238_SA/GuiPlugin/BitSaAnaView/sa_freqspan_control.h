#ifndef SA_FREQSPAN_CONTROL_H
#define SA_FREQSPAN_CONTROL_H

#include "sa_user_variable.h"
#include "sa_user_limit.h"

class sa_FreqSpan_Control
{
public:
    sa_FreqSpan_Control(user_variable &m_user_variable,user_limit &m_user_limit);
    ~sa_FreqSpan_Control();

    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
};

#endif // SA_FREQSPAN_CONTROL_H
