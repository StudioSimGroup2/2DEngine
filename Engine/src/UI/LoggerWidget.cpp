#include "LoggerWidget.h"

#include "imgui.h"

#include "Utils\Logger.h"

namespace Engine
{
	void LoggerWidget::Render()
	{
		ImGui::Begin("Logger");

		std::string sen;
		for (std::string s : Logger::GetTextBuffer())	// Format the logs into one giant string... not ideal, as we cant do fancy colouring.
			sen += s;
		ImGui::Text("%s", sen.c_str());

		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())	// Auto scroll to bottom
			ImGui::SetScrollHereY(1.0f);

		ImGui::End();

		if (Logger::GetTextBuffer().size() > 512) 
			Logger::GetTextBuffer().erase(Logger::GetTextBuffer().begin(), Logger::GetTextBuffer().begin() + 256);
	}

	LoggerWidget::LoggerWidget()
	{
	}

	LoggerWidget::~LoggerWidget()
	{
	}
}
