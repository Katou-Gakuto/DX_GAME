# 概要

DxLibを使用した3Dアクションゲーム「Robot_Battle」の個人開発プロジェクト

- ジャンル: 3Dアクションゲーム
- 開発規模: 200ファイル以上、C++20
- 開発期間: 個人開発
- 役割: 全工程担当（設計、実装、テスト）

**ゲーム内容:**
- TITLE → TOWN（町）→ DUNGEON（ダンジョン）→ BATTLE（バトル）→ RESULT → GAME_CLEAR/GAME_OVERの進行構造
- ステージ構成: TOWN_1〜3, DUNGEON_1〜3, BATTLE_1〜3
- キャラクター種類: プレイヤー、敵、マップ上の敵、ボス敵
- 攻撃方法: ノーマル攻撃、スペシャル攻撃、ジャンプ攻撃、ショット攻撃
- オブジェクト種類: キャラクター、建物（壁）、攻撃オブジェクト、UI
- スコア評価システム: A〜Dランク

# 担当箇所

## 全工程担当

- ゲームループ、更新/描画処理
- 状態管理システム（FSM）
- リソース管理システム
- オブジェクト管理システム
- 入力システム（キーボード、コントローラー、マウス）
- 3Dカメラ、3Dサウンド、シャドウマップ
- UIシステム、シーン遷移
- 全てのマネージャークラスの実装

## 主要クラス

- **Master**: 全マネージャーの静的ポインタ管理（24のマネージャー）
- **GameManager**: ゲーム内マネージャー統括、ゲームループ制御
- **TimeManager**: 時間管理、固定フレームレート制御
- **KeyState**: 入力システム（キーボード、コントローラー、マウス）
- **ObjectManager**: オブジェクト管理（線形リスト構造）
- **SceneManager**: シーン管理（FSMScene）
- **ResourceManager**: リソース管理（参照カウント）
- **DrawManager**: 描画情報管理
- **FSMBase**: 有限状態マシン基底クラス
- **BIT_FLAG**: 汎用ビットフラグ構造体
- **HandleContainer**: 汎用ハンドルコンテナ

# 使用技術

## プログラミング言語・ライブラリ

- **C++20**
  - テンプレートメタプログラミング（SFINAE）
  - テンプレートオーバーロード
  - std::futureによる非同期処理
  - std::map, std::vectorによるコンテナ管理

- **DxLib**（DirectXライブラリ）
  - 3Dモデル描画
  - 3Dサウンド
  - シャドウマップ
  - 入力処理

- **ImGui**（デバッグ用UI）

- **Effekseer**（エフェクトライブラリ）

- **Visual Studio 2022**

- **Windows API**

- **XAudio2**（サウンド）

## 開発環境

- OS: Windows
- コンパイラ: MSVC
- ビルドシステム: Visual Studioプロジェクト

# システム構成

## マネージャークラス一覧（24クラス）

### Master管理
- **Master**: 全マネージャーの静的ポインタ管理

### ゲーム内マネージャー（GameManager所有）
- **AttackManager**: 攻撃管理
- **CameraManager**: カメラ管理
- **CollisionManager**: 当たり判定管理
- **DotWeenManager**: 補間アニメーション管理
- **MapManager**: マップ管理
- **ObjectManager**: オブジェクト管理
- **SceneManager**: シーン管理
- **TargetManager**: ターゲット管理

### Master管理（ゲーム外）
- **DataManager**: データ管理
- **DrawManager**: 描画情報管理
- **EndManager**: 終了管理
- **FadeManager**: フェード管理
- **ImguiManager**: ImGui管理
- **KeyState**: 入力管理
- **LoadingManager**: ローディング管理
- **ResourceManager**: リソース管理
- **StageDataManager**: ステージデータ管理
- **StopManager**: ストップ管理
- **TelopManager**: テロップ管理
- **ThreadManager**: スレッド管理
- **TimeManager**: 時間管理
- **SoundManager**: サウンド管理

## 有限状態マシン（FSM）

### 6種類のFSM

1. **FSMAnimation**: アニメーション状態管理
   - StateMVOneAnimation
   - StateMVOneOperationAnimation
   - StateNormalAttackInAnimationController
   - StateNormalAttackOutAnimationController
   - など

2. **FSMCamera**: カメラ状態管理
   - StateTitleCamera
   - StateGameCamera
   - StateResultCamera
   - など

3. **FSMCharacter**: キャラクター状態管理
   - StateTownPlayer
   - StateDungeonPlayer
   - StateBattlePlayer
   - StateEnemy
   - StateBossEnemy
   - など

