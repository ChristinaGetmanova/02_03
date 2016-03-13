	#pragma once
#include "vector"
#include "iostream"

using namespace std;

template <typename ValueType> struct Gene
{
	Gene();
	explicit Gene(int);
	//Конструктор копирования для работы с обычными ссылками lvalue
	Gene(const Gene<ValueType>& other);
	//Конструктор перемещения для move и работы с типами ссылок rvalue, часто применяется при работе с векторами
	Gene(Gene<ValueType>&& other);
	~Gene();

	vector<ValueType>get_gene();
	vector<ValueType>& get_gene_ref();

	friend bool operator== (const Gene<ValueType>& left, const Gene<ValueType>& right);

	Gene<ValueType>& operator=(const Gene<ValueType>& other);
	Gene<ValueType>& operator=(Gene<ValueType>&& other);

	//inline ValueType* operator[](int index); закомменчено для работы в 2010 студии
	inline ValueType operator[](int index) const;

private:
	vector<ValueType>* _gene;
};

template<typename ValueType>
Gene<ValueType>::Gene()
{
	_gene = new vector<ValueType>();
}

template<typename ValueType>
Gene<ValueType>::Gene(int size)
{
	_gene = new vector<ValueType>(size);
}

template <typename ValueType>
Gene<ValueType>::Gene(const Gene<ValueType>& other) : _gene(new vector<ValueType>(other._gene->size()))
{
	copy(other._gene->begin(), other._gene->end(), _gene->begin());
}

template <typename ValueType>
Gene<ValueType>::Gene(Gene<ValueType>&& other) : _gene(nullptr)
{
	_gene = other._gene;
	other._gene = nullptr;
}

template<typename ValueType>
Gene<ValueType>::~Gene()
{
	/*if (_gene == nullptr)
	cout << "can't dest" << endl;*/
	delete _gene;
	/*cout << "Destructor gene" << endl;*/
}

template<typename ValueType>
vector<ValueType> Gene<ValueType>::get_gene()
{
	return *_gene;
}

template<typename ValueType>
vector<ValueType>& Gene<ValueType>::get_gene_ref()
{
	return *_gene;
}

template<typename ValueType>
bool operator==(const Gene<ValueType>& left, const Gene<ValueType>& right);

template <typename ValueType>
bool operator==(const Gene<ValueType>& left, const Gene<ValueType>& right)
{
	return equal(left.get_gene()->begin(), left.get_gene()->end(), right.get_gene()->begin());

	/*auto size = left.get_size();
	for (int i = 0; i < left.get_size(); i++)
	{
	if (left[i] != right[i])
	return false;
	}*/
}

template <typename ValueType>
Gene<ValueType>& Gene<ValueType>::operator=(const Gene<ValueType>& other)
{
	if (this != &other)
	{
		delete _gene;
		this->_gene = new vector<ValueType>(other._gene->size());
		copy(other._gene->begin(), other._gene->end(), this->_gene->begin());
	}
	return *this;
}

template <typename ValueType>
Gene<ValueType>& Gene<ValueType>::operator=(Gene<ValueType>&& other)
{
	if (this != &other)
	{
		delete _gene;
		*this = move(other);
	}
	return *this;
}

//template<typename ValueType>
//inline ValueType* Gene<ValueType>::operator[](int index)
//{
//	ValueType* p = _gene->data() + index - 1;
//	return p;
//}

template <typename ValueType>
inline ValueType Gene<ValueType>::operator[](int index) const
{
	return _gene[index];
}

