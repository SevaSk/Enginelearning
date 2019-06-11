#pragma once
#include "Drawable.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ComputeShader.h"

template<class T>
class DrawableBase : public Drawable
{
protected:
	static bool IsStaticInitialized() noexcept
	{
		return !staticBinds.empty();
	}
	static void AddStaticBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG)
	{
		assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
		staticBinds.push_back(std::move(bind));
	}
	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ibuf) noexcept(!IS_DEBUG)
	{
		assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
		pIndexBuffer = ibuf.get();
		staticBinds.push_back(std::move(ibuf));
	}

	void AddStaticVertexBuffer(std::unique_ptr<VertexBuffer> vbuf) noexcept(!IS_DEBUG)
	{
		pVertexBuffer = vbuf.get();
		staticBinds.push_back(std::move(vbuf));
	}

	void AddStaticComputeShader(std::unique_ptr<ComputeShader> cShader) noexcept(!IS_DEBUG)
	{
		assert("Attempting to add computeshader a second time" && pIndexBuffer == nullptr);
		pComputeShader = cShader.get();
		staticBinds.push_back(std::move(cShader));
	}


	void SetIndexFromStatic() noexcept(!IS_DEBUG)
	{
		assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
		for (const auto& b : staticBinds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
			{
				pIndexBuffer = p;
				return;
			}
		}
		assert("Failed to find index buffer in static binds" && pIndexBuffer != nullptr);
	}

	void SetVertexFromStatic() noexcept(!IS_DEBUG)
	{
		for (const auto& b : staticBinds)
		{
			if (const auto p = dynamic_cast<VertexBuffer*>(b.get()))
			{
				pVertexBuffer = p;
				return;
			}
		}
		assert("Failed to find index buffer in static binds" && pIndexBuffer != nullptr);
	}

	void SetComputeFromStatic() noexcept(!IS_DEBUG)
	{
		for (const auto& b : staticBinds)
		{
			if (const auto p = dynamic_cast<ComputeShader*>(b.get()))
			{
				pComputeShader = p;
				return;
			}
		}
		assert("Failed to find index buffer in static binds" && pIndexBuffer != nullptr);
	}



private:
	const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept override
	{
		return staticBinds;
	}
private:
	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};

template<class T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::staticBinds;