#ifndef DEF_STAGE_H
#define DEF_STAGE_H

#include<memory>
#include<set>
#include"Block.h"
#include"PutPos.h"

//�X�e�[�W��\������N���X
//�X�e�[�W�̌`�͑�܂���x�����s�������݂���ʘZ�p�`�ɂ��A�L�����ɂ���Ēu���Ȃ��ꏊ(=����)�����݂���
//�����́u�i�v�ɏ����ł��Ȃ����ז��u���b�N�v����������u����Ă��邱�Ƃŕ\������
class Stage{
	//�^�E�񋓑�
protected:
	//�ǂ��ɉ��̃u���b�N�����邩���܂Ƃ߂�����
	struct BlockInfo{
		//�ϐ�
		PutPos pos;//�ʒu
		std::shared_ptr<Block> pBlock;//�u���b�N�̏��

		//�֐�
		BlockInfo(PutPos i_pos,std::shared_ptr<Block> i_pBlock);
		~BlockInfo();

		bool operator<(const BlockInfo &otherobj)const;
	};

	//�萔
protected:

	//�ϐ�
protected:
	size_t m_size;//�X�e�[�W�̑傫��
	std::set<BlockInfo> m_blocks;//�u���b�N���

	//�֐�
protected:
	
public:
	Stage(size_t size);
	~Stage();
	void Draw(const Vector2D &center)const;//�X�e�[�W�̕`��
	bool PutBlock(const PutPos &pos,const std::shared_ptr<Block> &pblock,Vector2D center);//�u���b�N��ݒu����A�u���Ȃ��ꍇ��false��Ԃ�
	bool JudgeInStage(const PutPos &pos)const;//pos���X�e�[�W���ɂ��邩�̔���
	std::shared_ptr<const Block> GetBlock(const PutPos &pos)const;//�u���b�N�����擾����
	void EraseBlocks(const std::vector<PutPos> &blockPosVec);//blockPosVec�ɑ��݂���u���b�N��S�ď�������
};


#endif // !DEF_STAGE_H

#pragma once
