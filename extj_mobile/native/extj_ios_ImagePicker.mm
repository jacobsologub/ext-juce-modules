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

END_JUCE_NAMESPACE

//==============================================================================
@interface JuceUIImagePicker : UIImagePickerController <UINavigationControllerDelegate, UIImagePickerControllerDelegate>
{
@private
    juce::ImagePicker* owner;
}

@end

@implementation JuceUIImagePicker

- (id) initWithOwner: (juce::ImagePicker*) owner_
{
    if ((self = [super init]) != nil)
    {
        owner = owner_;
        
        self.mediaTypes = [NSArray arrayWithObject: (id) kUTTypeImage];
        self.allowsEditing = NO;
        self.delegate = self;
    }
    
    return self;
}

- (void) dealloc
{
    [super dealloc];
}

- (void) imagePickerController: (UIImagePickerController*) picker didFinishPickingMediaWithInfo: (NSDictionary*) info
{
    owner->sendImagePickerFinishedMessage (self, info);
}

- (void) imagePickerControllerDidCancel: (UIImagePickerController*) picker
{
    self.delegate = nil;
    owner->sendImagePickerCanceledMessage (self);
}

+ (UIViewController*) topLevelViewController
{
    UIResponder* responder = ((UIView*) [[UIApplication sharedApplication].keyWindow.subviews objectAtIndex: 0]).nextResponder;
    
    if ([responder isKindOfClass: [UIViewController class]])
    {
        return (UIViewController*) responder;
    }
    
    return nil;
}
@end

BEGIN_JUCE_NAMESPACE

//==============================================================================
ImagePicker::ImagePicker()
    : orientation (Up)
{
    
}

ImagePicker::~ImagePicker()
{
    
}

//==============================================================================
bool ImagePicker::isSourceAvailable (Source sourceToLookFor)
{
    return (bool) [JuceUIImagePicker isSourceTypeAvailable: (UIImagePickerControllerSourceType) sourceToLookFor];
}

StringArray ImagePicker::availableMediaTypesForSource (Source sourceToUse)
{
    NSArray* types = [JuceUIImagePicker availableMediaTypesForSourceType: (UIImagePickerControllerSourceType) sourceToUse];
    StringArray availableTypes;
    
    for (NSString* mediaType in types) 
    {
        availableTypes.add (CharPointer_UTF8 ([mediaType UTF8String]));
    }
    
    return availableTypes;
}

//==============================================================================
void ImagePicker::addListener (Listener* const newListener)
{
    listeners.add (newListener);
}

void ImagePicker::removeListener (Listener* const listener)
{
    listeners.remove (listener);
}

//==============================================================================
void ImagePicker::show (Source sourceToUse)
{    
    UIViewController* controller = [JuceUIImagePicker topLevelViewController];
    
    if (controller != nil)
    {
        JuceUIImagePicker* imagePicker = [[JuceUIImagePicker alloc] initWithOwner: this];
        imagePicker.sourceType = (UIImagePickerControllerSourceType) sourceToUse;
        [controller presentModalViewController: imagePicker animated: YES];
    }
}

//==============================================================================
void ImagePicker::saveToPhotosAlbum (const Image& imageToSave)
{
    JPEGImageFormat jpgff;
    MemoryOutputStream mos;
    jpgff.writeImageToStream (imageToSave, mos);
    
    UIImage* im = [UIImage imageWithData: [NSData dataWithBytes: mos.getData() length: mos.getDataSize()]];
    UIImageWriteToSavedPhotosAlbum (im, nil, nil, nil);
}

//==============================================================================
void ImagePicker::sendImagePickerFinishedMessage (void* picker_, void* info)
{
    UIViewController* controller = [JuceUIImagePicker topLevelViewController];
    
    if (controller != nil)
    {
        [controller dismissModalViewControllerAnimated: YES];
        
        JuceUIImagePicker* imagePicker = (JuceUIImagePicker*) picker_;
        [imagePicker release];
    }
    
    NSDictionary* dictionary = (NSDictionary*) info;
    
    NSString* mediaType = [dictionary objectForKey: UIImagePickerControllerMediaType];
    UIImage* originalImage = nil;
    
    if (CFStringCompare ((CFStringRef) mediaType, kUTTypeImage, 0) == kCFCompareEqualTo) 
    {
        originalImage = (UIImage*) [dictionary objectForKey: UIImagePickerControllerOriginalImage];
    }
    
    if (CFStringCompare ((CFStringRef) mediaType, kUTTypeMovie, 0) == kCFCompareEqualTo)
    {
        // Intentionally empty..
    }
    
    NSData* data = UIImageJPEGRepresentation (originalImage, 1.0f);
    Image im = ImageFileFormat::loadFrom (data.bytes, data.length);
    orientation = (Orientation) originalImage.imageOrientation;
    
    int originalH = im.getHeight();
    int originalW = im.getWidth();
    AffineTransform transform = AffineTransform::identity;
    
    if (orientation == ImagePicker::Right)
    {
        swapVariables<int> (originalH, originalW);
        transform = AffineTransform::rotation (float_Pi * 0.50f).translated (originalW, 0.0f);        
    }
    else if (orientation == ImagePicker::Down)
    {        
        transform = AffineTransform::rotation (float_Pi * 1.00f).translated (originalW, originalH);
    }
    else if (orientation == ImagePicker::Left)
    {
        swapVariables<int> (originalH, originalW);
        transform = AffineTransform::rotation (float_Pi * -0.50f).translated (0, originalH);
    }
    
    Image ti (Image::ARGB, originalW, originalH, true);
    Graphics g (ti);
    g.addTransform (transform);
    g.drawImageAt (im, 0, 0);
    im = ti;
    
    listeners.call (&Listener::imagePickerFinished, im);
}

void ImagePicker::sendImagePickerCanceledMessage (void* picker_)
{
    UIViewController* controller = [JuceUIImagePicker topLevelViewController];
    
    if (controller != nil)
    {
        [controller dismissModalViewControllerAnimated: YES];
        
        JuceUIImagePicker* imagePicker = (JuceUIImagePicker*) picker_;
        [imagePicker release];
    }
}