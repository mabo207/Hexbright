#include<iostream>
#include<fstream>
#include<cassert>
#include"FileRead.h"




//�t�@�C����ǂݍ���vector<char>�^�ɂ��ĕԂ�
vector<char> FileRead(const char *DatabaseName){
	//�t�@�C�����J��
	ifstream ifs(DatabaseName);
	if(!ifs){
		assert(false);
		return vector<char>();
	}
	//������ǂݍ���
	vector<char> OriginalStr;
	while(true){
		char word=ifs.get();
		if(word==EOF){//�ǂݎ�������̂�EOF�ɂȂ�܂Ń��[�v����
			break;
		}
		OriginalStr.push_back(word);
	}

	//�t�@�C�������
	ifs.close();

	return OriginalStr;
}

//�t�@�C����ǂݍ��݁A���s�E�J���}�ŋ�؂�ꂽ��������ʂ��ĕԂ�(�����`��)
vector<vector<string>> CommaCutRead(const char *DatabaseName){
	//�t�@�C���̓ǂݍ���
	vector<char> OriginalData=FileRead(DatabaseName);
	//���s���Ƀf�[�^�𕪂��āA�P�s���ɂ��ăJ���}��؂�ŕ������ǂݎ��
	vector<vector<string>> CutData;//������Ԃ�
	vector<string> LineData;//�P�s���̃f�[�^
	string Str="";//LineData�ɓ���镶����
	for(unsigned int i=0;i<OriginalData.size();i++){
		switch(OriginalData[i]){
		case('\n')://���s�����̎�
			if(Str!=""){
				LineData.push_back(Str);//Str�ɉ��������Ă����LineData�ɉ�����
			}
			CutData.push_back(LineData);//CutData�ɑ}��
			//������
			LineData.clear();
			Str.clear();
			break;
		case(',')://�J���}�̎�
			LineData.push_back(Str);//LineData�ɑ}��
			//������
			Str.clear();
			break;
		default://����ȊO�̎�
			Str=Str+OriginalData[i];//������ɕ�����ǉ�
			break;
		}
	}
	return CutData;
}

//�t�@�C����ǂݍ���string�^�ɂ��ĕԂ�
string FileStrRead(const char *DatabaseName){
	//�t�@�C���̓ǂݍ���
	vector<char> OriginalData=FileRead(DatabaseName);
	//string�^�ɒ���
	string Str;
	for(unsigned int i=0;i<OriginalData.size();i++){
		Str=Str+OriginalData[i];
	}
	return Str;
}

//�������split�ŕ������S�ĕԂ�
vector<string> StrTok(const string OriginalStr,const char split){
	//OriginalStr��split�ŕ�������CutStr�Ɋi�[����
	vector<string> CutStr;
	for(unsigned int i=0;i<OriginalStr.size();i++){
		static string CutData;//�����ɕ�����ǉ����Ă����Asplit��������CutStr�Ɋi�[����
		//OriginalStr��i�Ԗڂ̕���������
		if(OriginalStr[i]==split){
			//CutData=CutData+'\0';
			CutStr.push_back(CutData);
			CutData.clear();
		}else{
			CutData=CutData+OriginalStr[i];
			if(i==OriginalStr.size()-1){//�����񂪏I��鎞
				//CutData=CutData+'\0';
				CutStr.push_back(CutData);
				CutData.clear();
			}
		}
	}
	return CutStr;
}

//�t�@�C����split1�ŕ������ēǂݍ��񂾌�A�c���split2�ŕ����Bsplit2�����ɑ΂��čŏ��̕������key�Ƃ���map��Ԃ�
map<string,vector<string>> ReadDoubleSplitToMap(const char *DatabaseName,const char split1,const char split2){
	//split1�ŕ����ǂݍ���
	vector<string> vs=StrTok(FileStrRead(DatabaseName),split1);
	//split2�ŕ����ǂݍ���
	map<string,vector<string>> rmap;
	for(unsigned int i=0;i<vs.size();i++){
		vector<string> vvs=StrTok(vs[i],split2);
		//map�Ɋi�[����̂�split2��2�ȏ�ɕ����ł����Ƃ��̂�
		if(vvs.size()>1){
			//�擪�v�f��ʂɋ~�o���Ă���폜
			string s=vvs[0];
			vvs.erase(vvs.begin());
			//rmap�Ɋi�[
			rmap.insert(pair<string,vector<string>>(s,vvs));
		}
	}
	return rmap;
}

//��������J���}�ŕ������A�擪�v�f��key�Ƃ���map�ɂ��ĕԂ�(�����`��)
map<string,vector<string>> CommaCutReadMap(const char *DatabaseName){
	//�J���}�����ǂݍ���
	vector<vector<string>> vvs=CommaCutRead(DatabaseName);
	//map�Ɋi�[
	map<string,vector<string>> map;
	for(unsigned int i=0;i<vvs.size();i++){
		if(vvs[i].size()>1){
			string key=vvs[i][0];
			vvs[i].erase(vvs[i].begin());
			map.insert(pair<string,vector<string>>(key,vvs[i]));
		}
	}
	return map;
}

//CSV�t�H���_��ǂݎ����vector<vector<int>>�^�ɂ��ĕԂ�(�����`��)
vector<vector<int>> CSVRead(const char *DatabaseName){
	//�J���}��؂�œǂݎ��
	vector<vector<string>> DatabaseStr=CommaCutRead(DatabaseName);
	//int�^�ɒ���
	vector<vector<int>> Database;
	for(unsigned int i=0;i<DatabaseStr.size();i++){
		vector<int> Data;//�����ɂP�s��������
		for(unsigned int n=0;n<DatabaseStr[i].size();n++){//i�s�ڂ̃f�[�^�����
			Data.push_back(atoi(DatabaseStr[i][n].c_str()));
		}
		Database.push_back(Data);
	}
	//�ǂݎ�������̂�Ԃ�
	return Database;
}

