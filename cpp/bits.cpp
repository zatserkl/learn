/*
http://stackoverflow.com/questions/10871970/reading-writing-a-value-at-specified-bit-offset

Bit-fiddling is seldom easy. Here's a complete working example of how to do what you want.
The big problem here is reading and writing blocks of numbers across byte boundaries. 
Problems are always easier if you break them into bite-size chunks, if you'll pardon the pun.

Firstly I created a class like std::bitset that can wrap a user-defined buffer. 
It lets us fiddle with individual bits in a big buffer of binary data.
*/

#include <cassert>  // for assert
#include <cstring>  // for memset
#include <cstdio>   // for printf

// A wrapper for a data buffer providing bit-level access.
class BitBuffer {
public:
    BitBuffer (unsigned char *src_buffer, size_t nbytes)
        : m_data( src_buffer ), m_size( nbytes )
    {
        if (m_size) assert(m_data);
    }

    // Clear the buffer (set all bits to 0).
    void clear () {
        memset( m_data, 0, m_size );
    }

    // Get an individual bit's value.
    bool get (size_t bitpos) const {
        assert( bitpos / 8 < m_size );
        return m_data[ bitpos / 8 ] & ( 1 << ( bitpos % 8 ) );
    }

    // Set an individual bit's value.
    void set (size_t bitpos, bool val=true) {
        assert( bitpos / 8 < m_size );
        if( val ) {
            m_data[ bitpos / 8 ] |= ( 1 << ( bitpos % 8 ) );
        } else {
            m_data[ bitpos / 8 ] &= ~( 1 << ( bitpos % 8 ) );
        }
    }

    // Switch off a bit.
    void reset (size_t bitpos) { 
        set( bitpos, false );
    }

    // Flip a bit.
    void flip (size_t bitpos) {
        set( bitpos, ! get( bitpos ) );
    }

    // Return the size of the buffer in bytes.
    size_t byte_size () const { return m_size; }

    // Return the size of the buffer in bits.
    size_t bit_size () const { return m_size * 8; }

    // Return a const pointer to the buffer.
    unsigned char const *  buffer () const { return m_data; }

private:
    unsigned char * m_data;
    size_t m_size;
};

/*
Then I wrote some functions to get and set blocks of bits from the buffer, MSB first.
*/

unsigned get_bits (BitBuffer& buffer, size_t offset, size_t bit_size)
{
    unsigned bits = 0;
    for (size_t i = 0; i < bit_size; i++) {
        // We reverse the order of the bits, so the first bit read
        // from the buffer maps to the high bit in 'bits'.
        bits |= ( buffer.get( offset + i ) << (bit_size - 1 - i) );
    }
    return bits;
}

void set_bits (BitBuffer& buffer, size_t offset, size_t bit_size, unsigned bits)
{
    for (size_t i = 0; i < bit_size; i++) {
        // We reverse the order of the bits, so the high bit of 'bits'
        // gets written to the buffer first.
        bool bit_value = bits & ( 1 << (bit_size - 1 - i) );
        buffer.set( offset + i, bit_value );
    }
}

/*
And a test harness:
*/

#include <cstdio>

// Print the bits of the buffer to stdout.
void dump_buffer (BitBuffer& buffer)
{
    for (size_t i = 0; i < buffer.bit_size(); i++) {
        printf( "%i", buffer.get(i) );
    }
    printf("\n");
}

#ifndef __CINT__

int main()
{
    const size_t byte_size = 4;  // size of buffer in bytes
    unsigned char * raw_buffer = new unsigned char[ byte_size ];

    BitBuffer buffer( raw_buffer, byte_size );
    buffer.clear();

    printf("Test #0: contents of 4-byte buffer:\n");

    // Show the buffer.
    dump_buffer( buffer );

    printf("\nTest #1: setting and flipping bits:\n");

    // Set some bits
    buffer.set( 5 );
    buffer.set( 10 );
    buffer.set( 12 );
    buffer.set( 31 );

    // Show the buffer.
    dump_buffer( buffer );

    // Read some bits.
    printf( "Value at 12 before flip: %i\n", buffer.get( 12 ) );
    buffer.flip( 12 );
    printf( "Value at 12 after flip: %i\n", buffer.get( 12 ) );

    printf("\nTest #2: setting all 1's, and writing 5, length 4 to offset 6:\n");

    // Fill with 1's.
    set_bits(buffer, 0, 32, 0xFFFFFFFF);

    // Set 5 at offset 6, bit size 4.
    set_bits(buffer, 6, 4, 5);
    assert( get_bits(buffer, 6, 4) == 5 );

    // Show the buffer.
    dump_buffer( buffer );

    // All done.
    delete raw_buffer;
    return 0;
}
#endif  // ifndef __CINT__

/*
To compile, just dump all this in one file and compile. Output of test run:

Test #0: contents of 4-byte buffer:
00000000000000000000000000000000

Test #1: setting and flipping bits:
00000100001010000000000000000001
Value at 12 before flip: 1
Value at 12 after flip: 0

Test #2: setting all 1's, and writing 5, length 4 to offset 6:
11111101011111111111111111111111

Let me know if you find it useful, or if you have any problems with it.
*/

/*
thx @QuasarDonkey, based on your answer and some of my other requirements I coded a small 
library for bit-manipulation. If you're interested it's here: 

https://github.com/wroniasty/bits 

Cheers. – wroniasty Jun 4 '12 at 13:57
*/
