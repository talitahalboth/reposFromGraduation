program multiplica;
var a,b,maior,menor,resultado,pot10:longint;

begin
	readln (a);
	readln (b);
	resultado:=0;
	pot10:=1;
	if a<b then
	begin
		menor:=a;
		maior:=b;
	end
	else
	begin
		menor:=b;
		maior:=a;
	end;
	while menor>0 do
	begin
		resultado:=resultado+(pot10*(menor mod 10)*maior);
		menor:=menor div 10;
		pot10:= pot10 * 10;
	end;
	writeln (resultado);
end.
