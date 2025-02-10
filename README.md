[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7OnrSidT)


# Lab 3 Exercises and Questions

This lab includes both the programming assignments and the Gradescope questions (which also appear on Gradescope). They are presented together because the questions are often related to the programming.. You can put the answers on Gradescope as you go, or keep track of the answers and add them there later. Boxes labeled &ldquo;Question&rdquo; are answered on Gradescope. Boxes labeled &ldquo;Program&rdquo; describe a program to be written, tested, committed, and submitted using GitHub Classroom. They have tests in the `Makefile` as with Lab 2.


## Linux system information

The command `uname` tells you some information about your Linux system. Look at the manual page for it.

> Question 1. What is the command, including any options, for finding out what the CPU architecture of the system is? (note: the option should be considered &ldquo;portable&rdquo;, which means you can expect it to work on different kinds of systems.)
> 


> Question 2. What is the output of that command on your system?
> 


## Printing memory addresses

For printing memory addresses, it&rsquo;s helpful to show them with a consistent format. As it turns out, our most common systems have memory addresses that are 64 bits long, but the actual virtual addresses only use 48 bits. So we can print out 48 bits for convenience, and show them in hexadecimal.

> Program 1. Write a C program called `print-addresses` that prints out a memory address formatted so that all 48 bits are shown in hexadecimal, with a prefix of &ldquo;0x&rdquo; so we know they are in hex, with upper case for letters. Your program should loop over all the numbers given on the command line. The arguments will be given as decimal numbers. (You may need to refer to manual pages to find some helpful information.)
> 

> Question 3. In Lab 2 we used the function `strtol` to convert string arguments to numbers. Can `strtol` provide the size of numbers we need in this lab? Briefly explain.
> 


## Masking bits, part 1

