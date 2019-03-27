/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "TransportState.h"

//==============================================================================
BasicAudioPlayerv2AudioProcessorEditor::BasicAudioPlayerv2AudioProcessorEditor (BasicAudioPlayerv2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);

	openButton.setButtonText("Open...");
	openButton.onClick = [this] { openButtonClicked(); };
	addAndMakeVisible(&openButton);

	playButton.setButtonText("Play");
	playButton.onClick = [this] { playButtonClicked(); };
	playButton.setColour(TextButton::buttonColourId, Colours::green);
	playButton.setEnabled(true);
	addAndMakeVisible(&playButton);


	stopButton.setButtonText("Stop");
	stopButton.onClick = [this] { stopButtonClicked(); };
	stopButton.setColour(TextButton::buttonColourId, Colours::red);
	stopButton.setEnabled(false);
	addAndMakeVisible(&stopButton);

	processor.transportSource.addChangeListener(this);
}

BasicAudioPlayerv2AudioProcessorEditor::~BasicAudioPlayerv2AudioProcessorEditor()
{
}

//==============================================================================
void BasicAudioPlayerv2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void BasicAudioPlayerv2AudioProcessorEditor::resized()
{
	openButton.setBounds(10, 10, getWidth() - 20, 30);
	playButton.setBounds(10, 50, getWidth() - 20, 30);
	stopButton.setBounds(10, 90, getWidth() - 20, 30);
}

void BasicAudioPlayerv2AudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &processor.transportSource)
	{
		if (processor.transportSource.isPlaying())
			changeState(Playing);
		else
			changeState(Stopped);
	}
}

void BasicAudioPlayerv2AudioProcessorEditor::changeState(TransportState newState)
{
	if (newState != state)
	{
		state = newState;

		switch (state) {
		case Stopped:
			playButton.setEnabled(true);
			processor.transportSource.setPosition(0.0);
			break;

		case Playing:
			playButton.setEnabled(true);
			break;

		case Starting:
			stopButton.setEnabled(true);
			playButton.setEnabled(false);
			processor.transportSource.start();
			break;

		case Stopping:
			playButton.setEnabled(true);
			stopButton.setEnabled(false);
			processor.transportSource.stop();
			break;
		}
	}
}

void BasicAudioPlayerv2AudioProcessorEditor::openButtonClicked()
{
	processor.loadFileIntoTransport();
}

void BasicAudioPlayerv2AudioProcessorEditor::playButtonClicked()
{
	changeState(Starting);
}

void BasicAudioPlayerv2AudioProcessorEditor::stopButtonClicked()
{
	changeState(Stopping);
}
