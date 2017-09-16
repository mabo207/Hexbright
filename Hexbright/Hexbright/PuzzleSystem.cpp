#include"DxLib.h"
#include"PuzzleSystem.h"
#include"input.h"
#include<set>

#include"NormalBlock.h"
#include"AttackBlock.h"
#include"HealBlock.h"
#include"ConnectBlock.h"

//-----------------------PuzzleSystem-----------------------
const Vector2D PuzzleSystem::aPuzzleSize=Vector2D(1280,720);

PuzzleSystem::PuzzleSystem()
	:m_stage(5),m_cursor(0,0),m_bootVertex(0)
	,m_center(aPuzzleSize/2),m_flowCircle(PutPos(0,0),m_center)
	,m_score(),m_flame(0)
	,m_timeFont(CreateFontToHandle("Eras Bold ITC",32,4,-1))
{
	//������
	for(int i=0;i<5;i++){
		AddSavedBlock();
	}
}

PuzzleSystem::~PuzzleSystem(){
	DeleteFontToHandle(m_timeFont);
}

void PuzzleSystem::AddSavedBlock(){
	//0�`5�������_���ɕ��ׂ�
	//�t�B�b�V���[�C�G�[�c�̃A���S���Y����p����
	int index[Hexagon::Vertexs::vnum];
	for(int i=0;i<Hexagon::Vertexs::vnum;i++){
		index[i]=i;
	}
	for(int i=0;i<Hexagon::Vertexs::vnum;i++){
		int a=GetRand(Hexagon::Vertexs::vnum-i-1);
		int b=index[Hexagon::Vertexs::vnum-i-1];
		index[Hexagon::Vertexs::vnum-i-1]=index[a];
		index[a]=b;
	}
	//�Z�p�`�ɐ������ǉ��ł��邩�𔻒肵�Ȃ��猩�Ă����A�_���ɂȂ����炻�̑O�̕���Ԃ��B
	std::vector<Block::Conductor> cons;
	for(unsigned int i=0;i<Hexagon::Vertexs::vnum/2;i++){
		bool flag=true;
		Block::Conductor con(index[i*2],index[i*2+1]);
		for(Block::Conductor c:cons){
			if(con.JudgeCross(c)){
				flag=false;
				break;
			}
		}
		if(flag){
			cons.push_back(con);
		}else{
			break;
		}
	}
	//�}�`���i�[�B��������ނ̓����_���B
	//�z���m��:red-30%,blue-30%,green-30%,yellow-10%
	int rand=GetRand(100);
	if(rand<30){
		m_savedBlock.push_back(std::shared_ptr<Block>(new NormalBlock(m_center+m_cursor.relativecoordinates(Block::BaseVector),cons)));
	}else if(rand<60){
		m_savedBlock.push_back(std::shared_ptr<Block>(new AttackBlock(m_center+m_cursor.relativecoordinates(Block::BaseVector),cons)));
	}else if(rand<90){
		m_savedBlock.push_back(std::shared_ptr<Block>(new HealBlock(m_center+m_cursor.relativecoordinates(Block::BaseVector),cons)));
	}else{
		m_savedBlock.push_back(std::shared_ptr<Block>(new ConnectBlock(m_center+m_cursor.relativecoordinates(Block::BaseVector),cons)));
	}
	

}

void PuzzleSystem::TurnBootVertex(int n){
	//���̃J�[�\���ʒu�Ƀu���b�N�����邩�𔻒�
	std::shared_ptr<const Block> pb=m_stage.GetBlock(m_cursor);
	if(pb.get()!=nullptr && !pb->GetConductors().empty()){
		//�u���b�N������A�u���b�N���ɓ��������݂���ꍇ
		//�������ʂ��Ă���u���b�N�̕Ӕԍ����i�[����
		std::vector<Block::Conductor> cVec=pb->GetConductors();
		std::set<int> set;
		for(Block::Conductor c:cVec){
			set.insert(c.GetN(0));
			set.insert(c.GetN(1));
		}
		//m_bootVertex�Ɏ��v�������ň�ԋ߂��ʒu�����߂�
		std::set<int>::const_iterator it=set.lower_bound(m_bootVertex);
		//��]������
		if(it!=set.end() && *it==m_bootVertex){
			//m_bootVertex�̈ʒu�ɔ��Γ_�����݂��Ă����ꍇ(n�񂾂���]������)

		}else{
			//m_bootVertex�̈ʒu�ɔ��Γ_�����݂��Ă��Ȃ��ꍇ(�����v���Ȃ�n��,���v���Ȃ�n-1�񂾂���]������)
			if(n==0){
				//n=1�̎��Ɠ���������������
				n=1;
			}
			if(n>0){
				//n>0�̎��́Ait�ɒl�������Ă����֌W�A�܂�n-1�񂾂���]������֌W��A��U�ЂƂO�ɃC�e���[�^��߂��Bit!=set.end()���ۏ؂����B
				if(it==set.begin()){
					it=set.end();
				}
				it--;
			}
		}
		if(n<0){
			for(int i=0;i>n;i--){
				if(it==set.begin()){
					it=set.end();
				}
				it--;
			}
		}else if(n>0){
			for(int i=0;i<n;i++){
				it++;
				if(it==set.end()){
					it=set.begin();
				}
			}
		}
		//�ړ���̕Ӕԍ����i�[
		m_bootVertex=*it;
	}else{
		//�u���b�N���Ȃ��ꍇ
		m_bootVertex=(m_bootVertex+Hexagon::Vertexs::vnum+n)%Hexagon::Vertexs::vnum;
	}
}

