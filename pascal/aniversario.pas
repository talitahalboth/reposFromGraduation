program aniversario;

type vetor=array[1..27000] of longint;
var datas:vetor;
	i,pos,contaOcorrencias:longint;



procedure preenche (var v:vetor);
var i,j:integer;


begin
	randomize;
	for i:=1 to 27000 do
	begin

		v[i]:=random(364)+1;
	end;

end;


function TemCoincidencia (var v:vetor; var pos:longint):boolean;
var i,j:integer;
	coincide:boolean;
begin
	coincide:=false;
	for i:=pos+1 to pos+27 do
	begin
		for j:=pos to pos+27 do
			if (v[i]=v[j]) and (i<>j) then
				coincide:=true;
			end;
	TemCoincidencia:=coincide;

	pos:=i;

end;



begin
	contaocorrencias:=0;
	pos:=0;
	preenche (datas);
	for i:=1 to 1000 do
	begin
		if TemCoincidencia (datas,pos) then
			contaocorrencias:=contaocorrencias+1;


	end;

	writeln (contaocorrencias);

	

end.
