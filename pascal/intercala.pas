program Intercalacao;
const max=10000;
type vetor=array [1 .. max] of real; 
var va,vb,vc:vetor;
	tama,tamb,tamc:integer;

procedure leVetor (var v:vetor; var tamv:integer);
var n:real;
begin
	read (n);
	tamv:=0;
	while n <> 0 do
	begin
		tamv:=tamv+1;
		v[tamv]:=n;
		read (n);
	end;
end;

procedure imprimeVetor (var v:vetor; tamv:integer);
var i:integer;
begin
	for i:=1 to tamv do
		write (v[i]:0:1,' ');
end;

procedure limpaVetor (var tamVetor:integer);
begin
	tamVetor:=0;
end;

procedure intercala (var va,vb,vc:vetor; tama,tamb:integer; var tamv:integer);
var i,j,k:integer;
begin
	i:=0;
	j:=0;
	k:=0;
	while (i<tama) and (j<tamb) do
	begin
		k:=k+1;
		if (k mod 2 <> 0) then //usar o valor dele (mod 2) para fazer a intercalação na hora de inserir elementos
		begin
			i:=i+1;
			vc[k]:=va[i];
		end
		else //se k for par
		begin
			j:=j+1;
			vc[k]:=vb[j];
		end;
	end;
	if i=tama then //descobrir porque saiu do laço. Continua colocando os valores que sobraram, se houver algum.
	begin
		while j<tamb do
		begin
			k:=k+1;
			j:=j+1;
			vc[k]:=vb[j];
		end;
	end
	else
	begin
		while i<tama do
		begin
			k:=k+1;
			i:=i+1;
			vc[k]:=va[i];	
		end;	
	end;
	tamc:=k;
end;

begin
	limpaVetor (tama); //coloca como 0 o valor do tamanho do vetor -->"limpa o vetor"
	limpaVetor (tamb);
	limpaVetor (tamc);
	leVetor (va, tama);
	leVetor (vb, tamb);
	intercala (va, vb, vc, tama,tamb,tamc);
	imprimevetor (vc, tamc);	
end.
