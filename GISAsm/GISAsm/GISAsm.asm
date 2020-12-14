.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	ExitProcess PROTO :DWORD

	includelib ../Debug/GISLib.lib
	writes PROTO :DWORD
	writed PROTO :DWORD
	comp PROTO :DWORD, :DWORD
	expn PROTO :DWORD, :DWORD
	kvadro PROTO :DWORD, :DWORD
	sum PROTO :DWORD, :DWORD

.stack 4096
.const
	literal0 DWORD 2
	literal1 DWORD 3
	literal2 DWORD 1
	literal3 DWORD 2
	literal4 BYTE "hi", 0
	literal5 BYTE "poit", 0
	literal6 BYTE 'a', 0
	literal7 DWORD 1
	literal8 BYTE "FitFit123", 0
	literal9 DWORD 3
	literal10 DWORD 3
	literal11 DWORD 0
.data
	zkek0 DWORD ?
	tkek0 DWORD ?
	skek0 DWORD ?
	xhea DWORD ?
	yhea DWORD ?
	zhea DWORD ?
	sahea DWORD ?
	sbhea DWORD ?
	shea DWORD ?
	fhea DWORD ?

.code
keke PROC ykek0:DWORD, xkek0:DWORD
push xkek0
push literal0
call expn
push eax
pop zkek0

push ykek0
push literal1
call kvadro
push eax
pop tkek0

push xkek0
push zkek0
push tkek0
pop eax
pop ebx
add eax, ebx
push eax
pop eax
pop ebx
mul ebx
push eax
pop skek0

	mov eax, skek0
	ret
keke ENDP

main PROC
push literal2
pop xhea

push literal3
pop yhea

push xhea
push yhea
call keke
push eax
pop zhea

	push zhea
	call writed
push offset literal4
pop sahea

push offset literal5
pop sbhea

push offset literal6
pop shea

push sbhea
push sahea
call comp
push eax
pop fhea

mov eax, fhea
cmp eax, literal7
jl right1
jl wrong1
right1:
	push sahea
	call writes
jmp fin1
wrong1:
	push shea
	call writes
fin1:
	push offset literal8
	call writes
push literal9
push literal10
call sum
push eax
pop zhea

	push zhea
	call writed
push 0
call ExitProcess
main ENDP
end main
