# Bitcoin-OTC Trust Network 

## Intro 

This repository was written by Kevin Le, Deepak Nair, Miguel Fernandez and Deniz Caglar for UIUC's  CS225 Spring 2021.
We implemented a graph data structure and graph algorithms based on [this bitcoin trading platform's](https://bitcoin-otc.com) web of trust network data. The .csv file for the database can be found in the repo and [here](http://snap.stanford.edu/data/soc-sign-bitcoin-otc.html) and you can find our video presentation [here](https://www.youtube.com/watch?v=68WcOoY4Y80&feature=youtu.be)

## Build

The project is compiled and built using clang++ and a Makefile. After meeting those dependencies, it is sufficient to run: 

```sh
make 
```

```sh 
make test 
```

To build the main executable and the testing suite. All of the object files will be placed in the .objs directory. All of the source 
files are in the local directory.
To include further test source files, it is sufficient to drop them in the tests/ folder and the Makefile will compile those with the 
initial testing suite when make test run again. 

To clear .o files and files written to the working directory due to write-to-file tests, the following command should be run

```sh
make clean
```

## Use 

The main executable provides access to the primary algorithms and functions of the Graph library, given a valid csv file in the expected format. The input csv file must constitute of a list of edges, where there's one edge per line and each line contains the following comma
separated values: source node index, destination node index, edge weight, time stamp - (optional to include, if not applicable to your graph include a dummy value)

Running 

```sh 
./main -h or ./main
```
will reveal the required syntax rules to run the executable or 

```sh
./test
```
will run the testing suite

It is possible to designate the input and output file locations by passing in the -i --infile and -o --ofile flags. The input file must be a csv file, while the output file will be a .txt file containing different types of information. 

It is also possible to give the input,output file flags and the functionality flags in any order, and run multiple algorithms on a single input with the same command. 

Some possible commands for the executable would be 

```sh 
./main --strongly-connected -i soc-sign-bitcoinotc.csv -o output1
```

```sh
./main --dijkstra-traversal 52 -i soc-sign-bitcoinotc.csv -o output6
```

```sh
./main --dijkstra-traversal 52 --strongly-connected -i soc-sign-bitcoinotc.csv -o output7
```

where the -i and -o flags will be followed by your chosen input and output filenames. If no input filename is provided the executable will 
look for a file called graph.csv in the local directory, and if no output name is provided the executable will output a file called 
graph_output_....txt where the suffix of the output file will be determined by the functionality run.

The repository also contains a python script called convert.py that can be used to convert the input csv files of the described format 
to a general use graphml format. To do this you could use : 

```sh 
./convert.py -i <input_filename> -o <output_filename> --weighted=True
```
to read weight data from the graph and apply our transformation function or 

```sh
./convert.py -i <input_filename> -o <output_filename> --weighted=False 
```
to have all the edges with a constant weight of 1.

-The transformation function on the weights can be removed by editing convert.py and was put in place to shift our edge weights 
from the [-10,10]  range to the [0,20] range to be able to run Dijkstra's Algorithm.-

This would take in a .csv file and output the same filename in a graphml format and with the .graphml prefix. If no input file is provided 
the script will look for graph.csv as an input and if no output filename is provided the output will be graph.graphml 

We recommend taking the output file of this conversion and importing it to [this website](https://graphonline.ru/en/) to be able to visualize it and
run a multitude of algorithms, some of which match our own,  on any graph you want.
