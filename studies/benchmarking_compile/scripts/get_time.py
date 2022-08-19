#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thr Aug 19 18:15:00 2022
Author: Gianluca Bianco
"""

#################################################
#     Modules
#################################################
import time
import doctest
import subprocess
import argparse as ap
from termcolor import colored as cl
import numpy as np

#################################################
#     get_time_of
#################################################
def get_time_of( bash_command ):
    """
    Function used to get the execution time of a bash command.

    Args:
        bash_command (str): the bash command.

    Returns:
        float: the execution time of the bash_command bash command.
    
    Testing:
        >>> 0.0009 <= get_time_of( "echo" ) <= 0.0017
        True
    """
    
    start_time = time.time()
    process = subprocess.Popen( bash_command.split(), stdout = subprocess.PIPE )
    output, error = process.communicate()
    end_time = time.time()
    elapsed_time = float( end_time - start_time )
    
    return elapsed_time

#################################################
#     get_time_of_stats
#################################################
def get_time_of_stats( program ):
    """
    Function used to get statistics from the compilation time of a C++ compilation.

    Args:
        program (str): the program name of the bash command execution through g++ std=c++17 program_name.cpp.

    Returns:
        float: mean and std of the compilation time.
    """
    
    additional_flags = "-O3 -O1 -falign-functions=32"
    ldflags = ""
    if "fmt" in program:
        ldflags = "-lfmt"

    iter_mean = np.array( [] )
    for n in range( int( args.niter ) ):
        get_time = get_time_of( "g++ -std=c++17 {} {} {}".format( additional_flags, program, ldflags ) )
        iter_mean = np.append( iter_mean, get_time )
    mean, std = iter_mean.mean(), iter_mean.std()
    
    return mean, std
    
#################################################
#     Main
#################################################
def main():
    
    # Variables
    programs = [
        "programs/stdout.cpp",
        "programs/ptc.cpp",
        "programs/fmt.cpp"
    ]
    
    # Launch benchmarks
    print()
    for program in programs:
        mean, std = get_time_of_stats( program )
        if args.plots == "no":
            print( "Program: ", cl( program, "green" ) )
            print( "- Mean: ", mean )
            print( "- STD: ", std )
            print()

if __name__ == "__main__":

    # Parser settings
    parser = ap.ArgumentParser( description = "Parsing input file names." ) 
    parser.add_argument( "--tests", default = "on", help = "Enable/disable tests (yes / no)." )
    parser.add_argument( "--niter", default = 100, help = "The number of benchmarking iterations." )
    parser.add_argument( "--plots", default = "no", help = "Produce or not plots." )
    args = parser.parse_args()
    
    # Main commands
    if args.tests == "on":
        doctest.testmod()
        main()
    elif args.tests == "off":
        main()
    else:
        raise RuntimeError( cl( "Inserted --tests option \"{}\" is not supported!".format( args.tests ), "red" ) )
