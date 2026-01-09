#include "DxLib.h"

#include "AnimationEnum.h"
#include "AnimationData.h"

#include "ModelBase.h"
#include "ModelsControllerBase.h"
#include "StateBase.h"
#include "StateModelsController.h"

StateMVOneModel::StateMVOneModel()
: IStateModelsController()
{
    mStateNumber = ANIMATION_MODEL_TYPE::MV1_MODEL;
}

// この状態に入った時の処理
void StateMVOneModel::OnEnter(ModelsControllerBase* modelsController, AnimationData& animationDatas, ModelBase* model)
{
}

// この状態を出る時の処理
void StateMVOneModel::OnExit(ModelsControllerBase* modelsController, AnimationData& animationDatas, ModelBase* model)
{
}

// 更新
void StateMVOneModel::Update(ModelsControllerBase* modelsController, AnimationData& animationDatas, ModelBase* model)
{
    // アニメーション変更
    ChangeAnimationModel();

    // アニメーション更新
    UpdateAnimation();
}

// アニメーションモデル切り替え
void StateMVOneModel::ChangeAnimationModel()
{
    
}

// アニメーション更新
void StateMVOneModel::UpdateAnimation()
{
    
}

//     if (index == -1) {
//         return;
//     }
//     if (mnModelHandle != -1) {
//         if (index != mnAnimNumber1)
//         {
//             // 前のアニメーションナンバーを保持
//             mnAnimNumber2 = mnAnimNumber1;
//             // 現在のアニメーションナンバーを保持
//             mnAnimNumber1 = index;

//             // 再生中のアニメーション2が有効状態だったらデタッチしておく
//             if (mnAnimation2 != (-1))
//             {

//                 MV1DetachAnim(mnModelHandle, mnAnimation2);
//                 mnAnimation2 = -1;
//             }

//             // 今まで再生されていた情報を2の方に保持しておく
//             mnAnimation2 = mnAnimation1;
//             mfAnimCount2 = mfAnimCount1;
//             mbLoopFlag2 = mbLoopFlag1;

//             // 新しいアニメーションアタッチして、アタッチ番号を保持しておく
//             if (!mbNotOneAnimFlag) {
//                 mnAnimation1 = MV1AttachAnim(mnModelHandle, index);
//             }
//             else {
//                 mnAnimation1 = MV1AttachAnim(mnModelHandle, 0, mnAnimHandle[mnAnimNumber1], FALSE);/*フレーム名が違くてもアタッチするようにしてる*/
//             }
//             mfAnimCount1 = 0.0f;

//             // 新しいアニメーションがループするかどうか
//             mbLoopFlag1 = LoopCheck(index);

//             // ブレンド率の初期値を設定
//             // note: アニメーション2が有効でない場合はブレンドさせないので1.0にしておく  
//             mfAnimBlendRate = (mnAnimation2 == -1 ? 1.0f : 0.0f);
//         }
//     }


//     if (mnModelHandle != -1) {

//         // ブレンド率を加算していく
//         if (mfAnimBlendRate < 1.0f)
//         {
//             mfAnimBlendRate += CHARA_ANIM_BLEND_SPEED;

//             if (mfAnimBlendRate > 1.0f)
//             {
//                 mfAnimBlendRate = 1.0f;
//             }
//         }
//         float fAnimTotalTime;

//         // アニメーション1の処理
//         if (mnAnimation1 != -1)
//         {
//             // 総再生時間を取得
//             fAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnAnimation1);
            
//             // 再生時間を進める
//             mfAnimCount1 += CHARA_PLAY_ANIM_SPEED;

//             // ループさせる
//             if (mfAnimCount1 >= fAnimTotalTime && mbLoopFlag1)
//             {
//                 ///
//                 mfAnimCount1 = fmodf(mfAnimCount1, fAnimTotalTime);
//                 ///
//             }
//             else if (mfAnimCount1 >= fAnimTotalTime && !mbLoopFlag1)
//             {
//                 mfAnimCount1 = fAnimTotalTime;
//             }

//             // モデルに反映
//             MV1SetAttachAnimTime(mnModelHandle, mnAnimation1, mfAnimCount1);

//             // アニメーション反映率を設定
//             MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimation1, mfAnimBlendRate);
//         }

        
//         // アニメーション2の処理
//         if (mnAnimation2 != -1)
//         {
//             // 総再生時間を取得
//             fAnimTotalTime = MV1GetAnimTotalTime(mnModelHandle, mnAnimation2);

//             // 再生時間を進める
//             mfAnimCount2 += CHARA_PLAY_ANIM_SPEED;

//             // ループさせる
//             if (mfAnimCount2 >= fAnimTotalTime && mbLoopFlag2)
//             {
//                 ///
//                 mfAnimCount2 = fmodf(mfAnimCount2, fAnimTotalTime);
//                 ///
//             }
//             else if (mfAnimCount2 >= fAnimTotalTime && !mbLoopFlag2)
//             {
//                 mfAnimCount2 -= CHARA_PLAY_ANIM_SPEED;
//             }


//             // モデルに反映
//             MV1SetAttachAnimTime(mnModelHandle, mnAnimation2, mfAnimCount2);

//             // アニメーション反映率を設定
//             MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimation2, 1.0f - mfAnimBlendRate);
//         }
//     }
// }