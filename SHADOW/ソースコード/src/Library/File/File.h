#pragma once
#include "DxLib.h"
#include <vector>
#include <string>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

//std�ȗ�
using namespace std;
//���O�ȗ�
namespace rx = rapidxml;

class CFile {
public:
	//xml�t�@�C���p�h�L�������g
	static rx::xml_document<> _Doc;

	// input �� delimiter �ŕ�������֐�
	static vector<string> split(string& input, char delimiter);
	//�t�@�C���ǂݍ���(2����)(int)
	static void Load(vector<vector<int>>& array, const char* DATA);
	//�t�@�C���ǂݍ���(2����)(float)
	static void Load(vector<vector<float>> &array, const char* DATA);
	/// <summary>
	/// xml�t�@�C���ǂݍ���(vector�Ƀ��[�h�����n���h�����i�[)
	/// </summary>
	/// <param name="array">�n���h���i�[�p�z��</param>
	/// <param name="file_name">�t�@�C����</param>
	/// <param name="node_name">�m�[�h��</param>
	/// <param name="is_model">true : model�p�X false : graph�p�X</param>
	/// <returns>�n���h����</returns>
	static int XmlFileInput(vector<int>& array, const char* file_name, const char* node_name, bool is_model);
};
