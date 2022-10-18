class LRUCache {
public:
    class Node {
      public:
      int val,key;
      Node *next,*prev;
      Node(int k, int ky) {
          val=k;
          key=ky;
          next=prev=NULL;
      }
    };
    map<int,Node*> mp;
    Node *head=new Node(-1,-1), *tail=new Node(-1,-1);
    int capacity;
    LRUCache(int cap) {
        capacity=cap;
        head->prev= tail;
        tail->next= head;
    }
     
    void addNode(Node *curr) {
        Node *headPrev = head->prev;
        headPrev->next = curr;
        curr->prev = headPrev;
        curr->next = head;
        head->prev = curr;
    }
    void deleteNode(Node *curr) {
        Node* prv = curr->prev;
        Node* nxt = curr->next;
        prv->next = nxt;
        nxt->prev = prv;   
    }
    int get(int key) {
        
        if(mp.find(key)==mp.end()) { return -1; }
        Node *curr = mp[key];
        deleteNode(curr);
        addNode(curr); 
        return curr->val;
    }
    
    void put(int key, int value) { 
        if(mp.find(key)==mp.end()) {
            Node *nw = new Node(value,key);
            mp[key] = nw;
            addNode(nw);
        }
        else {
            Node *curr = mp[key];
            deleteNode(curr);
            addNode(curr);
            curr->val = value;
        } 
        if(mp.size()>capacity) {
            Node *toDelete = tail->next; 
            deleteNode(toDelete);
            mp.erase(toDelete->key);
        } 
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
