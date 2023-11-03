# BTP - Wireless Charging of Static Sensors in the Neighbourhood

## Input Parameters

`input.txt` contains the input details about the number of static sensors, $\gamma$ - Range of charging and the parameters of each static sensor, like `(X,Y)` coordinate, `b` - battery capacity, `S.O.C` - state of charge, `Cr` - Charging rate of $SS_i$, `Dr` - Discharging rate of $SS_i$.

After this the speed of WCV - $v$, constant of Charging - $\rho$ and Total Charge available on the WCV - $B$ is described.
The coordinates of Base Station are described as $BS_x$ and $BS_y$.

### Input format

$N$ $\gamma$ 

Each of the next N line contains 6 integers $SS_i$

$X_{i}$ &nbsp; $Y_{i}$ &nbsp; $b_{i}$ &nbsp; $S.O.C_{i}$ &nbsp; $C_r$ &nbsp; $D_r$

The next line contains 3 integers

$v$ &nbsp; $\rho$ &nbsp; $B$ &nbsp; 

The next line contains 2 integers: 


$BS_{x}$ &nbsp; $BS_{y}$ 


## To run the code

To generate the Sojourn Locations, Sequence of Sojourn Locations, C++ is used which takes input from input.txt and stores the output in `./DelanuayTriangleWithSLs` and `./WCVsPathTracing`

Install g++ compiler and set up the path of bin folder in PATH env variables. Then run the following code.

```
g++ main.cpp -o main
./main
```
The output is now stored in the 2 folders.


For visualization code, python is used. Install `python3` and install pip.

Virutal envrionment is to be created. It can be installed by
```
pip install virtualenv
```

Now create a virtualenvironment

```
python -m venv .venv
./venv/Scripts/activate
# Now you are inside virtualenv
pip install -r requirements.txt
python ./main.py
```

Visualization image will be stored in `./OuputImage`

