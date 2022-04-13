#include "GJHGameEngineImage.h"
#include <GJHGameEngineDebug.h>
#include "GJHGameEngineWindow.h"

#pragma comment(lib, "msimg32.lib")

GJHGameEngineImage::GJHGameEngineImage() :
	m_DC(0),
	m_BitMap(0),
	m_OldBitMap(0),
	m_Info(),
	m_Size(0, 0)
{

}

GJHGameEngineImage::~GJHGameEngineImage()
{

}

void GJHGameEngineImage::Create(HDC _Dc)
{
	if (_Dc == 0)
	{
		AssertMsg("if (0 == _Dc)");
	}

	m_DC = _Dc;

	ImageSizeCheck();
}

void GJHGameEngineImage::Release()
{
	if (m_BitMap != 0)
	{
		DeleteObject(m_BitMap);
	}

	if (m_OldBitMap != 0)
	{
		DeleteObject(m_OldBitMap);
	}

	if (m_DC != 0)
	{
		DeleteDC(m_DC);
	}
}

void GJHGameEngineImage::Create(const GJHVector& _Size)
{
	if (_Size.IsZero())
	{
		AssertMsg("if (_Size.IsZero())");
	}

	m_BitMap = CreateCompatibleBitmap(GJHGameEngineWindow::MainWindow()->GetBackGround().GetHDC()
		, _Size.ix(), _Size.iy());

	m_DC = CreateCompatibleDC(nullptr);

	if (m_DC == nullptr)
	{
		AssertMsg("if (m_DC == nullptr");
	}

	m_OldBitMap = (HBITMAP)SelectObject(m_DC, m_BitMap);

	ImageSizeCheck();
}

void GJHGameEngineImage::Load(const GJHString& _Path)
{
	m_BitMap = (HBITMAP)LoadImageA(nullptr,
		_Path,
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE);

	if (m_BitMap == nullptr)
	{
		AssertMsg(_Path + "Load Error");
	}

	m_DC = CreateCompatibleDC(nullptr);
	m_OldBitMap = (HBITMAP)SelectObject(m_DC, m_BitMap);
	ImageSizeCheck();
}

void GJHGameEngineImage::ImageSizeCheck()
{
	HBITMAP CheckBitMap = (HBITMAP)GetCurrentObject(m_DC, OBJ_BITMAP);
	GetObject(CheckBitMap, sizeof(BITMAP), &m_Info);

	m_Size.x = (float)m_Info.bmWidth;
	m_Size.y = (float)m_Info.bmHeight;
}

void GJHGameEngineImage::AlphaCopy(const GJHGameEngineImage& _Other, const GJHVector& _RenderPos, const GJHVector& _RenderSize, const GJHVector& _ImagePos, const GJHVector& _ImageSize, unsigned int _AlphaColor)
{
	BLENDFUNCTION BlendState = BLENDFUNCTION();
	BlendState.AlphaFormat = AC_SRC_OVER;
	BlendState.BlendFlags = 0;
	BlendState.AlphaFormat = AC_SRC_ALPHA;
	BlendState.SourceConstantAlpha = _AlphaColor;

	AlphaBlend(m_DC,
		_RenderPos.ix(),
		_RenderPos.iy(),
		_RenderSize.ix(),
		_RenderSize.iy(),
		_Other.m_DC,
		_ImagePos.ix(),
		_ImagePos.iy(),
		_ImageSize.ix(),
		_ImageSize.iy(),
		BlendState);
}

void GJHGameEngineImage::TransCopy(const GJHGameEngineImage& _Other, const GJHVector& _Pos, const GJHVector& _Size, const GJHVector& _ImagePivot, const GJHVector& _ImageSize, unsigned int _TransColor)
{
	TransparentBlt(m_DC,
		_Pos.ix(),
		_Pos.iy(),
		_Size.ix(),
		_Size.iy(),
		_Other.m_DC,
		_ImagePivot.ix(),
		_ImagePivot.iy(),
		_ImageSize.ix(),
		_ImageSize.iy(),
		_TransColor);
}

void GJHGameEngineImage::BitCopy(const GJHGameEngineImage& _Other, const GJHVector& _Pos, const GJHVector& _Pivot)
{
	BitBlt(m_DC,
		_Pos.ix(),
		_Pos.iy(),
		m_Size.ix(),
		m_Size.iy(),
		_Other.m_DC,
		_Pivot.ix(),
		_Pivot.iy(),
		SRCCOPY);
}

void GJHGameEngineImage::BitCopy(const GJHGameEngineImage& _Other)
{
	BitBlt(m_DC,
		0,
		0,
		m_Size.ix(),
		m_Size.iy(),
		_Other.m_DC,
		0,
		0,
		SRCCOPY);
}

void GJHGameEngineImage::Clear()
{
	Rectangle(m_DC,
		0,
		0,
		m_Size.ix(),
		m_Size.iy()
		);
}

void GJHGameEngineImage::Cutting(const GJHVector& _Size, bool _XReverse)
{
	int X = Size().ix() / _Size.ix();
	int Y = Size().iy() / _Size.iy();

	Cutting(X, Y, _XReverse);
}

void GJHGameEngineImage::Cutting(int _X, int _Y, bool _XReverse)
{
	float SizeX = Size().x / _X;
	float SizeY = Size().y / _Y;

	float PlusX = SizeX;

	float StartX = 0.0f;
	float Dir = 1.0f;

	GJHVector Start = { 0, 0 };

	if (_XReverse == true)
	{
		StartX = (_X - 1) * SizeX;
		Start.x = StartX;
		PlusX = -PlusX;
	}

	for (size_t y = 0; y < _Y; y++)
	{
		for (size_t x = 0; x < _X; x++)
		{
			GJHGeometryInfo2D Info;
			Info.Pos = Start;
			Info.Size = { SizeX, SizeY };
			m_CuttingData.push_back(Info);
			Start.x += PlusX;
		}

		Start.x = StartX;
		Start.y += SizeY;
	}
}

void GJHGameEngineImage::SetImagePixel(int _X, int _Y, int _Color)
{
	if (Size().ix() < _X)
	{
		AssertMsg("if (Size().ix() < _X)");
	}

	if (Size().iy() < _Y)
	{
		AssertMsg("if (Size().iy() < _Y)");
	}

	SetPixel(m_DC, _X, _Y, _Color);
}

int GJHGameEngineImage::GetImagePixel(int _X, int _Y)
{
	if (Size().ix() < _X)
	{
		AssertMsg("if (Size().ix() < _X)");
	}

	if (Size().iy() < _Y)
	{
		AssertMsg("if (Size().iy() < _Y)");
	}

	return GetPixel(m_DC, _X, _Y);
}