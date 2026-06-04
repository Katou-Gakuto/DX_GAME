# Robot_Battle - 3Dアクションゲーム

## 概要

DxLibを使用した3Dアクションゲームの個人開発プロジェクト

- **ジャンル**: 3Dアクションゲーム
- **開発規模**: 200ファイル以上、C++20
- **開発期間**: 個人開発
- **役割**: 全工程担当（設計、実装、テスト）

## ゲーム内容

- **進行構造**: TITLE → TOWN（町）→ DUNGEON（ダンジョン）→ BATTLE（バトル）→ RESULT → GAME_CLEAR/GAME_OVER
- **ステージ構成**: TOWN_1〜3, DUNGEON_1〜3, BATTLE_1〜3
- **キャラクター**: プレイヤー、敵、マップ上の敵、ボス敵
- **攻撃方法**: ノーマル攻撃、スペシャル攻撃、ジャンプ攻撃、ショット攻撃
- **オブジェクト種類**: キャラクター、建物（壁）、攻撃オブジェクト、UI
- **スコア評価**: A〜Dランク

## 使用技術

### プログラミング言語・ライブラリ
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

## ファイル構成

```
DX_GAME/
├── Source/                    # ソースコード
│   ├── Main.cpp              # エントリーポイント
│   ├── Animation/            # アニメーション関連
│   │   ├── AnimationBase.h/cpp
│   │   └── AnimationData.h
│   ├── Container/            # コンテナ関連
│   │   └── HandleContainer.h  # 参照カウント付きハンドルコンテナ
│   ├── DebugLogs/            # デバッグログ
│   ├── Enum/                 # 列挙型定義
│   │   ├── SceneEnum.h       # シーン列挙
│   │   ├── CharacterEnum.h  # キャラクター列挙
│   │   └── ...
│   ├── Model/                # モデル関連
│   │   ├── ModelBase.h/cpp
│   │   └── ModelsController/
│   ├── Object/               # オブジェクト関連
│   │   ├── ObjectBases.h     # オブジェクト基底クラス
│   │   ├── CharacterBase.h/cpp
│   │   ├── BuildingBase.h/cpp
│   │   ├── AttackBase.h/cpp
│   │   └── UIBase.h/cpp
│   ├── Singleton/            # マネージャークラス（48ファイル）
│   │   ├── Master.h         # 全マネージャーの静的ポインタ管理
│   │   ├── GameManager.h/cpp # ゲームマネージャー
│   │   ├── TimeManager.h/cpp # 時間管理
│   │   ├── KeyState.h/cpp    # 入力管理
│   │   ├── ObjectManager.h/cpp # オブジェクト管理
│   │   ├── SceneManager.h/cpp # シーン管理
│   │   ├── ResourceManager.h/cpp # リソース管理
│   │   ├── DrawManager.h/cpp # 描画管理
│   │   ├── CameraManager.h/cpp
│   │   ├── CollisionManager.h/cpp
│   │   ├── AttackManager.h/cpp
│   │   ├── MapManager.h/cpp
│   │   ├── TargetManager.h/cpp
│   │   ├── DotWeenManager.h/cpp
│   │   ├── FadeManager.h/cpp
│   │   ├── LoadingManager.h/cpp
│   │   ├── StopManager.h/cpp
│   │   ├── TelopManager.h/cpp
│   │   ├── ThreadManager.h/cpp
│   │   ├── SoundManager.h/cpp
│   │   ├── DataManager.h/cpp
│   │   ├── StageDataManager.h/cpp
│   │   ├── EndManager.h/cpp
│   │   └── ImguiManager.h/cpp
│   ├── State/                # 状態管理（FSM）
│   │   ├── StateBase.h       # 状態基底インターフェース
│   │   ├── FSM.h             # 有限状態マシン基底クラス
│   │   ├── Animation/        # アニメーション状態
│   │   ├── Camera/           # カメラ状態
│   │   ├── Character/        # キャラクター状態
│   │   ├── Scene/            # シーン状態
│   │   └── UI/               # UI状態
│   ├── Struct/               # 構造体
│   │   └── BitFlag.h         # 汎用ビットフラグ構造体
│   └── Util/                 # ユーティリティ
│       ├── UtilCalc.h/cpp    # 計算ユーティリティ
│       ├── UtilChange.h/cpp  # 変換ユーティリティ
│       └── UtilFactorys.h/cpp # ファクトリーメソッド
├── Resource/                 # リソースファイル
│   ├── 3D/                   # 3Dモデル
│   ├── Graph/                # 画像
│   ├── Sound/                # サウンド
│   └── Effect/               # エフェクト
├── Data/                     # データファイル
├── MapData/                  # マップデータ
├── Text/                     # テキストファイル
├── XML_Excel/                # XML/Excelファイル
├── Robot_Battle.vcxproj      # Visual Studioプロジェクトファイル
└── README.md                # README（簡易版）
```

