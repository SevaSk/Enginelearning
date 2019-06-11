#include "Drawable.h"
#include "GraphicsThrowMacros.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ComputeShader.h"
#include <cassert>
#include <typeinfo>

void Drawable::Draw(Graphics& gfx) const noexcept(!IS_DEBUG)
{
	for (auto& b : binds)
	{
		b->Bind(gfx);
	}
	for (auto& b: GetStaticBinds() )
	{
		b->Bind(gfx);
	}

	gfx.DrawInstancedIndirect(pComputeShader->GetArgsBuffer());
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG)
{
	assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
	binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf) noexcept(!IS_DEBUG)
{
	assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
	pIndexBuffer = ibuf.get();
	binds.push_back(std::move(ibuf));
}

//for drawing non index buffers temp fix 
void Drawable::AddVertexBuffer(std::unique_ptr<VertexBuffer> vbuf) noexcept(!IS_DEBUG)
{
	pVertexBuffer = vbuf.get();
	binds.push_back(std::move(vbuf));
}

void Drawable::AddComputeShader(std::unique_ptr<class ComputeShader> cShader) noexcept(!IS_DEBUG)
{
	pComputeShader = cShader.get();
	binds.push_back(std::move(cShader));
}
