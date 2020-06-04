/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidSideStereoShaperAudioProcessor::MidSideStereoShaperAudioProcessor()
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
	//Set the initial values for the plugin parameters
	midGain = 1.0;
	sideGain = 1.0;
	postGain = 1.0;
}

MidSideStereoShaperAudioProcessor::~MidSideStereoShaperAudioProcessor()
{
}

//==============================================================================
const String MidSideStereoShaperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidSideStereoShaperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidSideStereoShaperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double MidSideStereoShaperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidSideStereoShaperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidSideStereoShaperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidSideStereoShaperAudioProcessor::setCurrentProgram (int index)
{
}

const String MidSideStereoShaperAudioProcessor::getProgramName (int index)
{
    return String();
}

void MidSideStereoShaperAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidSideStereoShaperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MidSideStereoShaperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidSideStereoShaperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MidSideStereoShaperAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	for (int i = 0; i < buffer.getNumSamples(); i++)
	{
		float* lChannel = buffer.getWritePointer(0);
		float* rChannel = buffer.getWritePointer(1);

		//Create temporary values for mid and side channel encoding
		//Mid = L + R
		float midChannel = lChannel[i] + rChannel[i];
		//Side = L - R
		float sideChannel = lChannel[i] - rChannel[i];

		//Apply gain to mid and side variables
		midChannel *= midGain;
		sideChannel *= sideGain;

		//Left and Right decoding
		//Left = (S + M) * 0.5
		lChannel[i] = (sideChannel + midChannel) * 0.5;
		//Right = (M - S) * 0.5
		rChannel[i] = (midChannel - sideChannel) * 0.5;

		//Apply Post gain to left and right channels
		lChannel[i] *= postGain;
		rChannel[i] *= postGain;
	}
}

//==============================================================================
bool MidSideStereoShaperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidSideStereoShaperAudioProcessor::createEditor()
{
    return new MidSideStereoShaperAudioProcessorEditor (*this);
}

//==============================================================================
void MidSideStereoShaperAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidSideStereoShaperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidSideStereoShaperAudioProcessor();
}
