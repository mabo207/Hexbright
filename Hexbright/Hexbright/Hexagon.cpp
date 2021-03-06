#define _USE_MATH_DEFINES
#include"DxLib.h"
#include"Hexagon.h"

//---------------Vertexs----------------
Hexagon::Vertexs::Vertexs(Vector2D i_p0,Vector2D i_p1,Vector2D i_p2,Vector2D i_p3,Vector2D i_p4,Vector2D i_p5){
	p[0]=i_p0;
	p[1]=i_p1;
	p[2]=i_p2;
	p[3]=i_p3;
	p[4]=i_p4;
	p[5]=i_p5;
}

Vector2D Hexagon::Vertexs::GetPoint(int n)const{
	if(n>=0 && n<vnum){
		return p[n];
	}
	return Vector2D(0,0);
}

bool Hexagon::Vertexs::SetPoint(int n,Vector2D v){
	if(n>=0 && n<vnum){
		p[n]=v;
		return true;
	}
	return false;
}


//---------------Hexagon----------------
Hexagon::Hexagon(Vector2D center,Vector2D baseVector)
	:m_center(center),m_baseVector(baseVector){}

Hexagon::~Hexagon(){}

Hexagon::Vertexs Hexagon::GetPoints()const{
	return GetPoints(m_center);
}

Hexagon::Vertexs Hexagon::GetPoints(Vector2D pos)const{
	/*
	return Vertexs(
		Vector2D(pos+m_baseVector.turn(M_PI*0/3)),
		Vector2D(pos+m_baseVector.turn(M_PI*1/3)),
		Vector2D(pos+m_baseVector.turn(M_PI*2/3)),
		Vector2D(pos+m_baseVector.turn(M_PI*3/3)),
		Vector2D(pos+m_baseVector.turn(M_PI*4/3)),
		Vector2D(pos+m_baseVector.turn(M_PI*5/3))
	);
	//*/
	return GetPoints(pos,m_baseVector);
}

void Hexagon::Draw(unsigned int color,int alpha)const{
	Draw(m_center,color,alpha,color,1);
}

void Hexagon::Draw(unsigned int color,int alpha,unsigned int linecolor)const{
	Draw(m_center,color,alpha,linecolor,1);
}

void Hexagon::Draw(Vector2D pos,unsigned int color,int alpha)const{
	Draw(pos,color,alpha,color,1);
}

void Hexagon::Draw(Vector2D pos,unsigned int color,int alpha,unsigned int linecolor,int lineThick)const{
	//頂点6つを求める
	Vertexs vs=GetPoints(pos);
	//中の描画(隣接する２点と中心点による三角形を６つ描画する)
	//中を初めに描画しないと辺が中とは違った色に見えなくなる
	if(alpha>0){
		int originmode,originpal;
		GetDrawBlendMode(&originmode,&originpal);
		if(originmode!=DX_BLENDMODE_ALPHA){
			originpal=255;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,alpha*originpal/255);
		for(int i=0;i<vs.vnum;i++){
			DrawTriangle((int)(vs.GetPoint(i%vs.vnum).x),(int)(vs.GetPoint(i%vs.vnum).y)
				,(int)(vs.GetPoint((i+1)%vs.vnum).x),(int)(vs.GetPoint((i+1)%vs.vnum).y)
				,(int)(pos.x),(int)(pos.y)
				,color,TRUE);
		}
		SetDrawBlendMode(originmode,originpal);
	}
	//辺の描画
	for(int i=0;i<vs.vnum;i++){
		DrawLine((int)(vs.GetPoint(i%vs.vnum).x),(int)(vs.GetPoint(i%vs.vnum).y)
			,(int)(vs.GetPoint((i+1)%vs.vnum).x),(int)(vs.GetPoint((i+1)%vs.vnum).y)
			,linecolor,lineThick);
	}

}

Hexagon::Vertexs Hexagon::GetPoints(Vector2D center,Vector2D baseVec){
	return Vertexs(
		Vector2D(center+baseVec.turn(M_PI*0/3)),
		Vector2D(center+baseVec.turn(M_PI*1/3)),
		Vector2D(center+baseVec.turn(M_PI*2/3)),
		Vector2D(center+baseVec.turn(M_PI*3/3)),
		Vector2D(center+baseVec.turn(M_PI*4/3)),
		Vector2D(center+baseVec.turn(M_PI*5/3))
	);
}
