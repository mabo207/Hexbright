#ifndef DEF_SCORESYSTEM_H
#define DEF_SCORESYSTEM_H

#include<vector>

#include"PutPos.h"
#include"Stage.h"
#include"ToolsLib.h"

//�X�R�A���Ǘ����A����Ɋւ��鐔�l��\������N���X
class ScoreSystem{
	//�^

	//�萔

	//�ϐ�
protected:
	Easing m_score;//���݂̓��_�\���B
	

	//�`��p�̕ϐ�
	
	//�t�H���g
	const int m_totalScoreFont;//���v���_��\�����邽�߂̃t�H���g
	const int m_blockScoreFont;//�u���b�N�̓��_��\�����邽�߂̃t�H���g

	//�֐�
protected:
	virtual int CalBlockScore(std::shared_ptr<const Block> pb,int count)const;//�u���b�N�������������ɓ����链�_���v�Z����B�L�����ɂ���ĕύX�ł���悤�ɉ��z�֐��Ƃ��邪�A���u�L�����̓��_�v�Z�͂���ɂ���čs���B

public:
	ScoreSystem();
	~ScoreSystem();
	void Update();//�\��������̂̍X�V�i�ʒu�␔�l�Ȃǁj
	void AddBlockScore(const std::vector<PutPos> &blockPosVec,const Stage &stage);//�X�R�A��ǉ�����
	void Draw(Vector2D center)const;//�\���֐�
	int GetScore()const;//���݂̓��_��Ԃ�(m_score.endx�̒l)
};

#endif // !DEF_SCORESYSTEM_H
#pragma once
