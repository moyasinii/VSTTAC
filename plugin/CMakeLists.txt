cmake_minimum_required(VERSION 3.22)
project(PreampPlugin VERSION 0.1.0)

# JUCE をビルド時に GitHub から自動取得
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        8.0.4
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(PreampPlugin
    COMPANY_NAME             "moyasinii"
    PLUGIN_MANUFACTURER_CODE Moya
    PLUGIN_CODE              Pre1
    FORMATS                  VST3
    PRODUCT_NAME             "Preamp Plugin"
    IS_SYNTH                 FALSE
    NEEDS_MIDI_INPUT         FALSE
    NEEDS_MIDI_OUTPUT        FALSE
    IS_MIDI_EFFECT           FALSE
    COPY_PLUGIN_AFTER_BUILD  FALSE
)

target_sources(PreampPlugin PRIVATE Source/PluginProcessor.cpp)
target_compile_features(PreampPlugin PRIVATE cxx_std_17)

target_compile_definitions(PreampPlugin PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(PreampPlugin
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