//�e�L�X�g�f�[�^�ACSV�f�[�^�̂ǂ���ł��������A����Ȃǂ̐�������ǂݎ��֐��B(�����`��)
//�������d���̂ŏ������@��ς��Ă���
string ExplainDataRead(const char *DatabaseName,const char *index,const char smallsplit,const char largesplit){
	//�����ł�smallsplit==',',largesplit=='$'�Ƃ��Đ�������
	//$�Ɉ͂�ꂽ�����̒���,�ŋ�؂�A��؂��������̕�����̓��A
	//1�Ԗڂ�index�Ɉ�v�����2�Ԗڂ̕������Ԃ�
	
	//�t�@�C�����J��
	ifstream ifs(DatabaseName);
	if(!ifs){
		assert(false);
		return "";
	}
	//������ǂݍ���
	string ReturnStr;//������Ԃ�
	string indexstr;//�����ɋ�؂��1�Ԗڂ�����
	int nowprocess=0;//��ƒi�K 0:$��T�� 1:��؂��1�Ԗڂ���� 2:ReturnStr�̍쐬
	bool roopflag=true;//��Ƃ��I����Ă��Ȃ����ǂ���
	while(roopflag){
		char word=ifs.get();
		if(word==EOF){//�ǂݎ�������̂�EOF�ɂȂ�܂Ń��[�v����
			break;
		}
		switch(nowprocess){
		case(0)://0:$��T��
			if(word==largesplit){
				nowprocess=1;//�������Ŏ��̒i�K�ɐi��
			}
			break;
		case(1)://1:��؂��1�Ԗڂ����
			if(word==smallsplit){//,1�Ԗڂ̋�؂肪���������Ȃ��
				if(indexstr==index){//1�Ԗڂ̋�؂肪index�Ɉ�v�����
					nowprocess=2;//���̒i�K�ɐi��
				}else{
					nowprocess=0;//$�T�������蒼��
				}
				indexstr.clear();//indexstr������������
			}else if(word==largesplit){//,�̋�؂��������O��$�̋�؂���������Ȃ�
				indexstr.clear();//�����Ȃ���Ԃ����蒼��
			}else{
				indexstr=indexstr+word;
			}
			break;
		case(2)://2:ReturnStr�̍쐬
			if(word==smallsplit || word==largesplit){//��؂����������
				roopflag=false;//�쐬�I��
			}else{
				ReturnStr=ReturnStr+word;
			}
			break;

		}
	}

	//�t�@�C������֐����I������
	ifs.close();

	return ReturnStr;
}

//json�^�̃f�[�^�̑S�̂�ǂݎ��
picojson::value PicojsonRead(const char *DatabaseName){
	picojson::value root;
	ifstream ifs(ShiftjisJsonCorrect(DatabaseName).c_str());
	assert(ifs);
	ifs>>root;
	assert(picojson::get_last_error().empty());
	return root;
}

//json�f�[�^����sjis��p���Ă���ƁA"�\po"�݂����Ȃ̂��ǂݎ��Ȃ��Ȃ�̂ŁA"�\\po"�ƒ������ĐV�����f�[�^������
//������̃t�@�C������Ԃ�
string ShiftjisJsonCorrect(const char *DatabaseName){
	if(DatabaseName==NULL){
		return "";
	}
	//��������t�@�C���������
	string GenerateDatabaseName="";
	bool flag=true;
	for(unsigned int i=0;i<strlen(DatabaseName)+1;i++){
		//�g���q�̓���O��"Corrected"�Ƃ����������������
		if(DatabaseName[i]=='.' && flag){
			GenerateDatabaseName+="Corrected";
			flag=false;//2�ȏ��Corrected�������Ȃ�
		}
		GenerateDatabaseName+=DatabaseName[i];
	}
	if(flag){//Corrected���t���������Ă��Ȃ��Ȃ�(�g���q�����݂��Ȃ������f�[�^)�����ɕt��������
		GenerateDatabaseName+="Corrected";
	}
	//�t�@�C���I�[�v��
	ifstream rf(DatabaseName);
	ofstream wf(GenerateDatabaseName.c_str());
	if(!rf || !wf){//�ǂݍ��ݎ��s��
		assert(1);
		return "";
	}
	//�ȉ��A�ǂݍ��݂Ə�������
	int state=0;//��ԁB0:1byte,2byte�ւ�炸1������ 1:2byte��2������ 2:���O��2byte������\�ł���������1������
	while(1){
		char c=rf.get();
		if(c==EOF){//���̓t�@�C���̖������m
			break;
		}
		switch(state){
		case(0):
			if(c<0){//c��2byte������1�����ڂȂ�
				state=1;
			}
			break;
		case(1):
			if(c=='\\'){
				//sjis��2byte�����ɂ��āA2byte�ڂ̕�����\�Ȃ���2��
				state=2;
			}else{
				//1�����ڂ̓ǂݎ���Ԃ�
				state=0;
			}
			break;
		case(2):
			if(c!='\\'){
				//2byte������\�̎��̕�����\�łȂ��Ȃ�\���o��
				wf<<'\\';
			}
			if(c<0){
				//c��2byte������1�����ڂȂ�
				state=1;
			}else{
				//�����łȂ��Ȃ�ʏ��1�����ڂ̓ǂݎ��ɖ߂�
				state=0;
			}
			break;
		}
		//�ǂݎ�����������o��
		wf<<c;
	}
	//�I������
	rf.close();
	wf.close();
	return GenerateDatabaseName;
}
