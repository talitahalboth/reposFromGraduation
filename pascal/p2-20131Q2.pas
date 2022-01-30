program balanceada;
const max=10000;
type vetor=array [1..max] of integer;
var v:vetor; tamv:integer;

procedure LeVetor (var v:vetor; var tamv:integer);
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

procedure trocaVetor (var v:vetor; a,b:integer);
var aux:integer;
begin
	aux:=v[a];
	v[a]:=v[b];
	v[b]:=aux;
end;

procedure OrdenaPorSelecao (var v:vetor; tamv:integer);
var posIni,posCompara,menor:integer;
begin
	posIni:=1; //posição inicial a partir da qual o vetor está ordenado
	posCompara:=1; //posição do elemento que estamos comparando
	menor:=1; //posição do menor elemento encontrado até o momento
	while (posIni <= tamv) do
	begin
		posCompara:=posCompara+1;
		while posCompara<=tamv do
		begin
			if v[posCompara]<v[menor] then
			begin
				menor:=posCompara; //ocorre a troca a cada vez que um elemento menor é achado - 1 3 5 2, o menos é 2.
			end;
			posCompara:=posCompara+1;
		end;
		trocaVetor(v,posIni,menor); //troca o vetor da posição inicial com menor elemento do vetor a partir da "posiçao inicial"
		posIni:=posIni+1;
		menor:=posIni; //NÃO ESQUECER DE MUDAR O MENOR!!
		posCompara:=posIni;

	end;
end;

function Balanceada (var v:vetor; tamv:integer):boolean;
var i,x,soma:integer; b:boolean; //b é a variável que controla se o vetor está balanceado
begin
	x:=tamv;
	b:=true;
	i:=1;
	soma:=(v[1]+v[tamv]); 
	while (i<x) and (b) do
	begin
		if (v[i]+v[x]) <> soma then //compara a soma do valor n mais alto e do n mais baixo
			b:=false;
		x:=x-1;
		i:=i+1;
	end;
	Balanceada:=b;
end;

begin
	LeVetor (v,tamv);
	OrdenaPorSelecao (v,tamv);
	if Balanceada (v,tamv) then
		writeln ('Sim, eh balanceada.')
	else
		writeln ('Nao eh balanceada.');	

end.
