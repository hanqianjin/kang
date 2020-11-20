macro MultiLineComment()

{


    hwnd = GetCurrentWnd()


    selection = GetWndSel(hwnd)


    LnFirst =GetWndSelLnFirst(hwnd)      //取首行行号


    LnLast =GetWndSelLnLast(hwnd)      //取末行行号


    hbuf = GetCurrentBuf()


 


    if(GetBufLine(hbuf, 0) =="//magic-number:tph85666031"){


        stop


    }

    Ln = Lnfirst


    buf = GetBufLine(hbuf, Ln)


    len = strlen(buf)


 


    while(Ln <= Lnlast) {


        buf = GetBufLine(hbuf, Ln)  //取Ln对应的行


        if(buf ==""){                   //跳过空行


            Ln = Ln + 1


            continue


        }


 


        if(StrMid(buf, 0, 1) == "/"){       //需要取消注释,防止只有单字符的行


            if(StrMid(buf, 1, 2) == "/"){


                PutBufLine(hbuf, Ln, StrMid(buf, 2, Strlen(buf)))


            }


        }


 


        if(StrMid(buf,0,1) !="/"){          //需要添加注释


            PutBufLine(hbuf, Ln, Cat("//", buf))


        }


        Ln = Ln + 1


    }


 


    SetWndSel(hwnd, selection)


}








macro UnMultiLineComment()  
{   //取消杠杠注释,不选中多行的话,默认只处理当前行  
    hwnd = GetCurrentWnd()  
    selection = GetWndSel( hwnd )  
    lnFirst = GetWndSelLnFirst( hwnd )  
    lnLast = GetWndSelLnLast( hwnd )  
  
    hbuf = GetCurrentBuf()  
    ln = lnFirst  
    while( ln <= lnLast )  
    {  
        buf = GetBufLine( hbuf, ln )  
        len = strlen( buf )  
        if( len >= 2 )  
        {  
            start = 0  
  
            while( strmid( buf, start, start + 1 ) == CharFromAscii(32) || strmid( buf, start, start + 1 ) == CharFromAscii(9) )  
            {  
                start = start + 1  
                if( start >= len )  
                    break  
            }  
            if( start < len - 2 )  
            {  
                if( strmid( buf, start, start + 2 ) == "//" )  
                {  
                    buf2 = cat( strmid( buf, 0, start ), strmid( buf, start + 2, len ) )  
                    PutBufLine( hbuf, ln, buf2 )  
                }  
            }  
        }  
        ln = ln + 1  
    }  
    SetWndSel( hwnd, selection )  
}  
