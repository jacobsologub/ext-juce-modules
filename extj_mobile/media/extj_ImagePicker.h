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

#ifndef __EXTJ_IMAGE_PICKER_EXTJHEADER__
#define __EXTJ_IMAGE_PICKER_EXTJHEADER__

#if JUCE_IOS || DOXYGEN

//==============================================================================
/**	ImagePicker class
 
    An iOS-specific class that can ne used for choosing saved images on 
    supported devices.
 */
class ImagePicker
{    
public:
    ImagePicker();
    ~ImagePicker();
    
    //==============================================================================
    /**	Source enum
        
        The source to use when picking an image or when determining available 
        media types.
     */
    enum Source
    {
        PhotoLibrary,
        Camera,
        SavedPhotosAlbum    
    };
    
    /**	Returns a value indicating whether the device supports picking media 
        using the specified source type.
     
        @see Source
     */
    static bool isSourceAvailable (Source sourceToLookFor);
    
    /**	Returns an array of the available media types for the specified source.
        
        @see @see Source, isSourceAvailable
     */
    static StringArray availableMediaTypesForSource (Source sourceToUse);
    
    //==============================================================================
    /** A class for receiving callbacks from a ImagePicker.
     
        To be told when a image picker changes, you can register a 
        ImagePicker::Listener object using ImagePicker::addListener().
     
        @see ImagePicker::addListener, ImagePicker::removeListener
     */
    class JUCE_API  Listener
    {
    public:
        /** Destructor. */
        virtual ~Listener() {}
        
        //==============================================================================
        /** Called when the image picker has finished loading the selected 
            image.
         
            @see ImagePicker::imagePickerCanceled
         */
        virtual void imagePickerFinished (const Image& image) = 0;
        
        /** Called when the image picker has been canceled by the user.
         
            @see ImagePicker::imagePickerFinished
         */
        virtual void imagePickerCanceled()  {}
    };
    
    /**	Description
        
        @see removeListener
     */
    void addListener (Listener* newListener);
    
    /**	Description

    	@see addListener
     */
    void removeListener (Listener* listener);
    
    //==============================================================================
    /**	Shows the image picker user interface.
     
        @see saveToPhotosAlbum
     */
    void show (Source sourceToUse = SavedPhotosAlbum);
    
    //==============================================================================
    /**	Adds the specified image to the user’s Camera Roll album.
        
        @see show
     */
    void saveToPhotosAlbum (const Image& imageToSave);
    
    //==============================================================================
    /**	@internal */
    void sendImagePickerFinishedMessage (void* picker, void* info);
    
    /**	@internal */
    void sendImagePickerCanceledMessage (void* picker);
    
private:
    ListenerList <Listener> listeners;
    
    //==============================================================================
    /**	Orientation enum
     
        Specifies the possible orientations of an image.
     */
    enum Orientation
    {
        Up,            // default orientation
        Down,          // 180 deg rotation
        Left,          // 90 deg CCW
        Right,         // 90 deg CW
        UpMirrored,    // as above but image mirrored along other axis. horizontal flip
        DownMirrored,  // horizontal flip
        LeftMirrored,  // vertical flip
        RightMirrored, // vertical flip
    };
    
    Orientation orientation;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImagePicker);
};

#endif
#endif   // __EXTJ_IMAGE_PICKER_EXTJHEADER__
