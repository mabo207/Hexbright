#ifndef DEF_TIMEATTACK_H

#include"VGameSystem.h"
#include"PuzzleSystem.h"
#include"input.h"
#include<memory>

//タイムアタックのシステムの実装
class TimeAttack:public VGameSystem{
	//型・列挙体
protected:
	//ゲーム段階を示す
	struct Phase{
		enum Kind{
			BEFORESTART,
			PLAYING,
			GAMEEND,
			RESULT,
			NAMEINPUT,
			END
		};
		static Kind link(int num){
			if(num<0 || num>END){
				return END;
			}
			return static_cast<Kind>(num);
		}
	};
	//定数

	//変数
protected:
	std::shared_ptr<PuzzleSystem> m_puzzle;//動かすパズルは１つだけ
	Phase::Kind m_phase;//現在のゲーム段階
	InputSingleCharStringControler m_nameInputer;//名前入力用
	//int m_timer1,m_timer2;//タイマー

	//関数
protected:

public:
	TimeAttack();
	~TimeAttack();
	int VCalculate();
	void VDraw()const;

};


#endif // !DEF_TIMEATTACK_H
#pragma once
