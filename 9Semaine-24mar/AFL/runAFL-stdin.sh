
PROF=/home/m/mounlaur
AFL_PATH=$PROF/AFL/afl-2.52b

# compile the example with instrumented code
# (seems required to enforce non 03 optimization to preserve crashes !)
echo "compile the pgm for AFL"
AFL_DONT_OPTIMIZE=1 $AFL_PATH/afl-gcc -g -O0 $1 

# launch the fuzzing campaign (ended by ^C)
echo "run AFL !"
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 AFL_SKIP_CPUFREQ=1 $AFL_PATH/afl-fuzz -i in/ -o out/ ./a.out --
