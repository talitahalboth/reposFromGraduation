Program BoulderDash;
uses crt;

const
    MAX = 100;
    PREGUICA = 100;
    ARQ_MINA = 'mina-nivel1.txt';
    cJOGADOR = '@';
    cSAIDA = 's';
    cDIAMANTE = '*';
    cPEDRA = 'o';
	cSAIDAFECHADA = '$';
	cESPACO = ' ';
	cTERRA = '.';
	cPAREDE = '#';
	cPEDRACAINDO = 'f';
	cDIAMANTECAINDO = 'l';
    ZERO = #0;
    CIMA  = #72; (* ^ *)
    ESQ	  = #75; (* < *)
    DIR	  = #77; (* > *)
    BAIXO = #80; (* v *)
    ESC	  = #27; (* ESC *)
type
    Tmina = array [1..MAX, 1..MAX] of char;

(* le uma mina de um arquivo *)
Procedure leMina(
        var tela: Tmina;
        var dimX, dimY: integer);
Var
    arquivo: text;
    i,j:integer;
Begin
    assign(arquivo, ARQ_MINA);
    reset(arquivo);
    readln(arquivo, dimY, dimX);
    for i:=1 to dimY do
    begin
        for j:=1 to dimX-1 do
            read(arquivo, tela[i,j]);
        readln(arquivo, tela[i,dimX]);
    end;    
    close(arquivo);
End;

function ContaObjeto (var tela:tmina; dimX,dimy:integer; obj:char):integer;
//conta ocorrências de um determinado objeto na fase
var i,j,n:integer;
begin
	n:=0;
	for i:=2 to dimy-1 do
		for j:=2 to dimx-1 do
			if tela[i,j]=obj then
				n:=n+1;
	ContaObjeto:=n;
end;
 
procedure EncontraObjeto (var tela:tmina; dimx,dimy:integer; var x,y:integer; obj:char);
	//encontra um determinado objeto na fase
var i,j:integer;
	achou:boolean;
begin
	achou:=false;
	i:=1;
	j:=1;
	while ( i< dimy) and(not achou) do
	begin
		while( j< dimx ) and (not achou) do
		begin
			if tela [i,j] = obj then
			begin
				achou:=true;
				x:=j;
				y:=i;
			end;
			j:=j+1;
		end;
		i:=i+1;	
		j:=1;

	end;

end;   

(* inicializa o jogo *)
Procedure inicializaJogo(
        var tela: Tmina;
        var dimX, dimY: integer;
        var jogX, jogY: integer; 
        var diamTotal, diamColet: integer;
        var pontos, numMovim: integer;
        var saidaX, saidaY: integer);
Begin
	//Le o arquivo da fase
    leMina(tela, dimX, dimY); 
    //Conta os diamantes
	diamTotal:=contaObjeto (tela,dimx,dimy,cDIAMANTE);
	//Inicializa o número de diamantes coletados
	diamColet:=0;
	//encontra a saída
	EncontraObjeto (tela,dimx,dimy,saidax,saiday,cSAIDA);
	//a saída é substituída pela saída fechada
	tela[saiday,saidax]:=cSAIDAFECHADA;
End;


Procedure mostraTela
	(var tela: Tmina; 
	dimX, dimY: integer; 
	diamtotal, diamcolet:integer);
Var
    i,j:integer;
Begin
    clrscr();
    //imprime o total de diamantes e os diamantes coletados
	writeln ('Total de Diamantes: ', diamtotal);
	writeln ('Diamantes Coletados: ', diamcolet);
    for i:=1 to dimY do
    begin
        for j:=1 to dimX-1 do
		begin
		//imprime a tela
			if tela[i,j] = cPEDRACAINDO then
				write(cPEDRA)
			else if tela[i,j] = cDIAMANTECAINDO then
				write(cDIAMANTE)

			else
           		write(tela[i,j]);
		end;
        writeln(tela[i,dimX]);
    end;
    writeln();
End;

(* le a entrada do teclado *)
Function leEntrada(): char;
Var ch: char;
Begin
    if KeyPressed then
    begin
        ch := ReadKey;
        if (ch = ZERO) then
            ch := ReadKey ;
    end
    else
        ch := ZERO;
    leEntrada := ch ;
End;
    
procedure MovimentaObjeto 
	(var tela:Tmina; 
	dimx,dimy:integer; 
	var jogx,jogy:integer; 
	movimento:char; Obj:char); //x=colunas, y=linhas

begin
	//serve para movimentar o mineiro (ou pedras q ele empurra)
	if movimento = esq then
	begin
		tela[jogy,jogx]:= cESPACO;
		tela[jogy,jogx-1]:= Obj;
	end;	
	if movimento = dir then
	begin
		tela[jogy,jogx]:= cESPACO;
		tela[jogy,jogx+1]:= obj;
	end;	
	if movimento = cima then
	begin
		tela[jogy,jogx]:= cESPACO;
		tela[jogy-1,jogx]:= obj;
	end;	
	if movimento = baixo then
	begin
		tela[jogy,jogx]:= cESPACO;
		tela[jogy+1,jogx]:= obj;
	end;	

