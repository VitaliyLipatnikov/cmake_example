//---------------------------------------------------------------------------
#ifndef WLoggerH
#define WLoggerH
//---------------------------------------------------------------------------
#include "P7_Client.h"
#include "P7_Trace.h"
#include "BCB_String.h"


class tcWLogger {
  private:
    IP7_Client * l_pClient;                      //Клиент общий для всех объектов
    IP7_Trace *pTraceMain;                              //Каждый отдельный объект использует свой объект транзакций
    IP7_Trace::hModule l_hModule;

    std::string loggerName;
    std::string sLogPath;
    int fileSizeLimit;
    int fileCountLimit;
    bool Ready = false;

  public:
    tcWLogger (const char * LogDir, const char * loggerName  ,  int  iFileSizeLimit  = 10 ,  int  iFileCountLimit = 50);

   ~tcWLogger (void);

    void  Write (const char* caInfo, const bool& bDateTime = true, const bool& bFTime = false);

    void  Write (const String& sInfo, const bool& bDateTime = true, const bool& bFTime = false);

    void FlushBuffer();

};
#endif
