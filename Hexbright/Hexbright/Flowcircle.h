#ifndef DEF_FLOWCIRCLE_H
#define DEF_FLOWCIRCLE_H

#include"Block.h"
#include"PutPos.h"
#include"Stage.h"

//ブロックの導線を辿る小さい丸
class FlowCircle{

	//変数
protected:
	Vector2D startPos;//導線辿りが始まった場所(この場所の周辺にたどり着いたら辿り終了)(絶対位置)
	int startDir;//導線辿りが始まった時の目的辺番号
	PutPos startBlock;//導線辿りが始まった時のブロックの位置(上二つの情報が被ったらstartPosに近づいているか判定すればよい(計算量削減))
	bool flowend;//FlowEnd()が返す値
	float speed;//速さ
	Vector2D destination;//移動先の描画座標(絶対位置)

	 //システム用変数
public:
	PutPos blockPos;//どのブロックの場所にいるか
	Vector2D drawPos;//どの描画位置にいるか(絶対位置)
	int beginVertex,endVertex;//どの辺からどの辺に向かっているか
	bool flowflag;//現在導線を辿るモードになっているかどうか

	 //関数
public:
	FlowCircle(PutPos i_blockPos,Vector2D i_drawPos);
	~FlowCircle();
	void Draw(Vector2D center)const;
	//void Update(PuzzleSystem *system);//変数の更新
	void Update(const Stage &stage,const PutPos &cursor,const Vector2D &center);//変数の更新
	bool FlowEnd()const;//導線辿りの終了した時のみtrueを返す
	bool Boot(const Stage &stage,const PutPos &cursor);//導線巡りを開始させる(失敗時はfalseを返す)
};

#endif // !DEF_FLOWCIRCLE_H
#pragma once
