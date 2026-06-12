#include <string>
#include <vector>

#pragma comment(lib, "winmm.lib")

#include "../プロジェクトに追加すべきファイル_VC用/DxLib.h"

#include "../Source/DebugLogs/DebugLog.h"

struct OUTPUT_LOG_DATA
{
	VECTOR leftUpRate = VGet(-1.0f, -1.0f, -1.0f);
	VECTOR rightDownRate = VGet(-1.0f, -1.0f, -1.0f);

	int outputState = 0;
};

/// <summary>
/// メイン
/// </summary>
/// <param name="hInstance">HINSTANCE</param>
/// <param name="hPrevInstance">HINSTANCE</param>
/// <param name="lpCmdLine">LPSTR</param>
/// <param name="nCmdShow">int</param>
/// <returns>int</returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

#ifdef _DEBUG

	// デバッグ初期化
	DEBUG::DebugInitialization(/**/true/*/false/**/);

	// デバッグテキストの出力先を新しいファイルにする
	{
		DEBUG::DebugCreateLogFileName();
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME);

		DEBUG::DebugCreateLogFileName((DEBUG::DEBUG_MAP_TYPE)1, "_rate");

		DEBUG::DebugCreateLogFileName((DEBUG::DEBUG_MAP_TYPE)2, "_screenSize");
	}
#endif

	// ウインドウモードで起動
	ChangeWindowMode(true);

	// DXライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;		// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	OUTPUT_LOG_DATA outputData;
	outputData.outputState = 0;

	std::vector<OUTPUT_LOG_DATA> drawData;

	bool preSetFlag = false;

	bool preDeleteFlag = false;

#ifdef _DEBUG
	int screenW, screenH, colorBitDepth;
	GetScreenState(&screenW, &screenH, &colorBitDepth);
	DEBUG::SaveText("SCREEN SIZE: (" + std::to_string(screenW) + ", " + std::to_string(screenH) + ")\n", (DEBUG::DEBUG_MAP_TYPE)2);
#endif
	// ループ
	while ((ProcessMessage() == 0) && (CheckHitKey(KEY_INPUT_ESCAPE) == 0))
	{
		// ctrl+zを押してるなら初期化
		if ((CheckHitKey(KEY_INPUT_Z) != 0) && ((CheckHitKey(KEY_INPUT_LCONTROL) != 0) || (CheckHitKey(KEY_INPUT_RCONTROL) != 0)))
		{
			outputData.leftUpRate = VGet(-1.0f, -1.0f, -1.0f);
			outputData.rightDownRate = VGet(-1.0f, -1.0f, -1.0f);
			outputData.outputState = 0;
		}
		if (CheckHitKey(KEY_INPUT_BACK))
		{
			if (!preDeleteFlag)
			{
				preDeleteFlag = true;

				if (drawData.size() > 0)
				{
					drawData.erase(drawData.begin());
				}
			}
		}
		else
		{
			preDeleteFlag = false;
		}

		// 画面サイズとクリックと前回クリック情報があるならデバックに出力後　今回分も含めて消す
		int x, y;
		if ((GetMousePoint(&x, &y) == 0) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		{
			if (!preSetFlag)
			{
				preSetFlag = true;

				// クリックした時のカーソル位置設定
				outputData.outputState++;
				switch (outputData.outputState)
				{
				case 1:
					outputData.leftUpRate = VGet((float)x / (float)screenW, (float)y / (float)screenH, 0.0f);
					break;

				case 2:
					outputData.rightDownRate = VGet((float)x / (float)screenW, (float)y / (float)screenH, 0.0f);
					break;
				}
			}
		}
		else
		{
			preSetFlag = false;
		}

		// 両方の情報がそろっているなら出力する
		if (outputData.outputState == 2)
		{
#ifdef _DEBUG
			DEBUG::SaveText("rateLeftUp: (" + std::to_string(outputData.leftUpRate.x) + ", " + std::to_string(outputData.leftUpRate.y) + ")  rateRightDown: (" + std::to_string(outputData.rightDownRate.x) + ", " + std::to_string(outputData.rightDownRate.y) + ")\n", (DEBUG::DEBUG_MAP_TYPE)1);
#endif
			outputData.outputState = 0;

			outputData.leftUpRate = VGet(outputData.leftUpRate.x * (float)screenW, outputData.leftUpRate.y * (float)screenH, 0.0f);
			outputData.rightDownRate = VGet(outputData.rightDownRate.x * (float)screenW, outputData.rightDownRate.y * (float)screenH, 0.0f);
			drawData.push_back(outputData);
		}


		// 描画
		{
			ClearDrawScreen();

			for (int i = 0; i < drawData.size(); i++)
			{
				DrawBox(drawData[i].leftUpRate.x, drawData[i].leftUpRate.y, drawData[i].rightDownRate.x, drawData[i].rightDownRate.y, GetColor(0 + i, 255 - i, 0), FALSE);
			}

			if (outputData.outputState == 1)
			{
				DrawBox(outputData.leftUpRate.x * (float)screenW, outputData.leftUpRate.y * (float)screenH, x, y, GetColor(0 + drawData.size(), 255 - drawData.size(), 0), FALSE);
			}

			ScreenFlip();
		}
	}

	// DXライブラリ使用の終了処理
	DxLib::DxLib_End();

	// ソフトの終了
	return 0;
}