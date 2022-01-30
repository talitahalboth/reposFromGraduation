program funcoeseProcedimentos;
const max=10000;

type	vetor=array [1..max] of integer;

var v:vetor;
	tamv:integer;

procedure LeVetor(var v:vetor; var tamv:integer);
var n,i:integer;
begin
	read (n);
	i:=0;
	while n <> 0 do
	begin
		i:=i+1;
		v[i]:=n;
		read (n);
	end;
	tamv:=i;
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

Procedure imprimeVetor (var v:vetor; tamv:integer);
var i:integer;
begin
	for i:=1 to tamv do
		write (v[i],' ');
end;

begin
	LeVetor (v,tamv);
	OrdenaPorSelecao (v,tamv);
	imprimeVetor (v,tamv);
	writeln ();
end.