4. **FSMDotWeen**: 補間アニメーション状態管理

5. **FSMScene**: シーン状態管理
   - StartScene
   - TitleScene
   - TownScene
   - DungeonScene
   - BattleScene
   - ResultScene
   - GameOverScene
   - GameClearScene
   - など

6. **FSMUI**: UI状態管理
   - StateTitleUI
   - StateGameUI
   - StateResultUI
   - など

## データ構造

### オブジェクト管理
- 線形リスト構造（双方向連結リスト）
- タイプ別リスト（全オブジェクト + キャラクター/建物/攻撃/UI）
- ID、タグ、チーム、オブジェクトタイプによる検索

### リソース管理
- 参照カウント付きハンドル管理
- HandleContainer<T>による汎用化
- リソース種類: 3Dモデル、画像、動画、サウンド、エフェクト

### 入力管理
- ビットフラグによるフラグ管理
- BIT_FLAG<T>による汎用化
- フラグ種類: NOW（押している）、DOWN（押し始めた）、UP（離した）

# 実装機能

## ゲームループ

### Main.cppの構造
```
1. DxLib_Init() - DXライブラリ初期化
2. while (!EndFlag()) {
   - ローディング処理
   - if (TimeManager->GetNextUpdateFlag()) {
     - ImGui更新（デバッグ時）
     - GameManager->Update()
     - GameManager->DeleteAllIfNeeded()
     - GameManager->Draw()
   }
}
3. Master->AllDelete()
4. DxLib_End()
```

### TimeManagerによるフレーム制御
- timeBeginPeriod(1)で1ms精度タイマー
- 固定フレームレート制御（デフォルト17ms = 約60FPS）
- デバッグ時は固定時間、リリース時は実時間
- バックグラウンド移行時の時間調整

## 更新処理

### GameManager::Update()の実行順序
1. KeyState->Update() - 入力状態更新
2. CameraManager->Update() - カメラ更新
3. ObjectManager->ObjectUpdate() - オブジェクト更新
4. DotWeenManager->Update() - 補間アニメーション更新
5. CollisionManager->CollisionProcess() - 当たり判定処理
6. ObjectManager->ObjectLastUpdate() - オブジェクト最終更新
7. SceneManager->Update() - シーン更新
8. ResourceManager->Update() - リソース更新

## 描画処理

### GameManager::Draw()の実行順序
1. ClearDrawScreen() - 画面クリア
2. CameraManager->Draw() - カメラ設定
3. ResourceManager->StartDraw() - 描画開始処理
4. ObjectManager->ObjectDraw() - オブジェクト描画（前半）
5. MapManager->Draw() - マップ描画（前半）
6. ResourceManager->MiddleDraw() - 中間描画処理
7. ObjectManager->ObjectDraw() - オブジェクト描画（後半）
8. MapManager->Draw() - マップ描画（後半）
9. ResourceManager->LastDraw() - 最終描画処理
10. DrawManager->Draw() - 描画マネージャー描画
11. FadeManager->Draw() - フェード描画
12. ResourceManager->DrawDataRelease() - 描画データ解放
13. ImguiManager->Draw() - ImGui描画（デバッグ時）
14. ScreenFlip() - 画面反転

## 入力システム

### KeyStateの管理対象
- キーボード（文字操作、特殊キー、テンキー）
- コントローラー（最大4台、ボタン、スティック、トリガー）
- マウス（ボタン、ホイール、移動）

### フラグ種類
- NOW - 現在押している
- DOWN - 押し始めた瞬間
- UP - 離した瞬間

### 取得メソッド
- GetKey_XXX() - 個別キー状態
- GetXXXKeyFlags_XXX() - フラグ一括取得
- GetKeyAllController() - 全コントローラー統合

## シーン管理

### シーン遷移フロー
1. SetNextScene(SCENE) - 次のシーン設定
   - FadeManager->FadeOut() - フェードアウト開始
2. SceneManager->NextScene() - シーン遷移実行
   - TimeManager->SetNewSceneTimeFlag() - 時間調整
   - 前シーンのOnExit()呼び出し
   - 前シーンのオブジェクト削除
   - DrawManager->DeleteDrawData() - 描画情報削除
   - FSMScene->NextScene() - FSMでシーン変更
   - ObjectSceneLastInitilize() - 新シーン初期化
3. FSMScene->Update() - 現在シーンの更新

