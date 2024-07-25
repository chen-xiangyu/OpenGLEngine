#pragma once
#include <set>
#include <map>
#include <string>
#include <GLFW/glfw3.h>

namespace hiveEngine
{
	//template <typename T>
	//class CAttributesRange
	//{
	//public:
	//	IAttributesRange() = default;
	//	~IAttributesRange() = default;

	//	static bool isCorrect(const T& vValue)
	//	{
	//		return m_Values.find(vValue) != m_Values.end();
	//	}
	//	static T getDefaultValue()
	//	{
	//		return m_DefaultValue;
	//	}

	//protected:
	//	static std::set<T> m_Values;
	//	static T m_DefaultValue;
	//};

	//class CVersionRange : public CAttributesRange<std::pair<int, int>>
	//{
	//public:
	//	CVersionRange() = default;
	//	~CVersionRange() = default;

	//private:

	//};
	//CVersionRange::m_Values = { {1, 2}, {3, 4} };
	//	const std::set<std::string> m_Versions = {
	//	"3.0", "3.1", "3.2", "3.3", "3.4",
	//	"4.0", "4.1", "4.2", "4.3", "4.4", "4.5", "4.6",
	//};

	//class CProfileRange : public CAttributesRange<std::string>
	//{
	//public:
	//	CProfileRange() = default;
	//	~CProfileRange() = default;

	//	bool isCorrect(const std::string& vValue) const override;
	//	std::string getDefaultValue() const override;
	//};
	class CVersionRange
	{
	public:
		CVersionRange() = default;
		~CVersionRange() = default;

		static bool isCorrect(const std::pair<int, int>& vValue)
		{
			return m_Versions.find(vValue) != m_Versions.end();
		}
		static std::pair<int, int> getDefaultValue()
		{
			return m_DefaultValue;
		}

	private:
		static const std::set<std::pair<int, int>> m_Versions;
		static const std::pair<int, int> m_DefaultValue;
	};

	class CProfileRange
	{
	public:
		CProfileRange() = default;
		~CProfileRange() = default;

		static bool isCorrect(const std::string& vValue)
		{
			return m_Profiles.find(vValue) != m_Profiles.end();
		}
		static std::string getDefaultValue()
		{
			return m_DefaultValue;
		}

	private:
		static const std::set<std::string> m_Profiles;
		static const std::string m_DefaultValue;
	};

	class CScreenSizeRange
	{
	public:
		CScreenSizeRange() = default;
		~CScreenSizeRange() = default;

		static bool isCorrect(const std::pair<int, int>& vValue)
		{
			int Width = vValue.first, Height = vValue.second;
			GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
			//if (!PrimaryMonitor) {
			//	std::cerr << "Failed to get primary monitor" << std::endl;
			//	glfwTerminate();
			//	return;
			//}
			const GLFWvidmode* mode = glfwGetVideoMode(PrimaryMonitor);
			//if (!mode) {
			//	std::cerr << "Failed to get video mode" << std::endl;
			//	glfwTerminate();
			//}

			if (Width <= 0 || Width > mode->width || Height <= 0 || mode->height)
			{
				return false;
			}
			return true;
		}
		static std::pair<int, int> getDefaultValue()
		{
			return m_DefaultValue;
		}

	private:
		static const std::pair<int, int> m_DefaultValue;
	};
}
