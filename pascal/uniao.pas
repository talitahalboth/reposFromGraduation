program uniao;
const max=10000;
type vetor=array [1..max] of integer;
var v,w,y:vetor; tamv,tamw,tamy:integer;

procedure LeVetor (var v:vetor; var tamv:integer);
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

procedure uniao (var v,w,y:vetor; tamv,tamw:integer; var tamy:integer);
var i,j,k:integer; repetido:boolean;
begin
	tamy:=0;
	k:=0;	
	repetido:=false;
	for i:=1 to tamv do
	begin
		for j:=1 to tamw do
		begin
			if (v[i]<>w[j]) and (not repetido) then
			begin
				k:=k+1;
				y[k]:=v[i];
				repetido:=true;
			end				
			else if (v[i]=w[j]) then
			begin
				w[j]:=-1;
			end;
		end;
		repetido:=false;
	end;
	for j:=1 to tamw do
	begin
		if w[j]<> (-1) then
		begin
			k:=k+1;
			y[k]:=w[j];
		end;
	end;
	tamy:=k;
end;

procedure imprimeVetor ( var v:vetor; tamv:integer);
var i:integer;
begin
	for i:=1 to tamv do
		write (v[i],' ');
end;

begin
	levetor (v,tamv);
	levetor (w,tamw);
	uniao (v,w,y,tamv,tamw,tamy);
	write ('Conjunto Uniao = ');
	imprimevetor (y,tamy);
end.