## システム構成

### マネージャークラス一覧（24クラス）

#### Master管理
- **Master**: 全マネージャーの静的ポインタ管理

#### ゲーム内マネージャー（GameManager所有）
- **AttackManager**: 攻撃管理
- **CameraManager**: カメラ管理
- **CollisionManager**: 当たり判定管理
- **DotWeenManager**: 補間アニメーション管理
- **MapManager**: マップ管理
- **ObjectManager**: オブジェクト管理
- **SceneManager**: シーン管理
- **TargetManager**: ターゲット管理

#### Master管理（ゲーム外）
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

### 有限状態マシン（FSM）

#### 6種類のFSM
1. **FSMAnimation**: アニメーション状態管理
2. **FSMCamera**: カメラ状態管理
3. **FSMCharacter**: キャラクター状態管理
4. **FSMDotWeen**: 補間アニメーション状態管理
5. **FSMScene**: シーン状態管理
6. **FSMUI**: UI状態管理

#### シーン種類
- START, TITLE
- TOWN, TOWN_1, TOWN_2, TOWN_3
- DUNGEON, DUNGEON_1, DUNGEON_2, DUNGEON_3
- BATTLE, BATTLE_1, BATTLE_2, BATTLE_3
- RESULT, DUNGEON_RESULT, BATTLR_RESULT
- GAME_OVER
- GAME_CLEAR

## 実装機能

### ゲームループ
- 固定フレームレート制御（約60FPS）
- デルタタイムの計算と適用
- バックグラウンド対応（アプリ非アクティブ時の時間調整）

### 更新処理（GameManager::Update()の実行順序）
1. KeyState->Update() - 入力状態更新
2. CameraManager->Update() - カメラ更新
3. ObjectManager->ObjectUpdate() - オブジェクト更新
4. DotWeenManager->Update() - 補間アニメーション更新
5. CollisionManager->CollisionProcess() - 当たり判定処理
6. ObjectManager->ObjectLastUpdate() - オブジェクト最終更新
7. SceneManager->Update() - シーン更新
8. ResourceManager->Update() - リソース更新

### 描画処理（GameManager::Draw()の実行順序）
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

### 入力システム（KeyState）
- キーボード（文字操作、特殊キー、テンキー）
- コントローラー（最大4台、ボタン、スティック、トリガー）
- マウス（ボタン、ホイール、移動）
- フラグ種類: NOW（押している）、DOWN（押し始めた）、UP（離した）

### リソース管理（ResourceManager）
- 3Dモデル（参照カウント）
- 画像（Div画像対応）
- 動画（再生制御）
- サウンド（2D/3D、ボリューム制御）
- エフェクト（Effekseer、再生制御）

### 3D機能
- 3Dカメラ制御（FSMCamera）
- 3Dサウンド（リスナー位置設定）
- シャドウマップ
- 球面当たり判定

### UIシステム
- TITLE UI, TOWN UI, DUNGEON UI, BATTLE UI, RESULT UI
- GAME CLEAR UI, STAGE START UI
- FSMUIによる状態管理

### デバッグ機能
- デバッグログシステム
- ImGuiデバッグUI
- デバッグビルド時のみのチェック（ビット数オーバーチェック）

## 技術的な工夫

### 1. 高度なC++テンプレートの活用

#### BIT_FLAG<T>（Struct/BitFlag.h:11-273）
- SFINAEによる型制約（std::enable_ifでunsigned整数のみ許可）
- テンプレートオーバーロードによるenum class対応
- 273行に及ぶ汎用的なビットフラグ実装
- ビット演算の共通化
- デバッグビルド時のみのビット数オーバーチェック

#### HandleContainer<T>（Container/HandleContainer.h:22-373）
- 任意のキー型に対応可能なテンプレートクラス
- std::string以外のキー型にも対応
- リソースハンドルの参照カウント管理を汎用化
- ハンドルフラグによる制御（ZERO_LOOK, ZERO_EXCEPT_LOOK）

### 2. デザインパターンの適用

