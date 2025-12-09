#pragma once

#include "Animation/3D/ZAnimation.h"
#include "Animation/3D/ZAnimator.h"


class Demon : public ZEntity
{
public:
	Demon() = default;
	~Demon() override;

	void Start() override;
	void FixedUpdate() override;
	void Update() override;

private:

	Animation z_DemonSitting{};
	Animator z_Animator{};
};

