# JMRI CMRI DOCUMENTS 

----



### BINARY 
```
BASE 2 
ONLY 0 OR 1 

 1024   512	256	128	64	32	16	8	4	2	1 
	1	0	0	0	0	0	0	0	0	0	0  = 1024X1 +   512X0	+	256X0	+	128X0	+	64X0	+	32X0	+	16X0	+	8X0		+	4X0	    +	2X0 	+	1X0  = 1024 
        1	0	0	0	0	0	0	0	0 	0  = 512X0  +	256X0	+	128X0	+	64X0	+	32X0	+	16X0	+	8X0		+	4X0	    +	2X0 	+	1X0  = 512
        	1	0	0	0	0	0	0	0 	0  = 256X1	+	128X0	+	64X0	+	32X0	+	16X0	+	8X0		+	4X0	    +	2X0 	+	1X0  = 256
        		1	0	0	0	0	0	0 	0  = 128X1	+	64X0	+	32X0	+	16X0	+	8X0		+	4X0	    +	2X0 	+	1X0  = 128
        			1	0	0	0	0	0 	0  = 64X1	+	32X0	+	16X0	+	8X0		+	4X0	    +	2X0 	+	1X0  = 64
        				1	0	0	0	0 	0  = 32X1	+	16X0	+	8X0		+	4X0	    +	2X0 	+	1X0  = 32
        					1	0	0	0 	0  = 16X1	+	8X0		+	4X0	    +	2X0 	+	1X0  = 16
        						1	0	0 	0  = 8X1	+	4X0	    +	2X0 	+	1X0  = 18
        							1	0 	0  = 4X1	+	2X0 	+	1X0  = 4
        								1  	0  = 2X1 	+	1X0  = 2
        									1  = 1X1  = 1 

```
### Binary addition 
```
0 + 0 = 0
0 + 1 = 1
1 + 0 = 1
1 + 1 = 0 (carry 1 to the next significant bit)
```

### Binary substration  
```
0 – 0 = 0
0 – 1 = 1, borrow 1 from the next more significant bit
1 – 0 = 1
1 – 1 = 0
```

### Binary mulitplication
```
0×0=0
1×0=0
0×1=0
1×1=1 (there is no carry or borrow for this)
````

### shif operation 
* Left shift (<<)
```
data stored, in memory, as a series of bits
or n = n*2: n = n<<1

left shift operation is shifting left is equivalent to multiplication by powers of its position 

Example 
6 stored as a 32-bit

00000000 00000000 00000000 00000110

Shifting this bit pattern to the left one position (6 << 1) would result in the number 12:

00000000 00000000 00000000 00001100

```

* Logical right shift (>>>)
```
A logical right shift is the move to bit the right

Example 
shifting the number 12:

00000000 00000000 00000000 00001100

right by one position (12 >>> 1) will get back our original 6:

00000000 00000000 00000000 00000110

```

* Arithmetic right shift (>>)
```

The arithmetic right shift is exactly like the logical right shift, except instead of padding with zero, it pads with the most significant bit. 
This is because the most significant bit is the sign bit, or the bit that distinguishes positive and negative numbers.
By padding with the most significant bit, the arithmetic right shift is sign-preserving
or 
n = n/2: n = n>>1

Example 

bit pattern as a negative number:

10000000 00000000 00000000 01100000

number -2,147,483,552. Shifting this to the right 4 positions with the arithmetic shift (-2,147,483,552 >> 4) would give us:


11111000 00000000 00000000 00000110


the number -134,217,722.

```


* Tips 
```
n = n*2: n = n<<1
n = n/2: n = n>>1
Checking if n is power of 2 (1,2,4,8,...): check !(n & (n-1))
Getting xth bit of n: n |= (1 << x)
Checking if x is even or odd: x&1 == 0 (even)
Toggle the nth bit of x: x ^ (1<<n)
```
