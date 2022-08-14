#pragma once

/// <summary>
/// While constructing the binary tree for Huffman Compression we need to match byte values with their frequencies.
/// </summary>
struct Byte
{
	unsigned short value;     // we define it using short because we want to assign different values (greater than 255) to internal nodes in tree
	unsigned int   frequency;

	Byte(unsigned short value, unsigned int frequency)
	{
		this->value = value;
		this->frequency = frequency;
	}

	Byte() = default;
};

/// <summary>
/// This is a structure which implements the operator overloading to compare and sort Byte structs inside the priority queue.
/// </summary>
struct Compare_Frequencies {
	bool operator()(Byte& const byte1, Byte& const byte2)
	{
		return byte1.frequency > byte2.frequency;
	}
};

/// <summary>
/// The struct to represent each node in the binary tree.
/// </summary>
struct Node
{
	bool           is_leaf_node; // true if is the node is a leaf node (if it has no child)
	unsigned short value;        // value of the node, this value is not important if it is not a leaf node. If it is a leaf node, this value indicates the byte value of the node.
	unsigned int   frequency;    // overall frequency of the node
	Node* parent_node;  // points to the parent node of the node
	Node* left_child;   // points to the left subnode of the node
	Node* right_child;  // points to the right subnode of the node

	Node(Byte const byte_struct)
	{
		value = byte_struct.value;
		frequency = byte_struct.frequency;
		value = byte_struct.value;

		if (byte_struct.value < 256) // a leaf node
		{
			is_leaf_node = true;
		}
		else // an internal node
		{
			is_leaf_node = false;
		}

		parent_node = nullptr;
		left_child = nullptr;
		right_child = nullptr;
	};
};

struct Binary_Tree
{
	Node* root_node;       // points to the root node of the binary tree
	Node* leaf_nodes[256]; // the array keeping the addresses of leaf nodes (1 leaf node for each existing byte)

	Binary_Tree() = default;
};



