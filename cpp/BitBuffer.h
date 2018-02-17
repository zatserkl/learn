//
//  Created by Andriy Zatserklyaniy on 1/19/14.
//  Copyright (c) 2014 Andriy Zatserklyaniy. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <exception>

using std::cout;    using std::endl;

#define ACRed  "\e[0;31m"
#define ACPlain  "\e[0m"

#ifndef BitBuffer_h
#define BitBuffer_h

class BitBuffer;

class BitBufferException: public std::exception {
  const BitBuffer* bitBuffer;
public:
  BitBufferException(const BitBuffer* the_bitBuffer) {
    bitBuffer = the_bitBuffer;
  }
  virtual const char* what() const throw() {
    return "*** EOF ***";
  }
  inline void Print() const;
};

class BitBuffer {
  friend class BitBufferException;
private:
  std::ifstream file;
  size_t file_last_byte;
  char* buffer;
  long buffer_size;
  long buffer_first_byte;   // abs position of the first byte of the buffer
  long buffer_last_byte;    // abs position of the last byte of the buffer
  long current_byte;        // last used byte in the buffer, 0 before the first read.
  int current_bit;            // bit in the current_byte to be returned
public:
  BitBuffer(const char* filename, unsigned buffer_size_=32)
    : file_last_byte(0)
      , buffer_size(buffer_size_)
      , current_byte(0)
      , current_bit(0)
  {
    file.open(filename, std::ios::binary);
    if (!file) {
      cout<< "Could not open file " << filename <<endl;
      exit(0);
    }
    // get length of file:
    file.seekg (0, std::ios::end);
    file_last_byte = file.tellg() - 1LL;
    cout<< "BitBuffer: file_size = " << file_last_byte + 1 <<endl;

    buffer = new char[buffer_size];
    Rewind();
  }
  ~BitBuffer() {
    file.close();
    delete[] buffer;
  }
  void Rewind() {
    current_bit = 0;
    current_byte = 0;
    file.seekg(0, std::ios::beg);
    // fill the buffer initially
    buffer_first_byte = 0;
    buffer_last_byte = buffer_size - 1;
    if (buffer_last_byte > file_last_byte) buffer_last_byte = file_last_byte;
    file.seekg (0, std::ios::beg);
    file.read(buffer, buffer_last_byte - buffer_first_byte + 1);
  }
  // methods which return next bit/byte and increament the bit/byte pointer
  inline bool getbit() {return nextbit();}                                    // version with exception
  inline bool getbit(bool& bit) {return nextbit(bit);}                        // version with condition
  inline unsigned char getbyte() {return nextbyte();}                         // version with exception
  inline unsigned char getbyte(unsigned char& byte) {return nextbyte(byte);}  // version with condition
  // methods to fill byte from the stream of bits
  inline unsigned char fillbyte()                                             // version with exception (through getbit)
  {
    // fills byte from the stream of bits
    unsigned char byte = 0;
    for (int i=0; i<8; ++i) {
      unsigned char digit = getbit()? 1 << (7-i): 0;
      byte = byte | digit;
    }
    return byte;
  }
  inline unsigned char fillbyte(unsigned char& byte)                          // version with condition
  {
    // fills byte from the stream of bits
    byte = 0;
    for (int i=0; i<8; ++i) {
      bool bit;
      if (!getbit(bit)) return 0;
      unsigned digit = bit? 1 << (7-i): 0;
      byte = byte | digit;
    }
    return 1;
  }
  inline unsigned char fillpart(unsigned char ndigits)                        // version with exception (through getbit)
  {
    // fills part of byte from the stream of bits
    // user is responsible that ndigits <= 8
    unsigned char byte = 0;
    unsigned char max_digit = ndigits - 1;
    for (int i=0; i<ndigits; ++i) {
      unsigned char digit = getbit()? 1 << (max_digit-i): 0;
      byte = byte | digit;
    }
    return byte;
  }
  inline unsigned char fillpart(unsigned char& byte, unsigned char ndigits)   // version with condition
  {
    // fills part of byte from the stream of bits
    // user is responsible that ndigits <= 8
    byte = 0;
    unsigned char max_digit = ndigits - 1;
    for (int i=0; i<ndigits; ++i) {
      bool bit;
      if (!getbit(bit)) return 0;
      unsigned char digit = bit? 1 << (max_digit-i): 0;
      byte = byte | digit;
    }
    return 1;
  }
  // method which returns byte currently in use. No increament of the byte pointer
  inline unsigned char get_current_byte() const {return buffer[current_byte];}

