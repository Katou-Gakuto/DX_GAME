#include "DxLib.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "ImguiManager.h"

#if _DEBUG

ImguiManager::ImguiManager()
{
}

ImguiManager::~ImguiManager()
{
}

// èâä˙âª
void ImguiManager::Initilize()
{
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;    
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // ImGui::StyleColorsDark();

    // ImGuiStyle& style = ImGui::GetStyle();


    // ImGui_ImplWin32_Init(DxLib::GetMainWindowHandle());
    // ImGui_ImplDX11_Init((ID3D11Device*)DxLib::GetUseDirect3D11Device(), (ID3D11DeviceContext*)DxLib::GetUseDirect3D11DeviceContext());
}

// èIóπ
void ImguiManager::Finalize()
{
    // ImGui_ImplDX11_Shutdown();
    // ImGui_ImplWin32_Shutdown();
    // ImGui::DestroyContext();
}

// çXêV
void ImguiManager::Update()
{	
    // ImGui_ImplDX11_NewFrame();
    // ImGui_ImplWin32_NewFrame();
    // ImGui::NewFrame();
    // ImGui::ShowDemoWindow();
}

// ï`âÊ
void ImguiManager::Draw()
{		
    // ImGui::Render();
    // ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
#endif