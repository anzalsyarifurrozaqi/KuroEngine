#pragma once

namespace Kuro
{
	class CameraPositionerInterface
	{
	public:
		virtual ~CameraPositionerInterface() = default;
		virtual glm::mat4 GetViewMatrix() const = 0;
		virtual glm::vec3 GetPosition() const = 0;
	};

	class Camera final
	{
	public:
		explicit Camera(CameraPositionerInterface& positioner)
			: m_Positioner(&positioner)
		{
			KURO_CORE_TRACE("Camera");

		}

		Camera(const Camera&) = default;
		Camera& operator = (const Camera&) = default;

		glm::mat4 GetViewMatrix() const { return m_Positioner->GetViewMatrix(); }
		glm::vec3 GetPosition() const { return m_Positioner->GetPosition(); }

	private:
		const CameraPositionerInterface* m_Positioner;
	};


}

