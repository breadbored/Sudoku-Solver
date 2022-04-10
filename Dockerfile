FROM gcc:bullseye

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/sudoku
WORKDIR /usr/src/sudoku

# This command compiles your app using GCC, adjust for your source code
RUN g++ -o sudoku main.cpp

# This command runs your application, comment out this line to compile only
CMD ["./sudoku"]

LABEL Name=sudoku Version=0.0.1
