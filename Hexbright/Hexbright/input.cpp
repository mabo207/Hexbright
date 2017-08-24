#define _USE_MATH_DEFINES
#include<iostream>
#include"DxLib.h"
#include"input.h"

//���͊֘A
static InputControler *inputControler;

int input_update(){
	return inputControler->Update();
}

//�L�[�{�[�h�֘A
int keyboard_get(int KeyCode){//KeyCode�̓L�[�{�[�h�̖��O
	return inputControler->Get(KeyCode);
}

//�}�E�X�֘A
int mouse_get(int MouseCode){
	return inputControler->MouseGet(MouseCode);
}

//�A�i���O�W���C�p�b�h�֘A
Vector2D analogjoypad_get(int InputType){
	int x,y;
	GetJoypadAnalogInput(&x,&y,InputType);
	return Vector2D((float)x,(float)y);
}

//���͏���S�ď���(�ǂ̃{�^�������͂���ĂȂ����Ƃɂ���)
void input_erase(){
	inputControler->InitInput();
}

//�{�^���������ꂽ���Ƃɂ���
void keyboard_COMinput(int KeyCode){
	inputControler->COMinput(KeyCode);
}

//���͊֘A
void InitInputControler(){
	inputControler=new InputControler();
}

void DeleteInputControler(){
	if(inputControler!=NULL){
		delete inputControler;
		inputControler=NULL;
	}
}

const std::string InputControler::InitFileName="Database/savedata/InputEdit.csv";

bool InputControler::GamepadKeyboardMap::operator<(const GamepadKeyboardMap &otherobj)const{
	if(keyboard < otherobj.keyboard){
		return true;
	}else if(keyboard > otherobj.keyboard){
		return false;
	}
	return (padbutton < otherobj.padbutton);
}

bool InputControler::GamepadKeyboardMap::operator==(const GamepadKeyboardMap &otherobj)const{
	return (this->keyboard == otherobj.keyboard);
}

bool InputControler::AnalogJoypadKeyboardMap::operator<(const AnalogJoypadKeyboardMap &otherobj)const{
	//keyboard�̑傫���ŏ��������߂�B
	if(keyboard < otherobj.keyboard){
		return true;
	} else if(keyboard > otherobj.keyboard){
		return false;
	}
	//�ȉ��e�L�g�[�B�������������Ȃ��悤�ɂ��Ă���B
	if(center < otherobj.center){
		return true;
	} else if(center > otherobj.center){
		return false;
	}
	if(okerror < otherobj.okerror){
		return true;
	} else if(okerror > otherobj.okerror){
		return false;
	}
	return(sizemin < otherobj.sizemin);
}

bool InputControler::AnalogJoypadKeyboardMap::operator==(const AnalogJoypadKeyboardMap &otherobj)const{
	return (keyboard==otherobj.keyboard);
}

bool InputControler::AnalogJoypadKeyboardMap::JudgeInput()const{
	Vector2D v=analogjoypad_get(DX_INPUT_PAD1);
	//�\���L�[�ɂ��v�̕␳
	if(GetJoypadNum()>0){
		if(keyboard_get(KEY_INPUT_UP)>0){
			v.y-=1000;
		}
		if(keyboard_get(KEY_INPUT_LEFT)>0){
			v.x-=1000;
		}
		if(keyboard_get(KEY_INPUT_RIGHT)>0){
			v.x+=1000;
		}
		if(keyboard_get(KEY_INPUT_DOWN)>0){
			v.y+=1000;
		}
	}
	//�p�x�̔F��
	double radian=v.GetRadian();
	double size=(double)v.size();
if(keyboard_get(KEY_INPUT_NUMPADENTER)==1){
		int poi=0;
	}


	return (std::fmin(std::abs(radian-center),M_PI*2-std::abs(radian-center))<okerror && sizemin<=size);
}

