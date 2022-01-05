/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an  BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   GenerateSineCandlesticksExampleApp.cpp
 * @author Scott Brauer
 * @date   12-02-2021
 */

#include <iostream>
#include <regex>

#include "imgui.h"
#include "implot.h"
#include "implot_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "easylogging++.h"

#include "GenerateSineCandlesticksExampleApp.hpp"

GenerateSineCandlesticksExampleApp::GenerateSineCandlesticksExampleApp():
		IImGuiApp(),
		m_clearColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f)),
		m_stepsPerDuration(0.01),
		m_sineData{
			{{ 5.0, 0.0, 20.0},  {60,  30, 240},  {0.0, 0.0, 20.0},  {0, 0, 60}},
			{{10.0, 0.0, 40.0},  {90,  30, 240},  {0.0, 0.0, 40.0},  {0, 0, 90}},
			{{20.0, 0.0, 80.0},  {120, 30, 480},  {0.0, 0.0, 80.0},  {0, 0, 120}},
			{{40.0, 0.0, 160.0}, {240, 30, 1024}, {0.0, 0.0, 160.0}, {0, 0, 240}}
		},
		m_graphToSineScale(0.01),
		m_sineWaveCollection(
				1000,
				offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"),
				std::chrono::seconds(5),
				{
						offcenter::trading::common::SineWave<FloatType>(m_sineData[0].amplitude.value, m_sineData[0].waveLengthInSeconds(), m_sineData[0].amplitudeShift.value, m_sineData[0].wavelengthShiftInMilliseconds()),
						offcenter::trading::common::SineWave<FloatType>(m_sineData[1].amplitude.value, m_sineData[1].waveLengthInSeconds(), m_sineData[1].amplitudeShift.value, m_sineData[1].wavelengthShiftInMilliseconds()),
						offcenter::trading::common::SineWave<FloatType>(m_sineData[2].amplitude.value, m_sineData[2].waveLengthInSeconds(), m_sineData[2].amplitudeShift.value, m_sineData[2].wavelengthShiftInMilliseconds()),
						offcenter::trading::common::SineWave<FloatType>(m_sineData[3].amplitude.value, m_sineData[3].waveLengthInSeconds(), m_sineData[3].amplitudeShift.value, m_sineData[3].wavelengthShiftInMilliseconds())
				}
		),
		m_showWave(false),
		m_showCandles(true)

{

}

GenerateSineCandlesticksExampleApp::~GenerateSineCandlesticksExampleApp() {
	// TODO Auto-generated destructor stub
}

void GenerateSineCandlesticksExampleApp::onInitProgramOptions(
		program_options::ProgramOptionsManager &optionsManager)
{
	m_options = optionsManager.add<GenerateSineCandlesticksExampleProgramOptions>();
}

void GenerateSineCandlesticksExampleApp::onSetUp()
{
	ImPlot::CreateContext();
}

