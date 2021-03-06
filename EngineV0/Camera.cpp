#include "Camera.h"

namespace dx = DirectX;

Camera::Camera(Mouse& mouse):
	cam_rot(DirectX::XMMatrixRotationRollPitchYaw(0.0f,0.0f,0.0f)),
	cam_pos({ 0.0f, 0.0f, 20.0f,0.0f }),
	mousex(mouse.GetPosX()),
	mousey(mouse.GetPosY())
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
		cam_pos = dx::XMVectorAdd(cam_pos, dx::XMVECTOR{ 0.0f,-0.3f,0.0f });
	}

	if (kbd.KeyIsPressed(VK_SHIFT))
	{
		cam_pos = dx::XMVectorAdd(cam_pos, dx::XMVECTOR{ 0.0f,0.3f,0.0f });
	}



	if (kbd.KeyIsPressed('R'))
	{
		Reset();
	}


	cam_rot = cam_rot*
		dx::XMMatrixRotationY(float(-mouse.GetPosX() + mousex)*dm)*
		dx::XMMatrixRotationX(float(-mouse.GetPosY() + mousey)*dm);
	mousey = mouse.GetPosY();
	mousex = mouse.GetPosX();
}

void Camera::Reset() noexcept
{
	cam_rot = DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	cam_pos = { 0.0f, 0.0f, 20.0f,0.0f };
}
