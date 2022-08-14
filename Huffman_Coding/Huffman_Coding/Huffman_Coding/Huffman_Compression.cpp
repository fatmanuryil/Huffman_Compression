#include "Huffman_Compression.h"
#include <queue>
#include <algorithm>

using namespace std;

/* In the constructor of the Huffman_Compression class, we construct the binary tree using respective frequencies of the characters.
   Because we need 2 minimum frequencies in each iteration, we use priority queue */
Huffman_Compression::Huffman_Compression(unsigned char* existing_chars, unsigned int* frequency_array, unsigned short num_chars)
{
	/* Generating  priority queue before constructing binary search tree */
	priority_queue<Byte, vector<Byte>, Compare_Frequencies> char_queue;
	for (auto idx = 0; idx < num_chars; idx++) // initializing inside this loop for each char value
	{
		Byte char_struct = Byte(existing_chars[idx], frequency_array[idx]);
		char_queue.push(char_struct);
	}

	/* Previously generated parent nodes become a child node of another parent node and we need to reach their addressed.This vector will keep
	   the addresses of these nodes. Also, once a node becomes a child node, we delete that node from the vector because, we will not need it
	   anymore. */
	vector<Node*> prev_root_nodes;

	/* Each node is identified by its value. 0-255 values are reserved by the char values, so we assign values from 256 to new internal nodes */
	unsigned short new_value = 256;

	huffman_tree = new Binary_Tree();
	Node* parent_node = nullptr; // a pointer for new generated parent nodes

	/* Tree construction starts here! We will iterate until we have only 1 root node. */
	while (char_queue.size() > 1)
	{
		/* Extracting 2 chars that have minimum 2 frequencies from the priority queue. We delete those elements after extracting. */
		Byte char1 = char_queue.top();
		char_queue.pop();
		Byte char2 = char_queue.top();
		char_queue.pop();

		Node* node1 = nullptr, * node2 = nullptr; // pointers for nodes corresponding to the chars extracted above

		/* If the value of the chars extracted above are smaller than 256, this means there is no previously generated node for that value,
		i.e. the node will be a leaf node. Else, there is already a generated parent node that we can reach from prev_root_nodes vector. */
		if (char1.value < 256) // if a real char value
		{
			node1 = new Node(char1);
			huffman_tree->leaf_nodes[char1.value] = node1;
		}
		else // else, the node is previously generated
		{
			for (auto idx = 0; idx < prev_root_nodes.size(); idx++)
			{
				if (prev_root_nodes[idx]->value == char1.value)
				{
					node1 = prev_root_nodes[idx];
					prev_root_nodes.erase(prev_root_nodes.begin() + idx);
					break;
				}
			}
		}

		if (char2.value < 256) // if a real char value
		{
			node2 = new Node(char2);
			huffman_tree->leaf_nodes[char2.value] = node2;
		}
		else // else, the node is previously generated
		{
			for (auto idx = 0; idx < prev_root_nodes.size(); idx++)
			{
				if (prev_root_nodes[idx]->value == char2.value)
				{
					node2 = prev_root_nodes[idx];
					prev_root_nodes.erase(prev_root_nodes.begin() + idx);
					break;
				}
			}
		}

		/* We generate a new Character object to insert to the priority queue */
		Byte parent_char_struct = Byte(new_value, char1.frequency + char2.frequency);
		char_queue.push(parent_char_struct);
		new_value++;

		parent_node = new Node(parent_char_struct); // a new parent node is generated

		parent_node->left_child = node1; // children of the parent node are pointed
		parent_node->right_child = node2;

		node1->parent_node = parent_node; // parents of the children are updated
		node2->parent_node = parent_node;

		prev_root_nodes.push_back(parent_node); // the new generated parent node (a root node) is pushed back to the vector
	}
	huffman_tree->root_node = parent_node; // after the loop ends, the final parent node is the only root our binary tree
}


