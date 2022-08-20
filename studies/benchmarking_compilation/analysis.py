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
import subprocess
import argparse as ap
from termcolor import colored as cl
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

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
    
    # Extra info for compilation flags
    additional_flags = "-O3 -O1 -falign-functions=32"
    ldflags = ""
    if "fmt" in program:
        ldflags = "-lfmt"

    # Getting time statistics
    iter_mean = np.array( [] )
    for n in range( int( args.niter ) ):
        get_time = get_time_of( "g++ -std=c++17 {} {} {}".format( additional_flags, program, ldflags ) )
        iter_mean = np.append( iter_mean, get_time )
    mean, std = iter_mean.mean(), iter_mean.std()
    
    return mean, std

#################################################
#     do_plot
#################################################
def do_plot( data_programs, data_mean, data_std ):
    """
    Function used to plot results.

    Args:
        data_programs (pandas.Series): container for program names.
        data_mean (pandas.Series): container for mean values.
        data_std (pandas.Series): container for STD values.
    """

    # Variables
    fig, ax = plt.subplots()
    colors = [ "red", "green", "blue", "orange", "pink", "cyan" ]
    
    # Plotting results
    plt.bar( data_programs, data_mean, yerr = data_std, color = colors, capsize = 5 )
    
    # Adding labels
    for i, val in enumerate( data_programs ):
        ax.text( i - 0.18 , 0.01, round( data_mean[ i ], 3 ), color = "white", fontweight = "bold" )
    ax.set_xlabel( "Object / function" )
    ax.set_ylabel( "Time (s)" )
    
    # Other plot settings
    ax.set_title( r'''$\bf{Compilation \ time \ benchmarks}$ (stdout stream)''' )
    ax.yaxis.grid( True )
    ax.set_axisbelow( True )

    # Save plots
    path = "../../img/benchmarks/compilation_time"
    if not os.path.exists( path ):
        os.makedirs( path )
    plt.savefig( "{}/stdout_stream.png".format( path ) )
    
#################################################
#     Main
#################################################
def main():
    
    # Variables
    data_programs = pd.Series( [], dtype = str )
    data_mean = pd.Series( [], dtype = float )
    data_std = pd.Series( [], dtype = float )
    programs = [
        "programs/ptc.cpp",    # ptc
        "programs/fmt.cpp",    # fmt
        "programs/printf.cpp", # printf
        "programs/stdout.cpp"  # stdout
    ]
    
    # Launching benchmarks
    for index, program in enumerate( programs ):
        mean, std = get_time_of_stats( program )
        data_programs[ index ] =  program[9:-4]
        if "ptc" in program:
            data_programs[ index ] =  "ptc::print"
        elif "fmt" in program:
            data_programs[ index ] =  "fmt::print"
        elif "stdout" in program:
            data_programs[ index ] =  "std::cout"
        data_mean[ index ] =  mean
        data_std[ index ] =  std
    
    # Dataframe settings
    data_dict = { "Object / function": data_programs, "Compile Time (Mean) [s]": data_mean, "Compile Time (STD) [s]": data_std }
    data = pd.concat( data_dict, axis = 1 )
    
    # Doing plots
    if args.plots == "no":
        print( data.to_markdown() )
    elif args.plots == "yes":
        do_plot( data_programs, data_mean, data_std )

if __name__ == "__main__":

    # Parser settings
    parser = ap.ArgumentParser( description = "Parsing input file names." ) 
    parser.add_argument( "--niter", default = 100, help = "The number of benchmarking iterations." )
    parser.add_argument( "--plots", default = "no", help = "Produce or not plots." )
    args = parser.parse_args()
    
    # Main commands
    main()
