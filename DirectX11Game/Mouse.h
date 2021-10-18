#pragma once
#include <queue>


class Mouse
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			Invalid

		};
	private:
		Type type;
		bool leftButtonPressed;
		bool rightButtonPressed;
		int x;
		int y;
	public:
		Event() noexcept : type(Type::Invalid), leftButtonPressed(false), rightButtonPressed(false), x(0), y(0)
		{}
		Event(Type type, const Mouse& parent) noexcept : type(type), leftButtonPressed(parent.leftButtonPressed), rightButtonPressed(parent.rightButtonPressed), x(parent.x), y(parent.y) {}
		bool isValid() const noexcept
		{
			return type != Type::Invalid;
		}
		Type GetType() const noexcept
		{
			return type;
		}
		std::pair<int, int> GetPos() const noexcept
		{
			return{ x,y };
		}
		int GetPosX() const noexcept
		{
			return x;
		}
		int GetPosY() const noexcept
		{
			return y;
		}
		bool LeftIsPressed() const noexcept
		{
			return leftButtonPressed;
		}
		bool RightIsPressed() const noexcept
		{
			return rightButtonPressed;
		}
	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	std::pair<int, int> GetPos() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool IsInWindow() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	Mouse::Event Read() noexcept;
	bool IsEmpty() const noexcept
	{
		return buffer.empty();
	}
	void Clear() noexcept;
private:
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;
	void OnMouseMove(int x, int y) noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnRightReleased(int x, int y) noexcept;
	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void TrimBuffer() noexcept;
	void OnWheelDelta(int x, int y, int delta) noexcept;
private:
	static constexpr unsigned int bufferSize = 16u;
	int x;
	int y;
	bool leftButtonPressed = false;
	bool rightButtonPressed = false;
	bool inWindow = false;
	int wheelDelta = 0;
	std::queue<Event> buffer;
};