#### ファクトリーパターン（Util/UtilFactorys.h:97-146）
- FSMAnimationFactory, FSMCameraFactory, FSMCharacterFactory
- FSMSceneFactory, FSMUIFactory
- ModelFactory, AnimationDataFactory, AttackDataFactory
- 複雑なオブジェクト生成を一箇所に集約

#### ステートマシンパターン（State/FSM.h:23-200）
- FSMBase<T, U>テンプレートによる汎用FSM
- 6種類のFSM（Animation, Camera, Character, DotWeen, Scene, UI）
- 状態遷移ロジックをカプセル化
- 新しいステートを追加する場合、IStateインターフェースを実装するだけでOK

#### シングルトンパターン（Singleton/Master.h:21-43）
- 全マネージャーの静的ポインタを一元管理
- グローバルアクセスポイントを提供
- AllDelete()による一括削除

#### コンポジションパターン（Animation/AnimationBase.h:9-76）
- AnimationBaseがModelsControllerBaseとFSMAnimationを所有
- 機能をモジュール化して組み合わせ

### 3. パフォーマンス最適化

#### 線形リストによるオブジェクト管理（Singleton/ObjectManager.cpp:56-72）
- ベクターよりメモリ効率が良い（再確保なし）
- 追加/削除がO(1)で可能（先頭/末尾操作）
- キャッシュヒット率が高い（連続メモリ）
- タイプ別リストの二重管理（全オブジェクト + タイプ別）

#### 参照カウントによるリソース管理（Container/HandleContainer.h:147-150）
- 同じリソースを複数オブジェクトで共有
- カウントが0になった時点で解放
- リソースの重複読み込みを防止
- ハンドルフラグによる制御（ZERO_LOOK: モデル複製なし、ZERO_EXCEPT_LOOK: 複製）

#### ビット演算によるフラグ管理（Struct/BitFlag.h:64-157）
- 1つの整数で複数のフラグを管理
- メモリ効率が良い
- 演算速度が速い
- 入力フラグのビット管理（FLAG_TYPE::MAX × CONTROLLER_KEY_NUMBER::MAX_CONTROLLER）

#### 非同期処理（Singleton/ThreadManager.h:6-23）
- std::future<void>で非同期タスク管理
- CleanupReadyTasksで完了タスクの削除
- ローディング処理の非同期化

#### 固定フレームレート制御（Singleton/TimeManager.cpp:49-118）
- timeBeginPeriod(1)で1ms精度タイマー
- GetNextUpdateFlag()で固定フレームレート（デフォルト17ms）
- デバッグ時は固定時間、リリース時は実時間

### 4. メモリ管理

#### 参照カウント付きリソース管理（Container/HandleContainer.h:218-237）
- mmHandleCountsで各ハンドルの参照数を管理
- RegisterHandleでカウント増加、DeleteHandleでカウント減少
- カウントが0でリソース解放
- リソース解放の遅延（削除予定ハンドルをvectorで返す）

#### 遅延削除によるメモリ管理（Singleton/ObjectManager.cpp:373-392）
- 削除フラグが立ったオブジェクトを一括削除
- 更新ループ中の削除による不整合を防止
- フレームの終了時にまとめて解放
- シーン切り替え時の削除（DeleteSetSceneで前シーンのオブジェクトに削除フラグ設定）

#### 明示的なライフサイクル管理（Singleton/GameManager.cpp:76-126）
- Initialize/SceneLastInitilize/Finalizeの3段階初期化
- Initialize: 基本的な初期化
- SceneLastInitilize: シーン固有の初期化
- Finalize: 終了処理
- 各マネージャーの明示的な初期化・終了
- 作成順序を制御（依存関係の解決）
- 逆順で終了処理

### 5. デバッグ容易化

#### デバッグログシステム（DebugLogs/DebugLog.h）
- シーン遷移、ハンドル未発見などのログ記録
- _DEBUGマクロで本番ビルド時に削除

#### ビットフラグの境界チェック（Struct/BitFlag.h:66-76, 86-96, 106-116）
- デバッグビルド時のみビット数オーバーチェック
- BIT_FAILURE_FLAGでエラー検出

#### ImGuiデバッグUI（Singleton/ImguiManager）
- デバッグ情報表示
- _DEBUGマクロで本番ビルド時に削除

### 6. 実務的な対応

#### バックグラウンド対応（Singleton/TimeManager.cpp:120-132）
- アプリ非アクティブ時の時間を記録
- 復帰時に経過時間を調整
- 未処理のバックグラウンド時間を経過時間に加算

