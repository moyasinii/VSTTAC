// Preamp Plugin - Phase 0 ひな形
// first_test.py と同じ tanh ソフトクリップを VST3 にしたもの。
// ここに Phase 1〜3 で作ったモデルを順番に移植していく。

#include <juce_audio_processors/juce_audio_processors.h>
#include <cmath>

class PreampAudioProcessor : public juce::AudioProcessor
{
public:
    PreampAudioProcessor()
        : AudioProcessor (BusesProperties()
                              .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                              .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
          apvts (*this, nullptr, "PARAMS", createLayout())
    {
        drive  = apvts.getRawParameterValue ("drive");
        output = apvts.getRawParameterValue ("output");
    }

    // ---- パラメータ（DAW のつまみ）----
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout()
    {
        juce::AudioProcessorValueTreeState::ParameterLayout layout;
        layout.add (std::make_unique<juce::AudioParameterFloat> (
            juce::ParameterID { "drive", 1 }, "Drive",
            juce::NormalisableRange<float> (0.0f, 24.0f, 0.1f), 6.0f,
            juce::AudioParameterFloatAttributes().withLabel ("dB")));
        layout.add (std::make_unique<juce::AudioParameterFloat> (
            juce::ParameterID { "output", 1 }, "Output",
            juce::NormalisableRange<float> (-24.0f, 6.0f, 0.1f), 0.0f,
            juce::AudioParameterFloatAttributes().withLabel ("dB")));
        return layout;
    }

    // ---- 音声処理 ----
    void prepareToPlay (double, int) override {}
    void releaseResources() override {}

    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) override
    {
        juce::ScopedNoDenormals noDenormals;

        const float g    = juce::Decibels::decibelsToGain (drive->load());
        const float norm = 1.0f / std::tanh (g);   // フルスケール(1.0)が 1.0 に戻るよう補正
        const float out  = juce::Decibels::decibelsToGain (output->load());

        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            auto* x = buffer.getWritePointer (ch);
            for (int i = 0; i < buffer.getNumSamples(); ++i)
                x[i] = std::tanh (g * x[i]) * norm * out;
        }
    }

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override
    {
        const auto& outSet = layouts.getMainOutputChannelSet();
        if (outSet != juce::AudioChannelSet::mono() && outSet != juce::AudioChannelSet::stereo())
            return false;
        return outSet == layouts.getMainInputChannelSet();
    }

    // ---- 画面（とりあえず JUCE 標準のつまみ画面）----
    bool hasEditor() const override { return true; }
    juce::AudioProcessorEditor* createEditor() override { return new juce::GenericAudioProcessorEditor (*this); }

    // ---- 設定の保存・復元 ----
    void getStateInformation (juce::MemoryBlock& destData) override
    {
        if (auto xml = apvts.copyState().createXml())
            copyXmlToBinary (*xml, destData);
    }

    void setStateInformation (const void* data, int sizeInBytes) override
    {
        if (auto xml = getXmlFromBinary (data, sizeInBytes))
            if (xml->hasTagName (apvts.state.getType()))
                apvts.replaceState (juce::ValueTree::fromXml (*xml));
    }

    // ---- その他（エフェクトなので固定値）----
    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

private:
    juce::AudioProcessorValueTreeState apvts;
    std::atomic<float>* drive  = nullptr;
    std::atomic<float>* output = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreampAudioProcessor)
};

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PreampAudioProcessor();
}
