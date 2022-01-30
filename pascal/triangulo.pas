program triangulo;
const max=10000;

type matriz = array [1..max,1..max] of longint;

var m:matriz; n:integer;

procedure imprimeMatriz (var m:matriz; n:integer);
var i,j:integer;
begin

	for i:=2 to n+1 do
	begin
		for j:=1 to n+1 do
			if m[i,j]<> 0 then
				write (m[i,j], ' ');
		writeln ();
	end;

end;

procedure imprimeTriangulo (var m:matriz; n:integer);
var i,j:integer;
begin


	m[1,2]:=1;
	for i:=1 to n+1 do
	begin
		for j:=i downto 2 do
		begin
			m[i,j]:=m[i-1,j-1]+m[i-1,j];
		end;
	end;
end;

procedure limpaMatriz (var m:matriz; n:integer);
var i,j:integer;
begin
	for i:=1 to n do
		for j:=1 to n do
			m[i,j]:=0;

end;

begin
	readln (n);
	limpaMatriz (m,n);
	imprimeTriangulo (m, n);
	imprimeMatriz(m,n);
end.
