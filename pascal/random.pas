program aniversario;

type vetor=array[1..27] of integer;
var v:vetor;
	i,j,n:integer;


begin
		randomize;

	for i:=1 to 27 do
	begin

		v[i]:=random(364)+1;
	end;
	for i:=1 to 27 do
		write (v[i],' ');
end.
