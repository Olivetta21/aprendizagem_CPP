void ordena(int vet[]) {
	for (int i = 0; i < 3; i++) {
		for (int j = i; j < 3; j++) {
			if (vet[i] < vet[j]) {
				int temp = vet[j];
				vet[j] = vet[i];
				vet[i] = temp;
			}
		}
	}
}