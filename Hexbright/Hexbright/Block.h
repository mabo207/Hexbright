#ifndef DEF_BLOCK_H
#define DEF_BLOCK_H

#include<memory>
#include<vector>
#include"Hexagon.h"

//ステージ上に置かれるオブジェクト
//0個以上3個以下の導線を持つ。導線の端点は正六角形の辺の中点にある。
class Block{
	//列挙体・型
public:
	//性質(継承先を示す)
	struct Feature{
		enum Kind{
			//種類を表す。また、ビット演算をすれば連鎖可能かの判定ができる
			normal=0x01,
			attack=0x02,
			heal=0x04,
			connect=0xff
		};
		Kind kind;
		Feature(Kind i_kind):kind(i_kind){}
		~Feature(){}
	};
	//導線
	struct Conductor{
	private:
		//導線の２端点の番号(0->1が0,...,4->5が4,5->0が5。%6すると扱いやすい)
		//常にn0<n1になるようにする
		int n0,n1;
	public:
		Conductor();//存在しない導線を作る
		Conductor(int i_n0,int i_n1);
		void turn(int n);//回転させる
		int GetN(int i)const;//n[N]の値を取る
		int GetOtherN(int n)const;//nでない方の別の端点番号を返す
		bool JudgeCross(const Conductor &otherobj)const;//交差判定(交差したらtrue)
		bool JudgeExist()const;//存在する導線か（falseなら非実在を示す）
	};

	//定数
protected:
	static const int lineThick;
	static const unsigned int lineColor;

public:
	static const Vector2D BaseVector;

	//変数
protected:
	std::shared_ptr<Hexagon> m_shape;//形状・モノクロ描画形式(位置大きさとどのくらい綺麗に表示するか)
	std::vector<Conductor> m_conductors;//導線群
	Feature m_feature;//性質(継承されたクラス)

	//関数
protected:
	virtual unsigned int GetColor()const;//ブロックの種類によって決定する色コードを取得するただしデフォルトではGetColor(160,160,160)の灰色との50%混合とする。
	virtual unsigned int GetVertexColor()const=0;//ブロックの種類によって決定する辺の色コードを取得する。

public:
	Block(std::shared_ptr<Hexagon> shape,const std::vector<Conductor> &conductors,Feature i_feature);
	Block(Vector2D center,const std::vector<Conductor> &conductors,Feature i_feature);
	~Block();

	//普通の関数
	void Draw()const;//ブロックを指定通りに描画
	void Draw(Vector2D pos)const;//ブロックの位置を指定して描画(溜めているブロックの描画等)
	void Draw(Vector2D pos,unsigned int vertexColor,unsigned int conductorColor)const;//辺と導線群を描画する(もしここに置いたらどうなるみたいなガイド)
	void Draw(Vector2D pos,unsigned int inColor,unsigned int vertexColor,unsigned int conductorColor,int alpha,int conductorThick)const;//描画処理の要素全てを引数に取れる
	Conductor GetConductor(int n)const;//入口の番号からそのブロックが持っている導線を返す
	Vector2D GetVertexPos(int n)const;//辺番号からその位置を返す
	Vector2D GetPos()const;//中心の絶対位置を返す
	void Turn(int n);//ブロックを回転させる。導線の回転とアニメーションの出力(こちらは未実装)
	bool JudgeConnect(const Block &otherobj)const;
	virtual int GetBaseScore(int gameMode)const=0;//ブロックの種類によって基本得点が決定する。なお、スコアアタックかVSモードかで基本得点を変えるかもしれないので引数を渡すようにしている。
	void Move(Vector2D pos){
		//posに中心を動かす
		m_shape.get()->Move(pos);
	}
	std::vector<Conductor> GetConductors()const{
		return m_conductors;
	}
	Feature GetFeature()const{
		return m_feature;
	}

	//静的関数
	static Vector2D GetVertexPos(int n,Vector2D center);//ブロックの中心位置さえ分かれば、HexagonのbaseVecはBaseVectorで固定なので求められる
};

#endif // !DEF_BLOCK_H
#pragma once
