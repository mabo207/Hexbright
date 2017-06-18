#ifndef DEF_PUZZLESYSTEM_H
#define DEF_PUZZLESYSTEM_H

#include<vector>
#include"Stage.h"
#include"PutPos.h"

//��l���̃p�Y���V�X�e����\������
class PuzzleSystem{
	//�^�E�񋓑�
protected:
	//�u���b�N�̓�����H�鏬������
	class FlowCircle{
	protected:
		Vector2D startPos;//�����H�肪�n�܂����ꏊ(���̏ꏊ�̎��ӂɂ��ǂ蒅������H��I��)(��Έʒu)
		int startDir;//�����H�肪�n�܂������̖ړI�Ӕԍ�
		PutPos startBlock;//�����H�肪�n�܂������̃u���b�N�̈ʒu(���̏�񂪔������startPos�ɋ߂Â��Ă��邩���肷��΂悢(�v�Z�ʍ팸))
		bool flowend;//FlowEnd()���Ԃ��l
		float speed;//����
		Vector2D destination;//�ړ���̕`����W(��Έʒu)

		//�V�X�e���p�ϐ�
	public:
		PutPos blockPos;//�ǂ̃u���b�N�̏ꏊ�ɂ��邩
		Vector2D drawPos;//�ǂ̕`��ʒu�ɂ��邩(��Έʒu)
		int beginVertex,endVertex;//�ǂ̕ӂ���ǂ̕ӂɌ������Ă��邩
		bool flowflag;//���ݓ�����H�郂�[�h�ɂȂ��Ă��邩�ǂ���

		//�֐�
	public:
		FlowCircle(PutPos i_blockPos,Vector2D i_drawPos);
		~FlowCircle();
		void Draw(Vector2D center)const;
		void Update(const Stage &stage,const PutPos &cursor,const Vector2D &center);//�ϐ��̍X�V
		bool FlowEnd()const;//�����H��̏I���������̂�true��Ԃ�
		bool Boot(const Stage &stage,const PutPos &cursor);//����������J�n������(���s����false��Ԃ�)
	};

	//�萔
protected:

	//�ϐ�
protected:
	Stage m_stage;//���݂̔Ֆ�
	PutPos m_cursor;//�J�[�\��
	Vector2D m_center;//�����̃}�X�̕`��ʒu
	FlowCircle m_flowCircle;//������H�鏬���Ȋ�
	std::vector<std::shared_ptr<Block>> m_savedBlock;//���ɏo�Ă���u���b�N�ꗗ

	//�֐�
protected:
	void AddSavedBlock();//�u���b�N������߂�
	
public:
	PuzzleSystem();
	~PuzzleSystem();

	void Update();//���t���[���Ăяo���čX�V����
	void Draw()const;
};

#endif // !DEF_PUZZLESYSTEM_H
#pragma once
