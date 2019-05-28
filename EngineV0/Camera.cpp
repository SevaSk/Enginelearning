#include "Camera.h"

namespace dx = DirectX;

Camera::Camera():
	cam_rot(DirectX::XMMatrixRotationRollPitchYaw(0.0f,0.0f,0.0f)),
	cam_pos({ 0.0f, 0.0f, 20.0f,0.0f })
{}

dx::XMMATRIX Camera::GetMatrix() const noexcept
{
	return dx::XMMatrixTranslationFromVector(cam_pos)*cam_rot;
}

void Camera::Update(float dt, Keyboard& kbd, Mouse& mouse) noexcept
{
	if (kbd.KeyIsPressed('W')) 
	{
		cam_pos = dx::XMVectorAdd(cam_pos,
			dx::XMVectorScale(dx::XMVector3Transform(dx::XMVectorSet(0.0f,0.0f,-1.0f,0.0f), dx::XMMatrixInverse(nullptr,cam_rot)),dp) 
		);
	}

	if (kbd.KeyIsPressed('S'))
	{
		cam_pos = dx::XMVectorAdd(cam_pos,
			dx::XMVectorScale(dx::XMVector3Transform(dx::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), dx::XMMatrixInverse(nullptr, cam_rot)), dp)
		);
	}

	if (kbd.KeyIsPressed('A'))
	{
		cam_pos = dx::XMVectorAdd(cam_pos,
			dx::XMVectorScale(dx::XMVector3Transform(dx::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), dx::XMMatrixInverse(nullptr, cam_rot)), dp)
		);
	}

	if (kbd.KeyIsPressed('D'))
	{
		cam_pos = dx::XMVectorAdd(cam_pos,
			dx::XMVectorScale(dx::XMVector3Transform(dx::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f), dx::XMMatrixInverse(nullptr, cam_rot)), dp)
		);
	}

	if (kbd.KeyIsPressed(VK_SPACE))
	{
		cam_pos = dx::XMVectorAdd(cam_pos, dx::XMVECTOR{ 0.0f,1.0f,0.0f });
	}

	if (kbd.KeyIsPressed(VK_SHIFT))
	{
		cam_pos = dx::XMVectorAdd(cam_pos, dx::XMVECTOR{ 0.0f,-1.0f,0.0f });
	}



	if (kbd.KeyIsPressed('R'))
	{
		Reset();
	}


	cam_rot = cam_rot*
		dx::XMMatrixRotationY(float(-mouse.GetPosX() + mousex)*dt*dm)*
		dx::XMMatrixRotationX(float(-mouse.GetPosY() + mousey)*dt*dm);
	mousey = mouse.GetPosY();
	mousex = mouse.GetPosX();
}

void Camera::Reset() noexcept
{
	cam_rot = DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	cam_pos = { 0.0f, 0.0f, 20.0f,0.0f };
}
