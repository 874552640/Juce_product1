/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 13 Feb 2024 4:11:11pm
    Author:  87209

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");
    trackTitles.push_back("Track 7");
    trackTitles.push_back("Track 8");
    trackTitles.push_back("Track 9");
    trackTitles.push_back("Track 10");
    trackTitles.push_back("Track 11");
    trackTitles.push_back("Track 12");
    trackTitles.push_back("Track 13");
    trackTitles.push_back("Track 14");
    trackTitles.push_back("Track 15");
    trackTitles.push_back("Track 16");
    trackTitles.push_back("Track 17");
    trackTitles.push_back("Track 18");
    trackTitles.push_back("Track 19");
    trackTitles.push_back("Track 20"); 
    trackTitles.push_back("Track 21");
    trackTitles.push_back("Track 22");
    trackTitles.push_back("Track 23");
    trackTitles.push_back("Track 24");
    trackTitles.push_back("Track 25");
    trackTitles.push_back("Track 26");
    

    tableComponent.getHeader().addColumn("Track title", 1, 150);
    tableComponent.getHeader().addColumn("Play", 2, 115);
    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
}


PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows() {
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) {
    if (rowIsSelected) {
        g.fillAll(Colours::orange);
    }
    else {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
    g.drawText(trackTitles[rowNumber], 2, 0, width - 4, height, Justification::centredLeft, true);
}

void PlaylistComponent::buttonClicked(Button* button) {
    int id = std::stoi(button->getComponentID().toStdString());
    std::cout << "PlaylistComponent::buttonClicked trackTitles id: " << trackTitles[id] << std::endl;
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) {
    if (columnId == 2) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{ "play" };
            btn->addListener(this);
            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);

            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}