#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <typeinfo>
#include <windows.h>
using namespace std;

// A Tree node
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

// Function to allocate a new tree node
Node *getNode(char ch, int freq, Node *left, Node *right)
{
	Node *node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(Node *l, Node *r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};
priority_queue<Node *, vector<Node *>, comp> pq;

// traverse the Huffman Tree and store Huffman Codes
// in a map.
void encode(Node *root, string str,
			unordered_map<char, string> &huffmanCode)
{

	// found a leaf node
	if (root->left == NULL && root->right == NULL)
	{
		huffmanCode[root->ch] = str;
		return;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// traverse the Huffman Tree and decode the encoded string
void decode(Node *root, int &index, string str)
{
	char a;
	fstream outfile;
	if (root->left == NULL && root->right == NULL)
	{
		outfile.open("HuffmanDecodedString.txt", std::ios_base::app); // append instead of overwrite
		outfile << root->ch;
		a=root->ch;
		cout<<a;
		return;
	}

	index++;
	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

// Builds Huffman Tree and decode given input text
void buildHuffmanTree(string myText, Node *root)
{
	fstream ofs;
	ofs.open("huffmanencodedoutput.bin", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);
	string message;
	message = "Huffman Codes for the given text input are :";
	for (int x = 0; x < message.length(); x++)
	{
		cout << message.at(x);
		Sleep(5);
	}
	cout << "\n"
		 << '\n';
	for (auto pair : huffmanCode)
	{
		cout << "'" << pair.first << "' :"
			 << " " << pair.second << '\n';
		Sleep(5);
	}
	Sleep(1000);
	// print encoded string
	string str = "";
	for (char ch : myText)
	{
		str += huffmanCode[ch];
	}
	long long int value = 0;
	int size = str.length();
	if (size % 4 != 0)
	{
		int remain = 4 - (size % 4);
		while (remain != 0)
		{
			str = str + "0";
			remain--;
		}
	}
	cout<<endl<<endl;
	message = "The encoded output is :";
	for (int x = 0; x < message.length(); x++)
	{
		cout << message.at(x);
		Sleep(5);
	}
	cout << endl;
	Sleep(1000);
	cout << str << endl<<endl;
	fstream my_file;
	my_file.open("HuffmanEncodedString.txt", ios::out);
	if (!my_file)
	{
		cout << "File not created!";
	}
	else
	{
		my_file << str;
		my_file.close();
	}
	// convert the string into hexadecimalvalue
	int itr = str.length() / 4;
	long long int value_arr[itr];
	int k = 4;
	int f = 0;
	// unsigned long long int value = 0;
	for (int j = 0; j < itr; j++)
	{
		for (int i = 0; i < k; i++)
		{
			if (str.at(f) == '1')
			{
				value = value + pow(2, ((k - 1) - i));
			}
			f++;
		}
		value_arr[j] = value;
		value = 0;
	}
	Sleep(1000);
	cout << "Data converted into hexadecimal successfully!" << endl<<endl;
	Sleep(1000);
	cout << "The hexadecimal values are:" << endl<<endl;
	Sleep(1000);
	fstream new_file;
	new_file.open("huffmanencodedoutput.bin", ios::binary | ios::out | ios::app);
	for (int l = 0; l < itr; l++)
	{
		int val = value_arr[l];
		if (new_file.is_open())
		{
			new_file << std::hex << val;
			cout << std::hex << val;
		}
	}
	cout << endl<<endl;
	Sleep(500);
	new_file.close();
}
// Huffman coding algorithm
int runHuffman(int choice)
{
	string message;
	string decode_input;
	int i = 0;
	fstream newfile;
	string myText;
	string complete_string;
	string str;
	int index = -1;
	int p = 0;
	newfile.open("input.txt", ios::in); // open a file to perform read operation using file object
	if (newfile.is_open())
	{ // checking whether the file is open

		while (getline(newfile, myText))
		{
			if (p == 0)
			{
				complete_string = myText;
			}
			else
			{
				complete_string = complete_string + " " + myText;
			}
			p = 1;
		}
		newfile.close(); // close the file object.
	}
	// count frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch : complete_string)
	{
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of  --> minimum priority queue.
	// Huffman tree;
	priority_queue<Node *, vector<Node *>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair : freq)
	{
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// do till there is more than one node in the min priotity queue i.e. ascending order
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node *left = pq.top();
		pq.pop();
		Node *right = pq.top();
		pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root stores pointer to root of Huffman Tree
	Node *root = pq.top();
	fstream ofs;

	switch (choice)
	{
	case 1:
	cout<<endl;
		for (int x = 0; x < 20; x++)
		{
			cout << "=";
			Sleep(10);
		}
		message = "Welcome to Huffman Encoding Program";
		for (int x = 0; x < message.length(); x++)
		{
			cout << message.at(x);
			Sleep(10);
		}
		for (int x = 0; x < 20; x++)
		{
			cout << "=";
			Sleep(10);
		}
		cout << endl<<endl<<endl;
		buildHuffmanTree(complete_string, root);
		ofs.open("HuffmanDecodedString.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		break;
	case 2:
		for (int x = 0; x < 20; x++)
		{
			cout << "=";
			Sleep(10);
		}
		message = "Welcome to Huffman Decoding Program";
		for (int x = 0; x < message.length(); x++)
		{
			cout << message.at(x);
			Sleep(10);
		}
		for (int x = 0; x < 20; x++)
		{
			cout << "=";
			Sleep(10);
		}
		cout << endl;
		ofs.open("HuffmanDecodedString.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		root = pq.top();
		newfile.open("outputtext.txt", ios::in); // open a file to perform read operation using file object
		if (newfile.is_open())
		{ // checking whether the file is open
			newfile >> decode_input;
			Sleep(1000);
			message = "Data to be decoded is:";
			for (int x = 0; x < message.length(); x++)
			{
				cout << message.at(x);
				Sleep(10);
			}
			Sleep(1000);
			cout << endl
				 << decode_input;
			while (decode_input[i])
			{
				switch (decode_input[i])
				{
				case '0':
					str = str + "0000";
					break;
				case '1':
					str = str + "0001";
					break;
				case '2':
					str = str + "0010";
					break;
				case '3':
					str = str + "0011";
					break;
				case '4':
					str = str + "0100";
					break;
				case '5':
					str = str + "0101";
					break;
				case '6':
					str = str + "0110";
					break;
				case '7':
					str = str + "0111";
					break;
				case '8':
					str = str + "1000";
					break;
				case '9':
					str = str + "1001";
					break;
				case 'A':
				case 'a':
					str = str + "1010";
					break;
				case 'B':
				case 'b':
					str = str + "1011";
					break;
				case 'C':
				case 'c':
					str = str + "1100";
					break;
				case 'D':
				case 'd':
					str = str + "1101";
					break;
				case 'E':
				case 'e':
					str = str + "1110";
					break;
				case 'F':
				case 'f':
					str = str + "1111";
					break;
				default:
					cout << "--Invalid Hex Digit (" << str[i] << ")--";
				}
				i++;
			}
			cout<<endl;
			message = "The Huffman Code for this data is:";
			for (int x = 0; x < message.length(); x++)
			{
				cout << message.at(x);
				Sleep(10);
			}
			cout << endl;
			Sleep(1000);
			cout << str;
			Sleep(1000);
			cout<<endl;
			message = "The final decoded data is :";
			for (int x = 0; x < message.length(); x++)
			{
				cout << message.at(x);
				Sleep(10);
			}
			Sleep(1000);
			cout<<endl;
			while (index < (int)str.size() - 2)
			{
				decode(root, index, str);
			}
			newfile.close();
			break;
		default:
			cout << "Wrong input!!!";
		}
		return 0;
	}
	return 0;
}
