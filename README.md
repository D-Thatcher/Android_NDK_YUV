# Android_NDK_YUV
A comparison of several NDK methods that convert a YUV encoded image to RGBA format

<br>
To reference these native methods in an Activity (Java), declare the method you wish to call inside the class
<br> 


`public native String getMyString();
` 
<br> 
and load the library that contains that method
<br> 
`
static {
        System.loadLibrary("native");
    }
`

<br>
These declarations should occur in-line with in your class' private member variables
<br>
