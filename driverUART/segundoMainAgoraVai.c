/*==============main.c============*/
/*==============lsl16-thcf16============*/

#include "cMIPS.h"
#include "../include/uart_defs.h"
#include "../include/fib_vet.h"

# define SPEED 3 // choose a data rate
# define COUNTING (( SPEED+2)*100) // wait for end of transmission
#define SEQ 1024 //tamanho fila de entrada
#define SOQ 1024 //tamanho fila de saída
extern UARTdriver Ud;


int proberx ( void );    // retorna nrx
int probetx ( void );    // retorna ntx
Tstatus iostat ( void ); // retorna inteiro com status no byte menos sign .
// escreve byte menos signif no reg . de contole
void ioctl(int rts, int intTX, int intRX, int speedd); 
char Getc ( void );      // retira octeto da fila, decrementa nrx
void Putc ( char );      // insere octeto na fila, decrementa ntx
int str2int ( int tam, char *str);
int int2str(int val, char *str);
int strLen (char *str);


volatile Tserial *uart;
volatile extern int tx_has_started;



int main ( void ) {
    /*=============VARIÁVEIS=============*/
    volatile int state; // GCC must not optimize away these
    volatile int * counter;
    volatile Tstatus status;
    Tcontrol ctrl;
    char filaEntrada[SEQ], filaSaida[SOQ], c;
    //head e tails das filas de entrada e saida
    int eHead = 0, eTail = 0, sHead = 0, sTail = 0;
    // auxiliares
    int eRecebidos = 0, iniTransm = 0, numFib, tam, completeStr = 0, sim = 0;


    /*=============INICIALIZAÇÕES=============*/
    tx_has_started = 0;
    Ud.ntx = 16;
    uart = (void *) IO_UART_ADDR; // UART address ( base )
    counter = (void*) IO_COUNT_ADDR; // counter address
    //para escrever no registrador de controle usamos ioctl
    ioctl(1, 1, 1, SPEED);// uart->ctl = ctrl; // write config to control register

    /*=============LOOP PRINCIPAL=============*/
    do {
        while (!proberx() && !eRecebidos && c != EOT) // enquanto fila de recepção está vazia
            cmips_delay(1); //espera primeira recepção
        //se tem algo na fila de recepção

        if (c!= EOT) c = Getc() ;
        // lê até encontrar fim de transmissão ou quebra de linha (fim de seq. de octetos)
        while (c != EOT && c != '\n'){  
            sim = 1;        
            filaEntrada[eTail] = c;
            eTail= (eTail + 1) % SEQ;
            while (proberx() < 1 )
                cmips_delay(1);
            c = Getc();
        }
        if (c == '\n')
        {       
            completeStr++;
            filaEntrada[eTail] = c;
            eTail= (eTail + 1) % SEQ;
            eRecebidos++;
        }        
        if (filaEntrada[(eTail-1)%SEQ]=='\n' && filaEntrada[(eTail-2)%SEQ]=='\n' && c != EOT)
        {
            c = EOT;
            eTail--;
            eRecebidos--;
            completeStr--;
        }

        while (eRecebidos > 0 || (sHead - sTail) != 0 && c!= EOT)
        {

            
            if (((sHead - sTail) != 0  || iniTransm == 0) && (eTail > eHead) && completeStr)
            {

                iniTransm = 1;
                numFib = str2int (strLen(filaEntrada+(eHead > 0 ? eHead : 1)), 
                    filaEntrada+(eHead > 0 ? eHead : 1) );

                if (numFib < FIB_SZ)
                { 
                    //print(numFib);
                    numFib = fibonacci[numFib];
                }
                tam = int2str (numFib, filaSaida+sTail);
                eHead = (strLen(filaEntrada+eHead) + eHead+1) % SEQ;

            
                //incrementa a head da fila de saída
                sTail+=tam;
                completeStr--;
            }
            
            if (probetx() > 0 && ((sTail - sHead) > 0)) 
            {
                Putc(filaSaida[sHead]);
                
                if (filaSaida[sHead] == '\n')
                {
                    eRecebidos--;
                }
                //incrementa tail da fila de saída
                sHead = (sHead + 1) % SOQ;
            }


            if (c!= EOT) 
            {
                c = Getc() ;

                sim = 1;
            }
            // lê até encontrar fim de transmissão ou quebra de linha (fim de seq. de octetos)
            //print(proberx());
            if ((c != EOT) && (c != '\n') && sim)
            {
                //print(9);
                filaEntrada[eTail] = c;
                eTail= (eTail + 1) % SEQ;
                sim = 0;
            }
            else if ((c == '\n') && (c!= EOT) && sim  )
            {
                
                completeStr++;                        
                filaEntrada[eTail] = c;
                eTail= (eTail + 1) % SEQ;
                eRecebidos++;
                sim = 0;
            }

            if (filaEntrada[(eTail-1)%SEQ]=='\n' && filaEntrada[(eTail-2)%SEQ]=='\n' && c != EOT)
            {

                completeStr--;
                c = EOT;
                eTail--;
                eRecebidos--;

            }



        }


    } while ((eRecebidos>0) ||  (probetx() < 16) );

    for (int i = 0; i < (200); ++i)
    {
       cmips_delay(1);
    }






}

