#include "engineph.h"
#include "FirstPersonCamera.h"
#include "Kuro/Core/Input.h"

namespace Kuro
{
	FirstPersonCamera::FirstPersonCamera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up)
		: m_CameraPosition(pos), m_CameraOrientation(glm::lookAt(pos, target, up)), m_Up(up)
	{
		KURO_CORE_TRACE("FirstPersonCamera::FirstPersonCamera");

	}

	void FirstPersonCamera::OnUpdate(Timestep ts)
	{
		if (Input::IsMouseButtonPressed(0))
		{
			const glm::vec2 delta = m_MouseState.Pos - m_MousePos;
			const glm::quat deltaQuat = glm::quat(glm::vec3(-m_MouseSpeed * delta.y, m_MouseSpeed * delta.x, 0.0f));
			m_CameraOrientation = deltaQuat * m_CameraOrientation;
			m_CameraOrientation = glm::normalize(m_CameraOrientation);
			SetupVector(m_Up);
		}
		m_MousePos = m_MouseState.Pos;

		const glm::mat4 v = glm::mat4(m_CameraOrientation);

		const glm::vec3 forward = -glm::vec3(v[0][2], v[1][2], v[2][2]);
		const glm::vec3 right = glm::vec3(v[0][0], v[1][2], v[2][0]);
		const glm::vec3 up = glm::cross(right, forward);

		glm::vec3 accel(0.0f);

		if (m_Movement.forward) accel += forward;
		if (m_Movement.backward) accel -= forward;

		if (m_Movement.left) accel -= right;
		if (m_Movement.right) accel += right;

		if (m_Movement.up) accel += up;
		if (m_Movement.down) accel -= up;

		if (m_Movement.fastSpeed) accel *= m_FastCoef;

		if (accel == glm::vec3(0))
		{
			// Decelerate naturally according to the damping value
			m_MoveSpeed -= m_MoveSpeed * std::min((1.0f / m_Damping) * static_cast<float>(ts), 1.0f);
		}
		else
		{
			// Acceleration
			m_MoveSpeed += accel * static_cast<float>(ts);
			const float maxSpeed = m_Movement.fastSpeed ? m_MaxSpeed * m_FastCoef : m_MaxSpeed;
			if (glm::length(m_MoveSpeed) > maxSpeed) m_MoveSpeed = glm::normalize(m_MoveSpeed) * maxSpeed;
		}
		
		m_CameraPosition += m_MoveSpeed * static_cast<float>(ts);
	}

	void FirstPersonCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseMovedEvent>(KURO_BIND_EVENT_FN(FirstPersonCamera::OnMouseMove));
	}

	glm::mat4 FirstPersonCamera::GetViewMatrix() const
	{
		//KURO_CORE_TRACE(m_CameraPosition);
		const glm::mat4 t = glm::translate(glm::mat4(1.0f), -m_CameraPosition);
		const glm::mat4 r = glm::mat4(m_CameraOrientation);
		return r * t;
	}

	glm::vec3 FirstPersonCamera::GetPosition() const
	{
		return m_CameraPosition;
	}

	void FirstPersonCamera::SetPosition(const glm::vec3& pos)
	{
		m_CameraPosition = pos;
	}

	void FirstPersonCamera::SetupVector(const glm::vec3& up)
	{
		const glm::mat4 view = GetViewMatrix();
		const glm::vec3 dir = -glm::vec3(view[0][2], view[1][2], view[2][2]);
		m_CameraOrientation = glm::lookAt(m_CameraPosition, m_CameraPosition + dir, up);
	}

	bool FirstPersonCamera::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return false;
	}

	bool FirstPersonCamera::OnMouseMove(MouseMovedEvent& e)
	{		
		m_MouseState.Pos.x = e.GetX();
		m_MouseState.Pos.y = e.GetY();
		return false;
	}
}
