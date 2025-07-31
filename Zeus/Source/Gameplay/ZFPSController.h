#pragma once

#include "Render/ZCamera.h"
#include "Windows/ZWindow.h"

class ZFPSController : public ZEntity
{
public:
	ZFPSController() = default;
	ZFPSController(ZWindow& window, ZCamera& camera);
	~ZFPSController() override;

	void Start() override;
	void FixedUpdate() override;
	void Update() override;

private:
	ZCamera* z_FPSCamera;
};

