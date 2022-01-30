program copiaEOrdenaRepetidos;
const max=10000;

type vetor=array [1..max] of integer;

var v:vetor; tamv:integer;

procedure LeVetor (var v:vetor; var tamv:integer);
var n:integer;
begin
	tamv:=0;
	read (n);
	while (n <> 0) do
	begin
		tamv:=tamv+1;
		v[tamv]:=n;
		read (n);
	end;
end;

procedure trocaValoresVetor1a1 (var v:vetor; primeiraPosicao,tamv:integer);
var i,aux:integer;

begin
	aux:=v[primeiraPosicao];
	for i:=primeiraPosicao to (tamv-1) do
	begin
		v[i]:=v[i+1];
	end;
	v[tamv]:=aux;
end;

procedure OrdenaRepetidos (var v:vetor; ini,fim:integer);
var seguinte:integer;

begin
	seguinte:=ini+1;
	while ini <= fim do
	begin
		while seguinte <= fim do
		begin
			while v[ini] > v[seguinte] do
			begin
				trocaValoresVetor1a1 (v, ini,fim);
			end;
			seguinte:=seguinte+1;
		end;
		ini:=ini+1;
		seguinte:=ini+1; //lembrar de reinicializar a var. Seguinte!
	end;
end;

procedure ImprimeVetor (v:vetor; tamv:integer);
var i:integer;
begin
	for i:=1 to tamv do
		write (v[i],' ');
end;

procedure MudaPosicaoRepetidos (var v: vetor; tamv:integer);
var ini,fim,seguinte:integer;
begin
	fim:=tamv;
	ini:=1;
	seguinte:=ini+1;
	while ini<>fim do
	begin
		while seguinte < fim do
		begin
			while v[seguinte] = v[ini] do // NÃO ESQUECER QUE É PRA COMPRAR O CONTEUDO DO VETOR NÃO O ÍNDICE!!!
			begin
				trocaValoresVetor1a1 (v, seguinte, tamv); // para trocar os valores precisa passar o tamanho do vetor! nao a var. fim! 
				fim:=fim-1;
			end;
			seguinte:=seguinte+1;
		end;
		ini:=ini+1;
		seguinte:=ini+1;
	end;
	OrdenaRepetidos (v, fim, tamv);
end;



begin
	LeVetor(v,tamv);
	MudaPosicaoRepetidos(v,tamv);
	ImprimeVetor (v,tamv);
	writeln ();
end.

