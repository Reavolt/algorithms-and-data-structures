#ifndef _QUEUE_H_
#define _QUEUE_H_
//-------------------------------------------------------------------------------------------------
template <typename Type>
class Queue
{
private:
	struct Node
	{
		Type element = {};
		Node* prev = nullptr;
		Node* next = nullptr;
	};
	size_t count;
	Node* head;
	Node* tail;
public:
	//Member functions
	Queue();
	Queue(const Queue & que);
	Queue(Queue && que);
	Queue & operator = (const Queue & que);
	Queue & operator = (Queue && que);
	~Queue();

	//Element access
	const Type & front() const;
	const Type & back() const;

	//Capacity
	bool empty() const;
	size_t size() const;

	//Modifiers
	void push(const Type & tp);
	void pop();
	void swap(Queue & que) noexcept;
	//emplace Not implemented
};
//-------------------------------------------------------------------------------------------------
template <typename Type>
Queue<Type>::Queue() : count(0), head(nullptr), tail(nullptr)
{
	//Body of the constructor class
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Queue<Type>::Queue(const Queue & que) : count(que.count), head(nullptr), tail(nullptr)
{
	for (const Node* n_ptr = que.head; n_ptr != nullptr; n_ptr = n_ptr->next)
	{
		Node* n_ptr_new = new Node;
		n_ptr_new->element = n_ptr->element;
		if (head == nullptr && tail == nullptr)
		{
			head = n_ptr_new;
			tail = head;
		}
		else
		{
			tail->next = n_ptr_new;
			n_ptr_new->prev = tail;
			n_ptr_new->next = nullptr;
			tail = n_ptr_new;
		}
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Queue<Type>::Queue(Queue && que) : count(que.count), head(que.head), tail(que.tail)
{
	que.count = 0;
	que.head = nullptr;
	que.tail = nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Queue<Type> & Queue<Type>::operator = (const Queue & que)
{
	if (this == &que)
	{
		return *this;
	}
	
	Queue tmp(que);
	std::swap(count, tmp.count);
	std::swap(head, tmp.head);
	std::swap(tail, tmp.tail);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Queue<Type> & Queue<Type>::operator = (Queue && que)
{
	if (this == &que)
	{
		return *this;
	}

	std::swap(count, que.count);
	std::swap(head, que.head);
	std::swap(tail, que.tail);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Queue<Type>::~Queue()
{
	while (head)
	{
		Node* n_ptr_del = head;
		head = head->next;
		delete n_ptr_del;
	}
	count = 0;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Queue<Type>::push(const Type & tp)
{
	Node* n_ptr_new = new Node;
	n_ptr_new->element = tp;
	if (head == nullptr && tail == nullptr)
	{
		head = n_ptr_new;
		tail = head;
	}
	else
	{
		tail->next = n_ptr_new;
		n_ptr_new->prev = tail;
		n_ptr_new->next = nullptr;
		tail = n_ptr_new;
	}
	++count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Queue<Type>::pop()
{
	if (empty())
	{
		throw std::out_of_range("Can't pop from empty list");
	}

	if (head == tail)
	{
		delete head;
		--count;
		head = nullptr;
		tail = nullptr;
		return;
	}

	Node* n_ptr_del = head;
	head = head->next;
	head->prev = nullptr;
	--count;
	delete n_ptr_del;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
bool Queue<Type>::empty() const
{
	return head == nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const Type & Queue<Type>::front() const
{
	if (empty())
	{
		throw std::out_of_range("List<Type>::top: empty stack");
	}
	return head->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const Type & Queue<Type>::back() const
{
	if (empty())
	{
		throw std::out_of_range("List<Type>::top: empty stack");
	}
	return tail->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
size_t Queue<Type>::size() const
{
	return count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Queue<Type>::swap(Queue & que) noexcept
{
	Queue temp(que);
	que = std::move(*this);
	*this = std::move(temp);
}
//-------------------------------------------------------------------------------------------------
#endif // _QUEUE_H_