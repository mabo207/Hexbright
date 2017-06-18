#ifndef DEF_PUTPOS_H
#define DEF_PUTPOS_H

#include"ToolsLib.h"

//�X�e�[�W��̃u���b�N�̈ʒu�̍��W�n
//�^�񒆂���ʒu�Ƃ��A�E��(1,0)(x����)�A�E����(0,1)(y����)�ŕ\������
class PutPos{
	//�^�E�񋓑�
public:
	//6�����̒�`(�E���玞�v��菇)(��ʂŌ�����)
	enum Direction{
		RIGHT
		,RIGHTDOWN
		,LEFTDOWN
		,LEFT
		,LEFTUP
		,RIGHTUP
	};
	//�萔
protected:

	//�ϐ�
protected:
	int x,y;

	//�֐�
protected:

public:
	PutPos(int i_x,int i_y):x(i_x),y(i_y){}
	~PutPos(){}
	//���Z�q
	PutPos operator+(const PutPos &otherobj)const{
		return PutPos(x+otherobj.x,y+otherobj.y);
	}
	PutPos operator-(const PutPos &otherobj)const{
		return PutPos(x-otherobj.x,y-otherobj.y);
	}
	PutPos operator*(const int a)const{
		return PutPos(x*a,y*a);
	}
	PutPos operator/(const int a)const{
		return PutPos(x/a,y/a);
	}
	bool operator<(const PutPos &otherobj)const;//x��y�̏��ɑ傫����r
	PutPos operator-()const{
		return (*this)*(-1);
	}
	//�֐�
	size_t size()const;//x��y�̐�Βl�̘a�B�P���m�����B
	Vector2D relativecoordinates(Vector2D upbaseVec)const;//�^��̌����̃u���b�N�̑傫�����߂��x�N�g������A���S����̑��΍��W���o��

	//�ÓI�֐�
	static PutPos BaseVec(Direction dir);//�e�����̒P�ʃx�N�g����Ԃ�
	
};


#endif // !DEF_PUTPOS_H

#pragma once
