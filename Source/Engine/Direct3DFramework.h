#pragma once
#include "BaseFramework.h"

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;

namespace wendy
{
	class CDirect3DFramework : public CBaseFramework
	{
	public:
		CDirect3DFramework();
		~CDirect3DFramework();

		virtual bool Init(const std::uint32_t aWidth, const std::uint32_t aHeight, CBaseWindow& aWindow) override;
		virtual bool BeginFrame() override;
		virtual bool EndFrame() override;
		virtual void OnWindowResize(const std::uint32_t aWidth, const std::uint32_t aHeight) override;

	private:
		ID3D11Device* myDevice;
		ID3D11DeviceContext* myDeviceContext;
		IDXGISwapChain* mySwapchain;
	};
}
