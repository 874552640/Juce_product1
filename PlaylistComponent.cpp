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
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _player,AudioFormatManager &  formatManager): player(_player)
{
//    formatManager.registerBasicFormats();
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
//    trackTitles.push_back("Track 1");
//    trackTitles.push_back("Track 2");
//    trackTitles.push_back("Track 3");
//    trackTitles.push_back("Track 4");
//    trackTitles.push_back("Track 5");
//    trackTitles.push_back("Track 6");
//    trackTitles.push_back("Track 7");
//    trackTitles.push_back("Track 8");
//    trackTitles.push_back("Track 9");
//    trackTitles.push_back("Track 10");
//    trackTitles.push_back("Track 11");
//    trackTitles.push_back("Track 12");
//    trackTitles.push_back("Track 13");
//    trackTitles.push_back("Track 14");
//    trackTitles.push_back("Track 15");
//    trackTitles.push_back("Track 16");
//    trackTitles.push_back("Track 17");
//    trackTitles.push_back("Track 18");
//    trackTitles.push_back("Track 19");
//    trackTitles.push_back("Track 20");
//    trackTitles.push_back("Track 21");
//    trackTitles.push_back("Track 22");
//    trackTitles.push_back("Track 23");
//    trackTitles.push_back("Track 24");
//    trackTitles.push_back("Track 25");
//    trackTitles.push_back("Track 26");
//

    tableComponent.getHeader().addColumn("Track title", 1, 150);
    tableComponent.getHeader().addColumn("Play", 2, 115);
    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
    
    
    addAndMakeVisible(playSequenceButton);
    playSequenceButton.setButtonText("Play Sequence/Stop");
    playSequenceButton.addListener(this);
    
    
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
    playSequenceButton.setBounds(0, getHeight()-30, getWidth(), 30);
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
//    int id = std::stoi(button->getComponentID().toStdString());
//    std::cout << "PlaylistComponent::buttonClicked trackTitles id: " << trackTitles[id] << std::endl;
//    std::cout << "URL:" << URL{trackVector[id].file}.toString(false) << std::endl;
        

//    if (player->isPlaying()) {
//            // 停止播放器
//            player->stop();
//
//            // 设置按钮文本为 "Play"
//            button->setButtonText("Play");
//        } else {
//            // 如果播放器没有播放，则开始播放
//            player->loadURL(URL{trackVector[id].file});
//            player->start();
//
//            // 设置按钮文本为 "Stop"
//            button->setButtonText("Stop");
//        }
    if (button == &playSequenceButton)
        {
            if(Timer::isTimerRunning()){
                stopTimer();
                player->stop();
            }else{
                // 开始播放顺序
                currentTrackIndex=0;
                startTimer(1000);
            }
            
            
        }
        else
        {
            stopTimer();
            player->stop();
            
            int index = button->getComponentID().getIntValue();
            currentTrackIndex=index;
            if (index >= 0 && index < trackVector.size())
            {
                player->loadURL(URL{trackVector[index].file});
                player->start();
//                playList();
                
                
                    
            }
        }
    
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
bool PlaylistComponent::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "isInterestedInFileDrag" << std::endl;
  return true;
}

void PlaylistComponent::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "filesDropped" << std::endl;
  if (files.size() == 1)
  {
      
//    player->loadURL(URL{File{files[0]}});
      File droppedFile(files[0]);
      String fileName = droppedFile.getFileName();
//      std::cout << "Dropped file name: " << fileName << std::endl;
      String path=droppedFile.getFullPathName();
      std::cout << "Dropped file path: " << path << std::endl;
      addTrackToList(trackTitles,fileName,droppedFile);
  }
}


void PlaylistComponent::addTrackToList(std::vector<String> &trackTitles,const String &fileName,const File &file)
{
    trackTitles.push_back(fileName);
    std::cout << "Dropped file name: " << fileName << std::endl;
    
    TrackInfo newTrackInfo;
    newTrackInfo.title = fileName;
    newTrackInfo.file=file;
    trackVector.push_back(newTrackInfo);
    
    tableComponent.updateContent();
}
    
    
//void PlaylistComponent::playList()
//{
//    while(currentTrackIndex < trackVector.size())
//    {
//        player->loadURL(URL{trackVector[currentTrackIndex].file});
//        player->start();
//
//
//        // 等待当前歌曲播放完成
//        while (player->isPlaying())
//        {
//            // 检查播放位置是否达到了文件末尾
//            if (player->getPositionRelative() ==1){
//
//                player->releaseResources();
//                break;
//            }
//
//
//        }
//
//
//        ++currentTrackIndex;
//    }
//}


void PlaylistComponent::timerCallback()
    {
        // 如果当前歌曲正在播放，直接返回，等待播放完成
        if (player->isPlaying())
            return;

        // 如果播放列表中还有歌曲
        if (currentTrackIndex < trackVector.size())
        {
            // 加载并播放下一首歌曲
            player->loadURL(URL{trackVector[currentTrackIndex].file});
            player->start();

            // 更新当前歌曲索引
            ++currentTrackIndex;
        }
        else
        {
            // 播放列表已经播放完毕，停止定时器
            stopTimer();
        }
    }
