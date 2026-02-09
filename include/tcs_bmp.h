#ifndef TCS_BMP_H //safe guard against accidently including this header and causeing the redefinition error
//compiler says if not defined then define it now and use the code below
#define TCS_BMP_H

#include <cstdint> //this library gives various sized int options
#include <vector>

//this is a compiler instruction that says
//hey compiler dont try to be smart and dont pad the items of struct for better performance
//i know what am doing
#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t file_type;       // Magic identifier: 0x4d42 ("BM")
    uint32_t file_size;       // File size in bytes
    uint16_t reserved1;       // Not used
    uint16_t reserved2;       // Not used
    uint32_t offset_data;     // Offset to image data in bytes
};

struct BMPInfoHeader {
    uint32_t size;            // Header size in bytes
    int32_t  width;           // Width of the image
    int32_t  height;          // Height of the image
    uint16_t planes;          // Number of color planes (must be 1)
    uint16_t bit_count;       // Bits per pixel (e.g., 24)
    uint32_t compression;     // Compression type
    uint32_t size_image;      // Image size in bytes
    int32_t  x_pixels_per_meter;
    int32_t  y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
};

#pragma pack(pop)//this restores what #pragma pack(push,1) did

// Our internal representation of a pixel
struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

// Our internal representation of an Image
struct TCSImage {
    int32_t width;
    int32_t height;
    std::vector<Pixel> data; // The raw pixel data
};

#endif // end of #ifndef