end;

procedure EncontraJogador (var tela:tmina; dimx,dimy:integer; var posx,posy:integer);
	//encontra a posição do jogador/mineiro
var i,j:integer;
begin
    for i:=1 to dimY do
    begin
        for j:=1 to dimX-1 do
            if tela [i,j]=cJOGADOR then
			begin
				posy:=i;
				posx:=j;
			end;
        if tela [i,dimx]=cJOGADOR then
			begin
				posy:=i;
				posx:=dimx;
			end;
    end;
end;

procedure DirecaoMovimento (var tela:tmina; jogx,jogy:integer; 
movimento:char; var x,y:integer);
// passa por referência a direção para onde vai o personagem

begin
	if movimento = esq then
	begin
		x:=jogx-1;
		y:=jogy;
	end;	
	if movimento = dir then
	begin
		x:=jogx+1;
		y:=jogy;
	end;	
	if movimento = cima then
	begin
		x:=jogx;
		y:=jogy-1;
	end;	
	if movimento = baixo then
	begin
		x:=jogx;
		y:=jogy+1;
	end;
end;



function ProximoObjeto (var tela:tmina; x,y:integer):integer;
//descobre qual objeto está diretamente na direção para onde o jogador vai
var i:integer;
(*	1 - espaco
	2 - terra
	3 - diamante
	4 - pedra
	5 - parede
*)
begin
	i:=0;
	if tela[y,x] = cJOGADOR then
		i:=0
	else if tela[y,x] = cSAIDA then
		i:=0
	else if tela[y,x] = cESPACO then
		i:=1
	else if tela[y,x] = cTERRA then
		i:=2
	else if tela[y,x] = cDIAMANTE then
		i:=3
	else if tela[y,x] = cPEDRA then
		i:=4
	else if tela[y,x] = cPAREDE then
		i:=5

	else if tela[y,x] = cPEDRACAINDO then
		i:=6
	else if tela[y,x] = cDIAMANTECAINDO then
		i:=7
	else if tela[y,x] = cSAIDAFECHADA then
		i:=8;
	proximoObjeto:=i;
end;


procedure CaiObjeto 
	//serve para diamantes e pedras que caem.
	(var tela:tmina; 
	dimx,dimy:integer; 
	obj, objCaindo:char;
	var morreu:boolean);

var i,j,c:integer;
begin
	for i:=dimy downto 1 do
	begin
		for j:=dimx downto 1 do
		begin
			if ((tela [i,j])=obj) or ((tela [i,j])=objCaindo) then
			begin
				c:=ProximoObjeto (tela,j,i+1); 
				 //tem jogador em baixo e a pedra/diamante está caindo, jogador morre
				if (c=0) and (tela [i,j]=objCaindo) then
				begin
					tela [i+1,j]:=cESPACO;
					morreu:=true;
				end
				//se tem espaço, pedra/diamante cai
				else if c = 1 then 
				begin
					tela [i,j]:=cESPACO;
					tela[i+1,j]:=objCaindo;
				end
				//se tem terra, pedra/diamante para de cair
				else if (proximoObjeto (tela, j,i+1) = 2) then 
				begin
					tela [i,j]:=obj;
				end
				// se tem diamante, parede ou outra pedra em baixo
				else if (proximoObjeto (tela, j,i+1) > 2) then 
				begin
					//se tem espaço vazio do lado, cai para o lado
					if (proximoObjeto (tela, j+1,i) = 1 ) and (proximoObjeto (tela, j+1,i+1) = 1 )then 
					begin
						tela [i,j]:=cespaco;	
						tela [i,j+1]:=obj;						
					end;
					//se tem espaço vazio do lado, cai para o lado²
					if (proximoObjeto (tela, j-1,i) = 1 ) and (proximoObjeto (tela, j-1,i+1) = 1 ) then 
					begin
						tela [i,j]:=cespaco;	
						tela [i,j-1]:=obj;						
					end
					else if (tela [i,j]=objcaindo) then
					begin
						//se não tem espaços vazios, o objCaindo volta a ser obj
						tela [i,j]:=obj; 
					end;
				end;//fim if para espaços vazios ao lado			
			end;
		end;
	end;
end;


procedure AtualizaJogo (var tela:Tmina; 
	                        dimx,dimy:integer; 
	                    var jogx,jogy:integer;
	                        movimento:char;
	                   var diamTotal, diamColet: integer; 
	                       pontos, numMovim: integer; 
	                       saidaX, saidaY: integer; 
	                   var morreu:boolean);

var xj,yj,Obj,xobj,yobj,obj2:integer;
	mineiro,pedra,pedraCaindo,diamante,diamanteCaindo:char;
