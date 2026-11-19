#include <istream>
#include <fstream>

#include "FileLoadingData.h"

#include "Master.h"

#include "EndManager.h"
#include "UtilFileLoading.h"


// ビットマップファイル読み込み
BitMapData UtilFileLoading::LoadingBitMapFile(std::string fileName)
{
	BitMapData bitMapData = BitMapData();

	std::ifstream file(fileName, std::ios::binary);

	if (!file) {
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::FILE_FLAG);
		return bitMapData;
	}

	file.read(reinterpret_cast<char*>(&bitMapData.bmpHeaderData), sizeof(bitMapData.bmpHeaderData));

	if (bitMapData.bmpHeaderData.bfType != 0x4D42) {
		return bitMapData;
	}

	bitMapData.maxYPos = bitMapData.bmpHeaderData.biHeight;
    bitMapData.maxXPos = bitMapData.bmpHeaderData.biWidth;
	bitMapData.onePixelData.resize(bitMapData.bmpHeaderData.biHeight * bitMapData.bmpHeaderData.biWidth);

	file.seekg(bitMapData.bmpHeaderData.bfOffBits, std::ios::beg);

	file.read(bitMapData[0], bitMapData.onePixelData.size() * 4);
	file.close();

	return bitMapData;
}