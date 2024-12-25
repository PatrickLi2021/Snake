#include "mbstrings.h"

/* mbslen - multi-byte string length
 * - Description: returns the number of UTF-8 code points ("characters")
 * in a multibyte string. If the argument is NULL or an invalid UTF-8
 * string is passed, returns -1.
 *
 * - Arguments: A pointer to a character array (`bytes`), consisting of UTF-8
 * variable-length encoded multibyte code points.
 *
 * - Return: returns the actual number of UTF-8 code points in `src`. If an
 * invalid sequence of bytes is encountered, return -1.
 *
 * - Hints:
 * UTF-8 characters are encoded in 1 to 4 bytes. The number of leading 1s in the
 * highest order byte indicates the length (in bytes) of the character. For
 * example, a character with the encoding 1111.... is 4 bytes long, a character
 * with the encoding 1110.... is 3 bytes long, and a character with the encoding
 * 1100.... is 2 bytes long. Single-byte UTF-8 characters were designed to be
 * compatible with ASCII. As such, the first bit of a 1-byte UTF-8 character is
 * 0.......
 *
 * You will need bitwise operations for this part of the assignment!
 */
size_t mbslen(const char* bytes) {
    int encoding_length = 0;
    while ((unsigned char) *bytes != '\0') {
        int byte_counter = 0;
        // Length = 1
        if ((unsigned char) bytes[0] >> 7 == 0b00000000) {
            byte_counter = 1;
            encoding_length += 1;
        }
        // Length = 2
        else if ((unsigned char) bytes[0] >> 5 == 0b00000110) {
            if ((unsigned char) bytes[1] >> 6 == 0b00000010) {
                byte_counter = 2;
                encoding_length += 1;
            }
            // If the second byte doesn't match up, then return an error
            else {
                return -1;
            }
        }
        // Length = 3
        else if ((unsigned char) bytes[0] >> 4 == 0b00001110 && (unsigned char) bytes[1] >> 6 == 0b00000010) {
            if ((unsigned char) bytes[2] >> 6 == 0b00000010) {
                byte_counter = 3;
                encoding_length += 1;
            }
            else {
                return -1;
            }
        }
        // Length = 4
        else if ((unsigned char) bytes[0] >> 3 == 0b00011110 && (unsigned char) bytes[1] >> 6 == 0b00000010 && (unsigned char) bytes[2] >> 6 == 0b00000010) {
            if ((unsigned char) bytes[3] >> 6 == 0b00000010) {
                byte_counter = 4;
                encoding_length += 1;
            }
            else {
                return -1;
            }
        }
        // Move the pointer of bytes by how long the encoding we just parsed over was
        bytes += byte_counter;
    }
    return encoding_length;
}
