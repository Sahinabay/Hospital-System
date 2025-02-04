#ifndef FCFS_LIST_IMPL_H
#define FCFS_LIST_IMPL_H

template<class T>
FCFSNode<T>:: FCFSNode(const T& t, FCFSNode* node)
    : item(t)
    , next(node)
{}

// ============================ //
template<class T>
FCFSList<T>::FCFSList()
    : head(NULL)
{
    
    head = new FCFSNode<T>(T());
}


template<class T>
FCFSList<T>::FCFSList(const FCFSList& other)
{
    if(other.head==NULL){
        head=NULL;
        return ;
    }
    head=new FCFSNode<T>(other.head->item);
    FCFSNode<T>* currOther=other.head->next;
    FCFSNode<T>* currThis=head;
    while(currOther){
        currThis->next= new FCFSNode<T>(currOther->item);
        currThis=currThis->next;
        currOther=currOther->next;
    }
    
    
    
}

template<class T>
FCFSList<T>& FCFSList<T>::operator=(const FCFSList& other)
{
    if(this==&other)return *this;
    if(head){
        FCFSNode<T>* currThis=head;
        FCFSNode<T>* tmp;
        while(currThis){
        tmp=currThis;
        currThis=currThis->next;
        delete tmp;
        }
        head=NULL;
    }
    if(other.head==NULL){
        head=NULL;
    }
    else{
    head= new FCFSNode<T>(T());
    FCFSNode<T>* currThis=head;
    FCFSNode<T>* currOther=other.head->next;
    while(currOther){
        currThis->next=new FCFSNode<T>(currOther->item);
        currThis=currThis->next;
        currOther=currOther->next;
    }
    }
    
    return *this;
}

template<class T>
FCFSList<T>::~FCFSList()
{
    FCFSNode<T>* currThis=head;
    while(currThis){
        FCFSNode<T>* tmp;
        tmp=currThis;
        currThis=currThis->next;
        delete tmp;
    }
    
}

template<class T>
void FCFSList<T>::Enqueue(const T& item)
{
    FCFSNode<T>* currThis=head;
    while(currThis->next){
        currThis=currThis->next;
    }
    currThis->next= new FCFSNode<T>(item,NULL);
}

template<class T>
bool FCFSList<T>::IsEmpty() const {
    return head->next == NULL;
}

template<class T>
T FCFSList<T>::Dequeue()
{
    if(head->next==NULL){
        return T();
    }
    if(head->next!=NULL){
        FCFSNode<T>* currThis=head->next;
        T res=currThis->item;
        head->next=currThis->next;
        delete currThis;
        return res;
    }
   
}



#endif