#### ローディング処理（Singleton/LoadingManager.h:10-42）
- BIT_FLAGでローディング状態管理
- フェード中、シーン切り替え時のローディング
- 非同期スレッドによるローディング

#### フェード遷移（Singleton/SceneManager.cpp:63-67）
- FadeManagerによるフェードアウト/イン
- シーン遷移時のフェード制御

#### ウィンドウプロシージャ（Singleton/GameManager.cpp:238-322）
- フォーカス管理
- アクティブ/非アクティブ時の処理

## 苦労した点

### 1. 複雑な状態管理
- 6種類のFSM連携
- シーン遷移時のオブジェクト削除、初期化、状態リセット
- キャラクターの状態とアニメーションの同期

### 2. リソース管理の複雑さ
- 参照カウントによる共有リソース管理
- ハンドルの複製と参照カウントの整合性
- 非同期ローディング時のリソース解放タイミング
- エフェクトの再生制御（停止/再生/削除）

### 3. 3Dゲームの複雑さ
- 3Dカメラ制御（FSMCameraによる状態管理）
- 3Dサウンドリスナー位置設定
- シャドウマップの実装
- 3Dモデルのアニメーション制御
- 球面当たり判定の実装

### 4. 入力システムの複雑さ
- キーボード、コントローラー（最大4台）、マウスの統合管理
- 押し始め/押している/離したの3状態管理
- ビットフラグによる効率的なフラグ管理
- コントローラーのスティック、トリガーのアナログ値管理

### 5. メモリ管理の難しさ
- 線形リストの追加/削除操作
- 遅延削除による更新ループ中の削除問題回避
- シーン切り替え時のオブジェクト一括削除
- リソースの参照カウント管理

### 6. アニメーションデータのハードコード
- アニメーション時間、パスなどがハードコードされている
- データマネージャーから取得できるようにする必要がある

## 今後の改善点

### 1. アニメーションデータのデータマネージャー対応
- データマネージャーからアニメーションデータを取得できるようにする
- XMLやJSONなどの外部ファイルから読み込む
- 設定ファイルによる柔軟な調整

### 2. 未実装関数の実装
- SettingAnimationAndModelFactory: 全アニメーションとモデル設定を一括で行う関数
- SwapHandle: HandleContainerのハンドル交換関数

### 3. 未完成関数の完成
- VVecToAngle: ベクトルをアングルに変換する関数（Yのみ実装済み）
- VAngleToVec: アングルをベクトルに変換する関数（未実装）

### 4. 各プロパティswitchの中身の簡素化
- 各プロパティswitchの中身を簡単にできるようにする
- マップやテーブルによる簡素化

### 5. 外で固定するフレームの名前取得機能
- 外で固定するフレームの名前取得できるようにする
- 設定ファイルから読み込む

### 6. 変数名の改善
- 変数名をわかりやすい名前に変更する
- 命名規則の統一

### 7. アニメーション終了後の次の行動の追加
- アニメーション終了後に次の行動を追加する
- アニメーション連鎖の実装

### 8. シーン名の仮実装からの改善
- シーン名以外の適切な命名に変更する
- アニメーション種類による分類

## 採用担当者へのアピールポイント

### 優先度1（必須）

1. **高度なC++テンプレートの活用**
   - SFINAEによる型制約
   - enum class対応テンプレートオーバーロード
   - 汎用的なビットフラグ構造体（BIT_FLAG<T>）

2. **デザインパターンの適切な適用**
   - ファクトリーパターン、ステートマシンパターン、シングルトンパターン
   - 6種類のFSMによる複雑な状態管理

3. **パフォーマンス最適化の実績**
   - 線形リスト、参照カウント、ビット演算、非同期スレッド

### 優先度2（強く推奨）

4. **3Dゲーム開発の経験**
   - 3Dカメラ、3Dサウンド、シャドウマップ、球面当たり判定

5. **ゲームループの制御**
   - 固定フレームレート制御、バックグラウンド対応

6. **入力システムの実装**
   - キーボード、コントローラー（最大4台）、マウス統合管理

### 優先度3（推奨）

7. **大規模プロジェクトの管理能力**
   - 200ファイル以上、24のマネージャークラス

8. **メモリ管理の理解**
   - 参照カウント、遅延削除

9. **デバッグ容易化の工夫**
   - デバッグログ、ImGuiデバッグUI
