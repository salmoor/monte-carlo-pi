# PI approximation using Monte Carlo Method
This programs approximates the value of PI using Monte Carlo Method.

More about Monte Carlo Method: [Monte Carlo Method](https://en.wikipedia.org/wiki/Monte_Carlo_method)

Great video about PI approximation using Monte Carlo Method: [Monte Carlo integration](https://youtu.be/ELetCV_wX_c)

Since the task is *embarrassingly parallel* we implement and make use of parallel versions of popular higher order functions such as [Map](https://en.wikipedia.org/wiki/Map_(higher-order_function)), [Filter](https://en.wikipedia.org/wiki/Filter_(higher-order_function)) and [Fold](https://en.wikipedia.org/wiki/Fold_(higher-order_function)).

## Installation

To run the program you need to install Open MPI. For directions please refer to: [Open MPI](https://www.open-mpi.org/)

After the completion of the previous step, download and compile the source code by

```bash
$ git clone https://github.com/salmoor/monte-carlo-pi.git
$ cd monte-carlo-pi
$ make
```



## How to use

You can run the program by

```bash
mpirun np -4 mcpi 10000 
```

* where **np** options is the number of processors used, and **10000** is the number of experiments performed.

