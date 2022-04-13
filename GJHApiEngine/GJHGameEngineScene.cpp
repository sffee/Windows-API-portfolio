#include "GJHGameEngineScene.h"
#include "GJHGameEngineActor.h"
#include "GJHRenderer.h"
#include "GJHCollision.h"
#include <EngineDefine.h>

GJHGameEngineScene::GJHGameEngineScene() : m_Actors(), m_IsDebugRender(false)
{

}

GJHGameEngineScene::~GJHGameEngineScene()
{
	std::list<GJHGameEngineActor*>::iterator Start = m_Actors.begin();
	std::list<GJHGameEngineActor*>::iterator End = m_Actors.end();

	for (; Start != End; ++Start)
	{
		if ((*Start) != nullptr)
		{
			delete (*Start);
			(*Start) = nullptr;
		}
	}
}


void GJHGameEngineScene::Loading()
{

}

void GJHGameEngineScene::Progress()
{
	SceneUpdate();

	{
		{
			std::map<int, std::list<GJHRenderer*>>::iterator StartRender = m_AllRenderer.begin();
			std::map<int, std::list<GJHRenderer*>>::iterator EndRender = m_AllRenderer.end();

			for (; StartRender != EndRender; ++StartRender)
			{
				std::list<GJHRenderer*>::iterator Start = StartRender->second.begin();
				std::list<GJHRenderer*>::iterator End = StartRender->second.end();

				for (; Start != End; ++Start)
				{
					if ((*Start)->GetActor()->IsOn() == false ||
						(*Start)->IsOn() == false)
					{
						continue;
					}

					(*Start)->CalcRender();
				}
			}
		}
	}

	{
		std::list<GJHGameEngineActor*>::iterator Start = m_Actors.begin();
		std::list<GJHGameEngineActor*>::iterator End = m_Actors.end();

		for (; Start != End; ++Start)
		{
			if ((*Start) != nullptr)
			{
				if ((*Start)->IsOn() == false)
				{
					continue;
				}

				(*Start)->Update();
			}
		}
	}

	{
		{
			std::map<int, std::list<GJHRenderer*>>::iterator StartRender = m_AllRenderer.begin();
			std::map<int, std::list<GJHRenderer*>>::iterator EndRender = m_AllRenderer.end();

			for (; StartRender != EndRender; ++StartRender)
			{
				std::list<GJHRenderer*>::iterator Start = StartRender->second.begin();
				std::list<GJHRenderer*>::iterator End = StartRender->second.end();

				for (; Start != End; ++Start)
				{
					if ((*Start)->GetActor()->IsOn() == false ||
						(*Start)->IsOn() == false)
					{
						continue;
					}

					(*Start)->Render();
				}
			}
		}

		{
			if (m_IsDebugRender == true)
			{
				std::map<int, std::list<GJHCollision*>>::iterator StartCollision = m_AllCollision.begin();
				std::map<int, std::list<GJHCollision*>>::iterator EndCollision = m_AllCollision.end();

				for (; StartCollision != EndCollision; ++StartCollision)
				{
					std::list<GJHCollision*>::iterator Start = StartCollision->second.begin();
					std::list<GJHCollision*>::iterator End = StartCollision->second.end();

					for (; Start != End; ++Start)
					{
						if ((*Start)->GetActor()->IsOn() == false ||
							(*Start)->IsOn() == false)
						{
							continue;
						}

						(*Start)->DebugRender();
					}
				}

				DebugRender();
			}
		}
	}

	{
		{
			std::map<int, std::list<GJHCollision*>>::iterator StartCollision = m_AllCollision.begin();
			std::map<int, std::list<GJHCollision*>>::iterator EndCollision = m_AllCollision.end();

			for (; StartCollision != EndCollision; ++StartCollision)
			{
				std::list<GJHCollision*>::iterator Start = StartCollision->second.begin();
				std::list<GJHCollision*>::iterator End = StartCollision->second.end();

				for (; Start != End; ++Start)
				{
					(*Start)->CalPos();
				}
			}
		}

		std::list<ColLink>::iterator StartLinkData = m_LinkData.begin();
		std::list<ColLink>::iterator EndLinkData = m_LinkData.end();

		for (; StartLinkData != EndLinkData; ++StartLinkData)
		{
			std::map<int, std::list<GJHCollision*>>::iterator LeftFind = m_AllCollision.find((*StartLinkData).Left);
			std::map<int, std::list<GJHCollision*>>::iterator RightFind = m_AllCollision.find((*StartLinkData).Right);

			if (LeftFind == m_AllCollision.end()
				|| RightFind == m_AllCollision.end())
			{
				continue;
			}

			std::list<GJHCollision*>& LeftList = LeftFind->second;
			std::list<GJHCollision*>& RightList = RightFind->second;

			if (LeftList.size() == 0)
			{
				continue;
			}

			if (RightList.size() == 0)
			{
				continue;
			}

			if ((*StartLinkData).Left == (*StartLinkData).Right)
			{
				ColThisGroupCheck(LeftList);
			}
			else
			{
				ColOtherGroupCheck(LeftList, RightList);
			}
		}
	}

	{
		if (m_IsDebugRender == true)
		{
			std::list<GJHGameEngineActor*>::iterator Start = m_Actors.begin();
			std::list<GJHGameEngineActor*>::iterator End = m_Actors.end();

			for (; Start != End; ++Start)
			{
				if ((*Start) != nullptr)
				{
					if ((*Start)->IsOn() == false)
					{
						continue;
					}

					(*Start)->DebugRender();
				}
			}
		}
	}

	Release();
}

