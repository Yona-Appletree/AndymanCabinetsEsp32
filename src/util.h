//
// Created by Yona Appletree on 1/24/20.
//

#ifndef ANDYMANCABINETSESP32_UTIL_H
#define ANDYMANCABINETSESP32_UTIL_H

#endif //ANDYMANCABINETSESP32_UTIL_H

/**
 * Maps a value from an input range to an output range without clamping to the given min and max values.
 *
 * @param x
 * @param in_min
 * @param in_max
 * @param out_min
 * @param out_max
 * @return
 */
double mapd(double x, double in_min, double in_max, double out_min, double out_max);

/**
 * Maps a value from an input range to an output range, clamping the value to ensure it doesn't go out of range.
 * @param x
 * @param in_min
 * @param in_max
 * @param out_min
 * @param out_max
 * @return
 */
double mapdClamp(double x, double in_min, double in_max, double out_min, double out_max);


double triangle(double input);