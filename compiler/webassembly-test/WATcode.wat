.data
x: .word 0
y: .word 0
z: .word 0
k: .word 0
NewLine: .asciiz "\n"
.text
.globl main
main:
# -----------------------
#----------assign x:4
 
lui $a0, 0
ori $a0, $a0, 4
la $t0, x
sw $a0, 0($t0)
#---------- 
#----------assign y:5
 
lui $a0, 0
ori $a0, $a0, 5
la $t0, y
sw $a0, 0($t0)
#---------- 
#----------assign k:1
 
lui $a0, 0
ori $a0, $a0, 1
la $t0, k
sw $a0, 0($t0)
#---------- 
#----------assign z:14
 
lui $a0, 0
ori $a0, $a0, 14
la $t0, z
sw $a0, 0($t0)
#---------- 
#----------assign x:19
 
lui $a0, 0
ori $a0, $a0, 19
la $t0, x
sw $a0, 0($t0)
#---------- 
# output x 
la $t0, x
lw $a0, 0($t0)
li $v0, 1
syscall
#-------- Print New Line
la $a0, NewLine
li $v0, 4
syscall
#-----------------------
# output z 
la $t0, z
lw $a0, 0($t0)
li $v0, 1
syscall
#-------- Print New Line
la $a0, NewLine
li $v0, 4
syscall
#-----------------------
# output k 
la $t0, k
lw $a0, 0($t0)
li $v0, 1
syscall
#-------- Print New Line
la $a0, NewLine
li $v0, 4
syscall
#-----------------------
li $v0, 10
syscall
# ----------------------- End of Main.
