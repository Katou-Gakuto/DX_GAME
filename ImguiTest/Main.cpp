
#include "DxLib.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

	// メッセージ処理はDxLibで行っているようだ

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int gh = -1; // グラフィックハンドル

	// 初期設定
	{
		// DxLib
		{
			DxLib::SetGraphMode(1280, 720, 32);
			DxLib::ChangeWindowMode(true);
			DxLib::SetUseDirect3DVersion(DX_DIRECT3D_11);
			DxLib::SetHookWinProc(WndProc);
			DxLib::SetAlwaysRunFlag(true);
			if (DxLib::DxLib_Init() == -1) { return false; }
			DxLib::SetDrawScreen(DX_SCREEN_BACK);

			gh = LoadGraph("test1.bmp"); // ★このファイルはDxLibのサンプルに入ってたものです(キャラ画像)
		}

		// ImGui
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows　★ここ消すとマルチウィンドウ解除

			ImGuiStyle& style = ImGui::GetStyle();
	/*		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}*/

			ImGui_ImplWin32_Init(DxLib::GetMainWindowHandle());
			ImGui_ImplDX11_Init((ID3D11Device*)DxLib::GetUseDirect3D11Device(), (ID3D11DeviceContext*)DxLib::GetUseDirect3D11DeviceContext());
		}
	}

	// メインループ
	while (!DxLib::ProcessMessage())
	{
		// 更新部
		{
			// DxLib
			{
				// 特になし
			}

			// ImGui
			{
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
				ImGui::ShowDemoWindow();
			}
		}

		// 描画部
		{
			DxLib::ClearDrawScreen();

			// DxLib
			{
				DrawGraph(0, 0, gh, true); // ★これが消えてしまう
			}

			// ImGui
			{
				ImGui::Render();
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
				// Update and Render additional Platform Windows
				//if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
				//{
				//	ImGui::UpdatePlatformWindows();
				//	ImGui::RenderPlatformWindowsDefault(); // ★これが怪しい
				//}
			}

			DxLib::ScreenFlip();
		}
	}

	// 終了処理
	{
		// ImGui
		{
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
		}

		// DxLib
		{
			DxLib::DxLib_End();
		}
	}

	return 0;
}