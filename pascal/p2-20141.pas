program VetorArrumado;
const max=10000;
type vetor=array [1..max] of integer;
var v:vetor; tamv:integer; indice:integer; arruma:boolean;

procedure LeVetor (var v:vetor; var tamv:integer);
var i,n:integer;
begin
	read (n);
	tamv:=n;
	for i:=1 to n do
		read (v[i]);
end;

procedure buscaMaior(var v:vetor; j:integer; var i:integer);
var n:integer;
begin
	i:=1;
	for n:=1 to j-1 do
	begin
		if v[n]>v[i] then
			i:=n;
	end;
end;

procedure buscaMenor (var v:vetor; j,tamv:integer; var k:integer);
var n:integer;

begin
	k:=j+1;
	for n:=j+1 to tamv do
	begin
		if v[n]<v[k] then
			k:=n;
	end;
end;

function arrumado (var v:vetor; tamv:integer; var indice:integer): boolean;
var i,j,k:integer;
begin
	indice:=0;
	j:=2;
	arrumado:=false;
	while (j < tamv-1) and (arrumado = false) do
	begin
		i:=1;
		k:=j+1;
		buscaMaior(v,j,i);
		buscaMenor(v,j,tamv,k);
		if (v[i]<=v[j]) and (v[j]<v[k]) then //compara o elemento da pos. J com o da pos. I, o mesmo com pos. J x pos. K
		begin
			arrumado:=arrumado or true; //só precisamos de 1 certo para que seja verdadeiro
			indice:=j;
		end;	
		j:=j+1;
	end;
end;

begin
	LeVetor (v,tamv);
	arruma:=arrumado(v,tamv,indice);
	if arruma then
		writeln (indice)
	else
		writeln ('Este vetor nao esta arrumado');
end.	
