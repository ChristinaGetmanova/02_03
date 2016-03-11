// 02_03.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Read_File.h"
#include "Genotype.h"
#include "Population.h"
#include "Selection.h"
#include "Recombination.h"
#include "Mutation.h"
#include "Select_In_Population.h"
#include <algorithm>
#include <random>

#include <fstream>
#include <functional>

using namespace std;

class Genotype2 : public Genotype<int> //���������� ������ � ���� ������ ����� ������ (��� ���������� ����������)
{
public:
	Genotype2(double** mas, int number) : Genotype(number), matrix(mas)
	{
		Distr distribution(1, _number_of_genes);
		for (size_t i = 0; i < _number_of_genes; i++)
		{
			Gene<int> g;
			g.get_gene_ref().push_back(distribution());
			genotype.push_back(move(g));
		}
		Genotype<int>::get_fitness();
	}
	//����������� �����������
	Genotype2(const Genotype2& other) : Genotype<int>(other._number_of_genes, other._fitness), matrix(nullptr)
	{
		if (this != &other)
		{
			auto lenght = other.genotype.size();
			genotype = vector<Gene<int>>(lenght);
			copy(other.genotype.begin(), other.genotype.end(), genotype.begin());

			matrix = other.matrix;
		}
	}
	//����������� ����������� ��� ��������� ��������� ������ � ��������,
	//����������������� ���� ����� ������ ������������ ���� �����������
	Genotype2(Genotype2&& other)
	{
		genotype = vector<Gene<int>>(move(other.genotype));

		_number_of_genes = other._number_of_genes;
		_fitness = other._fitness;
		matrix = other.matrix;
		other.matrix = nullptr;
	}

private:
	double** matrix;
	static const int line_in_genes = 1;
	static const int column_in_genes = 3;

	//����� ��� ��������� ������������ ������������� ��� ����������
	class Distr
	{
		random_device rd;
		mt19937 generator;
		uniform_int_distribution<> distrib;

		int a, b;
		vector<int> chisla;

	public:
		Distr(int a, int b) : a(a), b(b)
		{
			generator = mt19937(rd());
			distrib = uniform_int_distribution<>(a, b);
		}

		int operator() () {
			while (true)
			{
				auto temp = distrib(generator);
				if (!binary_search(chisla.begin(), chisla.end(), temp))
				{
					chisla.push_back(temp);
					return temp;
				}
				/*if (find(chisla.begin(), chisla.end(), temp) == chisla.end())
				{
				chisla.push_back(temp);
				return temp;
				}*/
			}
		}
	};

	bool checked(Gene<int> gene)
	{
		/*auto val = find(genotype.begin(), genotype.end(), number);
		auto v = genotype.end() - 1;*/
		if (find(genotype.begin(), genotype.end(), gene) == genotype.end())
			return true;
		return false;
	}

	double count_fitness() override
	{
		int n_l, n_c;
		double fitness = 0;
		for (auto& gen : genotype)
		{
			for (auto item : gen.get_gene_ref())
			{
				int num_of_gene = --item;
				n_l = line_in_genes * (num_of_gene / 159);
				n_c = column_in_genes * (num_of_gene % 159);

				for (size_t i = n_c; i < n_c + column_in_genes; i++)
					fitness += matrix[n_l][i];
			}
		}
		return fitness;
	}
};


int main()
{
	string file_name = "matrix.txt";
	Read_File *file = new Read_File(file_name);

	const int line = file->get_line();
	const int column = file->get_column();

	double **matrix = new double*[line];
	for (int i = 0; i < line; i++)
		matrix[i] = new double[column];

	double value;
	for (int i = 0; i < line; i++)
		for (int j = 0; j < column; j++)
		{
			*(file->get_file()) >> value;
			matrix[i][j] = value;
		}

	vector<Genotype<int>> vec;
	for (size_t i = 0; i < 100; i++)
	{
		Genotype2 g(matrix, 7807);//��� ����� Genotype2 ����� ��� ���������� ������ ������������ � �������� ������
		vec.push_back(dynamic_cast<Genotype<int>&>(g));//������������ ���������� ��� ����, ����� �������� � ����������� ������ Population2, ��� ������ ��� ������ ��� ������ � ���������
	}

	auto temp_s = Selection::inbreeding<int>();
	auto temp_r = Recombination::discrete<int>();
	auto temp_m = nullptr;
	auto temp_sp = Select_In_Population::elite<int>();

	Population<int> p(7807, vec, temp_s, temp_r, temp_m, temp_sp);

	for (size_t i = 0; i < 500; i++)
	{
		p.select();
		p.recom();
		//p.mut();
		p.select_in_population();
	}

	return 0;
}

