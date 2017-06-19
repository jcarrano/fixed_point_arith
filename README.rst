===============================
Fixed Point Arithmetic Routines
===============================

Introduction
------------

This library implements fixed point arithmetic in C, along with vectors and 
quaternions. The format for fixed point is the "Q format". 

Check out the Doxyren reference at https://jcarrano.github.io/fixed_point_arith/

Acknowledgements
----------------

Most of this code was written between March and July 2013 by Juan I. Carrano,
with contributions from Andrés Calcabrini, Juan I. Ubeira and Nicolás Venturo.

Fractional (fixed point) numbers and Q format
---------------------------------------------

Fixed point binary numbers are able to represent numbers of the form

::

             N-1
        x = ± Σ a(i)*2**(i+r)
             i=0

Where r is generally less than 0. The a(i)'s are either 0 or 1.

One possibility for a computer representation would be to form a binary 
number out of the a(i)'s plus a sign bit. A better alternative is to use 
two's complement. 

For all N bits binary numbers with bits ```b(N-1) ... b2 b1 b0``` and two
constants **p** and **q**, such that ```p+q = N```, the Qp.q format tells us
how to interpret those bits to find out which number ther represent. Note the
distinction between the binary number itself and the value which it represents.
For example, if we have a 32 bit value we can think of it as a signed integer,
unsigned integer, a IEEE floating point number or just a bit mask.

The Qp.q format can be defined in terms of the two's complement representation
of the number, which we call **B**. Then, in the Qp.q format, the value is
```B/(2**q)```. We can see that **p** and **q** have an interpretation: **q**
is the number of fractional bits and **p** of integer bits (plus the 'sign' bit).

Signed integers can be seen as a special case of Q numbers: ```QN.0```.

Fixed point representations have some advantages over floating point:

- The resolution is constant.
- Many CPUs, especially microcontrollers, do not have hardware floating point
  support. Soft fixed point is much faster than soft floats.
- The addition and substraction operations are *exactly the same* as for integers.
- If the format can only represent values in the range (-1,1), the the product
  of two such numbers will always be in-range.

Operations on fixed point numbers
---------------------------------

The C programming language does not natively support fractional types. Thus,
we must define fractional operations in terms of integer operations. Earlier
we mentioned that we could use an integer B to represent a value of B/(2**q).
Note, however, that from the compiler's perspective, this object will always
be an integer. It will behave as a fractional type only if we apply fractional
operations to it.

Addition
	

Substracion
	The same as addition

Product (fractional by fractional -> fractional)

Product (fractional by integer -> integer)
	

Quotient
	dfsdf
	
	The quotient operations is not implemented in this library at the moment.

Quaternions
-----------



References
----------


