#ifndef Lab1_h
#define Lab1_h
#include <iostream>
/**
 * \brief Basic singly-lined list implementation.
 */
template<typename Key, typename Info>
class Sequence{
    /**
     * \brief Individual node of a list.
    */
    struct Node{
        Key key;
        Info info;
        Node* next;
        
        Node(const Key& vKey, const Info& vInfo, Node* vnext = nullptr):
            key(vKey),
            info(vInfo),
            next(vnext) {}
    };
    /**
     *  Pointer to a head.
    */
    Node* head;
    /**
     * Copies toCopy number of elements from the curr Node to the copy Node
     * @param[in] x : A Sequence from which we copy the elements.
    */
    bool copyElements(const Sequence<Key, Info>& x);
    /**
     *  Moves Node* reference to the end of the list. \n
     *  If nullptr the list is empty.
    */
    void getLastElement(Node*& curr);
    /**
     *  Outputs list elements into the ostream.
    */
    void getElements(std::ostream& os) const;
    /**
     *  Finds an element (vKey) and its previous element according to the given occurence. \n
     *  @return : True - if element has been found, False - otherwise.
     */
    bool find(Node*& curr, Node*& prev, const Key& vKey, int occurrence = 1) const;
public:
	class iterator {
    	friend Sequence<Key, Info>;
    	mutable Node* current;
    	/**
     	*  Node constructor.
    	*/
    	iterator(Node* x): current(x) {};
    public:
    	/**
     	*  Copy constructor.
    	*/
    	iterator(const iterator& x): current(x.current) {}
    	
    	~iterator() = default;
    	/**
     	*  Assign operator.
    	*/
    	iterator& operator=(const iterator& x) { 
			current = x.current; 
			return *this; 
		}
    	/**
     	*  Equal to operator.
    	*/
		bool operator==(const iterator& x) const { 
			return current == x.current; 
		}
		/**
     	*  Not equal to operator.
    	*/
		bool operator!=(const iterator& x) const { 
			return current != x.current; 
		}
		/**
     	*  Postfix increment operator.
    	*/
		const iterator& operator++() const { 
            if (!current->next)
                throw "Next does not exist!";
			current = current->next; 
			return *this; 
		}
		/**
     	*  Prefix increment operator.
    	*/
		iterator operator++(int) const {
            if (!current->next)
                throw "Next does not exist!";
			iterator curr(*this); 
			current = current->next; 
			return curr; 
		}
		/**
     	*  Asterix operator.
    	*/
		Info& operator*() { 
            if (!current)
                throw "Current does not exist!";
			return current->info; 
		};
		/**
     	*  Constant asterix operator.
     	*  @return: Key value.
    	*/
		const Info& operator*() const {
            if (!current)
                throw "Current does not exist!";
			return current->info; 
		};
		/**
     	*  Pointer to member
     	*  @return: Key value.
    	*/
		Info* operator->() { 
            if (!current)
                throw "Current does not exist!";
			return current->info; 
		};
		/**
     	*  Constant pointer to member
     	*  @return: Key value.
    	*/
		const Info* operator->() const { 
            if (!current)
                throw "Current does not exist!";
			return current->info; 
		};
		/**
     	*  Outputs the key.
     	*  @return: Key value.
    	*/
		const Key& getKey() const { 
			return current->key; 
		}
		/**
     	*  Outputs the info.
     	*  @return: Info value.
    	*/
		const Info& getInfo() const { 
			return current->info; 
		}
		/**
     	*  Inserts the element after the iterator.
     	*  @return: Info value.
    	*/
		iterator insert_after(const Key& key, const Info& info){
			Node* loc = current;
			if(loc != nullptr){
				Node* loc = new Node(key, info, current->next);
				current->next = loc;
				return iterator(loc);
			} else {
				throw "List is empty!";
			}
		}
	};
    /**
     * Constructs the list.
     */
    Sequence();
    /**
     * Copy constuctor.
     */
    Sequence(const Sequence<Key, Info>& x);
    /**
     * Destructs the list
     */
    ~Sequence();
    /**
     *  Assign values to the container
    */
    Sequence<Key, Info>& operator=(const Sequence<Key, Info>& x);
    /**
     *  Iterator to first element of the list.
    */
    iterator begin() const { 
		return iterator(head); 
	};
    /**
     *  Iterator to last element of the list + 1.
    */
	iterator end() const { 
		return iterator(nullptr); 
	};
	/**
     *  Method finding an element.
    */
	iterator find(const Key& vKey, int occurrence = 1) const;
	/**
    *  Clears all of the elements of the list.
    */
    void clear();
    /**
     *  Outputs information about the status of the elements.
     *  @return : False - if there are elements in the list, True - otherwise.
    */
    bool empty() const;
    /**
     * Pushes value and key to the front of the list.
     * @param[in] key : Key
     * @param[in] info : Info
     */
    void push_front(const Key& key, const Info& info);
    /**
     * Pushes value and key to the front of the list.
     * @param[in] key : Key
     * @param[in] info : Info
     */
    void push_front(const iterator& it);
    /**
     * Pushes value and key after the given occurence number of Key.
     * @param[in] key : Key to be inserted.
     * @param[in] info : Info to be inserted
     * @param[in] where : Element after which we want to insert.
     * @param[in] occurrence : Number of occurences of a where. 1 by default.
     * @return : True - if element has been added, False - otherwise.
     */
    bool push_after(const Key& key, const Info& info, const Key& where, int occurrence = 1);
    /**
     * Deletes the first element of the list.
     * @return : True - first element was deleted. False - otherwise.
     */
    bool pop_front();
    /**
     * Removes a given occurence of a Key
     * @param[in] key : Key
     * @param[in] occurrence : Occurence of a key.
     * @return : True - element was deleted. False - otherwise.
     */
    bool remove(const Key& key, int occurrence=1);
    /**
     * Overloading the << operator.
     */
    template<typename A, typename B>
    friend std::ostream& operator<<(std::ostream& os, const Sequence<A, B>& x);
};

