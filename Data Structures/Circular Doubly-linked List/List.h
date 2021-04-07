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
		Node* prev = nullptr;
		Node* next = nullptr;
	};
	size_t count;
	Node* head;
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
List<Type>::List() : count(0), head(nullptr)
{
	//Body of the constructor class
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::List(const List & lst) : count(lst.count), head(nullptr)
{
	for (size_t i = 0; i < lst.count; ++i)
	{
		Node* n_ptr_rvl = lst.head;
		Node* n_ptr_new = new Node;
		n_ptr_new->element = n_ptr_rvl->element;
		if (head == nullptr)
		{
			head = n_ptr_new;
			head->prev = head;
			head->next = head;
		}
		else
		{
			Node* n_ptr_lst = head;
			while (n_ptr_lst->next != head)
			{
				n_ptr_lst = n_ptr_lst->next;
			}
			n_ptr_lst->next = n_ptr_new;
			n_ptr_new->prev = n_ptr_lst;
			n_ptr_new->next = head;
			head->prev = n_ptr_new;
		}
		n_ptr_rvl = n_ptr_rvl->next;
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
List<Type>::List(List && lst) : count(lst.count), head(lst.head)
{
	lst.count = 0;
	lst.head = nullptr;
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
	if (head == nullptr)
	{
		head = n_ptr_new;
		head->prev = head;
		head->next = head;
	}
	else
	{
		Node* n_ptr_lst = head;
		while (n_ptr_lst->next != head)
		{
			n_ptr_lst = n_ptr_lst->next;
		}
		n_ptr_new->next = head;
		head->prev = n_ptr_new;
		n_ptr_new->prev = n_ptr_lst;
		n_ptr_lst->next = n_ptr_new;
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
	if (head == nullptr)
	{
		head = n_ptr_new;
		head->prev = head;
		head->next = head;
	}
	else
	{
		Node* n_ptr_lst = head;
		while (n_ptr_lst->next != head)
		{
			n_ptr_lst = n_ptr_lst->next;
		}
		n_ptr_lst->next = n_ptr_new;
		n_ptr_new->prev = n_ptr_lst;
		n_ptr_new->next = head;
		head->prev = n_ptr_new;
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
		Node* n_ptr_lst = head;
		n_ptr_new->element = tp;
	
		for (size_t i = 0; i < pos; ++i)
		{
			n_ptr_prev = n_ptr_lst;
			n_ptr_lst = n_ptr_lst->next;
		}
		n_ptr_prev->next = n_ptr_new;
		n_ptr_new->prev = n_ptr_prev;
		n_ptr_new->next = n_ptr_lst;
		n_ptr_lst->prev = n_ptr_new;
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
	
	if (head->next == head)
	{
		delete head;
		--count;
		head = nullptr;
		return;
	}

	Node* n_ptr_lst = head;
	while (n_ptr_lst->next != head)
	{
		n_ptr_lst = n_ptr_lst->next;
	}
	n_ptr_lst->next = head->next;

	Node* n_ptr_del = head;
	head = head->next;
	head->prev = n_ptr_lst;
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

	if (head->next == head)
	{
		delete head;
		--count;
		head = nullptr;
		return;
	}

	Node* n_ptr_prev = nullptr;
	Node* n_ptr_lst = head;
	while (n_ptr_lst->next != head)
	{
		n_ptr_prev = n_ptr_lst;
		n_ptr_lst = n_ptr_lst->next;
	}
	n_ptr_prev->next = head;
	head->prev = n_ptr_prev;
	--count;
	delete n_ptr_lst;
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
		n_ptr_pos->prev = n_ptr_prev;
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
const Type & List<Type>::front() const
{
	if (empty())
	{
		throw std::out_of_range("List<Type>::top: empty stack");
	}
	return head->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const Type & List<Type>::back() const
{
	if (empty())
	{
		throw std::out_of_range("List<Type>::top: empty stack");
	}

	Node* n_ptr_lst = head;
	while (n_ptr_lst->next != head)
	{
		n_ptr_lst = n_ptr_lst->next;
	}
	return n_ptr_lst->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
size_t List<Type>::size() const
{
	return count;
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