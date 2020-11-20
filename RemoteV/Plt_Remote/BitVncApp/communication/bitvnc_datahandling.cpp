#include "bitvnc_datahandling.h"

bitvnc_DataHandling::bitvnc_DataHandling(QObject *parent) : QObject(parent)
{

}

void bitvnc_DataHandling::readData(QByteArray pData)
{
    //把数据存到缓存
    qint32 len= pData.length();
    for(int i=0;i<len;i++)
    {
        pReadDate[pReadPos] = pData[i];
        pReadPos++;
    }

}

void bitvnc_DataHandling::readOneInfo(QByteArray *pData)
{
    QByteArray pTmpData;
    qint32 len= pReadDate.length();
    qint32 findheader = false;
    qint32 findtail = false;

    //while (true)
    {
        //找头部
        if(pReadDate[0] != 0xeb && pReadDate[1] != 0x99)
        {
            for(int i=1;i<=pReadPos-2;i++)
            {
                //抛弃头部之前内容
                if (pReadDate[i] == 0xeb && pReadDate[i+1] == 0x99)
                {
                    for(int j=i;j<=len-1;j++)
                    {
                        pReadDate[j-i]=pReadDate[j];
                    }
                    pReadPos = pReadPos-i;
                    findheader = true;
                    break;
                }
            }
        }

        if (pReadDate[0] == 0xeb && pReadDate[1] == 0x99)
        {
            findheader=true;
        }

        if(!findheader)
        {
            return;
        }

        //找尾部
        findtail=false;
        for(int i=2;i<=pReadPos-2;i++)
        {
            if (pReadDate[i] == 0x99 && pReadDate[i+1] == 0xBE)
            {
                pTmpData.resize(i+2);
                for(int j=0;j<=i+1;j++)
                {
                    pTmpData[j]=pReadDate[j];
                }
                for(int j=i+2;j<=pReadPos-1;j++)
                {
                    pReadDate[j-i-2]=pReadDate[j];
                }
                pReadPos = pReadPos-i-2;
                findtail=true;
                break;
            }

        }

        if(!findtail)
        {
            return;
        }

        if(0xeb == (unsigned char)pTmpData[0] && 0x99 == (unsigned char)pTmpData[1])
        {
            for(qint32 i = 2;i<pTmpData.size()-2;i++)
            {
                pData->append(pTmpData[i]);
            }
        }
    }
    return;
}
