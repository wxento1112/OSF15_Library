#ifndef BITMAP_H__
#define BITMAP_H__

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef struct bitmap bitmap_t;

// WARNING: Bit requests outside the bitmap and NULL pointers WILL result in a segfault
// This is meant to be a high performance library (except the terrible ffs/ffz implementation),
//  so it assumes you're going to use it right.

// V2: errno? flz/fls?

///
/// Sets requested bit in bitmap
/// \param bitmap The bitmap
/// \param bit The bit to set
///
void bitmap_set(bitmap_t *const bitmap,const size_t bit);

///
/// Clears requested bit in bitmap
/// \param bitmap The bitmap
/// \param bit The bit to clear
///
void bitmap_reset(bitmap_t *const bitmap, const size_t bit);

///
/// Returns bit in bitmap
/// \param bitmap The bitmap
/// \param bit The bit to query
/// \raturn State of requested bit
///
bool bitmap_test(const bitmap_t *const bitmap, const size_t bit);

///
/// Flips bit in bitmap
/// \param bitmap The bitmap
/// \param bit The bit to flip
///
void bitmap_flip(bitmap_t *const bitmap, const size_t bit);

///
/// Find first set
/// \param bitmap The bitmap
/// \return The first one bit address, SIZE_MAX on error/not found
///
size_t bitmap_ffs(const bitmap_t *const bitmap);

///
/// Find first zero
/// \param bitmap The bitmap
/// \return The first zero bit address, SIZE_MAX on error/not found
///
size_t bitmap_ffz(const bitmap_t *const bitmap);

///
/// Resets bitmap contents to the desired pattern
/// (pattern not guarenteed accurate for final bits
/// 		if bit_count is not a multiple of 8)
/// \param bitmap The bitmap
/// \param pattern The pattern to apply to all bytes
///
void bitmap_format(bitmap_t *const bitmap, const uint8_t pattern);

///
/// Gets total number of bits in bitmap
/// \param bitmap The bitmap
/// \return The number of bits in the bitmap
///
size_t bitmap_get_bits(const bitmap_t *const bitmap);

///
/// Gets total number of bytes in bitmap
/// \param bitmap The bitmap
/// \return number of bytes used by bitmap storage array
///
size_t bitmap_get_bytes(const bitmap_t *const bitmap);

///
/// Gets pointer to the internal data for exporting
///  Be sure to query the bit and byte size if it's unknown
/// \param bitmap The bitmap
/// \return Pointer for writing
///
const uint8_t *bitmap_export(const bitmap_t *const bitmap);

///
/// Creates a new bitmap with the provided data
/// Note: This does not use the buffer but copies the data
///  to an internal buffer
/// (V2: create a func that allows using a pre-existing buffer)
/// \param n_bits The number of bits in the bitmap
/// \param bitmap_data The data to import
/// \return New bitmap pointer, NULL on error
///
bitmap_t *bitmap_import(const size_t n_bits, const  uint8_t *const bitmap_data);

///
/// Creates a bitmap to contain n bits (zero initialized)
/// \param n_bits
/// \return New bitmap pointer, NULL on error
///
bitmap_t *bitmap_create(const size_t n_bits);

///
/// Destructs and destroys bitmap object
/// \param bitmap The bitmap
///
void bitmap_destroy(bitmap_t *bitmap);


#endif
