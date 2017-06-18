#include"Stage.h"
#include"DxLib.h"
#include<cmath>

//----------------BlockInfo----------------
Stage::BlockInfo::BlockInfo(PutPos i_pos,std::shared_ptr<Block> i_pBlock)
	:pos(i_pos),pBlock(i_pBlock){}

Stage::BlockInfo::~BlockInfo(){}

bool Stage::BlockInfo::operator<(const BlockInfo &otherobj)const{
	//�召�֌W��pos�݂̂Ō��߂�B�Ȃ��Ȃ瓯��Stage�ɂ���u���b�N�͓����ʒu�ɕ������݂��Ă͂����Ȃ����߁B
	return (this->pos<otherobj.pos);
}

//----------------Stage----------------
Stage::Stage(size_t size)
	:m_size(size)
{
	//m_blocks�̏�����
	//�ЂƂ܂���ɂ��Ă���
}

Stage::~Stage(){}

void Stage::Draw(const Vector2D &center)const{
	//�X�e�[�W�̕`��
	int absmax=m_size-1;
	for(int y=-absmax;y<=absmax;y++){
		int bx=max(0-absmax,y-absmax),ex=min(absmax,y+absmax);
		for(int x=bx;x<=ex;x++){
			Vector2D v=center+PutPos(x,y).relativecoordinates(Block::BaseVector);
			Hexagon(v,Block::BaseVector).Draw(GetColor(196,196,196),198);
		}
	}
	//�u���b�N�̕`��
	for(BlockInfo b:m_blocks){
		b.pBlock->Draw();
	}
}

void Stage::PutBlock(const PutPos &pos,const std::shared_ptr<Block> &pblock){
	m_blocks.insert(BlockInfo(pos,pblock));
}
