/*
  ==============================================================================
   
   Copyright (C) 2012 Jacob Sologub
   
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
  
  ==============================================================================
*/

}

#import <MediaPlayer/MediaPlayer.h>

namespace juce
{

SystemAudioVolumeComponent::SystemAudioVolumeComponent()
{
    MPVolumeView* mpv = [[MPVolumeView alloc] initWithFrame: CGRectZero];
    mpv.showsVolumeSlider = true;
    mpv.showsRouteButton = true;
    embededView.setView (mpv);
    [mpv release];
    
    addAndMakeVisible (&embededView);
}
    
SystemAudioVolumeComponent::~SystemAudioVolumeComponent()
{
    
}

void SystemAudioVolumeComponent::resized()
{
    embededView.setBounds (getLocalBounds());
    MPVolumeView* view = (MPVolumeView*) embededView.getView();
    CGSize size = [view sizeThatFits: CGSizeMake ((float) getWidth(), (float) getHeight())];
    view.frame = CGRectMake (0.0f, 0.0f, size.width, size.height);
}

//==============================================================================
void SystemAudioVolumeComponent::setShowsVolumeSlider (bool shouldShowVolumeSlider)
{
    ((MPVolumeView*) embededView.getView()).showsVolumeSlider = shouldShowVolumeSlider;
}

bool SystemAudioVolumeComponent::getShowsVolumeSlider() const
{
    return ((MPVolumeView*) embededView.getView()).showsVolumeSlider;
}

void SystemAudioVolumeComponent::setShowsRouteButton (bool shouldShowRouteButton)
{
    ((MPVolumeView*) embededView.getView()).showsRouteButton = shouldShowRouteButton;
}

bool SystemAudioVolumeComponent::getShowsRouteButton() const
{
    return ((MPVolumeView*) embededView.getView()).showsRouteButton;
}

//==============================================================================
void SystemAudioVolumeAlert::show()
{
    MPVolumeSettingsAlertShow();
}

void SystemAudioVolumeAlert::hide()
{
    MPVolumeSettingsAlertHide();
}

bool SystemAudioVolumeAlert::visible()
{
    return MPVolumeSettingsAlertIsVisible();
}