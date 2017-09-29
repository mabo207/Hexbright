#ifndef DEF_PUZZLESYSTEM_H
#define DEF_PUZZLESYSTEM_H

#include<vector>
#include"Stage.h"
#include"PutPos.h"
#include"FlowEraseCircle.h"
#include"FlowGuideCircle.h"
#include"ScoreSystem.h"

//��l���̃p�Y���V�X�e����\������
class PuzzleSystem{
	//�^�E�񋓑�
protected:
	
	//�萔
protected:

public:
	static const Vector2D aPuzzleSize;//�P�l���̉�ʂ̑傫��

	//�ϐ�
protected:
	Stage m_stage;//���݂̔Ֆ�
	PutPos m_cursor;//�J�[�\��
	int m_bootVertex;//���Γ_�ƂȂ��
	Vector2D m_center;//�����̃}�X�̕`��ʒu
	std::shared_ptr<ScoreSystem> m_pScore;//�X�R�A
	FlowEraseCircle m_flowCircle;//������H�鏬���Ȋ�
	std::vector<std::shared_ptr<Block>> m_savedBlock;//���ɏo�Ă���u���b�N�ꗗ
	int m_flame;//���݂̃X�^�[�g����̃t���[����

	FlowGuideCircle m_flowGuideCircle;//��������K�C�h

	//�p�Y���S�̂̊Ǘ��N���X�������Ă����ׂ������ȕϐ�
	//���Ԍv�����s�����߂̕ϐ�(�|�[�Y��ʐM���O�ɂ��Ή��ł���d�l)

	//�`��p�ϐ�
	int m_timeFont;//���ԕ\���p�̃t�H���g�n���h��(�p�Y���S�̂̊Ǘ��N���X�������Ă����ׂ�����)

	//�֐�
protected:
	void AddSavedBlock();//�u���b�N������߂�
	void TurnBootVertex(int n);//n�񂾂����v���ɔ��Γ_����]������Bn=0�ł��A���݂̈ʒu�ɔ��Εӂ��Ȃ����n=1�Ɠ�������������i���v�������ň�ԋ߂����ΕӂɈړ�����j
	
public:
	PuzzleSystem();
	~PuzzleSystem();

	void Update();//���t���[���Ăяo���čX�V����
	void Draw()const;

	int GetScore()const;
};

#endif // !DEF_PUZZLESYSTEM_H
#pragma once
