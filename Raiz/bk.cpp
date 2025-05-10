double potencia(double num, const int pot) {
	double resp = 1;
	for (int i = 1; i <= pot; i++) {
		resp *= num;
	}
	return resp;
}


double raizquadrada(const double v3__raizDe) {
	const int v0__indice = 2;
	const double v1__1Div_v0 = (double)1 / v0__indice;
	const int v2__v0Nmin1 = v0__indice - 1;
	double v4__resposta = (v3__raizDe == 0) ? 0 : 1;
	double v5__v4rElev_v2;
	double v6__v3Cdiv_v5;
	double v7__v2min1vezesR;
	double v8__somav7v6;
	double testar = 0;

	while (testar < v3__raizDe - 0.00001 || testar > v3__raizDe + 0.00001) {
		v5__v4rElev_v2 = potencia(v4__resposta, v2__v0Nmin1);
		v6__v3Cdiv_v5 = v3__raizDe / v5__v4rElev_v2;
		v7__v2min1vezesR = v2__v0Nmin1 * v4__resposta;
		v8__somav7v6 = v6__v3Cdiv_v5 + v7__v2min1vezesR;
		v4__resposta = v8__somav7v6 * v1__1Div_v0;
		testar = potencia(v4__resposta, v0__indice);

	}

	return v4__resposta;
}