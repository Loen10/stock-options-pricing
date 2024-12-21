These are some stock options pricing calculators made with C++.
Currently includes the Black-Scholes-Merton pricing model which utilizes the
standard normal cumulative distribution function. The C++ standard library
does not have such a function but it can be derived from the error function
within the standard library.

This version calculates a more precise time to expiration by finding the
difference in years between the current time and the option's expiration date.
This was done using the ctime library as I'm still hesitant to use C++20
features and I don't want to rely on any external libraries.
