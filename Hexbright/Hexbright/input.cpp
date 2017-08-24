#define _USE_MATH_DEFINES
#include<iostream>
#include"DxLib.h"
#include"input.h"

//入力関連
static InputControler *inputControler;

int input_update(){
	return inputControler->Update();
}

//キーボード関連
int keyboard_get(int KeyCode){//KeyCodeはキーボードの名前
	return inputControler->Get(KeyCode);
}

//マウス関連
int mouse_get(int MouseCode){
	return inputControler->MouseGet(MouseCode);
}

//アナログジョイパッド関連
Vector2D analogjoypad_get(int InputType){
	int x,y;
	GetJoypadAnalogInput(&x,&y,InputType);
	return Vector2D((float)x,(float)y);
}

//入力情報を全て消す(どのボタンも入力されてないことにする)
void input_erase(){
	inputControler->InitInput();
}

//ボタンを押されたことにする
void keyboard_COMinput(int KeyCode){
	inputControler->COMinput(KeyCode);
}

//入力関連
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
	//keyboardの大きさで順序を決める。
	if(keyboard < otherobj.keyboard){
		return true;
	} else if(keyboard > otherobj.keyboard){
		return false;
	}
	//以下テキトー。矛盾だけ生じないようにしている。
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
	//十字キーによるvの補正
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
	//角度の認識
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
	
	//ジョイパッドボタンとキーボードの対応表
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

	
	//ジョイパッドのアナログスティックとキーボードの対応表
	//(centerに誤差を与えておくことで上下キー入力がdoubleの計算誤差によって左上左下に対応して不可逆入力になるという歪な事態を避ける)
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
	//キーボードの更新
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);//tmpKeyだとtmpKeyの先頭のアドレスを示す
	int tmpPad=0;//ゲームパッドのボタンの入力
	if(GetJoypadNum()>0){
		tmpPad=GetJoypadInputState(DX_INPUT_PAD1);//ジョイパッドが１つでも入力されていれば、１つ目のジョイパッドのボタン入力を受け付ける
	}
	std::set<GamepadKeyboardMap>::iterator cit=m_connectmap.begin(),cite=m_connectmap.end();
	std::set<AnalogJoypadKeyboardMap>::iterator sit=m_stickmap.begin(),site=m_stickmap.end();
	bool cflag,sflag;
	for(int i=0;i<KeyNum;i++){
		cflag=((cit!=cite) && (cit->keyboard)==i);//キーボード入力に対応するパッドボタンが存在すればtrueとなる。
		sflag=((sit!=site) && (sit->keyboard)==i);//キーボード入力に対応するジョイパッドアナログスティックの入力方法が存在すればtrueとなる。
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
	//マウスの更新
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
	//MouseCodeの下からx個目のbitが1ならばm_mouseFlame[x-1]に入力フレーム数が格納されている
	//つまりn回右シフトしたところ1が見えたならばm_mouseFlame[n]を返してあげれば良い
	//ここでは、最下位bitが1のものを1bitずつ左シフトしていき、それとのAND演算によって何bit目に1があるかを検出する
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