### シーン種類
- START, TITLE
- TOWN, TOWN_1, TOWN_2, TOWN_3
- DUNGEON, DUNGEON_1, DUNGEON_2, DUNGEON_3
- BATTLE, BATTLE_1, BATTLE_2, BATTLE_3
- RESULT, DUNGEON_RESULT, BATTLR_RESULT
- GAME_OVER
- GAME_CLEAR

## リソース管理

### 管理するリソース
- 3Dモデル（HandleContainerで参照カウント）
- 画像（HandleContainer、Div画像対応）
- 動画（HandleContainer、再生制御）
- サウンド（2D/3D、ボリューム制御）
- エフェクト（Effekseer、再生制御）

### 描画機能
- StartDraw() - 描画開始（シャドウマップ等）
- MiddleDraw() - 中間処理
- LastDraw() - 最終処理
- DrawModelHandle() - 3Dモデル描画
- DrawData_Graph() - 画像描画
- DrawEffect() - エフェクト描画

## 3D機能

### 3Dカメラ
- FSMCameraによる状態管理
- タイトル、ゲーム、リザルトなどシーン別カメラ

### 3Dサウンド
- 3Dサウンドリスナー位置設定
- ボリューム制御
- 再生制御

### シャドウマップ
- シャドウマップ初期化
- 描画開始時のシャドウマップ設定

### 当たり判定
- 球面当たり判定（SphereCollision）
- VECTOR計算ユーティリティ

## UIシステム

### UI種類
- TITLE UI
- TOWN UI
- DUNGEON UI
- BATTLE UI
- RESULT UI
- GAME CLEAR UI
- STAGE START UI

### FSMUIによる状態管理
- StateTitleUI
- StateGameUI
- StateResultUI
- StateGameClearUI
- StateStageStartUI

## デバッグ機能

### デバッグログシステム
- シーン遷移ログ
- ハンドル未発見ログ
- _DEBUGマクロで本番ビルド時に削除

### ImGuiデバッグUI
- デバッグ情報表示
- _DEBUGマクロで本番ビルド時に削除

### デバッグビルド時のみのチェック
- ビット数オーバーチェック（BIT_FLAG）
- エラー時のフラグ設定

# 技術的な工夫

## 高度なC++テンプレートの活用

### BIT_FLAG<T>（BitFlag.h:11-273）
- SFINAEによる型制約（std::enable_ifでunsigned整数のみ許可）
- テンプレートオーバーロードによるenum class対応
- 273行に及ぶ汎用的なビットフラグ実装
- ビット演算の共通化
- デバッグビルド時のみのビット数オーバーチェック

### HandleContainer<T>（HandleContainer.h:22-373）
- 任意のキー型に対応可能なテンプレートクラス
- std::string以外のキー型にも対応
- リソースハンドルの参照カウント管理を汎用化
- ハンドルフラグによる制御（ZERO_LOOK, ZERO_EXCEPT_LOOK）

## デザインパターンの適用

### ファクトリーパターン（UtilFactorys.h:97-146）
- FSMAnimationFactory
- FSMCameraFactory
- FSMCharacterFactory
- FSMSceneFactory
- FSMUIFactory
- ModelFactory
- AnimationDataFactory
- AttackDataFactory
- 複雑なオブジェクト生成を一箇所に集約

### ステートマシンパターン（FSM.h:23-200）
- FSMBase<T, U>テンプレートによる汎用FSM
- 6種類のFSM（Animation, Camera, Character, DotWeen, Scene, UI）
- 状態遷移ロジックをカプセル化
- 新しいステートを追加する場合、IStateインターフェースを実装するだけでOK

### シングルトンパターン（Master.h:21-43）
- 全マネージャーの静的ポインタを一元管理
- グローバルアクセスポイントを提供
- AllDelete()による一括削除

### コンポジションパターン（AnimationBase.h:9-76）
- AnimationBaseがModelsControllerBaseとFSMAnimationを所有
- 機能をモジュール化して組み合わせ

## パフォーマンス最適化

### 線形リストによるオブジェクト管理（ObjectManager.cpp:56-72）
- ベクターよりメモリ効率が良い（再確保なし）
- 追加/削除がO(1)で可能（先頭/末尾操作）
- キャッシュヒット率が高い（連続メモリ）
- タイプ別リストの二重管理（全オブジェクト + タイプ別）

### 参照カウントによるリソース管理（HandleContainer.h:147-150）
- 同じリソースを複数オブジェクトで共有
- カウントが0になった時点で解放
- リソースの重複読み込みを防止
- ハンドルフラグによる制御（ZERO_LOOK: モデル複製なし、ZERO_EXCEPT_LOOK: 複製）

