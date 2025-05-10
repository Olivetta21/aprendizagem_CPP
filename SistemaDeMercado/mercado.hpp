void ordena(int vet[], int tam) {
	for (int i = 0; i < tam; i++) {
		for (int j = i; j < tam; j++) {
			if (vet[i] < vet[j]) {
				int temp = vet[j];
				vet[j] = vet[i];
				vet[i] = temp;
			}
		}
	}
}