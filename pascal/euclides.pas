program euclides;
var mdc:integer;

function EncontraMDC (a,b:integer):integer; //faz mdc de 2 números
var r:integer; //r é o resto, com a=b.x+r
begin
	r:=(a mod b);
	while r <> 0 do
	begin
		a:=b;
		b:=r;
		r:=(a mod b);
	end;
	EncontraMDC:= b;
end;

function LeEAchaMDC :integer;
var n,a,b,mdc:integer;
begin
	read (n);
	mdc:=n;
	read (n);
	while n <> 0 do
	begin
		if mdc>n then
		begin
			a:=mdc;
			b:=n;
		end
		else
		begin
			b:=mdc;
			a:=n;
		end;
		mdc:=(EncontraMDC(a,b));
		read (n);
	end;
	LeEAchaMDC:=mdc;
end;


begin
	mdc:=LeEAchaMDC;
	writeln (mdc);
end.
