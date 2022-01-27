// HuffmanCoding.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <iomanip>

#define pa std::pair<int,int> //优先队列使用pair数据结构，其中first为出现次数，second为字符id

int child[60][2] = {}; //哈夫曼树上父节点的两个子节点
int num[60] = {}; //每个节点的权重（字符的出现次数）
int tot, root, ans = 0; //哈夫曼树上的点数，哈夫曼树的根节点，文本转化为哈夫曼编码的比特数

void InputData(char* a, int& size); //输入数据并将大写字母转换为小写，其他字符转化为'#'
void getNum(char* str, int size); //统计每种字符出现次数
void GetHuffman(); //构造哈夫曼编码
void OutputHuffman(int fa, std::string code); //输出每个字符的哈夫曼编码

void InputData(char* a,int &size) {
    std::ifstream data;
    data.open("Input.txt");
    int i = 0;
    while ((a[i] = data.get()) != EOF) {
        if (a[i] >= 'A' && a[i] <= 'Z')a[i] = a[i] - 'A' + 'a';
        else if (a[i]>'z'||a[i]<'a') {
            a[i] = '#';
        }
        ++i;
    }size = i;
}
void getNum(char* str, int size) {
    for (int i = 0; i < 30; ++i)num[i] = 0;
    for (int i = 0; i < size; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z')++num[str[i] - 'a'];
        else ++num[26];
    }
    tot = 27;
}
void GetHuffman() {
    std::priority_queue<pa, std::vector<pa>, std::greater<pa>>q;
    for (int i = 0; i <= 26; ++i) {
        if (num[i] <= 0)continue;
        q.push(std::make_pair(num[i], i));
    }ans = 0;
    while (!q.empty()) {
        pa x = q.top();
        q.pop();
        if (q.empty()) {
            root = x.second;
            break;
        }
        pa y = q.top();
        q.pop();
        num[tot] = x.first + y.first;
        ans += num[tot];
        child[tot][0] = x.second;
        child[tot][1] = y.second;
        q.push(std::make_pair(num[tot], tot));
        ++tot;
    }
}
void OutputHuffman(int fa, std::string code) {
    if (fa < 27) {
        std::cout << "字符：";
        if (fa == 26) std::cout << '#' << "  ";
        else std::cout << char('a' + fa) << "  ";
        std::cout.setf(std::ios::left);
        std::cout << "出现次数：" << std::setfill(' ') << std::setw(4) << num[fa] << "  ";
        std::cout << "哈夫曼编码：" << code << std::endl;
        return;
    }
    OutputHuffman(child[fa][0], code + '0');
    OutputHuffman(child[fa][1], code + '1');
}
int main()
{
    std::cout << "Hello World!\n";
    int size = 0;
    char* str = new char[5000];
    std::cout << "开始读入文本\n";
    InputData(str, size);
    std::cout << "文本定长编码后的总长度为 " << size * 5 << std::endl;
    std::cout << "开始计算哈夫曼编码\n";
    getNum(str,size);
    GetHuffman();
    std::cout << "文本哈夫曼编码后的总长度为 " << ans << std::endl;
    OutputHuffman(root,"");
    delete[]str;
    return 0;
}
