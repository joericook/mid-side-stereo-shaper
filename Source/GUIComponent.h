/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_9789856CF44A38A8__
#define __JUCE_HEADER_9789856CF44A38A8__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"

class MidSideStereoShaperAudioProcessor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GUIComponent  : public Component,
                      public LookAndFeel_V3,
                      public SliderListener
{
public:
    //==============================================================================
    GUIComponent (MidSideStereoShaperAudioProcessor* P);
    ~GUIComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
		float /*sliderPos*/,
		float /*minSliderPos*/,
		float /*maxSliderPos*/,
		const Slider::SliderStyle /*style*/, Slider& slider);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* guibackground_png;
    static const int guibackground_pngSize;
    static const char* faderBackground_png;
    static const int faderBackground_pngSize;
    static const char* faderHandle_png;
    static const int faderHandle_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MidSideStereoShaperAudioProcessor* processor;

	Image imgFaderBackground;
	Image imgFaderHandle;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> MidGain;
    ScopedPointer<Slider> SideGain;
    ScopedPointer<Slider> PostGain;
    Image cachedImage_guibackground_png_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_9789856CF44A38A8__
