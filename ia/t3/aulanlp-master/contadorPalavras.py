

#recebe um array de textos
#taxa de frequência. exemplo, se passar 0.8 vai retornar palavras que tem uma 
#taxa de frequência de 80%
#retorna um vocabulário filtrado pela 
def main(textos=[], taxa=0.6):
	qt_textos = len(textos)
	freq_necessaria = qt_textos*taxa
	print(f"Frequencia necessária: {freq_necessaria}")
	vocab = {}
	#interando sobre os textos
	for text in textos:
		_aux = text.lower().split()
		for palavra in _aux:
			if not palavra in vocab:
				vocab[palavra]=1
			else:
				vocab[palavra]+=1

	#selecioando palavras que apareçam em no mínimo 'freq_necessaria'
	vocab = dict((k, v) for k, v in vocab.items() if v >= freq_necessaria)
	print(vocab)


		
	

if __name__ == '__main__':
	textos = [
		'A cada de maria é branca',
		'Maria tem tem tem tem tem grande sabedoria',
		'essa Coisa é de maria',
		'cada coisa em seu lugar',
		'lugar de mulher é onde ela quiser'
	]
	main(textos=textos, taxa=1)