Huffman_Compression::Huffman_Compression(unsigned int* frequency_array)
{
	/* Generating  priority queue before constructing binary search tree */
	priority_queue<Byte, vector<Byte>, Compare_Frequencies> char_queue;
	for (auto idx = 0; idx < 256; idx++) // initializing inside this loop for each char value
	{
		Byte char_struct = Byte(idx, frequency_array[idx]);
		char_queue.push(char_struct);
	}

	/* Previously generated parent nodes become a child node of another parent node and we need to reach their addressed.This vector will keep
	   the addresses of these nodes. Also, once a node becomes a child node, we delete that node from the vector because, we will not need it
	   anymore. */
	vector<Node*> prev_root_nodes;

	/* Each node is identified by its value. 0-255 values are reserved by the char values, so we assign values from 256 to new internal nodes */
	unsigned short new_value = 256;

	huffman_tree = new Binary_Tree();
	Node* parent_node = nullptr; // a pointer for new generated parent nodes

	/* Tree construction starts here! We will iterate until we have only 1 root node. */
	while (char_queue.size() > 1)
	{
		/* Extracting 2 chars that have minimum 2 frequencies from the priority queue. We delete those elements after extracting. */
		Byte char1 = char_queue.top();
		char_queue.pop();
		Byte char2 = char_queue.top();
		char_queue.pop();

		Node* node1 = nullptr, * node2 = nullptr; // pointers for nodes corresponding to the chars extracted above

		/* If the value of the chars extracted above are smaller than 256, this means there is no previously generated node for that value,
		i.e. the node will be a leaf node. Else, there is already a generated parent node that we can reach from prev_root_nodes vector. */
		if (char1.value < 256) // if a real char value
		{
			node1 = new Node(char1);
			huffman_tree->leaf_nodes[char1.value] = node1;
		}
		else // else, the node is previously generated
		{
			for (auto idx = 0; idx < prev_root_nodes.size(); idx++)
			{
				if (prev_root_nodes[idx]->value == char1.value)
				{
					node1 = prev_root_nodes[idx];
					prev_root_nodes.erase(prev_root_nodes.begin() + idx);
					break;
				}
			}
		}

		if (char2.value < 256) // if a real char value
		{
			node2 = new Node(char2);
			huffman_tree->leaf_nodes[char2.value] = node2;
		}
		else // else, the node is previously generated
		{
			for (auto idx = 0; idx < prev_root_nodes.size(); idx++)
			{
				if (prev_root_nodes[idx]->value == char2.value)
				{
					node2 = prev_root_nodes[idx];
					prev_root_nodes.erase(prev_root_nodes.begin() + idx);
					break;
				}
			}
		}

		/* We generate a new Character object to insert to the priority queue */
		Byte parent_char_struct = Byte(new_value, char1.frequency + char2.frequency);
		char_queue.push(parent_char_struct);
		new_value++;

		parent_node = new Node(parent_char_struct); // a new parent node is generated

		parent_node->left_child = node1; // children of the parent node are pointed
		parent_node->right_child = node2;

		node1->parent_node = parent_node; // parents of the children are updated
		node2->parent_node = parent_node;

		prev_root_nodes.push_back(parent_node); // the new generated parent node (a root node) is pushed back to the vector
	}
	huffman_tree->root_node = parent_node; // after the loop ends, the final parent node is the only root our binary tree
}


void Huffman_Compression::huffmanCompressor(unsigned char* input_byte_stream, const unsigned int input_byte_stream_len, unsigned char* compressed_byte_stream, unsigned int* compressed_bit_len)
{
	/* Althoug compressed_byte_stream is a byte stream, we will fill it bit by bit, so, we will need the variables defined below */
	unsigned char compressed_byte[20] = {}; // each element will represent a bit of a byte after compressed
	unsigned int  out_byte_idx = 0;  // the byte index we are in compressed_byte_stream 
	unsigned char bit_idx_in_byte = 0;  // the bit index we are in the next byte of compressed_byte_stream

	for (auto idx = 0; idx < input_byte_stream_len; idx++)
	{
		/* We will start from the leaf node corresponding to the byte and go upward */
		Node node = *huffman_tree->leaf_nodes[input_byte_stream[idx]];

		/* Finding the number of bits to represent the byte */
		unsigned char bit_len = 0;
		while (node.parent_node != nullptr)
		{
			node = *node.parent_node;
			bit_len++;
		}

		/* Finding bits corresponding to the byte after compression */
		node = *huffman_tree->leaf_nodes[input_byte_stream[idx]];
		for (auto bit_idx = bit_len - 1; bit_idx >= 0; bit_idx--)
		{
			/* Corresponding bit is 0 if the node is the left child of its parent */
			if (node.value == node.parent_node->left_child->value)
			{
				compressed_byte[bit_idx] = 0;
			}
			/* Corresponding bit is 1 if the node is the right child of its parent */
			else
			{
				compressed_byte[bit_idx] = 1;
			}
			node = *node.parent_node;
		}

		/* We found the bits corresponding to the char, now we will put these bits into the compressed_stream bytes */
		for (auto bit_idx = 0; bit_idx < bit_len; bit_idx++)
		{
			compressed_byte_stream[out_byte_idx] ^= compressed_byte[bit_idx] << bit_idx_in_byte;
			bit_idx_in_byte++;

			/* If the byte is full, then pass to the next byte */
			if (bit_idx_in_byte == 8)
			{
				bit_idx_in_byte = 0;
				out_byte_idx++;
			}
		}
		*compressed_bit_len += bit_len;
		memset(compressed_byte, 0, sizeof(unsigned char) * bit_len);
	}
}


void Huffman_Compression::huffmanDecompressor(unsigned char* compressed_byte_stream, const unsigned int compressed_bit_len, unsigned char* decompressed_byte_stream, unsigned int* decompressed_byte_len)
{
	*decompressed_byte_len = 0;

	/* We will start from the root node of the tree and go bit by bit. */
	unsigned int  byte_idx = 0; // the byte index we are in compressed_byte_stream 
	unsigned char bit_idx_in_byte = 0; // the bit index we are in the next byte of compressed_byte_stream

	unsigned int  in_bit_idx = 0; // number of bits processed in compressed_byte_stream
	while (in_bit_idx < compressed_bit_len)
	{
		unsigned char len = 0;
		Node node = *huffman_tree->root_node;
		while (!node.is_leaf_node)
		{
			/* Extract the next bit from the compressed stream and go to the left (0 bit) or right (1 bit) child */
			unsigned char next_bit = compressed_byte_stream[byte_idx] >> bit_idx_in_byte & 0x01;
			if (next_bit == 0)
			{
				node = *node.left_child;
			}
			else
			{
				node = *node.right_child;
			}

			in_bit_idx++;
			bit_idx_in_byte++;
			if (bit_idx_in_byte == 8)
			{
				bit_idx_in_byte = 0;
				byte_idx++;
			}
		}
		decompressed_byte_stream[(*decompressed_byte_len)++] = node.value;
	}
}