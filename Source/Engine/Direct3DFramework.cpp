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
	{
	}

	CDirect3DFramework::~CDirect3DFramework()
	{
		SAFE_RELEASE(mySwapchain);
		SAFE_RELEASE(myDeviceContext);
		SAFE_RELEASE(myDevice);
	}

	bool CDirect3DFramework::Init(const std::uint32_t aWidth, const std::uint32_t aHeight, CBaseWindow& aWindow)
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = aWidth;
		swapChainDesc.BufferDesc.Height = aHeight;
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

		HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &mySwapchain, &myDevice, nullptr, &myDeviceContext);
		if (FAILED(result))
		{
			return false;
		}

		return true;
	}

	bool CDirect3DFramework::BeginFrame()
	{
		return false;
	}

	bool CDirect3DFramework::EndFrame()
	{
		return false;
	}

	void CDirect3DFramework::OnWindowResize(const std::uint32_t /*aWidth*/, const std::uint32_t /*aHeight*/)
	{
	}
}
