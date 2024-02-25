/*
  ==============================================================================

    PlaylistComponent.h
    Created: 13 Feb 2024 4:11:11pm
    Author:  87209

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DJAudioPlayer.h"
//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component, public TableListBoxModel, public Button::Listener,public FileDragAndDropTarget,public Timer
{
public:
    PlaylistComponent(DJAudioPlayer* player,AudioFormatManager &formatManager);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;

    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    void addTrackToList(std::vector<String> &trackTitles,const juce::String &fileName,const File &file);
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    void playNextTrack();
    
    void transportSourceStopped()
        {
            // Logic to play the next track
            playNextTrack();
        }

private:
    struct TrackInfo
        {
            String title;
            File file;
        };
    TableListBox tableComponent;
    std::vector<String> trackTitles;
    std::vector<TrackInfo> trackVector;
    bool isInterestedInFileDrag(const StringArray &file) override;
    void filesDropped (const StringArray &files, int x, int y) override;
    
    void playList();
    int currentTrackIndex = 0; // 当前播放的曲目索引
    TextButton playSequenceButton; // 顺序播放按钮
    
   
    
    AudioFormatManager formatManager;

    DJAudioPlayer* player;
    
    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
