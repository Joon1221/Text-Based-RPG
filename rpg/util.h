#ifndef UTIL_H
#define UTIL_H

//==============================================================================
// Process Key Input
//==============================================================================

int _kbhit(void);

//==============================================================================
// Measure time difference
//==============================================================================

/**
 * Returns the real time, in seconds, or -1.0 if an error occurred.
 *
 * Time is measured since an arbitrary and OS-dependent start time.
 * The returned real time is only useful for computing an elapsed time
 * between two calls to this function.
 */
double getRealTime();

#endif
