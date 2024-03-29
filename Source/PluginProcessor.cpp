/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicAudioPlayerv2AudioProcessor::BasicAudioPlayerv2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	formatManager.registerBasicFormats();
}

BasicAudioPlayerv2AudioProcessor::~BasicAudioPlayerv2AudioProcessor()
{
}

//==============================================================================
const String BasicAudioPlayerv2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicAudioPlayerv2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicAudioPlayerv2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicAudioPlayerv2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicAudioPlayerv2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicAudioPlayerv2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicAudioPlayerv2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicAudioPlayerv2AudioProcessor::setCurrentProgram (int index)
{
}

const String BasicAudioPlayerv2AudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicAudioPlayerv2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BasicAudioPlayerv2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BasicAudioPlayerv2AudioProcessor::releaseResources()
{
	transportSource.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicAudioPlayerv2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BasicAudioPlayerv2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	transportSource.getNextAudioBlock(AudioSourceChannelInfo(buffer));
}

//==============================================================================
bool BasicAudioPlayerv2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BasicAudioPlayerv2AudioProcessor::createEditor()
{
    return new BasicAudioPlayerv2AudioProcessorEditor (*this);
}

//==============================================================================
void BasicAudioPlayerv2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicAudioPlayerv2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void BasicAudioPlayerv2AudioProcessor::loadFileIntoTransport()
{
	//choose a file
	FileChooser chooser("Choose a Wav or AIFF File", File::getSpecialLocation(File::userDesktopDirectory), "*.wav; *.mp3");

	//if the user chooses a file
	if (chooser.browseForFileToOpen())
	{
		File myFile;

		//what did the user choose?
		myFile = chooser.getResult();

		//read the file
		AudioFormatReader* reader = formatManager.createReaderFor(myFile);

		if (reader != nullptr)
		{
			//get the file ready to play
			std::unique_ptr<AudioFormatReaderSource> tempSource(new AudioFormatReaderSource(reader, true));

			transportSource.setSource(tempSource.get());
			// changeState(Stopped);

			readerSource.reset(tempSource.release());
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicAudioPlayerv2AudioProcessor();
}
