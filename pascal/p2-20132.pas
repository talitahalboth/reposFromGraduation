program passou_do_limite;
const max=10000;
type vetor=array [1..max] of integer;
var v,w:vetor; tamv,tamw,limite:integer;

procedure LeVetor (var v:vetor; var tamv:integer);
var n,i:integer;
begin
	read (n);
	tamv:=0;
	i:=0;
	while n <> 0 do
	begin
		i:=i+1;
		v[i]:=n;
		read (n);
	end;
	tamv:=i; //não esquecer de atribuir o valor de i ao tamw no fim :)
end;

procedure testaLimite (var v,w:vetor; tamv:integer; var tamw:integer; limite:integer);
var cont,cont2,soma:integer;
begin
	cont:=1;
	cont2:=0;
	soma:=0;
	while cont < tamv do
	begin
		while (soma<limite) and (cont <= tamv) do
		begin
			soma:=soma+v[cont];
			cont:=cont+1;
		end;
		if soma > limite then //w só recebe os valores de somas acima de 90! testar se saiu do laço por causa da soma ou do tamv.
		begin
			cont2:=cont2+1;
			w[cont2]:=v[cont-1];
			soma:=0;
		end;
	end;
	tamw:=cont2;
end;

procedure ImprimeVetor (var v:vetor; tamv:integer);
var i:integer;
begin
	for i:=1 to tamv do
		write (v[i],' ');
end;

begin
	LeVetor (v,tamv);
	readln (limite);
	testaLimite (v,w,tamv,tamw,limite);
	ImprimeVetor (w,tamw);	
end.

