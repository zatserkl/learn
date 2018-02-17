//
//  main.cpp
//  getbit
//
//  Created by Andriy Zatserklyaniy on 1/17/14.
//  Copyright (c) 2014 Andriy Zatserklyaniy. All rights reserved.
//

#include "BitBuffer.h"

#include <iostream>
#include <fstream>
#include <exception>

//using std::cout;    using std::endl;

void write_bin_file(const char* ofname = "getbit.bin")
{
  std::ofstream ofile(ofname, std::ios::binary);

  char buffer[256];           // cannot be unsigned char: conflict with ofstream::write
  for (int i=0; i<256; ++i) {
    buffer[i] = (unsigned char) i;
  }

  ofile.write(buffer, 256);
}

inline bool getbit(const char* buf, size_t n)
{
  return buf[n/8] & (1 << (7 - n%8));
}
inline bool getbit(const unsigned char* buf, size_t n)
{
  return buf[n/8] & (1 << (7 - n%8));
}

int main()
{
  const char* filename = "getbit.bin";

  //--done-- write_bin_file(filename);

  std::ifstream ifile(filename, std::ios::binary|std::ios::in);
  if (!ifile) {
    cout<< "Could not open file " << filename <<endl;
    cout<< "(Perhaps, you have to uncomment the line which writes it)" <<endl;
    return 0;
  }

  // get length of file:
  ifile.seekg (0, std::ios::end);
  long long length = ifile.tellg();
  ifile.seekg (0, std::ios::beg);
  cout<< "length = " << length <<endl;

  char buffer[1024];
  ifile.read(buffer, 256);

  ifile.seekg (0, std::ios::end);
  length = ifile.tellg();
  ifile.seekg (0, std::ios::beg);
  cout<< "after the read length = " << length <<endl;

  cout<< "read with getbit" <<endl;

  for (int ibit=0; ibit<256*8; ++ibit)
  {
    bool bit = getbit(buffer, ibit);
    if (ibit > 0 && ibit%8 == 0) cout<< " ";
    cout<< bit;
  }
  cout<<endl;

  ifile.close();

  cout<< "\nInstantiate BitBuffer" <<endl;

  // unsigned buffer_size = 32;
  // unsigned buffer_size = 100;
  // unsigned buffer_size = 10;
  // unsigned buffer_size = 200;
  unsigned buffer_size = 1;
  BitBuffer bitBuffer("getbit.bin", buffer_size);

  bool bit;               // return value for bitBuffer.getbit(bit)
  unsigned char byte;     // return value for bitBuffer.getbyte(byte)
  long nbit = 0;           // counter

  // for (int ibit=0; ibit<8; ++ibit) {
  //   cout<< "ibit = " << ibit << "\t" << bitBuffer.getbit() <<endl;
  // }

  /// for (int ibit=0; ibit<256*8; ++ibit) {
  ///   bool bit = bitBuffer.getbit();
  ///   if (ibit > 0 && ibit%8 == 0) cout<< " " <<std::flush;
  ///   cout<< bit <<std::flush;
  /// }
  /// cout<<endl;

  // for (int ibit=0; ibit<4*8; ++ibit) {
  //   bool bit = bitBuffer.getbit();
  //   cout<< ibit << "\t" << bit <<endl;
  // }
  // return 0;

  cout<< "use bitBuffer.getbit(bit)" <<endl;
  nbit = 0;
  while (bitBuffer.getbit(bit))
  {
    if (nbit > 0 && nbit%8 == 0) cout<< " " <<std::flush;
    cout<< bit <<std::flush;
    ++nbit;
  }
  cout<<endl;
  cout<< "nbit = " << nbit <<endl<<endl;

  cout<< "bitBuffer.current_byte = " << bitBuffer.Current_byte() << " bitBuffer.current_bit = " << bitBuffer.Current_bit() <<endl;
  //cout<< "bitBuffer.Eof() = " << bitBuffer.Eof() <<endl;

  cout<< "\nRewind\n" <<endl;
  bitBuffer.Rewind();
  //cout<< "bitBuffer.Eof() = " << bitBuffer.Eof() <<endl;

  //    for (int ibyte=0; ibyte<256; ++ibyte) {
  //        // for (int ibyte=0; ibyte<250; ++ibyte) {
  //        if (bitBuffer.getbyte(byte)) {
  //            cout<< (unsigned int) byte << " ";
  //            // cout<< ibyte << "\t" << (unsigned int) byte <<endl;
  //        }
  //        else {
  //            cout<< "*** no bytes left. Stop." <<endl;
  //            break;
  //        }
  //    }
  //    cout<<endl;


  while (bitBuffer.getbyte(byte)) {
    cout<< (unsigned int) byte << " ";
  }
  cout<<endl;
  bitBuffer.Print();

  // cout<< "\nExercise ungetbyte and getbyte" <<endl;
  // int nrep = 10;
  // for (int ibyte=0; ibyte<nrep; ++ibyte) bitBuffer.ungetbyte();
  // for (int ibyte=0; ibyte<nrep; ++ibyte) {
  //   cout<< (unsigned) bitBuffer.getbyte() <<endl;
  // }
  // return 0;

  cout<< "\nDo ungetbyte in loop" <<endl;
  //-- for (int ibyte=0; ibyte<60; ++ibyte) {
  for (int ibyte=0; ibyte<256; ++ibyte) {
    bitBuffer.ungetbyte();
  }
  cout<<endl;

  cout<< "bitBuffer.Current_byte() = " << bitBuffer.Current_byte() << " bitBuffer.Current_bit() = " << bitBuffer.Current_bit() <<endl;

  //    cout<< "getbyte again" <<endl;
  //    //-- for (int ibyte=0; ibyte<60; ++ibyte) {
  //    for (int ibyte=0; ibyte<256; ++ibyte) {
  //        if (bitBuffer.getbyte(byte)) {
  //            cout<< (unsigned) (unsigned char) bitBuffer.getbyte() << " ";
  //        }
  //        else {
  //            cout<< "*** no bytes left. Stop." <<endl;
  //            break;
  //        }
  //    }
  //    cout<<endl;

  //--does_not_help-- bitBuffer.Rewind();

  cout<< "getbyte again" <<endl;
  while(bitBuffer.getbyte(byte)) {
    cout<< (unsigned) (unsigned char) byte << " ";
  }
  cout<<endl;

  cout<< "\nRewind, getbit and ungetbit in loop" <<endl;

  bitBuffer.Rewind();

  cout<< "\n--> do getbit" <<endl;

  /// for (int ibit=0; ibit<256*8; ++ibit) {
  /// //-- for (int ibit=0; ibit<32; ++ibit) {
  ///   bool bit = bitBuffer.getbit();
  ///   if (ibit > 0 && ibit%8 == 0) cout<< " ";
  ///   cout<< bit;
  /// }
  /// cout<<endl;

  nbit = 0;
  while (bitBuffer.getbit(bit)) {
    if (nbit > 0 && nbit%8 == 0) cout<< " " <<std::flush;
    ++nbit;
    cout<< bit <<std::flush;
  }
  cout<<endl;

  cout<< "\n--> do ungetbit" <<endl;

  for (int ibit=0; ibit<nbit; ++ibit) {
    bitBuffer.ungetbit();
  }
  cout<<endl;

  cout<< "bitBuffer.Current_bit() = " << bitBuffer.Current_bit() << " bitBuffer.Current_byte() = " << bitBuffer.Current_byte() <<endl;

  cout<< "\nDo getbit again" <<endl;

  nbit = 0;
  while (bitBuffer.getbit(bit))
  {
    if (nbit > 0 && nbit%8 == 0) cout<< " ";
    cout<< bit;
    ++nbit;
  }
  cout<<endl;

  cout<< "\nCause an exception" <<endl;
  cout<< "Current status: is"; bitBuffer.Print();
  try {
    cout<< "Next call of the getbyte will generate an exception" <<endl;
    bitBuffer.getbyte();
  }
  catch (const BitBufferException& bitBufferException) {
    cout<< "bitBufferException.what() = " << bitBufferException.what() <<endl;
    bitBufferException.Print();
  }

  cout<< "\nRewind" <<endl;
  bitBuffer.Rewind();

  cout<< "\n--- Find byte pattern ---" <<endl;

  const int pattern_size = 4;
  unsigned char pattern[pattern_size];
  pattern[0] = 'A';
  pattern[1] = 'B';
  pattern[2] = 'C';
  pattern[3] = 'D';

  unsigned char test_pattern[pattern_size];
  for (int i=0; i<pattern_size; ++i) test_pattern[i] = pattern[i];
  if (true
      && test_pattern[0] == pattern[0]
      && test_pattern[1] == pattern[1]
      && test_pattern[2] == pattern[2]
      && test_pattern[3] == pattern[3]
     )
  {
    cout<< "test passed" <<endl;
  }
  else {
    cout<< "test failed" <<endl;
  }

  bool found = false;
  //-- for (int ibyte=0; ibyte<256; ++ibyte) {
  while (bitBuffer.getbyte(byte)) {
    if (byte == 'A') {
      cout<< "found!" <<endl;
      found = true;
      break;
    }
  }
  if (!found) cout<< "not found" <<endl;

  bitBuffer.Rewind();                         // rememeber to Rewind()

  for (int ibyte=0; ibyte<4; ++ibyte) {
    cout<< pattern[ibyte];
  }
  cout<<endl;

  unsigned char buf[pattern_size];
  for (int i=0; i<pattern_size; ++i) buf[i] = bitBuffer.getbyte();

  bool same = true
    && buf[0] == pattern[0]
    && buf[1] == pattern[1]
    && buf[2] == pattern[2]
    && buf[3] == pattern[3]
    ;

  while (!same) {
    for (int ielement=0; ielement<pattern_size-1; ++ielement) buf[ielement] = buf[ielement+1];
    buf[pattern_size-1] = bitBuffer.getbyte();
    same = true
      && buf[0] == pattern[0]
      && buf[1] == pattern[1]
      && buf[2] == pattern[2]
      && buf[3] == pattern[3]
      ;
  }

  if (same) cout<< "The next element after the pattern is " << bitBuffer.getbyte() <<endl;
  else cout<< "The pattern was not found" <<endl;

  cout<< "\nTest of fillbyte\n" <<endl;

  bitBuffer.Rewind();

  for (int i=0; i<256; ++i) {
    unsigned char byte = bitBuffer.fillbyte();
    // cout<< i <<"\t"<< std::hex << std::setw(2) << std::setfill('0') << (unsigned) byte << std::dec << std::setfill(' ') <<endl;
    cout<< (unsigned int) byte << " ";
  }
  cout<<endl;

  cout<< "\nCheck direct filling of byte (unsigned char) w/o bitset" <<endl;

  bitBuffer.Rewind();

  for (int ibyte=0; ibyte<256; ++ibyte) {
    byte = 0;
    for (int ibit=0; ibit<8; ++ibit) {
      unsigned char digit = bitBuffer.getbit()? 1 << (7-ibit): 0;
      byte = byte | digit;
    }
    cout<< (unsigned) byte << " ";
  }
  cout<<endl;

  cout<< "\nTest BitBuffer::fillpart" <<endl;

  bitBuffer.Rewind();

  for (int ipart=0; ipart<256*2; ++ipart) {
    byte = bitBuffer.fillpart(4);
    cout<< std::hex << std::setw(1) << (unsigned) byte << std::dec;
    if (ipart > 0 && ipart%2 == 1) cout<< " ";
  }
  cout<<endl;

  return 0;
}
