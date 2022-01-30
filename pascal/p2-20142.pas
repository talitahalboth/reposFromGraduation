program prova2;
const max=10000;
type vetor=array [1..max] of integer;
var vetor1,vetor2:vetor; grau,discrepancia:integer;

procedure LeVetor (var v:vetor);
var i:integer;
begin
	for i:=1 to 10 do
		read (v[i]);
end;

procedure compara (var v1,v2:vetor; grau:integer; var disc:integer);
var i:integer;
begin
	disc:=0;
	for i:=1 to 10 do
	begin
		if (v2[i]-grau>v1[i]) or (v1[i]>v2[i]+grau) then
			disc:=disc+1;
	end;
end;

begin
	LeVetor (vetor1);
	LeVetor (vetor2);
	read (grau);
	compara (vetor1, vetor2, grau,discrepancia);
	if discrepancia > 0 then
		writeln ('DIFERENTES com ', discrepancia,' discrepantes')
	else
		writeln ('PARECIDOS');
end.