  // actual low level methods
  inline unsigned char nextbyte()
  {
    // version with exception
    ++current_byte;
    if (buffer_first_byte + current_byte > buffer_last_byte) {
      if (buffer_last_byte == file_last_byte) {
        --current_byte;                             // restore last current_byte
        throw BitBufferException(this);
      }
      // read the next buffer
      buffer_first_byte = buffer_last_byte + 1;
      buffer_last_byte = buffer_first_byte + buffer_size - 1;
      if (buffer_last_byte > file_last_byte) buffer_last_byte = file_last_byte;
      file.read(buffer, buffer_last_byte - buffer_first_byte + 1);
      current_byte = 0;
    }
    current_bit = 0;
    return buffer[current_byte];
  }
  inline unsigned char nextbyte(unsigned char& byte)
  {
    // version with condition
    ++current_byte;
    if (buffer_first_byte + current_byte > buffer_last_byte) {
      if (buffer_last_byte == file_last_byte) {
        --current_byte;                             // restore last current_byte
        return 0;
      }
      // read the next buffer
      buffer_first_byte = buffer_last_byte + 1;
      buffer_last_byte = buffer_first_byte + buffer_size - 1;
      if (buffer_last_byte > file_last_byte) buffer_last_byte = file_last_byte;
      file.read(buffer, buffer_last_byte - buffer_first_byte + 1);
      current_byte = 0;
    }
    byte = buffer[current_byte];
    current_bit = 0;
    return 1;
  }
  inline bool nextbit() {
    // version with exception
    if (current_bit > 7) nextbyte();
    return buffer[current_byte] & (1 << (7-current_bit++));   // returns current_bit from current_byte
  }
  inline bool nextbit(bool& bit) {
    // version with condition
    if (buffer_first_byte + current_byte == file_last_byte && current_bit > 7) return false;
    bit = getbit();
    return true;
  }

  // unget bit/byte
  bool ungetbyte() {
    if (current_byte > 0) {
      current_byte--;
      return true;
    }
    else {
      // this is the first byte of the new buffer
      // read previous block
      //cout<< "// read previous block. Currently: buffer_first_byte = " << buffer_first_byte << " buffer_last_byte = " << buffer_last_byte << " current_byte = " << current_byte <<endl;
      if (buffer_first_byte == 0) return false;               // ignore unget before the first get

      buffer_last_byte = buffer_first_byte - 1;
      buffer_first_byte = buffer_last_byte - buffer_size + 1;
      if (buffer_first_byte < 0) buffer_first_byte = 0;

      file.seekg(buffer_first_byte, std::ios::beg);
      file.read(buffer, buffer_last_byte - buffer_first_byte + 1);
      current_byte = buffer_last_byte - buffer_first_byte;
      //cout<< "after read: buffer_first_byte = " << buffer_first_byte << " buffer_last_byte = " << buffer_last_byte << " current_byte = " << current_byte <<endl;
      return true;
    }
  }
  bool ungetbit() {
    if (current_bit > 0) {
      current_bit--;
      return true;
    }
    else {
      // look in the previous byte
      if (ungetbyte()) {
        current_bit = 7;
        return true;
      }
      else {
        // special case of unget before the first get
        current_bit = 0;
        return false;
      }
    }
  }

  bool Inside() const {
    if (current_byte < file_last_byte) return true;
    if (current_byte == file_last_byte && current_bit < 8) return true;
    return false;
  }

  // debug methods
  unsigned long FileSize() const {return file_last_byte + 1;}
  void Print() const {
    cout<< "BitBuffer::Print: current_byte = " << current_byte << " current_bit = " << current_bit
      << " buffer_first_byte = " << buffer_first_byte << " buffer_last_byte = " << buffer_last_byte
      << " file_last_byte = " << file_last_byte
      << " get_current_byte() = " << std::hex << std::setfill('0') << std::setw(2) << (unsigned) get_current_byte() << std::dec
    <<endl;
  }
  unsigned Current_byte() const {return current_byte;}
  int Current_bit() const {return current_bit;}
  void PrintBuffer() const {
    cout<< "0\t";
    for (int ibyte=0; ibyte<=buffer_last_byte-buffer_first_byte; ++ibyte) {
      if (ibyte > 0 && ibyte%10 == 0) cout<< "\n" << ibyte << "\t";
      cout<< std::hex << std::setfill('0') << std::setw(2) << (unsigned) (unsigned char) buffer[ibyte] << std::dec << " ";
    }
    cout<<endl;
  }

  // declare a global operator << as a friend to let it access the private data
  friend std::ostream& operator <<(std::ostream&, const BitBuffer&);
};

//
//  global operator << is a friend of the class BitBuffer
//
std::ostream& operator <<(std::ostream& os, const BitBuffer& bitBuffer)
{
    os<< "current_byte = " << bitBuffer.current_byte << " current_bit = " << bitBuffer.current_bit
      << " buffer_first_byte = " << bitBuffer.buffer_first_byte << " buffer_last_byte = " << bitBuffer.buffer_last_byte
      << " file_last_byte = " << bitBuffer.file_last_byte
      << " get_current_byte() = " << std::hex << std::setw(2) << std::setfill('0') << (unsigned) bitBuffer.get_current_byte() << std::setfill(' ') << std::dec
    ;
    return os;
}

//
// method BitBufferException::Print() is a friend of the class BitBuffer (need to be after BitBuffer code to know its contents)
//
inline void BitBufferException::Print() const {
  cout<< "BitBufferException::Print:"
    << " current_byte = " << bitBuffer->current_byte
    << " current_bit = " << bitBuffer->current_bit
    << " buffer_first_byte = " << bitBuffer->buffer_first_byte
    << " buffer_last_byte = " << bitBuffer->buffer_last_byte
    << " file_last_byte = " << bitBuffer->file_last_byte
  <<endl;
}

#endif  // BitBuffer_h
