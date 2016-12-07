//
// Created by mark on 16-12-7.
//

#include <iostream>
#include <queue>

using std::queue;
using std::cout;
using std::endl;

template <typename T>
class PseudoQueue{
public:
    void push(const T &value);
    const T& pop();
    const T& top();
    bool empty();
private:
    queue<int> que;
};

template <typename T>
void PseudoQueue<T>::push(const T &val) {
    que.push(val);
    for(int i = 0; i < que.size() - 1; ++i){
        que.push(que.front());
        que.pop();;
    }
}

template <typename T>
const T& PseudoQueue<T>::pop(){
    que.pop();
}

template <typename T>
const T& PseudoQueue<T>::top(){
    return que.front();
}

template <typename T>
bool PseudoQueue<T>::empty() {
    return que.empty();
}

int main(int argc, char **argv){
    PseudoQueue<int> pq;
    for(int x = 0; x < 5; ++x){
        pq.push(x+1);
    }
    while(!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}