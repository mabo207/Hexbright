#include"DxLib.h"
#include"PuzzleSystem.h"
#include"input.h"

#include"NormalBlock.h"

//-----------------------FlowCircle-----------------------
PuzzleSystem::FlowCircle::FlowCircle(PutPos i_blockPos,Vector2D i_drawPos)
	:blockPos(i_blockPos),drawPos(i_drawPos)
	,beginVertex(-1),endVertex(-1),flowflag(false)
	,startPos(0,0),startDir(-1),startBlock(0,0),flowend(false),speed(4.0),destination(0,0)
{
	//�Q�[���J�n���ɂ̂݌Ă΂��̂ł���ŗǂ�
}

PuzzleSystem::FlowCircle::~FlowCircle(){}

void PuzzleSystem::FlowCircle::Draw(Vector2D center)const{
	int mode,pal;
	GetDrawBlendMode(&mode,&pal);
	//�������ۂ͉��Z�u�����h��p���Č����ĕ\��������
	SetDrawBlendMode(DX_BLENDMODE_ADD,255);
	for(int i=-2;i<=2;i++){
		Vector2D v=drawPos+(destination-drawPos).norm()*speed*(float)i;
		DrawCircle((int)(v.x),(int)(v.y),2,GetColor(100,100,120),TRUE);
	}
	SetDrawBlendMode(mode,pal);
}

void PuzzleSystem::FlowCircle::Update(const Stage &stage,const PutPos &cursor,const Vector2D &center){
	if(flowflag){
		//�������肪�n�܂��Ă���ꍇ
		flowend=false;//���false�ɂ���B�X�V���ɓ��ʂȂ��Ƃ�����΂��̎��̂�true�ƂȂ�悤�ɂ���
		//���x����

		//�ʒu�ύX
		drawPos=drawPos+(destination-drawPos).norm()*speed;
		//�ړI�n���B�̔���
		//�ړI�n�ƌ��݈ʒu�̋�����speed�̔����ȉ��Ȃ瓞�B�Ƃ���
		if((destination-drawPos).size()<speed/2){
			//���݂���u���b�N��ύX
			switch(endVertex){
			case(0)://�E��̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::RIGHTUP);
				break;
			case(1)://�E�̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::RIGHT);
				break;
			case(2)://�E���̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::RIGHTDOWN);
				break;
			case(3)://�����̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::LEFTDOWN);
				break;
			case(4)://���̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::LEFT);
				break;
			case(5)://����̕ӂɐi��
				blockPos=blockPos+PutPos::BaseVec(PutPos::LEFTUP);
				break;
			}
			//���̖ړI�n��ݒ肷�邩�̔���
			std::shared_ptr<const Block> pb=stage.GetBlock(blockPos);
			flowflag=false;//��U����������I�����������Ƃɂ��A�p���\�Ȃ�true�ɖ߂�
			if((destination-startPos).size()>0){
				//���݂̖ړI�n���X�^�[�g�n�_�Ɉ�v���Ă��Ȃ��Ȃ�
				if(pb.get()!=nullptr){
					//���ɐi�ރu���b�N�����݂��Ă��āc�c
					beginVertex=(endVertex+Hexagon::Vertexs::vnum/2)%Hexagon::Vertexs::vnum;//���Ƃ����Z�p�`�̕ӂ��甼���i�߂�ƍ�����Z�p�`�̕ӂ�\���悤�ɂȂ�
					if(pb.get()->GetConductor(beginVertex).JudgeExist()){
						//�Ή�����ӂ����݂���Ȃ��
						flowflag=true;//��������p��
					}
				}
			}else{
				//��v���Ă��鎞�͓�������͕K���I��������
				flowflag=false;
			}
			//���̖ړI�n�̐ݒ�
			if(!flowflag){
				//��������̏I�����L�^
				flowend=true;
				//�ʒu�����ɖ߂�
				blockPos=cursor;
				//Boot�Őݒ肳���ϐ��͖߂��Ȃ�

			}else{
				endVertex=pb.get()->GetConductor(beginVertex).GetOtherN(beginVertex);
				if(startDir==endVertex && startBlock==blockPos){
					//��������J�n���̖ړI�ӂ��s����ł���΁A�s������J�n�ꏊ�ɁB
					destination=startPos;
				} else{
					//�����łȂ��Ȃ�A�s�����ӂɁB
					destination=pb.get()->GetVertexPos(endVertex);
				}
			}
		}
	}else{
		//�����������Ă��Ȃ��ꍇ
		blockPos=cursor;
		drawPos=cursor.relativecoordinates(Block::BaseVector)+center;
	}
}

bool PuzzleSystem::FlowCircle::FlowEnd()const{
	return flowend;
}

bool PuzzleSystem::FlowCircle::Boot(const Stage &stage,const PutPos &cursor){
	//���̏ꏊ�Ƀu���b�N������A�u���b�N�ɓ��������݂��邩���ׂ�
	std::shared_ptr<const Block> pb=stage.GetBlock(cursor);
	if(pb.get()!=nullptr && pb.get()->GetConductors().size()>0){
		//���Ώꏊ������(�e�L�g�[)
		Block::Conductor c=pb.get()->GetConductors()[0];
		beginVertex=c.GetN(0);
		endVertex=c.GetN(1);
		startDir=endVertex;
		drawPos=pb.get()->GetVertexPos(beginVertex);
		startPos=drawPos;
		destination=pb.get()->GetVertexPos(endVertex);
		startBlock=cursor;

		//���ΊJ�n
		flowflag=true;

		return true;
	}
	return false;
}

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
		m_flowCircle.Boot(m_stage,m_cursor);
	}
	
}

void PuzzleSystem::Draw()const{
	//�w�i�̕`��

	//�Ֆʂ̕`��
	m_stage.Draw(m_center);
	//�ۂ̕`��
	m_flowCircle.Draw(m_center);
	//���܂��Ă���u���b�N�Q�̕`��
	for(size_t i=0;i<m_savedBlock.size();i++){
		m_savedBlock[i].get()->Draw(Vector2D(750,(float)(100*i+150)));
	}

}
