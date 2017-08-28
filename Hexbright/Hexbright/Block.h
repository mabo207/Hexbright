#ifndef DEF_BLOCK_H
#define DEF_BLOCK_H

#include<memory>
#include<vector>
#include"Hexagon.h"

//�X�e�[�W��ɒu�����I�u�W�F�N�g
//0�ȏ�3�ȉ��̓��������B�����̒[�_�͐��Z�p�`�̕ӂ̒��_�ɂ���B
class Block{
	//�񋓑́E�^
public:
	//����(�p���������)
	struct Feature{
		enum Kind{
			//��ނ�\���B�܂��A�r�b�g���Z������ΘA���\���̔��肪�ł���
			normal=0x01,
			attack=0x02,
			heal=0x04,
			connect=0xff
		};
		Kind kind;
		Feature(Kind i_kind):kind(i_kind){}
		~Feature(){}
	};
	//����
	struct Conductor{
	private:
		//�����̂Q�[�_�̔ԍ�(0->1��0,...,4->5��4,5->0��5�B%6����ƈ����₷��)
		//���n0<n1�ɂȂ�悤�ɂ���
		int n0,n1;
	public:
		Conductor();//���݂��Ȃ����������
		Conductor(int i_n0,int i_n1);
		void turn(int n);//��]������
		int GetN(int i)const;//n[N]�̒l�����
		int GetOtherN(int n)const;//n�łȂ����̕ʂ̒[�_�ԍ���Ԃ�
		bool JudgeCross(const Conductor &otherobj)const;//��������(����������true)
		bool JudgeExist()const;//���݂��铱�����ifalse�Ȃ����݂������j
	};

	//�萔
protected:
	static const int lineThick;
	static const unsigned int lineColor;

public:
	static const Vector2D BaseVector;

	//�ϐ�
protected:
	std::shared_ptr<Hexagon> m_shape;//�`��E���m�N���`��`��(�ʒu�傫���Ƃǂ̂��炢�Y��ɕ\�����邩)
	std::vector<Conductor> m_conductors;//�����Q
	Feature m_feature;//����(�p�����ꂽ�N���X)

	//�֐�
protected:
	virtual unsigned int GetColor()const;//�u���b�N�̎�ނɂ���Č��肷��F�R�[�h���擾���邽�����f�t�H���g�ł�GetColor(160,160,160)�̊D�F�Ƃ�50%�����Ƃ���B
	virtual unsigned int GetVertexColor()const=0;//�u���b�N�̎�ނɂ���Č��肷��ӂ̐F�R�[�h���擾����B

public:
	Block(std::shared_ptr<Hexagon> shape,const std::vector<Conductor> &conductors,Feature i_feature);
	Block(Vector2D center,const std::vector<Conductor> &conductors,Feature i_feature);
	~Block();

	//���ʂ̊֐�
	void Draw()const;//�u���b�N���w��ʂ�ɕ`��
	void Draw(Vector2D pos)const;//�u���b�N�̈ʒu���w�肵�ĕ`��(���߂Ă���u���b�N�̕`�擙)
	void Draw(Vector2D pos,unsigned int vertexColor,unsigned int conductorColor)const;//�ӂƓ����Q��`�悷��(���������ɒu������ǂ��Ȃ�݂����ȃK�C�h)
	void Draw(Vector2D pos,unsigned int inColor,unsigned int vertexColor,unsigned int conductorColor,int alpha,int conductorThick)const;//�`�揈���̗v�f�S�Ă������Ɏ���
	Conductor GetConductor(int n)const;//�����̔ԍ����炻�̃u���b�N�������Ă��铱����Ԃ�
	Vector2D GetVertexPos(int n)const;//�Ӕԍ����炻�̈ʒu��Ԃ�
	Vector2D GetPos()const;//���S�̐�Έʒu��Ԃ�
	void Turn(int n);//�u���b�N����]������B�����̉�]�ƃA�j���[�V�����̏o��(������͖�����)
	bool JudgeConnect(const Block &otherobj)const;
	virtual int GetBaseScore(int gameMode)const=0;//�u���b�N�̎�ނɂ���Ċ�{���_�����肷��B�Ȃ��A�X�R�A�A�^�b�N��VS���[�h���Ŋ�{���_��ς��邩������Ȃ��̂ň�����n���悤�ɂ��Ă���B
	void Move(Vector2D pos){
		//pos�ɒ��S�𓮂���
		m_shape.get()->Move(pos);
	}
	std::vector<Conductor> GetConductors()const{
		return m_conductors;
	}
	Feature GetFeature()const{
		return m_feature;
	}

	//�ÓI�֐�
	static Vector2D GetVertexPos(int n,Vector2D center);//�u���b�N�̒��S�ʒu����������΁AHexagon��baseVec��BaseVector�ŌŒ�Ȃ̂ŋ��߂���
};

#endif // !DEF_BLOCK_H
#pragma once
