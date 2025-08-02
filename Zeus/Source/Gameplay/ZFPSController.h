#pragma once

#include "Render/ZCamera.h"
#include "Windows/ZWindow.h"

class ZFPSController : public ZEntity
{
public:
	ZFPSController() = default;
	ZFPSController(ZCamera& camera);
	~ZFPSController() override;

	void Start() override;
	void FixedUpdate() override;
	void Update() override;

private:
	ZCamera* z_FPSCamera;
};

