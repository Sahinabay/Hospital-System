#ifndef SORTED_LIST_IMPL_H
#define SORTED_LIST_IMPL_H

template<class T>
SortedListNode<T>::SortedListNode(T* itemIn,
                                  SortedListNode* nextNodeIn,
                                  SortedListNode* prevNodeIn)
    : item(itemIn)
    , next(nextNodeIn)
    , prev(prevNodeIn)
{}

template<class T>
SortedList<T>::SortedList()
    : head(NULL)
    , back(NULL)
{}

template<class T>
SortedList<T>::SortedList(const SortedList& other)
    : head(NULL)
    , back(NULL)
{
    if(other.head==NULL){
        head=NULL;
        back=NULL;
    }
    else{
        SortedListNode<T>* currOther=other.head;
        while(currOther!=NULL){
            T* nw= new T(*currOther->item);
            SortedListNode<T>* tmp= new SortedListNode<T>(nw,NULL,NULL);
            currOther=currOther->next;
            if(head==NULL){
                head=tmp;
                back=tmp;
            }
            else{
                tmp->prev=back;
                back->next=tmp;
                back=tmp;
            }
            
        }
    }
    // TODO: Implement
}

template<class T>
SortedList<T>& SortedList<T>::operator=(const SortedList& other)
{
    if(this==&other)return *this;
    
    if(head){
        SortedListNode<T>* tmp;
        while(head!=NULL){
            tmp=head;
            head=head->next;
            delete tmp->item;
            delete tmp;
        }
        
    }
    if(other.head==NULL){
        return *this;
    }
    else{
        SortedListNode<T>* currOther=other.head;
        while(currOther!=NULL){
            T* nw = new T(*currOther->item);
            SortedListNode<T>* tmp=new SortedListNode<T>(nw,NULL,NULL);
            currOther=currOther->next;
            if(head==NULL){
                head = tmp;
                back = tmp;
            }
            else{
                tmp->prev=back;
                back->next=tmp;
                back=tmp;
            }
            
        }
    }
    // TODO: Implement
    return *this;
}

template<class T>
SortedList<T>::~SortedList()
{
    
    if(head!=NULL){
        SortedListNode<T>* tmp;
        while(head!=NULL){
            tmp=head;
            head=head->next;
            delete tmp->item;
            delete tmp;
        }
    }
    // TODO: Implement
}

template<class T>
void SortedList<T>::InsertItem(T* i)
{
    SortedListNode<T>* nw = new SortedListNode<T>(i, NULL, NULL);
    if (head==NULL) {
        head = nw;
        back= nw;
    } else {
        if (*i < *head->item ) {
            nw->next = head;
            head->prev = nw;
            head = nw;
        } else if (*back->item < *i || *back->item == *i) {
            nw->prev = back;
            back->next = nw;
            back = nw;
        } else {
            SortedListNode<T>* ptr = head;
            while (ptr->next && (*(ptr->next->item) < *i || *(ptr->next->item) == *i)) {
                ptr = ptr->next;
            }
            nw->next = ptr->next;
            nw->prev = ptr;
            if (ptr->next) {
                ptr->next->prev = nw;
            }
            ptr->next = nw;
        }
    }
    // TODO: Implement
}

template<class T>
void SortedList<T>::InsertItemPrior(T* i)
{
    SortedListNode<T>* nw = new SortedListNode<T>(i,NULL,NULL);
    if(head==NULL){
        head=back=nw;
    }
    else{
        if((*i) < *(head->item) || (*i) == *(head->item)){
            nw->next=head;
            head->prev=nw;
            head=nw;
        }
        else if( *(back->item) < *i ){
            back->next=nw;
            nw->prev=back;
            back=nw;
        }
        else{
            SortedListNode<T>* curr = head;
            while(curr->next && *(curr->next->item)<*(i)){
                curr=curr->next;
            }
            nw->prev=curr;
            nw->next=curr->next;
            curr->next->prev=nw;
            curr->next=nw;
        }
        
    }
    // TODO: Implement
}

template<class T>
T* SortedList<T>::RemoveFirstItem()
{
    if(head==NULL){
        return NULL;
    }
    else{
        
        if(head==back){
            T* i=head->item;
            SortedListNode<T>* tmp =head;
            head=NULL;
            back=NULL;
            delete tmp;
            return i;
            
        }
        else{
             SortedListNode<T>* tmp =head;
             T* i=head->item;
             head=head->next;
             head->prev=NULL;
             delete tmp;
             return i;
             
        }
    }
    // TODO: Implement
    
}

