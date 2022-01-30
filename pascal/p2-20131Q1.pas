program Fahrenheit;
const max=10000;
type vetor=array [1..max] of real;
var v:vetor; tamv:integer;

procedure LeVetor (var v:vetor; var tamv:integer);
var n:real;
begin
	read (n);
	tamv:=0;
	while n <> 0 do
	begin
		tamv:=tamv+1;
		v[tamv]:= n;
		read (n);
	end;
end;

procedure converte (var v:vetor; tamv:integer);
var i:integer;
begin
	for i:=1 to tamv do
	begin
		v[i]:=(5*(v[i]-32)/9); //fórmula de conversão Fahrenheit -- Celsius
	end;
end;

function Media ( var v:vetor; tamv:integer):real;
var i:integer; soma:real;
begin
	soma:=0;
	for i:=1 to tamv do
	begin
		soma:=soma+v[i];
	end;
	Media:=soma/tamv; //Soma todos os valores do vetor e divide pela quantidade de elementos
end;	

function DesvioPadrao (var v:vetor; tamv:integer):real;
var m,desvio:real; i:integer;
begin
	desvio:=0;
	m:=Media (v,tamv); // já temos uma função pronta para a Média, é só usá-la! (mas não colocar no FOR, pos ficaria caro)
	for i:=1 to tamv do
		desvio:=((v[i]-m)*(v[i]-m))+desvio;
	DesvioPadrao:=sqrt (desvio/tamv); //raiz!!
end;

begin
	LeVetor (v,tamv);
	if tamv <> 0 then //confere se há elementos no vetor :)
	begin
		converte (v,tamv);
		writeln ('A media eh ',Media(v,tamv):0:3,' e o desvio eh ',DesvioPadrao(v,tamv):0:3);
	end
	else
		writeln ('Nao ha elementos no vetor!');
end.


