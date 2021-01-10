# optee-fun

How to create a new TA and get it deployed in the filesystem
(tested and verified on OP-TEE 3.3.0, using both QEMU v7 and FVP)
================================================================================
   
   1.  Setup either QEMU or FVP (other build.git probably also works fine)
       according to: https://github.com/OP-TEE/build
       
   2.  $ cd <optee-root>/optee_examples
   
   3.  $ git checkout 3.3.0
   
   4.  $ wget http://people.linaro.org/~joakim.bech/new_ta/create_new_ta.patch
   
   5.  $ git am create_new_ta.patch
   
   6.  $ cd <optee-root>/build
   
   7.  $ make run
   
   8.  In the "normal world" terminal, run: my_ta
   

What changes did you do to make this work?
================================================================================

   1.  $ cd <optee-root>/optee_examples

   2.  Simply run:
          $ git log --stat -p 3.3.0..HEAD

       and study the changes.


Frequently asked questions
================================================================================

   1. Q: What else do I need to do to make my new TA to end up in the root fs?

      A: Nothing, the current makefile system in build.git will find the new TA
         in optee_examples automatically and put it into the root fs for you.

Joakim Bech - 2018-11-02
