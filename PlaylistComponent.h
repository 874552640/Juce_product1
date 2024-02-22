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
//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component, public TableListBoxModel, public Button::Listener,public FileDragAndDropTarget
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;

    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

private:
    TableListBox tableComponent;
    std::vector<std::string> trackTitles;
    bool isInterestedInFileDrag(const StringArray &file) override;
    void filesDropped (const StringArray &files, int x, int y) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
