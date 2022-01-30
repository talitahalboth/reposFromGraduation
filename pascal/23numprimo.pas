program calcula23numprimo;

function calculaNumerosPrimos (n:integer):integer;
var primoteste,numprimos,divisores:integer; primo:boolean;
begin
	primoteste:=3;	
	primo:=true;
	numprimos:=2;
	while numprimos < n do
	begin
		primoteste:=primoteste+2;
		divisores:=primoteste-1;
		while divisores>2 do
		begin
			if primoteste mod divisores = 0 then
				primo:=false;
			divisores:=divisores-1;
		end;
		if primo then
			numprimos:=numprimos+1;
		primo:=true;
	end;
	calculaNumerosPrimos:=primoteste;
end;

begin
	writeln (calculaNumerosPrimos (23));

end.



