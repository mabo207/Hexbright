#include"Block.h"
#include"DxLib.h"

//-------------------Conductor-------------------
Block::Conductor::Conductor():n0(-1),n1(-1){}

Block::Conductor::Conductor(int i_n0,int i_n1){
	if(i_n0==i_n1 || i_n0<0 || i_n0>=6 || i_n1<0 || i_n1>=6){
		//“_‚ªˆê’v‚µ‚Ä‚é‚©A“ü—Í”Ô†‚ª0ˆÈã5ˆÈ‰º‚Å‚È‚©‚Á‚½‚ç‘¶İ‚µ‚È‚¢“±ü‚É‚·‚é
		n0=-1,n1=-1;
	}else{
		//n0<n1‚Æ‚È‚é‚æ‚¤‚É‘ã“ü
		n0=min(i_n0,i_n1);
		n1=i_n0+i_n1-n0;
	}
}

void Block::Conductor::turn(int n){
	//”Ô†‚ğ‚Ç‚¿‚ç‚àn‚¸‚ç‚·
	this->n0+=n;
	this->n1+=n;
}

bool Block::Conductor::JudgeCross(const Conductor &otherobj)const{
	//ˆê’v‚µ‚Ä‚¢‚é“_”Ô†‚ª‚ ‚Á‚½‚çŒğ·‚Æ‚İ‚È‚·
	if(this->n0==otherobj.n0 || this->n1==otherobj.n0 || this->n0==otherobj.n1 || this->n1==otherobj.n1){
		return true;
	}
	//ˆê’v‚µ‚Ä‚¢‚é“_”Ô†‚Í‚È‚¢‚Ì‚Åthis‚©‚çŒ©‚Ä“¯‚¶‘¤‚É‚ ‚éotherobj‚Ì“_‚Ì”‚ğ’²‚×‚Ä‹ô”‚È‚çŒğ·‚µ‚È‚¢
	return ((n0-otherobj.n0)*(n1-otherobj.n0)*(n0-otherobj.n1)*(n1-otherobj.n1)<0);
}

int Block::Conductor::GetN(int i)const{
	switch(i){
	case(0):
		return n0;
	case(1):
		return n1;
	}
	return -1;
}

int Block::Conductor::GetOtherN(int n)const{
	if(n==n0 || n==n1){
		return n0+n1-n;
	}
	return -1;
}

bool Block::Conductor::JudgeExist()const{
	return (n0<0 || n0>=6 || n1<0 || n1>=6);
}

//-------------------Block-------------------
const int Block::lineThick=3;
const unsigned int Block::lineColor=DxLib::GetColor(127,127,127);
const Vector2D Block::BaseVector=Vector2D(0,-40);

Block::Block(std::shared_ptr<Hexagon> shape,const std::vector<Conductor> &conductors)
	:m_shape(shape),m_conductors(conductors){}

Block::Block(Vector2D center,const std::vector<Conductor> &conductors)
	:m_shape(std::shared_ptr<Hexagon>(new Hexagon(center,BaseVector))),m_conductors(conductors){}

Block::~Block(){}

void Block::Draw()const{
	//³˜ZŠpŒ`‚Ì•`‰æ
	m_shape.get()->Draw(GetColor(),TRUE);
	//“±ü‚Ì•`‰æ
	Hexagon::Vertexs vs=m_shape.get()->GetPoints();
	for(Conductor c:m_conductors){
		Vector2D v0=(vs.GetPoint(c.GetN(0))+vs.GetPoint((c.GetN(0)+1)%Hexagon::Vertexs::vnum))/2
			,v1=(vs.GetPoint(c.GetN(1))+vs.GetPoint((c.GetN(1)+1)%Hexagon::Vertexs::vnum))/2;
		DrawLine((int)(v0.x),(int)(v0.y),(int)(v1.x),(int)(v1.y),lineColor,lineThick);
	}
}

Block::Conductor Block::GetConductor(int n)const{
	for(Conductor c:m_conductors){
		if(n==c.GetN(0) || n==c.GetN(1)){
			return c;
		}
	}
	return Conductor();
}

void Block::Turn(int n){
	//‘¶İ‚·‚é“±ü‚ğ‰ñ“]‚³‚¹‚é
	for(Conductor c:m_conductors){
		c.turn(n);
	}
}


