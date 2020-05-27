#include <rubberband/RubberBandStretcher.h>
#include <emscripten/bind.h>

#include <vector>

using namespace emscripten;
using namespace RubberBand;

// fixme: getting out of bounds accesses with this, is the pointer not right?
void RubberBandStretcher_process(RubberBandStretcher& self, uintptr_t input_flat_ptr, size_t samples, int channels, bool final)
{
    auto* input_flat = reinterpret_cast<float*>(input_flat_ptr);

    std::vector<float*> input;
    for (int i = 0; i < channels; ++i) {
        input.push_back(&input_flat[samples * i]);
    }

    self.process(&input[0], samples, final);
}

void RubberBandStretcher_study(RubberBandStretcher& self, uintptr_t input_flat_ptr, size_t samples, int channels, bool final)
{
    auto* input_flat = reinterpret_cast<float*>(input_flat_ptr);

    std::vector<float*> input;
    for (int i = 0; i < channels; ++i) {
        input.push_back(&input_flat[samples * i]);
    }

    self.study(&input[0], samples, final);
}

size_t RubberBandStretcher_retrieve(RubberBandStretcher& self, uintptr_t output_flat_ptr, size_t samples, int channels)
{
    auto* output_flat = reinterpret_cast<float*>(output_flat_ptr);

    std::vector<float*> output;
    for (int i = 0; i < channels; ++i) {
        output.push_back(&output_flat[samples * i]);
    }

    return self.retrieve(&output[0], samples);
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
