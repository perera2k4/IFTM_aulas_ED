#include <stdio.h>
#include <stdlib.h>
int main() {
	int n, i; // Note que o array não foi declarado previamente!
	printf("Digite o tamanho do array: ");
	scanf("%d", &n);
	int *arr = (int *)malloc(n * sizeof(int));
	if (arr == NULL) {
		printf("Falha na alocação de memória.\n");
		return 1;
 	}
	printf("Digite os elementos do array:\n");
	for (i = 0; i < n; i++) {
		// scanf("%d", arr + i);
		scanf("%d", &arr[i]);
	}
	printf("Elementos do array:\n");
	for (i = 0; i < n; i++) {
		//printf("%d ", *(arr + i));
		printf("%d ", (arr[i]));
	}
	free(arr);
	return 0;
}