template<typename Key, typename Info>
Sequence<Key, Info>::Sequence(): head(nullptr)
{}

template<typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& x): head(nullptr)
{
	*this = x;
}

template<typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
    clear();
}

template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info>& x){
    if(this != &x){
        Node* curr = nullptr;
        Node* copy = x.head;
        clear();
        copyElements(curr, copy);
    }
    return *this;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::copyElements(const Sequence<Key, Info>& x){
    Node* copy = x.head;
    Node* curr = head;
    while(copy){
        Node* element = new Node(copy->key, copy->info);
        if(!element)
            return false;
        if(!head)
            head = element;
        else
            curr->next = element;
        curr = element;
        copy = copy->next;
    }
    return true;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::getLastElement(Node*& curr){
    curr = head;
    if(curr){
        while(curr->next){
            curr = curr->next;
        }
    }
}

template<typename Key, typename Info>
void Sequence<Key, Info>::getElements(std::ostream& os) const{
    Node* curr = head;
    while(curr){
        os << "Key: "<<curr->key<<", info: "<<curr->info<<std::endl;
        curr = curr->next;
    }
}

template<typename Key, typename Info>
typename Sequence<Key, Info>::iterator Sequence<Key, Info>::find(const Key& vKey, int occurrence) const {
	Node* curr = head;
	Node* prev = nullptr;
	if(!find(curr, prev, vKey, occurrence)){
		return iterator(nullptr);
	}
	return iterator(curr);
}

template<typename Key, typename Info>
void Sequence<Key, Info>::clear(){
    while(!empty()){
        pop_front();
    }
    head = nullptr;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::find(Node*& curr, Node*& prev, const Key& vKey, int occurrence) const{
    curr = head;    
	prev = nullptr;

	while(curr != nullptr and occurrence != 0) {
        if(curr->key == vKey){
            if(--occurrence == 0)
                return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::empty() const{
    return head == nullptr;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key& key, const Info& info){
    Node* element = new Node(key, info, head);
    head = element;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::push_front(const iterator& it){
   	Node* element = new Node(it.getKey(), it.getInfo(), head);
   	head = element;
}
	
template<typename Key, typename Info>
bool Sequence<Key, Info>::push_after(const Key& key, const Info& info, const Key& where, int occurrence){
    Node* curr = head;
    Node* prev = nullptr;
    if(find(curr, prev, where, occurrence)){
        Node* newElem = new Node(key, info, curr->next);
        curr->next = newElem;
        return true;
    } else {
        return false;
    }
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::pop_front(){
	if(!empty()){
		Node* curr = head;
	    curr = curr->next;
	    delete head;
	    head = curr;
	    return true;
	}
	return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::remove(const Key& key, int occurrence){
    Node* curr = head;
    Node* prev = nullptr;
    if(find(curr, prev, key, occurrence)){
        if(prev == head){
            pop_front();
        } else {
            prev->next = curr->next;
            delete curr;
        }
        return true;
    }
    return false;
}

template<typename Key, typename Info>
std::ostream& operator<<(std::ostream& os, const Sequence<Key, Info>& x){
    x.getElements(os);
    return os;
}
#endif /* Lab1_h */
