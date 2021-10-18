#pragma once
#include "WindowInclude.h"
#include "ErrorHandling.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <optional>
#include "Graphics.h"
#include <memory>

class Window
{
public:
	class Exception : public ErrorHandling
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};

private:
	class WinClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		WinClass() noexcept;
		~WinClass();
		WinClass(const Window&) = delete;
		WinClass& operator=(const WinClass&) = delete;
		static constexpr const char* winClassName = "DirectX Game";
		static WinClass windowClass;
		HINSTANCE hInst;
	};

public: 
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	Graphics& getGfx();
private:
	static LRESULT CALLBACK MsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgCall(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard keyboard;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> gfx;
};

#define CHWND_EXCEPT(hr) Window::Exception(__LINE__,__FILE__,hr)

