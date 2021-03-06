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
 * @file   GenerateSineCandlesticksExampleApp.hpp
 * @author Scott Brauer
 * @date   12-03-2021
 */

#ifndef GENERATESINECANDLESTICKSEXAMPLEAPP_HPP_
#define GENERATESINECANDLESTICKSEXAMPLEAPP_HPP_

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"

#include "offcenter/common/imgui/IImGuiApp.hpp"

#include "offcenter/trading/datatypes/common/GenerateSineCandlesticks.hpp"

#include "GenerateSineCandlesticksExampleProgramOptions.hpp"

struct SineData {
	struct FloatData {
		float value;
		float min;
		float max;
	};
	struct IntData {
		int value;
		int min;
		int max;
	};
	FloatData amplitude;
	IntData wavelength;
	FloatData amplitudeShift;
	IntData wavelengthShift;
	bool showSineWave;

	std::chrono::seconds waveLengthInSeconds() { return std::chrono::seconds(wavelength.value); }
	std::chrono::milliseconds wavelengthShiftInMilliseconds() { return std::chrono::milliseconds(wavelengthShift.value); }
};

/**
 *
 */
class GenerateSineCandlesticksExampleApp:
		public offcenter::common::imgui::IImGuiApp
{
public:
	using FloatType = double;
	using CandlesticksType = offcenter::trading::common::GenerateSineCandlesticks<FloatType, std::chrono::seconds, 5>;

public:
	explicit GenerateSineCandlesticksExampleApp();
	virtual ~GenerateSineCandlesticksExampleApp();

	void onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onExecute() override;
	std::string windowTitle() override { return "Sine Wave Candlesticks"; }
	void onExecute(GLFWwindow* window) override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

    //offcenter::trading::common::CombineSine<FloatType>& sines() { return m_candlesticks.sines(); }
    FloatType graphToSineScale() { return m_graphToSineScale; }
    offcenter::trading::common::SineWaveOHLCCollection<FloatType>& sineWaveCollection() { return m_sineWaveCollection; }

private:
    void genSineEditColumn(int sineIndex, SineData& sinData);
    ImPlotPoint displaySineWave(void* data, int idx, int waveNum);

    template<int index>
    void initDisplaySineWave(const std::string label, const ImVec4& color, int indexCount) {
		if (m_sineData.at(index).showSineWave) {
			ImPlot::SetNextLineStyle(color);
			ImPlot::PlotLineG(label.c_str(),
					[](void* data, int idx) -> ImPlotPoint {
						GenerateSineCandlesticksExampleApp* app = static_cast<GenerateSineCandlesticksExampleApp*>(data);
						return app->displaySineWave(data, idx, index);
					},
					this, indexCount
			);
		}
    }

	template<typename SliderLambda>
	void displayColumn(int maxIndex, const std::vector<ImVec4>& sineColors, const std::string& label, SliderLambda lambda)
	{
		ImGui::TableNextRow();
		for (int index = 0; index < maxIndex; index++) {
			ImGui::TableSetColumnIndex(index);
			ImGui::PushStyleColor(ImGuiCol_Text, sineColors.at(index));
			std::string text(label + "(" + std::to_string(index) + ")");
			lambda(text, index);
			ImGui::PopStyleColor();
		}
	}

private:
	GenerateSineCandlesticksExampleProgramOptions::ConfigPtr m_options;
    ImVec4 m_clearColor;
    FloatType m_stepsPerDuration;
    FloatType m_graphToSineScale;
    std::vector<SineData> m_sineData;

	offcenter::trading::common::SineWaveOHLCCollection<FloatType> m_sineWaveCollection;
	bool m_showWave;
	bool m_showCandles;

};

#endif /* GENERATESINECANDLESTICKSEXAMPLEAPP_HPP_ */
