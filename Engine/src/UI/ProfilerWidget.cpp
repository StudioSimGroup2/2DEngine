#include "ProfilerWidget.h"

#include "imgui.h"
#include "implot\implot.h"

#include "Engine\Renderer\Device.h"

namespace Engine
{
	void ProfilerWidget::Render()
	{
		ImS16 Default[3] = { 1, 1, 1 };
		ImS16 Renderer[3] = { 1, 1, 1 };
		ImS16 Assets[3] = { 1, 1, 1 };

		static const char* labels[] = { "Default", "Renderer", "Assets" };
		static const double positions[] = { 0, 1, 2 };

		ImGui::Begin("Profiler", NULL);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Graphics Card Name: %s", Device::GetDeviceData().mGraphicsCardName.c_str());
		ImGui::Text("Estimated Total Memory: %iMB", Device::GetDeviceData().mGraphicsCardTotalMemory);
		ImGui::Text("Renderer API: %s", Device::GetDeviceData().mRendererAPI.c_str());
		ImGui::Separator();
		if (ImGui::CollapsingHeader("Heap"))
		{
			ImPlot::SetNextPlotLimits(0, 110, -0.5, 9.5, ImGuiCond_Always);
			ImPlot::SetNextPlotTicksY(positions, 3, labels);

			if (ImPlot::BeginPlot("Heap Profiler", "Memory (MB)", "Heap",
				ImVec2(-1, 0), 0, 0, ImPlotAxisFlags_Invert | ImPlotFlags_NoLegend))
			{
				ImPlot::SetLegendLocation(ImPlotLocation_West, ImPlotOrientation_Vertical);
				ImPlot::PlotBarsH("Default", Default, 3, 0.2, -0.2);
			}
			ImPlot::EndPlot();
		}
		ImGui::End();
	}
	
	ProfilerWidget::ProfilerWidget()
	{
		ImPlot::CreateContext();
	}

	ProfilerWidget::~ProfilerWidget()
	{
		ImPlot::DestroyContext();
	}
}