template<class T>
T* SortedList<T>::RemoveFirstItem(int priority)
{
    if(head==NULL){
        return NULL;
    }
    else{
        SortedListNode<T>* curr =head;
        T* i=head->item;
        if(*(head->item)==priority){
            if(head==back){
                head=NULL;
                back=NULL;
                delete curr;
                return i;
            }
            else{
                head=head->next;
                head->prev=NULL;
                delete curr;
                return i;
            }
            
        }
            while(curr->next){
                if(*(curr->next->item)==priority){
                    SortedListNode<T>* tmp =curr->next;
                    T* i=curr->next->item;
                    curr->next=curr->next->next;
                    if (curr->next != NULL) {
                        curr->next->prev = curr;
                    }else{
                        back=curr;
                    }    
                    delete tmp;
                    return i;
                }
                curr=curr->next;
            }
        
    }
    
    
    return NULL;
}

template<class T>
T* SortedList<T>::RemoveLastItem(int priority)
{
    if(head==NULL){
        return NULL;
    }
    
    if(*(back->item)==priority){
        SortedListNode<T>* tmp;
        T* i=back->item;
        if(head==back){
            tmp=back;
            back=NULL;
            head=NULL;
            delete tmp;
            return i;
        }
        else{
            tmp=back;
            back=back->prev;
            back->next=NULL;
            delete tmp;
            return i;
        }
    }
    else{
        SortedListNode<T>* curr=back;
        while(curr){
            if(*(curr->item)==priority){
                T* i = curr->item;
                if(curr==head){
                    head=head->next;
                    if(head){
                        head->prev=NULL;
                    }
                    else{
                        back=NULL;
                    }
                   
                }
                else{
                    curr->prev->next=curr->next;
                    if(curr->next){
                        curr->next->prev = curr->prev;
                    }
                    else{
                        back = curr->prev;
                    }
                }
                delete curr;
                return i;
            }
            curr=curr->prev;
        }
        
    
    return NULL;
    }
}

template<class T>
const T* SortedList<T>::FirstItem() const
{
    return (head) ? head->item : NULL;
}

template<class T>
const T* SortedList<T>::LastItem() const
{
    return (back) ? back->item : NULL;
}

template<class T>
bool SortedList<T>::IsEmpty() const
{
    return head == NULL;
}

template<class T>
void SortedList<T>::ChangePriorityOf(int priority, int newPriority)
{
   SortedListNode<T>* curr=head;
   SortedListNode<T>* tmp=head;
   while(curr){
       if(*(curr->item)==priority){
           curr->item->setPriority(newPriority);
       }
       curr=curr->next;
   }
   curr=head;
   while(curr->next){
       if(curr->next->item->getPriority() < curr->item->getPriority() ){
           tmp=curr;
           curr=curr->next;
           T* r=RemoveFirstItem(tmp->item->getPriority());
           InsertItemPrior(r);
           continue;
       }
       curr=curr->next;
   }
    // TODO: Implement
}

    

template<class T>
void SortedList<T>::Split(SortedList& listLeft,
                          SortedList& listRight,
                          int priority)
{
    while(head){
        SortedListNode<T>* curr=head;
        head=head->next;
        if(head){
            head->prev=NULL;
        }
        curr->next=NULL;
        curr->prev=NULL;    
        if (*(curr->item) < priority) {
            if (listLeft.head) {
                listLeft.back->next = curr;
                curr->prev = listLeft.back;
                listLeft.back = curr;
            } 
            else {
                listLeft.head =curr;
                listLeft.back = curr;
            }
            
        } 
        else {
            if (listRight.head) {
                listRight.back->next = curr;
                curr->prev = listRight.back;
                listRight.back = curr;
            } else {
                listRight.head =curr;
                listRight.back = curr;
            }
        }

        
    }
    head=NULL;
    back=NULL;
    
    
    // TODO: Implement
}
template<class T>
SortedList<T> SortedList<T>::Merge(const SortedList& list0,
                                   const SortedList& list1)
{
    SortedList<T> merged;
    
    SortedListNode<T>* curr1=list0.head;
    SortedListNode<T>* curr2=list1.head;
    while(curr1 || curr2){
        if(curr1 && curr2){
            if(*(curr1->item) < *(curr2->item)){
                T* newItem = new T(*(curr1->item));
                merged.InsertItem(newItem);
                curr1=curr1->next;
                }
                else if(*(curr1->item) == *(curr2->item)){
                    T* newItem = new T(*(curr1->item));
                    merged.InsertItem(newItem);
                    curr1=curr1->next;
                }
                else{
                    T* newItem = new T(*(curr2->item));
                    merged.InsertItem(newItem);
                    curr2=curr2->next;
                }
                
            }
            else if(curr1){
                T* newItem = new T(*(curr1->item));
                merged.InsertItem(newItem);
                curr1=curr1->next;
            }
            else{
                T* newItem = new T(*(curr2->item));
                merged.InsertItem(newItem);
                curr2=curr2->next;
            }
        }
    
   // TODO: Implement
   return merged;
}

#endif