InputControler::InputControler(){
	for(int i=0;i<KeyNum;i++){
		m_keyboardFlame[i]=0;
	}
	for(int i=0;i<MouseButtonNum;i++){
		m_mouseFlame[i]=0;
	}
	
	//�W���C�p�b�h�{�^���ƃL�[�{�[�h�̑Ή��\
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_NUMPADENTER,PAD_INPUT_4));
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_BACK,PAD_INPUT_3));
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_Q,PAD_INPUT_5));
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_R,PAD_INPUT_6));
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_1,PAD_INPUT_7));
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_4,PAD_INPUT_8));
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_UP,PAD_INPUT_UP));
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_LEFT,PAD_INPUT_LEFT));
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_RIGHT,PAD_INPUT_RIGHT));
	m_connectmap.insert(GamepadKeyboardMap(KEY_INPUT_DOWN,PAD_INPUT_DOWN));

	
	//�W���C�p�b�h�̃A�i���O�X�e�B�b�N�ƃL�[�{�[�h�̑Ή��\
	//(center�Ɍ덷��^���Ă������Ƃŏ㉺�L�[���͂�double�̌v�Z�덷�ɂ���č��㍶���ɑΉ����ĕs�t���͂ɂȂ�Ƃ����c�Ȏ��Ԃ������)
	SetJoypadDeadZone(DX_INPUT_PAD1,0.0);
	m_stickmap.insert(AnalogJoypadKeyboardMap(KEY_INPUT_W,-M_PI*2/3+0.0001,M_PI/6,1000));
	m_stickmap.insert(AnalogJoypadKeyboardMap(KEY_INPUT_E,-M_PI/3+0.0001,M_PI/6,1000));
	m_stickmap.insert(AnalogJoypadKeyboardMap(KEY_INPUT_D,0.0001,M_PI/6,1000));
	m_stickmap.insert(AnalogJoypadKeyboardMap(KEY_INPUT_X,M_PI/3+0.0001,M_PI/6,1000));
	m_stickmap.insert(AnalogJoypadKeyboardMap(KEY_INPUT_Z,M_PI*2/3+0.0001,M_PI/6,1000));
	m_stickmap.insert(AnalogJoypadKeyboardMap(KEY_INPUT_A,M_PI+0.0001,M_PI/6,1000));
}

InputControler::~InputControler(){}

int InputControler::Update(){
	//�L�[�{�[�h�̍X�V
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);//tmpKey����tmpKey�̐擪�̃A�h���X������
	int tmpPad=0;//�Q�[���p�b�h�̃{�^���̓���
	if(GetJoypadNum()>0){
		tmpPad=GetJoypadInputState(DX_INPUT_PAD1);//�W���C�p�b�h���P�ł����͂���Ă���΁A�P�ڂ̃W���C�p�b�h�̃{�^�����͂��󂯕t����
	}
	std::set<GamepadKeyboardMap>::iterator cit=m_connectmap.begin(),cite=m_connectmap.end();
	std::set<AnalogJoypadKeyboardMap>::iterator sit=m_stickmap.begin(),site=m_stickmap.end();
	bool cflag,sflag;
	for(int i=0;i<KeyNum;i++){
		cflag=((cit!=cite) && (cit->keyboard)==i);//�L�[�{�[�h���͂ɑΉ�����p�b�h�{�^�������݂����true�ƂȂ�B
		sflag=((sit!=site) && (sit->keyboard)==i);//�L�[�{�[�h���͂ɑΉ�����W���C�p�b�h�A�i���O�X�e�B�b�N�̓��͕��@�����݂����true�ƂȂ�B
		if(tmpKey[i]!=0 || (cflag && (tmpPad & cit->padbutton)!=0) || (sflag && sit->JudgeInput())){
			m_keyboardFlame[i]++;
		}else{
			m_keyboardFlame[i]=0;
		}
		if(cflag){
			cit++;
		}
		if(sflag){
			sit++;
		}
	}
	//�}�E�X�̍X�V
	int mouseinput=GetMouseInput();
	for(int i=0;i<MouseButtonNum;i++){
		if((mouseinput>>i) & 0x01){
			m_mouseFlame[i]++;
		}else{
			m_mouseFlame[i]=0;
		}
	}
	return 0;
}

int InputControler::Get(int KeyCode){
	if(KeyCode>=0 && KeyCode<KeyNum){
		return m_keyboardFlame[KeyCode];
	}
	return 0;
}

int InputControler::MouseGet(int MouseCode){
	//MouseCode�̉�����x�ڂ�bit��1�Ȃ��m_mouseFlame[x-1]�ɓ��̓t���[�������i�[����Ă���
	//�܂�n��E�V�t�g�����Ƃ���1���������Ȃ��m_mouseFlame[n]��Ԃ��Ă�����Ηǂ�
	//�����ł́A�ŉ���bit��1�̂��̂�1bit�����V�t�g���Ă����A����Ƃ�AND���Z�ɂ���ĉ�bit�ڂ�1�����邩�����o����
	int bit=0x01;
	for(int i=0;i<MouseButtonNum;i++){
		if(MouseCode & (bit<<i)){
			return m_mouseFlame[i];
		}
	}
	return 0;
}

void InputControler::InitInput(){
	for(int i=0;i<KeyNum;i++){
		m_keyboardFlame[i]=0;
	}
	for(int i=0;i<MouseButtonNum;i++){
		m_mouseFlame[i]=0;
	}
}

void InputControler::COMinput(int KeyCode){
	if(KeyCode>=0 && KeyCode<KeyNum){
		m_keyboardFlame[KeyCode]++;
	}
}

void InputControler::AddConnectMap(int KeyCode,int PadButton){
	m_connectmap.insert(GamepadKeyboardMap(KeyCode,PadButton));
}

void InputControler::MapSaving(){

}


