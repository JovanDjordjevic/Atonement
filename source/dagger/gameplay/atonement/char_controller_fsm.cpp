#include "char_controller_fsm.h"
#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include <gameplay/atonement/atonement_controller.h>

#include <iostream>

using namespace dagger;
using namespace atonement;

// Idle

void CharControllerFSM::Idle::Enter(CharControllerFSM::StateComponent& state_)
{
	std::cout << "[IDLE]" << std::endl;
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	AnimatorPlay(animator, "BlueWizard:IDLE");
}

DEFAULT_EXIT(CharControllerFSM, Idle);

void CharControllerFSM::Idle::Run(CharControllerFSM::StateComponent& state_)
{
	auto& input = Engine::Registry().get<InputReceiver>(state_.entity);

	if (EPSILON_NOT_ZERO(input.Get("walk")))
	{
		GoTo(ECharStates::Walking, state_);
	}

	if (EPSILON_NOT_ZERO(input.Get("jump")))
	{
		GoTo(ECharStates::JumpWindup, state_);
	}

	if (EPSILON_NOT_ZERO(input.Get("dash")))
	{
		GoTo(ECharStates::Dashing, state_);
	}

	// TODO transition to JumpWinddown if not grounded
}


// Walking

void CharControllerFSM::Walking::Enter(CharControllerFSM::StateComponent& state_)
{
	std::cout << "[WALK]" << std::endl;
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	AnimatorPlay(animator, "BlueWizard:WALK");
}

// same as: DEFAULT_EXIT(CharacterControllerFSM, Walking);
void CharControllerFSM::Walking::Exit(CharControllerFSM::StateComponent& state_)
{}

void CharControllerFSM::Walking::Run(CharControllerFSM::StateComponent& state_)
{
	auto&& [sprite, input, character] = Engine::Registry().get<Sprite, InputReceiver, AtonementController::AtonementCharacter>(state_.entity);

	Float32 walk = input.Get("walk");

	if (EPSILON_ZERO(walk))
	{
		GoTo(ECharStates::Idle, state_);
	}
	else
	{
		if((sprite.scale.x < 0 && walk > 0) || (sprite.scale.x > 0 && walk < 0)){
			sprite.scale.x *= -1;
		}
		sprite.position.x += character.speed * sprite.scale.x * Engine::DeltaTime();
	}

	if (EPSILON_NOT_ZERO(input.Get("jump")))
	{
		GoTo(ECharStates::JumpWindup, state_);
	}

	if (EPSILON_NOT_ZERO(input.Get("dash")))
	{
		GoTo(ECharStates::Dashing, state_);
	}

	// TODO transition to JumpWinddown if not grounded
}

// Jump Windup

void CharControllerFSM::JumpWindup::Enter(CharControllerFSM::StateComponent& state_)
{
	std::cout << "[JUMP_WU]" << std::endl;
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	AnimatorPlayOnce(animator, "BlueWizard:JUMP_WINDUP");
}

DEFAULT_EXIT(CharControllerFSM, JumpWindup);

void CharControllerFSM::JumpWindup::Run(CharControllerFSM::StateComponent& state_)
{
	auto&& [sprite, input, character] = Engine::Registry().get<Sprite, InputReceiver, AtonementController::AtonementCharacter>(state_.entity);

	if (EPSILON_NOT_ZERO(input.Get("dash")))
	{
		GoTo(ECharStates::Dashing, state_);
	}

	Float32 walk = input.Get("walk");

	if (!(EPSILON_ZERO(walk))) {
		if ((sprite.scale.x < 0 && walk > 0) || (sprite.scale.x > 0 && walk < 0)) {
			sprite.scale.x *= -1;
		}
		sprite.position.x += character.speed * sprite.scale.x * Engine::DeltaTime();
	}

	if (character.jumped < character.jumpHeight) {
		Float32 tmp = character.jumpSpeed * sprite.scale.y * Engine::DeltaTime();
		sprite.position.y += tmp;
		character.jumped += tmp;
	}
	else {
		character.jumped = 0;
		GoTo(ECharStates::JumpWinddown, state_);
	}

	// TODO in case of collision transition to winddown
}

// Jump Winddown

void CharControllerFSM::JumpWinddown::Enter(CharControllerFSM::StateComponent& state_)
{
	std::cout << "[JUMP_WD]" << std::endl;
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	AnimatorPlay(animator, "BlueWizard:JUMP_WINDDOWN");
}

DEFAULT_EXIT(CharControllerFSM, JumpWinddown);

void CharControllerFSM::JumpWinddown::Run(CharControllerFSM::StateComponent& state_)
{
	auto&& [sprite, input, character] = Engine::Registry().get<Sprite, InputReceiver, AtonementController::AtonementCharacter>(state_.entity);

	if (EPSILON_NOT_ZERO(input.Get("dash")))
	{
		GoTo(ECharStates::Dashing, state_);
	}

	Float32 walk = input.Get("walk");

	if (!(EPSILON_ZERO(walk))) {
		if ((sprite.scale.x < 0 && walk > 0) || (sprite.scale.x > 0 && walk < 0)) {
			sprite.scale.x *= -1;
		}
		sprite.position.x += character.speed * sprite.scale.x * Engine::DeltaTime();
	}

	// TODO while not grounded fall down


	// TODO refactor
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	if (animator.currentFrame == 3) {
		GoTo(ECharStates::Idle, state_);
	}
}

// Dashing

void CharControllerFSM::Dashing::Enter(CharControllerFSM::StateComponent& state_)
{
	std::cout << "[DASH]" << std::endl;
	auto& animator = Engine::Registry().get<Animator>(state_.entity);
	AnimatorPlayOnce(animator, "BlueWizard:DASH");
}

DEFAULT_EXIT(CharControllerFSM, Dashing);

void CharControllerFSM::Dashing::Run(CharControllerFSM::StateComponent& state_)
{
	// TODO transition back to idle after animation finishes
	// TODO transition to JumpWinddown if not grounded
}