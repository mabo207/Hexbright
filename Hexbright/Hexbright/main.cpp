#include"DxLib.h"
#include"GraphicControl.h"
#include"input.h"
#include"ToolsLib.h"

#include"Title.h"
#include<memory>
#include"PuzzleSystem.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	//dx���C�u�����̏�����
	//��ʃ��[�h�̐ݒ�(�ꉞ����Ȋ���)
	SetGraphMode((int)PuzzleSystem::aPuzzleSize.x,(int)PuzzleSystem::aPuzzleSize.y,16);
	//�^�C�g�����j���[����
	SetMainWindowText("Hexbright");
	//�E�C���h�E�T�C�Y�̕ύX
	SetWindowSizeExtendRate(1.0);
	//�E�C���h�E�T�C�Y�̕ύX���ł���悤�ɂ���
	SetWindowSizeChangeEnableFlag(TRUE);
	//�A�C�R���̐ݒ�
	SetWindowIconID(101);

	if(ChangeWindowMode(TRUE) != 0) {
		return 0;
	}
	if(DxLib_Init() != 0) {
		return 0;
	}
	if(SetDrawScreen(DX_SCREEN_BACK) != 0) {
		DxLib_End();
		return 0;
	}

	//���͋@�\�̏�����
	InitInputControler();

	
	std::shared_ptr<Title> title(new Title());
	SRand(123456);
	
	//�A�v���P�[�V��������
	while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//�Q�[���{��
		//�L�[���X�V
		input_update();
		//�`��
		title->Draw();
		//�v�Z����
		int index=title->Calculate();
		//�I�����o
		if(index<0 || keyboard_get(KEY_INPUT_ESCAPE)>0){
			break;
		}
	}

	//�I������
	DeleteInputControler();//���͋@�\�̉��

	DxLib_End();

	return 0;
}
