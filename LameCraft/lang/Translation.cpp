#include "translation.h"
#include <vector>
#include <string>
#include <map>

using std::string;
using std::map;

Translation::Translation() {

}

Translation::~Translation() {

}

Translation* Translation::instance = NULL;

Translation* Translation::GetInstance() {
    if(instance==NULL){
        instance = new Translation();
    }
    return instance;
}

void Translation::loadLanguage(string languageName, string languageFileName) {
    this->languageName = languageName;
    this->languageFileName = languageFileName;

    string filePath = "Assets/Lang/" + languageFileName;

    FILE *file;
    file = fopen(filePath.c_str(), "r");
    char line[256];
    map<string, string> currentMap;
    while (fgets(line, sizeof(line), file)) {
        string linestr(line);

        int pos = linestr.find("=");
        string translationKey = linestr.substr(0, pos);
        string value = linestr.substr(pos+1, linestr.length()-1);

        pos = translationKey.find(".");
        string type = translationKey.substr(0, pos);
        string id = translationKey.substr(pos+1, translationKey.length()-1);

        translationValues[type][id] = value;
    }

    fclose(file);
}

map<string, string> Translation::getTranslationsOfType(string translationType) {
    return translationValues[translationType];
}

vector<string> Translation::getValuesOfType(string translationType) {
    map<string, string> typeMap = translationValues[translationType];
    vector<string> values;
    for (map<string, string>::iterator it = typeMap.begin(); it != typeMap.end(); ++ it) {
        values.push_back(it->second);
    }
    return values;
}

string Translation::getValue(string translationType, string key) {
    return translationValues[translationType][key];
}

string Translation::getLanguageName() {
    return languageName;
}