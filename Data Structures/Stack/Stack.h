#ifndef _STACK_H_
#define _STACK_H_
//-------------------------------------------------------------------------------------------------
template <typename Type>
class Stack
{
private:
	struct Node
	{
		Type element = {};
		Node* next = nullptr;
	};
	size_t count;
	Node* tail;
public:
	//Member functions
	Stack();
	Stack(const Stack & stk);
	Stack(Stack && stk);
	Stack & operator = (const Stack & stk);
	Stack & operator = (Stack && stk);
	~Stack();
	
	//Element access
	const Type & top() const;

	//Capacity
	bool empty() const;
	size_t size() const;

	//Modifiers
	void push(const Type & val);
	void push(Type && val);
	void swap(Stack & stk);
	//emplace Not implemented
	void pop();
};
//-------------------------------------------------------------------------------------------------
template <typename Type>
Stack<Type>::Stack() : count(0), tail(nullptr)
{
	//Body of the constructor class
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Stack<Type>::Stack(const Stack & stk) : count(stk.count), tail(nullptr)
{
	Node **n_ptr_next = &tail;
	for (const Node* n_ptr = stk.tail; n_ptr != nullptr; n_ptr = n_ptr->next)
	{
		Node* n_ptr_new = new Node(*n_ptr);
		*n_ptr_next = n_ptr_new;
		n_ptr_next = &n_ptr_new->next;
	}
	*n_ptr_next = nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Stack<Type>::Stack(Stack && stk) : count(stk.count), tail(stk.tail)
{
	stk.count = 0;
	stk.tail = nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Stack<Type> & Stack<Type>::operator = (const Stack & stk)
{
	if (this == &stk)
	{
		return *this;
	}

	Stack temp(stk);
	std::swap(tail, temp.tail);
	std::swap(count, temp.count);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Stack<Type> & Stack<Type>::operator = (Stack && stk)
{
	if (this == &stk)
	{
		return *this;
	}

	std::swap(tail, stk.tail);
	std::swap(count, stk.count);
	return *this;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
Stack<Type>::~Stack()
{
	while (tail)
	{
		Node* n_ptr_del = tail;
		tail = tail->next;
		delete n_ptr_del;
	}
	count = 0;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Stack<Type>::push(Type && val)
{
	Node* n_ptr_new = new Node;
	n_ptr_new->element = val;
	count++;
	n_ptr_new->next = tail;
	tail = n_ptr_new;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Stack<Type>::push(const Type & val)
{
	Node* n_ptr_new = new Node;
	n_ptr_new->element = val;
	count++;
	n_ptr_new->next = tail;
	tail = n_ptr_new;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Stack<Type>::pop()
{
	Node* n_ptr_del = tail;
	tail = tail->next;
	count--;
	delete n_ptr_del;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
const Type & Stack<Type>::top() const
{
	if (empty())
	{
		throw std::runtime_error("Stack<Type>::top: empty stack");
	}
	return tail->element;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
size_t Stack<Type>::size() const
{
	return count;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
bool Stack<Type>::empty() const
{
	return tail == nullptr;
}
//-------------------------------------------------------------------------------------------------
template <typename Type>
void Stack<Type>::swap(Stack & stk)
{
	Stack temp(stk);
	stk = std::move(*this);
	*this = std::move(temp);
}
//-------------------------------------------------------------------------------------------------
#endif // STACK_H_