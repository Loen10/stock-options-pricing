These are some stock options pricing calculators made with C++. I originally started making this in Go, because of it's simplicity but I'm just so used to C++ it feels awkward.
The C++ version calculates a more precise time to expiration by finding the difference in years between the current time and the option's expiration date. This was done
using the ctime library as I'm still hesitant to use C++20 features and I don't want to rely on any external libraries.
