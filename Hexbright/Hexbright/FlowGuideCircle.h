#ifndef DEF_FLOWGUIDECIRCLE_H
#define DEF_FLOWGUIDECIRCLE_H

#include"FlowCircle.h"

//実際に起動したらどうなるかをシミュレートするFlowCircle。ゲームに影響を及ぼさない。
class FlowGuideCircle:public FlowCircle{
	//定数
protected:

	//変数
protected:

	//関数
protected:
	void NextConductorProcess(const Stage &stage);

public:
	FlowGuideCircle(PutPos i_blockPos,Vector2D i_drawPos);
	~FlowGuideCircle();
	void Draw(Vector2D center)const;
};

#endif // !DEF_FLOWGUIDECIRCLE_H
#pragma once
