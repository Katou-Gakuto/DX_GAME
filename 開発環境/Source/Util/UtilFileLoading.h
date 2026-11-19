#pragma once
#include <string>

#include "FileLoadingData.h"

namespace UtilFileLoading
{
    /// <summary>ビットマップファイル読み込み</summary>
    BitMapData LoadingBitMapFile(std::string fileName);
}