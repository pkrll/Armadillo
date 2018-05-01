/**
 * @file
 * @brief Input / output library
 */

#ifndef __STDIO_H_
#define __STDIO_H_

#include <mips/adresses.h>

/**
 * Prints the string to the UART 16550 device.
 *
 * @param s The string to print out.
 */
void printk(const char* s);
/**
 * Prints a formatted string to the UART 16550 device.
 *
 * @param string 	The string to print out.
 * @param VARARGS	Additional arguments, replacing format
 * 								specifiers in string.
 */
void printf(const char *s, ...);
/**
 * Prints an 8 character string to the ASCII led board.
 *
 * @param s The string to print out.
 */
void print_to_ascii(const char *s);
/**
 * Turns on the LED lights, based on which bits
 * are set to 1 in p.
 *
 * @param p The bits to turn on.
 */
void print_to_led(const int p);
/**
 * Resets the LED display.
 */
void reset_led();

#endif
