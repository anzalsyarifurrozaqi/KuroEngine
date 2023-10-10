#pragma once

#include "Camera.h"
#include "Kuro/Core/TimeStep.h"
#include "Kuro/Events/Event.h"
#include "Kuro/Events/MouseEvent.h"

namespace Kuro
{
	class FirstPersonCamera final : public CameraPositionerInterface
	{
	public:
		FirstPersonCamera() = default;
		FirstPersonCamera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		virtual glm::mat4 GetViewMatrix() const override;
		virtual glm::vec3 GetPosition() const override;

		void SetPosition(const glm::vec3& pos);
		void SetupVector(const glm::vec3& up);
		void ResetMousePosition(const glm::vec2& p) { m_MousePos = p; }

		inline void LookAt(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up)
		{
			m_CameraPosition = pos;
			m_CameraOrientation = glm::lookAt(pos, target, up);
		}

	public:
		struct Movement
		{
			bool forward = false;
			bool backward = false;
			bool left = false;
			bool right = false;
			bool up = false;
			bool down = false;
			bool fastSpeed = false;
		} m_Movement;

		struct MouseState
		{
			glm::vec2 Pos = glm::vec2(0.0f);
			bool PressedLeft = false;
		} m_MouseState;

	public:
		float m_MouseSpeed = 4.0f;
		float m_Acceleration = 150.0f;
		float m_Damping = 0.2f;
		float m_MaxSpeed = 10.0f;
		float m_FastCoef = 10.0f;

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMove(MouseMovedEvent& e);
		//bool OnWindowResized(WindowResizeEvent& e);

	private:
		glm::vec2 m_MousePos = glm::vec2(0);
		glm::vec3 m_CameraPosition = glm::vec3(0.0f, 10.0f, 10.0f);
		glm::quat m_CameraOrientation = glm::quat(glm::vec3(0));
		glm::vec3 m_MoveSpeed = glm::vec3(0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 0.0f, 1.0f);
	};
}
