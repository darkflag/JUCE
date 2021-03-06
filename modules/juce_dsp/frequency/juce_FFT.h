/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 5 End-User License
   Agreement and JUCE 5 Privacy Policy (both updated and effective as of the
   27th April 2017).

   End User License Agreement: www.juce.com/juce-5-licence
   Privacy Policy: www.juce.com/juce-5-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/


/**
    Performs a fast fourier transform.

    This is only a simple low-footprint implementation and isn't tuned for speed - it may
    be useful for simple applications where one of the more complex FFT libraries would be
    overkill. (But in the future it may end up becoming optimised of course...)

    The FFT class itself contains lookup tables, so there's some overhead in creating
    one, you should create and cache an FFT object for each size/direction of transform
    that you need, and re-use them to perform the actual operation.
*/
class JUCE_API  FFT
{
public:
    //==============================================================================
    /** Initialises an object for performing forward and inverse FFT with the given size.
        The number of points the FFT will operate on will be 2 ^ order.
    */
    FFT (int order);

    /** Destructor. */
    ~FFT();

    //==============================================================================
    /** Performs an out-of-place FFT, either forward or inverse.
        The arrays must contain at least getSize() elements.
    */
    void perform (const Complex<float> *input, Complex<float> * output, bool inverse) const noexcept;

    /** Performs an in-place forward transform on a block of real data.

        The size of the array passed in must be 2 * getSize(), and the first half
        should contain your raw input sample data. On return, the array will contain
        size complex real + imaginary parts data interleaved, and can be passed to
        performRealOnlyInverseTransform() in order to convert it back to reals.
    */
    void performRealOnlyForwardTransform (float* inputOutputData) const noexcept;

    /** Performs a reverse operation to data created in performRealOnlyForwardTransform().

        The size of the array passed in must be 2 * getSize(), containing size complex
        real and imaginary parts interleaved numbers. On return, the first half of the
        array will contain the reconstituted samples.
    */
    void performRealOnlyInverseTransform (float* inputOutputData) const noexcept;

    /** Takes an array and simply transforms it to the magnitude frequency response
        spectrum. This may be handy for things like frequency displays or analysis.
        The size of the array passed in must be 2 * getSize().
    */
    void performFrequencyOnlyForwardTransform (float* inputOutputData) const noexcept;

    /** Returns the number of data points that this FFT was created to work with. */
    int getSize() const noexcept            { return size; }

    //==============================================================================
   #ifndef DOXYGEN
    /* internal */
    struct Instance;
    template <typename> struct EngineImpl;
   #endif

private:
    //==============================================================================
    struct Engine;

    ScopedPointer<Instance> engine;
    int size;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFT)
};
