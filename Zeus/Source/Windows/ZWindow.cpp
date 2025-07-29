#include "ZWindow.h"

namespace {

	/*void CursorPosCallback(GLFWwindow* window, double _x, double _y)
	{
		GInput->GetMouse().SetPosition(_x, _y);
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		GInput->GetMouse().SetButtons(button, action);
	}

	void MouseWheelCallback(GLFWwindow* window, double dx, double dy)
	{
		GInput->GetMouse().SetWheel(dx, dy);
	}*/

}

ZWindow::ZWindow(std::string_view title, const int width, const int height)
{
	auto success = glfwInit();

	if (success == 0)
	{
		//Error error("Glfw failed to initialize");
	}

	m_PlatformWindow = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

	if (!m_PlatformWindow)
	{
		//Error error("Glfw failed to create window");
	}

	glfwMakeContextCurrent(m_PlatformWindow);

	/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Error error("Failed to initialize glad");
	}*/

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (!monitor)
	{
		//Error error("Failed to get primary monitor");
		glfwTerminate();
	}

	m_VideoMode = glfwGetVideoMode(monitor);
	if (!m_VideoMode)
	{
		//Error error("Failed to get video mode");
		glfwTerminate();
	}

	//glfwSetKeyCallback(mPlatformWindow, Keyboard::KeyCallback);
	glfwSetFramebufferSizeCallback(m_PlatformWindow, FramebufferSizeCallback);
	//glfwSetCursorPosCallback(mPlatformWindow, CursorPosCallback);
	//glfwSetMouseButtonCallback(mPlatformWindow, MouseButtonCallback);
	//glfwSetScrollCallback(mPlatformWindow, MouseWheelCallback);

	glfwSwapInterval(1);

	m_WindowSize.Width = width;
	m_WindowSize.Height = height;

	//glEnable(GL_DEBUG_OUTPUT);
	//glDebugMessageCallback(DebugLog, nullptr);
}

ZWindow::~ZWindow()
{
	glfwDestroyWindow(m_PlatformWindow);
	glfwTerminate();
}

void ZWindow::Events() const
{
	glfwPollEvents();

	/*if (GInput->KeyWentDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(m_PlatformWindow, true);
	}*/
}

void ZWindow::SwapBuffers() const
{
	glfwSwapBuffers(m_PlatformWindow);
}

void ZWindow::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	m_WindowSize.Width = width;
	m_WindowSize.Height = height;
	//glViewport(0, 0, width, height);
}

void ZWindow::DebugLog(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
	/*switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::println("OpenGL High {}", message);
		break;

	case GL_DEBUG_SEVERITY_MEDIUM:
		std::println("OpenGL Medium {}", message);
		break;

	case GL_DEBUG_SEVERITY_LOW:
		std::println("OpenGL Low {}", message);
		break;

	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::println("OpenGL Notification {}", message);
		break;

	default:

		break;
	}*/
}
