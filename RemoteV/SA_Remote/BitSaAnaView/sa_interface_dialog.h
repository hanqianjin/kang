#ifndef SA_INTERFACE_DIALOG_H
#define SA_INTERFACE_DIALOG_H


class sa_interface_dialog
{
public:
    sa_interface_dialog();

    /**
    * @brief show dialog
    * @param[in]
    * @return error<0
   */
     virtual void showWidget() = 0;
    /**
    * @brief hide dialog
    * @param[in]
    * @return error<0
   */
     virtual void hideWidget() = 0;

    /**
    * @brief init dialog display
    * @param[in]
    * @return error<0
   */
     virtual void initDisplay() = 0;

    /**
    * @brief refresh button visiable or invisiable.
    * @param[in]
    * @return error<0
   */
     virtual void initWidget() = 0;
};

#endif // SA_INTERFACE_DIALOG_H
