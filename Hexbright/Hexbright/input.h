#ifndef DEF_INPUT_H
#define DEF_INPUT_H


#include"ToolsLib.h"
#include<set>
#include<string>

//キーボード関連
int input_update();

int keyboard_get(int KeyCode);

int mouse_get(int MouseCode);

Vector2D analogjoypad_get(int InputType);

void input_erase();//入力情報を全て消す(どのボタンも入力されてないことにする)

void keyboard_COMinput(int KeyCode);//ボタンを押されたことにする

//入力関連
void InitInputControler();

void DeleteInputControler();

class InputControler{
	//型
protected:
	//ゲームパッドのボタンとキーボードの対応をする構造体
	struct GamepadKeyboardMap{
		int keyboard;
		int padbutton;
		bool operator<(const GamepadKeyboardMap &otherobj)const;
		bool operator==(const GamepadKeyboardMap &otherobj)const;
		GamepadKeyboardMap(int i_keyboard,int i_padbutton)
			:keyboard(i_keyboard),padbutton(i_padbutton){}
		~GamepadKeyboardMap(){}
	};
	//ゲームパッドのジョイパッドの入力状態とキーボードの対応をする構造体
	struct AnalogJoypadKeyboardMap{
		int keyboard;//対応キーボード入力
		double center;//中心の角度
		double okerror;//許容誤差角度幅
		double sizemin;//必要な入力の大きさ
		bool operator<(const AnalogJoypadKeyboardMap &otherobj)const;
		bool operator==(const AnalogJoypadKeyboardMap &otherobj)const;
		AnalogJoypadKeyboardMap(int i_keyboard,double i_center,double i_okerror,double i_sizemin)
			:keyboard(i_keyboard),center(i_center),okerror(i_okerror),sizemin(i_sizemin){}
		~AnalogJoypadKeyboardMap(){}
		bool JudgeInput()const;
	};

	//定数
	static const std::string InitFileName;
	static const int KeyNum=256;//キーボードの入力キー数
	static const int MouseButtonNum=8;//マウスの入力ボタン数

	//変数
	int m_keyboardFlame[KeyNum];//各キーボードが入力されたフレーム数
	int m_mouseFlame[MouseButtonNum];//各マウスのボタンが入力されたフレーム数
	std::set<GamepadKeyboardMap> m_connectmap;//ゲームパッドとキーボードの対応表
	std::set<AnalogJoypadKeyboardMap> m_stickmap;//アナログスティックとキーボードの対応表

	//関数
protected:

public:
	InputControler();
	~InputControler();
	int Update();
	int Get(int KeyCode);
	int MouseGet(int MouseCode);
	void InitInput();
	void COMinput(int KeyCode);
	void AddConnectMap(int KeyCode,int PadButton);
	void MapSaving();
};

#endif