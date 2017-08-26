#ifndef DEF_SCORESYSTEM_H
#define DEF_SCORESYSTEM_H

#include<vector>

#include"PutPos.h"
#include"Stage.h"
#include"ToolsLib.h"

//�X�R�A���Ǘ����A����Ɋւ��鐔�l��\������N���X
class ScoreSystem{
	//�^
protected:
	//�u���b�N�_���̕`��v�f
	struct BlockScorePos{
		//�萔
	protected:
		static const double singleDegree;//SingleBlockScore()�ɂ�����pos��degree�̏������l
		static const int singleFlame;//SingleBlockScore()�ɂ�����pos��flame�̏������l
		static const double bonusRate;//BonusScore()�ł�SingleBlockScore()��艽�{�����\�������邩
		//�ϐ�
	public:
		std::string score;//�_��
		PositionControl pos;//�\���ʒu
		//�֐�
	protected:
		BlockScorePos(const std::string &i_score,PositionControl i_pos);
	public:
		~BlockScorePos();
		virtual void Draw(int font)const;
		//�ÓI�֐�
		static std::shared_ptr<BlockScorePos> SingleBlockScore(int i_score,Vector2D v);//1�̓����ɂ���ē�����_���̕\��
	};
	struct BonusScorePos:public BlockScorePos{
		BonusScorePos(const std::string &i_score,PositionControl i_pos):BlockScorePos(i_score,i_pos){}
		void Draw(int font)const;
		static std::shared_ptr<BlockScorePos> BonusScore(int i_score,Vector2D v);//�����̃{�[�i�X�ɂ���ē�����_���̕\��
	};

	//�萔

	//�ϐ�
protected:
	Easing m_score;//���݂̓��_�\���B
	
	//�������蒆�̂ݏ�����Ԃł͂Ȃ��Ȃ�ϐ�
	int m_combo;//�A����
	//���̂����AAddBlockScore()�ł̌v�Z�����N�ɂ��邽�߂̓r���o�߂��c���Ă��������̕ϐ�
	int m_flowingScore;//���݂̓�������ŉ҂��ł��链�_

	//�`��p�̕ϐ�
	std::vector<std::shared_ptr<BlockScorePos>> m_scoreTexts;//�u���b�N�̓_���̕\��
	
	//�t�H���g
	const int m_totalScoreFont;//���v���_��\�����邽�߂̃t�H���g
	const int m_blockScoreFont;//�u���b�N�̓��_��\�����邽�߂̃t�H���g

	//�֐�
protected:
	virtual int CalBlockScore(std::shared_ptr<const Block> pb,int count)const;//�u���b�N�������������ɓ����链�_���v�Z����B�L�����ɂ���ĕύX�ł���悤�ɉ��z�֐��Ƃ��邪�A���u�L�����̓��_�v�Z�͂���ɂ���čs���B
	void InitFlowingPal();//�������蒆�̂ݎg�p����l������������

public:
	ScoreSystem();
	~ScoreSystem();
	void Update();//�\��������̂̍X�V�i�ʒu�␔�l�Ȃǁj
	void AddBlockScore(const std::vector<PutPos> &blockPosVec,const Stage &stage);//�����ɂ���u���b�N�̃X�R�A�����Z����BblockPosVec�ɗv�f���P�����ǉ����ꂽ�Ƃ����O��̂��Ǝg�p�����B
	void AddFlowEndScore(bool circlingFlag,const Vector2D &flowCirclePos);//����I�����ɂP������������s���ă{�[�i�X�X�R�A�����Z����B���������s���B
	void Draw(Vector2D center)const;//�\���֐�
	int GetScore()const;//���݂̓��_��Ԃ�(m_score.endx�̒l)
	
};

#endif // !DEF_SCORESYSTEM_H
#pragma once