### ビット演算によるフラグ管理（BitFlag.h:64-157）
- 1つの整数で複数のフラグを管理
- メモリ効率が良い
- 演算速度が速い
- 入力フラグのビット管理（FLAG_TYPE::MAX × CONTROLLER_KEY_NUMBER::MAX_CONTROLLER）

### 非同期処理（ThreadManager.h:6-23）
- std::future<void>で非同期タスク管理
- CleanupReadyTasksで完了タスクの削除
- ローディング処理の非同期化

### 固定フレームレート制御（TimeManager.cpp:49-118）
- timeBeginPeriod(1)で1ms精度タイマー
- GetNextUpdateFlag()で固定フレームレート（デフォルト17ms）
- デバッグ時は固定時間、リリース時は実時間

## メモリ管理

### 参照カウント付きリソース管理（HandleContainer.h:218-237）
- mmHandleCountsで各ハンドルの参照数を管理
- RegisterHandleでカウント増加、DeleteHandleでカウント減少
- カウントが0でリソース解放
- リソース解放の遅延（削除予定ハンドルをvectorで返す）

### 遅延削除によるメモリ管理（ObjectManager.cpp:373-392）
- 削除フラグが立ったオブジェクトを一括削除
- 更新ループ中の削除による不整合を防止
- フレームの終了時にまとめて解放
- シーン切り替え時の削除（DeleteSetSceneで前シーンのオブジェクトに削除フラグ設定）

### 明示的なライフサイクル管理（GameManager.cpp:76-126）
- Initialize/SceneLastInitilize/Finalizeの3段階初期化
- Initialize: 基本的な初期化
- SceneLastInitilize: シーン固有の初期化
- Finalize: 終了処理
- 各マネージャーの明示的な初期化・終了
- 作成順序を制御（依存関係の解決）
- 逆順で終了処理

## デバッグ容易化

### デバッグログシステム（DebugLogs/DebugLog.h）
- シーン遷移、ハンドル未発見などのログ記録
- _DEBUGマクロで本番ビルド時に削除

### ビットフラグの境界チェック（BitFlag.h:66-76, 86-96, 106-116）
- デバッグビルド時のみビット数オーバーチェック
- BIT_FAILURE_FLAGでエラー検出

### ImGuiデバッグUI（ImguiManager）
- デバッグ情報表示
- _DEBUGマクロで本番ビルド時に削除

## 実務的な対応

### バックグラウンド対応（TimeManager.cpp:120-132）
- アプリ非アクティブ時の時間を記録
- 復帰時に経過時間を調整
- 未処理のバックグラウンド時間を経過時間に加算

### ローディング処理（LoadingManager.h:10-42）
- BIT_FLAGでローディング状態管理
- フェード中、シーン切り替え時のローディング
- 非対応スレッドによるローディング

### フェード遷移（SceneManager.cpp:63-67）
- FadeManagerによるフェードアウト/イン
- シーン遷移時のフェード制御

### ウィンドウプロシージャ（GameManager.cpp:238-322）
- フォーカス管理
- アクティブ/非アクティブ時の処理

# 苦労した点

## 複雑な状態管理

### 6種類のFSM連携
- Animation, Camera, Character, DotWeen, Scene, UIのFSMを連携させる必要がある
- シーン遷移時にオブジェクトの削除、初期化、状態リセットを適切に行う必要がある
- キャラクターの状態（待機、移動、攻撃、ダメージ、死亡）とアニメーションの同期

### 根拠
- FSM.h:23-200（6種類のFSMクラス）
- StateBase.h:28-241（7種類のIStateインターフェース）
- SceneManager.cpp:41-60（シーン遷移時の複雑な処理）

## リソース管理の複雑さ

### 参照カウントによる共有リソース管理
- ハンドルの複製（モデル複製）と参照カウントの整合性
- 非同期ローディング時のリソース解放タイミング
- エフェクトの再生制御（停止/再生/削除）

### 根拠
- HandleContainer.h:22-373（参照カウント管理）
- ResourceManager.h:244-269（エフェクト管理）
- ThreadManager.h:6-23（非同期スレッド）

## 3Dゲームの複雑さ

### 3D機能の実装
- 3Dカメラ制御（FSMCameraによる状態管理）
- 3Dサウンドリスナー位置設定
- シャドウマップの実装
- 3Dモデルのアニメーション制御
- 球面当たり判定の実装

### 根拠
- ResourceManager.h:220-222（3Dサウンド）
- ResourceManager.h:72-73（シャドウマップ）
- UtilCalc.h:82（球面当たり判定）
- AnimationBase.h:9-76（アニメーション管理）

