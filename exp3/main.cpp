#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>
#include <cstring> // 用于 memset 函数

class BinTreeNode {
public:
    char data;
    int freq;
    std::shared_ptr<BinTreeNode> left, right;

    BinTreeNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// 二叉树类
class BinTree {
public:
    std::shared_ptr<BinTreeNode> root;

    BinTree() : root(nullptr) {}
    BinTree(std::shared_ptr<BinTreeNode> node) : root(node) {}
};

struct Compare {
    bool operator()(std::shared_ptr<BinTreeNode> const& a, std::shared_ptr<BinTreeNode> const& b) {
        return a->freq > b->freq;  // 优先队列基于频率排序
    }
};

class HuffTree : public BinTree {
public:
    HuffTree(const std::unordered_map<char, int>& freq_map) {
        std::priority_queue<std::shared_ptr<BinTreeNode>, std::vector<std::shared_ptr<BinTreeNode>>, Compare> minHeap;

        for (const auto& [ch, freq] : freq_map) {
            minHeap.push(std::make_shared<BinTreeNode>(ch, freq));
        }

        while (minHeap.size() > 1) {
            auto left = minHeap.top(); minHeap.pop();
            auto right = minHeap.top(); minHeap.pop();

            auto merged = std::make_shared<BinTreeNode>('\0', left->freq + right->freq);
            merged->left = left;
            merged->right = right;
            minHeap.push(merged);
        }

        root = minHeap.top();
    }
};

class Bitmap {
private:
    unsigned char* M;
    int N, _sz;

    void init(int n) {
        M = new unsigned char[N = (n + 7) / 8];
        memset(M, 0, N);
        _sz = 0;
    }

public:
    Bitmap(int n = 8) { init(n); }
    ~Bitmap() { delete[] M; M = nullptr; _sz = 0; }

    void set(int k) { M[k / 8] |= (0x80 >> (k % 8)); }
    void clear(int k) { M[k / 8] &= ~(0x80 >> (k % 8)); }
    bool test(int k) { return M[k / 8] & (0x80 >> (k % 8)); }
};

class HuffCode {
public:
    std::unordered_map<char, std::string> huff_map;

    void generateCode(const std::shared_ptr<BinTreeNode>& node, const std::string& code) {
        if (!node) return;
        if (node->data != '\0') {
            huff_map[node->data] = code;
        }
        generateCode(node->left, code + "0");
        generateCode(node->right, code + "1");
    }

    std::string encode(const std::string& text) {
        std::string encoded = "";
        for (const char& ch : text) {
            encoded += huff_map[ch];
        }
        return encoded;
    }
};

int main() {
    // 统计文本中各字母的频率
    std::unordered_map<char, int> freq_map = {
        {'d', 1}, {'r', 1}, {'e', 1}, {'a', 1}, {'m', 1}, {'t', 1}, {'o', 1}, {'y', 1} // 增加 't', 'o', 'y' 的频率
    };

    HuffTree huffTree(freq_map);
    HuffCode huffCode;
    huffCode.generateCode(huffTree.root, "");

    // 编码示例
    std::string word = "dream";
    std::cout << "Encoded word for \"" << word << "\": " << huffCode.encode(word) << std::endl;

    // 对 "today" 进行编码
    std::string word_today = "today";
    std::cout << "Encoded word for \"" << word_today << "\": " << huffCode.encode(word_today) << std::endl;

    return 0;
}
