#ifndef DEF_HEXAGON_H
#define DEF_HEXAGON_H

#include"ToolsLib.h"

//�Z�p�`�ɂ��ẴN���X
class Hexagon{
	//�\���́E�񋓑�
public:
	//���_�W�����Ӗ�����B�U��Vector2D�^�z��Ȃ��������A�U�ł��鎖��ۏ؂��邽�ߍ�����B
	struct Vertexs{
		//�萔
	public:
		static const size_t vnum=6;//���_��
		//�ϐ�
	private:
		Vector2D p[vnum];
		//�֐�
	public:
		Vertexs(Vector2D i_p0,Vector2D i_p1,Vector2D i_p2,Vector2D i_p3,Vector2D i_p4,Vector2D i_p5);
		Vector2D GetPoint(int n)const;
		bool SetPoint(int n,Vector2D v);
	};
	
public:

	//�ϐ�
protected:
	Vector2D m_center;//���S�_
	Vector2D m_baseVector;//��x�N�g��

	//�֐�
protected:

public:
	Hexagon(Vector2D center,Vector2D baseVector);
	~Hexagon();

	//�ϐ��̒��g��Ԃ�
	Vector2D GetCenter()const{
		return m_center;
	}
	Vector2D GetBaseVector()const{
		return m_baseVector;
	}

	//�@�\
	void Draw(unsigned int color,int alpha)const;//�`��(���ƕӂ͓����F�n���Aalpha�͒��̓����x)
	void Draw(unsigned int color,int alpha,unsigned int incolor)const;//�`��(���ƕӂ͌ʂɐF���w���Aalpha�͒��̓����x)
	void Draw(Vector2D pos,unsigned int color,int alpha)const;//�`��(���ƕӂ͓����F�n���Aalpha�͒��̓����x)
	void Draw(Vector2D pos,unsigned int color,int alpha,unsigned int incolor)const;//�`��(���ƕӂ͌ʂɐF���w���Aalpha�͒��̓����x)
	Vertexs GetPoints()const;//���_�U�̍��W�����߂�
	Vertexs GetPoints(Vector2D pos)const;//pos�𒆐S�Ƃ������̒��_�U�̍��W�����߂�
	void Move(Vector2D pos){
		//pos�ɒ��S�_���ڂ�
		m_center=pos;
	}

	//�ÓI�֐�
	static Vertexs GetPoints(Vector2D center,Vector2D baseVec);
};


#endif // !DEF_HEXAGON_H
#pragma once