begin
	mineiro:='@';
	pedra:=cPEDRA;
	pedraCaindo:=cPEDRACAINDO;
	diamante:=cDIAMANTE;	
	diamanteCaindo:=cDIAMANTECAINDO;	
	direcaoMovimento (tela,jogx,jogy,movimento,xj,yj);
	obj:=proximoObjeto (tela,xj,yj) ;
	if obj=3 then
		diamcolet:=diamcolet+1;
	if obj < 4 then
		movimentaObjeto (tela,dimx,dimy,jogx,jogy,movimento,mineiro);
	if obj = 4 then //se tem uma pedra na frente do jogador
	begin
		direcaoMovimento (tela,xj,yj,movimento,xobj,yobj);
		obj2:=proximoObjeto (tela,xobj,yobj);	
		// a pedra se move se não tem mais pedras, mas só move pra esq. e dir.
		if (obj2 = 1) and (movimento <> cima) and (movimento <> baixo)then 
		begin
			movimentaObjeto (tela,dimx,dimy,xj,yj,movimento,pedra);		
			movimentaObjeto (tela,dimx,dimy,jogx,jogy,movimento,mineiro);	
			
		end;
	end;
	CaiObjeto (tela,dimx,dimy,pedra,pedraCaindo,morreu);
	CaiObjeto (tela,dimx,dimy,DIAMANTE,DIAMANTECAINDO,morreu);
	
end;

procedure explosao (var tela:tmina; x,y,k:integer);
var i,j:integer;
begin
    case k of
    	0:for i:=y-1 to y+2 do
    			for j:=x-1 to x+2 do
    				tela[i,j]:=cESPACO;
    	1:for i:=y-1 to y+2 do
    			for j:=x-1 to x+2 do
    				tela[i,j]:='.';
    	2:for i:=y-1 to y+2 do
    			for j:=x-1 to x+2 do
    				tela[i,j]:='*';
    	3:for i:=y-1 to y+2 do
    			for j:=x-1 to x+2 do
    				tela[i,j]:='X';
    	4:for i:=y-1 to y+2 do
    			for j:=x-1 to x+2 do
    				tela[i,j]:='#';
    	5:for i:=y-1 to y+2 do
    			for j:=x-1 to x+2 do
    				tela[i,j]:='X';	
    	6:for i:=y-1 to y+2 do
    			for j:=x-1 to x+2 do
    				tela[i,j]:='*';	
    	7:for i:=y-1 to y+2 do
    			for j:=x-1 to x+2 do
    				tela[i,j]:='.';	
    	8:for i:=y-1 to y+2 do
    			for j:=x-1 to x+2 do
    				tela[i,j]:=cESPACO;
	end;
	
end;

procedure TelaVitoria;

begin
	clrscr();
	writeln ('VOCE VENCEU!');
	writeln ();
	writeln ();
	writeln ();
	writeln ();
	writeln ('Aperte "esc" para sair');
end;

Var
    tela: Tmina;
    dimX, dimY: integer; (* dimensoes da mina *)
    jogX, jogY: integer; (* coordenadas do jogador *)
    diamTotal, diamColet: integer;
    pontos, numMovim: integer;
    saidaX, saidaY: integer;
    movimento: char;
	morreu:boolean;
	i:integer;
	saiu:boolean;
Begin
    inicializaJogo(tela, dimX, dimY, jogX, jogY, diamTotal, diamColet, pontos, numMovim, saidaX, saidaY);
	clrscr();
	morreu:=false;

   writeln('Pressione ENTER para iniciar o jogo!');
   readln();
    repeat
        mostraTela(tela, dimX, dimY,diamtotal,diamcolet);
        movimento := leEntrada();
		encontraJogador (tela, dimx,dimy,jogx,jogy);
		AtualizaJogo(tela,dimx,dimy,jogx,jogy,movimento,diamTotal, diamColet, pontos, numMovim, saidaX, saidaY,morreu);   
        delay(PREGUICA); 
    until (movimento = ESC) or (morreu) or (diamcolet=diamtotal);
//    finalizaJogo();
	if morreu then
		for i:=0 to 8 do
		begin
			encontraJogador (tela, dimx,dimy,jogx,jogy);
			explosao (tela, jogx,jogy,i);
			mostraTela(tela, dimX, dimY,diamtotal,diamcolet);
      	  	delay(PREGUICA); 
		end;
	if diamcolet = diamtotal then
	begin
	tela[saiday,saidax]:=cSAIDA;
	saiu:=false;
	repeat
        mostraTela(tela, dimX, dimY,diamtotal,diamcolet);
        movimento := leEntrada();
		encontraJogador (tela, dimx,dimy,jogx,jogy);
		AtualizaJogo(tela,dimx,dimy,jogx,jogy,movimento,diamTotal, diamColet, pontos, numMovim, saidaX, saidaY,morreu);   
        delay(PREGUICA); 
		if (jogx=saidax) and (jogy=saiday) then
			saiu:=true;
    until (movimento = ESC) or (saiu);
	end;
	if (saiu) then
	begin
		repeat
			telaVitoria();	
			delay (PREGUICA);
			movimento := leEntrada();
		until (movimento = ESC);
	end;
End.
