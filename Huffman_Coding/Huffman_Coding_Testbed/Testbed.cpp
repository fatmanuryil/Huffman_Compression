#include "Huffman_Compression.h"
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	const unsigned short num_chars = 16;

	unsigned char existing_bytes[num_chars] = { ' ', 'a', 'e', 'f', 'h', 'i', 'm', 'n', 's', 't', 'l', 'o', 'p', 'r', 'u', 'x' };
	unsigned int  frequency_array[num_chars] = { 7,   4,   4,   3,   2,   2,   2,   2,   2,   2,   1,   1,   1,   1,   1,   1 };

	auto* huffman_compression = new Huffman_Compression(existing_bytes, frequency_array, num_chars);

	/* input string to compress */
	string input_string = "this is an example of a huffman tree";
	auto string_len = input_string.length();
	auto* byte_stream = new unsigned char[string_len];

	for (auto idx = 0; idx < string_len; idx++)
	{
		byte_stream[idx] = static_cast<unsigned char>(input_string[idx]);
	}

	unsigned char compressed_stream[100] = {};
	unsigned int  compressed_bit_len = 0;
	unsigned char decompressed_stream[100] = {};
	unsigned int  decompressed_byte_len = 0;

	huffman_compression->huffmanCompressor(byte_stream, string_len, compressed_stream, &compressed_bit_len);

	huffman_compression->huffmanDecompressor(compressed_stream, compressed_bit_len, decompressed_stream, &decompressed_byte_len);

	// if decompressed_stream is the same as byte_stream, then this means that the functions work

	delete[] byte_stream;
	return 0;
}