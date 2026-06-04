# 技術資料（TECHNICAL.md）

## システム概要

本プロジェクトはDxLibを使用して開発した3Dアクションゲームです。

単純なゲーム完成だけでなく、拡張性・保守性・再利用性を意識したアーキテクチャ設計を目的として開発しました。

ゲーム内機能はManagerクラスへ責務ごとに分離し、状態管理にはFSM（Finite State Machine）を採用しています。

---

# アーキテクチャ

## 全体構成

ゲーム全体はGameManagerを中心として構成されています。

```text
Main
 ↓
GameManager
 ↓
 ├ AttackManager
 ├ CameraManager
 ├ CollisionManager
 ├ DotWeenManager
 ├ MapManager
 ├ ObjectManager
 ├ SceneManager
 └ TargetManager

Master
 ↓
 ├ ResourceManager
 ├ TimeManager
 ├ DrawManager
 ├ SoundManager
 ├ LoadingManager
 ├ ThreadManager
 └ KeyState
```

各Managerは単一責任を持つよう設計し、機能の独立性を高めています。

---

# ゲームループ

ゲームループは固定フレームレート制御を採用しています。

```cpp
while (!EndFlag())
{
    if (TimeManager->GetNextUpdateFlag())
    {
        GameManager->Update();
        GameManager->DeleteAllIfNeeded();
        GameManager->Draw();
    }
}
```

60FPSを目標として動作し、処理負荷によるゲーム速度の変化を防止しています。

---

# 初期化フロー

起動時は依存関係を考慮し以下の順序で初期化します。

```text
DxLib_Init
 ↓
Master生成
 ↓
Manager生成
 ↓
Resource初期化
 ↓
Scene初期化
 ↓
ゲーム開始
```

終了時は逆順で解放します。

---

# FSM設計

## 採用理由

ゲーム開発初期ではswitch文による状態管理を行っていました。

しかし状態数増加に伴い可読性が低下したためFSMへ移行しました。

---

## FSM一覧

### FSMScene

シーン遷移管理

```text
Title
 ↓
Town
 ↓
Dungeon
 ↓
Battle
 ↓
Result
 ↓
GameClear
```

---

### FSMCharacter

キャラクター状態管理

```text
Idle
Move
Attack
Damage
Dead
```

---

### FSMCamera

カメラ状態管理

```text
TitleCamera
GameCamera
ResultCamera
```

---

### FSMAnimation

アニメーション状態管理

プレイヤーや敵のアニメーション遷移を担当します。

---

### FSMUI

UI状態管理

タイトル画面やリザルト画面ごとのUIを管理します。

---

### FSMDotWeen

補間アニメーション管理

UI演出やカメラ演出に利用しています。

---

# ObjectManager

## 管理対象

```text
Character
Building
Attack
UI
```

---

## オブジェクトライフサイクル

```text
生成
 ↓
Initialize
 ↓
Update
 ↓
LastUpdate
 ↓
Draw
 ↓
DeleteFlag
 ↓
DeleteAllIfNeeded
 ↓
削除
```

---

## 遅延削除

更新中にdeleteを行うとコンテナ破壊が発生する可能性があります。

そのため削除要求時は削除フラグのみ設定し、フレーム終了時に一括削除を行っています。

```cpp
object->SetDeleteFlag(true);
```

```cpp
DeleteAllIfNeeded();
```

---

# ResourceManager

## 管理対象

* モデル
* 画像
* サウンド
* エフェクト
* 動画

---

## 参照カウント方式

同じリソースを複数回ロードしないよう参照カウント方式を採用しています。

```text
Player
 ↓

player.mv1

 ↓

Enemy
```

両方が同じモデルを共有できます。

---

## 読み込み

```text
Load
 ↓
登録
 ↓
Count++
```

---

## 解放

```text
Delete
 ↓
Count--
 ↓
0
 ↓
解放
```

---

## 効果

* メモリ削減
* ロード時間短縮
* リソース共有

---

# KeyState

## 対応デバイス

### キーボード

全キー入力管理

### コントローラー

最大4台対応

管理内容

* ボタン
* スティック
* トリガー

### マウス

* 左クリック
* 右クリック
* 中央クリック
* ホイール
* 座標

---

## 入力状態

```text
NOW
DOWN
UP
```

---

## 更新処理

```text
前フレーム取得
 ↓
現在フレーム取得
 ↓
比較
 ↓
NOW生成
 ↓
DOWN生成
 ↓
UP生成
```

---

# CollisionManager

## 管理方法

全オブジェクトの衝突判定を管理します。

---

## 判定方式

球体判定を採用しています。

```cpp
distance <= radiusA + radiusB
```

---

## 採用理由

* 計算量が少ない
* 実装が容易
* 3Dアクションとの相性が良い

---

# DrawManager

## 目的

描画処理の責務分離

---

## フロー

```text
Object
 ↓
DrawManagerへ登録
 ↓
DrawManagerが描画
```

ゲームオブジェクト側は描画要求のみ行います。

---

# TimeManager

## 機能

* 固定FPS制御
* 経過時間計測
* シーン切り替え補正
* 非アクティブ対応

---

## フレーム制御

```cpp
timeBeginPeriod(1);
```

を利用して高精度タイマーを実現しています。

---

# ThreadManager

## 利用目的

ローディング処理の非同期化

---

## 使用技術

```cpp
std::future<void>
```

---

## 処理フロー

```text
ロード要求
 ↓
Task生成
 ↓
future管理
 ↓
完了確認
 ↓
削除
```

---

# パフォーマンス最適化

## ビット演算

入力状態をビットで管理しています。

メリット

* 高速
* 省メモリ

---

## リソース共有

同一モデルの重複ロード防止

---

## 非同期ロード

ロード中のフレーム停止軽減

---

## 遅延削除

更新中削除によるクラッシュ防止

---

# 開発中に発生した問題

## 問題1

シーン切り替え時にクラッシュ

### 原因

更新中にオブジェクトを削除していた

### 解決

遅延削除を導入

---

## 問題2

ロード時間増加

### 原因

同一リソースの重複ロード

### 解決

参照カウント方式を導入

---

## 問題3

状態管理の複雑化

### 原因

switch文の肥大化

### 解決

FSMへ移行

---

# 学んだこと

本プロジェクトを通して以下を学びました。

* ゲームループ設計
* FSM設計
* リソース管理
* メモリ管理
* 非同期処理
* C++テンプレート
* 3Dゲームアーキテクチャ設計
* 入力システム設計
* 大規模プロジェクト管理

```
```
