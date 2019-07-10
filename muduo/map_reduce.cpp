// g++  map_reduce.cpp  -std=c++11  -o count
#include <boost/noncopyable.hpp> 
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <boost/ptr_container/ptr_vector.hpp> 
#include <memory>

using namespace std;

// shuffle将大文件hash大不同的小文件中
class Sharder : public boost::noncopyable {
public:
    explicit Sharder(int nbuckets):_nbuckets(nbuckets) {
        // 根据nbuckets的个数,输出的shuffle文件名放入buckets
        for (int i = 0; i < nbuckets; ++i) {
            char buf[256];
            snprintf(buf, sizeof(buf), "%05d-of-%05d", i, nbuckets);
            _buckets.push_back(new ofstream(buf));
        }
    }
    void output(const std::string& word, int count) {
        //int index = std::hash<string>()(word) % _nbuckets.size();
        // 将word词hash为输出到不同的文件,
        int index = std::hash<string>()(word) % _nbuckets;
        _buckets[index] << word << "\t" << count << "\n";
    }

private:
    int _nbuckets;
    boost::ptr_vector<std::ofstream> _buckets;
};

//读入文件hash为小文件
void shard(int nbuckets, int argc, char *argv[]) {
    Sharder shard(nbuckets);
    int kMaxSize = 10 * 1000 * 1000;
    // first为word,second为word的次数
    std::unordered_map<std::string, int> word_counts;
    for (int i = 1; i < argc; ++i) {
        std::ifstream in(argv[i]);
        while (in && !in.eof()) {
            word_counts.clear();
            std::string word;
            while(in >> word) {
                word_counts[word]++;
                // 读完10M内存,hash到不同的小文件
                if (word_counts.size() > kMaxSize) {
                    break;
                }
            }
            // 将读完10M内存的word词频,hash到不同的小文件
            for (const auto& ite : word_counts) {
                shard.output(ite.first, ite.second);
            }
        }
    }
}

// 将单个文件中的word统计出现的次数
std::unordered_map<std::string, int> read_shard(int index, int nbuckets) {
    std::unordered_map<std::string, int> word_count;
    char buf[256];
    snprintf(buf, sizeof(buf), "%05d-of-%05d", index, nbuckets);
    std::string line;
    std::ifstream in(buf);
    while (getline(in, line)) {
        size_t tab = line.find('\t');
        if (tab != std::string::npos) {
            int count = strtol(line.c_str()+tab, nullptr, 10);
            // shuffle文件中,所有相同的word的频次相加
            word_count[line.substr(0, tab)] += count;
        }    
    }
    // 删除shuffle的小文件
    unlink(buf);
    return word_count;
}

//每个小文件的word可以读入内存,按照word次数从大到小排序,写入reduce文件
void sort_shards(int nbuckets) {
    vector<std::pair<int, std::string>> words;
    //遍历所有的小文件
    for (int i = 0; i < nbuckets; ++i) {
        words.clear();
        for (const auto& ite : read_shard(i, nbuckets)) {
            words.push_back(make_pair(ite.second, ite.first));
        }
        //sort(words.begin(), words.end(), [](std::pair<int, std::string> a, std::pair<int, std::string> b){
        //文件行按照出现单词频次从大到小排序
        sort(words.begin(), words.end(),
                [](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b){
            return a.first > b.first;
        });
        char buf[256];
        snprintf(buf, sizeof(buf), "%05d-of-%05d-reduce", i, nbuckets);
        //将合并次数并且排序的vector,输出到reduce文件
        std::ofstream output(buf);
        for (const auto& ite : words) {
            output << ite.second << "\t" << ite.first << "\n";
        }
    }
}


class Source {
public:
    //explicit Source(std::ifstream* in):_in(in),_count(0),_word() {
    explicit Source(const shared_ptr<std::ifstream>& in):_in(in),_count(0),_word() {
    }
    bool next() {
        std::string line;
        //if(getline(*_in, line)) {
        if(getline(*_in, line)) {
            size_t tab = line.find("\t");
            _word = line.substr(0, tab);
            _count = strtol(line.c_str()+tab, nullptr, 10);
            return true;
        }
        return false;
    }
    bool operator < (const Source& source) {
        return _count < source._count;
    }
    void output(std::ofstream& out) {
        out << _word << "\t" << _count << "\n";
    }
private:
    //std::ifstream* _in;
    shared_ptr<std::ifstream> _in;
    std::string _word;
    int _count;
};

void merge(int nbuckets) {
    vector<Source> keys;
    //shared_ptr<std::ifstream[]> inputs;
    //vector<shared_ptr<std::ifstream>> inputs;
    for (int i = 0; i < nbuckets; ++i) {
        char buf[256];
        snprintf(buf, sizeof(buf), "%05d-of-%05d-reduce", i, nbuckets);
        //inputs[i] = make_shared<std::ifstream>(buf);
        //Source source(inputs[i].get());
        //Source source(inputs[i]);
        Source source(make_shared<std::ifstream>(buf));
        // 判断reduce是否有下一行,如果存在放入vector 
        if (source.next()) {
            keys.push_back(source);
        }
        unlink(buf);
    }
    // merge的文件名
    std::ofstream output("output");
    // 构建最大堆,大小依据Source中每个单词的count频次
    make_heap(keys.begin(), keys.end());
    while (!keys.empty()) {
        // 将堆顶移动到末尾,vector的back为当前堆最大值
        pop_heap(keys.begin(), keys.end());
        // 将最大值写入merge的outout文件
        keys.back().output(output);
        // 判断堆顶的文件是否有下一行
        if (keys.back().next()) {
            // 堆顶文件存在下一行,将新一行添加入堆中
            std::push_heap(keys.begin(), keys.end());
        } else {
            // 如果reduce文件不存在新一行,则从vector中pop
            keys.pop_back();
        }
    }
}

int main(int argc, char* argv[]) {
    int nbuckets = 5;
    shard(nbuckets, argc, argv);
    sort_shards(nbuckets);
    merge(nbuckets);
}

