#ifndef DEF_GRAPHICCONTROL_H
#define DEF_GRAPHICCONTROL_H

#include<vector>
#include<string>

using namespace std;

void hogehogehogehoge();

//�����ǂݍ��݂������̂̈ꕔ�������݂����Ȃ��Ƃ�����f�[�^�͂����ł͊Ǘ����Ȃ�
class GraphicControlClass{
	//�^�錾
protected:
	//(�����ǂݍ��݂��Ȃ�)�O���t�B�b�N�^(�����ǂݍ��ݎ��͕������ꂽ���̂�����)
	struct GraphicData{
		int m_handle;//�f�[�^�n���h��
		string m_name;//���[�h���̖��O
		int m_number;//���̃O���t�B�b�N�f�[�^�����ӏ��ŗp�����Ă��邩
		GraphicData(int handle,string name,int number);
		~GraphicData();
	};
	//�����ǂݍ��݂���O���t�B�b�N�^(����Ȃ�)
	struct DivGraphicData{
		int *m_handle;//�f�[�^�n���h��(���I�m��)
		string m_name;//���[�h���̖��O
		int m_number;//���̃O���t�B�b�N�f�[�^�����ӏ��ŗp�����Ă��邩
		int m_divNUM;//������(�f�[�^�n���h����)
		DivGraphicData(int *handle,string name,int number,int divNUM)
			:m_handle(handle),m_name(name),m_number(number),m_divNUM(divNUM)
		{
			int i=0;
		}
		~DivGraphicData(){
			if(m_handle!=NULL){
				delete [] m_handle;
				m_handle=NULL;
			}
		}
		DivGraphicData(const DivGraphicData &otherobj)
			:m_handle(NULL),m_name(otherobj.m_name),m_number(otherobj.m_number),m_divNUM(otherobj.m_divNUM)
		{
			//m_handle�͓��I�m�ۂ����z��Ȃ̂ŁA�R�s�[�̍ۂ͐V�������������m�ۂ��Ă�����K�v������
			if(otherobj.m_handle!=NULL){//NULL�łȂ���΃R�s�[������̂�����
				m_handle=new int [m_divNUM];
				for(int i=0;i<m_divNUM;i++){
					m_handle[i]=otherobj.m_handle[i];
				}
			}
		}
		DivGraphicData operator=(const DivGraphicData &otherobj){//������Z�q=�̃I�[�o�[���[�h
			return DivGraphicData(otherobj);
		}
	};
	
	//�ϐ�
protected:
	vector<GraphicData> m_Graphic;
	vector<DivGraphicData> m_DivGraphic;//����Ȃ�

	//�֐�
protected:
	vector<GraphicData>::iterator GraphicSearch(int GRHandle);
	vector<GraphicData>::iterator GraphicSearch(string GRName);


public:
	GraphicControlClass();
	~GraphicControlClass();
	int LoadGraphEX(string filename);//(�߂�l)-1:�G���[���� -1�ȊO:�O���t�B�b�N�n���h��
	int LoadDivGraphEX(string filename,int Allnum,int XNum,int YNum,int XSize,int YSize,int *HandleBuf);//(�߂�l)-1:�G���[���� 0:����
	int CopyGraph(int GRHandle);//(�߂�l)-1:�G���[���� ����ȊO:�O���t�B�b�N�n���h��//�O���t�B�b�N�f�[�^�𕡐�����(�����I�ɂ͎g���Ă���ӏ���1���₷����)
	int DeleteGraphEX(int GRHandle);//(�߂�l)-1:�G���[���� 0:����
	int InitGraphEX();//�S�ẴO���t�B�b�N�f�[�^���폜����
};

void GraphicControler_Init();

void GraphicControler_End();

int LoadGraphEX(string filename);

int LoadDivGraphEX(string filename,int Allnum,int XNum,int YNum,int XSize,int YSize,int *HandleBuf);

int CopyGraph(int GRHandle);

int DeleteGraphEX(int GRHandle);

#endif