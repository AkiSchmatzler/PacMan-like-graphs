# PAC-Man like graphs  
### This project is part of the second Data structure and algorithms class (SDA2) at the University of Strasbourg   (4th Semester)
*(see assignement description (In french))*  

## Presentation  
You can create graphs with this program and also represent it as an image (in the image/ directory you'll find some examples of graphs)  
The images use the .pgm file extension

### Makefile  
`make` compiles the code, creates bin/ and obj/ directories. Execute code with ./bin/main  
`make clean` removes the binary files in bin/ and obj/ and removes those directories  
`make docs` creates the documentation for this project, using doxygen  
`make dist` creates an archive for this project in the dist/ repository that is created  
`make rmdist` removes the archive and the dist/ directory containing it  


### Execution  
After the files have been compiled, you can use `./bin/main` to execute the program  


### File organisation  
The source C file are in src/ directory, the headers are in the include/ directory  
The images are going to be put in the image/ directory  
:warning: Do not remove image/ directory.  
If you wanna keep an image, change it's name, the generic name is always image.pgm, which means an image will write over the current image.pgm file content (if this file exists in the image/ repository)  

