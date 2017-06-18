#ifndef DEF_PUZZLESYSTEM_H
#define DEF_PUZZLESYSTEM_H

#include<vector>
#include"Stage.h"
#include"PutPos.h"

//一人分のパズルシステムを表現する
class PuzzleSystem{
	//型・列挙体
protected:
	//ブロックの導線を辿る小さい丸
	class FlowCircle{
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
		void Update(const Stage &stage,const PutPos &cursor,const Vector2D &center);//変数の更新
		bool FlowEnd()const;//導線辿りの終了した時のみtrueを返す
		bool Boot(const Stage &stage,const PutPos &cursor);//導線巡りを開始させる(失敗時はfalseを返す)
	};

	//定数
protected:

	//変数
protected:
	Stage m_stage;//現在の盤面
	PutPos m_cursor;//カーソル
	Vector2D m_center;//中央のマスの描画位置
	FlowCircle m_flowCircle;//導線を辿る小さな丸
	std::vector<std::shared_ptr<Block>> m_savedBlock;//次に出てくるブロック一覧

	//関数
protected:
	void AddSavedBlock();//ブロックを一つ貯める
	
public:
	PuzzleSystem();
	~PuzzleSystem();

	void Update();//毎フレーム呼び出して更新する
	void Draw()const;
};

#endif // !DEF_PUZZLESYSTEM_H
#pragma once
