//
// Created by user on 16.02.2023.
//

#ifndef INIREADER_TMEMINIFILE_H
#define INIREADER_TMEMINIFILE_H


#define MAX_LEN_STRING_IN_INIFILE 255

#include   <string>
#include <algorithm>
#include <sstream>
#include "BCB_TDateTime.h"
#include "glib.h"

class TMemIniFile {
private:
    GKeyFile* file;
    std::string path;
    GError *error = NULL;
    gboolean openStatus  = FALSE;                                                           //Если файл успешно открыт то устанавливается 1
public:
     TMemIniFile (std::string path);
    ~TMemIniFile (void);

    //Если файл открыть не удалось - неверный путь или файл содержит некорректный синтаксис
    bool ConfigFileIsCorrect();

    int ReadInteger (const std::string &Section, const std::string &Ident, int Default);
    int ReadInteger (const char* Section, const char* Ident, int Default);

    std::string ReadString (std::string &Section, std::string &Ident, std::string &Default);
    std::string ReadString (const char * Section, const char * Ident, const char * Default);

    bool ReadBool (const std::string &Section, const std::string &Ident, bool Default);
    bool ReadBool (const char * Section, const char * Ident, bool Default);


    TDateTime ReadDateTime (const std::string &Section, const std::string &Ident, const TDateTime &Default);
    TDateTime ReadDateTime (const char * Section, const char * Ident, TDateTime &Default);


    double ReadFloat (const std::string &Section, const std::string &Ident, double Default);
    double ReadFloat (const char * Section, const char * Ident, double Default);

    bool WriteInteger (const std::string &Section, const std::string &Ident, int Value);
    bool WriteInteger (const char * Section, const char * Ident, int Value);

    //ДВА ДАННЫХ МЕТОДА ДОБАВЛЯЮТ '@' В НАЧАЛО И КОНЕЦ СТРОКИ
    bool WriteString (const std::string &Section, const std::string &Ident, const std::string &Value);
    bool WriteString (const char * Section, const char * Ident, char * Value);

    //ЗАПИСЬ СТРОКИ БЕЗ '@' В НАЧАЛЕ И КОНЦЕ
    bool WriteStringWithoutDogs (const std::string &Section, const std::string &Ident, const std::string &Value);
    bool WriteStringWithoutDogs (const char * Section ,  const char * Ident, const char * Value);


    bool WriteBool (const std::string &Section, const std::string &Ident, bool Value);
    bool WriteBool (const char * Section , const char * Ident, bool Value);


    bool WriteDateTime (const std::string &Section, const std::string &Ident, const TDateTime &Value);
    bool WriteDateTime (const char * Section, const char *Ident, const TDateTime  &Value);


    bool WriteDate (const std::string &Section, const std::string &Ident, const std::string &Value);
    bool WriteDate (const char * Section, const char *  Ident, const char * Value);


    bool WriteFloat (const std::string &Section, const std::string &Ident, double Value);
    bool WriteFloat (const char * Section, const char * Ident, double Value);

    //УДАЛИТЬ ВСЮ СЕКЦИЮ, НЕ КЛЮЧ А ВСЮ СЕКЦИЮ!!!!!!!!
    bool EraseSection (const std::string &Section);
    bool EraseSection (const char * Section);

    //Сохранить изменения на диск.
    bool UpdateFile (void);
};

#endif //INIREADER_TMEMINIFILE_H
