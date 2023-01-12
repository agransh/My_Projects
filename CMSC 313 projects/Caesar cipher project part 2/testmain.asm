;Name: Agransh Srivastava, Matthew Yu
;Filename: Yu_srivastava_project4.asm
;User ID: asrivas1@umbc.edu, myu2@umbc.edu
;Class: CMSC 313
;Professor: Ivan Sekyonda
;Date: 7/18/2022
;Desciption: this program has a menu option that performs multiple operations such as taking aa string, encrypting it, decrypting it, using ceasar cipher and other logic
extern display
extern edit
extern scanf
extern printf
extern decipher

	
	section .data
titlemessage	db	"Encryption menu options: ", 10
t_len		equ	$-titlemessage

op1		db	"s- show current message",10
op1_len		equ	$-op1

op2             db      "r- read new message",10
op2_len         equ     $-op2

op3             db      "c- caesar cipher",10
op3_len         equ     $-op3

op4             db      "f- frequency decrypt",10
op4_len         equ     $-op4

op5             db      "q- quit program",10
op5_len         equ     $-op5

input           db   	 "Enter option letter: ",10
in_len         	equ     $-input

num_r           db      "Enter a shift value: ",20
len_r           equ     $-num_r

err             db      "Error please try again",10
len_e           equ     $-err

encr            db      "Encryption: ",9
encr_len        equ     $-encr

err2		db	"Invalid option! Try again!",10
len_e2		equ	$-err2

intB		dd	0

intC		dd	0

num 		dd 	230
msg 		db 	"Enter a string: " , 0
msg2 		db 	"Enter an index between 0 and 9: ", 0
orgmsg          db      "This is the orignial message", 10, 0
fmtS 		db 	"%d", 0
new_line	db	10
	section .bss
temp		resb	2
arr		resq 	10
string_buff	resb	255
num_buff	resb 	3
char_buff	resb	1
stringB		resd	255
numI		resd	1			;this reserves space for an integer
	section .text
	global main
main:
	mov 	r9, 0				;moves 0 into 49 to initialize it
	call	arrlabel			;calls testlabel which makes the array
	jmp 	menu				;jmp to menu call
arrlabel:
 	mov     qword[arr+r9], orgmsg		;putting the original messaage in every single index here
        add     r9 , 8				;moves the pointer to the next index
        cmp     r9, 80				;runs the pointer for 10 spots
        jl      arrlabel			;loops back again to test label if less
	ret
menu:	
	mov     rax, 1				;prints out the title message
        mov     rdi, 1				
        mov     rsi, titlemessage
        mov     rdx, t_len
        syscall
	
 	mov     rax, 1				;prints out the first option
        mov     rdi, 1
        mov     rsi, op1
        mov     rdx, op1_len
        syscall

        mov     rax, 1				;prints out the second option
        mov     rdi, 1
        mov     rsi, op2
        mov     rdx, op2_len
        syscall

        mov     rax, 1				;prints out the third option
        mov     rdi, 1
        mov     rsi, op3
        mov     rdx, op3_len
        syscall

        mov     rax, 1				;prints out the fourth option
        mov     rdi, 1
        mov     rsi, op4
        mov     rdx, op4_len
        syscall

        mov     rax, 1				;prints out the fifth option
        mov     rdi, 1
        mov     rsi, op5
        mov     rdx, op5_len
        syscall

        mov     rax, 1				;prints out the message asking user to put in a character
        mov     rdi, 1
        mov     rsi, input
        mov     rdx, in_len
        syscall

        mov     rax, 0				;stores that letter the user chose in char buff
        mov     rdi, 0
        mov     rsi, char_buff
        mov     rdx, 2
        syscall
	
	mov 	r8b, [char_buff]		;gets that letter from the buffer and stores it into r8b
	cmp	r8b, 's'			;here we check if the user put in s or S
	jz  	show				;which jumps to show if the user did choose that
	cmp	r8, 'S'
	jz	show
	
	cmp     r8b, 'r'			;here we check if the user chose in r or R
        jz      read				;ju,ps to the read label if the user did that
        cmp     r8b, 'R'
        jz      read

  	cmp     r8b, 'c'			;here the code checks if the user puts in a c or a C			
        jz      caesar				;jumps to ceaser if so
        cmp     r8b, 'C'
        jz      caesar
	
	cmp     r8b, 'f'			;here the code checks if the user put in f
        jz      decrypt				;jumps to the decrypt label if so
        cmp     r8b, 'F'
        jz      decrypt	

	cmp 	r8b,'q'				;here the code checks if the user put in q or q
	jz	exit				;exits the program if so
	cmp	r8b,'Q'
	jz	exit
 	
	mov     rax, 1                          ;prints out the error message in case the user inputs in a wrong choice
        mov     rdi, 1
        mov     rsi, err2
        mov     rdx, len_e2
        syscall

	jmp 	menu


show:						;here are the different labels that call each funciton seperately
	call 	showmsg				;here we call showmsg
	jmp 	menu				;jump to menu after we are done so that the program can keep looping
read:
	call readmsg				;here we call readmsg
	jmp menu				;jumps to menu when done
caesar:
	call encrypt				;here we call encrypt
	jmp menu
decrypt:
	call dcr				;here we call dcr which is the decipher function
	jmp menu
	
readmsg:					;this is our read function
	mov	rdi, msg			;here we store msg which asks the user to enter ni a string into rdi
	xor	rax, rax			;here we move in 0 into rax to empty it out
	call	printf				;print out the statement from above

	xor	rdi, rdi
	mov	rdi, arr			;here we move the array address into rdi
	xor	rsi, rsi			;we xor rsi to clear out rsi
	mov	rsi, intB			;we then pass the integer buffer in here
	call	edit				;call the edit function here from our C file
	ret					;retrun to the read label

