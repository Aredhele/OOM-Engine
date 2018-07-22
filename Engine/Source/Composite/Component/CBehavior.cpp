/// \file       CBehavior.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite/Component
/// \author     Vincent STEHLY--CALISTO

#include "Composite/Component/CBehavior.hpp"

namespace Oom
{

void CBehavior::Awake()
{ /* None */ }

void CBehavior::Start()
{ /* None */ }

void CBehavior::Update()
{ /* None */ }

void CBehavior::OnDestroy()
{ /* None */ }

void CBehavior::OnEnable()
{ /* None */ }

void CBehavior::OnDisable()
{ /* None */ }

void CBehavior::OnDrawGizmos()
{ /* None */ }

void CBehavior::__Awake()
{
    Awake();
}

void CBehavior::__Start()
{
    Start();
    m_first_update = false;
}

void CBehavior::__Update()
{
    Update();
}

void CBehavior::__OnDestroy()
{
    OnDestroy();
}

void CBehavior::__OnEnable()
{
    OnEnable();
}

void CBehavior::__OnDisable()
{
    OnDisable();
}

void CBehavior::__OnDrawGizmos()
{
    OnDrawGizmos();
}

}