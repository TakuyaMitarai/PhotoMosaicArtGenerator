#include "PartialPopulation.h"

// コンストラクタ
PartialPopulation::PartialPopulation()
{
	int i;

	for(i = 0; i < PPOP_SIZE; i++)
		pop[i] = new PartialIndividual();
}

// デストラクタ
PartialPopulation::~PartialPopulation()
{
	int i;

	for(i = 0; i < PPOP_SIZE; i++)
		delete pop[i];
}

// 次世代生成
void PartialPopulation::newGeneration()
{
	int i, j, a, index1, index2;

	/*
	for(i = PPOP_SIZE / 4 * 3, j = 0; i < PPOP_SIZE; i += 2, j++) {
		a = ((rand() % (PPOP_SIZE / 4 - 1)) + j) % (PPOP_SIZE / 4);
		index1 = rand() % PCHROM_LEN;
		index2 = ((rand() % (PCHROM_LEN - 1)) + index1) % PCHROM_LEN;
		pop[i]->newGeneration(pop[j], pop[a], index1, index2);
		pop[i+1]->newGeneration(pop[a], pop[j], index1, index2);
	}
	for(i = 0; i < PPOP_SIZE / 4 * 3; i++)
		pop[i]->newGeneration();
	*/
	/*
	for(i = PPOP_SIZE / 8 * 1, j = 0; i < PPOP_SIZE; i += 2, j++) {
		a = ((rand() % (PPOP_SIZE / 8 - 7)) + j) % (PPOP_SIZE / 8);
		index1 = rand() % PCHROM_LEN;
		index2 = ((rand() % (PCHROM_LEN - 1)) + index1) % PCHROM_LEN;
		pop[i]->newGeneration(pop[j], pop[a], index1, index2);
		pop[i+1]->newGeneration(pop[a], pop[j], index1, index2);
	}
	for(i = 0; i < PPOP_SIZE / 8 * 7; i++)
		pop[i]->newGeneration();
	*/

	for(i = PPOP_SIZE / 20 * 1, j = 0; i < PPOP_SIZE; i += 2, j++) {
		a = ((rand() % (PPOP_SIZE / 20 - 19)) + j) % (PPOP_SIZE / 20);
		index1 = rand() % (PCHROM_LEN - 1);
		index2 = ((rand() % (PCHROM_LEN - 2) + 1) + index1) % (PCHROM_LEN - 1);
		pop[i]->newGeneration(pop[j], pop[a], index1, index2);
		pop[i+1]->newGeneration(pop[a], pop[j], index1, index2);
	}
	for(i = 0; i < PPOP_SIZE / 20 * 19; i++)
		pop[i]->newGeneration();
}

// 評価
void PartialPopulation::evaluation()
{
	sort(0, PPOP_SIZE - 1);
}

// 評価値初期化
void PartialPopulation::evalinit()
{
	int i;
	
	for(i = 0; i < PPOP_SIZE; i++)
		pop[i]->fitness = DBL_MAX;
}

// popをfitnessの値によって昇順にソート（クイックソート）
// lb : ソートするpopの範囲の最小インデックス
// rb : ソートするpopの範囲の最大インデックス
void PartialPopulation::sort(int lb, int ub)
{
	int i, j, k;
	double pivot;
	PartialIndividual* swap;

	if(lb < ub) {
		k = (lb + ub) / 2;
		pivot = pop[k]->fitness;
		i = lb;
		j = ub;
		do {
			while(pop[i]->fitness < pivot)
				i++;
			while(pop[j]->fitness > pivot)
				j--;
			if(i <= j) {
				swap = pop[i];
				pop[i] = pop[j];
				pop[j] = swap;
				i++;
				j--;
			}
		} while(i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}