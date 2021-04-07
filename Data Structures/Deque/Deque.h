#ifndef _DEQUE_H_
#define _DEQUE_H_
//-------------------------------------------------------------------------------------------------
template <typename Type>
class Deque
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
	Deque();
	Deque(const Deque & deq);
	Deque(Deque && deq);
	Deque & operator = (const Deque & deq);
	Deque & operator = (Deque && deq);
	~Deque();

	//Element access
	//const Type & at(Deque pos) const; Not implemented
	//template <typename Type>
	//const Type & operator[](size_type pos) const; Not implemented
	const Type & front() const;
	const Type & back() const;

	//Iterators
	//TODO: Implement in the near future 

	//Capacity
	bool empty() const;
	size_t size() const;
	//size_t max_size() const noexcept; Not implemented

	//Modifiers
	void push_front(const Type & tp);
	void push_back(const Type & tp);

	//void emplace_front(); Not implemented
	//void emplace_back(); Not implemented

	void pop_front();
	void pop_back();

	void clear() noexcept;
	void swap(Deque & deq) noexcept;
};
//-------------------------------------------------------------------------------------------------
template <typename Type>
Deque<Type>::Deque() : count(0), head(nullptr), tail(nullptr)
{
	//Body of the constructor class
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Deque<Type>::Deque(const Deque & deq) : count(deq.count), head(nullptr), tail(nullptr)
{
	for (const Node* n_ptr = deq.head; n_ptr != nullptr; n_ptr = n_ptr->next)
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
Deque<Type>::Deque(Deque && deq) : count(deq.count), head(deq.head), tail(deq.tail)
{
	deq.count = 0;
	deq.head = nullptr;
	deq.tail = nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Deque<Type> & Deque<Type>::operator = (const Deque & deq)
{
	if (this == &deq)
	{
		return *this;
	}
	
	Deque tmp(deq);
	std::swap(count, tmp.count);
	std::swap(head, tmp.head);
	std::swap(tail, tmp.tail);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Deque<Type> & Deque<Type>::operator = (Deque && deq)
{
	if (this == &deq)
	{
		return *this;
	}

	std::swap(count, deq.count);
	std::swap(head, deq.head);
	std::swap(tail, deq.tail);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Deque<Type>::~Deque()
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
void Deque<Type>::push_front(const Type & tp)
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
		n_ptr_new->next = head;
		n_ptr_new->prev = nullptr;
		head->prev = n_ptr_new;
		head = n_ptr_new;
	}
	++count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Deque<Type>::push_back(const Type & tp)
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
void Deque<Type>::pop_front()
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
void Deque<Type>::pop_back()
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

	Node* n_ptr_del = tail;
	tail = tail->prev;
	tail->next = nullptr;
	--count;
	delete n_ptr_del;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
bool Deque<Type>::empty() const
{
	return head == nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const Type & Deque<Type>::front() const
{
	if (empty())
	{
		throw std::out_of_range("List<Type>::top: empty stack");
	}
	return head->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const Type & Deque<Type>::back() const
{
	if (empty())
	{
		throw std::out_of_range("List<Type>::top: empty stack");
	}
	return tail->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
size_t Deque<Type>::size() const
{
	return count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Deque<Type>::clear() noexcept
{
	while (count)
	{
		pop_back();
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Deque<Type>::swap(Deque & deq) noexcept
{
	Deque temp(deq);
	deq = std::move(*this);
	*this = std::move(temp);
}
//-------------------------------------------------------------------------------------------------
#endif // _DEQUE_H_