program Ocorrencias;

const max=10000;

type 
	vetor=array [1..max] of integer;
var
	tamv,fim:integer;
	v:vetor;

procedure leVetor (var v:vetor; var tamv:integer);
var n:integer;
begin
	read (n);
	tamv:=0;
	while (n <> 0) do
	begin
		tamv:=tamv+1;
		v[tamv]:=n;
		read (n);
	end;
end;

procedure ColocaNoFim (var v:vetor; j,tamv:integer);
var aux:integer;
begin
	aux:=v[j];
	while j < tamv do //troca os valores 1 a 1. No fim a posição v[tamv] fica com lixo de memória
	begin
		v[j]:=v[j+1]; 
		j:=j+1;
	end;
	v[tamv]:=aux; //colocar o auxiliar na posição final do vetor (v[vamv])
end;

procedure comparaETroca (var v:vetor; i,j:integer; var fim:integer);
begin
	if (v[i]=v[j]) then //compara se são iguais os dois elementos
	begin
		ColocaNoFim(v,j,tamv); 
		fim:=fim-1; //a última posição que não tem nenhum elemento repetido é decrescida em '1'
	end;
end;

procedure trocaRepetidos (var v:vetor; tamv:integer; var fim:integer);
var i,j:integer;
begin
	i:=1;
	j:=i+1; //posição dos elementos a serem comparados
	fim:=tamv; //variável que controla a posição onde terminam os elementos não repetidos do vetor
	while (i<fim) do
	begin
		while (j<fim) do
		begin
			comparaEtroca (v,i,j,fim);
			j:=j+1;
		end;	
		i:=i+1;
		j:=i+1;
	end;
end;

procedure imprimeQuantidadeDeRepetidos (var v:vetor; fim,tamv:integer);
var i,j,ocorrencias:integer;
begin
	i:=0;
	ocorrencias:=1; //todo elemento do vetor tem pelo menos uma ocorrência, e esta deve ser somada à quantidade de vezes que ele repete
	while i < fim do
	begin
		i:=i+1;
		j:=fim+1; //a partir da prosição seguinte à posição onde se encontra o último elemento não repetido! 
		while j <= tamv do
		begin
			if (v[i] = v[j]) then
				ocorrencias:=ocorrencias+1;
			j:=j+1;
		end;
		if (ocorrencias > 1) then //confere se é só uma ou mais de uma ocorrências
			writeln (v[i],': ', ocorrencias,' ocorrencias')
		else
			writeln (v[i],': ', ocorrencias,' ocorrencia');
		ocorrencias:=1;
	end;
end;

begin
	leVetor (v,tamv);
	fim:=tamv;
	trocaRepetidos (v,tamv,fim);
	writeln ('A sequencia contem:');
	imprimeQuantidadeDeRepetidos (v,fim,tamv);
end.
