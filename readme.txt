Self implemented ls

-use the make command to build the executable
-use ./main to run the executable
-the follwing tags are implemented:

    -l    use a long listing format
    -h    with -l, print sizes like 1K 234M 2G etc.
    -o    like -l, but do not list group information
    -d    list directories themselves, not their contents
    -f    generates an ls.txt   (!!not like original ls -f!!)
    --help   display this help and exit

    examples for using tags: ./main -l, ./main -lh, ./main -l -h

    if no directory is given the home directory is used

    examples for using own directory: ./main /home/user, ./main -lh /home/user


-use the make clean command to remove the executable
