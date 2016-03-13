#pragma once
#include "Population.h"
#include <algorithm>
#include <random>

using namespace std;

class Select_In_Population
{
	Select_In_Population() { };
	
	template<typename ValueType>
	static bool cmp(Genotype<ValueType> g1, Genotype<ValueType> g2);

	//отбор усечением
	template<typename ValueType>
	static void sp_truncation(Population<ValueType>&);

	//элитарный отбор
	template<typename ValueType>
	static void sp_elite(Population<ValueType>&);
	
	//отбор вытеснением
	template<typename ValueType>
	static void sp_exclusion(Population<ValueType>&);

	//метод Больцмана
	template <typename ValueType>
	static void sp_bolzman(Population<ValueType>&);

public:
	template<typename ValueType>
	static function<void(Population<ValueType>&)> truncation()
	{
		return [](Population<ValueType>& p) { sp_truncation(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> elite()
	{
		return [](Population<ValueType>& p) { sp_elite(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> exclusion()
	{
		return [](Population<ValueType>& p) { sp_exclusion(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> bolzman()
	{
		return [](Population<ValueType>& p) { sp_bolzman(p); };
	}
};

template <typename ValueType>
inline bool Select_In_Population::cmp(Genotype<ValueType> g1, Genotype<ValueType> g2)
{
	return (g1.get_fitness() < g2.get_fitness());
}

template <typename ValueType>
void Select_In_Population::sp_truncation(Population<ValueType>& p)
{
	double limit = 0.8;
	p.parent_vector.insert(p.parent_vector.end() - 1, p.childrn_vector.begin(), p.childrn_vector.end());
	sort(p.parent_vector.begin(), p.parent_vector.end(), 
		[](Genotype<ValueType> g1, Genotype<ValueType> g2){return (g1.get_fitness() > g2.get_fitness());});
	auto t = limit * p.parent_vector.size();
	auto size = p.parent_vector.size();

	for (size_t i = t; i < size; i++)
		p.parent_vector.pop_back();

	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_population(0, t);
	p.population.clear();

	for (size_t i = 0; i < p.number_of_genotype; i++)
		p.population.push_back(p.parent_vector[uniform_population(generator)]);
}

//тут надо выбирать не только из родителей и детей, но и из остальных особей популяции
template <typename ValueType>
void Select_In_Population::sp_elite(Population<ValueType>& p)
{
	p.parent_vector->insert(p.parent_vector->end() - 1, p.childrn_vector->begin(), p.childrn_vector->end());
	sort(p.parent_vector->begin(), p.parent_vector->end(),
		[](Genotype<ValueType> g1, Genotype<ValueType> g2) {return (g1.get_fitness() > g2.get_fitness());});

	p.population.clear();
	for (size_t i = 0; i < p.number_of_genotype; i++)
	{
		p.population.push_back(p.parent_vector->at(i));
	}
}

template <typename ValueType>
void Select_In_Population::sp_exclusion(Population<ValueType>& p)
{
}

template <typename ValueType>
void Select_In_Population::sp_bolzman(Population<ValueType>& p)
{
}
