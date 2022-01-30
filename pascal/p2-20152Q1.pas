program MinMaxV2;
const MAXI=10000;
type vetor=array [1..MAXI] of integer;

var v,v2:vetor;
	tam,tam2,min,max:integer;
	
procedure LeVetor (var v:vetor; var tamv:integer);
var n,i:integer;
begin
	read (n);
	for i:=1 to n do
		read (v[i]);
	tamv:=i;	
end;

procedure VetorMinMax(var v,v2:vetor; tam,min,max:integer; var tam2:integer);
var i,j:integer;
begin
	j:=0;
	for i:=1 to tam do
	begin
		if v[i] >= min then
		begin
			v2[j]:=v[i];
			j:=j+1;
		end
		else if v[i] <= max then
		begin
			v2[j]:=v[i];
			j:=j+1;
		end;
	end;
	tam2:=j;
end;

procedure imprimeVetor (var v:vetor; tam:integer);
var i:integer;
begin
	for i:=1 to tam do
		write (v[i],' ');
end;

begin
	tam2:=0;
	tam:=0;
	LeVetor (v,tam);
	read (min);
	read (max);
	VetorMinMax(v,v2,tam,min,max,tam2);
	writeln ();
	imprimeVetor (v2, tam2);
	writeln ();
end.
