#include <iostream>
#include <fstream>
#include <iomanip>

#include <cstdio>

using std::cout;      using std::endl;
using std::hex;       using std::dec;       using std::setw;

union Word4 {
  unsigned int word;
  unsigned short word2[2];
  char sbyte[4];            // signed char: binary write and read need char (signed char)
  unsigned char ubyte[4];   // unsigned char: for test purpose only
  Word4(): word(0) {}
  void print() const {
    cout<< "decimal word: " << word <<endl;
    cout<< "word: " << hex << word << dec <<endl;
    printf("sbyte: %02x %02x %02x %02x\n", (unsigned char) ubyte[0], (unsigned char) ubyte[1], (unsigned char) ubyte[2], (unsigned char) ubyte[3]);
    printf("ubyte: %02x %02x %02x %02x\n", ubyte[0], ubyte[1], ubyte[2], ubyte[3]);
  }
};

int main()
{
  Word4 word4;
  word4.word = 2011;
  cout<< "word " << word4.word << " in hex: " << hex << word4.word << dec <<endl;
  cout<< "byte content:" <<endl;
  cout<< "print as hex << (unsigned int) unsigned char" <<endl;
  for (int i=0; i<4; ++i) cout<< i << ": " << setw(2) << std::setfill('0') << hex << (unsigned int) word4.ubyte[i] << dec <<endl;
  cout<< "print as hex << (unsigned int) signed char" <<endl;
  for (int i=0; i<4; ++i) cout<< i << ": " << setw(2) << std::setfill('0') << hex << (unsigned int) word4.sbyte[i] << dec <<endl;
  cout<< "print as hex << (unsigned int) (unsigned char) signed char" <<endl;
  for (int i=0; i<4; ++i) cout<< i << ": " << setw(2) << std::setfill('0') << hex << (unsigned int) (unsigned char) word4.sbyte[i] << dec <<endl;

  printf("printf(\"%%02x\", word4.ubyte[i])\n");
  for (int i=0; i<4; ++i) printf("%02x\n", word4.ubyte[i]);
  printf("printf(\"%%02x\", word4.sbyte[i])\n");
  for (int i=0; i<4; ++i) printf("%02x\n", word4.sbyte[i]);
  printf("printf(\"%%02x\", (unsigned char) word4.sbyte[i])\n");
  for (int i=0; i<4; ++i) printf("%02x\n", (unsigned char) word4.sbyte[i]);

  cout<<endl<< "Seems, to print in hex, the best is to use printf with explicit cast into (unsigned char)" <<endl;
  cout<< "To use printf:" <<endl;
  cout<< "printf(\"%02x\", (unsigned char) sbyte[i]);" <<endl;
  cout<< "To use cout:" <<endl;
  cout<< "cout<< std::hex << (unsigned int) (unsigned char) sbyte[i] << std::dec <<endl;" <<endl;
  cout<< "Comments for cout:" <<endl;
  cout<< "-- You need conversion to (unsigned int) because modifier std::hex applies for integer-like types, not char" <<endl;
  cout<< "-- You need to convert char to (unsigned char) to print its sbyte content" <<endl;
  cout<< "-- you have to use std::dec to change the stream state to dec for the next printouts" <<endl;
  cout<<endl<< "NB: for both, printf and cout you have to convert char to (unsigned char)" <<endl<<endl;

  const char fname[] = "readbin.dat";
  
  cout<< "write year in two bytes of 4-bytes integer in binary file " << fname <<endl;

  std::ofstream ofile(fname, std::ios::binary);
  ofile.write(word4.sbyte, 2);                   // write 2 bytes from buffer word4.sbyte
  ofile.close();
  
  cout<< "read binary file " << fname <<endl<<endl;

  word4.word = 0;

  std::ifstream ifile(fname, std::ios::binary);
  ifile.read(word4.sbyte, 2);                    // write year into two bytes
  ifile.close();

  //cout<< "word: " << hex << word4.word << dec <<endl;
  //printf("bytes: %02x %02x %02x %02x\n", (unsigned char) word4.sbyte[0], (unsigned char) word4.sbyte[1], (unsigned char) word4.sbyte[2], (unsigned char) word4.sbyte[3]);
  word4.print();

  cout<<endl<< "write and read year and month in 4-bytes integer" <<endl;

  // write the data

  std::ofstream ofile1(fname, std::ios::binary | std::ios::app);
  // ofile1.seekp(0, std::ios_base::end);   // do not need because of std::ios::app

  word4.word = 2011;
  ofile1.write(word4.sbyte, 2);
  word4.word = 9;
  ofile1.write(word4.sbyte, 2);
  ofile1.close();

  // read the data
  std::ifstream ifile1(fname, std::ios::binary);

  // read the first two bytes (with just year)
  if (ifile1.read(word4.sbyte, 2)) cout<< "the first two bytes: year: " << word4.word <<endl;
  else {
    cout<< "readout error" <<endl;
    return 0;
  }

  cout<< "ifile.tellg() = " << ifile.tellg() <<endl;
  cout<< "ifile.rdstate() = " << ifile.rdstate() <<endl;
  cout<< "ifile.eofbit = " << ifile.eofbit <<endl;

  cout<< "year and month from next four bytes:" <<endl;
  word4.word = 0;
  if (ifile1.read(word4.sbyte, 2)) cout<< "word4.word = " << word4.word <<endl;
  else {
    cout<< "readout error" <<endl;
    return 0;
  }
  word4.word = 0;
  if (ifile1.read(word4.sbyte, 2)) cout<< "word4.word = " << word4.word <<endl;
  else {
    cout<< "readout error" <<endl;
    return 0;
  }

  cout<< "std::ios::beg = " << std::ios::beg <<endl;
  cout<< "std::ios::end = " << std::ios::end <<endl;
  cout<< "std::ios::cur = " << std::ios::cur <<endl;
  cout<< "ifile.tellg() = " << ifile.tellg() <<endl;
  if (ifile.tellg() == std::ios::end) cout<< "EOF has been reached" <<endl;
  if (ifile.eof()) cout<< "eof has been reached" <<endl;

  cout<< "ifile.rdstate() = " << ifile.rdstate() <<endl;
  cout<< "ifile.eofbit = " << ifile.eofbit <<endl;

  cout<< "\ntry to read by the end of file" <<endl;

  if (ifile1.read(word4.sbyte, 2)) cout<< "read another 2 bytes" <<endl;
  else {
    cout<< "--> the read operation failed" <<endl;
    cout<< "(ifile.rdstate() & std::ifstream::failbit) = " << (ifile.rdstate() & std::ifstream::failbit) <<endl;
    cout<< "ifile.rdstate() = " << ifile.rdstate() <<endl;
    cout<< "ifile.eofbit = " << ifile.eofbit <<endl;
  }

  ifile1.close();

  // cout try to read two 2-bytes words at once as 4-bytes word

  cout<< "\n read two 2-bytes words at once" <<endl;

  // read the data
  std::ifstream ifile2(fname, std::ios::binary);
  
  // read first word: just year
  word4.word = 0;
  if (ifile2.read(word4.sbyte, 2)) cout<< "word4.word = " << word4.word <<endl;
  else {
    cout<< "readout error" <<endl;
    return 0;
  }

  cout<< "read two 2-bytes word" <<endl;

  word4.word = 0;
  if (ifile2.read(word4.sbyte, 4))    // NB: read 4 bytes!
  {
    cout<< "word4.word2[0] = " << word4.word2[0] <<endl;
    cout<< "word4.word2[1] = " << word4.word2[1] <<endl;
  }
  else {
    cout<< "readout error" <<endl;
    return 0;
  }

  cout<< "read done" <<endl<<endl;

  ifile2.close();

  /////////////////////////////////////////////////////
  //
  //  try to figure out am I at end of the file
  //
  /////////////////////////////////////////////////////
  cout<< "\n try to figure out am I at end of the file" <<endl;

  std::ifstream ifile4(fname, std::ios::binary);
  if (!ifile4) {
    cout<< "file not found: " << fname <<endl;
    return 0;
  }

  ifile4.seekg(0, std::ios::end);
  std::streampos pos_end = ifile4.tellg();
  if (pos_end < 0) {
    cout<< "read error, pos_end == " << pos_end <<endl;
    return 0;
  }
  ifile4.seekg(0);

  cout<< "pos_end = " << pos_end <<endl;

  std::streampos pos = 0;

  ifile4.read(word4.sbyte, 2);
  pos = ifile4.tellg(); if (pos < 0) {
    cout<< "file error" <<endl;
    return 0;
  }
  cout<< "after reading of 2 bytes pos == " << pos <<endl;

  ifile4.read(word4.sbyte, 2);
  pos = ifile4.tellg(); if (pos < 0) {
    cout<< "file error" <<endl;
    return 0;
  }
  cout<< "after reading of 2 bytes pos == " << pos <<endl;

  ifile4.read(word4.sbyte, 2);
  pos = ifile4.tellg(); if (pos < 0) {
    cout<< "file error" <<endl;
    return 0;
  }
  cout<< "after reading of 2 bytes pos == " << pos <<endl;

  pos = ifile4.tellg(); if (pos < 0) {
    cout<< "file error" <<endl;
    return 0;
  }
  cout<< "after reading of 2 bytes pos == " << pos <<endl;
  cout<< "we should be at the end of the file now, pos = " << pos <<endl;
  if (pos == pos_end) cout<< "yes, it is" <<endl;

  ////////////////////////////////////////////////////////////////
  //
  //  exception handling during readout
  //
  ////////////////////////////////////////////////////////////////

  std::ifstream ifile3(fname, std::ios::binary);

  // set exception mask for ifile3
  ifile3.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  // find the file length
  ifile3.seekg(0, std::ios::end);
  int length = ifile3.tellg();
  ifile3.seekg(0);                // the same as ifile3.seekg(0, std::ios::beg);

  char buffer[8];
  int nbytes_read = length;

  try {
    cout<< "\ntry to read " << nbytes_read << " bytes from file with size " << length << " bytes" <<endl;
    ifile3.read(buffer, nbytes_read);       // NB: our file has 6 bytes length
  }
  catch (std::ifstream::failure e) {
    cout<< "read error: " << e.what() <<endl;
    return 0;
  }
  cout<< "ok" <<endl;

  ifile3.seekg(0);    // go back to the beginning of the file
  nbytes_read = length + 1;

  try {
    cout<< "try to read " << nbytes_read << " bytes from file with size " << length << " bytes" <<endl;
    ifile3.read(buffer, nbytes_read);       // NB: our file has 6 bytes length
  }
  catch (std::ifstream::failure e) {
    cout<< "read error: " << e.what() <<endl;
    return 0;
  }
  cout<< "ok" <<endl;

  ifile3.close();

  return 0;
}
