
#!/bin/bash

PROF=/home/m/mounlaur
AFL_PATH=$PROF/AFL/afl-2.52b

# compile the example with instrumented code
# (seems required to enforce non 03 optimization to preserve crashes !)
echo "compile the pgm for AFL"
AFL_USE_ASAN=1 AFL_DONT_OPTIMIZE=1 $AFL_PATH/afl-gcc -g -fsanitize=address -O0 $1 

# launch the fuzzing campaign (ended by ^C)
echo "run AFL !"
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 AFL_SKIP_CPUFREQ=1 AFL_USE_ASAN=1 $AFL_PATH/afl-fuzz -m none -i in/ -o out/ ./a.out --
