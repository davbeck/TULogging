# TULogging

Better logging that uses ASL log levels. Based on work by Mike Weller: [http://doing-it-wrong.mikeweller.com/2012/07/youre-doing-it-wrong-1-nslogdebug-ios.html](http://doing-it-wrong.mikeweller.com/2012/07/youre-doing-it-wrong-1-nslogdebug-ios.html).

## Installation

### CocoaPods

    pod 'TULogging'

### Manually

Add the `TULogging ` subfolder to your project. There are no required libraries.

## Usage

*(See example Xcode project)*

Simply `alloc`/`init` an instance of `TUSafariActivity` and pass that object into the applicationActivities array when creating a `UIActivityViewController`.

```objectivec
TULogError(@"Could not open file: %@", fileName);
TULogWarning(@"No default image supplied.");
TULogNotice(@"Using cached result: %@", result);
TULogInfo(@"Requesting %@", requestURL);
TULogDebug(@"name: %@", name);
```

Every log is performed asynchronously on a serial background queue. This means that if you are using the debugger to step through your code, the log output will not appear immediately. But, everything will still be in order (with respect to TULog* calls). This makes logging thread safe, and won't tie up the main thread.

See the [original post](http://doing-it-wrong.mikeweller.com/2012/07/youre-doing-it-wrong-1-nslogdebug-ios.html) for more details.