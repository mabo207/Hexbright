#define _USE_MATH_DEFINES
#include"PutPos.h"
#include<cmath>

bool PutPos::operator<(const PutPos &otherobj)const{
	//x��D�悷��
	if(x<otherobj.x){
		return true;
	}else if(x>otherobj.x){
		return false;
	}
	if(y<otherobj.y){
		return true;
	} else if(y>otherobj.y){
		return false;
	}
	return false;
}

size_t PutPos::size()const{
	return abs(x)+abs(y);
}

PutPos PutPos::BaseVec(Direction dir){
	switch(dir){
	case(RIGHT):
		return PutPos(1,0);
	case(RIGHTDOWN):
		return PutPos(1,1);
	case(LEFTDOWN):
		return PutPos(0,1);
	case(LEFT):
		return -BaseVec(RIGHT);
	case(LEFTUP):
		return -BaseVec(RIGHTDOWN);
	case(RIGHTUP):
		return -BaseVec(LEFTDOWN);
	}
	return PutPos(0,0);//�����ɗ���̂͂��肦�Ȃ�
}

Vector2D PutPos::relativecoordinates(Vector2D upbaseVec)const{
	//upbaseVec�͏�����Ȃ̂Œ�����r�Ƃ����
	//�}�b�v���W(1,0):upbaseVec�𔽎��v����90�x��]���ā�3�{�L�΂�
	//�}�b�v���W(0,1):(1,0)��-1/2�{���AupbaseVec��-3/2�{�������̂𑫂�
	float xRate=((float)x*2-y)/2,yRate=-(float)y*3/2;
	
	Vector2D a=upbaseVec.turn(M_PI/2);
	Vector2D b=a*((float)sqrt(3.0));
	Vector2D c=b*xRate;
	Vector2D d=upbaseVec*yRate;
	Vector2D e=c+d;
	
	return upbaseVec.turn(M_PI/2)*((float)sqrt(3.0))*xRate+upbaseVec*yRate;
}
