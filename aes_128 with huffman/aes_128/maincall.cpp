#include <iostream>
#include "huffman.cpp"
#include "AES.cpp"
int main()
{
	cout << endl
		 << endl;
	string message;
	int i = 2;
	int choice;
	for (int x = 0; x < 20; x++)
	{
		cout << "=";
		Sleep(10);
	}
	message = "Welcome to our Minor 1 project presentation";
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
	cout << endl
		 << endl;
	message = "Enter 1 for encoding and encryption :";
	for (int x = 0; x < message.length(); x++)
	{
		cout << message.at(x);
		Sleep(10);
	}
	cout << endl;
	message = "Enter 2 for decoding and decryption :";
	for (int x = 0; x < message.length(); x++)
	{
		cout << message.at(x);
		Sleep(10);
	}
	cout << endl;
	while (i != 0)
	{
		message = "Enter your choice :";
		cout << endl;
		for (int x = 0; x < message.length(); x++)
		{
			cout << message.at(x);
			Sleep(10);
		}
		cin >> choice;

		switch (choice)
		{
		case 1:
			runHuffman(1);
			aes(1);
			break;
		case 2:
			aes(2);
			runHuffman(2);
			i = 0;
			break;
		default:
			cout << "Your entered an unknown request ! " << endl;
			return -1;
		}
	}

	cout << endl
		 << endl;
}