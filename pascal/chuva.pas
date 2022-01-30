program chuva;
uses CRT;
const
	max=10000;
	gotas=1;
	espacos=0;

type matriz= array [1..max,1..max] of integer;

var m:matriz;
	lin,col,j,numgotas:integer;

procedure LeLinhaseColunas (var lin,col,gotas:integer);
begin
	lin:=70;
	col:=100;
	gotas:=40;
end;

procedure EncheMatrizdeEspacos (var m:matriz; lin,col:integer);
var i,j:integer;
begin
	for i:=1 to lin do
		for j:=1 to col do
			m[i,j]:=(espacos);
end;

procedure adicionaGotasaleatorias (var m:matriz; lin,col,numdegotas:integer);
var x,y,i:integer;
begin
	for i:=1 to numdegotas do
	begin
		x:=random(col)+1;
		y:=random(lin)+1;
		m[y,x]:=(gotas);
	end;

end;

procedure adicionaGotaslinha1 (var m:matriz; lin,col:integer);
var i,j,x:integer;
begin
	j:=random(3);
	for i:=1 to j do
	begin
		x:=random(col)+1;
		m[1,x]:=(gotas);
	end;
end;

procedure Imprimegotas (var m:matriz; lin,col:integer);
var i,j,k:integer;
begin
		for k:=1 to col+2 do
			write ('-'); //topo da janela
		writeln ();
	for i:=1 to lin do
	begin
		for j:=1 to col do
		begin
			if j=1 then
				write ('|'); //borda esquerda
			
			if m[i,j] = gotas then
				write ('|')
			else
				write (' ' );
			if j = col then

		end;
		writeln ('|');
	end;

	for k:=1 to col+2 do // base da janela 
		write ('+');
	writeln ();
end;

procedure desceChuvaUmaLinha (var m:matriz; lin,col:integer);
var i,j:integer;
begin
	for i:=lin downto 2 do
		for j:=col downto 1 do
			m[i,j]:=m[i-1,j];
	for j:=1 to col do
		m[1,j]:=espacos;
	
end;

begin
	randomize ();
	Lelinhasecolunas(lin,col,numgotas);
	enchematrizdeespacos(m,lin,col);
	adicionagotasaleatorias(m,lin,col,numgotas);
	imprimegotas (m,lin,col);
	for j:=1 to 500 do
	begin
		descechuvaumalinha (m,lin,col);
		delay (100);
		clrscr();
		imprimegotas (m,lin,col);
		adicionagotaslinha1 (m,lin,col);

	end;


end.


