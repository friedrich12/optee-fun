# optee-fun

### Deploy TA in filesystem
   
   1.  https://github.com/OP-TEE/build
       
   2.  $ cd <optee-root>/optee_examples
   
   3.  $ git checkout 3.3.0
   
   4.  Drag your application files to optee_examples
   
   4.  $ make run
   
   5.  In the "normal world" terminal, run: my_app
  

### NOTE

   The current makefile system in build.git will find the new TA
   in optee_examples automatically and put it into the root fs for you.

