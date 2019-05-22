#pragma once
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"

class Camera
{
public:
	Camera();
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void Update(float dt, Keyboard& kdb, Mouse& mouse) noexcept;
	void Reset() noexcept;
	

private:
	int mousex = 0;
	int mousey = 0;
	float dp = 0.3f;
	DirectX::XMMATRIX cam_rot;
	DirectX::XMVECTOR cam_pos;
};

