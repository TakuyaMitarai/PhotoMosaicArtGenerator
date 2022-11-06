#include "WholePopulation.h"

// コンストラクタ
WholePopulation::WholePopulation()
{
	int i;

	for(i = 0; i < WPOP_SIZE; i++)
		pop[i] = new WholeIndividual();
	for(i = 0; i < CHILDPOP; i++)
		childpop[i] = new WholeIndividual();
}

// デストラクタ
WholePopulation::~WholePopulation()
{
	int i;

	for(i = 0; i < WPOP_SIZE; i++)
		delete pop[i];
	for(i = 0; i < CHILDPOP; i++)
		delete childpop[i];
}

// 次世代生成
void WholePopulation::newGeneration()
{
	int i, a, b, index1, index2;

	a = rand() % WPOP_SIZE;
	b = (rand() % (WPOP_SIZE - 1) + a + 1) % WPOP_SIZE;
	index1 = rand() % WCHROM_LEN;
	index2 = ((rand() % (WCHROM_LEN - 1)) + index1) % WCHROM_LEN;
	childpop[0]->newGeneration(pop[a], pop[b], index1, index2);
	childpop[1]->newGeneration(pop[b], pop[a], index1, index2);
	childpop[2]->newGeneration(pop[a]);
	childpop[3]->newGeneration(pop[b]);
	childpop[4]->newGeneration();
	childpop[5]->newGeneration();
	changePC(a, b);
	for(i = 0; i < WPOP_SIZE; i++) {
		if((i != a) && (i != b))
			pop[i]->newGeneration();
	}
}

// 親子選択
void WholePopulation::changePC(int a, int b)
{
	int i, best, worst;
	double alpha, beta, fitsum, r;
	WholeIndividual* tmp;

	// 最良個体を残す
	childpop[0]->evaluation();
	for(best = 0, i = 1; i < CHILDPOP; i++) {
		childpop[i]->evaluation();
		if(childpop[best]->fitness > childpop[i]->fitness)
			best = i;
	}
	if(best) {
		tmp = childpop[0];
		childpop[0] = childpop[best];
		childpop[best] = tmp;
	}
	tmp = pop[a];
	pop[a] = childpop[0];
	childpop[0] = tmp;
	
	// スケーリング法で適応度を変換
	for(best = 1, worst = 1, i = 2; i < CHILDPOP; i++) {
		if(childpop[worst]->fitness < childpop[i]->fitness)
			worst = i;
		if(childpop[best]->fitness > childpop[i]->fitness)
			best = i;
	}
	alpha = (100000 / (double)(CHILDPOP - 1) - 100) / (childpop[best]->fitness - childpop[worst]->fitness);
	beta = 100 - alpha * childpop[worst]->fitness;
	fitsum = 0.0;
	for(i = 1; i < CHILDPOP; i++) {
		childfit[i] = alpha * childpop[i]->fitness + beta;
		fitsum += childfit[i];
	} 
	for(i = 1; i < CHILDPOP; i++)
		childfit[i] /= fitsum;

	// 残りからルーレットで１つ選んで残す
	r = (double)rand() / RAND_MAX;
	for(i = 1; i < CHILDPOP - 1; i++) {
		if(r < childfit[i])
			break;
		r -= childfit[i];
	}
	tmp = pop[b];
	pop[b] = childpop[i];
	childpop[i] = tmp;
}

// 評価
void WholePopulation::evaluation()
{
	int i, j;

	for(i = 0; i < WPOP_SIZE; i++) {
		pop[i]->evaluation();
		// 参照先の個体の適応度を算出
		for(j = 0; j < WCHROM_LEN; j++) {
			if(pop[i]->chrom[j]->fitness > pop[i]->fitness)
				pop[i]->chrom[j]->fitness = pop[i]->fitness;
		}
	}
	sort(0, WPOP_SIZE-1);
}

// 昇順にクイックソート
// lb : 開始点添字
// ub : 終了点添字
void WholePopulation::sort(int lb, int ub)
{
	int i, j, k;
	double pivot;
	WholeIndividual* swap;

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
