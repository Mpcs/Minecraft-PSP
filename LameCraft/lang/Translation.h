#ifndef TRANSLATION_H_
#define TRANSLATION_H_

#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::map;

class Translation {
public:
    Translation();

    virtual ~Translation();

    static Translation *GetInstance();

    void loadLanguage(string languageName, string languageFileName);

    string getLanguageName();

    map<string, string> getTranslationsOfType(string translationType);
    vector<string> getValuesOfType(string translationType);
    string getValue(string translationType, string key);

private:
    static Translation* instance;
    string languageName;
    string languageFileName;
    map<string,map<string, string> > translationValues;
};

#endif
