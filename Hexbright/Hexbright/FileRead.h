#ifndef DEF_FILEREAD_H
#define DEF_FILEREAD_H

//�C���N���[�h��
#include<vector>
#include<string>
#include<map>
#include"picojson.h"

using namespace std;

//�֐�
//�t�@�C����ǂݍ���vector<char>�^�ɂ��ĕԂ�
vector<char> FileRead(const char *DatabaseName);

//�t�@�C����ǂݍ���string�^�ɂ��ĕԂ�
string FileStrRead(const char *DatabaseName);

//�t�@�C����ǂݍ��݁A���s�E�J���}�ŋ�؂�ꂽ��������ʂ��ĕԂ�(�����`��)
vector<vector<string>> CommaCutRead(const char *DatabaseName);

//�������split�ŕ������S�ĕԂ�
vector<string> StrTok(const string OriginalStr,const char split);

//�t�@�C����split1�ŕ������ēǂݍ��񂾌�A�c���split2�ŕ����Bsplit2�����ɑ΂��čŏ��̕������key�Ƃ���map��Ԃ�
map<string,vector<string>> ReadDoubleSplitToMap(const char *DatabaseName,const char split1,const char split2);

//��������J���}�ŕ������A�擪�v�f��key�Ƃ���map�ɂ��ĕԂ�(�����`��)
map<string,vector<string>> CommaCutReadMap(const char *DatabaseName);

//CSV�t�H���_��ǂݎ����vector<vector<int>>�^�ɂ��ĕԂ�(�����`��)
vector<vector<int>> CSVRead(const char *DatabaseName);

//�e�L�X�g�f�[�^�ACSV�f�[�^�̂ǂ���ł��������A����Ȃǂ̐�������ǂݎ��֐�(�����`��)
//�������d���̂ŏ������@��ς��Ă���
string ExplainDataRead(const char *DatabaseName,const char *index,const char smallsplit,const char largesplit='\0');

//json�^�̃f�[�^�̑S�̂�ǂݎ��(picojson::value�^�ŕԂ�)
picojson::value PicojsonRead(const char *DatabaseName);

//json�f�[�^����sjis��p���Ă���ƁA"�\po"�݂����Ȃ̂��ǂݎ��Ȃ��Ȃ�̂ŁA"�\\po"�ƒ������ĐV�����f�[�^������
//������̃t�@�C������Ԃ�
string ShiftjisJsonCorrect(const char *DatabaseName);

#endif