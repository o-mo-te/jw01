#pragma once

#include <JuceHeader.h>
#include "JW01AudioProcessor.h"
#include "NotificationName.h"

class JW01AudioProcessorEditor : public juce::AudioProcessorEditor {
    
    public:
    JW01AudioProcessorEditor(JW01AudioProcessor&);
    ~JW01AudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void resized() override;

    private:
    JW01AudioProcessor& processor;
    juce::Label overdriveLabel;
    juce::Label gainLabel;
    juce::Slider overdriveSlider;
    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> overdriveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JW01AudioProcessorEditor)
};
