#include "Overlay.h"



LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {

	if (ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam))
		return 0L;

	if (message == WM_DESTROY) {

		PostQuitMessage(0);
		return 0L;

	}

	// Messages don't handle by the procedure
	return DefWindowProc(window, message, wParam, lParam);
}


// -------------------------------------------------------------------- //
//                        Constructor & Destructor                      //
// -------------------------------------------------------------------- //

Overlay::Overlay(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, INT showCmd) : 

	instance(instance),
	prevInstance(prevInstance),
	cmdLine(cmdLine),
	showCmd(showCmd),
	window(CreateOverlayWindow())

{

	ExtendFrameIntoClientArea();
	InitializeGraphics();
	

	ShowWindow(this->window, this->showCmd);
	UpdateWindow(this->window);


	// IMGUI Context
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(this->window);
	ImGui_ImplDX11_Init(this->device, this->deviceContext);

}


Overlay::~Overlay() {

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// Release DirectX
	if (this->swapChain) this->swapChain->Release();
	if (this->deviceContext) this->deviceContext->Release();
	if (this->device) this->device->Release();
	if (this->renderTargetView) this->renderTargetView->Release();

	// CleanUp Window
	DestroyWindow(this->window);
	UnregisterClassW(wc.lpszClassName, wc.hInstance);

	// CleanUp ImGui
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();


}


// -------------------------------------------------------------------- //
//                           Public Methods                             //
// -------------------------------------------------------------------- //

void Overlay::BeginFrame() {

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

}


void Overlay::DrawObjects(const std::vector<Object>& objects) {

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

	for (const auto& object : objects) {

		std::visit(
			[drawList](auto&& arg) {

				using T = std::decay_t<decltype(arg)>;

				if constexpr (std::is_same_v<T, Circle>)
					drawList->AddCircle(arg.center, arg.radius, arg.color);

				else if constexpr (std::is_same_v<T, Line>)
					drawList->AddLine(arg.p1, arg.p1, arg.color, arg.thickness);

				else if constexpr (std::is_same_v<T, Rect>)
					drawList->AddRect(arg.min, arg.max, arg.color);

			}, object
		);

	}

}


void Overlay::EndFrame() {

		ImGui::Render();

		// Target Color
		deviceContext->OMSetRenderTargets(1U, &renderTargetView, nullptr);
		deviceContext->ClearRenderTargetView(renderTargetView, color);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		
		swapChain->Present(1U, 0U);

}


// -------------------------------------------------------------------- //
//                          Private Methods                             //
// -------------------------------------------------------------------- //

HWND Overlay::CreateOverlayWindow() {

	// Window Class
	this->wc.cbSize = sizeof(WNDCLASSEXW);
	this->wc.style = CS_HREDRAW | CS_VREDRAW;
	this->wc.lpfnWndProc = WindowProcedure;
	this->wc.cbClsExtra = 0;
	this->wc.cbWndExtra = 0;
	this->wc.hInstance = instance;
	this->wc.hIcon = NULL;
	this->wc.hbrBackground = NULL;
	this->wc.lpszMenuName = NULL;
	this->wc.lpszClassName = L"Overlay Class";
	this->wc.hIconSm = NULL;

	// Register Class
	if (RegisterClassExW(&wc) == 0) {

		MessageBoxA(nullptr, "Failed to register class", "Error", MB_ICONERROR);
		exit(1);

	}

	// Create Window
	const HWND window = CreateWindowExW(
		WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
		wc.lpszClassName,
		L"Overlay",
		WS_POPUP,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);

	if (SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA) == 0) {

		std::string error = "Failed to set layered attributes " + std::to_string(GetLastError());

		MessageBoxA(nullptr, error.c_str(), "Error", MB_ICONERROR);
		exit(1);

	}


	return window;
}


void Overlay::ExtendFrameIntoClientArea() {

	RECT clientArea {};
	GetClientRect(this->window, &clientArea);

	RECT windowArea {};
	GetWindowRect(this->window, &windowArea);

	POINT diff {};
	ClientToScreen(this->window, &diff);

	const MARGINS margins{
		windowArea.left + (diff.x - windowArea.left),
		windowArea.top + (diff.y - windowArea.top),
		windowArea.right,
		windowArea.bottom,
	};

	if (DwmExtendFrameIntoClientArea(this->window, &margins) != S_OK) {

		MessageBoxA(nullptr, "Failed to extended the window frame into the client area", "Error", MB_ICONERROR);
		exit(1);

	}

}


void Overlay::InitializeGraphics() {

	// Set up DirectX 11
	DXGI_SWAP_CHAIN_DESC sd {};
	sd.BufferDesc.RefreshRate.Numerator = 60U;
	sd.BufferDesc.RefreshRate.Denominator = 1U;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1U;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2U;
	sd.OutputWindow = this->window;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Features wanted
	constexpr D3D_FEATURE_LEVEL levels[2]{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};

	if (D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0U,
		levels,
		2U,
		D3D11_SDK_VERSION,
		&sd,
		&this->swapChain,
		&this->device,
		&this->level,
		&this->deviceContext
	) != S_OK) {

		MessageBoxA(nullptr, "Failed to create device and swap chain", "Error", MB_ICONERROR);
		exit(1);

	}


	// Render Target
	this->swapChain->GetBuffer(0U, IID_PPV_ARGS(&backBuffer));

	if (this->backBuffer) {

		this->device->CreateRenderTargetView(this->backBuffer, nullptr, &this->renderTargetView);
		this->backBuffer->Release();

	} else {

		MessageBoxA(nullptr, "Failed to create render tartget view", "Error", MB_ICONERROR);
		exit(1);

	}


}

