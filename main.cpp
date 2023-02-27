
#include <fstream>
#include <iostream>
#include "priority_queue_min.h"

using namespace std;

void frequency_calculation(string str, unsigned char *&symbol, int *&frequencies, int& n) {
    int frequencies_all_char[256];
    unsigned char c;

    for(int i = 0; i < 256; ++i) {
        frequencies_all_char[i] = 0;
    }

    for(int i = 0; i < str.size(); ++i) {
        ++frequencies_all_char[str[i]];
    }

    for(int i = 0; i < 256; ++i) {
        if(frequencies_all_char[i] > 0) {
            ++n;
        }
    }

    symbol = new unsigned char[n];
    frequencies = new int [n];

    int index = 0;

    for(int i = 0; i < 256; ++i) {
        if(frequencies_all_char[i] > 0) {
            symbol[index] = static_cast<unsigned char>(i);
            frequencies[index] = frequencies_all_char[i];
            ++index;
        }
    }
}


void encode(istream & fin, char *file_output, Priority_Queue_Min &tree) {
    string str;
    fin.clear();
    fin.seekg(0, ios::beg);
    ofstream fout(file_output);
    unsigned char curChar = 0;
    int index = 7;
    while(getline(fin, str)) {
        str += '\n';
        for (int i = 0; i < str.size(); ++i) {
            string cur = tree.Encode(str[i]);
            for (int j = 0; j < cur.size(); ++j) {
                if (cur[j] == '1') {
                    curChar |= (1 << index);
                } else {
                    curChar &= ~(1 << index);
                }
                if (index == 0 ) {
                    fout << curChar;
                    index = 7;
                } else {
                    --index;
                }
            }
        }
    }

}

void decode(char *file_encode, char *file_decode, Priority_Queue_Min& tree, Node *root_huffman) {
    ifstream code_file(file_encode);
    ofstream decode_file(file_decode);
    string cur;
    string str;
    unsigned char c;
    while (true) {
        if (code_file.eof()) {//end of file
            break;
        }
        c = code_file.get();
        int index = 8;
        while (index > 0) {
            if (c & (1 << 7)) {
                cur += '1';
            } else {
                cur += '0';
            }
            c <<= 1;
            string decode = tree.Decode(cur, root_huffman);
            if (!decode.empty()) {
                decode_file << decode;
                cur = "";
		if (code_file.eof()) {//end of file
            		break;
        	}

            }
            --index;
        }
    }
}


int main(int argc, char* argv[]) {
    int n = 0;
    unsigned char *symbol = nullptr;
    int *frequencies = nullptr;
    string str;
    string tmp;
    ifstream fin(argv[1]);

    while(getline(fin, tmp)) {
        str += '\n';
        str += tmp;
    }
    frequency_calculation(str, symbol, frequencies, n);

    Priority_Queue_Min tree(n, symbol, frequencies);
    Node* root_huffman = tree.Build_Huffman_Tree();
    tree.Gen_Huffman_leaf(root_huffman);
    encode(fin, argv[2], tree);
    decode(argv[2], argv[3], tree, root_huffman);

    return 0;
}
