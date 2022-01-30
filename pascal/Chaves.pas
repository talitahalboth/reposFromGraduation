program clah;
var n:integer;

function Balanco (n:integer):boolean;
var abrecolchete,fechacolchete,i:integer;
	c:char;	
	balanceado:boolean;
begin
	i:=0;
	abrecolchete:=0;
	fechacolchete:=0;
	while i <> n do
	begin
		read (c);
		if c = ('{') then
			abrecolchete:=abrecolchete+1;
		if c = ('}') then
		begin
			fechacolchete:=fechacolchete+1;
			if fechacolchete > abrecolchete then //tem que abrir uma chave antes de fechá-la! se tiver mais fechadas algo está errado.
				balanceado:=false;
		end;
		if c = chr(10) then 
			i:=i+1;			
	end;
	if abrecolchete <> fechacolchete then
		balanceado:=false;
	Balanco:=balanceado;
end;

begin
	readln (n);
	if Balanco (n) then
		writeln ('S')
	else
		writeln ('N');
	
end.
