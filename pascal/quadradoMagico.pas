program quadradoMagico;

function quadrado (n11,n12,n13,n21,n22,n23,n31,n32,n33:integer):boolean;

begin
if (n11+n12+n13=15) and (n21+n22+n23=15) and (n31+n32+n33=15) and (n11+n21+n31=15) 
	and (n12+n22+n32=15) and (n31+n32+n33=15) and (n11+n22+n33=15) and (n13+n22+n31=15) 
	and (n13+n23+n33=15) and (n11<>n12) and (n11<>n13) and (n11<>n21) and (n11<>n22) 
	and (n11<>n23) and (n11<>n31) and (n11<>n32) and (n11<>n33) and (n12<>n13) and (n12<>n21) 
	and (n12<>n22) and (n12<>n23) and (n12<>n31) and (n12<>n32) and (n12<>n33) and (n13<>n21) 
	and (n13<>n22) and	(n13<>n23) and	(n13<>n31) and	(n13<>n32) and	(n13<>n33) and (n21<>n22) 
	and	(n21<>n23) and	(n21<>n31) and	(n21<>n32) and	(n21<>n23) and	(n22<>n23) and	(n22<>n31)
	 and	(n22<>n32) and	(n22<>n33) and (n23<>n31) and	(n23<>n32) and	(n23<>n33) 
	 and (n31<>n32) and 	(n31<>n33) and	(n32<>n33) then
	quadrado:=true;
end;
var
n11,n12,n13,n21,n22,n23,n31,n32,n33:integer;
achou:boolean;
begin
	n11:=0;
	n33:=0;
	achou:=false;
	while (n11 <> 9) and (not achou) do
	begin
	n11:=n11+1;
		for n12:=1 to 9 do
			for n13:=1 to 9 do
				for n21:=1 to 9 do
					for n22:=1 to 9 do
						for n23:=1 to 9 do
							for n31:=1 to 9 do
								for n32:=1 to 9 do
								begin
									while( n33 < 9) and (not achou) do
									begin	
										n33:=n33+1;
										if quadrado (n11,n12,n13,n21,n22,n23,n31,n32,n33) then
															begin
																achou:=true;
																write (n11,' ',n12,' ',n13,' ');
																writeln ();	
																write (n21,' ',n22,' ',n23,' ');
																writeln ();	
																write (n31,' ',n32,' ',n33,' ');
																writeln ();	
															end;
														end;
											n33:=0;
										end;


	end;
end.
