#pragma once

#include <JuceHeader.h>
#include "JW01AudioProcessor.h"

class TestAudioProcessorEditor : public juce::AudioProcessorEditor {
    public:
    TestAudioProcessorEditor(JW01AudioProcessor&);
    ~TestAudioProcessorEditor() override;
    
    void paint(juce::Graphics&) override;
    void resized() override;
    
    private:
    JW01AudioProcessor& processor;
    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestAudioProcessorEditor)
};