//escreve no reg. de controle da uart
void ioctl(int rts, int intTX, int intRX, int speed) {

  volatile Tcontrol ctrl;

    ctrl.rts = 1; // RTS =1 to wake up Remota
    ctrl.ign = 0;
    ctrl.ign2 = 0;
    ctrl.intTX = 1;
    ctrl.intRX = 1;
    ctrl.speed = speed & 0x07; // máximo 3 bits

    uart->ctl = ctrl;
} 

//retorna o estado
Tstatus iostat ( void )
{
    return (uart->stat);
}

//retorna nrx
int proberx ( void )
{
    return (Ud.nrx);
}
//retorna ntx
int probetx ( void )
{
    return (Ud.ntx);
}

char Getc ( void )
{
    char c;
    
    //desabilita interrpuções
    disableInterr ();
    //decrementa nrx
    Ud.nrx = (Ud.nrx - 1) % 16;
    //pega char na head da fila
    c = Ud.rx_q[ Ud.rx_hd ];
    //incrementa o indice da head da fila
    Ud.rx_hd = (Ud.rx_hd + 1) & 15; // %16
    //reabilita interrupções
    enableInterr();
    
    return (c);

}

void Putc ( char c)
{
      //desabilita as interrupções
      disableInterr ();
      //decrementa espaços na fila de transmissão
      Ud.ntx = (Ud.ntx -1);
      //coloca o char na tail da fila de transmissão
      Ud.tx_q [ Ud.tx_tl ] = c;
      //Incrementa a tail
      Ud.tx_tl = (Ud.tx_tl + 1) & 15;
      //habilita as interrupções de novo

      if ((Ud.ntx == 14) && (!tx_has_started))
      {
        uart->interr.setTX = 1;
      }

      
      enableInterr ();
}


int char2int (char c)
{
    if (c >= '0' && c <= '9')
        return ((int)c - 48);   
    else if (c >= 'a' && c <= 'f')
        return ((int)c - 97+10);
    else if (c >= 'A' && c <= 'F')
        return ((int)c - 65+10);
    else
        return -1;
}

int str2int ( int tam, char *str)
{
    int i;
    int saida = 0, x;
    for (i = 0; i < tam; ++i)
    {
        x = char2int(str[i]);
        //é um valor válido?
        if (x == -1) return x;
        saida = (saida << 4) + x;
    }
    return (saida);
}

char int2char (int val)
{
    val = val % 16;
    if (val < 10 ){
        return ((char)(val + 48));
    }
    else
    {
        return ((char)(val - 10 + 97));
    }
}

int int2str(int val, char *str)
{
    int size = 0;
    char s[9];
    s[8] = '\n';
    for (int i = 7; i >= 0; --i)
    {
        s[i]=int2char(val);
        val = val / 16;
    }
    for (int i = 0; i < 10; ++i)
    {
        *str = s[i];
        str++;
    }
    size = 9;
    return size;
}

int strLen (char *str)
{
    int i;
    for (i = 0; str[i]!='\n' ; ++i);

    return i;
}