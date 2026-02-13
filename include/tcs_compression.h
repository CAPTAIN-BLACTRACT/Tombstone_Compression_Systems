#ifndef TCS_COMPRESSION_H
#define TCS_COMPRESSION_H

#include <cstddef>
#include <cstdint>
#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "tcs_bmp.h"

bool arePixelsSame(const Pixel& a, const Pixel& b){

  return (a.blue==b.blue&&a.green==b.green&&a.red==b.red);
  
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
