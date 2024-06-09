//---------------------------------------------------------------------------

#include "WLogger.h"
//---------------------------------------------------------------------------


tcWLogger::tcWLogger (const char* LogDir, const char * logName  ,  int  FileSizeLimit ,  int  FileCountLimit) :
        loggerName(logName) , sLogPath(LogDir) , fileSizeLimit(FileSizeLimit) , fileCountLimit(FileCountLimit)
{
    //Строка настройки логгера
    String configString;
    configString.sprintf( "/P7.Sink=FileTxt /P7.Name=%s /P7.Files=%d /P7.Roll=%dmb /P7.Dir=%s/ /P7.Pool=20480 %s",
         logName, fileCountLimit, fileSizeLimit, LogDir, "/P7.Format=\"%ix %lv [%tf] module:%mn   %ms  \"");
    P7_Set_Crash_Handler();
    l_pClient = P7_Create_Client(TM(configString.c_str()));

    //Создание объекта транзакций
    pTraceMain = P7_Create_Trace(l_pClient, TM("avcam"));
    if (pTraceMain == nullptr)  Ready = false;

    pTraceMain->Register_Module(TM(loggerName.c_str()), &l_hModule);


    Ready = true;
}


tcWLogger::~tcWLogger (void)
{
    pTraceMain->Release();
}


void  tcWLogger::Write (const char* caInfo, const bool& bDateTime, const bool& bFTime) {
    if (!Ready) return;
    if (!caInfo) return;
    pTraceMain->P7_INFO(l_hModule, TM("%s"), caInfo);
}

void  tcWLogger::Write (const String& sInfo, const bool& bDateTime, const bool& bFTime)
{
    if(!Ready) return;
    if(sInfo.IsEmpty()) return;
    pTraceMain->P7_INFO(l_hModule, TM("%s"),  sInfo.c_str());
}

void tcWLogger::FlushBuffer() {
    l_pClient->Flush();
}

