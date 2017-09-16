#ifndef DEF_TITLE_H
#define DEF_TITLE_H

#include<memory>
#include"VGameSystem.h"
#include"DisplayRanking.h"

//タイトル画面
class Title{
	//型・列挙体

	//定数

	//変数
protected:
	std::shared_ptr<VGameSystem> m_game;
	std::shared_ptr<DisplayRanking> m_ranking;
	int m_process;//0:タイトル 1:ゲーム 2:ランキング表示

	int m_font;

	//関数
public:
	Title();
	~Title();
	int Calculate();
	void Draw()const;

};


#endif // !DEF_TITLE_H
#pragma once
