#ifndef DEF_HEXAGON_H
#define DEF_HEXAGON_H

#include"ToolsLib.h"

//六角形についてのクラス
class Hexagon{
	//構造体・列挙体
public:
	//頂点集合を意味する。６個のVector2D型配列なだけだが、６個である事を保証するため作った。
	struct Vertexs{
		//定数
	public:
		static const size_t vnum=6;//頂点数
		//変数
	private:
		Vector2D p[vnum];
		//関数
	public:
		Vertexs(Vector2D i_p0,Vector2D i_p1,Vector2D i_p2,Vector2D i_p3,Vector2D i_p4,Vector2D i_p5);
		Vector2D GetPoint(int n)const;
		bool SetPoint(int n,Vector2D v);
	};
	
public:

	//変数
protected:
	Vector2D m_center;//中心点
	Vector2D m_baseVector;//基準ベクトル

	//関数
protected:

public:
	Hexagon(Vector2D center,Vector2D baseVector);
	~Hexagon();

	//変数の中身を返す
	Vector2D GetCenter()const{
		return m_center;
	}
	Vector2D GetBaseVector()const{
		return m_baseVector;
	}

	//機能
	void Draw(unsigned int color,int alpha)const;//描画(中と辺は同じ色系統、alphaは中の透明度)
	void Draw(unsigned int color,int alpha,unsigned int incolor)const;//描画(中と辺は個別に色を指示、alphaは中の透明度)
	void Draw(Vector2D pos,unsigned int color,int alpha)const;//描画(中と辺は同じ色系統、alphaは中の透明度)
	void Draw(Vector2D pos,unsigned int color,int alpha,unsigned int incolor)const;//描画(中と辺は個別に色を指示、alphaは中の透明度)
	Vertexs GetPoints()const;//頂点６つの座標を求める
	Vertexs GetPoints(Vector2D pos)const;//posを中心とした時の頂点６つの座標を求める
	void Move(Vector2D pos){
		//posに中心点を移す
		m_center=pos;
	}

	//静的関数
	static Vertexs GetPoints(Vector2D center,Vector2D baseVec);
};


#endif // !DEF_HEXAGON_H
#pragma once
