#include"Stage.h"
#include"DxLib.h"
#include<cmath>

//----------------BlockInfo----------------
Stage::BlockInfo::BlockInfo(PutPos i_pos,std::shared_ptr<Block> i_pBlock)
	:pos(i_pos),pBlock(i_pBlock){}

Stage::BlockInfo::~BlockInfo(){}

bool Stage::BlockInfo::operator<(const BlockInfo &otherobj)const{
	//大小関係はposのみで決める。なぜなら同じStageにあるブロックは同じ位置に複数存在してはいけないため。
	return (this->pos<otherobj.pos);
}

//----------------Stage----------------
Stage::Stage(size_t size)
	:m_size(size)
{
	//m_blocksの初期化
	//ひとまず空にしておく
}

Stage::~Stage(){}

void Stage::Draw(const Vector2D &center)const{
	//ステージの描画
	int absmax=m_size-1;
/*
	for(int y=-absmax;y<=absmax;y++){
		int bx=max(0-absmax,y-absmax),ex=min(absmax,y+absmax);
		for(int x=bx;x<=ex;x++){
			Vector2D v=center+PutPos(x,y).relativecoordinates(Block::BaseVector);
			Hexagon(v,Block::BaseVector).Draw(GetColor(196,196,196),198);
		}
	}
//*/
	for(int y=-absmax;y<=absmax;y++){
		for(int x=-absmax;x<=absmax;x++){
			if(JudgeInStage(PutPos(x,y))){
				Vector2D v=center+PutPos(x,y).relativecoordinates(Block::BaseVector);
				Hexagon(v,Block::BaseVector).Draw(GetColor(196,196,196),198);
			}
		}
	}
	//ブロックの描画
	for(BlockInfo b:m_blocks){
		b.pBlock->Draw();
	}
}

bool Stage::PutBlock(const PutPos &pos,const std::shared_ptr<Block> &pblock,Vector2D center){
	pblock.get()->Move(center+pos.relativecoordinates(Block::BaseVector));
	return m_blocks.insert(BlockInfo(pos,pblock)).second;
}

bool Stage::JudgeInStage(const PutPos &pos)const{
	return (std::abs(pos.GetX())<m_size && std::abs(pos.GetY())<m_size && std::abs(pos.GetY()-pos.GetX())<m_size);
}

std::shared_ptr<const Block> Stage::GetBlock(const PutPos &pos)const{
	//キー検索はposのみでできるのでこれでよい
	std::set<BlockInfo>::const_iterator it=m_blocks.find(BlockInfo(pos,std::shared_ptr<Block>(nullptr)));
	if(it!=m_blocks.end()){
		return it->pBlock;
	}
	//もしブロックが存在しなければnullptrを返す
	return std::shared_ptr<const Block>(nullptr);
}

void Stage::EraseBlocks(const std::vector<PutPos> &blockPosVec){
	//事前にblockPosVecをソートすれば高速化できそうな気がするし、m_blocks.erase()にBlockInfoのvectorを入れても同じ機能で効率が良い気もしなくはないけど、バグを防ぐために必要になるまで高速化はしないでおく。
	for(const PutPos &p:blockPosVec){
		std::set<BlockInfo>::iterator it=m_blocks.find(BlockInfo(p,std::shared_ptr<Block>(nullptr)));
		if(it!=m_blocks.end()){
			m_blocks.erase(it);
		}
	}
}
