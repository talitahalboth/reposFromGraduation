program CombinaVetoresAPartirdeK;
const max=200;
type vetor=array [1..max] of integer;
var v,w:vetor; n,m,k:integer;

procedure LeVetor (var v:vetor; n:integer);
var i:integer;
begin
	for i:=1 to n do
		read (v[i]);
end;

procedure TrocaPosVetor1a1 (var v:vetor; posIni,posFim,k:integer); //coloca o último elemento válido do vetor na nova última posição (tamv)
var i,x:integer;
begin
	x:=posIni;
	while (posFim <> k) do
	begin
		v[posFim]:=v[x];
		x:=x-1;
		posFim:=posFim-1;
	end;
end;

procedure CombinaVetor (var v,w:vetor; k,tamw:integer; var tamv:integer);
var i,j,x:integer;
begin
	x:=tamv+tamw;
	j:=1;
	if (tamv+tamw <= max) then
	begin
		TrocaPosVetor1a1 (v,tamv,x,k); //tamv é onde começa a copia que vai descendo até k. tamv+tamw é para onde é feia a cópia 
		for i:=k to tamw+k-1 do //cópia inválida entrando na posição tamw+k do vetor V. 
		begin
			v[i]:=w[j];	
			j:=j+1;
		end;
	end
	else
		writeln ('ERRO'); //dá erro se a soma de w e v for maior que a capacidade de v (200, no caso)
end;


procedure ImprimeVetor (var v:vetor; tamv:integer);
var i:integer;
begin
	for i:=1 to tamv do
		write (v[i],' ');
end;

begin
	read (n,m); //n e m são os tamanhos dos vetores v e w, respectivamente
	LeVetor (v, n);
	LeVetor (w, m);
	read (k); //a partir de onde inserir o vetor w
	CombinaVetor (v,w,k,m,n);
	ImprimeVetor (v,n+m);
	writeln ();
end.
