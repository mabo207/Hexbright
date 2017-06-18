#define _USE_MATH_DEFINES
#include"PutPos.h"
#include<cmath>

bool PutPos::operator<(const PutPos &otherobj)const{
	//xを優先する
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
	return PutPos(0,0);//ここに来るのはありえない
}

Vector2D PutPos::relativecoordinates(Vector2D upbaseVec)const{
	//upbaseVecは上向きなので長さをrとすると
	//マップ座標(1,0):upbaseVecを反時計回りに90度回転して√3倍伸ばす
	//マップ座標(0,1):(1,0)を-1/2倍し、upbaseVecを-3/2倍したものを足す
	float xRate=((float)x*2-y)/2,yRate=-(float)y*3/2;
	
	Vector2D a=upbaseVec.turn(M_PI/2);
	Vector2D b=a*((float)sqrt(3.0));
	Vector2D c=b*xRate;
	Vector2D d=upbaseVec*yRate;
	Vector2D e=c+d;
	
	return upbaseVec.turn(M_PI/2)*((float)sqrt(3.0))*xRate+upbaseVec*yRate;
}
