#pragma once

#include <memory>
#include "Shader/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "Effect.h"


//�v���C���[
class Player : public Character
{
public:
	//�X�e�[�g
	enum class AttackType
	{
		Hammer,
		Spear,
		Sword,

		None,
	};
	AttackType GetAttackType() const { return Atype; }

	//�X�e�[�g
	enum class State
	{
		Idle,
		IdleToRun,
		Run,
		RunToIdle,
		JumpStart,
		JumpLoop,
		JumpAir,
		JumpEnd,
		Damage,
		Dead,
		AttackHammer1,
		AttackHammer2,
		AttackHammerJump,
		AttackSpear1,
		AttackSpear2,
		AttackSpear3,
		AttackSpearJump,
		AttackSword1,
		AttackSword2,
		AttackSword3,
		AttackSwordJump,
		CliffGrab,

		None,
	};
	State GetState() const { return state; }

	//�A�j���[�V����
	enum Animation
	{
		Anim_None,
		Anim_CliffGrab,
		Anim_Damage,
		Anim_Death,
		Anim_AttackHammer1,
		Anim_AttackHammer2,
		Anim_AttackHammerJump,
		Anim_Idle,
		Anim_IdleToRun,
		Anim_JumpAir,
		Anim_JumpEnd,
		Anim_JumpLoop,
		Anim_JumpStart,
		Anim_Running,
		Anim_RunToIdle,
		Anim_AttackSpear1,
		Anim_AttackSpear2,
		Anim_AttackSpear3,
		Anim_AttackSpearJump,
		Anim_AttackSword1,
		Anim_AttackSword2,
		Anim_AttackSword3,
		Anim_AttackSwordJump,
	};

	struct Arms
	{
		const char* nodeName;
		XMFLOAT3	position;
		const XMVECTOR	rootOffset;
		const XMVECTOR	tipOffset ;
		float		radius;
		bool flag1;
		bool flag2;
		bool flag3;
		bool flagJump;
	};

public:
	Player();
	~Player() override;

	//�C���X�^���X�擾
	static Player& Instance();

	//�X�V
	void Update(float elapsedTime,int playCount);

	//�`��
	void ShadowRender(const RenderContext& rc, ShadowMap* shadowMap);
	//�`��
	void Render(const RenderContext& rc, ModelShader* shader);

	//�W�����v���͏���
	bool InputJumpButton();
	void UpdateJump(float elapsedTime);
	// �U������
	bool InputAttackFromNoneAttack();
	bool InputAttackFromJump(float elapsedTime);
	bool InputHammerButton();
	bool InputSwordButton();
	bool InputSpearButton();

	//�f�o�b�O�v���~�e�B�u�`��
	void DrawDebugPrimitive();


	Model* GetModel() const { return model.get(); }
	int GetFlashCount() const { return flashCount; }

	//���S�������ɌĂ΂��
	void OnDead();
protected:
	//���n�������ɌĂ΂��
	void OnLanding(float elapsedTime) override;
	//�_���[�W�󂯂����ɌĂ΂��
	void OnDamaged();

	//�������͍X�V �I�[�o�[���C�h
	void UpdateVerticalVelocity(float elapsedFrame);

private:
	// �X�e�B�b�N���͒l����ړ��x�N�g�����擾
	XMFLOAT3 GetMoveVec() const;
	// �ړ����͏���
	bool InputMove(float elapsedTime);

	// Update
	void UpdateArmPositions(Model* model, Arms& arm);

	// �v���C���[�ƃG�l�~�[�Ƃ̏Փˏ���
	void CollisionPlayerVsEnemies();
	// ����ƂƃG�l�~�[�̏Փˏ���
	void CollisionArmsVsEnemies(Arms arm);

	// ========�J��========
	// �ҋ@�X�e�[�g
	void TransitionIdleState();
	// �ړ��X�e�[�g
	void TransitionRunState();
	// �ҋ@�ړ��ؑփX�e�[�g
	void TransitionIdleToRunState();
	void TransitionRunToIdleState();
	// �W�����v�X�e�[�g
	void TransitionJumpStartState();
	void TransitionJumpLoopState();
	void TransitionJumpAirState();
	void TransitionJumpEndState();
	// �_���[�W�X�e�[�g
	void TransitionDamageState();
	// ���S�X�e�[�g
	void TransitionDeadState();

	// �U���X�e�[�g
	void TransitionAttackHummer1State();
	void TransitionAttackHummer2State();
	void TransitionAttackHummerJumpState(float elapsedTime);
	void TransitionAttackSpear1State();
	void TransitionAttackSpear2State();
	void TransitionAttackSpear3State();
	void TransitionAttackSpearJumpState();
	void TransitionAttackSword1State();
	void TransitionAttackSword2State();
	void TransitionAttackSword3State();
	void TransitionAttackSwordJumpState(float elapsedTime);
	void TransitionCliffGrabState();



	// �e�X�e�[�W���Ƃ̍X�V����
	void UpdateEachState(float elapsedTime);

private:

	std::unique_ptr<Model> model;
	State	state = State::Idle;
	AttackType	Atype = AttackType::None;
	
	//�W�����v�U�����Ɏg�p
	bool isMoveAttack = false;

	// SwordAttack
	static const int MAX_POLYGON = 32;
	XMFLOAT3 trailPositions[2][MAX_POLYGON];
	DirectX::XMFLOAT4 color = { 1, 1, 1, 1 };

	float moveSpeed = 5.0f;
	float turnSpeed = XMConvertToRadians(720);

	bool isDamaged = false;
	float stateTimer = 0.0f;
	float DamageFlash = 0.1f;
	int flashCount = 0;
	//float	friction = 0.5f;
	//float acceleration = 1.0f;

	float jumpSpeed = 17.5f;

	DirectX::XMFLOAT3 offset;

	enum JumpState
	{
		CanJump,
		CanDoubleJump,
		CannotJump
	};
	JumpState jumpTrg = CanJump;

	Arms Hammer
	{
		"Hammer",
		{0,0,0},
		{0,0,0},
		{0,35,0},
		0.4f,
		false,
		false,
		false,
		false,
	};

	Arms Spear
	{
		"Spear",
		{0,0,0},
		{0,0,0},
		{0,100,0},
		0.2f,
		false,
		false,
		false,
		false,

	};
	Arms Sword
	{
		"Sword",
		{0,0,0},
		{0,0,0},
		{0,45,0},
		0.25f,
		false,
		false,
		false,
		false,
	};

	std::unique_ptr<Effect> hitEffect;
};