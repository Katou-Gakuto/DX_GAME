#include "Master.h"

#include "GameManager.h"
#include "StateEnemy.h"
#include "TargetManager.h"

/*------------------*/
/*     y‹¤’Êz     */
/*------------------*/

/*----------------------*/
/*yƒGƒlƒ~[‹¤’Êˆ——pz*/
/*----------------------*/
EnemyProcess::EnemyProcess()
: mpTargetManager(Master::mpGameManager->GetTargetManager())
{
}