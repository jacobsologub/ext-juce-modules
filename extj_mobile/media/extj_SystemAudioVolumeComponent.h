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

#ifndef __EXTJ_SYSTEM_AUDIO_VOLUME_COMPONENT_EXTJHEADER__
#define __EXTJ_SYSTEM_AUDIO_VOLUME_COMPONENT_EXTJHEADER__

#if JUCE_IOS || DOXYGEN

//==============================================================================
/**
    An iOS specific component that displays the systme volume view MPVolumeView.
*/
class SystemAudioVolumeComponent : public Component
{
public:
    /**	Creates a SystemAudioVolumeComponent. */
    SystemAudioVolumeComponent();
    
    /** Destructor. */
    ~SystemAudioVolumeComponent();
    
    //==============================================================================
    /**	Sets whether or not to show the volume slider in the volume view. The 
        volume slider is visible by default.
     
        @see 
    */
    void setShowsVolumeSlider (bool shouldShowVolumeSlider);
    
    /**	Retruns a value indicating whether or not the volume slider is shown.
        
        @see setShowsVolumeSlider
    */
    bool getShowsVolumeSlider() const;
    
    /**	Sets whether or not to show the route button in the volume view. The 
        route button is visible by default when there is more than one audio 
        output route available.
     
        @see 
    */
    void setShowsRouteButton (bool shouldShowRouteButton);
    
    /**	Retruns a value indicating whether or not the route button is shown.
     
        @see setShowsRouteButton
    */
    bool getShowsRouteButton() const;
    
    /** @internal */
    void resized();
private:
    UIViewComponent embededView;
};

//==============================================================================
/**	
    Functions for use in displaying and hiding volume controls inside an
    alert window.
 */
class SystemAudioVolumeAlert
{
public:
    /**	Displays an alert panel for controlling the system volume.
     
        @see SystemAudioVolumeComponent::hide, SystemAudioVolumeComponent::visible
    */
    static void show();
    
    /**	Hides the alert panel that controls the system volume.
     
        @see SystemAudioVolumeComponent::hide, SystemAudioVolumeComponent::visible
    */
    static void hide();
    
    /**	Returns a boolean value indicating whether the volume alert panel is
        currently visible.
     
        @see SystemAudioVolumeComponent::show, SystemAudioVolumeComponent::hide
    */
    static bool visible();
};

#endif
#endif   // __EXTJ_SYSTEM_AUDIO_VOLUME_COMPONENT_EXTJHEADER__
