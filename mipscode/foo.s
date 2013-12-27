.data
str: .asciiz "fail\n"

.text

# _start is the entry point into any program.
.global _start
.ent    _start 
_start:

#
#  The header ends here, and code goes below
#

# print a string.  (note the %lo syntax only works if the string is
# in the lower 32KB of memory, which it always will be for us)
	     lui     $8, 0x0000
	     ori     $8, $8, 0x0100
	     addiu   $9, $0, 1
	     sw      $9, 0($8)
	     addiu   $9, $0, 2
	     sw      $9, 4($8)
	     addiu   $9, $0, -2
	     sw      $9, 8($8)
	     lw      $10, 4($8)
	     lw      $11, 8($8)
	     #bne	 $11, $10, fail
	     mult    $11, $10
	     mfhi	 $12
	     mflo	 $9
	     addiu	 $11, $0, -1
	     bne 	 $12, $11, fail
	     addiu	 $11, $0, -4
	     bne 	 $9, $11, fail
	     j		 done

# exit the simulation (v0 = 10, syscall)
fail:
	ori   $a0, %lo(str)
	ori   $v0, $zero, 4
	syscall

done:
	ori   $v0, $zero, 10
	syscall

.end _start
