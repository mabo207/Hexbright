#ifndef DEF_STAGE_H
#define DEF_STAGE_H

#include<memory>
#include<set>
#include"Block.h"
#include"PutPos.h"

//ステージを表現するクラス
//ステージの形は大まかにx軸平行線が存在する凸六角形にし、キャラによって置けない場所(=抜け)が存在する
//抜けは「永久に消去できないお邪魔ブロック」が初期から置かれていることで表現する
class Stage{
	//型・列挙体
protected:
	//どこに何のブロックがあるかをまとめたもの
	struct BlockInfo{
		//変数
		PutPos pos;//位置
		std::shared_ptr<Block> pBlock;//ブロックの情報

		//関数
		BlockInfo(PutPos i_pos,std::shared_ptr<Block> i_pBlock);
		~BlockInfo();

		bool operator<(const BlockInfo &otherobj)const;
	};

	//定数
protected:

	//変数
protected:
	size_t m_size;//ステージの大きさ
	std::set<BlockInfo> m_blocks;//ブロック情報

	//関数
protected:
	
public:
	Stage(size_t size);
	~Stage();
	void Draw(const Vector2D &center)const;//ステージの描画
	bool PutBlock(const PutPos &pos,const std::shared_ptr<Block> &pblock,Vector2D center);//ブロックを設置する、置けない場合はfalseを返す
	bool JudgeInStage(const PutPos &pos)const;//posがステージ内にあるかの判定
	std::shared_ptr<const Block> GetBlock(const PutPos &pos)const;//ブロック情報を取得する
	void EraseBlocks(const std::vector<PutPos> &blockPosVec);//blockPosVecに存在するブロックを全て消去する
};


#endif // !DEF_STAGE_H

#pragma once