void GJHGameEngineScene::ColThisGroupCheck(std::list<GJHCollision*>& _This)
{
	std::list<GJHCollision*>::iterator ThisStart = _This.begin();
	std::list<GJHCollision*>::iterator ThisEnd = _This.end();

	for (; ThisStart != ThisEnd; ++ThisStart)
	{
		if ((*ThisStart)->GetActor()->IsOn() == false ||
			(*ThisStart)->IsOn() == false)
		{
			continue;
		}

		if ((*ThisStart)->GetName() == "TombStone")
		{
			int a = 0;
		}

		std::list<GJHCollision*>::iterator CheckStart = ThisStart;
		++CheckStart;

		for (; CheckStart != ThisEnd; ++CheckStart)
		{
			if ((*CheckStart)->GetActor()->IsOn() == false ||
				(*CheckStart)->IsOn() == false)
			{
				continue;
			}

			(*ThisStart)->CollisionCheck((*CheckStart));
		}
	}
}

void GJHGameEngineScene::ColOtherGroupCheck(std::list<GJHCollision*>& _Left, std::list<GJHCollision*>& _Right)
{
	std::list<GJHCollision*>::iterator LeftStart = _Left.begin();
	std::list<GJHCollision*>::iterator LeftEnd = _Left.end();

	for (; LeftStart != LeftEnd; ++LeftStart)
	{
		if ((*LeftStart)->GetActor()->IsOn() == false ||
			(*LeftStart)->IsOn() == false)
		{
			continue;
		}

		std::list<GJHCollision*>::iterator RightStart = _Right.begin();
		std::list<GJHCollision*>::iterator RightEnd = _Right.end();

		for (; RightStart != RightEnd; ++RightStart)
		{
			if ((*RightStart)->GetActor()->IsOn() == false ||
				(*RightStart)->IsOn() == false)
			{
				continue;
			}

			(*LeftStart)->CollisionCheck((*RightStart));
		}
	}
}

void GJHGameEngineScene::PushRender(GJHRenderer* _Render)
{
	if (_Render == nullptr)
	{
		AssertMsg("if (_Render == nullptr)");
	}

	std::map<int, std::list<GJHRenderer*>>::iterator Iter = m_AllRenderer.find(_Render->GetOrder());

	_Render->m_Scene = this;

	if (Iter == m_AllRenderer.end())
	{
		m_AllRenderer.insert(std::map<int, std::list<GJHRenderer*>>::value_type(_Render->GetOrder(), std::list<GJHRenderer*>()));

		Iter = m_AllRenderer.find(_Render->GetOrder());
	}

	Iter->second.push_back(_Render);
}

void GJHGameEngineScene::PushCollision(GJHCollision* _Collision)
{
	if (_Collision == nullptr)
	{
		AssertMsg("if (_Collsion == nullptr)");
	}

	std::map<int, std::list<GJHCollision*>>::iterator Iter = m_AllCollision.find(_Collision->GetOrder());

	_Collision->m_Scene = this;

	if (Iter == m_AllCollision.end())
	{
		m_AllCollision.insert(std::map<int, std::list<GJHCollision*>>::value_type(_Collision->GetOrder(), std::list<GJHCollision*>()));

		Iter = m_AllCollision.find(_Collision->GetOrder());
	}

	Iter->second.push_back(_Collision);
}

void GJHGameEngineScene::Release()
{
	{
		std::map<int, std::list<GJHRenderer*>>::iterator StartRender = m_AllRenderer.begin();
		std::map<int, std::list<GJHRenderer*>>::iterator EndRender = m_AllRenderer.end();

		for (; StartRender != EndRender; ++StartRender)
		{
			std::list<GJHRenderer*>::iterator Start = StartRender->second.begin();
			std::list<GJHRenderer*>::iterator End = StartRender->second.end();

			for (; Start != End; )
			{
				if ((*Start)->GetActor()->IsDeath() == true
					|| (*Start)->IsDeath() == true)
				{
					Start = StartRender->second.erase(Start);
				}
				else
				{
					++Start;
				}
			}
		}
	}

	{
		std::map<int, std::list<GJHCollision*>>::iterator StartCollision = m_AllCollision.begin();
		std::map<int, std::list<GJHCollision*>>::iterator EndCollision = m_AllCollision.end();

		for (; StartCollision != EndCollision; ++StartCollision)
		{
			std::list<GJHCollision*>::iterator Start = StartCollision->second.begin();
			std::list<GJHCollision*>::iterator End = StartCollision->second.end();

			for (; Start != End; )
			{
				if ((*Start)->GetActor()->IsDeath() == true
					|| (*Start)->IsDeath() == true)
				{
					Start = StartCollision->second.erase(Start);
				}
				else
				{
					++Start;
				}
			}
		}
	}

	{
		std::list<GJHGameEngineActor*>::iterator Start = m_Actors.begin();
		std::list<GJHGameEngineActor*>::iterator End = m_Actors.end();

		for (; Start != End;)
		{
			(*Start)->Release();

			if ((*Start)->IsDeath())
			{
				(*Start)->DeathFunc();

				if ((*Start) != nullptr)
				{
					SAFE_DELETE(*Start);
				}

				Start = m_Actors.erase(Start);
			}
			else
			{
				++Start;
			}
		}
	}
}

void GJHGameEngineScene::SceneChangeStart()
{
	std::list<GJHGameEngineActor*>::iterator Start = m_Actors.begin();
	std::list<GJHGameEngineActor*>::iterator End = m_Actors.end();

	for (; Start != End; ++Start)
	{
		if ((*Start) != nullptr)
		{
			if ((*Start)->IsOn() == false)
			{
				continue;
			}

			(*Start)->SceneStart();
		}
	}
}