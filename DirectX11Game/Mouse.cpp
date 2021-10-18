#include "Mouse.h"
#include <Windows.h>

std::pair<int, int> Mouse::GetPos() const noexcept
{
    return {x,y};
}

int Mouse::GetPosX() const noexcept
{
    return x;
}

int Mouse::GetPosY() const noexcept
{
    return y;
}

bool Mouse::IsInWindow() const noexcept
{
    return inWindow;
}


bool Mouse::LeftIsPressed() const noexcept
{
    return leftButtonPressed;
}

bool Mouse::RightIsPressed() const noexcept
{
    return rightButtonPressed;
}

Mouse::Event Mouse::Read() noexcept
{
    if(buffer.size() > 0u)
    {
        Mouse::Event event = buffer.front();
        buffer.pop();
        return event;
    }
    else
    {
        return Mouse::Event();
    }
}

void Mouse::Clear() noexcept
{
    buffer = std::queue<Event>();
}

void Mouse::OnMouseLeave() noexcept
{
    inWindow = false;
    buffer.push(Mouse::Event(Mouse::Event::Type::Leave, *this));
    TrimBuffer();
}

void Mouse::OnMouseEnter() noexcept
{
    inWindow = true;
    buffer.push(Mouse::Event(Mouse::Event::Type::Enter, *this));
    TrimBuffer();
}

void Mouse::OnMouseMove(int x2, int y2) noexcept
{
    x = x2;
    y = y2;

    buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
    TrimBuffer();
}

void Mouse::OnLeftPressed(int x, int y) noexcept
{
    leftButtonPressed = true;
    buffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
    TrimBuffer();
}

void Mouse::OnLeftReleased(int x, int y) noexcept
{
    leftButtonPressed = false;
    buffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
    TrimBuffer();
}

void Mouse::OnRightPressed(int x, int y) noexcept
{
    rightButtonPressed = true;
    buffer.push(Mouse::Event(Mouse::Event::Type::RPress, *this));
    TrimBuffer();
}

void Mouse::OnRightReleased(int x, int y) noexcept
{
    rightButtonPressed = false;
    buffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
    TrimBuffer();
}

void Mouse::OnWheelUp(int x, int y) noexcept
{
    buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
    TrimBuffer();
}

void Mouse::OnWheelDown(int x, int y) noexcept
{
    buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
    TrimBuffer();
}

void Mouse::TrimBuffer() noexcept
{
    while(buffer.size() > bufferSize)
    {
        buffer.pop();
    }
}

void Mouse::OnWheelDelta(int x, int y, int delta) noexcept
{
    wheelDelta += delta;

    while(wheelDelta >= WHEEL_DELTA)
    {
        wheelDelta -= WHEEL_DELTA;
        OnWheelUp(x, y);
    }
    while(wheelDelta <= -WHEEL_DELTA)
    {
        wheelDelta += WHEEL_DELTA;
        OnWheelDown(x, y);
    }
}
