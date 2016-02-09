# STATUS: POSSIBLY WORKING
It compiles without errors. Some conversion functions, multiply, and sine have been tested for the `lfix_t` type.


# AVRFIX -- A fixed point math library for Arduino
Original authors: Maximilian Rosenblattl and Andreas Wolf. 
Their work may be found [here](http://avrfix.sourceforge.net/).

Their library was meant to be compiled as a static `.a` file. Arduino doesn't have the ability to include pre-built `.a` files as libraries. I am in the process of porting the code to be compatible with Arduino.

I am also fixing several bugs.

# Functions
* type conversions
* multiplication
* division
* absolute value
* rounding
* countls (What is this? I don't know yet.)
* square root
* sine/cosine/tangent
* arctangent/arctangent2
* log 2/e/10

The source library is missing exponentiation. Hopefully someone can find the time to add it.

# Usage
I'm not totally sure yet how everything works, but I have one example sketch. 

# TODO:
* Verification/testing -- do the functions actually work?
* Profiling -- is this actually faster than floating point math? 
* Implement exponentiation -- `exp` is love. `exp` is life.