#ifndef DEF_FLOWGUIDECIRCLE_H
#define DEF_FLOWGUIDECIRCLE_H

#include"FlowCircle.h"

//実際に起動したらどうなるかをシミュレートするFlowCircle。ゲームに影響を及ぼさない。
class FlowGuideCircle:public FlowCircle{
	//定数
protected:

	//変数
protected:
	std::vector<Vector2D> m_pointPoss;//折れ線の折れる座標群

	//関数
protected:
	void NextConductorProcess(const Stage &stage);

public:
	FlowGuideCircle(PutPos i_blockPos,Vector2D i_drawPos);
	~FlowGuideCircle();
	bool Boot(const Stage &stage,const PutPos &cursor,const int bootVertex);//m_pointPossを初期化する
	void Draw(Vector2D center)const;
};

#endif // !DEF_FLOWGUIDECIRCLE_H
#pragma once