## 入力システムの複雑さ

### 入力デバイスの統合管理
- キーボード（文字操作、特殊キー、テンキー）、コントローラー（最大4台）、マウスの統合管理
- 押し始め/押している/離したの3状態管理
- ビットフラグによる効率的なフラグ管理
- コントローラーのスティック、トリガーのアナログ値管理

### 根拠
- KeyState.h:1-843（843行の入力管理）
- BitFlag.h:11-273（ビットフラグ実装）

## メモリ管理の難しさ

### 線形リストの操作
- 線形リストの追加/削除操作
- 遅延削除による更新ループ中の削除問題回避
- シーン切り替え時のオブジェクト一括削除
- リソースの参照カウント管理

### 根拠
- ObjectManager.cpp:113-201（線形リスト操作）
- ObjectManager.cpp:373-392（遅延削除）
- SceneManager.cpp:46（シーン切り替え時の削除）

## アニメーションデータのハードコード

### データマネージャー未対応
- アニメーション時間、パスなどがハードコードされている
- データマネージャーから取得できるようにする必要がある

### 根拠
- UtilFactorys.cpp:346, 381, 454, 486, 518（ハードコード）
- TODOコメント: 「データマネージャー取得できるようにする」

# 今後の改善点

## アニメーションデータのデータマネージャー対応

### 現状
- アニメーション時間、パスなどがハードコードされている（UtilFactorys.cpp）
- 各キャラクター種類ごとに個別に設定している

### 改善案
- データマネージャーからアニメーションデータを取得できるようにする
- XMLやJSONなどの外部ファイルから読み込む
- 設定ファイルによる柔軟な調整

### 根拠
- UtilFactorys.cpp:346, 381, 454, 486, 518
- TODOコメント: 「データマネージャー取得できるようにする」

## 未実装関数の実装

### SettingAnimationAndModelFactory
- 全アニメーションとモデル設定を一括で行う関数
- 現在はコメントアウトされている

### SwapHandle
- HandleContainerのハンドル交換関数
- 現在は空実装

### 根拠
- UtilFactorys.h:119-121（SettingAnimationAndModelFactory）
- HandleContainer.h:369-372（SwapHandle）

## 未完成関数の完成

### VVecToAngle
- ベクトルをアングルに変換する関数
- 現在はYのみ実装済み

### VAngleToVec
- アングルをベクトルに変換する関数
- 現在は未実装

### 根拠
- UtilCalc.h:54-60（TODOコメント: 未完）

## 各プロパティswitchの中身の簡素化

### 現状
- UtilFactorys.cpp:161-201で各プロパティのswitch文が長い
- モデル種類ごとに個別に処理している

### 改善案
- 各プロパティswitchの中身を簡単にできるようにする
- マップやテーブルによる簡素化

### 根拠
- UtilFactorys.cpp:161（TODOコメント: 各プロパティswitchの中身を簡単にできるC）

## 外で固定するフレームの名前取得機能

### 現状
- フレーム名がハードコードされている（例: "root"）

### 改善案
- 外で固定するフレームの名前取得できるようにする
- 設定ファイルから読み込む

### 根拠
- UtilFactorys.cpp:178（HACKコメント: 外で固定するフレームの名前取得できるようにする）

## 変数名の改善

### 現状
- 一部の変数名が紛らわしい
- HACKコメントで改善が必要とされている

### 改善案
- 変数名をわかりやすい名前に変更する
- 命名規則の統一

### 根拠
- HandleContainer.h:200（HACKコメント: 変数名紛らわしいから変更）
- UtilFactorys.h:100（HACKコメント: 変数名変更する）

## アニメーション終了後の次の行動の追加

### 現状
- アニメーション終了後の次の行動が未実装

### 改善案
- アニメーション終了後に次の行動を追加する
- アニメーション連鎖の実装

### 根拠
- UtilFactorys.cpp:425, 467, 532, 559, 586, 619（TODOコメント: アニメーション終了後に次に行くの追加）

## シーン名の仮実装からの改善

### 現状
- ANIMATION_FACTORY_NUMBERがシーン名で仮実装されている

### 改善案
- シーン名以外の適切な命名に変更する
- アニメーション種類による分類

### 根拠
- UtilFactorys.h:29（TODOコメント: 仮でシーン名でやっている）

## シーン種類変更関数の改善

### 現状
- SceneState関数がswitch文で実装されている

### 改善案
- 関数を変更する
- マップによる簡素化

### 根拠
- UtilChange.h:17（TODOコメント: 後で関数変更）
