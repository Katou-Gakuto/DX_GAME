#pragma once
#include "DrawData.h"
#include "ResourceData.h"

class CharacterBase;

enum class STATE_ENEMY_TYPE
{
    NONE = -1,
    MAP_ENEMY = 0,
    BATTLE_ENEMY,

    MAX
};

class EnemyCommonProcessing
{
private:
    //enum ENEMY_DATA_DRAW_TYPE
    //{
    //    FRAME = 0,
    //    BASE,
    //    ENEMY_DATA_MAX
    //};
    
	enum ENEMY_DRAW_TYPE
	{
        //RAME,

		HP_FRAME,
		HP_RIGHT,
		HP_LEFT,

		ENEMY_DRAW_MAX
	};

    // �G�l�~�[�X�e�[�g���
    STATE_ENEMY_TYPE meEnemyType;

    // TODO: �`��}�l�[�W���[��肻���ɏ��n���n���h����ݒ肷��@����̎Q�Ƃ�؂邱�Ƃō폜�������Ƃɂ���s
    // �`��p�X�N���[���n���h��
    int mnScreenHandle;

    const DisplaySize SCREEN_SIZES[(int)STATE_ENEMY_TYPE::MAX] = //{ {Vector2(70.0f, 40.0f), 0 }, {Vector2(70.0f, 80.0f), 0,}};
                                                                 { {Vector2(70.0f, 40.0f), 0 }, {Vector2(110.0f, 30.0f), 0,}};

	const Vector2_Int HP_FRAME_SIZE = Vector2_Int(5, 3);
	Vector2_Int mstHpLeftUp = Vector2_Int(0 + HP_FRAME_SIZE.x, 0 + HP_FRAME_SIZE.y);
	Vector2_Int mstHpRightDown = Vector2_Int(100 + HP_FRAME_SIZE.x, 20 + HP_FRAME_SIZE.y);

	const Vector2_Int HP_GRAPH_SIZE = Vector2_Int(2151, 83);

protected:
    EnemyCommonProcessing(STATE_ENEMY_TYPE enemyType);
    ~EnemyCommonProcessing();

    /*�폜����*/
    void EnemyCommonProcessingData_Delete();

    /*�G�l�~�[���`��*/
    void EnemyDataDraw(CharacterBase *enemy);

    /*�G�l�~�[�摜�f�[�^������*/
    void EnemyGraphDataInitialize(CharacterBase *enemy);

    /*HP�`����ݒ�*/
    void HpDrawInfoSetup(CharacterBase *enemy);
};