void GenerateSineCandlesticksExampleApp::onExecute()
{

}
void GenerateSineCandlesticksExampleApp::onExecute(GLFWwindow* window)
{
	ImVec4 sine0Color(0.5f, 0.2f, 0.9f, 0.8f);
	ImVec4 sine1Color(0.2f, 0.85f, 0.85f, 0.5f);
	ImVec4 sine2Color(0.2f, 0.85f, 0.2f, 0.75f);
	ImVec4 sine3Color(0.9f, 0.5f, 0.2f, 0.9f);
	std::vector<ImVec4> sineColors{sine0Color, sine1Color, sine2Color, sine3Color};

	int w, h;
	glfwGetWindowSize(window, &w, &h);
	ImGui::SetNextWindowSize(ImVec2(w, h));
	ImGui::SetNextWindowPos({0,0});

	ImGui::Begin("ImGraph", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Hideable;

	int maxIndex = 4;
	if (ImGui::BeginTable("table1", maxIndex, flags))
	{

		// Table headers
		ImGui::TableSetupColumn("Sine0", ImGuiTableColumnFlags_WidthStretch);

		if (maxIndex >= 1) {
			ImGui::TableSetupColumn("Sine1", ImGuiTableColumnFlags_WidthStretch);
		}

		if (maxIndex >= 2) {
			ImGui::TableSetupColumn("Sine2", ImGuiTableColumnFlags_WidthStretch);
		}

		if (maxIndex >= 3) {
			ImGui::TableSetupColumn("Sine3", ImGuiTableColumnFlags_WidthStretch);
		}

		ImGui::TableHeadersRow();

		displayColumn(maxIndex, sineColors, "Amplitude",
				[this](const std::string& text, int index) {
					if (ImGui::SliderFloat(text.c_str(), &m_sineData.at(index).amplitude.value, m_sineData.at(index).amplitude.min, m_sineData.at(index).amplitude.max, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
						m_sineWaveCollection.setAmplitude(index, m_sineData.at(index).amplitude.value);
					}
				}
		);
		/*
		ImGui::TableNextRow();
		for (int index = 0; index < maxIndex; index++) {
			ImGui::TableSetColumnIndex(index);
			ImGui::PushStyleColor(ImGuiCol_Text, sineColors.at(index));
			std::string text("Amplitude(" + std::to_string(index) + ")");
			if (ImGui::SliderFloat(text.c_str(), &m_sineData.at(index).amplitude.value, m_sineData.at(index).amplitude.min, m_sineData.at(index).amplitude.max, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
				m_sineWaveCollection.setAmplitude(index, m_sineData.at(index).amplitude.value);
			}
			ImGui::PopStyleColor();
		}
		*/

		displayColumn(maxIndex, sineColors, "Wavelength",
				[this](const std::string& text, int index) {
					if (ImGui::SliderInt(text.c_str(), &m_sineData.at(index).wavelength.value, m_sineData.at(index).wavelength.min, m_sineData.at(index).wavelength.max, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
						m_sineWaveCollection.setWavelength(index, std::chrono::seconds(m_sineData.at(index).wavelength.value));
						m_sineData.at(index).wavelengthShift.max = m_sineData.at(index).wavelength.value;
						m_sineData.at(index).wavelengthShift.value = std::min(m_sineData.at(index).wavelengthShift.max, m_sineData.at(index).wavelengthShift.value);
					}
				}
		);
		/*
		ImGui::TableNextRow();
		for (int index = 0; index < maxIndex; index++) {
			ImGui::TableSetColumnIndex(index);
			std::string text("Wavelength(" + std::to_string(index) + ")");
			if (ImGui::SliderInt(text.c_str(), &m_sineData.at(index).wavelength.value, m_sineData.at(index).wavelength.min, m_sineData.at(index).wavelength.max, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
				m_sineWaveCollection.setWavelength(index, std::chrono::seconds(m_sineData.at(index).wavelength.value));
				m_sineData.at(index).wavelengthShift.max = m_sineData.at(index).wavelength.value;
				m_sineData.at(index).wavelengthShift.value = std::min(m_sineData.at(index).wavelengthShift.max, m_sineData.at(index).wavelengthShift.value);
			}
		}
		*/

		displayColumn(maxIndex, sineColors, "Amplitude Shift",
				[this](const std::string& text, int index) {
					if (ImGui::SliderFloat(text.c_str(), &m_sineData.at(index).amplitudeShift.value, m_sineData.at(index).amplitudeShift.min, m_sineData.at(index).amplitudeShift.max, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
						m_sineWaveCollection.setAmplitudeShift(index, m_sineData.at(index).amplitudeShift.value);
					}
				}
		);
		/*
		ImGui::TableNextRow();
		for (int index = 0; index < maxIndex; index++) {
			ImGui::TableSetColumnIndex(index);
			std::string text("Amplitude Shift(" + std::to_string(index) + ")");
			if (ImGui::SliderFloat(text.c_str(), &m_sineData.at(index).amplitudeShift.value, m_sineData.at(index).amplitudeShift.min, m_sineData.at(index).amplitudeShift.max, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
				m_sineWaveCollection.setAmplitudeShift(index, m_sineData.at(index).amplitudeShift.value);
			}
		}
		*/

		displayColumn(maxIndex, sineColors, "Wavelength Shift",
				[this](const std::string& text, int index) {
					if (ImGui::SliderInt(text.c_str(), &m_sineData.at(index).wavelengthShift.value, m_sineData.at(index).wavelengthShift.min, m_sineData.at(index).wavelengthShift.max, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
						m_sineWaveCollection.setWavelengthShift(index, std::chrono::seconds(m_sineData.at(index).wavelengthShift.value));
					}
				}
		);
		/*
		ImGui::TableNextRow();
		for (int index = 0; index < maxIndex; index++) {
			ImGui::TableSetColumnIndex(index);
			std::string text("Wavelength Shift(" + std::to_string(index) + ")");
			if (ImGui::SliderInt(text.c_str(), &m_sineData.at(index).wavelengthShift.value, m_sineData.at(index).wavelengthShift.min, m_sineData.at(index).wavelengthShift.max, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
				m_sineWaveCollection.setWavelengthShift(index, std::chrono::seconds(m_sineData.at(index).wavelengthShift.value));
			}
		}
		*/

		ImGui::TableNextRow();
		for (int index = 0; index < maxIndex; index++) {
			ImGui::TableSetColumnIndex(index);
			ImGui::PushStyleColor(ImGuiCol_Text, sineColors.at(index));
			std::string text("Show Wave(" + std::to_string(index) + ")");
			ImGui::Checkbox(text.c_str(), &m_sineData.at(index).showSineWave);
			ImGui::PopStyleColor();
		}

		ImGui::EndTable();
	}

	ImGui::Checkbox("Sine Wave", &m_showWave);
	ImGui::SameLine();
	ImGui::Checkbox("Candlesticks", &m_showCandles);

	if (ImPlot::BeginPlot("##Curve", ImVec2(-1,-1))) {
		ImPlot::SetupAxis(ImAxis_X1, "Time", ImPlotAxisFlags_Time | ImPlotAxisFlags_LockMin);// | ImPlotAxisFlags_AutoFit);
		ImPlot::SetupAxisLimits(
				ImAxis_X1,
				offcenter::common::UTCDateTimeSecondsFromEpoch(m_sineWaveCollection.startTime()),
				offcenter::common::UTCDateTimeSecondsFromEpoch(m_sineWaveCollection.endTime()),
				ImPlotCond_Once);

		ImPlot::SetupAxis(ImAxis_Y1, "Price");
		ImPlot::SetupAxisLimits(
				ImAxis_Y1,
				m_sineWaveCollection.minAmplitude(),
				m_sineWaveCollection.maxAmplitude(),
				ImPlotCond_Once);

		ImDrawList* draw_list = ImPlot::GetPlotDrawList();
		ImVec4 bullCol = ImVec4(0, 0.4, 0, 1);
		ImVec4 bullColBorder = ImVec4(0, 1, 0, 1);
		ImVec4 bearCol = ImVec4(0.4, 0, 0, 1);
		ImVec4 bearColBorder = ImVec4(1, 0, 0, 1);
		//CandlesticksType::CandlestickDuration stepDuration(m_candlesticks.durationInSeconds());
		//offcenter::common::UTCDateTime endTime = m_candlesticks.startTime() + CandlesticksType::CandlestickDuration(m_candlesticks.durationInSeconds()* 1000);
		// Candlesticks
		if (m_showCandles && ImPlot::BeginItem("Candlesticks")) {
			ImPlot::GetCurrentItem()->Color = ImGui::GetColorU32(bullCol);
			std::chrono::milliseconds offset = std::chrono::duration_cast<std::chrono::milliseconds>(m_sineWaveCollection.duration() * 0.40);

			for (offcenter::trading::common::SineWaveOHLCElement<FloatType>& element : m_sineWaveCollection.ohlcElements()) {
				ImU32 color       = ImGui::GetColorU32(element.ohlc().open > element.ohlc().close ? bearCol : bullCol);
				ImU32 colorBorder = ImGui::GetColorU32(element.ohlc().open > element.ohlc().close ? bearColBorder : bullColBorder);

	            offcenter::common::UTCDateTime startTime = element.ohlc().time - offset;
				offcenter::common::UTCDateTime endTime = element.ohlc().time + offset;
				ImVec2 open_pos  = ImPlot::PlotToPixels(offcenter::common::UTCDateTimeSecondsFromEpoch(startTime), element.ohlc().open);
				ImVec2 close_pos = ImPlot::PlotToPixels(offcenter::common::UTCDateTimeSecondsFromEpoch(endTime), element.ohlc().close);
				ImVec2 low_pos   = ImPlot::PlotToPixels(offcenter::common::UTCDateTimeSecondsFromEpoch(element.ohlc().time), element.ohlc().low);
	            ImVec2 high_pos  = ImPlot::PlotToPixels(offcenter::common::UTCDateTimeSecondsFromEpoch(element.ohlc().time), element.ohlc().high);

	            draw_list->AddLine(low_pos,  high_pos , colorBorder, 1.0); //ImMax(1.0f, ImAbs(open_pos.x - close_pos.x)/10.0f));
				draw_list->AddRectFilled(open_pos, close_pos, color);
				draw_list->AddRect(open_pos, close_pos, colorBorder);
			}

			ImPlot::EndItem();
		}

		// Sine wave
		if (m_showWave) {
			ImPlot::SetNextLineStyle(ImVec4(1,0.75f,0,1));
			ImPlot::PlotLineG("Curve",
					[](void* data, int idx) -> ImPlotPoint {
						GenerateSineCandlesticksExampleApp* app = static_cast<GenerateSineCandlesticksExampleApp*>(data);
						const offcenter::trading::common::OHLC<FloatType>& ohlc = app->sineWaveCollection().ohlc(idx);
						return ImPlotPoint(offcenter::common::UTCDateTimeSecondsFromEpoch(ohlc.time), app->sineWaveCollection().y(idx));
					},
					this, 1000
			);
		}

		initDisplaySineWave<0>("Sine0", sineColors.at(0), 1000);
		initDisplaySineWave<1>("Sine1", sineColors.at(1), 1000);
		initDisplaySineWave<2>("Sine2", sineColors.at(2), 1000);
		initDisplaySineWave<3>("Sine3", sineColors.at(3), 1000);

		// End of plot
		ImPlot::EndPlot();
	}

	ImGui::End();
}

void GenerateSineCandlesticksExampleApp::onTearDown()
{
	ImPlot::DestroyContext();
}

void GenerateSineCandlesticksExampleApp::onHelp(const std::string &help)
{

}

void GenerateSineCandlesticksExampleApp::onVersion()
{
}

void GenerateSineCandlesticksExampleApp::genSineEditColumn(int sineIndex, SineData& sinData)
{
	/*
	ImGui::TableSetColumnIndex(sineIndex);
	ImGui::TableNextRow();
	if (ImGui::SliderFloat("Amplitude", &sinData.amplitude, sinData.amplitudeMin, sinData.amplitudeMax, "%.3f")) { m_sines.sine(sineIndex).setAmplitude(sinData.amplitude); }
	ImGui::TableNextRow();
	if (ImGui::SliderFloat("Frequency", &sinData.frequency, sinData.frequencyMin, sinData.frequencyMax, "%.3f")) { m_sines.sine(sineIndex).setFrequency(sinData.frequency); }
	ImGui::TableNextRow();
	if (ImGui::SliderFloat("Amplitude Shift", &sinData.amplitudeShift, sinData.amplitudeShiftMin, sinData.amplitudeShiftMax, "%.3f")) { m_sines.sine(sineIndex).setAmplitudeShift(sinData.amplitudeShift); }
	ImGui::TableNextRow();
	if (ImGui::SliderFloat("Frequency Shift", &sinData.frequencyShift, sinData.amplitudeShiftMin, sinData.amplitudeShiftMax, "%.3f")) { m_sines.sine(sineIndex).setFrequencyShift(sinData.frequencyShift); }
	*/
}

ImPlotPoint GenerateSineCandlesticksExampleApp::displaySineWave(void* data, int idx, int waveNum) {
	const offcenter::trading::common::OHLC<FloatType>& ohlc = sineWaveCollection().ohlc(idx);
	const offcenter::trading::common::OHLC<FloatType>& ohlcFirst = sineWaveCollection().ohlc(0);
	return ImPlotPoint(offcenter::common::UTCDateTimeSecondsFromEpoch(ohlc.time), sineWaveCollection().sineWave(waveNum).y(ohlc.time - ohlcFirst.time));
}

/*
template <typename SetValue>
void GenerateSineCandlesticksExampleApp::genAmplitudeEdit(int sineIndex, SineData::ElementData& data, SetValue&& setValue)
{
	ImGui::TableSetColumnIndex(sineIndex);
	if (ImGui::SliderFloat("Amplitude", &data.value, data.min, data.max, "%.3f"))
	{
		setValue(sineIndex, data.value);
	}
}
*/
