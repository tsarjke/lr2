#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main (int argc,char *argv[]) {
	FILE *source, *graph; //csv с данными, файл для графика
	double Q, X, c = 0;
	int a = 0, b = 0;
	char string[500], temp[10], *check, *istr, sep[2]=",", dur[15];
	memset(&dur,0,sizeof(dur));
	memset(&temp,0,sizeof(temp));
	char ip[15] = "192.168.250.59";
	//Проверка любого ip
	//printf("Введите ip: ");
	//scanf("%s",number);
	graph = fopen("graph.txt", "w");
	source = fopen("source.csv", "r");
	while(1) {
		check = fgets(string, 1000, source); //читаем строку
		if (!check) {
			break;
		}
		istr = strtok(string, sep); //делим строку на части (разделитель - запятая)
		while(istr) {
			a++; 
			if (a == 3) {
				for (int i = 0; i < strlen(istr); i++) {
					dur[i] = istr[i];
				}
				dur[strlen(istr)] = '\0';
			}
			if (a == 4) { //ищем строку sa (адрес источника)
				for (int i = 0; i < 14; i++) {
					if (istr[i] == ip[i]) {
						b++;
					}
					else {
						b = 0;
					}
				}
			}
			if (b == 14 && a == 13) { //ищем трафик источника
				for (int i = 0; i < strlen(istr); i++) {
					temp[i] = istr[i];
				}
				temp[strlen(istr)] = '\0';
				Q += atof(temp)/1024; //Кб делаем (Примечание 2)
				c += atof(dur);
				fprintf(graph,"%lf\t%lf\n",c,Q); //данные для графика
			}
			istr = strtok(NULL, sep);
		}
		a = 0;
		b = 0;
	}
	fclose(source);
	fclose(graph);
	if (Q < 500 ) {
		X = Q * 0.5;
	}
	else {
		X = 500 * 0.5 + (Q - 500) * 1;
	}	
	printf("%lf Кб\n",Q);
	printf("Итого: %.2lf рублей\n",X);
	return 0;
}
