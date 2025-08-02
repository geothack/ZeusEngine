#pragma once

struct Size
{
	int Width;
	int Height;
};

class ZWindow
{
public:
	ZWindow() = default;
	ZWindow(std::string_view title, const int width, const int height);
	~ZWindow();

	

	ZWindow(const ZWindow&) = delete;
	ZWindow& operator=(ZWindow&&) = delete;
	ZWindow& operator=(const ZWindow&) = delete;
	ZWindow(ZWindow&&) = delete;

	void Events() const;

	void SwapBuffers() const;

	static GLFWwindow* Get() { return z_PlatformWindow; }

	const GLFWvidmode* GetVideoMode() const { return z_VideoMode; }

	static Size GetSize() { return z_WindowSize; }

private:
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void APIENTRY DebugLog(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);

private:
	inline static GLFWwindow* z_PlatformWindow = nullptr;
	const GLFWvidmode* z_VideoMode;

	inline static Size z_WindowSize = {};
};

