class botaoComFilho {
private:
	HWND hwnd;
	HWND father;
	RECT actRect;	
	struct children {
		HWND hChild;
		long double x, y, w, h;
		children(HWND _hwnd, long double x, long double y, long double w, long double h) : hChild(_hwnd), x(x), y(y), w(w), h(h) {};
	};

	std::vector<children> childs;

	void adjust(int x, int y, int w, int h, UINT args) {

		for (children& c : childs) {
			SetWindowPos(c.hChild, NULL,
				x + (w * c.x), 		y + (h * c.y),
				w * c.w,			h * c.h,
				args
			);

			SendMessage(c.hChild, WM_SETFONT, (WPARAM)fontePadrao, FALSE);
		}
		
		
		
		SetWindowPos(father, NULL, x, y, w, h, args);
		
		
	}
public:
	botaoComFilho() {
		hwnd = NULL;
		father = NULL;
		actRect = { 0 };
	};

	void registrar(HWND _hwnd, HWND f) {
		hwnd = _hwnd;
		father = f;
	}
	
	void getActRect(){	
		GetWindowRect(hwnd, &actRect);
		
		for (children& c : childs){
			RECT tmpRect;
			GetWindowRect(c.hChild, &tmpRect);
			
			if (tmpRect.left < actRect.left) actRect.left = tmpRect.left;
			if (tmpRect.right > actRect.right) actRect.right = tmpRect.right;
			if (tmpRect.top < actRect.top) actRect.top = tmpRect.top;
			if (tmpRect.bottom > actRect.bottom) actRect.bottom = tmpRect.bottom;
		};
		
	};

	void setPosition(int x, int y, int w = 0, int h = 0) {
		RECT rec;
		GetClientRect(hwnd, &rec);
		updateFontSize(rec.right * 1.5);


		UINT args = NULL;
		if (w == 0 && h == 0) args = SWP_NOSIZE;
		
		
		
		SetWindowPos(father, NULL, x, y, w, h, args);
		adjust(x, y, w, h, args);
		
		getActRect();
		
		x += x - actRect.right;
		y += y - actRect.bottom;
		
		SetWindowPos(father, NULL, x, y, w, h, args);
		adjust(x, y, w, h, args);
		
		SendMessage(father, WM_SETFONT, (WPARAM)fontePadrao, FALSE);
		
		
	}

	HWND& createChild(std::wstring classe, std::wstring nome, UINT styles, long double xPercent, long double yPercent, long double wPercent, long double hPercent, UINT hMenu) {
		HWND tmpChild = CreateWindow(classe.c_str(), nome.c_str(),
			styles,
			0, 0, 0, 0,
			hwnd, (HMENU)hMenu, NULL, NULL);
		childs.push_back(children(tmpChild, xPercent, yPercent, wPercent, hPercent));
		
		return childs[childs.size() - 1].hChild;
	}
};







//-FUNCAO PARA CENTRALIZAR AS JANELAS----------------------------------------------------------------------------------------//
void centerMyWnds(std::vector<HWND>& vec, int wTam, int hTam, bool horiz, int otherDirec, float begin, float end, bool lockL) { //	
	int buttonSize = 0;																										 //
	int X = otherDirec, Y = otherDirec, *thisPos = nullptr;																	 //
																															 //
	//Define se o que precisamos eh a altura ou comprimento, e faz o ponteiro apontar pro mesmo.							 //
	if (horiz){																											 //
		buttonSize = wTam;																									 //
		thisPos = &X;																										 //
	}																														 //
	else {																													 //
		buttonSize = hTam;																									 //
		thisPos = &Y;																										 //
	}																														 //
																															 //
																															 //
																															 //
	float winsEspace = buttonSize * vec.size();	//Espaco que as janelas juntas ocupam.										 //
	float espace = (end - begin - winsEspace) / (vec.size() + 1);	//Espaco entre as janelas.								 //
																															 //
	float aux = espace, aux2 = 0;																							 //
																															 //
	if (lockL) {																											 //
		//Se estiver com a trava do lado esquerdo, pintar a primeira janela sem o espacamento inicial.						 //
		aux = 0;																											 //
		//O espacamento inicial que existia antes eh divido pros que sobraram.												 //
		espace += espace / (vec.size() - 1);																				 //
	}																														 //
																															 //
	if (end - begin < winsEspace) {																							 //
		//Caso o espaco ocupado pelas janelas for maior que a area do comeco e fim, deixe-os lado a lado.					 //
		espace = 0;																											 //
		aux = espace;																										 //
	}																														 //
																															 //
	for (HWND& b : vec) {																									 //
		//Altera o X ou o Y, isso vai depender do que foi recebido pela funcao.												 //
		*thisPos = begin + aux + aux2;	//Truncamento.																		 //
																															 //
		SetWindowPos(b, NULL,																								 //
			X, Y,																											 //
			wTam, hTam, NULL);																								 //
																															 //
		//Calculo para saber onde eh a proxima janela.																		 //
		aux += espace;																										 //
		aux2 += buttonSize;																									 //
	}																														 //
}																															 //
//---------------------------------------------------------------------------------------------------------------------------//