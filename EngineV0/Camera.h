#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"

class Camera
{
public:
	Camera(Mouse& mouse);
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void Update(float dt, Keyboard& kdb, Mouse& mouse) noexcept;
	void Reset() noexcept;
	

private:
	int mousex;
	int mousey;
	float dp = 0.3f;
	float dm = 0.01f;
	DirectX::XMMATRIX cam_rot;
	DirectX::XMVECTOR cam_pos;
};

