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
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os
from tqdm import tqdm
from datetime import date

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
#     get_size_of
#################################################
def get_size_of( executable ):
    """
    Function used to get the size of an executable.

    Args:
        executable (str): the executable file name.

    Returns:
        float: the size of the executable.
    """
    
    command = "wc -c < bin/{}".format( executable )
    output = subprocess.check_output( [ "wc", "-c", "bin/{}".format( executable ) ] )
    if "fmt" in executable or "ptc" in executable:
        output = str( output )[2:-11]
    elif "printf" in executable or "stdout" in executable or "pprint" in executable:
        output = str( output )[2:-14]
    output = int( output )
    
    return output

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
    additional_flags = "-O3"
    ldflags = ""
    if "fmt" in program:
        ldflags = "-lfmt"

    # Getting time statistics
    iter_mean = np.array( [] )
    if not os.path.exists( "bin" ):
        os.makedirs( "bin" )
    for n in range( int( args.niter ) ):
        get_time = get_time_of( "g++ -std=c++17 {} {} {} -o bin/{}".format( additional_flags, program, ldflags, program[9:-4] ) )
        iter_mean = np.append( iter_mean, get_time )
    mean, std = iter_mean.mean(), iter_mean.std()
    
    return mean, std

#################################################
#     do_plot
#################################################
def do_plot( data_programs, data, data_std, atype = "Time" ):
    """
    Function used to plot results.

    Args:
        data_programs (pandas.Series): container for program names.
        data (pandas.Series): container for mean values.
        data_std (pandas.Series): container for STD values.
        type (str): the plot type.
    """

    # Variables
    fig, ax = plt.subplots()
    colors = [ "red", "green", "blue", "orange", "pink", "cyan" ]
    
    # Plotting results
    if atype == "Time":
        plt.bar( data_programs, data, yerr = data_std, color = colors, capsize = 5 )
    elif atype == "Size":
        plt.bar( data_programs, data, color = colors, capsize = 5 )
    
    # Adding labels
    for i, val in enumerate( data_programs ):
        if atype == "Time":
            ax.text( i - 0.18 , 0.01, round( data[ i ], 3 ), color = "white", fontweight = "bold" )
        elif atype == "Size":
            ax.text( i - 0.1 , 4, round( data[ i ], 3 ), color = "white", fontweight = "bold" )
    ax.set_xlabel( "Object / function" )
    if atype == "Time":
        ax.set_ylabel( "Time (s)" )
    elif atype == "Size":
        ax.set_ylabel( "Size (KiB)" )
    
    # Other plot settings
    current_date = date.today()
    if atype == "Time":
        ax.set_title( r'''$\bf{Compilation \ time \ benchmarks}$ (stdout stream)''' 
                      "\n"
                      r''' Date: (%(date)s)'''% { "date": current_date })
    elif atype == "Size":
        ax.set_title( r'''$\bf{Executable \ size}$ (stdout stream)'''
                      "\n"
                      r''' Date: (%(date)s)'''% { "date": current_date })
    ax.yaxis.grid( True )
    ax.set_axisbelow( True )

    # Save plots
    if args.macro == "yes":
        suffix = "_macro"
    elif args.macro == "no":
        suffix = ""
    if atype == "Time":
        path = "../../img/benchmarks/compilation_time"
    elif atype == "Size":
        path = "../../img/benchmarks/executable_size"
    if not os.path.exists( path ):
        os.makedirs( path )
    plt.savefig( "{}/stdout_stream{}.png".format( path, suffix ) )
    
#################################################
#     Main
#################################################
def main():
    
    # Variables
    data_programs = pd.Series( [], dtype = str )
    data_mean = pd.Series( [], dtype = float )
    data_std = pd.Series( [], dtype = float )
    data_size = pd.Series( [], dtype = int )
    programs = [
        "programs/ptc.cpp",    # ptc
        "programs/fmt.cpp",    # fmt
        "programs/printf.cpp", # printf
        "programs/stdout.cpp", # stdout
        "programs/pprint.cpp"  # pprint
    ]
    
    # Launching benchmarks
    print( "Generating data for compile time benchmarks:" )
    for index, program in enumerate( tqdm( programs ) ):
        mean, std = get_time_of_stats( program )
        data_programs[ index ] =  program[9:-4]
        if "ptc" in program:
            data_programs[ index ] =  "ptc::print"
        elif "fmt" in program:
            data_programs[ index ] =  "fmt::print"
        elif "stdout" in program:
            data_programs[ index ] =  "std::cout"
        elif "pprint" in program:
            data_programs[ index ] =  "pprint"
        data_mean[ index ] =  mean
        data_std[ index ] =  std

    # Computing executable size
    print( "Generating data for executable size:" )
    for index, program in enumerate( tqdm( programs ) ):
        size = get_size_of( program[9:-4] )
        data_size[ index ] = round( size / 1000 )
    
    # Dataframe settings
    data_dict = { "Object / function": data_programs, "Compile Time (Mean) [s]": data_mean, "Compile Time (STD) [s]": data_std, "Executable Size [KiB]": data_size }
    data = pd.concat( data_dict, axis = 1 )
    
    # Doing plots
    print( "Doing plots..." )
    if args.plots == "no":
        print( data.to_markdown() )
    elif args.plots == "yes":
        do_plot( data_programs, data_mean, data_std, atype = "Time" )
        do_plot( data_programs, data_size, data_std, atype = "Size" )
    print( "Done!" )

if __name__ == "__main__":

    # Parser settings
    parser = ap.ArgumentParser( description = "Parsing input file names." ) 
    parser.add_argument( "--niter", default = 100, help = "The number of benchmarking iterations." )
    parser.add_argument( "--plots", default = "no", help = "Produce or not plots." )
    parser.add_argument( "--macro", default = "no", help = "Enable or disable macro usage." )
    args = parser.parse_args()
    
    # Main commands
    main()
