#include "SymbioticEvolution.h"

// コンストラクタ
SymbioticEvolution::SymbioticEvolution()
{
	int i, j;
	// 初期集団生成
	for(i = 0; i < WCHROM_LEN; i++)
		ppop[i] = new PartialPopulation();
	WholeIndividual::ppop = ppop;
	wpop = new WholePopulation();
	wpop->evaluation();
	for(i = 0; i < WCHROM_LEN; i++)
		ppop[i]->evaluation();
	// 最適解初期化
	bestfit = wpop->pop[0]->fitness;
	for(i = 0; i < WCHROM_LEN; i++) {
		for(j = 0; j < PCHROM_LEN; j++)
			best[i*PCHROM_LEN+j] = wpop->pop[0]->chrom[i]->chrom[j];
	}
	printf("初期世代\t最良個体の適応度は%f\n", bestfit);
}

// デストラクタ
SymbioticEvolution::~SymbioticEvolution()
{
	int i;

	for(i = 0; i < WCHROM_LEN; i++)
		delete ppop[i];
	delete wpop;
}

// 進化
void SymbioticEvolution::solve(void)
{
	int gen, i, j;
	double ave = 0, diff = 0;

	for(gen = 1; gen <= GENERATION_MAX; gen++) {
		// 次世代生成
		
		for(i = 0; i < WCHROM_LEN; i++)
			ppop[i]->newGeneration();
		wpop->newGeneration();
		// 評価
		for(i = 0; i < WCHROM_LEN; i++)
			ppop[i]->evalinit();
		wpop->evaluation();
		for(i = 0; i < WCHROM_LEN; i++)
			ppop[i]->evaluation();
		// 最適解更新
		if(wpop->pop[0]->fitness < bestfit) {
			bestfit = wpop->pop[0]->fitness;
			//初期化
			for(i = 0; i < PEOPLE_NUM; i++) {
				used_photo_cnt[i] = 0;
			}
	
			for(i = 0; i < WCHROM_LEN; i++) {
				for(j = 0; j < PCHROM_LEN; j++) {
					best[i*PCHROM_LEN+j] = wpop->pop[0]->chrom[i]->chrom[j];
					used_photo_cnt[best[i * PCHROM_LEN + j] / (MATERIAL_PHOTO_NUM / PEOPLE_NUM)]++;
				}
			}
			//平均
			for(i = 0; i < PEOPLE_NUM; i++) {
				printf("%d人目　%f枚\n",i, used_photo_cnt[i]);
				ave += used_photo_cnt[i];
			}
			ave /= PEOPLE_NUM;

			//分散
			for(i = 0; i < PEOPLE_NUM; i++) {
				diff += (used_photo_cnt[i] - ave) * (used_photo_cnt[i] - ave);
			}
			diff /= PEOPLE_NUM;

			for(i = 0; i < PEOPLE_NUM; i++) {
				printf("%d人目　%f枚\n",i, used_photo_cnt[i]);
			}
			if(diff <= 0.25) printf("0.25未満です！！！！！！！");
			printf("\n画像としての良さ：%f, 分散：%f\n", bestfit - diff * SCALE, diff);
			printf("第%d世代\t最良個体の適応度は%f\n", gen, bestfit);
		}
	}
}