We can use bitwise operations to &ldquo;mask off&rdquo; or select certain bits in a value. For example, the hex number `0xFF` (binary `11111111`) has all eight bits set in the lowest byte, which the decimal value 255. If we AND that with a number bigger than 255 (as in the expression 343427 & 0xFF, the only 1 bits we get out are in the lowest byte. (Try writing out an example in binary to see how it works.) Note that each digit of a hex number corresponds to 4 bits in binary.

It turns out that `strtol` conveniently handles parsing a hex number for you. If you look at the test data in the Makefile, you&rsquo;ll see that we take advantage of that. 

> Program 2. Write a C program called `print-low` that prints the low-order 8 bits for each number on the command line, one result per line. Each line should have the following items separated by one space:
> 
> -   number of the command-line argument, starting at 1
> -   hex value first (using upper case and a `0x` prefix) of the low-order 8 bits
> -   decimal value of the low-order 8 bits
> 
> Choose a field width for each column that is big enough to contain any possible value of the result, and not any bigger.
> 
> For example, an output line for `./print-low 15` would look like:
> 
> `1 0x0F 15`
> 

Sometimes hexadecimal numbers are written with either upper case or lower case letters `A` to `F`. In this class, for hex constants we will use upper case for any literal numbers we write. If you get any negative numbers, think about why that might be!

Also note that our friend `strtol` can parse either decimal or hex numbers on the command line if the `base` argument to it is `0`.


## Masking bits, part 2

Now suppose we wanted to get the byte value of the next lower byte. For convenience, we&rsquo;ll call the lowest one byte 0 and the next one byte 1.

Try the following experiment: copy your `print-low.c` code to a new file call `print-byte1.c`. Modify it to run it with a mask to extract byte 1 and try it out. 

If you run your new program with an argument of (say) 432, you might notice that the output is bigger than a byte (that is, it has more than two hex digits). Fortunately, C gives us a way to shift the bits with a value up or down. To shift the upper byte of a value down to the lower byte, you can write `x >> 8`. Shifting up is `<<`, and you can shift by any number of bits you want by changing the `8`.

> Program 3. Modify `print-byte1` to print the shifted hex value of byte 1, without any extra bits.
> 

> Question 4. If you shift an integer value one bit to the left, what is the effect on the numerical value of the integer?
> 


> Question 5. How did you figure out the answer to the previous question?
> 


## Looking at addresses

Using pointers and the `&` operator to get addresses, we can look at where various things get laid out in memory.

> Program 4. Write a C program called `list-addresses` that prints out 48-bit addresses (in hex) for the following kinds of things on your system. Each address should be printed in the format `label: value` with the labels given below.
> 
> -   address of a variable on the stack (label: &ldquo;stack variable&rdquo;)
> -   address of a string that is allocated as a constant in your program (&ldquo;initialized data&rdquo;)
> -   address of a variable that is allocated as uninitialized data in your program (for example, a variable declared like `int x` in your code outside of any function. (&ldquo;uninitialized data&rdquo;)
> -   address of `main` (&ldquo;main&rdquo;)
> -   define another function and get its address (&ldquo;function&rdquo;)
> 

> Question 6. In the box here, paste the output of your program. This is not autograded becaused the exact addresses may vary.
> 


> Question 7. Do the values you get roughly match the kind of memory layouts we looked at in class? Explain.
> 


> Question 8. Can you match up the areas in memory as shown by the `nm` program with the addresses you printed and where you expect them to be?
> 


> Question 9. What do you notice about the relationships among the different addresses?
> 


## Trying out the debugger

In class, we mentioned that trying to use a NULL pointer, which has the value 0, can crash a program. Let&rsquo;s see that in action.

Read over the program in `crash.c`.

You can see that it directly tries to dereference a NULL pointer in the second `printf` of the `crash` function. Try to compile and run it. What happens?

The message &ldquo;Segmentation fault&rdquo; means a memory reference error, almost always a null pointer reference. We can find out more using a debugger.

First, we have to tell the system to give a memory dump (or &ldquo;core dump&rdquo;) when the crash happens. The shell command `ulimit` helps us with that. It&rsquo;s a built-in command for the shell, so look at the `bash` manual page and search for `ulimit`. It will tell you the option to set the maximum size of a core dump file

> Question 10. What is the command you used to enable core dumps?
> 


Now run the `crash` program again. The message should now be &ldquo;Segmentation fault (core dumped)&rdquo;. The core dump is put in a file called `core`. Look at it with `ls` to see how bit it is.

Now run GDB, the GNU Debugger, like this (if you used a different name for the executable, use that instead):

    gdb crash core

First `gdb` prints some introductory information and then some details of our program. It probably says something &ldquo;Program terminated with signal SIGSEGV, Segmentation fault.&rdquo; and gives us a command prompt.

Try the command `where`.

Does it tell you which function was running when the program crashed?

We&rsquo;d like to get some more information about what was going on, but `gdb` told us that &ldquo;(No debugging symbols found in crash)&rdquo;. Having the symbols is very helpful for debugging, so let&rsquo;s go put them in. Quit `gdb` with the command `quit` or just `q`.

Now compile `crash.c` again with the `-g` flag, which means to add symbol information. Something like this:

    gcc -g -o crash crash.c

Start `gdb` again the same way.

Wow, now it&rsquo;s already telling us a lot more. The problem is on line 7, with the call to `printf`. The code looks OK, and the only variable reference in it is the `*x`.

Print the value `x` with `print x`. Yes, it&rsquo;s a NULL pointer reference!

There&rsquo;s a quick fix using the argument to the crash function. Can you see what it is, and fix the error?

> Question 11. What change did you make in the program? Why did it work?
> 


## Stack direction

> Question 12. Suppose a data item A is pushed onto the stack, and then a data item B is pushed onto the stack.
> When we say the stack &ldquo;grows down&rdquo;, which of the following is true:
> 
> -   [ ] Address of A is greater than the address of B
> -   [ ] Address of A is less than the address of B
> -   [ ] The addresses are the same
> -   [ ] You can&rsquo;t compare the addresses
> 


## Memory allocation

> Question 13. What is the most common function to call for allocating memory on the heap?
> 


> Question 14. If you ask malloc for an odd number of bytes, would you expect the resulting pointer value to be:
> 
> -   [ ] Unaligned
> -   [ ] Aligned
> -   [ ] From the stack area
> -   [ ] Random
> 


> Question 15. Suppose you ask malloc for N bytes, and then a subsequent call asks to get M bytes. Would you expect malloc to return a pointer to the byte right after the end of the first N bytes?
> 


> Question 16. In a virtual memory system, does a process know the physical addresses in memory it is using?
> 
> -   [ ] Yes
> -   [ ] No
> -   [ ] It can find out using the getphysaddr() system call
> 


> Question 17. In a multi-process, virtual memory system like Linux, can two processes use the same virtual addresses at the same time without interfering with each other, or at least coordinating their memory use?
> 
> -   [ ] Yes
> -   [ ] No
> 


> Question 18. In a multi-process, virtual memory system like Linux, can two processes use the same physical addresses at the same time without interfering with each other, or at least coordinating their memory use?
> 
> -   [ ] Yes
> -   [ ] No
> 


> Question 19. Explain the basic function of a memory cache in modern computer systems
> 


> Question 20. What are some good reasons for computer systems to use virtual memory?
> 


> Question 21. The system call sbrk() is used on Linux mostly by:
> 
> -   [ ] Programmers greedy for more memory
> -   [ ] Allocating  memory for a stack frame in a function call
> -   [ ] Memory allocators available as libraries, like malloc
> -   [ ] Programs that don&rsquo;t use very much memory
> 


## Sizes of numbers in memory

We have mentioned in class that different numeric types may be represented with different numbers of bits. Let&rsquo;s find out how big each kind is. C has an operator `sizeof` that tells us the size in bytes of a data type. For example, `sizeof(int)` tells us how big an integer is.

We&rsquo;ll focus here on integer types and pointers, since that&rsquo;s mostly what we talk about in this class.

An interesting point is that the C standard specifies minimum sizes for integer types, but not exactly what they are or how big they might be. The only guarantees are that `long long` is not smaller than `long`, `long` is not smaller than `int`, and `int` is not smaller than `short.`

The GNU C library, which is the C library implementation used on Linux systems, defines signed and unsigned integer types of specific sizes in the header file `stdint.h`. They are:

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-right" />

<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-right">Number of bits</th>
<th scope="col" class="org-left">Signed</th>
<th scope="col" class="org-left">Unsigned</th>
</tr>
</thead>
<tbody>
<tr>
<td class="org-right">8</td>
<td class="org-left"><code>int8_t</code></td>
<td class="org-left"><code>uint8_t</code></td>
</tr>

<tr>
<td class="org-right">16</td>
<td class="org-left"><code>int16_t</code></td>
<td class="org-left"><code>uint16_t</code></td>
</tr>

<tr>
<td class="org-right">32</td>
<td class="org-left"><code>int32_t</code></td>
<td class="org-left"><code>uint32_t</code></td>
</tr>

<tr>
<td class="org-right">32</td>
<td class="org-left"><code>int64_t</code></td>
<td class="org-left"><code>uint64_t</code></td>
</tr>
</tbody>
</table>

We use these sometimes when we want to be very precise about the integer type we want, and how many bytes it should be. For example, it&rsquo;s usually better to use `uint8_t` for a unsigned byte value than `char` because `char` might not be treated as an unsigned 8-bit value. On the other hand, you may come across existing code that assumes that, and sometimes it might be possible to exploit that in an attack!

Reminders:

-   the type of a pointer is written like `int \ast` to mean &ldquo;pointer to integer.&rdquo;
-   use the `&` prefix operator to get a pointer to a variable. This even works for functions!

> Program 5. Write a C program called `print-sizes` that does the following (you can choose the names of any variables unless specified):
> 
> 1.  Declare an integer variable with a value of `978`.
> 2.  Declare an integer pointer variable.
> 3.  Declare a character array variable with size 200.
> 4.  Declare a character pointer variable.
> 5.  Print a table of the sizes of the following types on your system: `char`, `short`, `int`, `long`, `long long`, `float`, `double`, `char \ast`,  `int \ast`, `long \ast`, in that order. Each output line should look like:
>     
>         The size of int is 47
>     
>     (with the correct size, which is not 47!).
> 
> 6.  Print the message `The size of my character array is <size>` with the `<size` filled in by calling `sizeof`.
> 7.  Set the character pointer to point to your character array.
> 8.  Print the message `The size of my character pointer is <size>`, filling in the `<size>` of the pointer with `sizeof.`
> 9.  Set the integer pointer variable to point at the your integer variable.
> 10. Print the message `The size of my int pointer is <size>`, filling in the `<size>` of the pointer with `sizeof` using the name of your integer pointer variable.
> 11. Print the message `The size of what my integer pointer points at is <size>`, filling in `<size>` from an appropriate expression.
> 

> Question 22. What do you notice about the sizes of pointers?  Why do you think that is?
> 


> Question 23. Are the sizes of your integer pointer variable and what it points at the same or different? Why do you think that is?
> 

