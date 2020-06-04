/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidSideStereoShaperAudioProcessorEditor::MidSideStereoShaperAudioProcessorEditor (MidSideStereoShaperAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), myGUI(&p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 250);

	addAndMakeVisible(&myGUI);
}

MidSideStereoShaperAudioProcessorEditor::~MidSideStereoShaperAudioProcessorEditor()
{
}

//==============================================================================
void MidSideStereoShaperAudioProcessorEditor::paint (Graphics& g)
{
	//Unneccesary code to be overwritten by GUI Component.
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void MidSideStereoShaperAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	myGUI.setBounds(0, 0, getWidth(), getHeight());
}
