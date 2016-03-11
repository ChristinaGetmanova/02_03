#pragma once
#include "vector"
#include "Gene.h"

template<typename ValueType> class Genotype
{
protected:
	int _number_of_genes;
	vector<Gene<ValueType>> genotype;
	double _fitness;

	Genotype(int number, double fitness)
	{
		_number_of_genes = number;
		_fitness = fitness;
	}

public:
	Genotype() : _number_of_genes(0), _fitness(0) {}
	explicit Genotype(int number) : _number_of_genes(number), _fitness(0) {}

	virtual ~Genotype() { };
	virtual double get_fitness()
	{
		if (_fitness == 0)
			_fitness = count_fitness();
		return _fitness;
	}

	virtual double count_fitness() { return 0.0; };
	vector<Gene<ValueType>>* get_genotype();
	int get_number_of_genes() const;
};

template<typename ValueType>
vector<Gene<ValueType>>* Genotype<ValueType>::get_genotype()
{
	return &genotype;
}

template<typename ValueType>
int Genotype<ValueType>::get_number_of_genes() const
{
	return _number_of_genes;
}
