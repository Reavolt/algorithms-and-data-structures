#ifndef _List_H_
#define _List_H_
//-------------------------------------------------------------------------------------------------
template <typename Type>
class List
{
private:
	struct Node
	{
		Type element = {};
		Node* next = nullptr;
	};
	size_t count;
	Node* head;
	Node* tail;
public:
	//Member functions
	List();
	List(const List & lst);
	List(List && lst);
	List & operator = (const List & lst);
	List & operator = (List && lst);
	~List();

	//Element access
	const Type & front() const;
	const Type & back() const;

	//Iterators
	//TODO: Implement in the near future

	//Capacity
	bool empty() const;
	size_t size() const;
	//size_type max_size() const noexcept; Not implemented

	//Modifiers
	void push_front(const Type & tp);
	void push_back(const Type & tp);
	void push_pos(const Type & tp, const size_t & pos);

	void pop_front();
	void pop_back();
	void pop_pos(const size_t & pos);

	//emplace_front Not implemented
	//emplace_back Not implemented
	//emplace Not implemented

	void clear() noexcept;
	//erase Not implemented
	void swap(List & lst) noexcept;
};
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::List() : count(0), head(nullptr), tail(nullptr)
{
	//Body of the constructor class
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::List(const List & lst) : count(lst.count), head(nullptr), tail(nullptr)
{
	for (const Node* n_ptr = lst.head; n_ptr != nullptr; n_ptr = n_ptr->next)
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
			tail = n_ptr_new;
		}
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::List(List && lst) : count(lst.count), head(lst.head), tail(lst.tail)
{
	lst.count = 0;
	lst.head = nullptr;
	lst.tail = nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type> & List<Type>::operator = (const List & lst)
{
	if (this == &lst)
	{
		return *this;
	}

	List tmp(lst);
	std::swap(count, tmp.count);
	std::swap(head, tmp.head);
	std::swap(tail, tmp.tail);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type> & List<Type>::operator = (List && lst)
{
	if (this == &lst)
	{
		return *this;
	}

	std::swap(count, lst.count);
	std::swap(head, lst.head);
	std::swap(tail, lst.tail);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::~List()
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
void List<Type>::push_front(const Type & tp)
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
		head = n_ptr_new;
	}
	++count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::push_back(const Type & tp)
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
		tail = n_ptr_new;
	}
	++count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::push_pos(const Type & tp, const size_t & pos)
{
	if (empty() || pos == 0)
	{
		push_front(tp);
		return;
	}

	if (pos == count)
	{
		push_back(tp);
		return;
	}

	if (pos < count && pos > 0)
	{
		Node* n_ptr_new = new Node;
		Node* n_ptr_prev = nullptr;
		Node* n_ptr_cur = head;
		n_ptr_new->element = tp;

		for (size_t i = 0; i < pos; ++i)
		{
			n_ptr_prev = n_ptr_cur;
			n_ptr_cur = n_ptr_cur->next;
		}
		n_ptr_prev->next = n_ptr_new;
		n_ptr_new->next = n_ptr_cur;
		++count;
	}
	else
	{
		throw std::out_of_range("Invalid position");
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::pop_front()
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
	--count;
	delete n_ptr_del;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::pop_back()
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

	Node* n_ptr_lst = head;
	while (n_ptr_lst->next != tail)
	{
		n_ptr_lst = n_ptr_lst->next;
	}
	--count;
	delete tail;

	tail = n_ptr_lst;
	tail->next = nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::pop_pos(const size_t & pos)
{
	if (empty())
	{
		throw std::out_of_range("Can't pop from empty list");
	}

	if (pos == 0)
	{
		pop_front();
		return;
	}
	else
	if (pos == count - 1)
	{
		pop_back();
		return;
	}

	if (pos < count && pos > 0)
	{
		Node* n_ptr_prev = nullptr;
		Node* n_ptr_pos = head;

		for (size_t i = 0; i < pos; ++i)
		{
			n_ptr_prev = n_ptr_pos;
			n_ptr_pos = n_ptr_pos->next;
		}
		n_ptr_prev->next = n_ptr_pos->next;
		--count;
		delete n_ptr_pos;
	}
	else
	{
		throw std::out_of_range("Invalid position");
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
bool List<Type>::empty() const
{
	return head == nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
size_t List<Type>::size() const
{
	return count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const Type & List<Type>::front() const
{
	if (empty())
	{
		throw std::out_of_range("List<Type>::front empty stack");
	}
	return head->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const Type & List<Type>::back() const
{
	if (empty())
	{
		throw std::out_of_range("List<Type>::back empty stack");
	}
	return tail->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::clear() noexcept
{
	while (count)
	{
		pop_back();
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void List<Type>::swap(List & lst) noexcept
{
	List temp(lst);
	lst = std::move(*this);
	*this = std::move(temp);
}
//-------------------------------------------------------------------------------------------------
#endif // _List_H_
