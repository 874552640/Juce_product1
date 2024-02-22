/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
                
                 
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse),transportSource()
{
    formatManager.registerBasicFormats();
    volumeLabel.setText("Volume: 0", dontSendNotification);
    speedLabel.setText("1 x", dontSendNotification);
    
    nameLabel.setText("SONG NAME",dontSendNotification);
    addAndMakeVisible(nameLabel);

    addAndMakeVisible(volumeLabel);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(recordButton);
    
    
       
    addAndMakeVisible(volumeKnob);
    addAndMakeVisible(speedKnob);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(waveformDisplay);


    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    recordButton.addListener(this);

    volumeKnob.addListener(this);
    speedKnob.addListener(this);
    posSlider.addListener(this);


    volumeKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumeKnob.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    volumeKnob.setRange(0.0, 1.0, 0.01);
    speedKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedKnob.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    speedKnob.setRange(0.1, 3.0, 0.1);
    
    
//    posSlider.setRange(0.0, 1.0);

    startTimer(500);
    


}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightyellow);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8; 
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);  
    recordButton.setBounds(getWidth()/2, rowH * 7, getWidth() / 2, rowH);
    volumeKnob.setBounds(0, rowH * 2.3, getWidth()/2, rowH *1.5);
    volumeLabel.setBounds(0, rowH * 3.8, getWidth()/2, 20);
    speedKnob.setBounds(getWidth()/2, rowH * 2.3, getWidth()/2, rowH*1.5);
    speedLabel.setBounds(165, rowH * 3.8, getWidth()/2, 20);
    posSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
    loadButton.setBounds(0, rowH * 7, getWidth()/2, rowH);

    const Font& font=nameLabel.getFont();
    int textWidth = font.getStringWidth("SONG NAME");
    nameLabel.setBounds((getWidth()-textWidth)/2, rowH * 2.1, getWidth(), 20);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
       if (!player->isPlaying())
        {
            
            player->start();
            waveformDisplay.updatePlaybackState(true);
            
        }
        else
        {
            
            player->stop();
            waveformDisplay.updatePlaybackState(false);
            
            
        }
    }
     if (button == &stopButton)
    {
        
        player->setPosition(0);


    }
       if (button == &loadButton)
    {
        auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            
            File fileSelected = chooser.getResult();
            player->loadURL(URL{chooser.getResult()});
            // and now the waveformDisplay as well
            waveformDisplay.loadURL(URL{chooser.getResult()});
            
//            formatManager.registerBasicFormats();

            AudioFormatReader* reader = formatManager.createReaderFor(fileSelected);

            
            
            if (reader != nullptr)
            {
                totalLength = reader->lengthInSamples / reader->sampleRate;
                posSlider.setRange(0.0, totalLength,0.1);
            }
            
            nameLabel.setText(fileSelected.getFileName(), dontSendNotification);
            const Font& font=nameLabel.getFont();
            int textWidth = font.getStringWidth(fileSelected.getFileName());
            
            Rectangle<int> labelBounds = nameLabel.getBounds();
            labelBounds.setX((getWidth()-textWidth)/2);
            
            nameLabel.setBounds(labelBounds);
            
        });
    }
    // if (button == &loadButton)
    // {
    //     FileChooser chooser{"Select a file..."};
    //     if (chooser.browseForFileToOpen())
    //     {
    //         player->loadURL(URL{chooser.getResult()});
    //         waveformDisplay.loadURL(URL{chooser.getResult()});
            
    //     }


    // }
       /*if (button == &recordButton) {
           if (!isRecording) {
               // Start recording
               isRecording = true;
               recordButton.setButtonText("Stop Recording");
               // Add your recording start logic here
           }
           else {
               // Stop recording
               isRecording = false;
               recordButton.setButtonText("Record");
               // Add your recording stop logic here
           }
       }*/
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volumeKnob)
    {
        player->setGain(slider->getValue());
        volumeLabel.setText("Volume: " + String(slider->getValue()), dontSendNotification);
    }

    if (slider == &speedKnob)
    {
        player->setSpeed(slider->getValue());
        speedLabel.setText("Speed: " + String(slider->getValue()), dontSendNotification);
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue()/totalLength);
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
    waveformDisplay.loadURL(URL{File{files[0]}});
    AudioFormatReader* reader = formatManager.createReaderFor(files[0]);
      totalLength = reader->lengthInSamples / reader->sampleRate;
      posSlider.setRange(0.0, totalLength,0.1);
      File file(files[0]);
      nameLabel.setText(file.getFileName(), dontSendNotification);
      const Font& font=nameLabel.getFont();
      int textWidth = font.getStringWidth(file.getFileName());
      
      Rectangle<int> labelBounds = nameLabel.getBounds();
      labelBounds.setX((getWidth()-textWidth)/2);
      
      nameLabel.setBounds(labelBounds);
      
  }
}

void DeckGUI::timerCallback()
{

    if (player->isPlaying())
        {
            // 获取当前播放位置（百分比）
            double position = player->getPositionRelative();
            // 根据播放位置设置 waveformDisplay 的值
            waveformDisplay.setPositionRelative(position);
            posSlider.setValue(position*totalLength, dontSendNotification);
        }
}





