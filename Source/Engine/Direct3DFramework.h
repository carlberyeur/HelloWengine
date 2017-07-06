#pragma once
#include "BaseFramework.h"

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;

struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace wendy
{
	class CDirect3DFramework : public CBaseFramework
	{
	public:
		CDirect3DFramework();
		~CDirect3DFramework();

		virtual bool Init(CBaseWindow& aWindow) override;
		virtual bool BeginFrame() override;
		virtual bool EndFrame() override;
		virtual void OnWindowResize(const cu::Vector2ui& aWindowSize) override;

		void ActivateBackBuffer(ID3D11DepthStencilView* aDepthStencilView);

	private:
		bool GetBackBuffer();

		ID3D11Device* myDevice;
		ID3D11DeviceContext* myDeviceContext;
		IDXGISwapChain* mySwapchain;

		ID3D11RenderTargetView* myBackBufferRTV;
	};
}
