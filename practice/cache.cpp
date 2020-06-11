class LRUCache {
struct Node {
    int key;
    int value;
};
public:
    LRUCache(int capacity) : _capacity(capacity) {
        _cache = new unordered_map<int, list<Node>::iterator>();
    }
    
    int get(int key) {
        auto it = _cache->find(key);
        if (it == _cache->end()) {
            return -1;
        }
        moveToHead(it->second);
        return it->second->value;
    }
    
    void put(int key, int value) {
        auto it = _cache->find(key);
        if (it == _cache->end()) {
            Node node = {key, value};
            _nodes.push_front(node);
            (*_cache)[key] = _nodes.begin();
            if (_cache->size() > _capacity) {
                int lastKey = _nodes.back().key;
                _cache->erase(lastKey);
                _nodes.pop_back();
            } 
        }else {
            (*it->second).value = value;
            moveToHead(it->second);
        }
    }
    
    void moveToHead(list<Node>::iterator it) {
        Node node = {it->key, it->value};
        _cache.erase(it);
        _nodes.push_front(node);
        (*_cache)[node.key] = _nodes.begin();
    }
    
private:
    int _capacity;
    list<Node> _nodes;
    unordered_map<int, list<Node>::iterator>* _cache;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */



class LRUCache {
struct ListNode {
    ListNode* pre;
    ListNode* post;
    int key;
    int value;
};
public:
    LRUCache(int capacity) {
        _capacity = capacity;
        _count = 0;
        
        head = new ListNode();
        tail = new ListNode();
        head->pre = NULL;
        tail->post = NULL;
        head->post = tail;
        tail->pre = head;
        
        cache = new unordered_map<int, ListNode*>();
    }
    
    void addNodeToHead(ListNode* node) {
        node->post = head->post;
        head->post->pre = node;
        head->post = node;
        node->pre = head;
    }
    
    void removeNode(ListNode* node) {
        ListNode* preNode = node->pre;
        ListNode* postNode = node->post;
        preNode->post = postNode;
        postNode->pre = preNode;
    }
    
    void moveToHead(ListNode* node) {
        removeNode(node);
        addNodeToHead(node);
    }
    
    int get(int key) {
        ListNode* node = (*cache)[key];
        if (node != nullptr) {
            moveToHead(node);
            return node->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        ListNode* node = (*cache)[key];
        if (node != nullptr) {
            node->value = value;
            moveToHead(node);
        }else {
            ListNode* new_node = new ListNode();
            new_node->key = key;
            new_node->value = value;
            addNodeToHead(new_node);
            (*cache)[key] = new_node;
            _count++;
            if (_count > _capacity) {
                //pop last node
                ListNode* last = tail->pre;
                cache->erase(last->key);
                removeNode(last);
                delete last;
                _count--;
            }
        }
        return;
    }
private:
    int _capacity;
    int _count;
    unordered_map<int, ListNode*>* cache;
    ListNode* head;
    ListNode* tail;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


/**/
struct node {
    node(int a, int b, int c, int d) :key(a), value(b), freq(c), time(d) {}
    int key;
    int value;
    int freq;
    int time;
};
struct comp {
    bool operator()(node const* a, node const* b) const {
        if (a->freq != b->freq) {
            return a->freq < b->freq;
        }
        return a->time < b->time;
    }
};
class LFUCache {
public:
    LFUCache(int capacity) {
        MaxSize = capacity;
        time = 0;
    }
    //T(n) = O(lgn)
    //S(n) = O(n)
    int get(int key) {
        if(MaxSize <= 0){return -1;}
        if (mymap.find(key) == mymap.end()) {
            return -1;
        }
        node* it = mymap[key];
        myset.erase(myset.find(it));
        it->freq++;
        time++;
        it->time = time;
        myset.insert(it);
        return it->value;
    }
    //T(n) = O(lgn)
    //S(n) = O(n)
    void put(int key, int value) {
        if(MaxSize <= 0){return;}
        if (mymap.find(key) == mymap.end()) {
            if (mymap.size() == MaxSize) {
                auto LeastUsed = myset.begin();
                mymap.erase((*LeastUsed)->key);
                myset.erase(LeastUsed);
            }
            time++;
            mymap[key] = new node(key, value, 1, time);
            myset.insert(mymap[key]);

        }
        else {
            auto it = mymap[key];
            myset.erase(myset.find(it));
            it->freq++;
            it->value = value;
            myset.insert(it);
        }
    }
private:
    unordered_map<int, node*> mymap;
    set<node*, comp> myset;
    int MaxSize;
    int time;
};
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
