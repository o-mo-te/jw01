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
    juce::Slider overdriveSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> overdriveAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JW01AudioProcessorEditor)
};
