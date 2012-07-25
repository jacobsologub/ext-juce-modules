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

#if defined (__EXTJ_IMAGE_PICKER_EXTJHEADER__)
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of Ext-JUCE cpp file"
#endif

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"

#include "../juce_core/native/juce_BasicNativeHeaders.h"
#include "extj_mobile.h"

//==============================================================================
#if JUCE_MAC
#elif JUCE_IOS

//==============================================================================
#elif JUCE_WINDOWS
 #if JUCE_WEB_BROWSER
 #endif

//==============================================================================
#elif JUCE_LINUX
#endif

//==============================================================================
// START_AUTOINCLUDE
// END_AUTOINCLUDE

using namespace juce;

namespace juce
{

//==============================================================================
#if JUCE_MAC || JUCE_IOS
 #if JUCE_MAC
 #endif

 #if JUCE_IOS
  #include "native/extj_ios_ImagePicker.mm"
 #endif

 #if JUCE_WEB_BROWSER
 #endif

//==============================================================================
#elif JUCE_WINDOWS

//==============================================================================
#elif JUCE_LINUX

//==============================================================================
#elif JUCE_ANDROID
#endif

}
