#ifndef DEF_PUTPOS_H
#define DEF_PUTPOS_H

#include"ToolsLib.h"

//ステージ上のブロックの位置の座標系
//真ん中を基準位置とし、右を(1,0)(x方向)、右下を(0,1)(y方向)で表現する
class PutPos{
	//型・列挙体
public:
	//6方向の定義(右から時計回り順)(画面で見た時)
	enum Direction{
		RIGHT
		,RIGHTDOWN
		,LEFTDOWN
		,LEFT
		,LEFTUP
		,RIGHTUP
	};
	//定数
protected:

	//変数
protected:
	int x,y;

	//関数
protected:

public:
	PutPos(int i_x,int i_y):x(i_x),y(i_y){}
	~PutPos(){}
	//演算子
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
	bool operator<(const PutPos &otherobj)const;//x→yの順に大きさ比較
	PutPos operator-()const{
		return (*this)*(-1);
	}
	//関数
	size_t size()const;//xとyの絶対値の和。１次ノルム。
	Vector2D relativecoordinates(Vector2D upbaseVec)const;//真上の向きのブロックの大きさを定める基準ベクトルから、中心からの相対座標を出す

	//静的関数
	static PutPos BaseVec(Direction dir);//各方向の単位ベクトルを返す
	
};


#endif // !DEF_PUTPOS_H

#pragma once
