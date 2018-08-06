/// \file       CTransform.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_TRANSFORM_HPP__
#define OOM_ENGINE_C_TRANSFORM_HPP__

#include <vector>

#include "Render/Config.hpp"
#include "Composite/IComponent.hpp"

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace Oom
{

class CTransform : public IComponent
{
public:

    CTransform();

public:

    // Properties
    const glm::vec3&    GetUp                 () const;
    const glm::vec3&    GetRight              () const;
    const glm::vec3&    GetForward            () const;
	const glm::vec3&    GetTarget             () const;
    const glm::vec3&    GetPosition           () const;
    const glm::vec3&    GetScale              () const;
    const glm::vec3&    GetOrientation        () const;
          glm::mat4     GetLocalToWorldMatrix () const;

    void SetScale       (const glm::vec3& scale);
    void SetScale       (float x, float y, float z);
    void SetPosition    (const glm::vec3& position);
    void SetPosition    (float x, float y, float z);
    void SetOrientation (const glm::vec3& orientation);
    void SetOrientation (float x, float y, float z);

public:

    // Methods
    const CTransform*   Find            (const CString& name);
	void				LookAt			(float x, float y, float z);
	void				LookAt			(const glm::vec3& target);
    void                LookAt          (const CTransform& target);
    void                Rotate          (float x, float y, float z);
    void                Rotate          (const glm::vec3& rotation);
    void                RotateAround    (const glm::vec3& point, const glm::vec3& axis, float angle);
    void                Translate       (float x, float y, float z);
    void                Translate       (const glm::vec3& translation);

protected:

    void _Register() final;
    void _Destroy () final;

private:

	void				RotateTarget    (const glm::vec3& rotation);
	void				TranslateTarget	(const glm::vec3& translation);

private:

    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_orientation;

    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_forward;
	glm::vec3 m_target;

private:

    friend class CEngine;
    friend class CGameObject;

    CGameObject* mp_game_object = nullptr;
};

}

#endif // !OOM_ENGINE_C_TRANSFORM_HPP__