void PuzzleSystem::Update(){
	//���Ԃ̍X�V
	m_flame++;
	//�ۂ̍X�V
	m_flowCircle.Update(m_stage,m_cursor,m_center,m_score);
	m_score.Update();
	if(m_flowCircle.FlowEnd()){
		//���傤�Ǔ������肪�I��������
		//���_���Z����
		//m_score.AddBlockScore(m_flowCircle.blockPosVec,m_stage);
		//��������I�����̓_�����Z�B���������s���B
		m_score.AddFlowEndScore(m_flowCircle.CirclingFlag(),m_flowCircle.drawPos);
		//�W�Q���M����

		//�u���b�N��������
		m_stage.EraseBlocks(m_flowCircle.blockPosVec);
	}
	//�J�[�\���̍X�V
	PutPos cursorpal=m_cursor;//�ꎞ�I�Ɉړ�����i�[����B
	if(keyboard_get(KEY_INPUT_D)%15==1){
		cursorpal=cursorpal+PutPos::BaseVec(PutPos::RIGHT);
	}else if(keyboard_get(KEY_INPUT_X)%15==1){
		cursorpal=cursorpal+PutPos::BaseVec(PutPos::RIGHTDOWN);
	}else if(keyboard_get(KEY_INPUT_Z)%15==1){
		cursorpal=cursorpal+PutPos::BaseVec(PutPos::LEFTDOWN);
	}else if(keyboard_get(KEY_INPUT_A)%15==1){
		cursorpal=cursorpal+PutPos::BaseVec(PutPos::LEFT);
	}else if(keyboard_get(KEY_INPUT_W)%15==1){
		cursorpal=cursorpal+PutPos::BaseVec(PutPos::LEFTUP);
	}else if(keyboard_get(KEY_INPUT_E)%15==1){
		cursorpal=cursorpal+PutPos::BaseVec(PutPos::RIGHTUP);
	}
	if(m_stage.JudgeInStage(cursorpal)){
		m_cursor=cursorpal;
		//���Γ_�̍X�V
		TurnBootVertex(0);
	}
	//�u���b�N��]���͎�t(���Γ_����])
	if(keyboard_get(KEY_INPUT_R)==1){
		//���v����]
		m_savedBlock[0].get()->Turn(1);
		//���Γ_�����v���ɉ�]
		TurnBootVertex(1);
	}else if(keyboard_get(KEY_INPUT_Q)==1){
		//�����v����]
		m_savedBlock[0].get()->Turn(Hexagon::Vertexs::vnum-1);//-1�������%�̎d�l��0->5�ƂȂ炸0->3�ƂȂ�B
		//���Γ_�������v���ɉ�]
		TurnBootVertex(-1);
	}
	//�}�b�v�ύX���͎�t
	if(keyboard_get(KEY_INPUT_NUMPADENTER)==1){
		//�u���b�N��u��
		if(m_stage.PutBlock(m_cursor,m_savedBlock[0],m_center)){
			//�擪�̃u���b�N��u�����ꍇ��
			//�擪�̃u���b�N����菜��
			m_savedBlock.erase(m_savedBlock.begin());
			//�u���b�N���P�ǉ�����
			AddSavedBlock();
			//���Γ_�̍X�V
			TurnBootVertex(0);
		}
	}else if(keyboard_get(KEY_INPUT_BACK)==1){
		//�N��
		m_flowCircle.Boot(m_stage,m_cursor,m_bootVertex,m_score);
	}
	//���Γ_�ύX���͎�t
	if(keyboard_get(KEY_INPUT_1)%10==1){
		//�����v����]
		TurnBootVertex(-1);
	}else if(keyboard_get(KEY_INPUT_4)%10==1){
		//���v����]
		TurnBootVertex(1);
	}
}

void PuzzleSystem::Draw()const{
	//�w�i�̕`��

	//�Ֆʂ̕`��
	m_stage.Draw(m_center);
	//�J�[�\���̕`��(�擪�̃u���b�N�𔒂��ӁE�����ŕ\���B���̕����͓_�ŕ\���B)
	Vector2D v=m_center+m_cursor.relativecoordinates(Block::BaseVector);//�J�[�\���`��Ɣ��Γ_�`��ŗp����
	m_savedBlock[0].get()->Draw(v,GetColor(255,255,255),GetColor(255,255,255),(-(m_flame%60-30)*(m_flame%60-30)+900)*255/900);
	//���Γ_�̕`��
	v=Block::GetVertexPos(m_bootVertex,v);
	DrawCircle((int)v.x,(int)v.y,3,GetColor(128,128,255),TRUE);
	//�ۂ̕`��
	m_flowCircle.Draw(m_center);
	//���܂��Ă���u���b�N�Q�̕`��
	for(size_t i=0;i<m_savedBlock.size();i++){
		m_savedBlock[i].get()->Draw(Vector2D(aPuzzleSize.x-80,(float)(aPuzzleSize.y*(i/7.0+1/5.0))));
	}
	//���_�̕`��
	m_score.Draw(m_center);
	
}

int PuzzleSystem::GetScore()const{
	return m_score.GetScore();
}
