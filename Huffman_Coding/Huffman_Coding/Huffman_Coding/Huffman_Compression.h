#pragma once
#include "Binary_Tree.h"

using namespace std;

/* Huffman Compression can be used to compress a text with specific characters. In that case, we do not need to add all byte values to the
   binary tree that we will construct. For this reason, we have 2 constructors. The first one constructs the tree only with existing byte values.
   The second one considers all byte values and can be applied to all binary files after indicating the frequencies of each byte in
   frequency_array. */

class __declspec(dllimport) Huffman_Compression
{
public:
	/// <summary>
	/// This constructor is used if only some byte values exist in the input stream to compress. The binary tree is constructed
	/// using only the existing bytes and their frequencies (number of occurences).
	/// </summary>
	/// <param name="existing_bytes"> points to the existing chars in the input stream </param>
	/// <param name="frequency_array"> points to the corresponding frequencies of existing chars </param>
	/// <param name="num_bytes"> number of existing chars </param>
	Huffman_Compression(unsigned char* existing_bytes, unsigned int* frequency_array, unsigned short num_bytes);

	/// <summary>
	/// This constructor is used if all 256 byte values and their frequencies are taken into account while constructing the binary tree.
	/// </summary>
	/// <param name="frequency_array"> points to the frequency array (length = 256) of the byte values </param>
	Huffman_Compression(unsigned int* frequency_array);

	/// <summary>
	/// The function implementing Huffman Compression algorithm. It takes a uncompressed byte array (input_byte_stream) and compresses using the  
	/// binary tree constructed (huffman_tree) inside the constructor of the class. It writes the compressed bytes to compressed_byte_stream 
	/// and updates compressed_bit_len (It counts bits because the byte at the end might not be full.)
	/// </summary>
	/// <param name="input_byte_stream"> points to the uncompressed input bytes </param>
	/// <param name="input_byte_stream_len"> number of bytes to compress </param>
	/// <param name="compressed_byte_stream"> points to the byte stream to be filled with compressed bytes (empty initially) </param>
	/// <param name="compressed_bit_len"> number of compressed bits (updated inside the function) </param>
	void huffmanCompressor(unsigned char* input_byte_stream, unsigned int input_byte_stream_len, unsigned char* compressed_byte_stream, unsigned int* compressed_bit_len);

	/// <summary>
	/// The function implementing Huffman Decompression algorithm. It takes a compressed byte array (compressed_byte_stream) and decompresses  
	/// using the binary tree constructed (huffman_tree) inside the constructor of the class. It writes the decompressed bytes to 
	/// decompressed_byte_stream and updates decompressed_byte_len.
	/// </summary>
	/// <param name="compressed_byte_stream"> points to the compressed input bytes </param>
	/// <param name="compressed_bit_len"> number of bits contained in compressed_byte_stream (not bytes because the byte at the end might not be full.) </param>
	/// <param name="decompressed_byte_stream"> points to the byte stream to be filled with decompressed bytes (empty initially) </param>
	/// <param name="decompressed_byte_len"> number of decompressed bytes (updated inside the function) </param>
	void huffmanDecompressor(unsigned char* compressed_byte_stream, unsigned int compressed_bit_len, unsigned char* decompressed_byte_stream, unsigned int* decompressed_byte_len);

private:
	Binary_Tree* huffman_tree; // the binary tree that is used to compress or decompress the data
};


