program repetidos;
const max=10000;
type vetor=array [1..max] of integer;
var v,w:vetor; tamv,tamw:integer;

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

procedure tiraRepetidos (var v,w:vetor; tamv:integer; var tamw:integer);
var i,j,k:integer; repetido:boolean;
begin
	repetido:=false;
	k:=0;
	for i:=1 to tamv do
	begin
		for j:=i+1 to tamv do
		begin
			if (v[i]=v[j]) and (not repetido) and (v[i]<>(-1))then
			begin
				repetido:=true;
				k:=k+1;
				w[k]:=v[i];
			end
			else if (v[i]=v[j]) and (repetido) then
				v[j]:=-1;
		end;
		repetido:=false;
	end;
	tamw:=k;
end;

procedure imprimevetor (var v:vetor; tamv:integer);
var i:integer;
begin
	for i:=1 to tamv do
		write (v[i],' ');
end;

begin
	Levetor (v,tamv);
	tirarepetidos(v,w,tamv,tamw);
	write ('Os repetidos sao: ');
	imprimevetor (w,tamw);
	
	
end.
