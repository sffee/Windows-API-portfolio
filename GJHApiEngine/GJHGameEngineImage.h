#pragma once
#include <Windows.h>
#include <GJHGameEngineMath.h>
#include <GJHString.h>
#include <vector>

class GJHGameEngineImage
{
private:
	HDC m_DC;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	BITMAP m_Info;
	GJHVector m_Size;

public:
	inline GJHVector Size()
	{
		return m_Size;
	}

public:
	inline HDC GetHDC()
	{
		return m_DC;
	}

public:
	operator HDC()
	{
		return m_DC;
	}

public:
	void Create(const GJHVector& _Size);
	void Create(HDC _Dc);
	void Load(const GJHString& _Path);
	void Release();

public:
	void ImageSizeCheck();

public:
	void AlphaCopy(const GJHGameEngineImage& _Other, const GJHVector& _RenderPos, const GJHVector& _RenderSize, const GJHVector& _ImagePos, const GJHVector& _ImageSize, unsigned int _AlphaColor);

	void TransCopy(const GJHGameEngineImage& _Other, const GJHVector& _Pos, const GJHVector& _Size, const GJHVector& _ImagePivot, const GJHVector& _ImageSize, unsigned int _TransColor);

	void BitCopy(const GJHGameEngineImage& _Other, const GJHVector& _Pos, const GJHVector& _Pivot = { 0, 0 });
	void BitCopy(const GJHGameEngineImage& _Other);
	void Clear();

private:
	std::vector<GJHGeometryInfo2D> m_CuttingData;

public:
	inline bool IsCut()
	{
		return m_CuttingData.size() != 0;
	}

	inline size_t CutSize()
	{
		return m_CuttingData.size();
	}

	inline GJHGeometryInfo2D GetCutData(int _Index)
	{
		if (CutSize() <= _Index)
		{
			AssertMsg("if (CutSize() <= _Index)");
		}

		return m_CuttingData[_Index];
	}

public:
	void Cutting(int _X, int _Y, bool _XReverse = false);
	void Cutting(const GJHVector& _Size, bool _XRevers = false);

	void SetImagePixel(int _X, int _Y, int _Color);
	int GetImagePixel(int _X, int _Y);

public:
	GJHGameEngineImage();
	~GJHGameEngineImage();
};

