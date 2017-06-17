#include<iostream>
#include<cassert>
#include"DxLib.h"
#include"GraphicControl.h"


using namespace std;



/*GraphicControlClass��p���邽�߂̊֐�*/
static GraphicControlClass *GraphicControler=NULL;

void hogehogehogehoge(){
	GraphicControlClass *g=GraphicControler;
}

void GraphicControler_Init(){
	GraphicControler=new GraphicControlClass;
	int i=0;
}

void GraphicControler_End(){
	if(GraphicControler!=NULL){
		GraphicControler->InitGraphEX();
		delete GraphicControler;
		GraphicControler=NULL;
	}
}

int LoadGraphEX(string filename){
	if(GraphicControler==NULL){
		return -1;
	}
	return GraphicControler->LoadGraphEX(filename);
}

int LoadDivGraphEX(string filename,int Allnum,int XNum,int YNum,int XSize,int YSize,int *HandleBuf){
	if(GraphicControler==NULL){
		return -1;
	}
	return GraphicControler->LoadDivGraphEX(filename,Allnum,XNum,YNum,XSize,YSize,HandleBuf);
}

int CopyGraph(int GRHandle){
	return GraphicControler->CopyGraph(GRHandle);
}

int DeleteGraphEX(int GRHandle){
	if(GraphicControler==NULL){
		return -1;
	}
	return GraphicControler->DeleteGraphEX(GRHandle);
}

/*GraphicControlClass*///������`����GraphicData���̖߂�l�̏������ɒ��ӁI�I
//m_Graphic�̒�����~�����f�[�^��T��(�������O�̂��͈̂�Ԕz��ԍ��̏��������̂��Ԃ��Ă���)
vector<GraphicControlClass::GraphicData>::iterator GraphicControlClass::GraphicSearch(int GRHandle){
	//�C�e���[�^��p��
	vector<GraphicData>::iterator pGraphic=m_Graphic.begin();
	for(;pGraphic!=m_Graphic.end();pGraphic++){
		if(pGraphic->m_handle==GRHandle){
			return pGraphic;
		}
	}
	//���������Ȃ��C�e���[�^��End�̃C�e���[�^�B�G���[����m_Graphic.End()��Ԃ�
	return m_Graphic.end();
}

vector<GraphicControlClass::GraphicData>::iterator GraphicControlClass::GraphicSearch(string GRName){
	//�C�e���[�^��p��
	vector<GraphicData>::iterator pGraphic=m_Graphic.begin();
	for(;pGraphic!=m_Graphic.end();pGraphic++){
		if(pGraphic->m_name==GRName){
			return pGraphic;
		}
	}
	//���������Ȃ��C�e���[�^��End�̃C�e���[�^�B�G���[����m_Graphic.End()��Ԃ�
	return m_Graphic.end();
}

//�O���t�B�b�N�̓ǂݍ���
int GraphicControlClass::LoadGraphEX(string filename){
	//�܂������f�[�^���Ȃ������m�F����B
	vector<GraphicData>::iterator pData=GraphicSearch(filename);
	if( pData != m_Graphic.end() ){//�����f�[�^������Ȃ�
		pData->m_number++;//�O���t�B�b�N�f�[�^�̗p�����Ă���ӏ��𑝂₷�B
		return pData->m_handle;//�O���t�B�b�N�n���h����Ԃ�
	}
	//�����f�[�^���Ȃ���Ζ����Ƀf�[�^��ǉ�
	const int GRHandle=LoadGraph(filename.c_str());
	if(GRHandle!=-1){//�G���[���N���Ă��Ȃ����
		m_Graphic.push_back(GraphicData(GRHandle,filename,1));//m_Graphic�Ƀf�[�^��ǉ��B1�ӏ��ŗp�����Ă���
	}
	return GRHandle;
}

//�O���t�B�b�N�̕����ǂݍ���
int GraphicControlClass::LoadDivGraphEX(string filename,int Allnum,int XNum,int YNum,int XSize,int YSize,int *HandleBuf){
	//��������0�ȉ��Ȃ玸�s
	if(Allnum<=0){
		return -1;
	}
	int flag=0;//�������ǂ����̃t���O
	//���O�ƕ������Ń_�u���̑��݂�����
	vector<DivGraphicData>::iterator pData=m_DivGraphic.begin();
	for(;pData!=m_DivGraphic.end();pData++){
		if(pData->m_name==filename && pData->m_divNUM==Allnum){//����Ă�����
			break;//�C�e���[�^�����̂܂܂ɂ��ĕԂ�
		}
	}
	//�_�u�����ݎ�
	if(pData!=m_DivGraphic.end()){
		//m_DivGraphic�̕ҏW
		pData->m_number++;
		//m_Graphic�̕ҏW
		for(int i=0;i<Allnum;i++){
			vector<GraphicData>::iterator pGdata=GraphicSearch(pData->m_handle[i]);
			if(pGdata!=m_Graphic.end()){//������i�Ԗڂ̃f�[�^�����݂��Ă���Ȃ��
				HandleBuf[i]=pData->m_handle[i];//HandleBuf�Ƀn���h�������Ă�����
				pGdata->m_number++;//�g���Ă���񐔂𑝂₷
			}else{
				HandleBuf[i]=-1;//i�Ԗڂ����ǂݍ��ݎ��s
				flag=-1;//�S�̂Ƃ��Ă͎��s
				assert(1==0);
			}
		}
	}
	//�_�u���񑶍ݎ�
	else{
		flag=LoadDivGraph(filename.c_str(),Allnum,XNum,YNum,XSize,YSize,HandleBuf);//�����ǂݍ��݂��s��
		if(flag==0){//�ǂݍ��ݐ�����
			//m_DivGraphic�̕ҏW
			/*int *pointer=new int [Allnum];
			for(int i=0;i<Allnum;i++){
				pointer[i]=HandleBuf[i];
			}*/
			m_DivGraphic.push_back(DivGraphicData(NULL,filename,1,Allnum));
			m_DivGraphic.back().m_handle=new int [Allnum];
			for(int i=0;i<Allnum;i++){
				m_DivGraphic.back().m_handle[i]=HandleBuf[i];
			}
			//m_Graphic�̕ҏW
			for(int i=0;i<Allnum;i++){
				m_Graphic.push_back(GraphicData(HandleBuf[i],filename,1));
			}
		}
	}
	return flag;
}

