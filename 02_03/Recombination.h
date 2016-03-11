#pragma once
#include "Population.h"
#include <random>
#include <vector>

using namespace std;

class Recombination
{
	Recombination();

	// Операторы рекомбинации (воспроизведения) - дискретная и кроссинговер --------------------------------------------

	template<typename ValueType>
	static void r_discrete(Population<ValueType>&);

	//промежуточная рекомбинация
	template<typename ValueType>
	static void r_intermediate(Population<ValueType>&);

	//линейная рекомбинация
	template<typename ValueType>
	static void r_line(Population<ValueType>&);

	// Методы кроссинговера --------------------------------------------------------------------------------------------

	//одноточечный кроссинговер
	template<typename ValueType>
	static void r_singlepoint(Population<ValueType>&);

	//двухточечный кроссинговер
	template<typename ValueType>
	static void r_doublepoint(Population<ValueType>&);

	//многоточечный кроссинговер
	template<typename ValueType>
	static void r_multipoint(Population<ValueType>&);

	//триадный кроссинговер
	template<typename ValueType>
	static void r_triadic(Population<ValueType>&);

	//однородный кроссинговер
	template<typename ValueType>
	static void r_uniform(Population<ValueType>&);

	//перетасовочный кроссинговер
	template<typename ValueType>
	static void r_shuffler(Population<ValueType>&);

	//кроссинговер с уменьшением замены
	template<typename ValueType>
	static void r_crossover_with_reduced_surrogate(Population<ValueType>&);

public:

	template<typename ValueType>
	static function<void(Population<ValueType>&)> discrete()
	{
		return [](Population<ValueType>& p) { r_discrete(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> intermediate()
	{
		return [](Population<ValueType>& p) { r_intermediate(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> line()
	{
		return [](Population<ValueType>& p) { r_line(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> singlepoint()
	{
		return [](Population<ValueType>& p) { r_singlepoint(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> doublepoint()
	{
		return [](Population<ValueType>& p) { r_doublepoint(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> multipoint()
	{
		return [](Population<ValueType>& p) { r_multipoint(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> triadic()
	{
		return [](Population<ValueType>& p) { r_triadic(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> uniform()
	{
		return [](Population<ValueType>& p) { r_uniform(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> shuffler()
	{
		return [](Population<ValueType>& p) { r_shuffler(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> crossover_with_reduced_surrogate()	
	{
		return [](Population<ValueType>& p) { r_crossover_with_reduced_surrogate(p); };
	}
};

template <typename ValueType>
void Recombination::r_discrete(Population<ValueType>& p)
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_int_distribution(0, 1);
	vector<Gene<ValueType>> parents[] = { *p.parent->get_genotype(), *p._parent->get_genotype() };

	for (size_t i = 0; i < p.parent->get_number_of_genes(); i++)
	{
		auto n = static_cast<bool>(uniform_int_distribution(generator));
		auto t = parents[n][i];
		p.child->get_genotype()->push_back(parents[n][i]);
		n = static_cast<bool>(uniform_int_distribution(generator));
		p._child->get_genotype()->push_back(parents[n][i]);
	}
	p.childrn_vector.push_back(*p.child);
	p.childrn_vector.push_back(*p._child);
}

template <typename ValueType>
void Recombination::r_intermediate(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_line(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_singlepoint(Population<ValueType>& p)
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_int_distribution(0, *p.parent->get_number_of_genes());
	auto point = uniform_int_distribution(generator);

	for (size_t i = 0; i < point; i++)
	{
		*p.child->get_genotype()->push_back(p.parent[i]);
		*p._child->get_genotype()->push_back(p._parent[i]);
	}

	for (size_t i = point; i < *p.parent->get_number_of_genes(); i++)
	{
		*p.child->get_genotype()->push_back(p._parent[i]);
		*p._child->get_genotype()->push_back(p.parent[i]);
	}
	p.childrn_vector.push_back(p.child);
	p.childrn_vector.push_back(p._child);
}

template <typename ValueType>
void Recombination::r_doublepoint(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_multipoint(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_triadic(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_uniform(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_shuffler(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_crossover_with_reduced_surrogate(Population<ValueType>&)
{
}
