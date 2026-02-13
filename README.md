# Tombstone Compression Systems

This is a hobby project focused on image compression.

## Current Functionality
The current version of Tombstone Compression Systems can:
- Read and validate BMP image files.
- Specifically supports 24-bit uncompressed BMPs.
- Checks for valid BMP file headers and information headers.
- Compress 24-bit BMP images into a custom `.tcs` format using Run-Length Encoding (RLE).

For details, please refer to `src/main.cpp`.

## Future Enhancements
Planned compression modes include:
2. Dictionary/Index Compression