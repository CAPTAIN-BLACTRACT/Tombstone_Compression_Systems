#ifndef TCS_COMPRESSION_H
#define TCS_COMPRESSION_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "tcs_bmp.h"


bool arePixelsSame(const Pixel& a, const Pixel& b){

  return (a.blue==b.blue&&a.green==b.green&&a.red==b.red);
  
}

void decompressRLE(string tcsFilename, string outBmpName){
  std::ifstream inputFile(tcsFilename, std::ios::binary);
  if(!inputFile){
  std::cerr<<"Cant open the file "<<tcsFilename<<std::endl;
    return;
  }
  
  char magicBuffer[5]={0};
  inputFile.read(magicBuffer, 4);

  if(std::string(magicBuffer)!="TCS1"){  
    std::cerr<<"This is not a valid tcs file"<<std::endl;
    return;
  }
  
  int32_t width,height;

  inputFile.read(reinterpret_cast<char*>(&width), sizeof(width) );
  inputFile.read(reinterpret_cast<char*>(&height), sizeof(height));

  std::cout<<"Restoring image: "<<width<<"x"<<height<<std::endl;
  int padding = (4-(width*3)%4)%4;

  uint32_t imageSize = (width*3 + padding)*height;
  uint32_t fileSize = 54 + imageSize;
// bhai ai ki madd se bna lo header aur info file 
  // apna dimag mt lagaie
  
}
  BMPFileHeader fileHeader;
  fileHeader.file_type = 0x4D42;
  fileHeader.file_size = fileSize;
  fileHeader.reserved1 = 0;
  fileHeader.reserved2 = 0;
  fileHeader.offset_data = 54;

  BMPInfoHeader infoHeader;
  infoHeader.size = 40;
  infoHeader.width = width;
  infoHeader.height = height;
  infoHeader.planes = 1;
  infoHeader.bit_count = 24;
  infoHeader.compression = 0;
  infoHeader.size_image = imageSize;
  infoHeader.x_pixels_per_meter = 0;
  infoHeader.y_pixels_per_meter = 0;
  infoHeader.colors_used = 0;
  infoHeader.colors_important = 0;
//ab likh lo
std::ofstream outFile(outBmpName,std::ios::binary);

outFile.write(reinterpret_cast<const char*>(&fileHeader),sizeof(fileHeader));
outFile.write(reinterpret_cast<const char*>(&infoHeader),sizeof(infoHeader));

int currentX =0;

while (inputFile.peek()!=EOF) {
  uint8_t count;
  Pixel color;

  inputFile.read(reinterpret_cast<char*>(&count),1);
  inputFile.read(reinterpret_cast<char*>(&color),3);

//agar beech me file khatam ho jae to bhag jao
  if(!inputFile) break;

  //pixel ko count baar likho
  for(int i=0;i<count;i++){
    outFile.write(reinterpret_cast<const char*>(&color),3);
    currentX++;

    if(currentX==width){
      char pad[3] = {0,0,0};
      outFile.write(pad,padding);
      currentX=0;
    }
  }



}

outFile.close();
std::cout<<"Success! Decompressed to : "<<outBmpName<<std::endl;

}

void compressRLE(const std::vector<Pixel>& pixels , int width, int height, const std::string& filename){
  std::ofstream outFile(filename,std::ios::binary);

  if(!outFile){
    std::cerr<<"Error couldnt create the output file "<<filename<<std::endl;
    return;
  }
//header
  const char* magic = "TCS1";
  outFile.write(magic,4);
  outFile.write(reinterpret_cast<const char*>(&width), sizeof(width));
  outFile.write(reinterpret_cast<const char*>(&height),sizeof(height));

  int count =1;
  Pixel current = pixels[0];

  for (size_t i=1; i<pixels.size();i++) {
    Pixel next = pixels[i];

    if(arePixelsSame(current, next) && count<255){
      count++;
    }else{
      uint8_t countByte = (uint8_t)count;
      outFile.write(reinterpret_cast<const char*>(&countByte),1);
      outFile.write(reinterpret_cast<const char*>(&current), 3);

      current=next;
      count=1;
    }
  }

  uint8_t countByte = (uint8_t)count;
  outFile.write(reinterpret_cast<const char*>(&countByte),1);
  outFile.write(reinterpret_cast<const char*>(&current),3);


  outFile.close();

  std::ifstream in(filename, std::ios::binary | std::ios::ate);

  size_t compressedSize = in.tellg();
  size_t originalSize = width*height*3 + 54;

  std::cout<<"-----------------------------------------"<<std::endl;
  std::cout<<"Original Size: "<<originalSize<<" bytes"<<std::endl;
  std::cout<<"Compressed Size: "<<compressedSize<<" bytes"<<std::endl;

  double ratio = 100.0 - ((double)compressedSize/originalSize*100.0);
  std::cout<<"Space saved:  "<<ratio<<"%"<<std::endl;

  #endif
}
