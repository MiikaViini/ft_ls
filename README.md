# ft_ls
Implement of ls command

First project of Unix -branch.

This was introduction to navigate in filesystem with C.
I managed to implement several options, and tried also
implement `-F` (specifys if file is a dir, executable and so on) and `-G` (colours)
but noticed, that i would have to reconstruct my project big time,
so i ditched those bonuses.

Hardest part was definetely `-R` option which navigates recursively from given directory.
Solved that problem by asking other Unix people and watching videos from YouTube.
Also lot of 'Trial and error'.

Usage:
1. Clone the repository
```
git clone https://github.com/MiikaViini/ft_ls.git
```
2.Compile the project
```
make
```
3. Run
```
./ft_ls [-ARadflnrt1] [file ...]
```
