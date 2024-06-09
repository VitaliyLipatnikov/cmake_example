//
// Created by user on 16.02.2023.
//
#include "ConfigReader.h"

TMemIniFile::TMemIniFile (std::string path) : path(path)
{
    file = g_key_file_new();
    openStatus = g_key_file_load_from_file(file , path.c_str() , G_KEY_FILE_KEEP_COMMENTS , &error );

}


TMemIniFile::~TMemIniFile (void) {
   if(error)  g_error_free(error);
   if(file)  g_key_file_free(file);
}


bool TMemIniFile::ConfigFileIsCorrect() {
   return openStatus;
}


int TMemIniFile::ReadInteger (const std::string &Section, const std::string &Ident, int Default) {
    if(!openStatus) return Default;
    int result;
    result = g_key_file_get_int64(file , Section.c_str() , Ident.c_str() , &error);
    if(error) {
        g_error_free(error);
        error = NULL;
        return Default;
    }
    else return result;
}

int TMemIniFile::ReadInteger (const char* Section, const char* Ident, int Default) {
    if(!Section || !Ident ) return Default;
    std::string sect = Section;
    std::string id = Ident;
    return ReadInteger(sect , id , Default);
}


std::string TMemIniFile::ReadString (std::string &Section, std::string &Ident, std::string &Default) {
    if(!openStatus) return Default;
    std::string result;

    if(error) g_error_free(error);
    //g_key_file_get_string возвращает указатель на динамически выделенную память, которую нужно очитсить с помощью free()
    char * temp = g_key_file_get_string(file , Section.c_str() , Ident.c_str() , &error);

    if(temp) {
        result = temp;
        free(temp);
    }
    else {
        result = Default;
    }

    if(error) {
        g_error_free(error);
        error = NULL;
        return Default;
    }
    else {
     //Некоторые строки в конфиге почему-то начинаются с '@' и заканчиваются на '@'. Если есть символ удалить его
     if(result[0] == '@' && result[result.size()-1] == '@') {
         result.erase(0,1);
         result.erase(result.size()-1 , 1);
     }
     return result;
    }
}

std::string TMemIniFile::ReadString (const char * Section, const char * Ident, const char * Default) {
    if(!Section || !Ident ) return Default;
    std::string sect = Section;
    std::string id = Ident;
    std::string def = Default;
    return ReadString(sect , id , def);
}


bool TMemIniFile::ReadBool (const std::string &Section, const std::string &Ident, bool Default) {
    if(!openStatus) return Default;
    bool result;
    result = g_key_file_get_boolean(file , Section.c_str() , Ident.c_str() , &error);
    if(error) {
        g_error_free(error);
        error = NULL;
        return Default;
    }
    else return result;
}


bool TMemIniFile::ReadBool (const char * Section, const char * Ident, bool Default)  {
    if(!Section || !Ident ) return Default;
    std::string sect = Section;
    std::string id = Ident;
    return ReadBool(sect , id , Default);
}


TDateTime TMemIniFile::ReadDateTime (const std::string &Section, const std::string &Ident, const TDateTime &Default) {
    if(!openStatus) return Default;
    std::string tempStr = "";
    TDateTime result;
    tempStr = g_key_file_get_string(file , Section.c_str() , Ident.c_str() , &error);
    if(error) {
        g_error_free(error);
        error = NULL;
        return Default;
    }
    else {
        StrToDateTimeForIni(tempStr, result);
        return result;
    }
}

TDateTime TMemIniFile::ReadDateTime (const char * Section, const char * Ident, TDateTime &Default) {
    if(!Section || !Ident  ) return Default;
    std::string sect = Section;
    std::string id = Ident;
    return ReadDateTime(sect , id , Default);
}



double TMemIniFile::ReadFloat (const std::string &Section, const std::string &Ident, double Default) {
    if(!openStatus) return Default;
    double result;
    result = g_key_file_get_double(file , Section.c_str() , Ident.c_str() , &error);
    if(error) {
        g_error_free(error);
        error = NULL;
        return Default;
    }
    else return result;
}

double TMemIniFile::ReadFloat (const char * Section, const char * Ident, double Default) {
    if(!Section || !Ident ) return Default;
    std::string sect = Section;
    std::string id = Ident;
    return ReadFloat(sect , id , Default);
}


bool TMemIniFile::WriteInteger (const std::string &Section, const std::string &Ident, int Value) {
    if(!openStatus) return false;
    g_key_file_set_integer(file , Section.c_str() , Ident.c_str() , Value);

    if(error) {
        g_error_free(error);
        error = NULL;
        return false;
    }
    else {
        return true;
    }
}


