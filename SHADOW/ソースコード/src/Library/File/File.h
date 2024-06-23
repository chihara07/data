#pragma once
#include "DxLib.h"
#include <vector>
#include <string>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

//std省略
using namespace std;
//名前省略
namespace rx = rapidxml;

class CFile {
public:
	//xmlファイル用ドキュメント
	static rx::xml_document<> _Doc;

	// input を delimiter で分割する関数
	static vector<string> split(string& input, char delimiter);
	//ファイル読み込み(2次元)(int)
	static void Load(vector<vector<int>>& array, const char* DATA);
	//ファイル読み込み(2次元)(float)
	static void Load(vector<vector<float>> &array, const char* DATA);
	/// <summary>
	/// xmlファイル読み込み(vectorにロードしたハンドルを格納)
	/// </summary>
	/// <param name="array">ハンドル格納用配列</param>
	/// <param name="file_name">ファイル名</param>
	/// <param name="node_name">ノード名</param>
	/// <param name="is_model">true : modelパス false : graphパス</param>
	/// <returns>ハンドル数</returns>
	static int XmlFileInput(vector<int>& array, const char* file_name, const char* node_name, bool is_model);
};