showmsg:
	mov     rdi , arr			;here we move the array into rdi
	call    display				;call teh display funciton in C
	ret					;return to show label

encrypt:
	mov     rdi, msg2			;moving the other message into rdi here where we ask the user to put in an index number they want to encrypt
        xor     rax, rax			;clearing rax
        call    printf				;printing out the above statement to theuser

        mov     rdi, fmtS			;we use scanf here and store teh number that the user gave us into num I
        mov     rsi, numI
        xor     rax, rax
        call    scanf

						
	mov     r10, arr			;here we move the array into r10 to loop through it
        mov     rcx, 0				;counter to keep track of the index that the code is on 
        sub     r10, 8				;this line ensure that the code will start at the 0th index
	dec 	rcx 				;decreases counter before entering so that the counter starts at 0
        looper2:
                add     r10, 8			;increments it to the next index since one index is 8 bits long
                inc     rcx			;increments the counter 
                cmp     rcx, [numI]		;this ensures that the code loops until the index that the user wants to be put in the code
                jl      looper2			;loops back to looper again if lesss
		

                mov     r11, r10		;moves the address of the array into r11

	mov     rax,1                   	;prints out the message for asking user for the shift value
        mov     rdi,1
        mov     rsi,num_r
        mov     rdx,len_r
        syscall


        mov     rax,0                   	;stores in the shift value here
        mov     rdi,0
        mov     rsi,num_buff
        mov     rdx,3
	syscall
			
	cmp     rax,2                   	;comparing if the length of the number is 2 digits
        jne     threecharcheck
        sub     byte [num_buff], 48

        jmp for_loop


	threecharcheck:
        	cmp     rax,2                   ;checks to see if the numbers are three characters
        	jnz     error_func              ;goes to error if more than 3
        	mov     r14, num_buff           ;stores the shift into r10
        	inc     r14                     ;increases r10 by 1 to get the first digit
        	cmp     byte[num_buff],45       ;checks if the number entered is a negative since ascii for '-' is 45
        	je      error_func              ;jumps to error
        	sub     byte[num_buff],48       ;subtracts 48 from the first digit
        	sub     byte[r14],48            ;subtracts 48 from the second digit
        	mov     al,10                   ;this part stores in double digits
        	mov     bl,[num_buff]
        	mul     bl                      ;we think the error is in the for loop either when we move r7b into the for loop or add r8b to the letter
        	add     al, [r14]
        	cmp     al,25
        	jg      error_func
        	jmp     for_loop

	for_loop:
        	mov     r9, r11			;stores the string into r9
        	dec     r9                      ;decrements r9 because it starts at the first letter  otherwise
        	mov     r13b,al
        	shift:                          ;shift by key  for the letters
                	inc r9                  ;incrementing r9
                	cmp byte[r9],0	        ;this makes sure that the loop runs until the end of the string by comparing it to 0. Pretty sure this is where the code segfaults according to gdb we dont know why
                	je printmsg             ;if true then we print
                	check_punc:
                        	cmp     byte[r9], 'A'   ;checks if the first byte is an A
                        	jl      shift           ;if it is less than an A then we go back to shift

                        	cmp     byte[r9], 'z'   ;checks if the first bytw is z
                        	jg      shift           ;if greater than z then we go back to shift
                        	cmp     byte[r9], 'Z'   ;checks if first byte is Z
                        	jg      check_lower     ;if greater than z then we go to check_lower
                	add byte[r9],r13b                ;shifts a character in the string by the numbuff
 	              	wrap_upper:
                        	cmp     byte[r9], 'Z'   ;wraps in case code hits upper case Z
                        	jg      subtract        ;calls subtract if its greater in order to wrap

                	jmp shift                       ;loops back to shift

	subtract:
        	sub     byte[r9],26                     ;subtracts 26 from Z or z to bring it back to either A or a
        	jmp     shift                           ;jumps to shift again to go back into the loop
	check_lower:
        	cmp     byte[r9],'a'                    ;compares the byte to lowercase a
        	jl      shift                           ;if its less than lowercase a then we go back to shift since its a special character
        	add     byte[r9],r13b                    ;add the shifter to the byte to encrypt
        	check_wrap:
                	cmp     byte[r9],'z'            ;checks if we hit z
                	jg      subtract                ;subtracts 26 to go back to a
        	jmp     shift

	error_func:
        	mov rax, 1                              ;prints out the error message if the user ever hit error in the code
        	mov rdi, 1
        	mov rsi, err
        	mov rdx, len_e
        	syscall
        	jmp exit                                ;jumps to exit to end code
	printmsg:
        	mov     rax, 1                          ;prints out the encryption message
        	mov     rdi, 1
  	     	mov     rsi, encr
        	mov     rdx, encr_len
    	   	syscall

        	mov     rax, 1                          ;prints out the encrypted string of letters
        	mov     rdi, 1
        	mov     rsi, r11
  	     	mov     rdx, 20
        	syscall
	
	ret
	

dcr:					
	mov     rdi, msg2				;moves in the message to ask user for the index	
        xor     rax, rax
        call    printf					;prints out the message here

        mov     rdi, fmtS				;here we store in that number into numI using scanf
        mov     rsi, numI
        xor     rax, rax
        call    scanf
	

        mov     rdi, arr				;move in the array into rdi 
        xor     rsi, rsi				;clear rsi
        mov     rsi, [numI]				;here we move in the index value inside rsi
        call    decipher				;we call decipher here
        ret						;returns to menu




	mov  	rax, 1					;this creates a newline in the code for organization purposes
        mov     rdi, 1
        mov     rsi, new_line
        mov     rdx,1
        syscall


exit:
	mov	rax, 60					;exits code here
	xor 	rdi,rdi
	syscall
