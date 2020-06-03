#include <rubberband/RubberBandStretcher.h>
#include <emscripten/bind.h>

#include <vector>

using namespace emscripten;
using namespace RubberBand;

void RubberBandStretcher_process(RubberBandStretcher& self, val input_arr, size_t samples, int channels, bool final)
{
    auto input = vecFromJSArray<uintptr_t>(input_arr);
    self.process(reinterpret_cast<float**>(&input[0]), samples, final);
}

void RubberBandStretcher_study(RubberBandStretcher& self, val input_arr, size_t samples, int channels, bool final)
{
    auto input = vecFromJSArray<uintptr_t>(input_arr);
    self.study(reinterpret_cast<float**>(&input[0]), samples, final);
}

size_t RubberBandStretcher_retrieve(RubberBandStretcher& self, val output_arr, size_t samples, int channels)
{
    auto output = vecFromJSArray<uintptr_t>(output_arr);
    return self.retrieve(reinterpret_cast<float**>(&output[0]), samples);
}

EMSCRIPTEN_BINDINGS(rubberband) {
    enum_<RubberBandStretcher::Option>("Option")
        .value("ProcessOffline", RubberBandStretcher::OptionProcessOffline)
        .value("ProcessRealTime", RubberBandStretcher::OptionProcessRealTime)
        .value("StretchElastic", RubberBandStretcher::OptionStretchElastic)
        .value("StretchPrecise", RubberBandStretcher::OptionStretchPrecise)
        .value("TransientsCrisp", RubberBandStretcher::OptionTransientsCrisp)
        .value("TransientsMixed", RubberBandStretcher::OptionTransientsMixed)
        .value("TransientsSmooth", RubberBandStretcher::OptionTransientsSmooth)
        .value("DetectorCompound", RubberBandStretcher::OptionDetectorCompound)
        .value("DetectorPercussive", RubberBandStretcher::OptionDetectorPercussive)
        .value("DetectorSoft", RubberBandStretcher::OptionDetectorSoft)
        .value("PhaseLaminar", RubberBandStretcher::OptionPhaseLaminar)
        .value("PhaseIndependent", RubberBandStretcher::OptionPhaseIndependent)
        .value("ThreadingAuto", RubberBandStretcher::OptionThreadingAuto)
        .value("ThreadingNever", RubberBandStretcher::OptionThreadingNever)
        .value("ThreadingAlways", RubberBandStretcher::OptionThreadingAlways)
        .value("WindowStandard", RubberBandStretcher::OptionWindowStandard)
        .value("WindowShort", RubberBandStretcher::OptionWindowShort)
        .value("WindowLong", RubberBandStretcher::OptionWindowLong)
        .value("SmoothingOff", RubberBandStretcher::OptionSmoothingOff)
        .value("SmoothingOn", RubberBandStretcher::OptionSmoothingOn)
        .value("FormantShifted", RubberBandStretcher::OptionFormantShifted)
        .value("FormantPreserved", RubberBandStretcher::OptionFormantPreserved)
        .value("PitchHighSpeed", RubberBandStretcher::OptionPitchHighSpeed)
        .value("PitchHighQuality", RubberBandStretcher::OptionPitchHighQuality)
        .value("PitchHighConsistency", RubberBandStretcher::OptionPitchHighConsistency)
        .value("ChannelsApart", RubberBandStretcher::OptionChannelsApart)
        .value("ChannelsTogether", RubberBandStretcher::OptionChannelsTogether)
        ;

    enum_<RubberBandStretcher::PresetOption>("PresetOption")
        .value("Default", RubberBandStretcher::DefaultOptions)
        .value("Percussive", RubberBandStretcher::PercussiveOptions)
        ;

    class_<RubberBandStretcher>("RubberBandStretcher")
        .constructor<size_t, size_t, int, double, double>()
        .function("reset", &RubberBandStretcher::reset)
        .function("setTimeRatio", &RubberBandStretcher::setTimeRatio)
        .function("setPitchScale", &RubberBandStretcher::setPitchScale)
        .function("getTimeRatio", &RubberBandStretcher::getTimeRatio)
        .function("getPitchScale", &RubberBandStretcher::getPitchScale)
        .function("getLatency", &RubberBandStretcher::getLatency)
        .function("setTransientsOption", &RubberBandStretcher::setTransientsOption)
        .function("setDetectorOption", &RubberBandStretcher::setDetectorOption)
        .function("setPhaseOption", &RubberBandStretcher::setPhaseOption)
        .function("setFormantOption", &RubberBandStretcher::setFormantOption)
        .function("setPitchOption", &RubberBandStretcher::setPitchOption)
        .function("setExpectedInputDuration", &RubberBandStretcher::setExpectedInputDuration)
        .function("setMaxProcessSize", &RubberBandStretcher::setMaxProcessSize)
        .function("getSamplesRequired", &RubberBandStretcher::getSamplesRequired)
        .function("setKeyFrameMap", &RubberBandStretcher::setKeyFrameMap)
        .function("study", &RubberBandStretcher_study)
        .function("process", &RubberBandStretcher_process)
        .function("available", &RubberBandStretcher::available)
        .function("retrieve", &RubberBandStretcher_retrieve)
        .function("getFrequencyCutoff", &RubberBandStretcher::getFrequencyCutoff)
        .function("setFrequencyCutoff", &RubberBandStretcher::setFrequencyCutoff)
        .function("getInputIncrement", &RubberBandStretcher::getInputIncrement)
        .function("getOutputIncrements", &RubberBandStretcher::getOutputIncrements)
        .function("getPhaseResetCurve", &RubberBandStretcher::getPhaseResetCurve)
        .function("getExactTimePoints", &RubberBandStretcher::getExactTimePoints)
        .function("getChannelCount", &RubberBandStretcher::getChannelCount)
        .function("calculateStretch", &RubberBandStretcher::calculateStretch)
        .function("setDebugLevel", &RubberBandStretcher::setDebugLevel)
        .function("setDefaultDebugLevel", &RubberBandStretcher::setDefaultDebugLevel)
        ;

    register_vector<int>("vector<int>");
    register_vector<float>("vector<float>");
    register_map<size_t, size_t>("map<size_t, size_t>");
}
