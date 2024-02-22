/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    void timerCallback() override; 

private:

    TextButton playButton{"PLAY/STOP"};
    TextButton stopButton{"RESTART"};
    TextButton loadButton{"LOAD"};
    TextButton recordButton{"RECORD"};
  
    Slider volumeKnob;
    Slider speedKnob;
    Slider posSlider;

    Label volumeLabel;
    Label speedLabel;
    Label nameLabel;

    FileChooser fChooser{"Select a file..."};


    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player;
    AudioTransportSource transportSource;
    AudioFormatManager formatManager;
    double totalLength;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
