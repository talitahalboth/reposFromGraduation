#==========HANDLERUART.S===========#
#======== lsl16 - thcf16 ==========#

_u_rx:  lui   $k0, %hi(_uart_buff)  # get buffer's address
    ori   $k0, $k0, %lo(_uart_buff)
    
    sw    $a0, 5*4($k0)     # save registers $a0,$a1, others?
    sw    $a1, 6*4($k0)
    sw    $a2, 7*4($k0)
    sw    $a3, 8*4($k0)

    lui   $a0, %hi(HW_uart_addr)# get device's address
    ori   $a0, $a0, %lo(HW_uart_addr)

    lw    $k1, USTAT($a0)       # Read status
    sw    $k1, 0*4($k0)  

    # a0 é o endereço da UART
    # k1 é o registrador de STATUS da UART
    # k0 é o endereço do buffer da UART

    andi $a1, $k1, U_rx_irq     # Is this reception?
    beq   $a1, $zero, transmit   #   no, maybe transmission?
    nop

    # handle reception 
    
    lw    $a1, UINTER($a0)
    nop
    nop
    ori   $a1, $a1, U_rx_irq  # Ativa clrRX
    sw    $a1, UINTER($a0)

    
    lw    $a1, UDATA($a0)   # Read data from device (rxreg), UDATA = 12
    nop
    nop
    sw    $a1, 9*4($k0)     # Salva dado no buffer da UART (k0)
    andi   $k1, $k1, 223   # RXcheio = 0

    lui   $a2, %hi(Ud)      # get address for data & flag
    ori   $a2, $a2, %lo(Ud) # a2 é o endereço de Ud
    
    lw    $a3, 48($a2)      # a3 recebe nrx (posição 48 na Ud)
    nop
    nop
    slti  $a1, $a3, 16 
    beq   $a1, $zero, overrun # fila de recepção cheia? OVERRUN!
    nop
    addiu $a3, $a3, 1       # incrementa nrx
    sw    $a3, 48($a2)

    lui   $a1, %hi(rx_tl)   # a1 recebe indice da cauda
    ori   $a1, $a1, %lo(rx_tl)
    
    lw    $a3, 0($a1)
    nop
    nop
    addiu $a3, $a3, 1       # incrementa indice
    andi  $a3, $a3, 16-1    # Para mod 16 fazer and com 15
    sw    $a3, 0($a1)       # atualiza indice

    lui   $a1, %hi(rx_q)    # get queue address
    ori   $a1, $a1, %lo(rx_q)
    addu  $a1, $a1, $a3    # acrescenta no endereço da fila o indice (não precisa multiplicar por 4 pq é char, apenas 1 byte)
    #  ^ ignora overflow
    
    lw    $a3, 9*4($k0)     # a3 recebe dado do buffer
    nop
    nop
    sb    $a3, 0($a1)       # guarda o char resgatado do buffer na cauda  
 

transmit:

    andi  $a1, $k1, U_tx_irq  # Is this transmition? k1 -> status
    beq   $a1, $zero, UARTret #   no, ignore it
    nop

    # handle transmission
    
     
    lw    $a1, UINTER($a0)
    nop
    nop
    ori   $a1, $a1, U_tx_irq  # ativa clrTX
    sw    $a1, UINTER($a0)

    lui   $a2, %hi(Ud)      # get address for data & flag
    ori   $a2, $a2, %lo(Ud) # a2 é o endereço de Ud
    
    lw    $a3, 52($a2)      # a3 recebe ntx (posição 52 na Ud)
    nop
    nop
    li    $a1, 16           # número de espaços máximo
    beq   $a3, $a1, reset # fila está vazia, volta ao curso normal
    nop

    addiu $a3, $a3, 1       # incrementa ntx, um espaço a mais
    sw    $a3, 52($a2)      # atualiza na Ud

    lui   $a1, %hi(tx_q)    # a1 recebe endereço da fila
    ori   $a1, $a1, %lo(tx_q)
    lui   $a2, %hi(tx_hd)   # a2 recebe endereço do indice da cabeça da fila
    ori   $a2, $a2, %lo(tx_hd)
    
    lw    $a3, 0($a2)       # a3 recebe indice da cabeça
    nop
    nop
    addu  $a1, $a1, $a3     # a1 = tx_q[0] + tx_hd => a1 = tx_q[tx_hd]
    addiu $a3, $a3, 1       # incrementa indice da cabeça da fila
    andi  $a3, $a3, 16-1    # mod 16
    sw    $a3, 0($a2)       # atualiza indice em tx_hd
    lbu   $a3, 0($a1)       # pega o char da cabeça da fila
    sb    $a3, UDATA($a0)   # salva em txreg

    
    lui   $a1, %hi(tx_has_started)    # ativa tx_has_started
    ori   $a1, $a1, %lo(tx_has_started)
    
    lw    $a2, 0($a1)
    nop
    nop
    ori   $a2, $a2, 1
    sw    $a2, 0($a1)

    b UARTret
    nop
    

reset:

    lui   $a1, %hi(tx_has_started)    # ativa tx_has_started
    ori   $a1, $a1, %lo(tx_has_started)
    
    lw    $a2, 0($a1)
    nop
    nop
    andi   $a2, $a2, 0
    sw    $a2, 0($a1)
    b UARTret
    nop
    

status:
    b UARTret
    nop
overrun:
    b UARTret
    nop

UARTret:
    lw    $a2, 7*4($k0)
    lw    $a1, 6*4($k0)         # restore registers $a0,$a1, others?
    lw    $a0, 5*4($k0)
    lw    $a3, 8*4($k0)
