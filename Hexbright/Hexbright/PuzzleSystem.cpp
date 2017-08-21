#include"DxLib.h"
#include"PuzzleSystem.h"
#include"input.h"

#include"NormalBlock.h"

//-----------------------PuzzleSystem-----------------------
PuzzleSystem::PuzzleSystem()
	:m_stage(5),m_cursor(0,0),m_center(400,300),m_flowCircle(PutPos(0,0),Vector2D(400,300))
{
	//������
	for(int i=0;i<5;i++){
		AddSavedBlock();
	}
}

PuzzleSystem::~PuzzleSystem(){}

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
	m_savedBlock.push_back(std::shared_ptr<Block>(new NormalBlock(m_center+m_cursor.relativecoordinates(Block::BaseVector),cons)));

}

void PuzzleSystem::Update(){
	//�J�[�\���̍X�V
	if(keyboard_get(KEY_INPUT_D)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::RIGHT);
	}else if(keyboard_get(KEY_INPUT_X)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::RIGHTDOWN);
	}else if(keyboard_get(KEY_INPUT_Z)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::LEFTDOWN);
	}else if(keyboard_get(KEY_INPUT_A)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::LEFT);
	}else if(keyboard_get(KEY_INPUT_W)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::LEFTUP);
	}else if(keyboard_get(KEY_INPUT_E)==1){
		m_cursor=m_cursor+PutPos::BaseVec(PutPos::RIGHTUP);
	}
	//�ۂ̍X�V
	m_flowCircle.Update(m_stage,m_cursor,m_center);
	//���͎�t
	if(keyboard_get(KEY_INPUT_NUMPADENTER)==1){
		//�u���b�N��u��
		if(m_stage.PutBlock(m_cursor,m_savedBlock[0],m_center)){
			//�擪�̃u���b�N��u�����ꍇ��
			//�擪�̃u���b�N����菜��
			m_savedBlock.erase(m_savedBlock.begin());
			//�u���b�N���P�ǉ�����
			AddSavedBlock();
		}
	}else if(keyboard_get(KEY_INPUT_BACK)==1){
		//�N��
		m_flowCircle.Boot(m_stage,m_cursor);
	}else if(keyboard_get(KEY_INPUT_R)==1){
		//���v����]
		m_savedBlock[0].get()->Turn(1);
	}else if(keyboard_get(KEY_INPUT_Q)==1){
		//�����v����]
		m_savedBlock[0].get()->Turn(5);//-1�������%�̎d�l��0->5�ƂȂ炸0->3�ƂȂ�B
	}
	
}

void PuzzleSystem::Draw()const{
	//�w�i�̕`��

	//�Ֆʂ̕`��
	m_stage.Draw(m_center);
	//�J�[�\���̕`��(�擪�̃u���b�N�𔒂��\��)
	m_savedBlock[0].get()->Draw(m_center+m_cursor.relativecoordinates(Block::BaseVector),GetColor(255,255,255),GetColor(255,255,255));
	//�ۂ̕`��
	m_flowCircle.Draw(m_center);
	//���܂��Ă���u���b�N�Q�̕`��
	for(size_t i=0;i<m_savedBlock.size();i++){
		m_savedBlock[i].get()->Draw(Vector2D(750,(float)(100*i+150)));
	}

}
