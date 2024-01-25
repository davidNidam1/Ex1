From gcc:latest

WORKDIR /user/src/ex1

COPY ./src/ .

RUN g++ -o ex1 ./Main.cpp ./BlackList.cpp ./BloomFilter.cpp ./Hashs.cpp ./InputOutput.cpp

CMD ["./ex1"]