bool TMemIniFile::WriteInteger (const char * Section, const char * Ident, int Value) {
    if(!Section || !Ident ) return false;
    std::string sect = Section;
    std::string id = Ident;
    return WriteInteger(sect , id , Value);
}


bool TMemIniFile::WriteString (const std::string &Section, const std::string &Ident, const std::string &Value) {
    if(!openStatus) return false;
    //ДОБАВИТЬ @ В НАЧАЛО И КОНЕЦ СТРОКИ
    std::stringstream ss;
    std::string strWithDogs;
    ss<<'@'<<Value<<'@';
    ss>>strWithDogs;

    g_key_file_set_string(file , Section.c_str() , Ident.c_str() , strWithDogs.c_str());

    if(error) {
        g_error_free(error);
        error = NULL;
        return false;
    }
    else {
        return true;
    }
}

bool TMemIniFile::WriteString (const char * Section, const char * Ident, char * Value) {
    if(!Section || !Ident || !Value) return false;
    std::string sect = Section;
    std::string id = Ident;
    std::string val = Value;
    return WriteString(sect , id , val);
}


bool TMemIniFile::WriteStringWithoutDogs (const std::string &Section, const std::string &Ident, const std::string &Value) {
    if(!openStatus) return false;
    g_key_file_set_string(file , Section.c_str() , Ident.c_str() , Value.c_str());

    if(error) {
        g_error_free(error);
        error = NULL;
        return false;
    }
    else {
        return true;
    }
}

bool TMemIniFile::WriteStringWithoutDogs (const char * Section ,  const char * Ident, const char * Value) {
    if(!Section || !Ident || !Value) return false;
    std::string sect = Section;
    std::string id = Ident;
    std::string val = Value;
    return WriteStringWithoutDogs(sect, id , val);
}



bool TMemIniFile::WriteBool (const std::string &Section, const std::string &Ident, bool Value) {
    if(!openStatus) return false;
    g_key_file_set_boolean(file , Section.c_str() , Ident.c_str() , Value);

    if(error) {
        g_error_free(error);
        error = NULL;
        return false;
    }
    else {
        return true;
    }
}


bool TMemIniFile::WriteBool (const char * Section , const char * Ident, bool Value) {
    if(!Section || !Ident) return false;
    std::string sect = Section;
    std::string id = Ident;
    return  WriteBool(sect , id , Value);
}




bool TMemIniFile::WriteDateTime (const std::string &Section, const std::string &Ident, const TDateTime &Value) {
    if(!openStatus) return false;
    std::string dateTimeStr;
    TDateTime tempVal = Value;
    DateTimeToStr(tempVal , dateTimeStr );
    return WriteStringWithoutDogs(Section , Ident , dateTimeStr);
}


bool TMemIniFile::WriteDateTime (const char * Section, const char *Ident, const TDateTime  & Value) {
    if(!Section || !Ident) return false;
    std::string sect = Section;
    std::string id = Ident;
    return WriteDateTime(sect , id , Value);
}


bool TMemIniFile::WriteDate (const std::string &Section, const std::string &Ident, const std::string &Value) {
    if(!openStatus) return false;
    return WriteString(Section , Ident , Value);
}

bool TMemIniFile::WriteDate (const char * Section, const char *  Ident, const char * Value) {
    if(!Section || !Ident) return false;
    std::string sect = Section;
    std::string id = Ident;
    std::string data = Value;
    return WriteString(sect , id , data);
}

bool TMemIniFile::WriteFloat (const std::string &Section, const std::string &Ident, double Value) {
    if(!openStatus) return false;
    g_key_file_set_double(file , Section.c_str() , Ident.c_str() , Value);

    if(error) {
        g_error_free(error);
        error = NULL;
        return false;
    }
    else {
        return true;
    }
}

bool TMemIniFile::WriteFloat (const char * Section, const char * Ident, double Value) {
    if(!Section || !Ident) return false;
    std::string sect = Section;
    std::string id = Ident;
    return WriteFloat(sect , id , Value);
}


bool TMemIniFile::EraseSection (const std::string &Section) {
    if(!openStatus) return false;
    g_key_file_remove_group (file , Section.c_str() , &error);

    if(error) {
        g_error_free(error);
        error = NULL;
        return false;
    }
    else {
        return true;
    }
}

bool TMemIniFile::EraseSection (const char * Section) {
    if(!openStatus) return false;
    std::string sect = Section;
    return EraseSection(sect);
}


bool TMemIniFile::UpdateFile (void) {
    if(!openStatus) return false;
    return g_key_file_save_to_file (file , path.c_str() , &error);
}
