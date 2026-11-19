#pragma once
#include <istream>
#include <vector>

#include "Vector2.h"

#pragma pack(push, 1)
/*ビットマップヘッダー*/
struct BMPHeader {
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;

	uint32_t biSize;
	int32_t  biWidth;
	int32_t  biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t  biXPelsPerMeter;
	int32_t  biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;

	BMPHeader()
	{
		bfType = 0;
		bfSize = 0;
		bfReserved1 = 0;
		bfReserved2 = 0;
		bfOffBits = 0;

		biSize = 0;
		biWidth = 0;
		biHeight = 0;
		biPlanes = 0;
		biBitCount = 0;
		biCompression = 0;
		biSizeImage = 0;
		biXPelsPerMeter = 0;
		biYPelsPerMeter = 0;
		biClrUsed = 0;
		biClrImportant = 0;
	}
};
#pragma pack(pop)

/*1ピクセル色情報*/
struct OnePixelColorData
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char alpha;

	operator char* ()
	{
		return (char*)(&blue);
	}
};

/*ビットマップデータ*/
struct BitMapData
{
	// ビットマップヘッダーデータ
	BMPHeader bmpHeaderData;

	// 色データ
	std::vector<OnePixelColorData> onePixelData;

	// X座標
	int xPos;
	// X座標
	int yPos;

	// 最大yポジション
	int maxYPos;

	// 最大xポジション
	int maxXPos;

	BitMapData()
	{
		bmpHeaderData = BMPHeader();
		onePixelData.clear();

		xPos = 0;
		yPos = 0;

		maxYPos = 0;
		maxXPos = 0;
	}

	OnePixelColorData& operator [](int number)
	{
		return onePixelData[number];
	}

	OnePixelColorData& GetMapPixel(bool xMoveFlag)
	{
		if (xMoveFlag)
		{
			xPos += 1;
			if (xPos >= bmpHeaderData.biWidth)
			{
				xPos = 0;
			}
		}
		else
		{
			yPos += 1;
			if (yPos >= bmpHeaderData.biHeight)
			{
				yPos = 0;
			}
		}
		return onePixelData[(yPos * maxYPos) + xPos];
	}

	OnePixelColorData& GetMapPixel(int x_Pos, int y_Pos)
	{
		if (y_Pos < 0)
		{
			y_Pos = ((y_Pos % bmpHeaderData.biHeight) + bmpHeaderData.biHeight) % bmpHeaderData.biHeight;
		}
		else
		{
			y_Pos %= bmpHeaderData.biHeight;
		}

		if (x_Pos < 0)
		{
			x_Pos = ((x_Pos % bmpHeaderData.biWidth) + bmpHeaderData.biWidth) % bmpHeaderData.biWidth;
		}
		else
		{
			x_Pos %= bmpHeaderData.biWidth;
		}

		return onePixelData[(y_Pos * maxYPos) + x_Pos];
	}

	OnePixelColorData& GetMapPixel(Vector2_Int pos)
	{
		return GetMapPixel(pos.x, pos.y);
	}
};