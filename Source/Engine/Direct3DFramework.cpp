#include "stdafx.h"
#include "Direct3DFramework.h"
#include "BaseWindow.h"

#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "dxgi.lib")
//#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_RELEASE(com_ptr) do { if (com_ptr) { com_ptr->Release(); com_ptr = nullptr; } } while(false)

namespace wendy
{
	CDirect3DFramework::CDirect3DFramework()
		: myDevice(nullptr)
		, myDeviceContext(nullptr)
		, mySwapchain(nullptr)
		, myBackBufferRTV(nullptr)
	{
	}

	CDirect3DFramework::~CDirect3DFramework()
	{
		SAFE_RELEASE(myBackBufferRTV);

		SAFE_RELEASE(mySwapchain);
		SAFE_RELEASE(myDeviceContext);
		SAFE_RELEASE(myDevice);
	}

	bool CDirect3DFramework::Init(CBaseWindow& aWindow)
	{
		cu::Vector2ui windowSize = aWindow.GetWindowSize();

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = windowSize.x;
		swapChainDesc.BufferDesc.Height = windowSize.y;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = static_cast<HWND>(aWindow.GetNativeHandle());
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0; // 
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

		UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined (DEBUG) || defined (_DEBUG)
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		HRESULT deviceAndSwapChainResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &mySwapchain, &myDevice, nullptr, &myDeviceContext);
		if (FAILED(deviceAndSwapChainResult))
		{
			return false;
		}

		if (!GetBackBuffer())
		{
			return false;
		}
		
		return true;
	}

	bool CDirect3DFramework::BeginFrame()
	{
		const float clearColour[4] = { 0.f, 0.f, 0.0f, 0.f };
		myDeviceContext->ClearRenderTargetView(myBackBufferRTV, clearColour);
		
		return true;
	}

	bool CDirect3DFramework::EndFrame()
	{
		HRESULT goodPresent = mySwapchain->Present(0, 0);

		return SUCCEEDED(goodPresent);
	}

	void CDirect3DFramework::OnWindowResize(const cu::Vector2ui& /*aWindowSize*/)
	{
	}

	void CDirect3DFramework::ActivateBackBuffer(ID3D11DepthStencilView* aDepthStencilView)
	{
		myDeviceContext->OMSetRenderTargets(1, &myBackBufferRTV, aDepthStencilView);
	}

	bool CDirect3DFramework::GetBackBuffer()
	{
		ID3D11Texture2D* backBuffer = nullptr;
		HRESULT backBufferResult = mySwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
		if (FAILED(backBufferResult))
		{
			return false;
		}

		HRESULT backBufferRTVResult = myDevice->CreateRenderTargetView(backBuffer, nullptr, &myBackBufferRTV);
		backBuffer->Release();
		if (FAILED(backBufferRTVResult))
		{
			return false;
		}

		return true;
	}
}
