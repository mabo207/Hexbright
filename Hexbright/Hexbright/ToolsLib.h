#ifndef DEF_TOOLSLIB_H
#define DEF_TOOLSLIB_H

//インクルード
#include<string>
#include<math.h>

//一般的に用いることができる便利関数・構造体をここに書く
//位置についての構造体
class Vector2D{
public:
	//変数
	float x, y;
	//関数
	Vector2D(): x(0),y(0){}//既定のコンストラクタ
	Vector2D(float i_x, float i_y) : x(i_x), y(i_y) {}
	const Vector2D operator+(const Vector2D &otherobj)const {
		return Vector2D(x+otherobj.x,y+otherobj.y);
	}
	const Vector2D operator-(const Vector2D &otherobj)const {
		return Vector2D(x - otherobj.x, y - otherobj.y);
	}
	//定数倍
	const Vector2D operator*(float aMag)const{
		return Vector2D(x *aMag, y*aMag);
	}
	const Vector2D operator/(float aMag)const {
		return Vector2D(x /aMag, y/aMag);
	}
	float dot(const Vector2D &otherobj)const {
		return x*otherobj.x + y*otherobj.y;
	}
	//this cross otherobjを返します。
	float cross(const Vector2D &otherobj)const {
		return x*otherobj.y - otherobj.x*y;
	}
	float size()const {
		return sqrtf(x*x + y*y);
	}
	//サイズの二乗を返す
	float sqSize()const {
		return x*x + y*y;
	}
	Vector2D norm()const {
		float siz = size();
		if(siz!=0.0){
			return Vector2D(x / siz,y / siz);
		}
		return Vector2D(0.0,0.0);
	}
	//時計回りに回転させた時のベクトルを返す(角度の単位はラジアン)
	Vector2D turn(double radian)const;
};

//マウスの位置をVector2D型で返す関数
Vector2D GetMousePointVector2D();



//描画関連
//画面全体を描画範囲にする
int SetDrawAllArea();

//文字列描画。\nで改行させる。また右端まで行ったら改行する。
//最後が\0で終わらない文字列だとフリーズまたはオーバーフローが起こる
int DrawStringNewLineToHandle(const int strX,const int strY,const int printableX,const int printableY,const int maxDX,const int maxDY,const int Color,const int Font,const int FontSize,const char *str);

int DrawStringNewLineToHandle(const int strX,const int strY,const int printableX,const int printableY,const int maxDX,const int maxDY,const int Color,const int Font,const int FontSize,const std::string &str);

//上の文字列描画の方式で、描画はせずに必要なY座標の幅のみ求める
int GetStringHeightNewLineToHandle(const int maxDX,const int font,const char *str);

int GetStringHeightNewLineToHandle(const int maxDX,const int font,const std::string str);

//拡大描画。位置指定ではなく大きさ指定で拡大率を指定。
int DrawExtendGraphSizeAssign(int x,int y,int dx,int dy,int GrHandle,int TransFlag);

//中央の描画位置を指定した文字列描画
int DrawStringCenterBaseToHandle(const int centerx,const int centery,const char *str,unsigned int color,int fonthandle,bool yposcenterbaseflag,unsigned int EdgeColor=0U,int VerticalFlag=0);

//位置を色々な式で管理するクラス
class PositionControl{
	//列挙体
public:
	enum TYPE{
		TYPE_IN,
		TYPE_OUT,
		TYPE_INOUT
	};
	enum FUNCTION{
		FUNCTION_LINER,
		FUNCTION_EXPO
	};
	//変数
protected:
	int flame,maxflame;//フレーム数の管理
	int x,startx,endx;//x座標の管理
	int y,starty,endy;//y座標の管理
	TYPE type;//位置変更の形状
	FUNCTION function;//位置変更関数
	double degree;//変化度合い
				  //関数
public:
	PositionControl(int i_x=0,int i_y=0,int i_maxflame=0,TYPE i_type=TYPE_IN,FUNCTION i_function=FUNCTION_LINER,double i_degree=0.0)
		:flame(0),maxflame(i_maxflame),x(i_x),startx(i_x),endx(i_x)
		,y(i_y),starty(i_y),endy(i_y),type(i_type),function(i_function),degree(i_degree){}//位置の初期化（最初のみ）
	virtual ~PositionControl(){}//デストラクタ
	virtual void Update();//位置更新
	void SetTarget(int i_endx,int i_endy,bool initflame);//目標位置を決める
	void EnforceEnd();//強制的に動作後にする
	void Retry();//動作をリセットしてやり直す
	void Retry(int i_startx,int i_starty);//動作をリセットしてやり直す。スタート位置も変える
	int GetX()const{
		return x;
	}
	int GetY()const{
		return y;
	}
	int GetstartX()const{
		return startx;
	}
	int GetstartY()const{
		return starty;
	}
	int GetendX()const{
		return endx;
	}
	int GetendY()const{
		return endy;
	}
	int GetFlame()const{
		return flame;
	}
	virtual int GetMaxFlame()const{
		return maxflame;
	}
	FUNCTION GetFunction()const{
		return function;
	}
	TYPE GetType()const{
		return type;
	}
	double GetDegree()const{
		return degree;
	}
	void SetMaxFlame(int flame,bool targetinitflag);
	virtual bool GetEndFlag()const;//動作が終了しているかを判定する
};

//速度制御によって速さを指定して真っ直ぐ進む
class PositionControlSpeeding:public PositionControl{
	//列挙体
public:
	//変数
protected:
	//max_flameは更新処理に用いられなくなる

	//関数
public:
	PositionControlSpeeding(int i_x=0,int i_y=0,int i_maxflame=0,TYPE i_type=TYPE_IN,FUNCTION i_function=FUNCTION_LINER,double i_degree=1.0);
	~PositionControlSpeeding(){}//デストラクタ
	void Update();//位置更新
	int GetMaxFlame()const;
	bool GetEndFlag()const;
};

//大きさ調整しつつ並べて表示する位置を計算するクラス
class LiningupScalingMechanism{
	//型・列挙体
public:
	enum DIRECTION{
		UP,
		LEFT,
		RIGHT,
		UNDER
	};
	//定数

	//変数
protected:
	DIRECTION fixedside;//どの辺を合わせるか
	int startx,starty;//開始位置
	PositionControl size;//拡大している物の調整

						 //関数
public:
	LiningupScalingMechanism(int x,int y,DIRECTION side,PositionControl initsize);
	~LiningupScalingMechanism();
	void SetScaling(int startdx,int startdy,int enddx,int enddy);//大きさを決定する
	void Update();
	void Retry();
	void EnforceEnd();
	int GetX(int n,int expandingn,int reducingn)const;
	int GetY(int n,int expandingn,int reducingn)const;
	int GetNormalSizeX()const;
	int GetNormalSizeY()const;
	int GetExpandingSizeX()const;
	int GetExpandingSizeY()const;
	int GetReducingSizeX()const;
	int GetReducingSizeY()const;
};



#endif // !DEF_TOOLSLIB_H
#pragma once