//�O���t�B�b�N�̕���
int GraphicControlClass::CopyGraph(int GRHandle){
	//�Y������O���t�B�b�N�̌���
	vector<GraphicData>::iterator Data=GraphicSearch(GRHandle);
	//Data���Ӗ��̂Ȃ��C�e���[�^���w���Ă��鎞�̓G���[�Ƃ��ď����B
	if(Data==m_Graphic.end()){
		return -1;
	}else{
		//�����łȂ��ꍇ�A�g���ӏ��̃J�E���g��1���₹�Ηǂ�
		Data->m_number++;
	}
	return Data->m_handle;
}

//�O���t�B�b�N�̍폜
int GraphicControlClass::DeleteGraphEX(int GRHandle){
	int returnnum=0;//�߂�l
	//m_Graphic����T��
	vector<GraphicData>::iterator pData=GraphicSearch(GRHandle);
	if(pData==m_Graphic.end()){//�f�[�^��������Ȃ������ꍇ
		returnnum=DeleteGraph(GRHandle);//�Ƃ肠����DeleteGraph�Ɠ�������������悤�ɂ���
	}else{
		//�f�[�^�����������ꍇ
		string GRName=pData->m_name;//��X���O�͗p����̂ŕۑ�
		pData->m_number--;//�g���Ă���ӏ���1���炷
		if(pData->m_number <= 0){//�g���Ă���ꏊ���Ȃ����
			//���̏ꏊ��j������
			returnnum=DeleteGraph(pData->m_handle);//�O���t�B�b�N�f�[�^�̍폜
			m_Graphic.erase(pData);//vector�̗v�f�̍폜
			m_Graphic.shrink_to_fit();//���ёւ�
			//�폜��Ƃ��I������Am_DivGraphic�̕ҏW
			//�폜�����f�[�^�ɂ��āA���ꂪ�����ǂݍ��݂��Ă������A
			//����Ɠ������O�̃O���t�B�b�N�����݂��Ă��Ȃ����m_DivGraph�����菜��
			//for(vector<DivGraphicData>::iterator pd=m_DivGraphic.begin();pd!=m_DivGraphic.end();pd++){
			vector<DivGraphicData>::iterator pd=m_DivGraphic.begin();
			while(true){
				vector<DivGraphicData>::iterator pdtmp=m_DivGraphic.end();
				if(pd==m_DivGraphic.end()){
					break;
				}
				bool eraseflag=false;//�v�f���������ǂ���
				//�܂����O�̈�v������
				if(pd->m_name==GRName){
					//���Ƀf�[�^�̏������Ă��邩������
					eraseflag=true;//�Ƃ肠���������t���O�𗧂ĂĂ���
					for(int i=0;i<pd->m_divNUM;i++){
						if(GraphicSearch(pd->m_handle[i])!=m_Graphic.end()){//�O���t�B�b�N�����݂��Ă���Ȃ��
							eraseflag=false;//�����ɍ���Ȃ���Ώ����Ȃ����ɂ���
							break;
						}
					}
					if(eraseflag){//true�̂܂܂Ȃ��(�S�ď����Ă���Ȃ��)
						//m_DivGraphic����v�f������
						pd=m_DivGraphic.erase(pd);
						//m_DivGraphic.shrink_to_fit();
						int hhhh=0;
					}
				}
				if(!eraseflag){//m_DivGraphic.erase()�����ĂȂ����͎��̃C�e���[�^�������ɂ̓C�e���[�^�𓮂����Ȃ��Ƃ����Ȃ�
					pd++;//while���[�v�̏I���pd�����̃C�e���[�^�ɓ�����
				}
			}
		}
	}
	
	return returnnum;
}

//�S�ẴO���t�B�b�N�f�[�^�̍폜
int GraphicControlClass::InitGraphEX(){
	while(!m_Graphic.empty()){
		DeleteGraph(m_Graphic.begin()->m_handle);
		m_Graphic.erase(m_Graphic.begin());
	}
	m_Graphic.shrink_to_fit();
	return 0;
}

GraphicControlClass::GraphicData::GraphicData(int handle,string name,int number)
	:m_handle(handle),m_name(name),m_number(number){}

GraphicControlClass::GraphicData::~GraphicData(){}

GraphicControlClass::GraphicControlClass(){

}

GraphicControlClass::~GraphicControlClass(){}
