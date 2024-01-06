#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <bitset>
#include <chrono>

struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

void encode(Node* root, std::string str, std::unordered_map<char, std::string> &huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void serializeTree(Node* root, std::ofstream& out, char escapeChar = '\\') {
    if (root == nullptr) {
        return;
    }

    if (root->ch == '\0') {
        out << escapeChar << "#";
    } else if (root->ch == '\n') {
        out << escapeChar << "n";
    } else if (root->ch == escapeChar || root->ch == ',') {
        out << escapeChar << root->ch;
    } else {
        out << root->ch;
    }

    out << "," << (root->left != nullptr) << "\n";
    serializeTree(root->left, out, escapeChar);
    serializeTree(root->right, out, escapeChar);
}

Node* reconstructTree(std::ifstream& in, char escapeChar = '\\') {
    std::string line;
    if (!getline(in, line)) {
        return nullptr;
    }

    std::stringstream linestream(line);
    std::string nodeData;
    char ch;
    bool hasChildren;

    int pos = 0;
    
	if (line[pos] == escapeChar) {
		if (pos + 1 < line.length()) {
			char nextChar = line[pos + 1];
			if (nextChar == '#') {
                ch = '\0';
            } else if (nextChar == 'n') {
				ch = '\n';
			} else {
				ch = nextChar;
			}
			pos += 2;
		}
	} else if (line[pos] != ',') {
		ch = line[pos];
		pos++;
    } 

    pos++;

    hasChildren = (line[pos] == '1');

    Node* node = getNode(ch, 0, nullptr, nullptr);
    if (hasChildren) {
        node->left = reconstructTree(in);
        node->right = reconstructTree(in);
    }
    return node;
}

Node* buildTreeFromSerialization(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return nullptr;
    }
    return reconstructTree(in);
}

void writeEncodedStringToBinaryFile(const std::string& encodedString, const std::string& outputFile) {
    std::ofstream output(outputFile, std::ios::binary);
	
    if (!output.is_open()) {
        std::cerr << "Error opening file for writing: " << outputFile << std::endl;
        return;
    }

    unsigned int length = encodedString.length();
    output.write(reinterpret_cast<char*>(&length), sizeof(length));

    uint32_t buffer = 0;
    uint32_t bufferBits = 0;

    for (char c : encodedString) {
        buffer = (buffer << 1) | (c == '1'); 
        bufferBits++;

        if (bufferBits == 32) {
            for (int i = 3; i >= 0; --i) {
                char byte = (buffer >> (i * 8)) & 0xFF;
                output.write(&byte, 1);
            }
            buffer = 0;
            bufferBits = 0;
        }
    }

    if (bufferBits > 0) {
        buffer <<= (32 - bufferBits);

        int bytesToWrite = (bufferBits + 7) / 8;

        for (int i = 3; i >= 3 - bytesToWrite + 1; --i) {
            char byte = (buffer >> (i * 8)) & 0xFF;
            output.write(&byte, 1);
        }
    }

    output.close();
}


void buildHuffmanTree(std::string text) {
    std::unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, comp> pq;

    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    Node* root = pq.top();

    std::unordered_map<char, std::string> huffmanCode;
    encode(root, "", huffmanCode);

    std::string str = "";
    for (char ch: text) {
        str += huffmanCode[ch];
    }

    writeEncodedStringToBinaryFile(str, "encoded.bin");

    std::ofstream tree_file("huffman_tree.txt");
    serializeTree(root, tree_file);
    tree_file.close();
}


void decodeFromFile(Node* root, const std::string& encodedFile, const std::string& decodedFile) {
    std::ifstream input(encodedFile, std::ios::binary);
    std::ofstream output(decodedFile);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    unsigned int length;
    input.read(reinterpret_cast<char*>(&length), sizeof(length));

    Node* current = root;
    char byte;
    int bitCount = 0;

    while (input.get(byte) && bitCount < length) {
        for (int i = 7; i >= 0 && bitCount < length; --i, ++bitCount) {
            if (byte & (1 << i)) {
                current = current->right;
            } else {
                current = current->left;
            }

            if (!current->left && !current->right) {
                output << current->ch;
                current = root;
            }
        }
    }

    input.close();
    output.close();
}

int main()
{
    std::string path = "input.txt";
    std::ifstream file(path);
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    if (text.empty()) {
        std::cerr << "File is empty or not found: " << path << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    buildHuffmanTree(text);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by buildHuffmanTree: " << duration.count() << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    Node* root = buildTreeFromSerialization("huffman_tree.txt");
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by buildTreeFromSerialization: " << duration.count() << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decodeFromFile(root, "encoded.bin", "decoded.txt");
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by decodeFromFile: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}