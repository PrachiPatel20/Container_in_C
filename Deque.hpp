#define Deque_DEFINE(t)                                                         \
struct Deque_##t##_Iterator{                                                    \
        struct Deque_##t *deq;                                                  \
        int counter;                                                            \
        bool flag;                                                              \
        void (*inc)(Deque_##t##_Iterator *);                                    \
        void (*dec)(Deque_##t##_Iterator *);                                    \
        t &(*deref)(Deque_##t##_Iterator *);                                    \
    };                                                                          \
struct Deque_##t {                                                              \
        t *data;                                                                \
        int start;                                                              \
        size_t count;                                                           \
        size_t capacity;                                                        \
        char type_name[6+sizeof(#t)]="Deque_";                           	\
        size_t (*size)(Deque_##t *);                                            \
        bool (*empty)(Deque_##t *);                                             \
        void (*push_back)(Deque_##t *, t);                                      \
        void (*push_front)(Deque_##t *, t);                                     \
        void (*pop_back)(Deque_##t *);                                          \
        void (*pop_front)(Deque_##t *);                                         \
        t &(*back)(Deque_##t *);                                                \
        t &(*front)(Deque_##t *);                                               \
        t &(*at)(Deque_##t *, size_t);                                          \
        void (*clear)(Deque_##t *);                                             \
        void (*dtor)(Deque_##t *);                                              \
        Deque_##t##_Iterator (*begin)(Deque_##t *);                             \
        Deque_##t##_Iterator (*end)(Deque_##t *);                               \
        bool (*compare)(const t&, const t&);                                  	\
        void (*sort)(Deque_##t *, Deque_##t##_Iterator, Deque_##t##_Iterator);  \
        int (*simple)(int);                                                     \
    };                                                                          \
    void inc(Deque_##t##_Iterator *it) {			                \
        it->counter++;                                                          \
        it->counter = it->counter % it->deq->capacity;                          \
    }                                                                           \
    void dec(Deque_##t##_Iterator *it) {	                                \
        it->counter--;                                                          \
	if(it->counter < 0) {							\
	    it->counter = it->deq->capacity - 1;				\
	}									\
    }                                                                           \
    t &deref(Deque_##t##_Iterator * it) {	                                \
        return it->deq->data[it->counter];                                      \
    }                                                                           \
    size_t size(Deque_##t *ob) {                                                \
        return ob->count;                                                       \
    }                                                                           \
    bool empty(Deque_##t *ob) {                                                 \
        return ob->count == 0;                                                  \
    }                                                                           \
    void allocateSize(Deque_##t *ob) {		                               	\
	ob->capacity = 2* ob->capacity;						\
        t *newData = (t *) malloc(ob->capacity * sizeof(t));                    \
        for(int i = 0; i<ob->count;i++) {                              		\
            newData[i] = ob->data[(i+ob->start)%ob->capacity];                  \
        }                                                                       \
        ob->start = 0;                                                          \
        free(ob->data);                                                         \
        ob->data = newData;                                                     \
    }                                                                           \
    void push_back(Deque_##t *ob, t mc) {                                       \
        if(ob->capacity == ob->count) {                                         \
            allocateSize(ob);                                                   \
	}									\
        ob->data[(ob->start + ob->count)%ob->capacity] = mc;                    \
        ob->count++;                                                            \
    }                                                                           \
    void push_front(Deque_##t *ob, t mc) {                                      \
        if(ob->capacity == ob->count)                                           \
            allocateSize(ob);                                                   \
        ob->start = ob->start-1;                                                \
	if(ob->start < 0) {							\
	    ob->start = ob->capacity - 1;					\
	}									\
        ob->data[ob->start] = mc;                                               \
        ob->count++;                                                            \
    }                                                                           \
    void pop_back(Deque_##t * deque) {				                \
        deque->count--;                                                         \
    }                                                                           \
    void pop_front(Deque_##t * deque) {		                                \
        deque->start++;                                                         \
        deque->start = deque->start % deque->capacity;                          \
        deque->count--;                                                         \
    }                                                                           \
    t &back(Deque_##t * ob) {                                                   \
        return ob->data[(ob->start + ob->count-1)%ob->capacity];                \
    }                                                                           \
    t &front(Deque_##t * deque) {                                               \
        return deque->data[deque->start];                                       \
    }                                                                           \
    t &at(Deque_##t * deque, size_t i) {				        \
        return deque->data[(deque->start+i) % deque->capacity];                 \
    }                                                                           \
    void clear(Deque_##t *deq) {                				\
    }                                                                           \
    void dtor(Deque_##t *deq) {                                                 \
        free(deq->data);                                                        \
    }                                                                           \
    Deque_##t##_Iterator begin(Deque_##t * deque) {		               	\
        Deque_##t##_Iterator it;                                                \
        it.deq = deque;                                                         \
        it.counter = deque->start;                                              \
        it.inc = &inc;                                                          \
        it.deref = &deref;                                                      \
        it.flag = false;                                                        \
        it.dec = &dec;                                                          \
        return it;                                                              \
    }                                                                           \
    Deque_##t##_Iterator end(Deque_##t * deque) {	                        \
        Deque_##t##_Iterator it;                                                \
        it.counter = (deque->start + deque->count) % deque->capacity;           \
        it.deq = deque;                                                         \
        it.deref = &deref;                                                      \
        it.dec = &dec;                                                          \
        return it;                                                              \
    }                                                                           \
    void swap(Deque_##t *deque, int index1, int index2) {                       \
        t temp = deque->data[index1];                                           \
        deque->data[index1] =  deque->data[index2];                             \
        deque->data[index2] = temp;                                             \
    }                                                                           \
    int randomizedPartition(Deque_##t *deque, Deque_##t##_Iterator low, Deque_##t##_Iterator high) {                                             	\
        int pivot1 = rand()%((high.counter - low.counter) + 1) + low.counter;   \
        swap(deque, pivot1, high.counter);                                      \
        t pivot = deque->data[high.counter];                                  	\
        int i=low.counter-1;                                                    \
        for(int j=low.counter;j<high.counter;j++) {	                      	\
            if(deque->compare(deque->data[j], pivot)) {                         \
                i++;                                                            \
                swap(deque, i, j);                                              \
            }                                                                   \
        }                                                                       \
        swap(deque, i+1, high.counter);                                         \
        return (i+1);                                                           \
    }                                                                           \
    void randomizedQuickSort(Deque_##t *deque, Deque_##t##_Iterator low, Deque_##t##_Iterator high) {	                                           	\
	if(low.counter < high.counter) {					\
	    int pivot = randomizedPartition(deque, low, high);			\
	    Deque_##t##_Iterator pit = low;					\
	    pit.counter = pivot - 1;						\
	    randomizedQuickSort(deque, low, pit);				\
	    pit.counter = pivot + 1;						\
	    randomizedQuickSort(deque, pit, high);				\
	}									\
    }                                                                           \
    void sort(Deque_##t *deque, Deque_##t##_Iterator low, Deque_##t##_Iterator high) {                                                                         \
        high.counter--;                                                         \
        if(high.counter < 0) {                                                  \
            high.counter = deque->capacity - 1;                                 \
	}									\
        randomizedQuickSort(deque, low, high);                                  \
    }                                                                           \
    Deque_##t *Deque_##t##_ctor(Deque_##t *deque, bool (*compare1)(const t &, const t &)) {     								\
        deque->capacity = 10;                                                   \
        deque->data = (t *) malloc(deque->capacity * sizeof(t));                \
        deque->size = &size;                                                    \
	strcpy(deque->type_name,#t);						\
        deque->empty = &empty;                                                  \
        deque->push_back = &push_back;                                          \
        deque->push_front = &push_front;                                        \
        deque->pop_back = &pop_back;                                            \
        deque->pop_front = &pop_front;                                          \
        deque->front = &front;                                                  \
        deque->back = &back;                                                    \
        deque->clear = &clear;                                                  \
        deque->dtor = &dtor;                                                    \
        deque->at = &at;                                                        \
        deque->begin= &begin;                                                   \
        deque->end= &end;                                                       \
        deque->start = 0;                                                       \
        deque->count = 0;                                                       \
        deque->sort = &sort;                                                    \
        deque->compare = compare1;                                              \
    }                                                                           \
    bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2) {                                                                          \
        if(it1.counter == (it2.deq->start+it2.deq->count)% it2.deq->capacity) { \
            return true;                                                        \
	}									\
    }                                                                           \
    bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2) {                    \
        int capacity = deq1.capacity;                                           \
        if(deq1.count != deq2.count || deq1.start != deq2.start) {              \
            return false;                                                       \
	}									\
        t *m1 = deq1.data;                                                    	\
        t *m2 = deq2.data;                                                    	\
        int count = 0;                                                          \
        bool flag = true;                                                       \
        for(int i=0;i<deq1.count;i++)                                           \
        {                                                                       \
	    if(flag == false) {							\
		break;								\
	    }									\
            int current = (i+deq1.start) % deq1.capacity;                       \
            bool check1 = deq1.compare(m1[current],m2[current]);                \
            bool check2 = deq1.compare(m2[current],m1[current]);                \
	    if(deq1.compare(m1[current],m2[current]) || deq1.compare(m2[current],m1[current])) {									\
		flag = false;							\
	    }									\
        }                                                                       \
        return flag;                                                            \
    }                                                                           
