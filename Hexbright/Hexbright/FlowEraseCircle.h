#ifndef DEF_FLOWERASECIRCLE_H
#define DEF_FLOWERASECIRCLE_H

#include"FlowCircle.h"

//ブロックの導線を辿る小さい丸
class FlowEraseCircle:public FlowCircle{
	//定数
protected:

	//変数
protected:

public:
	std::vector<PutPos> blockPosVec;//経由したブロックの位置群(先頭に近いほど初めに通ったブロックになる)
	std::shared_ptr<ScoreSystem> m_pScoreSystem;//点数の加算先

	 //関数
protected:
	void NextConductorProcess(const Stage &stage);

public:
	FlowEraseCircle(PutPos i_blockPos,Vector2D i_drawPos,std::shared_ptr<ScoreSystem> i_pScoreSystem);
	~FlowEraseCircle();
	void Draw(Vector2D center)const;
	bool Boot(const Stage &stage,const PutPos &cursor,const int bootVertex);
};

#endif // !DEF_FLOWERASECIRCLE_H
#pragma once
