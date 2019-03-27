/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BasicAudioPlayerv2AudioProcessorEditor  : public AudioProcessorEditor,
												public ChangeListener
{
public:
    BasicAudioPlayerv2AudioProcessorEditor (BasicAudioPlayerv2AudioProcessor&);
    ~BasicAudioPlayerv2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BasicAudioPlayerv2AudioProcessor& processor;

	void openButtonClicked();
	void playButtonClicked();
	void stopButtonClicked();

	void changeState(TransportState newState);
	void changeListenerCallback(ChangeBroadcaster *source) override;

	TransportState state;

	TextButton openButton;
	TextButton playButton;
	TextButton stopButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicAudioPlayerv2AudioProcessorEditor)
};
