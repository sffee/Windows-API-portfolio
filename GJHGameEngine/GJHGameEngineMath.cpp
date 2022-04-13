#include "GJHGameEngineMath.h"

const GJHVector GJHVector::ZERO = { 0.0f, 0.0f };
const GJHVector GJHVector::LEFT = { -1.0f, 0.0f };
const GJHVector GJHVector::RIGHT = { 1.0f, 0.0f };
const GJHVector GJHVector::UP = { 0.0f, -1.0f };
const GJHVector GJHVector::DOWN = { 0.0f, 1.0f };

bool (*GJHColCheckFunc::ColCheck2D[(int)COLGEOTYPE::CGT_MAX][(int)COLGEOTYPE::CGT_MAX])(GJHGeometryInfo2D, GJHGeometryInfo2D) = { nullptr };

GJHColCheckFunc::ColCheckFuncStaticInit Inst = GJHColCheckFunc::ColCheckFuncStaticInit();

GJHColCheckFunc::ColCheckFuncStaticInit::ColCheckFuncStaticInit()
{
	ColCheck2D[(int)COLGEOTYPE::CGT_RECT][(int)COLGEOTYPE::CGT_RECT] = &GJHColCheckFunc::RectToRect2D;
	ColCheck2D[(int)COLGEOTYPE::CGT_RECT][(int)COLGEOTYPE::CGT_POINT] = &GJHColCheckFunc::RectToPoint2D;
	ColCheck2D[(int)COLGEOTYPE::CGT_RECT][(int)COLGEOTYPE::CGT_CIRCLE] = &GJHColCheckFunc::RectToCircle2D;
}

GJHColCheckFunc::ColCheckFuncStaticInit::~ColCheckFuncStaticInit()
{

}