_printString PROTO
_getString PROTO
_newLine PROTO

extrn ExitProcess : proc; defining the exit process
extrn CreateFileA : proc	; A = ANSI
extern WriteFile: proc
extrn ReadFile : proc
extrn CloseHandle : proc

.data

msg1 byte "e",0; testing
msg2 byte "assembly",0



;File data
num QWORD 100
inputFile BYTE "input.txt",0
outputFile BYTE "output.txt",0
charBuffer byte 100 DUP (0)
charBufferTEMP byte 100 DUP (0)

;return data
FD QWORD ?
read QWORD ?
charsRead QWORD 0
charsWrote QWORD 0
button QWORD ?
closed QWORD ?

.code
_asmMain PROC

	push rbp
	sub rsp, 10h				; reserve for return and rbp
	sub rsp, 18h				; reserve for parameters
	sub rsp, 20h				; reserve shadow space for regs
	lea rbp, [rsp + 20h]		; align stack pointer

	;Opening input file by Abbi G
	;adapted from https://github.com/brianrhall/Assembly/blob/master/Chapter_10/Program%2010.8/Program_10.8_Windows_MASM.asm
	lea rcx, inputFile					; address of file name
	mov rdx, 80000000h					; constant for GENERIC_READ
	xor r8, r8							; 0 share mode
	xor r9, r9							; 0 security
	mov QWORD PTR [rsp+48h-28h], 3		; reverse order, 3 open existing
	mov QWORD PTR [rsp+48h-20h], 80h	; flags FILE_ATTRIBUTE_NORMAL
	mov QWORD PTR [rsp+48h-18h], 0		; 0 template
	call CreateFileA
	mov FD, rax							; save handle

	;reading from input file
	mov rcx, FD							; pass FD
	lea rdx, charBuffer					; pass address of buffer
	mov r8, num							; pass buffer size
	lea r9, charsRead					; pass address of charsRead
	mov QWORD PTR [rsp+48h-28h], 0		; 0 overlap
	call ReadFile
	mov read, rax						; save characters read

	mov rcx, FD					; pass handle
	call CloseHandle			; close file handle
	mov closed, rax				; save status
	xor rax, rax


	lea rcx, charBuffer
	call _printString

	call _newLine

	call _iterateBuffer

	lea rcx, charBuffer
	call _printString


	;Opening output file by Abbi G, 
	;adapted from https://github.com/brianrhall/Assembly/blob/master/Chapter_10/Program%2010.8/Program_10.8_Windows_MASM.asm
	lea rcx, outputFile					; address of file name
	mov rdx, 40000000h					; constant for GENERIC_WRITE
	xor r8, r8							; 0 share mode
	xor r9, r9							; 0 security
	mov QWORD PTR [rsp+48h-28h], 3		; reverse order, 3 open existing
	mov QWORD PTR [rsp+48h-20h], 80h	; flags FILE_ATTRIBUTE_NORMAL
	mov QWORD PTR [rsp+48h-18h], 0		; 0 template
	call CreateFileA
	mov FD, rax							; save handle

	; writing the buffer to the file
	mov rcx, FD							; pass FD
	lea rdx, charBuffer					; pass address of buffer
	mov r8, charsRead
	lea r9, charsWrote					; pass address of charsRead
	mov QWORD PTR [rsp+48h-28h], 0		; 0 overlap
	call WriteFile

	mov rcx, FD					; pass handle
	call CloseHandle			; close file handle
	mov closed, rax				; save status


	lea rsp, [rbp];				stack eplilogue code
	pop rbp
	xor rcx,rcx
	call ExitProcess; starting the exit process

_asmMain ENDP; ending main


_hashChar PROC;		this function takes a char and converts it to an index of an array of 8 elements

	xor rdx, rdx;		clearing remainder register
	mov rax, [rcx];		moving the divitend to the rax register
	mov rcx, 1;			moving the divisor to the rcx register
	div rcx;			dividing char by 8

	ret
_hashChar ENDP; ending hashing function


_iterateBuffer PROC;	by Abbi G: iterate through charBuffer to convert all letters to uppercse
	
	mov rbx, charsRead
	lea rsi, offset charBuffer
	xor rdi,rdi
	xor rax, rax

	;loops through every character
	bufferItr:
		mov cl, [rsi+rdi*1]
		and cl, 0DFh				;to uppercase mask

		;jump to spacetoJ if the character is a space
		cmp cl, 0h
		JE spaceToJ

		;jump to bad if below 65 or above 90 (outside uppercase character range)
		cmp cl, 65
		JB bad
		cmp cl, 90
		JA bad
		jmp good

		bad:
		inc rax		;counting skipped characters
		jmp fin

		spaceToJ:
		mov cl, 4Ah

		good:
		sub rdi, rax		;adjusting for skipped characters with rax
		mov [rsi+rdi], cl
		add rdi, rax
		fin:

		inc rdi			;incrementing loop
		cmp rdi, rbx
		jne bufferItr


	sub rdi, rax
	clearJunk:				;clearing junk that piles up when a character is skipped T??E~~ST would equal TEST
		mov cl, 20h
		mov [rsi+rdi], cl
		inc rdi
		
		cmp rdi, rbx
		jne clearJunk	

	sub charsRead, rax		;adjust chars read to new size
	ret
_iterateBuffer ENDP;

END; ending the program