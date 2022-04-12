; TRABALHO PRATICO - CODIGO XXXX
; Aluno 1: Rafael Alves
; Aluno 2: Abílio Costa

.8086
.model small
.stack 2048

dseg segment para public 'data'
	; VARIAVEIS...
	alt byte 5
	larg byte 7
	lin byte 2
	col byte 3
dseg ends

cseg segment para public 'code'
     assume cs:cseg, ds:dseg
main proc
     mov ax, dseg
     mov ds, ax
     mov ax, 0B800h
     mov es, ax
	 
	 xor di, di
	 xor si, si
	 xor ax, ax
	 xor dx, dx
	 
     ; CODIGO...
	 ;conta das linhas e colunas
	 mov al, lin
	 mov bl, 160
	 mul bl
	 mov di, ax
	 mov al, col
	 mov bl, 2
	 mul bl
	 add di, ax
	 
	 ;guardar para primeira linha, segunda coluna
	 mov si, di
	 
	 ;testa impar
	 mov al, alt
	 mov bl, 2
	 div bl
	 cmp ah,0
	 je fim
	 mov al, larg
	 mov bl, 2
	 div bl
	 cmp ah,0
	 je fim
	 
	 xor ax, ax
	 xor bx, bx

	 ;metade da largura
	 mov al, larg
	 dec al  ;para dividir com num. par
	 mov bl, 2
	 div bl
	 mov dl, al

	 ;atributos
	 mov ah, '+'
	 mov al, 01110000b
	 
	 mov cl, larg
	 ;dec cl

primeira_linha:
     mov es:[di], ah
     mov es:[di+1], ah
     add di, 2
     loop primeira_linha
     mov cl, alt
     dec cl
     sub di, 8
primeira_coluna:
     mov es:[di], ah
     mov es:[di+1], ah
     add di, 160
     loop primeira_coluna
     mov cl, alt
     dec cl
     sub di, 6
ultima_linha:
     mov es:[di], ah
     mov es:[di+1], ah
     add di, 2
     loop ultima_linha
fim:
     mov ah, 4ch
     int 21h
main endp
cseg ends

end main