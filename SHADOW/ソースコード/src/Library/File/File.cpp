#include "File.h"
#include <fstream>
#include <sstream>

rx::xml_document<> CFile::_Doc = {};

// input を delimiter で分割する関数
vector<string> CFile::split(string& input, char delimiter) {
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) result.push_back(field);
    return result;
}

//ファイル読み込み(2次元)(int)
void CFile::Load(vector<vector<int>>& array, const char* DATA) {
    ifstream ifs(DATA);                       // 読み取り用ストリーム
    if (ifs) {
        string line;

        // 一行目がラベルの場合
        getline(ifs, line);
        vector<string> strvec = split(line, ',');

        while (getline(ifs, line)) {
            vector<int> datvec;
            vector<string> strvec = split(line, ',');
            for (auto&& s : strvec) datvec.push_back(stoi(s)); // セルの文字列を数値に変換
            array.push_back(datvec);
        }
    }
}

//ファイル読み込み(2次元)(float)
void CFile::Load(vector<vector<float>>& array, const char* DATA) {
    ifstream ifs(DATA);                       // 読み取り用ストリーム
    if (ifs) {
        string line;

        // 一行目がラベルの場合
         getline(ifs, line);
         vector<string> strvec = split(line, ',');

        while (getline(ifs, line)) {
            vector<float> datvec;
            vector<string> strvec = split(line, ',');
            for (auto&& s : strvec) datvec.push_back(stof(s)); // セルの文字列を数値に変換
            array.push_back(datvec);
        }
    }
}

int CFile::XmlFileInput(vector<int>& array, const char* file_name, const char* node_name, bool is_model) {
    int n = 0;

    _Doc.clear();
    rx::file<> input(file_name);
    _Doc.parse<0>(input.data());

    rx::xml_node<>* node = _Doc.first_node(node_name);

    for (rx::xml_node<>* child = node->first_node(); child != nullptr; child = child->next_sibling()) {
        if (is_model) {
            array.push_back(MV1LoadModel(child->value()));
        }
        else {
            array.push_back(LoadGraph(child->value()));
        }
        n++;
    }

    return n;
}
