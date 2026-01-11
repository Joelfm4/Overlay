#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <type_traits>

#include <d3d11.h>
#include <dwmapi.h>
#include <Windows.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

#include "Object.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Receibes the messages that are comming to the window
LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam);



class Overlay {



public:

	Overlay(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, INT showCmd);
	~Overlay();

	void BeginFrame();
	void DrawObjects(const std::vector<Object>& objects);
	void EndFrame();


private:

	HWND CreateOverlayWindow();
	void ExtendFrameIntoClientArea();
	void InitializeGraphics();


private:

	HINSTANCE instance;
	HINSTANCE prevInstance;
	PSTR cmdLine;
	INT showCmd;

	WNDCLASSEXW wc{};
	HWND window;

	// DirectX Variables
	ID3D11Device* device { nullptr };
	D3D_FEATURE_LEVEL level {};
	ID3D11Texture2D* backBuffer { nullptr };
	ID3D11RenderTargetView* renderTargetView { nullptr };
	ID3D11DeviceContext* deviceContext { nullptr };
	IDXGISwapChain* swapChain { nullptr };

	const float color[4]{0.f, 0.f, 0.f, 0.f};

};


